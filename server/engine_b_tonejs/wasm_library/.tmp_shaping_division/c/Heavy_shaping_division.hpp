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

#ifndef _HEAVY_CONTEXT_SHAPING_DIVISION_HPP_
#define _HEAVY_CONTEXT_SHAPING_DIVISION_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalVar.h"
#include "HvControlDelay.h"
#include "HvSignalPhasor.h"
#include "HvControlCast.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvTable.h"
#include "HvControlSlice.h"
#include "HvControlSystem.h"
#include "HvSignalTabwrite.h"
#include "HvControlBinop.h"

class Heavy_shaping_division : public HeavyContext {

 public:
  Heavy_shaping_division(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_division();

  const char *getName() override { return "shaping_division"; }
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
  static void hTable_7wzGNwE9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_DVv4fTAS_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_nScyR1lV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_bQBUrccI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_xTq6PDDm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9bLBHTgP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0Ha6mXzS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vnGzkq8m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_bNSvEZRM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_W9wzgs8o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_l8mIVAZH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mGuUv8kf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SG7b6sK4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DAnepnnx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_osrVR2sL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_udO0pVp5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Mgz16kIi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_bdqoQ8pN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_RXfIe5V8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_UZ8AuaDt_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_K0aVZBMh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Rj0pMk9I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_r2p8fSdV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Uywu5qBx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_nuQAxm4F_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_N87979ce_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qEydQWUJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CHuubXX5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_es73s0KG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_zRANnLt9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_TpDLXU7D_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_DZuNh0cq_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_TZX5XV7c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_08g0VMp2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_ek6XMBWG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_It4EP8c7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TmOZUJsK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PiRFDp2N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_CMzf0yRp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_TOrCvTAI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_n9WtDXw9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_KKx0xyjn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sm3azfzj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3RVKyboM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_q53JcDgU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_IWbEWDVn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_fWdu2H97_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_EfE0oiky_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_45T7hXbE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_d7DJxcG6_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_JxrsaphK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_fDSoP790_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_nRtzy4SD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9wYGsmrf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iqEqH7RD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IUBzu7uB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_INyVXtbc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_XYctH0SU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sYeTpzB1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_w9KBhe63_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TGAMnrTF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_faFO4PzY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_IjBEeNOH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3ctNdMtR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_tAZ7gF3z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ebfbEHiV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FHmpkV0L_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_mYvheMEJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_qBeWyX4E_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_L3oHnMdf;
  SignalTabwrite sTabwrite_EG1pq8ZG;
  SignalPhasor sPhasor_yfHANcLI;
  SignalTabwrite sTabwrite_fodSLJVl;
  SignalTabwrite sTabwrite_SbQYDNwh;
  HvTable hTable_7wzGNwE9;
  ControlDelay cDelay_nScyR1lV;
  ControlVar cVar_bQBUrccI;
  ControlSlice cSlice_xTq6PDDm;
  ControlSlice cSlice_9bLBHTgP;
  ControlBinop cBinop_0Ha6mXzS;
  ControlBinop cBinop_vnGzkq8m;
  ControlBinop cBinop_mGuUv8kf;
  ControlBinop cBinop_SG7b6sK4;
  ControlDelay cDelay_K0aVZBMh;
  ControlVar cVar_nuQAxm4F;
  ControlBinop cBinop_qEydQWUJ;
  ControlBinop cBinop_CHuubXX5;
  ControlBinop cBinop_es73s0KG;
  HvTable hTable_TpDLXU7D;
  ControlDelay cDelay_TZX5XV7c;
  ControlVar cVar_08g0VMp2;
  ControlSlice cSlice_ek6XMBWG;
  ControlSlice cSlice_It4EP8c7;
  ControlBinop cBinop_TmOZUJsK;
  ControlBinop cBinop_PiRFDp2N;
  ControlBinop cBinop_KKx0xyjn;
  ControlBinop cBinop_sm3azfzj;
  HvTable hTable_45T7hXbE;
  ControlDelay cDelay_JxrsaphK;
  ControlVar cVar_fDSoP790;
  ControlSlice cSlice_nRtzy4SD;
  ControlSlice cSlice_9wYGsmrf;
  ControlBinop cBinop_iqEqH7RD;
  ControlBinop cBinop_IUBzu7uB;
  ControlBinop cBinop_w9KBhe63;
  ControlBinop cBinop_TGAMnrTF;
};

#endif // _HEAVY_CONTEXT_SHAPING_DIVISION_HPP_
