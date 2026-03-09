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

#ifndef _HEAVY_CONTEXT_FLY1_HPP_
#define _HEAVY_CONTEXT_FLY1_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalRPole.h"
#include "HvControlVar.h"
#include "HvControlSlice.h"
#include "HvControlBinop.h"
#include "HvSignalPhasor.h"
#include "HvTable.h"
#include "HvControlDelay.h"
#include "HvControlCast.h"
#include "HvMath.h"
#include "HvSignalTabwrite.h"
#include "HvControlSystem.h"
#include "HvSignalDel1.h"
#include "HvSignalVar.h"

class Heavy_fly1 : public HeavyContext {

 public:
  Heavy_fly1(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_fly1();

  const char *getName() override { return "fly1"; }
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
  static void cVar_FscvEiDf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PSPnePpx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sFJOLY8W_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_lq3VDEzs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DI97FRsV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_BBGfvBm8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5ZCBEGGs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_yA5ZvjJh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MziFSBzj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_o8njDEnK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WH1mmw3U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZCqfWhNt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FNMzbwAN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DL35KU6o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_zRtCE5R4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_Pvro5czw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_2mCltRkf_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_LBCg28hU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_vhzazwWF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_g2MJJ4mM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_vtaRrDMe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_l0aGGGJg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_37OH0qLQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_M7ox2dKd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_XUUgCycg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xDZLpIJQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_k3HmGgEK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FV3hd8Gq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_XfHID6KD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3rb1W2yD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_LHhFdRuW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_4S3eQ4HQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_eei5R8H4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_DLpTh3l3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_HdrVv0cn_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_LhVF2i9n_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_kfAcB895_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_XwUlFWbn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_yiTUmE29_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_7X9OtB0Y_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_hODYm5xm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_a62DpukI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6cjiJyIR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sYczhr8e_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_xKJ38eOW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_Cf6ptvy3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_11snfWnE_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_jEt9h5FX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_MjUKg1lG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_5UxknBrR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_O7YVyjS6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_cUxe6INp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QrVLahKJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4uytPlY9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_zf7UqAi9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FqKuiuxQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_W0EHI4EL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6YlNJl1S_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_qqUS7SoP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1xT99EpG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_LLpiTgWZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_QPVbfsTG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_PZqkHeC8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_bPdQxkoi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_05bjHDSD_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_fE0xv6iW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_z5l7Sxv0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_pgM10CMO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_icrr9XOK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MwRm49Ri_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bb5kKs3B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_YPQjRMQp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_l14ihcIO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GYcVOske_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lSEDa4wg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bpboy8Pj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_setbk8th_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_6i7Cbaje_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_F0y4NQmX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_qQSUGCZJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_pq4B9lsq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_aiBzM6bW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_EpSYHmaB_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_kmhLKMoY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_dRDN6XBE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9pvMWQqM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_SZIFtoGl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PX5iHND2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8iz8fBZv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Cdxs5ODg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_OFSKp5eL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_b4dbRCV5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_g8wJ8QxE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SrhFFFDe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xHW2QAPy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_CykuCGdT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_tlmFnjB2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_RLZeVpj2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vuUreMyj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_EnHQk7d0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_9GJLnqGH_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_A9FwP2lj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_be6rmBRc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_72ci4kZk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_KJLJ8ieD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TIN53ZXr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ePLOraPT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FkALE6TU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_plteolKF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_y0FJJRub_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lxUuBviD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Fll9vTJ4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DrljkDI5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ilm2GS3t_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_nRCZfrmq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Oh4GRRPp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_d8eEp8US_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TmeE09Fq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_8SmdVsCr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_iTNkiuhZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_tz4Plguy;
  SignalTabwrite sTabwrite_GwhtcM2T;
  SignalTabwrite sTabwrite_oohy4Zsc;
  SignalTabwrite sTabwrite_NGZXgHpn;
  SignalTabwrite sTabwrite_wbN09ZOy;
  SignalRPole sRPole_qST1ApRr;
  SignalDel1 sDel1_V6sRg3jX;
  SignalTabwrite sTabwrite_9SJaraAz;
  ControlVar cVar_FscvEiDf;
  ControlBinop cBinop_PSPnePpx;
  ControlBinop cBinop_sFJOLY8W;
  SignalVarf sVarf_8tpg2s8p;
  ControlVar cVar_lq3VDEzs;
  ControlBinop cBinop_5ZCBEGGs;
  ControlBinop cBinop_yA5ZvjJh;
  ControlBinop cBinop_o8njDEnK;
  ControlBinop cBinop_WH1mmw3U;
  ControlBinop cBinop_ZCqfWhNt;
  ControlBinop cBinop_FNMzbwAN;
  ControlBinop cBinop_DL35KU6o;
  SignalVarf sVarf_EYY0DrXZ;
  ControlVar cVar_zRtCE5R4;
  HvTable hTable_Pvro5czw;
  ControlDelay cDelay_LBCg28hU;
  ControlVar cVar_vhzazwWF;
  ControlSlice cSlice_g2MJJ4mM;
  ControlSlice cSlice_vtaRrDMe;
  ControlBinop cBinop_l0aGGGJg;
  ControlBinop cBinop_37OH0qLQ;
  ControlBinop cBinop_k3HmGgEK;
  ControlBinop cBinop_FV3hd8Gq;
  ControlDelay cDelay_LhVF2i9n;
  ControlVar cVar_7X9OtB0Y;
  ControlBinop cBinop_a62DpukI;
  ControlBinop cBinop_6cjiJyIR;
  ControlBinop cBinop_sYczhr8e;
  HvTable hTable_Cf6ptvy3;
  ControlDelay cDelay_jEt9h5FX;
  ControlVar cVar_MjUKg1lG;
  ControlSlice cSlice_5UxknBrR;
  ControlSlice cSlice_O7YVyjS6;
  ControlBinop cBinop_cUxe6INp;
  ControlBinop cBinop_QrVLahKJ;
  ControlBinop cBinop_W0EHI4EL;
  ControlBinop cBinop_6YlNJl1S;
  HvTable hTable_bPdQxkoi;
  ControlDelay cDelay_fE0xv6iW;
  ControlVar cVar_z5l7Sxv0;
  ControlSlice cSlice_pgM10CMO;
  ControlSlice cSlice_icrr9XOK;
  ControlBinop cBinop_MwRm49Ri;
  ControlBinop cBinop_bb5kKs3B;
  ControlBinop cBinop_lSEDa4wg;
  ControlBinop cBinop_bpboy8Pj;
  HvTable hTable_aiBzM6bW;
  ControlDelay cDelay_kmhLKMoY;
  ControlVar cVar_dRDN6XBE;
  ControlSlice cSlice_9pvMWQqM;
  ControlSlice cSlice_SZIFtoGl;
  ControlBinop cBinop_PX5iHND2;
  ControlBinop cBinop_8iz8fBZv;
  ControlBinop cBinop_g8wJ8QxE;
  ControlBinop cBinop_SrhFFFDe;
  HvTable hTable_EnHQk7d0;
  ControlDelay cDelay_A9FwP2lj;
  ControlVar cVar_be6rmBRc;
  ControlSlice cSlice_72ci4kZk;
  ControlSlice cSlice_KJLJ8ieD;
  ControlBinop cBinop_TIN53ZXr;
  ControlBinop cBinop_ePLOraPT;
  ControlBinop cBinop_lxUuBviD;
  ControlBinop cBinop_Fll9vTJ4;
  ControlBinop cBinop_TmeE09Fq;
  SignalVarf sVarf_IpE1q8uJ;
};

#endif // _HEAVY_CONTEXT_FLY1_HPP_
