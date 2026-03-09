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

#ifndef _HEAVY_CONTEXT_SHAPING_ANTIPHASE_HPP_
#define _HEAVY_CONTEXT_SHAPING_ANTIPHASE_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlSystem.h"
#include "HvSignalTabread.h"
#include "HvControlVar.h"
#include "HvSignalTabwrite.h"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlSlice.h"
#include "HvControlBinop.h"
#include "HvTable.h"
#include "HvControlDelay.h"
#include "HvControlCast.h"
#include "HvMath.h"

class Heavy_shaping_antiphase : public HeavyContext {

 public:
  Heavy_shaping_antiphase(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_antiphase();

  const char *getName() override { return "shaping_antiphase"; }
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
  static void hTable_OnSSKNGe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_cDec39zX_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_EpvZt1cv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_6RzMDb9w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_elSgZlJW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_j6tapito_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gkZmtWCy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_a3T8uVE6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_EDYkSJSw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_aLCRWAwh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_s4qc71wm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_RSCXg6Zp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lo4EdVoV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_mtiuWA1d_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_lerw2eug_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_5TdifJNd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_1xGyOxlq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZgglqEel_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_UUR22lls_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_m8j8usye_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_1mLa5FjA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_6KaKn1mm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_LkkFB7F8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Ml5vq1Ws_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ingYMZKt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4tj1xLZG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sQ3Os5hr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_pfjSM6d8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LCsUyGxK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_qRDGmQs3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_QR2FbsGH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_z2cI05cG_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_qyEA7ORp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_iqjn2LzZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_JLAPK8FA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_FIeviGzh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iQCtZBhy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BrhoeTgg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_rXnOJeC5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_qmsI0AWb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_o2iJvKrP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lb7niaB7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_KyB2waXZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WR3SAEUz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_SuE9lMe7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_pXkHJKUZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Up4c6SPQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_dAfvO4L0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_zBXIaPW2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_qxBVyhfu_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_CouNlwYn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_L126blV9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_YMFoalMF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_rbJvrcb4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZZ6HFV4g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_zRSMWQ6k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZosCtV8N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_c23vatsB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ASmMQaQ8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DLgA10kt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YZx6sEIU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_RY1JNCk9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZDLokTkM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Jm45uCNf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_gqUOi8Mz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_LUzZnzD9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_y1QMXfpz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ZqVVsL9O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_X5nuE080_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_XnxO7mTU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wpTC7L04_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_mKi1V1dV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_n1AVCy5L_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FWf20nxx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_VZ5Epm5o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_AyxpUdTu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_utRgvsYX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_EAFI3ABL_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_nFpq1YcW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_Letgajgb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jhm71FHe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_47FEbxRW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Cj6VzcvR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_JQAkCeSj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2eyarZPi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_du3lz2fS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Fn7Xg5TT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_wLqBFMbr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_m2nqZwfk_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_tw5En2RY;
  SignalTabwrite sTabwrite_DWBkCHEL;
  SignalTabhead sTabhead_IHira7ZX;
  SignalTabread sTabread_hIkXsKXc;
  SignalTabread sTabread_rmdJflzp;
  SignalTabwrite sTabwrite_nK03YFPf;
  SignalTabwrite sTabwrite_SHSkGHvV;
  SignalTabwrite sTabwrite_Uyn3e8MU;
  HvTable hTable_OnSSKNGe;
  ControlDelay cDelay_EpvZt1cv;
  ControlVar cVar_6RzMDb9w;
  ControlSlice cSlice_elSgZlJW;
  ControlSlice cSlice_j6tapito;
  ControlBinop cBinop_gkZmtWCy;
  ControlBinop cBinop_a3T8uVE6;
  ControlBinop cBinop_RSCXg6Zp;
  ControlBinop cBinop_lo4EdVoV;
  ControlDelay cDelay_1mLa5FjA;
  ControlVar cVar_ingYMZKt;
  ControlBinop cBinop_sQ3Os5hr;
  ControlBinop cBinop_pfjSM6d8;
  ControlBinop cBinop_LCsUyGxK;
  HvTable hTable_QR2FbsGH;
  ControlDelay cDelay_qyEA7ORp;
  ControlVar cVar_iqjn2LzZ;
  ControlSlice cSlice_JLAPK8FA;
  ControlSlice cSlice_FIeviGzh;
  ControlBinop cBinop_iQCtZBhy;
  ControlBinop cBinop_BrhoeTgg;
  ControlBinop cBinop_lb7niaB7;
  ControlBinop cBinop_KyB2waXZ;
  HvTable hTable_zBXIaPW2;
  ControlDelay cDelay_CouNlwYn;
  ControlVar cVar_L126blV9;
  ControlSlice cSlice_YMFoalMF;
  ControlSlice cSlice_rbJvrcb4;
  ControlBinop cBinop_ZZ6HFV4g;
  ControlBinop cBinop_zRSMWQ6k;
  ControlBinop cBinop_DLgA10kt;
  ControlBinop cBinop_YZx6sEIU;
  ControlVar cVar_X5nuE080;
  ControlBinop cBinop_wpTC7L04;
  ControlBinop cBinop_n1AVCy5L;
  SignalVarf sVarf_N09yXvo7;
  SignalVarf sVarf_uQMCIw2K;
  SignalVarf sVarf_ZyLx5Kcr;
  ControlDelay cDelay_AyxpUdTu;
  ControlDelay cDelay_utRgvsYX;
  ControlBinop cBinop_nFpq1YcW;
  HvTable hTable_Letgajgb;
  ControlBinop cBinop_47FEbxRW;
};

#endif // _HEAVY_CONTEXT_SHAPING_ANTIPHASE_HPP_
