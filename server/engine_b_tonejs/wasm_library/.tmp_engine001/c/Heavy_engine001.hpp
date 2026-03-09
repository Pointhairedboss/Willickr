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

#ifndef _HEAVY_CONTEXT_ENGINE001_HPP_
#define _HEAVY_CONTEXT_ENGINE001_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvControlCast.h"
#include "HvTable.h"
#include "HvSignalTabwrite.h"
#include "HvSignalVar.h"
#include "HvControlSlice.h"
#include "HvControlBinop.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvSignalPhasor.h"

class Heavy_engine001 : public HeavyContext {

 public:
  Heavy_engine001(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_engine001();

  const char *getName() override { return "engine001"; }
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
  static void hTable_ZpweBxzN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_eXrXauuD_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_TKUzT7rN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_4YOMvOxh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_zPe7Mmqc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_JMOCBOM8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7W6GDSnQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JpPq9aLM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_EnZAjazE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Ow5tONNj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_K0iiE0He_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MzFd42hq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7muUNmae_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_azVDFt31_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iEpsEW5P_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BTWsLS5K_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_GhJ0Vut3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_E0n6oXEP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_YakH2wmK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_CUlO9YyT_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_ClBLURpb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_waoK0naR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_34BMo2O2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Ivim4OYt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_lLr76hED_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_dHxWzgYE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sdfFFWpC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eSVIQ549_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1yghyHTD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_AG1Q1XY7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_bzGz0ns5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_YfNuxGyr_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_LLh93VqV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_2K2LYfgf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_IctiKfRe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_urVxCrDe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iyyDXHeN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qvAhOCUF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_tT7aN9E8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_dS11NMcb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_yecQvNlp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_S2pQ6Whf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_49WjPTxe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_geL2lfyv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ntGpbrKW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_zh5phfib_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_KDKlDp6v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WDotHt2g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_9JI9eEg5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_810FpEDx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_AqOYTY95_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_xMsqjdRF_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_hl86fsLb;
  SignalTabwrite sTabwrite_YjAfboUp;
  SignalTabwrite sTabwrite_36FSP8kv;
  HvTable hTable_ZpweBxzN;
  ControlDelay cDelay_TKUzT7rN;
  ControlVar cVar_4YOMvOxh;
  ControlSlice cSlice_zPe7Mmqc;
  ControlSlice cSlice_JMOCBOM8;
  ControlBinop cBinop_7W6GDSnQ;
  ControlBinop cBinop_JpPq9aLM;
  ControlBinop cBinop_MzFd42hq;
  ControlBinop cBinop_7muUNmae;
  ControlDelay cDelay_ClBLURpb;
  ControlVar cVar_lLr76hED;
  ControlBinop cBinop_sdfFFWpC;
  ControlBinop cBinop_eSVIQ549;
  ControlBinop cBinop_1yghyHTD;
  HvTable hTable_bzGz0ns5;
  ControlDelay cDelay_LLh93VqV;
  ControlVar cVar_2K2LYfgf;
  ControlSlice cSlice_IctiKfRe;
  ControlSlice cSlice_urVxCrDe;
  ControlBinop cBinop_iyyDXHeN;
  ControlBinop cBinop_qvAhOCUF;
  ControlBinop cBinop_S2pQ6Whf;
  ControlBinop cBinop_49WjPTxe;
  ControlVar cVar_9JI9eEg5;
  ControlBinop cBinop_810FpEDx;
};

#endif // _HEAVY_CONTEXT_ENGINE001_HPP_
