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

#ifndef _HEAVY_CONTEXT_SHAPING_RECIPROCAL_HPP_
#define _HEAVY_CONTEXT_SHAPING_RECIPROCAL_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlVar.h"
#include "HvControlBinop.h"
#include "HvSignalPhasor.h"
#include "HvMath.h"
#include "HvControlCast.h"
#include "HvControlDelay.h"
#include "HvSignalTabwrite.h"
#include "HvControlSlice.h"
#include "HvTable.h"
#include "HvSignalVar.h"
#include "HvControlSystem.h"

class Heavy_shaping_reciprocal : public HeavyContext {

 public:
  Heavy_shaping_reciprocal(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_reciprocal();

  const char *getName() override { return "shaping_reciprocal"; }
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
  static void hTable_tef62hQG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_rV9kT2FS_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_YJiP10kQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_EAeYZX0S_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_oj283eDn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_lAlS2KLh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HDKDC7eO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wg4zwBe4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_6GWYtjpk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_wIXIowYD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_mOAclbc2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hAXXLvFK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mb9vcF4H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1PJrR324_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_v3mAGA6n_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3li97a46_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_6NPzS5uh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_nJ7KUw71_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_BfWIvXFk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_xu0quhpW_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_vzOABrQs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ov4cQ4w2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_HURYrTOV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_km5vNvAI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ZBvb3AmE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Jq4MwydP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4FZhjprY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6zpnJBQM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SwQt4PId_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_xJyMxtZC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_HYSVlqIQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_AOXBX0MH_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_zzWKaqGz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Ogo9KK2H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_VFds4idg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_0PNnRG2g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BdlfUwn6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0jgO8JGd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FVogeEPL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Oh451iNn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_lCmiMkzV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PyJs15UW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gX8mCwon_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_JzgWekvT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GsNVByzl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_7owNRPB3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_j7AtWYDZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_6EoqQUMW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_meOve4GM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_VN2Ukm1R_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_CSYcispo;
  SignalTabwrite sTabwrite_uxT82hlB;
  SignalPhasor sPhasor_AwCnZv0T;
  HvTable hTable_tef62hQG;
  ControlDelay cDelay_YJiP10kQ;
  ControlVar cVar_EAeYZX0S;
  ControlSlice cSlice_oj283eDn;
  ControlSlice cSlice_lAlS2KLh;
  ControlBinop cBinop_HDKDC7eO;
  ControlBinop cBinop_wg4zwBe4;
  ControlBinop cBinop_hAXXLvFK;
  ControlBinop cBinop_mb9vcF4H;
  ControlDelay cDelay_vzOABrQs;
  ControlVar cVar_ZBvb3AmE;
  ControlBinop cBinop_4FZhjprY;
  ControlBinop cBinop_6zpnJBQM;
  ControlBinop cBinop_SwQt4PId;
  HvTable hTable_HYSVlqIQ;
  ControlDelay cDelay_zzWKaqGz;
  ControlVar cVar_Ogo9KK2H;
  ControlSlice cSlice_VFds4idg;
  ControlSlice cSlice_0PNnRG2g;
  ControlBinop cBinop_BdlfUwn6;
  ControlBinop cBinop_0jgO8JGd;
  ControlBinop cBinop_PyJs15UW;
  ControlBinop cBinop_gX8mCwon;
  SignalVarf sVarf_0ZJAzFUg;
  SignalVarf sVarf_W0pawAJA;
};

#endif // _HEAVY_CONTEXT_SHAPING_RECIPROCAL_HPP_
