/**
 * Copyright (c) 2026 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_CONTEXT_SHAPING_TRIANGLE_HPP_
#define _HEAVY_CONTEXT_SHAPING_TRIANGLE_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlSlice.h"
#include "HvTable.h"
#include "HvControlSystem.h"
#include "HvSignalPhasor.h"
#include "HvControlVar.h"
#include "HvControlDelay.h"
#include "HvMath.h"
#include "HvControlBinop.h"
#include "HvSignalTabwrite.h"
#include "HvSignalVar.h"
#include "HvControlCast.h"

class Heavy_shaping_triangle : public HeavyContext {

 public:
  Heavy_shaping_triangle(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_triangle();

  const char *getName() override { return "shaping_triangle"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 0; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;


  /*
  * Code for expr~ implementation
  * Write out the generic header code
  */

  // per class code

  // per object code


  // static sendMessage functions
  static void hTable_PuWFNHLH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_uZKpTsfu_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_LmPMWKna_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_evavdJvI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_sgXAlODo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_jgPOP7cV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PgAfJ2z5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_du1o8cQ1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ypJgCZ2k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_qn9Vs4Y7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_zIeHnlV3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JrTQhWw8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_birpo0g5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_c3b6JSGl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Qi9LmQGk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xeBYkEmG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_llFzvK6B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_nVXscBWj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_D0C0FSYd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_nfWdeskQ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_9WG0zgNe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_2mOXvdYv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_x5bKISI1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_EEtDRAeE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_rFfSJGuf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_0Yt7cBQu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_zbYgLpVY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UtESpiKu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YFgiFHsw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_DfBlvnTh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_R24cwQB5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_7u6TJyxQ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_WhpkqLI8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_fopEutFu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_5R7YJ0f3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_j5ePV7rz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_J9Sdn6UL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_t0cSRj6B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_kAx27zwi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_DY3aTqzN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3LG5KxFA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_E6jxy9nd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BiuEO54M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ucTcGIV9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1pWrY1rN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vty6sSdD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_wtjmILjk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xY2OoaMl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_SSWmBs6j_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_IzqKRnvU_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_94pOkH3x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_IAMZZc2b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_NxqIRZtR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_xQJx80bV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7Q2amRe6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_OSJM3kWJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9eb1xOJO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_FxM0rXs4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_JBuhgIex_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_XJeMes0o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kzMPeujv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vbG9eo1A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_IA87yviA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xC94Kzuk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_MFNZ4f9p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9SyEqoNv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_mmE8TNXC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_yJbCyNoY_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_hhRfvzJA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ipSlSNem_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_X1fzVmg5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_XJ1CtmnF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SP86onZ3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wfuIaTF2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_TmjmwLoJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_BWNA1vTq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_yGLaYXTx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LVka6UmO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9bqKUHzU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_AWy2aHEp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wf6YpRUd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_5gcxoKVs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ykhdDUnb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_hsHrHURg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_je35nvvc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_CWAiIkPO_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_KSTKyBbo;
  SignalTabwrite sTabwrite_WWn8hI6u;
  SignalTabwrite sTabwrite_EM9scoWf;
  SignalTabwrite sTabwrite_wnUOdEVt;
  SignalPhasor sPhasor_8TbNCTjc;
  HvTable hTable_PuWFNHLH;
  ControlDelay cDelay_LmPMWKna;
  ControlVar cVar_evavdJvI;
  ControlSlice cSlice_sgXAlODo;
  ControlSlice cSlice_jgPOP7cV;
  ControlBinop cBinop_PgAfJ2z5;
  ControlBinop cBinop_du1o8cQ1;
  ControlBinop cBinop_JrTQhWw8;
  ControlBinop cBinop_birpo0g5;
  ControlDelay cDelay_9WG0zgNe;
  ControlVar cVar_rFfSJGuf;
  ControlBinop cBinop_zbYgLpVY;
  ControlBinop cBinop_UtESpiKu;
  ControlBinop cBinop_YFgiFHsw;
  HvTable hTable_R24cwQB5;
  ControlDelay cDelay_WhpkqLI8;
  ControlVar cVar_fopEutFu;
  ControlSlice cSlice_5R7YJ0f3;
  ControlSlice cSlice_j5ePV7rz;
  ControlBinop cBinop_J9Sdn6UL;
  ControlBinop cBinop_t0cSRj6B;
  ControlBinop cBinop_E6jxy9nd;
  ControlBinop cBinop_BiuEO54M;
  HvTable hTable_SSWmBs6j;
  ControlDelay cDelay_94pOkH3x;
  ControlVar cVar_IAMZZc2b;
  ControlSlice cSlice_NxqIRZtR;
  ControlSlice cSlice_xQJx80bV;
  ControlBinop cBinop_7Q2amRe6;
  ControlBinop cBinop_OSJM3kWJ;
  ControlBinop cBinop_XJeMes0o;
  ControlBinop cBinop_kzMPeujv;
  HvTable hTable_mmE8TNXC;
  ControlDelay cDelay_hhRfvzJA;
  ControlVar cVar_ipSlSNem;
  ControlSlice cSlice_X1fzVmg5;
  ControlSlice cSlice_XJ1CtmnF;
  ControlBinop cBinop_SP86onZ3;
  ControlBinop cBinop_wfuIaTF2;
  ControlBinop cBinop_LVka6UmO;
  ControlBinop cBinop_9bqKUHzU;
  SignalVarf sVarf_i8i0mi18;
  SignalVarf sVarf_Fcy6PSa9;
  SignalVarf sVarf_4s3gLK0b;
  SignalVarf sVarf_FAkBb17d;
};

#endif // _HEAVY_CONTEXT_SHAPING_TRIANGLE_HPP_
