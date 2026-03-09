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

#ifndef _HEAVY_CONTEXT_SHAPING_INVERT_HPP_
#define _HEAVY_CONTEXT_SHAPING_INVERT_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlBinop.h"
#include "HvControlSystem.h"
#include "HvControlSlice.h"
#include "HvTable.h"
#include "HvSignalVar.h"
#include "HvMath.h"
#include "HvControlDelay.h"
#include "HvSignalTabwrite.h"
#include "HvSignalPhasor.h"
#include "HvControlCast.h"
#include "HvControlVar.h"

class Heavy_shaping_invert : public HeavyContext {

 public:
  Heavy_shaping_invert(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_invert();

  const char *getName() override { return "shaping_invert"; }
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
  static void hTable_jxLhkdQN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_tjJmMbRH_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_3hxof349_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ZmG6RDjN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_XMp1TAY9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_hHEgXSRM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1Lqlubhs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_01LYgceK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_pDccOZOQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_d1liANLY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1IPKsKqS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5qKOGqvd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_36bCnqQb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_NBKxwvD4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_fUy3QZOQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gJvbDWYw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_EBk94ddc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_adBu2Trz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_WWlpf8AV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_9aqfjC1L_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_InKsCEk4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_KsYcjffk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jzbqiQ3j_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_d4XytP80_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_YHCFUVp2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_r9gsVJUH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_uimQyL8b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bdycZYnE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_76QhVcxM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_BSWbpcif_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_0oLKQM01_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_hdI9fTVY_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_3zKS5DtJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_2rX6Na5A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_bSRHweSM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_U726Oy8N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ACT4eDql_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_fEFchBa0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DQj6iAeY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_8RjeOd5M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Q7qxvIsP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jUDUUHe5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_58zuMeuP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_7cGm5KJQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_x62f07vx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3ebEaRyO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_mylelkhN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_PQLJjZ4I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_PRlu2O9k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_Whi7UCOJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_WX0C6DoN;
  SignalTabwrite sTabwrite_frxA4WOu;
  SignalPhasor sPhasor_vfBW6158;
  HvTable hTable_jxLhkdQN;
  ControlDelay cDelay_3hxof349;
  ControlVar cVar_ZmG6RDjN;
  ControlSlice cSlice_XMp1TAY9;
  ControlSlice cSlice_hHEgXSRM;
  ControlBinop cBinop_1Lqlubhs;
  ControlBinop cBinop_01LYgceK;
  ControlBinop cBinop_5qKOGqvd;
  ControlBinop cBinop_36bCnqQb;
  ControlDelay cDelay_InKsCEk4;
  ControlVar cVar_YHCFUVp2;
  ControlBinop cBinop_uimQyL8b;
  ControlBinop cBinop_bdycZYnE;
  ControlBinop cBinop_76QhVcxM;
  HvTable hTable_0oLKQM01;
  ControlDelay cDelay_3zKS5DtJ;
  ControlVar cVar_2rX6Na5A;
  ControlSlice cSlice_bSRHweSM;
  ControlSlice cSlice_U726Oy8N;
  ControlBinop cBinop_ACT4eDql;
  ControlBinop cBinop_fEFchBa0;
  ControlBinop cBinop_jUDUUHe5;
  ControlBinop cBinop_58zuMeuP;
  SignalVarf sVarf_RbiU3p9B;
  SignalVarf sVarf_TqXezXGM;
};

#endif // _HEAVY_CONTEXT_SHAPING_INVERT_HPP_
