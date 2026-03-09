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

#ifndef _HEAVY_CONTEXT_SPARKS1_HPP_
#define _HEAVY_CONTEXT_SPARKS1_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlDelay.h"
#include "HvSignalPhasor.h"
#include "HvSignalTabwrite.h"
#include "HvControlSlice.h"
#include "HvControlCast.h"
#include "HvControlVar.h"
#include "HvTable.h"
#include "HvSignalRPole.h"
#include "HvControlRandom.h"
#include "HvControlUnop.h"
#include "HvSignalVar.h"
#include "HvControlSystem.h"
#include "HvSignalDel1.h"
#include "HvControlBinop.h"
#include "HvMath.h"

class Heavy_sparks1 : public HeavyContext {

 public:
  Heavy_sparks1(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_sparks1();

  const char *getName() override { return "sparks1"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 2; }

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
  static void cSwitchcase_1NggNnye_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_yWaklT4T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_qbwFq4h2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_SuomrmVr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_jorbmrrf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3a1zLt13_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_a8xA8XOb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_86QhSULN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_V627o2yZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xMr2DZrf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_pOdg35y1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wNT68zic_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wN2gzfdf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vr6acgRQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Xl2T8bUt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_uOYL5zo5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_kgZO27Fw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_du9FeVsH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Yi6NLAYc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_aA2ju1mj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_eYJUOKNm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ROkzlUGp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_oqh0ExWh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_06YwPxOZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_3Cky9xh8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Mu3tFzNj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_84hXiBZp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_oF0gD4S8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9Ds2hW8a_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_nZMxBDhx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_uW6y21VK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_k4lJol4A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_q5y9Nqv5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_OFBsFTl0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bMf3eqNy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_lMln8v7c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KzuiE9bI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_z64uc01b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Td9jo79W_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4DIOBouu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_JW4NUGeG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YchwG2ID_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8dDTGfWE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1uzTX8Ee_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_OjEUUhBI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LZwcROyp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_Ovk4XTR3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Q0EK0Ei0_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_M95PKX6H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Xql09hiw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Kb8L22Za_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_QOam4WXU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dkQASNnV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GqzCIVxf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZdcjMvvc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_TU9fnil7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wRduhgCa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BagOA9xa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_P1E17mHV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8UE4pSH3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UpWfvdgJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sWX7LNl4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_QVL7rSND_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4KXXiHRV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_5ra9YbPc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_4LTBNCvJ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_Px1N2ud9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_MSZAreUi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WwWOrjUe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_BTVuIWs0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ccBGNSYX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_HAnjkGrC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qDfw3C5t_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2bHMM2gu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dSpMYeYk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_5cBJ4t5M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_vC8rnniw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_UFQr19ny_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_3oUch8Al_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_xt4LPfd9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Eu3bLyuN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_H8wjqMR2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_fCqT1K8S_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GHL9rfvP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Bglf3ydV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_MPby37Z0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_X7ncficS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hWSqYjJx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2BtQZQfm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ubdaqBv6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3nzRdeh3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Pan4SPfl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_0M8ZsPKl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DIFFx5Eb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_5sMpYNmV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_RnVGGm8m_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_cjhQ5Mkw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_yWBHAHNz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_FVKFFD6D_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_kQe9X6DR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5Sa0cuN2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rgQnwTAX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_t4rVQ8Gs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_SZEBuFMh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_pFxQuGg7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_d7QRjK9v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_oc4Wok1Z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KSLeZ21H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_0QxsEqA0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4z2ntFpa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_YN2tDKuk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GanpyRFD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Pnq8Sot7_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_LWIGsjS3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_WL7DyUm0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_K8hJT5R7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_opoknvYc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_fULtvESV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_5AMuUuoQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QKKfvUrP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_WYWMu679_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lGwTbdc7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EA6Hwn2j_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BGpIVGlG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ecnKwh7N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hmEmEeba_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_XgfxVQpB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_TPiSkgvz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ISl9PwSJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ZfvyIMgW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jBUDbrQS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TFFsEAWk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_kpuMNnIr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kRUBi1XL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_aArakkfr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_L57UnDAK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_nZAYo7pb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_iTQog7KE_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_SGV61dpE;
  SignalRPole sRPole_W3i6yULt;
  SignalRPole sRPole_HVtQKBgG;
  SignalRPole sRPole_IZ0U55zx;
  SignalDel1 sDel1_muBne6Eu;
  SignalTabwrite sTabwrite_rA5oFaRI;
  SignalTabwrite sTabwrite_AVsLwLdO;
  SignalTabwrite sTabwrite_mpsDhAtv;
  SignalRPole sRPole_HCeOCHeK;
  SignalRPole sRPole_QsK9DAVs;
  SignalRPole sRPole_IGZ5oC4v;
  ControlBinop cBinop_yWaklT4T;
  ControlRandom cRandom_SuomrmVr;
  ControlSlice cSlice_jorbmrrf;
  SignalVari sVari_a62orTAj;
  ControlVar cVar_a8xA8XOb;
  ControlBinop cBinop_xMr2DZrf;
  ControlBinop cBinop_pOdg35y1;
  SignalVarf sVarf_B28WTaWh;
  ControlBinop cBinop_wN2gzfdf;
  ControlBinop cBinop_vr6acgRQ;
  ControlBinop cBinop_Xl2T8bUt;
  SignalVarf sVarf_ile4bqFX;
  ControlVar cVar_uOYL5zo5;
  ControlBinop cBinop_Yi6NLAYc;
  ControlBinop cBinop_aA2ju1mj;
  SignalVarf sVarf_zzUc3rJU;
  ControlBinop cBinop_ROkzlUGp;
  ControlBinop cBinop_oqh0ExWh;
  ControlBinop cBinop_06YwPxOZ;
  SignalVarf sVarf_JyGAIWyL;
  ControlVar cVar_3Cky9xh8;
  ControlBinop cBinop_oF0gD4S8;
  ControlBinop cBinop_9Ds2hW8a;
  SignalVarf sVarf_bG4CSF4l;
  ControlBinop cBinop_uW6y21VK;
  ControlBinop cBinop_k4lJol4A;
  ControlBinop cBinop_q5y9Nqv5;
  SignalVarf sVarf_6SXzzG0k;
  ControlBinop cBinop_OFBsFTl0;
  ControlBinop cBinop_bMf3eqNy;
  SignalVarf sVarf_WMEodz6D;
  ControlVar cVar_lMln8v7c;
  ControlBinop cBinop_Td9jo79W;
  ControlBinop cBinop_4DIOBouu;
  ControlBinop cBinop_YchwG2ID;
  ControlBinop cBinop_8dDTGfWE;
  ControlBinop cBinop_1uzTX8Ee;
  ControlBinop cBinop_OjEUUhBI;
  ControlBinop cBinop_LZwcROyp;
  SignalVarf sVarf_6zg8Cd2I;
  HvTable hTable_Ovk4XTR3;
  ControlDelay cDelay_M95PKX6H;
  ControlVar cVar_Xql09hiw;
  ControlSlice cSlice_Kb8L22Za;
  ControlSlice cSlice_QOam4WXU;
  ControlBinop cBinop_dkQASNnV;
  ControlBinop cBinop_GqzCIVxf;
  ControlBinop cBinop_BagOA9xa;
  ControlBinop cBinop_P1E17mHV;
  ControlDelay cDelay_Px1N2ud9;
  ControlVar cVar_ccBGNSYX;
  ControlBinop cBinop_qDfw3C5t;
  ControlBinop cBinop_2bHMM2gu;
  ControlBinop cBinop_dSpMYeYk;
  HvTable hTable_vC8rnniw;
  ControlDelay cDelay_3oUch8Al;
  ControlVar cVar_xt4LPfd9;
  ControlSlice cSlice_Eu3bLyuN;
  ControlSlice cSlice_H8wjqMR2;
  ControlBinop cBinop_fCqT1K8S;
  ControlBinop cBinop_GHL9rfvP;
  ControlBinop cBinop_hWSqYjJx;
  ControlBinop cBinop_2BtQZQfm;
  HvTable hTable_5sMpYNmV;
  ControlDelay cDelay_cjhQ5Mkw;
  ControlVar cVar_yWBHAHNz;
  ControlSlice cSlice_FVKFFD6D;
  ControlSlice cSlice_kQe9X6DR;
  ControlBinop cBinop_5Sa0cuN2;
  ControlBinop cBinop_rgQnwTAX;
  ControlBinop cBinop_d7QRjK9v;
  ControlBinop cBinop_oc4Wok1Z;
  ControlBinop cBinop_LWIGsjS3;
  ControlRandom cRandom_K8hJT5R7;
  ControlSlice cSlice_opoknvYc;
  SignalVari sVari_KIys9Mzu;
  ControlVar cVar_5AMuUuoQ;
  ControlBinop cBinop_lGwTbdc7;
  ControlBinop cBinop_EA6Hwn2j;
  SignalVarf sVarf_hcxSySvJ;
  ControlBinop cBinop_ecnKwh7N;
  ControlBinop cBinop_hmEmEeba;
  ControlBinop cBinop_XgfxVQpB;
  SignalVarf sVarf_igfdKqu0;
  ControlVar cVar_TPiSkgvz;
  ControlBinop cBinop_jBUDbrQS;
  ControlBinop cBinop_TFFsEAWk;
  SignalVarf sVarf_yLh16ugo;
  ControlBinop cBinop_kRUBi1XL;
  ControlBinop cBinop_aArakkfr;
  ControlBinop cBinop_L57UnDAK;
  SignalVarf sVarf_O5QRGrVw;
};

#endif // _HEAVY_CONTEXT_SPARKS1_HPP_
