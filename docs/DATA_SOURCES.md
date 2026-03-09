# Real-time Data Sources for Willickr

Guide for the Antigravity Agent on connecting to real-time streams.

## 1. Astronomy & Space
*   **Satellite Orbits (TLE)**
    *   **Source**: [CelesTrak](https://celestrak.org/NORAD/documentation/gp-data-formats.php) or [TLE API](https://tle.ivanstanojevic.me/)
    *   *Usage*: Get Two-Line Element (TLE) sets for ISS, Hubble, Starlink.
    *   *Sonification*: Map Orbital Period to LFO rate; Altitude to Filter Cutoff.
*   **Constellations & Star Charts**
    *   **Source**: [AstronomyAPI](https://astronomyapi.com/)
    *   *Usage*: Get RA/Dec coordinates for stars/constellations.
    *   *Sonification*: Use Star Brightness -> Note Velocity; Position -> Pan/Pitch.
*   **Sun/Moon Phases**
    *   **Source**: [Open-Meteo Astronomy](https://open-meteo.com/en/docs/astronomy-api)
    *   *Usage*: Sunrise/Sunset times, Moon illumination %.

## 2. Geological & Seismic
*   **Earthquakes**
    *   **Source**: [USGS Earthquake Feed](https://earthquake.usgs.gov/earthquakes/feed/v1.0/geojson.php)
    *   *Format*: GeoJSON (Real-time).
    *   *Sonification*: Magnitude -> Bass Note Amplitude; Depth -> Reverb Size.

## 3. Public Transport (Melbourne)
*   **Tram/Train Disruptions**
    *   **Source**: [PTV Timetable API](https://www.ptv.vic.gov.au/footer/data-and-reporting/datasets/ptv-timetable-api/)
    *   *Status*: **Requires Developer Key**.
    *   *Endpoint*: `/v3/disruptions`
    *   *Sonification*: "Dirge mode" based on count of active disruptions. Map route_id to specific synth patches.

## 4. Weather & Tides
*   **General Weather**
    *   **Source**: [Open-Meteo](https://open-meteo.com/en/docs)
    *   *Usage*: Temp, Wind Speed, Rain.
*   **Tides & Marine**
    *   **Source**: [Open-Meteo Marine](https://open-meteo.com/en/docs/marine-weather-api) (or StormGlass).
    *   *Sonification*: Tide Height -> Master Volume or Drone Pitch (slow breathing effect).

## 5. NOAA / Oceanic & Atmospheric
*   **Space Weather (SWPC)**
    *   **Source**: [SWPC Data Service](https://services.swpc.noaa.gov/json/)
    *   *Data*: Planetary K-index, Solar wind plasma.
    *   *Sonification*: Magnetic storm intensity -> Distortion/Dissonance. Solar wind speed -> Granular grain size.
*   **Ocean Tides & Currents**
    *   **Source**: [CO-OPS API](https://api.tidesandcurrents.noaa.gov/api/prod/)
    *   *Data*: Water levels, currents, salinity.
    *   *Sonification*: Tidal cycles as extremely slow LFOs (0.00002 Hz) controlling harmony.
*   **Atmospheric Carbon**
    *   **Source**: [GML Trends](https://gml.noaa.gov/ccgg/trends/)
    *   *Data*: Daily CO2/CH4 averages.
    *   *Sonification*: "The Keeling Drone" - a rising pitch tracking CO2 levels over decades.
