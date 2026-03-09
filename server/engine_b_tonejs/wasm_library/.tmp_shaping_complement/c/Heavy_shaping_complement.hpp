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

#ifndef _HEAVY_CONTEXT_SHAPING_COMPLEMENT_HPP_
#define _HEAVY_CONTEXT_SHAPING_COMPLEMENT_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalPhasor.h"
#include "HvTable.h"
#include "HvControlSystem.h"
#include "HvSignalTabwrite.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvControlDelay.h"
#include "HvControlSlice.h"
#include "HvControlCast.h"
#include "HvControlBinop.h"
#include "HvSignalVar.h"

class Heavy_shaping_complement : public HeavyContext {

 public:
  Heavy_shaping_complement(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_complement();

  const char *getName() override { return "shaping_complement"; }
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
  static void hTable_e3w5D7xF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_e2f4Yn7s_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_XpOm5ORv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Xh0NKrLM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_XKnUeSfM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_EFEKrJpN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QQ2ufCgb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hV6Tmfc1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_o2bAU2jd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_eztmg7KT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_HPAjxX5B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jDecEOFF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ddelnjvo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_bXs1diS1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ItA6BF4z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_J5KFAFtd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Oli0OdIU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_pPooawgx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Wjlq1y1W_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_pENtbcl9_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_Z9x3FIeT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_3OPR8Dfb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MwjKoUxK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_5fmQX5no_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_z9uy4t3w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xthUoIt7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xzBq7nZj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_tZY1bCQM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MhjBpD0V_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_dheML6yA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_0oNBEAOt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_uRF5AUGn_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_xZP64MBH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ePvMJDYd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_U7JcEUiW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_14L10zOK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Gq0wYuzM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_fdWXW9v1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_dDsFGT7I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_aGkXlpw9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_OKfvMhcX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1wRkxaxJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_56qlsFbc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vddjBW0T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_v2pC2hMM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_avk5X5YG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_KlnVGKoM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3KcSjnXY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_wGt892rq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_yO3Q6UXe_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_umzVZH7q;
  SignalTabwrite sTabwrite_enf9Wm34;
  SignalPhasor sPhasor_WyalQe6W;
  HvTable hTable_e3w5D7xF;
  ControlDelay cDelay_XpOm5ORv;
  ControlVar cVar_Xh0NKrLM;
  ControlSlice cSlice_XKnUeSfM;
  ControlSlice cSlice_EFEKrJpN;
  ControlBinop cBinop_QQ2ufCgb;
  ControlBinop cBinop_hV6Tmfc1;
  ControlBinop cBinop_jDecEOFF;
  ControlBinop cBinop_Ddelnjvo;
  ControlDelay cDelay_Z9x3FIeT;
  ControlVar cVar_z9uy4t3w;
  ControlBinop cBinop_xzBq7nZj;
  ControlBinop cBinop_tZY1bCQM;
  ControlBinop cBinop_MhjBpD0V;
  HvTable hTable_0oNBEAOt;
  ControlDelay cDelay_xZP64MBH;
  ControlVar cVar_ePvMJDYd;
  ControlSlice cSlice_U7JcEUiW;
  ControlSlice cSlice_14L10zOK;
  ControlBinop cBinop_Gq0wYuzM;
  ControlBinop cBinop_fdWXW9v1;
  ControlBinop cBinop_1wRkxaxJ;
  ControlBinop cBinop_56qlsFbc;
  SignalVarf sVarf_cMrgoGQU;
  SignalVarf sVarf_K8tsVDOW;
};

#endif // _HEAVY_CONTEXT_SHAPING_COMPLEMENT_HPP_
