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

#ifndef _HEAVY_CONTEXT_FAN5_HPP_
#define _HEAVY_CONTEXT_FAN5_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvMath.h"
#include "HvTable.h"
#include "HvControlUnop.h"
#include "HvSignalRPole.h"
#include "HvControlDelay.h"
#include "HvControlTabhead.h"
#include "HvControlSystem.h"
#include "HvSignalPhasor.h"
#include "HvSignalTabwrite.h"
#include "HvControlSlice.h"
#include "HvControlBinop.h"
#include "HvSignalBiquad.h"
#include "HvSignalTabread.h"
#include "HvSignalDel1.h"
#include "HvControlCast.h"
#include "HvControlRandom.h"
#include "HvControlVar.h"
#include "HvSignalVar.h"

class Heavy_fan5 : public HeavyContext {

 public:
  Heavy_fan5(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_fan5();

  const char *getName() override { return "fan5"; }
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
  static void cSwitchcase_14puOi6D_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_AsqxdsEQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_0xCpQDWA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_x9X5khnD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_HTnt8L9i_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_o6QuYzO5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_uCWHRy1Y_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_vsrSRFIv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_6vXtjVAS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_QjWkAbu5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_lNppuZKb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_3tU0MzFm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TtadUZVu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kEM5Stdi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Tji6jSdj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PeI6wtnx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EfgKzjjt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dcwJfTnf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_vGiZaC6q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wqq5GpAH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JYPHPFKL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QMaDJQb0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WvachQzr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_apQUdgNE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gGo7I3ze_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lA2eClXw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_tJePAhUC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Keo0LtRs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ey95eUqD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_p4I42NaM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Eo9Nu4LB_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_ahsXfXjs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_BdtZ5ui2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_TXF6eu0E_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_TO23cAXF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LVtckAVd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_99P2SU3T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_18qS0dvq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_836dOjfS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VtwlACzi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JQcgdGKO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hxM6JgOK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KfJ7hliM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_tZ3FtU1J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_dtNTwlQR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_T9Pt7BjR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GjH79a8o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Cq7gacxD_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_pIhRgbyL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_d1jIkVFp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_d7whLdaT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_193VLGXc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_0L2WoE4W_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_0IFYE7QV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_aBt1wuRa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_AsZP6Jq0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8I4lCzhb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_tevNQiUa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7t8lEzn0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_hSFkF9EM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_dOQmVsEl_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_GygHAOF7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_ebkGscwg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_EfUaOpOz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_xT7Alqbi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Gw6cng97_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_b3R9fHt1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_HRl6DIil_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_rkCkqlnf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_rUDxfvhO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_qKOiARcS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_a2yxDYkk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mva9y7kM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_phcxbz80_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xlzqAk1P_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BgrkAUUG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_cjgQLieB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HTazhCcs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_LEqS40yW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_C8cKombn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VFa1fYYp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ibx0kLxl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Hgx1wZbC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_n0YU7EJp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CKn5psfC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_KUOh206v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_aNEdcUx3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Lvtc9vou_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hf8QQWTD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_qX8CbISf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_0QNuDMbG_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_mRcBzT6L_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_EiaycPXl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Svb34gWM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_4NWAf18y_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_c5prK4kl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_giNuAwkF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ChnvYq0s_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_aT5MmDY3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_i3bDGP5p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hUbH6J0h_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IZVCE1u8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_dlccti6N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_yn0LtXv1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_864sEK0m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_XqOmfTkF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_cwe7DdDS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_S1Yo1Ism_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_dFISdY8s_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_3WE0LFgw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_4QTxSalu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_PYJYliG6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_e4DN5W2C_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MPefJjxo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_r7oEZDdv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_fz4MsRXm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_RIL8vVMV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_uqpIHkfJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UZk1pxZJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_NNP48sub_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_slArbZbC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_aMtxITIt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_d34Bo8tz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Lz4XJ86e_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wWymkIaa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabhead_KA4ReXLP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MwyaLCiN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_kR75ssGV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Bt6ZXVH1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_CabsyshW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_wrpYU0pn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void sTabread_xO4pdvLF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UR7bOPUs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qYadZgWc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Irt3ug2E_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_fr4FDjke_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ObEGHBci_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jxhyekJF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KM3bPnwS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_z4Lxgga2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_7UdUiGNS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LSKFu6gS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2q0K6HEn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_6kwPeeib_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_qgYRmlVZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_FqiGH3TU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_QqfRh0nR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_PZSVi8YR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_O9IWSrYQ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_yUh77zFW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_sl8X6nxd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QBsmNU31_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_RybWbieL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GexnjT3Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_pOFrja9I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_kmCl6KzI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_dNap4IFv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_D2nV0uLT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_B00rsnLx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_s1gmYAv7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_AA16GBek_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_cu6P8gsQ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_wPxs2UTl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_LXuTqM7q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gVrbkFcG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xKXCU0YI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_m8xY29Cx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_0lo4ecSr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BTrtl8wc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_lGt5osVl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabhead_9tIVRY0Z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_qPHayVsy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_hmV1XsOA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_tabHvzGG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_nthuiEXL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_Ony0ykKn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void sTabread_wck5v1Vg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jf051dJF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_opHiYehL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YufXSgr3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_xfkO4j3x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_A89lfZIw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jktS3jRA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_x0OunjmE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_uJtVIwrx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_BAdRq8Mw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_joNbTYnt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iu2hDlXC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_3hPT7wSN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_t7Fs3oHP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Bh60oeQ8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_tdX3oFZP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bKdWNsFq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xDlhtGVQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_r0NuWM8O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hiB7z0v8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_somMHHpX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wfv7MMoO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_CK2e9VG5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_k8fFeCh0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_J6CCFvyj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_7TWrE3yc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QW41zO75_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_hgl34Owo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_EIRdPPlY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_0QvtJiQw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_OQvGabr5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_sCvoJHfb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QHaGG32w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_rZcFQyg6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_R9WDYAkT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_v2Xqvvw6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_78pDshN1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_pcZQVIb9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_kW0CMjy6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_15nsigot_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_zavxO3qA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_FXzGi5BY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_h4RF5kY6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_NB9m4dA0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_HMCBP9RY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_gBVAONbf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Q3Qe88ha_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_OKKFKdqO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GVjr6djF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_pQKnXogO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Kg0G44If_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_LiMPtsNx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_m5x9yO8f_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_y5bT28BD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_R5Nr0JsZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_itXpYaX5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_GbHYyzUQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_9EZlkex4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_lXLrfsgd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_Iw7k4Je5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_KThKoCZd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_PV4bzj8A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_9zwj0MKN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_wpKlYFLL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_bX3xsffC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_K8vgUG5Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_yuSmtrGr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_TFDYJPsV_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalRPole sRPole_DXCRdDUm;
  SignalPhasor sPhasor_bAUgZhoj;
  SignalBiquad_k sBiquad_k_odBNp9ay;
  SignalTabwrite sTabwrite_zXqGyPkz;
  SignalTabwrite sTabwrite_Vo79vvID;
  SignalTabwrite sTabwrite_IJtdaUda;
  SignalBiquad_k sBiquad_k_Fy314rNR;
  SignalTabwrite sTabwrite_yGPAHk6D;
  SignalTabwrite sTabwrite_VaKhSsAL;
  SignalTabread sTabread_xO4pdvLF;
  SignalTabread sTabread_wck5v1Vg;
  ControlBinop cBinop_AsqxdsEQ;
  ControlRandom cRandom_x9X5khnD;
  ControlSlice cSlice_HTnt8L9i;
  SignalVari sVari_jmppcbIl;
  ControlVar cVar_6vXtjVAS;
  ControlVar cVar_QjWkAbu5;
  ControlBinop cBinop_3tU0MzFm;
  ControlBinop cBinop_TtadUZVu;
  ControlBinop cBinop_kEM5Stdi;
  ControlBinop cBinop_Tji6jSdj;
  ControlBinop cBinop_PeI6wtnx;
  ControlBinop cBinop_EfgKzjjt;
  ControlBinop cBinop_dcwJfTnf;
  ControlBinop cBinop_wqq5GpAH;
  ControlBinop cBinop_JYPHPFKL;
  ControlBinop cBinop_QMaDJQb0;
  ControlBinop cBinop_WvachQzr;
  ControlBinop cBinop_apQUdgNE;
  ControlBinop cBinop_gGo7I3ze;
  ControlBinop cBinop_lA2eClXw;
  ControlBinop cBinop_tJePAhUC;
  ControlBinop cBinop_Keo0LtRs;
  ControlBinop cBinop_ey95eUqD;
  HvTable hTable_p4I42NaM;
  ControlDelay cDelay_ahsXfXjs;
  ControlVar cVar_BdtZ5ui2;
  ControlSlice cSlice_TXF6eu0E;
  ControlSlice cSlice_TO23cAXF;
  ControlBinop cBinop_LVtckAVd;
  ControlBinop cBinop_99P2SU3T;
  ControlBinop cBinop_JQcgdGKO;
  ControlBinop cBinop_hxM6JgOK;
  ControlDelay cDelay_pIhRgbyL;
  ControlVar cVar_0L2WoE4W;
  ControlBinop cBinop_aBt1wuRa;
  ControlBinop cBinop_AsZP6Jq0;
  ControlBinop cBinop_8I4lCzhb;
  ControlVar cVar_tevNQiUa;
  ControlBinop cBinop_7t8lEzn0;
  SignalVarf sVarf_NYvmHLRP;
  ControlBinop cBinop_GygHAOF7;
  ControlRandom cRandom_EfUaOpOz;
  ControlSlice cSlice_xT7Alqbi;
  SignalVari sVari_rwKe0k3n;
  ControlVar cVar_rkCkqlnf;
  ControlVar cVar_rUDxfvhO;
  ControlBinop cBinop_a2yxDYkk;
  ControlBinop cBinop_mva9y7kM;
  ControlBinop cBinop_phcxbz80;
  ControlBinop cBinop_xlzqAk1P;
  ControlBinop cBinop_BgrkAUUG;
  ControlBinop cBinop_cjgQLieB;
  ControlBinop cBinop_HTazhCcs;
  ControlBinop cBinop_C8cKombn;
  ControlBinop cBinop_VFa1fYYp;
  ControlBinop cBinop_Ibx0kLxl;
  ControlBinop cBinop_Hgx1wZbC;
  ControlBinop cBinop_n0YU7EJp;
  ControlBinop cBinop_CKn5psfC;
  ControlBinop cBinop_KUOh206v;
  ControlBinop cBinop_aNEdcUx3;
  ControlBinop cBinop_Lvtc9vou;
  ControlBinop cBinop_hf8QQWTD;
  HvTable hTable_qX8CbISf;
  ControlDelay cDelay_mRcBzT6L;
  ControlVar cVar_EiaycPXl;
  ControlSlice cSlice_Svb34gWM;
  ControlSlice cSlice_4NWAf18y;
  ControlBinop cBinop_c5prK4kl;
  ControlBinop cBinop_giNuAwkF;
  ControlBinop cBinop_hUbH6J0h;
  ControlBinop cBinop_IZVCE1u8;
  SignalVarf sVarf_jZVxDLLO;
  HvTable hTable_S1Yo1Ism;
  ControlDelay cDelay_3WE0LFgw;
  ControlVar cVar_4QTxSalu;
  ControlSlice cSlice_PYJYliG6;
  ControlSlice cSlice_e4DN5W2C;
  ControlBinop cBinop_MPefJjxo;
  ControlBinop cBinop_r7oEZDdv;
  ControlBinop cBinop_UZk1pxZJ;
  ControlBinop cBinop_NNP48sub;
  SignalVarf sVarf_UTsplJWF;
  SignalVarf sVarf_VpHfd1O2;
  ControlTabhead cTabhead_KA4ReXLP;
  ControlVar cVar_Bt6ZXVH1;
  ControlDelay cDelay_CabsyshW;
  ControlDelay cDelay_wrpYU0pn;
  ControlBinop cBinop_UR7bOPUs;
  ControlBinop cBinop_qYadZgWc;
  ControlBinop cBinop_Irt3ug2E;
  ControlBinop cBinop_z4Lxgga2;
  ControlBinop cBinop_LSKFu6gS;
  ControlBinop cBinop_2q0K6HEn;
  ControlDelay cDelay_QqfRh0nR;
  ControlDelay cDelay_PZSVi8YR;
  ControlBinop cBinop_yUh77zFW;
  HvTable hTable_sl8X6nxd;
  ControlBinop cBinop_RybWbieL;
  ControlDelay cDelay_s1gmYAv7;
  ControlDelay cDelay_AA16GBek;
  ControlBinop cBinop_wPxs2UTl;
  HvTable hTable_LXuTqM7q;
  ControlBinop cBinop_xKXCU0YI;
  ControlTabhead cTabhead_9tIVRY0Z;
  ControlVar cVar_tabHvzGG;
  ControlDelay cDelay_nthuiEXL;
  ControlDelay cDelay_Ony0ykKn;
  ControlBinop cBinop_jf051dJF;
  ControlBinop cBinop_opHiYehL;
  ControlBinop cBinop_YufXSgr3;
  ControlBinop cBinop_uJtVIwrx;
  ControlBinop cBinop_joNbTYnt;
  ControlBinop cBinop_iu2hDlXC;
  ControlVar cVar_t7Fs3oHP;
  ControlBinop cBinop_bKdWNsFq;
  ControlBinop cBinop_xDlhtGVQ;
  SignalVarf sVarf_I2erwRBn;
  ControlBinop cBinop_hiB7z0v8;
  ControlBinop cBinop_somMHHpX;
  ControlBinop cBinop_wfv7MMoO;
  SignalVarf sVarf_d3me7osH;
  SignalVarf sVarf_trz2L29X;
  SignalVarf sVarf_yhDp3E8n;
  SignalVarf sVarf_7nRpGgjH;
  SignalVarf sVarf_tZpUyHg9;
  SignalVarf sVarf_6hkgItsS;
  SignalVarf sVarf_i25aRqqe;
  SignalVarf sVarf_VPHZMRCn;
};

#endif // _HEAVY_CONTEXT_FAN5_HPP_
