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

#ifndef _HEAVY_CONTEXT_SHAPING_TRIANGLE2_HPP_
#define _HEAVY_CONTEXT_SHAPING_TRIANGLE2_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalVar.h"
#include "HvSignalTabwrite.h"
#include "HvControlVar.h"
#include "HvTable.h"
#include "HvControlBinop.h"
#include "HvSignalPhasor.h"
#include "HvControlSystem.h"
#include "HvControlDelay.h"
#include "HvMath.h"
#include "HvControlCast.h"
#include "HvControlSlice.h"

class Heavy_shaping_triangle2 : public HeavyContext {

 public:
  Heavy_shaping_triangle2(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_triangle2();

  const char *getName() override { return "shaping_triangle2"; }
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
  static void hTable_GMEHKzIL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_u3WLVEnK_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_ZMFAZ6dt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_7HRBEbAF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_61hIdMPF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_NtI1zjIV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PBRD9SVE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vltMA1hK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_cpEf5TxO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_1LW8BjkW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8VEvpJEe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_OafTGz5I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8omIYtP9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jn8IDNGu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_HGc5N64a_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_u9ZQtoFy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_zm40AcRF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_uf9PELUp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_qalIxo5m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_6YYEaU1G_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_fufNtvRL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_0h7FoCTV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_g1NuZQnu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_r3S5MddD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_P70HOU3Z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_qBxExFhC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_fgha1lIm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_OQ8Lbha5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xNLHnrmy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_YMPLGQs4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_DqV5UWOl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_rXolPKVN_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_t1wEGPJz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_f9jfwxMb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_lIL7fhJF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_NeRQZ67v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vJAvyeEF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_R0dKBHaq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_t29YIrnb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_udKEfoZd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MxWZZGvQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Of7krYgq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CSO7q6iE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vXJ2DeBT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_v5dfdMCL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_NM1Nr6zY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_fzOSjH3J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_bQ4PeirU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_P8i2qxAT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Jbbz37Hk_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_Ucnwuy1A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Hm4HzID2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_7Lm4RIvH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_QaC8oRdZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SIsnok9x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_M6WBHBRq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_JqckFzWv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_1tN2edwp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BvCT1Jcs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_t6zUAGE0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1n46z0xt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_P3ZhRAsN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Fn0XJClY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Vj6LFcgI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_4x4U6wIV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_IgGPNXYt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_QKLcogBJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_VF5qmoPV_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_BLhWKZ77_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_tj3Z1CSQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_77fPIGr7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_PRQ0LT1O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xgb4ha6S_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_726WQON9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_XrCs2qTc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_KCUniw3v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DKVj1VYH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_psWQk0R6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bqLXLDTA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KaCgXfoy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_njeu2U10_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iW8KulTG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_xq4ukfC2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VmUA0sOY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_ahMXR32m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_1vEi3zu3_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_XtgFaQpz;
  SignalTabwrite sTabwrite_J5J90O6S;
  SignalTabwrite sTabwrite_vb4o7aOS;
  SignalTabwrite sTabwrite_8QJGNRs7;
  SignalPhasor sPhasor_Vzu3ra0X;
  HvTable hTable_GMEHKzIL;
  ControlDelay cDelay_ZMFAZ6dt;
  ControlVar cVar_7HRBEbAF;
  ControlSlice cSlice_61hIdMPF;
  ControlSlice cSlice_NtI1zjIV;
  ControlBinop cBinop_PBRD9SVE;
  ControlBinop cBinop_vltMA1hK;
  ControlBinop cBinop_OafTGz5I;
  ControlBinop cBinop_8omIYtP9;
  ControlDelay cDelay_fufNtvRL;
  ControlVar cVar_P70HOU3Z;
  ControlBinop cBinop_fgha1lIm;
  ControlBinop cBinop_OQ8Lbha5;
  ControlBinop cBinop_xNLHnrmy;
  HvTable hTable_DqV5UWOl;
  ControlDelay cDelay_t1wEGPJz;
  ControlVar cVar_f9jfwxMb;
  ControlSlice cSlice_lIL7fhJF;
  ControlSlice cSlice_NeRQZ67v;
  ControlBinop cBinop_vJAvyeEF;
  ControlBinop cBinop_R0dKBHaq;
  ControlBinop cBinop_Of7krYgq;
  ControlBinop cBinop_CSO7q6iE;
  HvTable hTable_P8i2qxAT;
  ControlDelay cDelay_Ucnwuy1A;
  ControlVar cVar_Hm4HzID2;
  ControlSlice cSlice_7Lm4RIvH;
  ControlSlice cSlice_QaC8oRdZ;
  ControlBinop cBinop_SIsnok9x;
  ControlBinop cBinop_M6WBHBRq;
  ControlBinop cBinop_t6zUAGE0;
  ControlBinop cBinop_1n46z0xt;
  HvTable hTable_QKLcogBJ;
  ControlDelay cDelay_BLhWKZ77;
  ControlVar cVar_tj3Z1CSQ;
  ControlSlice cSlice_77fPIGr7;
  ControlSlice cSlice_PRQ0LT1O;
  ControlBinop cBinop_xgb4ha6S;
  ControlBinop cBinop_726WQON9;
  ControlBinop cBinop_psWQk0R6;
  ControlBinop cBinop_bqLXLDTA;
  SignalVarf sVarf_7APsJZeK;
  SignalVarf sVarf_oexnJTep;
  SignalVarf sVarf_GZ6nAkBL;
  SignalVarf sVarf_PQ7DwCqP;
};

#endif // _HEAVY_CONTEXT_SHAPING_TRIANGLE2_HPP_
