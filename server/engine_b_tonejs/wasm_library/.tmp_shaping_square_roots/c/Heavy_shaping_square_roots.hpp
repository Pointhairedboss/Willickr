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

#ifndef _HEAVY_CONTEXT_SHAPING_SQUARE_ROOTS_HPP_
#define _HEAVY_CONTEXT_SHAPING_SQUARE_ROOTS_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalTabwrite.h"
#include "HvControlSystem.h"
#include "HvMath.h"
#include "HvControlSlice.h"
#include "HvControlDelay.h"
#include "HvTable.h"
#include "HvControlVar.h"
#include "HvControlCast.h"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlBinop.h"

class Heavy_shaping_square_roots : public HeavyContext {

 public:
  Heavy_shaping_square_roots(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_square_roots();

  const char *getName() override { return "shaping_square_roots"; }
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
  static void hTable_Yk5esszA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_hC1ZGqiF_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_rCuO9v1X_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_djGONbj3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9AKLYiNH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_VME0szSg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Jxuif0TR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_y63msKHy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FspRSFbG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_14cTCHH5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iRQB4aJO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PjDoXyXq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hq90dFbh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sYPTvT6M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_OJZSOYHp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MfuzunyN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_yLJUbnf4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_feaRnQX2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_On1CVeIN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_MeBuoEWi_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_TmPoe2R3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ldKBdBre_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_fX8ha2Fk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oYwE9vtl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_tY3075mA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9zv5Ko8q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_i3a2SsTL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ApKmEu6g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_M1xIf5mb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_KZsf51xy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_7M1aar09_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_ul7PgafA_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_wsNPgh9T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_1HSABbC9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9CTD9AfA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Sz23q5ya_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GTKmohjr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mUxzM022_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BdMwO2TI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_zrGyskNr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_r1HzEmut_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hYlFx4XD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6xziqyV6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2rYEGXzc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_uAp5ZYNa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_eDSUGzxQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_WXlb5psE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sQwl8xln_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_8A2KuNxD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_eflaUw9P_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_CX8AlrEf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_JeMdcMfa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_osj53OfY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_yCVvdqq3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_auPKZl26_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QXeltenH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_5MSfYfjo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_KVVjFmVG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_bZGoVZb3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZzNlbM8K_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wyUfU1of_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_JDrc9guQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QL6LoDvt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_dobMnlIW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_5NbRWR8c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZzlsAC3d_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_IoeVuP0N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_rV86FGJH_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_aMVmt5uW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_PjJLbrkB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_egv7sjma_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_XnSKaKKc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_T8JDOruv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mingTh0k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_L4vjgqLI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_b6E5y8VK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_hjLFrBu2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iYZrgQjP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dorCxAQx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZfwpkF1s_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_yrJxUFsP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_baqLJWth_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_m6sWmPzZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_TcUBsjvp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_DvOmgbp8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_uBkGU3KY_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_AWnQylR7;
  SignalTabwrite sTabwrite_3A4K4qZj;
  SignalTabwrite sTabwrite_bNNgy9B2;
  SignalTabwrite sTabwrite_J05Gl847;
  SignalPhasor sPhasor_9yfgymGv;
  SignalPhasor sPhasor_FukGnbHC;
  SignalPhasor sPhasor_7pUTUikC;
  SignalPhasor sPhasor_iKiZy6h3;
  HvTable hTable_Yk5esszA;
  ControlDelay cDelay_rCuO9v1X;
  ControlVar cVar_djGONbj3;
  ControlSlice cSlice_9AKLYiNH;
  ControlSlice cSlice_VME0szSg;
  ControlBinop cBinop_Jxuif0TR;
  ControlBinop cBinop_y63msKHy;
  ControlBinop cBinop_PjDoXyXq;
  ControlBinop cBinop_hq90dFbh;
  ControlDelay cDelay_TmPoe2R3;
  ControlVar cVar_tY3075mA;
  ControlBinop cBinop_i3a2SsTL;
  ControlBinop cBinop_ApKmEu6g;
  ControlBinop cBinop_M1xIf5mb;
  HvTable hTable_7M1aar09;
  ControlDelay cDelay_wsNPgh9T;
  ControlVar cVar_1HSABbC9;
  ControlSlice cSlice_9CTD9AfA;
  ControlSlice cSlice_Sz23q5ya;
  ControlBinop cBinop_GTKmohjr;
  ControlBinop cBinop_mUxzM022;
  ControlBinop cBinop_hYlFx4XD;
  ControlBinop cBinop_6xziqyV6;
  HvTable hTable_8A2KuNxD;
  ControlDelay cDelay_CX8AlrEf;
  ControlVar cVar_JeMdcMfa;
  ControlSlice cSlice_osj53OfY;
  ControlSlice cSlice_yCVvdqq3;
  ControlBinop cBinop_auPKZl26;
  ControlBinop cBinop_QXeltenH;
  ControlBinop cBinop_ZzNlbM8K;
  ControlBinop cBinop_wyUfU1of;
  HvTable hTable_IoeVuP0N;
  ControlDelay cDelay_aMVmt5uW;
  ControlVar cVar_PjJLbrkB;
  ControlSlice cSlice_egv7sjma;
  ControlSlice cSlice_XnSKaKKc;
  ControlBinop cBinop_T8JDOruv;
  ControlBinop cBinop_mingTh0k;
  ControlBinop cBinop_iYZrgQjP;
  ControlBinop cBinop_dorCxAQx;
  SignalVarf sVarf_KGXTa0zK;
  SignalVarf sVarf_TYXPNpwh;
  SignalVarf sVarf_9YBlBTWL;
  SignalVarf sVarf_PuyWc4GD;
};

#endif // _HEAVY_CONTEXT_SHAPING_SQUARE_ROOTS_HPP_
