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

#ifndef _HEAVY_CONTEXT_SHAPING_DIFFERENTIATION_HPP_
#define _HEAVY_CONTEXT_SHAPING_DIFFERENTIATION_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlSlice.h"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvControlVar.h"
#include "HvTable.h"
#include "HvControlCast.h"
#include "HvSignalTabwrite.h"
#include "HvMath.h"
#include "HvSignalVar.h"
#include "HvSignalDel1.h"
#include "HvControlBinop.h"
#include "HvSignalPhasor.h"

class Heavy_shaping_differentiation : public HeavyContext {

 public:
  Heavy_shaping_differentiation(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_differentiation();

  const char *getName() override { return "shaping_differentiation"; }
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
  static void hTable_vgjLf1yx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_4yto3r1j_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_CSsUKjW0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_qlARrarP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Ot7n02is_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_VfMoc2Xm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jRHRZUOY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_P9nzbruF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_B4e7HTqU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_jL6wYlD3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_olvCS106_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PcthOgEk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gZO6uuvp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_zWuZEPen_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xT4yAOrm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Qy1LqfAK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_w5ktd0Jf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_oKHR0Ilu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_izyrCKNG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_4YXK0jKs_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_szZOaSWZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_A4uB6g9l_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ptZM8KyL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_hhekCkNu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_gBgRrP6N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FuTiDtWS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wgkMrf6Z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YhZTVcy1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kHdqtNIz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_SYJerNPh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_YrkR6NU4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_K3Dyfvve_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_gcpjvaPN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_tNlALIOc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_nzXhGACZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_nttYJjhG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mX7OTQdn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eeGGtQ1M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_C4HXwb9h_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_jZVFGa8d_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MXE2Xpiw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TwpZvDig_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8vvrCEIF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iHxegBgy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_16Lzeh1r_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_M0kOvjzq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_muMBaOHl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Xf7NzomM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_ZoothvoL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_MSFlkM1m_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_DyzVy4Qe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_O9McjCkU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_NFwPuJ8o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_LwKGPlsU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_F2b4LL4Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_M5Tt5ffO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1pkRKLET_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_4y384Zop_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_rmUAQQOq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_k1XYScWt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_S2n6royc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_c5pjYMWo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3hCz0gAL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gqWbg9mf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_I5ZU60sk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UmZR5dWJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_Qv9OPxJL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_QiXiGI69_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_oxkoejTT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_kUzvyOyA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_iDcKAw0R_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_jkDE4AHS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lNBRPhIu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_H9tuLBAK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_NDCt7CL8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oMxJsqic_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_k34id42H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xf9tQF6J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mKoJdzDm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_w7qghfpA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9xLSacO3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Cqi9O63H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_JjKBQ5EI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VTklzR4T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_GIThdFdU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_901voABB_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_6Yygueok;
  SignalTabwrite sTabwrite_EdFOvAZi;
  SignalDel1 sDel1_xTVuXzpY;
  SignalTabwrite sTabwrite_j2cygHDq;
  SignalTabwrite sTabwrite_YQOU89sw;
  SignalDel1 sDel1_TFvoZ0ck;
  SignalTabwrite sTabwrite_URfiSrmB;
  HvTable hTable_vgjLf1yx;
  ControlDelay cDelay_CSsUKjW0;
  ControlVar cVar_qlARrarP;
  ControlSlice cSlice_Ot7n02is;
  ControlSlice cSlice_VfMoc2Xm;
  ControlBinop cBinop_jRHRZUOY;
  ControlBinop cBinop_P9nzbruF;
  ControlBinop cBinop_PcthOgEk;
  ControlBinop cBinop_gZO6uuvp;
  ControlDelay cDelay_szZOaSWZ;
  ControlVar cVar_gBgRrP6N;
  ControlBinop cBinop_wgkMrf6Z;
  ControlBinop cBinop_YhZTVcy1;
  ControlBinop cBinop_kHdqtNIz;
  HvTable hTable_YrkR6NU4;
  ControlDelay cDelay_gcpjvaPN;
  ControlVar cVar_tNlALIOc;
  ControlSlice cSlice_nzXhGACZ;
  ControlSlice cSlice_nttYJjhG;
  ControlBinop cBinop_mX7OTQdn;
  ControlBinop cBinop_eeGGtQ1M;
  ControlBinop cBinop_TwpZvDig;
  ControlBinop cBinop_8vvrCEIF;
  HvTable hTable_ZoothvoL;
  ControlDelay cDelay_DyzVy4Qe;
  ControlVar cVar_O9McjCkU;
  ControlSlice cSlice_NFwPuJ8o;
  ControlSlice cSlice_LwKGPlsU;
  ControlBinop cBinop_F2b4LL4Q;
  ControlBinop cBinop_M5Tt5ffO;
  ControlBinop cBinop_k1XYScWt;
  ControlBinop cBinop_S2n6royc;
  HvTable hTable_Qv9OPxJL;
  ControlDelay cDelay_oxkoejTT;
  ControlVar cVar_kUzvyOyA;
  ControlSlice cSlice_iDcKAw0R;
  ControlSlice cSlice_jkDE4AHS;
  ControlBinop cBinop_lNBRPhIu;
  ControlBinop cBinop_H9tuLBAK;
  ControlBinop cBinop_xf9tQF6J;
  ControlBinop cBinop_mKoJdzDm;
};

#endif // _HEAVY_CONTEXT_SHAPING_DIFFERENTIATION_HPP_
