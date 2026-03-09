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

#ifndef _HEAVY_CONTEXT_SHAPING_WRAPPING_HPP_
#define _HEAVY_CONTEXT_SHAPING_WRAPPING_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlDelay.h"
#include "HvControlBinop.h"
#include "HvMath.h"
#include "HvControlSystem.h"
#include "HvTable.h"
#include "HvSignalTabwrite.h"
#include "HvControlVar.h"
#include "HvControlSlice.h"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlCast.h"

class Heavy_shaping_wrapping : public HeavyContext {

 public:
  Heavy_shaping_wrapping(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_wrapping();

  const char *getName() override { return "shaping_wrapping"; }
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
  static void hTable_3QklcXLI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_F9g5Wy8E_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_SJ0gB1yJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_iVwfhTXR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_rWj1TqZe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_DDajsr7b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lhq9dOSM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6H081qgv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_X5eYrenJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_wcWf7DpM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_aFwgU9x2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sbrlGjid_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sh2P58S6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sLxpRxHw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KGLHLrMX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ySXyNRRE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_OkMvjctW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FBg0xaKm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_9TinTlOK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_4pnFzDn9_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_YJMnFHSW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_YUhHYvtj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UIDfjPBu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_QsnquvaL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_bxruSGW2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_TKHjdNg2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wekSdVih_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_N3y0tGbS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DtzaaSvi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_Xsg6dePe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_GjoAqeRn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Tno1EbYr_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_5aiMAhLk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_FrSavYkm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_gcwFR7qH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_7d3oCMTp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rbSA88YS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0KmvbAr8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vvXy7tye_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oBtGaAH6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8fS7edd7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_J8Sw5Xrl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qFnPtwk7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Gskz0pNt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MQBooOgD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Zhsji135_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_1Stx8dlK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_20D7MJYs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_ccSMjGO2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_KGXizcKQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_FierNd0G;
  SignalTabwrite sTabwrite_TCfmZD0E;
  SignalTabwrite sTabwrite_kbEl4u23;
  HvTable hTable_3QklcXLI;
  ControlDelay cDelay_SJ0gB1yJ;
  ControlVar cVar_iVwfhTXR;
  ControlSlice cSlice_rWj1TqZe;
  ControlSlice cSlice_DDajsr7b;
  ControlBinop cBinop_lhq9dOSM;
  ControlBinop cBinop_6H081qgv;
  ControlBinop cBinop_sbrlGjid;
  ControlBinop cBinop_sh2P58S6;
  ControlDelay cDelay_YJMnFHSW;
  ControlVar cVar_bxruSGW2;
  ControlBinop cBinop_wekSdVih;
  ControlBinop cBinop_N3y0tGbS;
  ControlBinop cBinop_DtzaaSvi;
  HvTable hTable_GjoAqeRn;
  ControlDelay cDelay_5aiMAhLk;
  ControlVar cVar_FrSavYkm;
  ControlSlice cSlice_gcwFR7qH;
  ControlSlice cSlice_7d3oCMTp;
  ControlBinop cBinop_rbSA88YS;
  ControlBinop cBinop_0KmvbAr8;
  ControlBinop cBinop_J8Sw5Xrl;
  ControlBinop cBinop_qFnPtwk7;
};

#endif // _HEAVY_CONTEXT_SHAPING_WRAPPING_HPP_
