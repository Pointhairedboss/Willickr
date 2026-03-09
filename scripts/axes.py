#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
AXIS DISCOVERY / SERIALIZATION PLANNER (prototype)

Goal
----
Given "any data" (bytes or text), discover a serialization axis (an ordering)
that makes the data most *predictable / structured* when streamed 1-D.
This is useful as a data-prep stage before downstream processing (e.g. sonification,
summarization, clustering, change detection), especially when the input format
is unknown or mixed.

Core idea (techniques used)
---------------------------
1) Multi-direction sampling (works for ANY data)
   - We don't assume structure. We take bounded samples (head/mid/tail) and create
     multiple "views" (directions) of the data:
       * forward bytes, reversed bytes
       * stride-k subsequences (b[offset::k]) to expose interleaving / record widths
       * bit-plane projections to expose packed flags / low-level structure
       * (text-ish only) column-wise streams from delimiter-suspected lines

2) Windowing + simple statistics (cheap, explainable)
   - Each view stream is chunked into fixed-size windows.
   - For each window, we compute:
       * byte histogram (256 bins), normalized
       * Shannon entropy (0..8 bits/byte)
       * size (bytes)

3) Spectral seriation (eigenvectors)
   - Build a similarity graph between windows using cosine similarity of histograms.
   - Compute the graph Laplacian L = D - W.
   - Use the Fiedler vector (the eigenvector of the 2nd-smallest eigenvalue) to
     derive a 1-D ordering that places similar windows near each other.
   - Libraries: NumPy + SciPy linear algebra.

4) Hamiltonian-path-style refinement (TSP heuristics)
   - Treat windows as nodes with distance = 1 - cosine_similarity.
   - Refine the spectral order using a cheap 2-opt improvement (common TSP heuristic),
     producing a "shorter" path = smoother stream.

5) Scoring candidate axes (choose the best view)
   - For each view we compute:
       * mean adjacent cosine similarity in the final order  (higher is better)
       * compressibility proxy: gzip_ratio of the ordered stream (lower is better)
       * mean entropy (lower tends to indicate more structure)
   - Combine into a composite score and pick the top view(s).

6) Segmentation (optional but handy)
   - After ordering, compute adjacent distances and flag boundaries where
     distance spikes (mean + k*std). This yields "segments" / cluster boundaries.

What this does NOT do (yet)
---------------------------
- It does not fully parse domain-specific formats (PCAP, GeoTIFF, etc.).
  Instead, it finds an axis that tends to reveal structure. You can plug in
  format-specific detectors later as additional "views" or as an earlier stage.
- It does not do 2D/3D intrinsic-dimension estimation; this is the generic
  blob-first axis discovery engine. (You can add a "spatial view generator"
  once coordinate groups are detected.)

Dependencies
------------
Required:
  pip install numpy scipy

Standard library:
  gzip, io, argparse, math, re, statistics

Usage
-----
As a library:
  from axis_discovery import analyze_blob
  result = analyze_blob(data_bytes_or_text)

As a script:
  python axis_discovery.py --file input.bin
  python axis_discovery.py --file input.txt --assume-text

Output
------
A dict with:
  - best_view: name
  - best_order: list[int] ordering of window indices
  - segments: list[int] boundary indices in the ordered list
  - view_reports: metrics for each view
  - evidence: human-readable evidence strings

Hand-off integration idea
-------------------------
This module is a *planner*: it outputs an ordering and segments plus evidence.
Your next stage can:
  - reconstruct an "ordered stream" (bytes or tokens) and run additional detectors,
  - convert windows to a canonical feature table for downstream algorithms,
  - emit an explainable event stream (segments, change points, etc.).

"""

from __future__ import annotations

import argparse
import gzip
import io
import math
import os
import re
import statistics
from dataclasses import dataclass
from typing import Dict, Iterable, List, Optional, Sequence, Tuple, Union

import numpy as np

try:
    from scipy.linalg import eigh  # dense symmetric eigendecomposition
except Exception as e:
    raise RuntimeError(
        "This script requires SciPy. Install with: pip install scipy"
    ) from e


# ----------------------------
# Sampling utilities
# ----------------------------

@dataclass
class Samples:
    head: bytes
    mid: bytes
    tail: bytes
    text_lines: Optional[List[str]] = None


def _safe_decode_utf8(b: bytes) -> Tuple[str, bool]:
    """Decode as UTF-8; return (text, utf8_ok)."""
    try:
        return b.decode("utf-8"), True
    except UnicodeDecodeError:
        return b.decode("utf-8", errors="ignore"), False


def sample_blob(
    data: bytes,
    sample_size: int = 256_000,
    max_text_lines: int = 400,
) -> Samples:
    """
    Take bounded samples from head/mid/tail.
    Also extract some text lines if data looks text-ish.
    """
    n = len(data)
    if n <= sample_size:
        head = data
        mid = data
        tail = data
    else:
        head = data[:sample_size]
        mid_start = max(0, (n // 2) - (sample_size // 2))
        mid = data[mid_start: mid_start + sample_size]
        tail = data[-sample_size:]

    # Decide whether to attempt text line extraction (heuristic)
    head_txt, utf8_ok = _safe_decode_utf8(head)
    printable = sum(1 for ch in head_txt if ch.isprintable() or ch in "\r\n\t")
    printable_ratio = printable / max(1, len(head_txt))

    text_lines = None
    if printable_ratio > 0.85 and len(head_txt) > 0:
        # Take lines from head only (cheap and stable); you can add reservoir sampling later.
        lines = [ln for ln in head_txt.splitlines() if ln.strip()]
        text_lines = lines[:max_text_lines]

    return Samples(head=head, mid=mid, tail=tail, text_lines=text_lines)


# ----------------------------
# Basic stats
# ----------------------------

def shannon_entropy(b: bytes) -> float:
    """Shannon entropy of a byte sequence in bits/byte (0..8)."""
    if not b:
        return 0.0
    freq = np.bincount(np.frombuffer(b, dtype=np.uint8), minlength=256).astype(np.float64)
    p = freq / freq.sum()
    p = p[p > 0]
    return float(-(p * np.log2(p)).sum())


def gzip_ratio(b: bytes) -> float:
    """Compressed size / original size. Random-ish data tends to ~1.0 or higher."""
    if not b:
        return 1.0
    out = io.BytesIO()
    with gzip.GzipFile(fileobj=out, mode="wb") as f:
        f.write(b)
    return len(out.getvalue()) / len(b)


def byte_histogram_normalized(b: bytes) -> np.ndarray:
    """256-bin normalized histogram as float32."""
    if not b:
        return np.zeros((256,), dtype=np.float32)
    x = np.frombuffer(b, dtype=np.uint8)
    h = np.bincount(x, minlength=256).astype(np.float32)
    s = float(h.sum())
    if s <= 0:
        return np.zeros((256,), dtype=np.float32)
    return h / s


def cosine_similarity_matrix(X: np.ndarray) -> np.ndarray:
    """
    Cosine similarity for row vectors in X (assumed non-negative and normalized-ish).
    If rows are normalized to sum=1, cosine is still meaningful.
    """
    # L2-normalize for cosine
    norms = np.linalg.norm(X, axis=1, keepdims=True) + 1e-12
    Y = X / norms
    return Y @ Y.T


# ----------------------------
# View generators (multi-direction)
# ----------------------------

@dataclass
class View:
    name: str
    stream: bytes
    evidence: List[str]


def _make_stride_views(b: bytes, ks: Sequence[int] = (2, 3, 4, 5, 8, 16)) -> List[View]:
    views: List[View] = []
    for k in ks:
        for off in range(min(k, 8)):  # cap offsets to keep view count bounded
            s = b[off::k]
            views.append(View(
                name=f"stride_k{k}_off{off}",
                stream=s,
                evidence=[f"Stride view: stream = b[{off}::{k}] (detects interleaving/record widths)"],
            ))
    return views


def _make_bitplane_views(b: bytes) -> List[View]:
    """
    Extract bit-planes (0..7) as a byte stream of 0/1 bytes.
    Useful for packed flags; cheap and often surprisingly revealing.
    """
    arr = np.frombuffer(b, dtype=np.uint8)
    views: List[View] = []
    for bit in range(8):
        plane = ((arr >> bit) & 1).astype(np.uint8).tobytes()
        views.append(View(
            name=f"bitplane_{bit}",
            stream=plane,
            evidence=[f"Bit-plane view: ((byte >> {bit}) & 1) stream (detects packed structure/flags)"],
        ))
    return views


def _detect_delimiter(lines: List[str]) -> Optional[str]:
    """
    Very simple delimiter stability detector for text lines.
    Returns a likely delimiter or None.
    """
    if not lines or len(lines) < 20:
        return None
    candidates = [",", "\t", ";", "|"]
    best = (0.0, None)
    for d in candidates:
        counts = [ln.count(d) for ln in lines[:200]]
        if max(counts) == 0:
            continue
        # mode stability: fraction of lines with same delimiter count
        mode = max(set(counts), key=counts.count)
        stable = sum(1 for c in counts if c == mode) / len(counts)
        if stable > best[0]:
            best = (stable, d)
    stable, delim = best
    if stable >= 0.80:
        return delim
    return None


def _make_text_column_views(lines: List[str], delim: str, max_cols: int = 8) -> List[View]:
    """
    Build "column streams": take ith field across lines and concatenate as bytes.
    This is a strong "direction change" for semi-structured tabular text.
    """
    split = [ln.split(delim) for ln in lines[:400]]
    col_count = min(max(len(r) for r in split if r), max_cols)
    views: List[View] = []
    for i in range(col_count):
        col_vals = []
        for row in split:
            if i < len(row):
                col_vals.append(row[i].strip())
        joined = "\n".join(col_vals).encode("utf-8", errors="ignore")
        views.append(View(
            name=f"text_col_{i}",
            stream=joined,
            evidence=[f"Text column view i={i} using delimiter '{delim}' (seriation across fields)"],
        ))
    return views


def generate_views(samples: Samples) -> List[View]:
    """
    Generate a bounded set of candidate "directions" / views from samples.
    We use the head sample for view generation; mid/tail help validation later.
    """
    b = samples.head  # use head for view streams (bounded); you can extend to aggregate head/mid/tail.
    views: List[View] = [
        View("bytes_forward", b, ["Forward byte stream (baseline view)"]),
        View("bytes_reverse", b[::-1], ["Reversed byte stream (catches tail-anchored structure)"]),
    ]
    views.extend(_make_stride_views(b))
    views.extend(_make_bitplane_views(b))

    # Text-ish: delimiter -> column views
    if samples.text_lines:
        delim = _detect_delimiter(samples.text_lines)
        if delim:
            views.extend(_make_text_column_views(samples.text_lines, delim))

    return views


# ----------------------------
# Windowing + feature extraction
# ----------------------------

@dataclass
class WindowFeatures:
    hist: np.ndarray   # shape (256,)
    entropy: float
    size: int


def window_stream(
    stream: bytes,
    window_size: int = 4096,
    max_windows: int = 160,
) -> Tuple[List[bytes], List[WindowFeatures]]:
    """
    Split stream into fixed-size windows. Cap count to keep spectral ops cheap.
    """
    if not stream:
        return [], []
    n = len(stream)
    # Determine windows; take first max_windows windows (simple); you can also stride or sample windows.
    windows: List[bytes] = []
    feats: List[WindowFeatures] = []
    count = 0
    for start in range(0, n, window_size):
        if count >= max_windows:
            break
        w = stream[start:start + window_size]
        if not w:
            break
        h = byte_histogram_normalized(w)
        e = shannon_entropy(w)
        windows.append(w)
        feats.append(WindowFeatures(hist=h, entropy=e, size=len(w)))
        count += 1
    return windows, feats


# ----------------------------
# Spectral ordering (Fiedler vector)
# ----------------------------

def spectral_order(histograms: np.ndarray) -> Tuple[List[int], Dict[str, float]]:
    """
    Compute a 1-D ordering via spectral seriation.
    - Build cosine similarity matrix W.
    - Laplacian L = D - W.
    - Get eigenpairs of L; pick the Fiedler vector.
    - Order indices by Fiedler vector values.
    Returns (order, diagnostics).
    """
    n = histograms.shape[0]
    if n <= 2:
        return list(range(n)), {"n": float(n), "note": 1.0}

    W = cosine_similarity_matrix(histograms).astype(np.float64)
    # Remove self-similarity to avoid trivial dominance (optional; can help)
    np.fill_diagonal(W, 0.0)

    D = np.diag(W.sum(axis=1))
    L = D - W

    # Dense eigendecomposition (n is capped ~160). For larger, switch to sparse eigsh.
    evals, evecs = eigh(L)

    # Pick the smallest eigenvector with eigenvalue > eps (Fiedler-ish)
    eps = 1e-9
    idx = None
    for i, ev in enumerate(evals):
        if ev > eps:
            idx = i
            break
    if idx is None:
        # Graph fully disconnected or numerically degenerate; fall back to identity
        return list(range(n)), {"n": float(n), "degenerate": 1.0}

    fiedler = evecs[:, idx]
    # Ensure native int types for JSON serialization
    order = [int(x) for x in np.argsort(fiedler)]

    diagnostics = {
        "n": float(n),
        "fiedler_eigenvalue": float(evals[idx]),
        "min_eigenvalue": float(evals[0]),
        "max_eigenvalue": float(evals[-1]),
    }
    return order, diagnostics


# ----------------------------
# Hamiltonian-path style refinement (2-opt)
# ----------------------------

def _path_distance(order: Sequence[int], dist: np.ndarray) -> float:
    return float(sum(dist[order[i], order[i + 1]] for i in range(len(order) - 1)))


def two_opt_refine(
    order: List[int],
    dist: np.ndarray,
    max_passes: int = 4,
    max_swaps_per_pass: int = 10_000,
) -> List[int]:
    """
    2-opt path improvement heuristic:
    Try reversing segments to reduce total path length.
    This approximates a short Hamiltonian path / TSP path.
    """
    n = len(order)
    if n < 5:
        return order

    improved = True
    passes = 0
    while improved and passes < max_passes:
        improved = False
        swaps = 0
        passes += 1

        # O(n^2) worst-case; bounded by caps
        for i in range(1, n - 2):
            for k in range(i + 1, n - 1):
                if swaps >= max_swaps_per_pass:
                    break
                a, b = order[i - 1], order[i]
                c, d = order[k], order[k + 1]
                # current edges: (a-b) + (c-d)
                # proposed edges: (a-c) + (b-d) after reversing [i..k]
                cur = dist[a, b] + dist[c, d]
                new = dist[a, c] + dist[b, d]
                if new + 1e-12 < cur:
                    order[i:k + 1] = reversed(order[i:k + 1])
                    improved = True
                    swaps += 1
            if swaps >= max_swaps_per_pass:
                break

    return order


# ----------------------------
# Scoring + segmentation
# ----------------------------

@dataclass
class ViewReport:
    view_name: str
    n_windows: int
    score: float
    mean_adj_cosine: float
    gzip_ratio_ordered: float
    mean_entropy: float
    evidence: List[str]
    spectral_diag: Dict[str, float]
    segments: List[int]


def segment_by_spikes(adj_dist: List[float], z: float = 2.0) -> List[int]:
    """
    Simple segmentation: mark boundaries where adjacent distance spikes.
    Returns boundary indices in the ordered list (i.e., boundary occurs BEFORE index i).
    """
    if len(adj_dist) < 8:
        return []
    mu = statistics.mean(adj_dist)
    sd = statistics.pstdev(adj_dist) or 1e-9
    thresh = mu + z * sd
    boundaries = [i + 1 for i, d in enumerate(adj_dist) if d > thresh]
    return boundaries


def score_view(
    windows: List[bytes],
    feats: List[WindowFeatures],
    order: List[int],
    histograms: np.ndarray,
) -> Tuple[float, float, float, float, List[int]]:
    """
    Compute metrics and a composite score.

    Metrics:
      - mean_adj_cosine: average cosine similarity between consecutive windows (higher better)
      - gzip_ratio_ordered: gzip_ratio(concat(ordered_windows)) (lower better)
      - mean_entropy: average Shannon entropy of windows (lower often indicates structure)

    Composite score (tunable):
      score = 1.2 * mean_adj_cosine
            + 1.0 * (1 - gzip_ratio_ordered_clamped)
            + 0.4 * (1 - mean_entropy/8)

    Note: gzip_ratio can be >1 for incompressible data; we clamp to [0, 1.25] before scoring.
    """
    n = len(order)
    if n <= 1:
        return 0.0, 0.0, 1.0, 8.0, []

    # Cosine similarity is dot product of L2-normalized histograms.
    X = histograms.astype(np.float64)
    norms = np.linalg.norm(X, axis=1, keepdims=True) + 1e-12
    Y = X / norms
    adj_cos = [float(Y[order[i]] @ Y[order[i + 1]]) for i in range(n - 1)]
    mean_adj_cos = float(statistics.mean(adj_cos)) if adj_cos else 0.0

    # Ordered stream compressibility
    ordered_stream = b"".join(windows[i] for i in order)
    gr = gzip_ratio(ordered_stream)
    gr_clamped = max(0.0, min(1.25, gr))  # allow slightly >1
    compress_term = 1.0 - (gr_clamped / 1.25)  # map [0..1.25] -> [1..0]

    mean_ent = float(statistics.mean(f.entropy for f in feats)) if feats else 8.0
    entropy_term = 1.0 - (mean_ent / 8.0)

    score = (1.2 * mean_adj_cos) + (1.0 * compress_term) + (0.4 * entropy_term)

    # Segment boundaries where adjacency distance spikes (distance = 1 - cosine)
    adj_dist = [1.0 - c for c in adj_cos]
    segments = segment_by_spikes(adj_dist, z=2.0)

    return score, mean_adj_cos, gr, mean_ent, segments


# ----------------------------
# Main analysis function
# ----------------------------

def analyze_blob(
    data: Union[bytes, str],
    user_hint: Optional[str] = None,
    sample_size: int = 256_000,
    window_size: int = 4096,
    max_windows: int = 160,
    max_views: int = 80,
) -> Dict[str, object]:
    """
    Analyze a blob and choose a best "axis" (view + ordering).

    Parameters
    ----------
    data: bytes or str
    user_hint: optional soft prior label (not enforced)
    sample_size: bytes per head/mid/tail sample
    window_size: window size for feature extraction
    max_windows: cap windows to keep spectral ops cheap
    max_views: cap number of views evaluated

    Returns
    -------
    dict with best_view, best_order, segments, view_reports, evidence
    """
    if isinstance(data, str):
        raw = data.encode("utf-8", errors="ignore")
    else:
        raw = data

    samples = sample_blob(raw, sample_size=sample_size)

    # Generate candidate views (multi-direction + optional text columns)
    views = generate_views(samples)
    if len(views) > max_views:
        views = views[:max_views]

    view_reports: List[ViewReport] = []
    evidence_global: List[str] = []

    # Global evidence: entropy/compressibility quick look
    ent_head = shannon_entropy(samples.head)
    gr_head = gzip_ratio(samples.head)
    evidence_global.append(f"Head sample entropy={ent_head:.3f} bits/byte (0..8).")
    evidence_global.append(f"Head sample gzip_ratio={gr_head:.3f} (lower => more compressible).")

    if ent_head > 7.7 and gr_head > 0.98:
        evidence_global.append(
            "Data looks high-entropy/incompressible at the byte level (may be compressed/encrypted/noise). "
            "Axis discovery may still find local structure, but expectations should be modest."
        )

    # Evaluate each view
    for v in views:
        windows, feats = window_stream(v.stream, window_size=window_size, max_windows=max_windows)
        if len(windows) < 6:
            # Not enough structure to order
            continue

        H = np.stack([f.hist for f in feats], axis=0)  # (n, 256)

        # Spectral ordering (Fiedler eigenvector)
        order0, diag = spectral_order(H)

        # Distance matrix for refinement: dist = 1 - cosine_similarity
        W = cosine_similarity_matrix(H).astype(np.float64)
        np.fill_diagonal(W, 1.0)
        dist = 1.0 - W

        # Hamiltonian-ish refinement (2-opt)
        order = two_opt_refine(order0, dist)

        # Score
        score, mean_adj_cos, gr, mean_ent, segments = score_view(windows, feats, order, H)

        # Soft prior boost if user_hint matches view type keywords (tiny nudge, not override)
        if user_hint:
            hint = user_hint.lower()
            if ("text" in hint and v.name.startswith("text_col_")) or ("stride" in hint and v.name.startswith("stride_")):
                score += 0.05

        view_reports.append(ViewReport(
            view_name=v.name,
            n_windows=len(windows),
            score=score,
            mean_adj_cosine=mean_adj_cos,
            gzip_ratio_ordered=gr,
            mean_entropy=mean_ent,
            evidence=v.evidence,
            spectral_diag=diag,
            segments=segments,
        ))

    if not view_reports:
        return {
            "best_view": None,
            "best_order": None,
            "segments": [],
            "view_reports": [],
            "evidence": evidence_global + ["No view produced enough windows to analyze (input too small or too uniform)."],
        }

    view_reports.sort(key=lambda r: r.score, reverse=True)
    best = view_reports[0]

    # Provide compact evidence: top 5 views
    top_k = view_reports[:5]
    evidence = list(evidence_global)
    evidence.append("Top view candidates (higher score => smoother/more compressible/more structured ordering):")
    for r in top_k:
        evidence.append(
            f"  - {r.view_name}: score={r.score:.3f}, "
            f"adj_cos={r.mean_adj_cosine:.3f}, gzip_ratio={r.gzip_ratio_ordered:.3f}, mean_entropy={r.mean_entropy:.3f}"
        )

    return {
        "best_view": best.view_name,
        "best_order": best,  # full report object (contains ordering? no; ordering is per-run; see below)
        "segments": best.segments,
        "view_reports": view_reports,
        "evidence": evidence,
        # NOTE: For handoff, you probably want to also return the ordered window indices and/or the ordered stream.
        # This prototype returns reports; to keep memory use down, it does not store raw windows per view in the report.
    }


# ----------------------------
# Convenience: run best view and export ordered stream + order indices
# ----------------------------

def run_best_axis(
    data: Union[bytes, str],
    sample_size: int = 256_000,
    window_size: int = 4096,
    max_windows: int = 160,
    max_views: int = 80,
) -> Dict[str, object]:
    """
    One-shot helper that returns:
      - best view name
      - ordered window indices
      - ordered bytes stream (for the sampled view only)
      - segment boundaries
      - evidence / metrics
    """
    if isinstance(data, str):
        raw = data.encode("utf-8", errors="ignore")
    else:
        raw = data

    samples = sample_blob(raw, sample_size=sample_size)
    views = generate_views(samples)[:max_views]

    best_payload: Optional[Dict[str, object]] = None
    best_score = -1e9
    
    # Track second best axis
    second_best_payload: Optional[Dict[str, object]] = None
    second_best_score = -1e9

    # Quick global evidence
    ent_head = shannon_entropy(samples.head)
    gr_head = gzip_ratio(samples.head)

    for v in views:
        windows, feats = window_stream(v.stream, window_size=window_size, max_windows=max_windows)
        if len(windows) < 6:
            continue
        H = np.stack([f.hist for f in feats], axis=0)

        order0, diag = spectral_order(H)
        W = cosine_similarity_matrix(H).astype(np.float64)
        np.fill_diagonal(W, 1.0)
        dist = 1.0 - W
        order = two_opt_refine(order0, dist)

        score, mean_adj_cos, gr, mean_ent, segments = score_view(windows, feats, order, H)

        if score > best_score:
            # Demote current best to second best
            second_best_score = best_score
            second_best_payload = best_payload
            
            best_score = score
            ordered_stream = b"".join(windows[i] for i in order)
            
            # Construct Timeline (Metadata for each window in the ordered stream)
            timeline = []
            for idx_ in order:
                f = feats[idx_] # WindowFeatures object
                # We can compute more stats like variance here if needed, but entropy is key
                timeline.append({
                    "view_index": int(idx_), # Original index in the view (provenance)
                    "entropy": float(f.entropy),
                    "size": int(f.size)
                })

            best_payload = {
                "best_view": v.name,
                "score": score,
                "order_indices": order,
                "segments": segments,
                "timeline": timeline, # NEW: Time-series metadata
                "metrics": {
                    "mean_adj_cosine": mean_adj_cos,
                    "gzip_ratio_ordered": gr,
                    "mean_entropy": mean_ent,
                    "spectral_diag": diag,
                    "head_entropy": ent_head,
                    "head_gzip_ratio": gr_head,
                },
                "evidence": v.evidence,
                "ordered_stream": ordered_stream,
            }
        elif score > second_best_score:
            # This is the new second best
            second_best_score = score
            second_ordered_stream = b"".join(windows[i] for i in order)
            
            second_timeline = []
            for idx_ in order:
                f = feats[idx_]
                second_timeline.append({
                    "view_index": int(idx_),
                    "entropy": float(f.entropy),
                    "size": int(f.size)
                })
            
            second_best_payload = {
                "second_view": v.name,
                "score": score,
                "order_indices": order,
                "segments": segments,
                "timeline": second_timeline,
                "ordered_stream": second_ordered_stream,
            }

    if best_payload is None:
        # Fallback: Just use the first view (Head) in identity order
        # We need to construct a basic timeline so the UI works
        fallback_stream = data[:sample_size] if isinstance(data, (bytes, str)) else b""
        if isinstance(fallback_stream, str): fallback_stream = fallback_stream.encode('utf-8')
        
        # Create Dummy Windows
        fb_windows, fb_feats = window_stream(fallback_stream, window_size=window_size)
        fb_timeline = []
        for i, f in enumerate(fb_feats):
            fb_timeline.append({
                "view_index": i,
                "entropy": float(f.entropy),
                "size": int(f.size)
            })
            
        return {
            "best_view": "raw_fallback",
            "score": 0.0,
            "order_indices": list(range(len(fb_windows))),
            "segments": [],
            "timeline": fb_timeline, # Fallback Timeline
            "metrics": {"mean_entropy": 4.0 if not fb_feats else statistics.mean([f.entropy for f in fb_feats])},
            "evidence": ["Analysis failed to converge, using raw data feedback."],
            "ordered_stream": fallback_stream,
        }

    # Add second axis info to best payload if available
    if second_best_payload is not None:
        best_payload["second_axis"] = second_best_payload
    
    return best_payload


# ----------------------------
# CLI
# ----------------------------

def _read_file(path: str) -> bytes:
    with open(path, "rb") as f:
        return f.read()


def main() -> None:
    ap = argparse.ArgumentParser(description="Axis discovery via multi-direction entropy + spectral seriation + 2-opt refinement")
    ap.add_argument("--file", required=True, help="Path to input file (binary or text)")
    ap.add_argument("--assume-text", action="store_true", help="Treat file as UTF-8 text (lossy if invalid)")
    ap.add_argument("--sample-bytes", type=int, default=256_000, help="Sample size for head/mid/tail")
    ap.add_argument("--window-bytes", type=int, default=4096, help="Window size for feature extraction")
    ap.add_argument("--max-windows", type=int, default=160, help="Max windows per view")
    ap.add_argument("--max-views", type=int, default=80, help="Max views to evaluate")
    ap.add_argument("--dump-ordered", default=None, help="If set, write ordered sample stream to this path")
    args = ap.parse_args()

    raw = _read_file(args.file)
    if args.assume_text:
        txt, _ = _safe_decode_utf8(raw)
        data: Union[str, bytes] = txt
    else:
        data = raw

    result = run_best_axis(
        data,
        sample_size=args.sample_bytes,
        window_size=args.window_bytes,
        max_windows=args.max_windows,
        max_views=args.max_views,
    )

    print("=== Axis Discovery Result ===")
    print(f"best_view: {result['best_view']}")
    print(f"score: {result['score']}")
    print(f"segments (boundary indices): {result['segments']}")
    print("metrics:")
    for k, v in result["metrics"].items():
        print(f"  - {k}: {v}")
    print("evidence:")
    for e in result["evidence"]:
        print(f"  * {e}")

    if args.dump_ordered:
        out_path = args.dump_ordered
        with open(out_path, "wb") as f:
            f.write(result["ordered_stream"])
        print(f"Wrote ordered stream (sampled view) to: {out_path} ({len(result['ordered_stream'])} bytes)")


if __name__ == "__main__":
    main()
