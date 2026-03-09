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

#ifndef _HEAVY_CONTEXT_000_EXPERIMENT_BROKEN_ENGINE_HPP_
#define _HEAVY_CONTEXT_000_EXPERIMENT_BROKEN_ENGINE_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlBinop.h"
#include "HvSignalRPole.h"
#include "HvControlCast.h"
#include "HvSignalBiquad.h"
#include "HvSignalPhasor.h"
#include "HvControlUnop.h"
#include "HvControlVar.h"
#include "HvControlSystem.h"
#include "HvMath.h"
#include "HvSignalVar.h"
#include "HvSignalDel1.h"
#include "HvControlSlice.h"
#include "HvControlRandom.h"

class Heavy_000_experiment_broken_engine : public HeavyContext {

 public:
  Heavy_000_experiment_broken_engine(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_000_experiment_broken_engine();

  const char *getName() override { return "000_experiment_broken_engine"; }
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
  static void cSwitchcase_v6XOwBbk_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_T3D9WP0T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_SPm4cHpd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_5nWZQcDN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_234COR5G_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_qM8qsvLa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_a7Pr3ynb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_nBaLG8DT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_RPCLfPWr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5FwpCmkn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bnjozLQI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_h5Keofm6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8ljSdYn1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iKHPnr5V_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UKMVkzDq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_h9VMBtjC_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_ly3Cleuz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_12yt8k65_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_YHzPfeyg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_ZWWPubRD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_90VZULAM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZeltXdYl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eO82OYwo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_K0xAkcsu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_bV4CI3E4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_61g9Ad0K_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_KUCbjdQq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2HZSzdqP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wZ5c7iFf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_d5MT1BRr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_zZd7UdyF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LMijW9t6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_V4YMauBh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9Xj146vh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_w1hE4Sf7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_naBk8SXt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_EPM0uxY1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ToZ0IIPU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_fZ7LknsL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GeeJoa8H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_oFVmAFTI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UFaUmt1Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DCoUvz6k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8oXV92kJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_3XUKeG8E_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_R7LwDtL7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6zKqgPit_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CVA13iVy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_3fEdOoEe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Nf6V4irR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2SMrRWpt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_QWM9Ayp0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ARY6I290_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mrDzd98p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_XnN2VOQj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0GhuiCaU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8fRnBt7u_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_cHSGcu8B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rHMariRo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EMtpmEzK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MG8hzyW0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ElS3KQXw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_fe1llnWZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_JmTYoMOq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_eTog3xFP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_yX2EssM4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_P1H8LnlX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8fAAbmIs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EEgG7SLT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DS95vVZ6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_cdV9ObqW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DaOAlcWb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_O0o2xfzT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bCkag7k9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_KWClFaAh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mtiJeyBK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_40VqsAEw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eavcgE79_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EjQnJU0l_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HnNq09mi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_NqcmPKzG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_N5P7faUc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eyRaYZUp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_vxtzZofc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TyZQbpZZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_EP6lfuvw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oCItwuPF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_phhDZezP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_gZsjGG8m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_1kMXPiX6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_H06Xrfrv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_3izcfcJE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qw9h4een_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MaRIBQ8D_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4HBvcxdR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FetmbTOA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WMw88fw7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Fm5reskv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_e9aAkm0b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9h53m92m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LrDndiKG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eYIQDaER_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GUm4OA1w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dXJYD3Rx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_fwnrITos_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_oRs7XSZz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7Dgel7c1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WgtTBnbs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UDpctZNa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_HnmukeFs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_5Jcr7Wau_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_8pT5ytYD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_SufMrpLx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BA9W1ivF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VaS8sdnf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1cyox1Ky_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nkw7U2KR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_tB1Zvlhz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LMhtwnhv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1x8ePwSC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_vgHoYbeF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iwJdxSN1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xr40uHgd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UrENTr3v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wKnPuBYh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6yYfGNtQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_btS6rfLV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_f8qf0c1B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_g79cFRpE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_M6nWCzzy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Mr6lSgLX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_0P9JvNoa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_9Eo3tcrg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_SFPCAMqc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_mJWHiWwD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_2eBLKzZC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_05wGDoPT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_71kFcMZJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_h2ejVXyR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CF62f9pZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sSAj6Rd4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6z3mC3hT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_B4XKyIoc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Mtqbd0hl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2ie8dJPw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ufO8v0uH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0QIuEYvV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_r71iJ36g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vj5qxOm9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qgXddseD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lw3OldBr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xCjfByKK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_t8wlALBp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FXLgxl96_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_CHmYbC2c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_odscMTkT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_bcIWuHyQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_KK7wIYVa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_qtx16Bse_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hpglZouU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_yfDiFV3m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BfMPV9ra_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_xz2Mi2j7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1wiTWhJA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SgPzOo02_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_L5A47ckl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_fSoX6myu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bMDK1Aee_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VJXJH7un_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8xtrfE5t_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IgmqTH7V_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_uOl04jYd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SDU9pRFq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WO9wq9ym_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_09ITJWZ5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_cB4fXX3s_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_NxvDLh8I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2ugXq8xf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_f4a3q2gU_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalBiquad_k sBiquad_k_vGu1wr0T;
  SignalPhasor sPhasor_GuywKxJc;
  SignalRPole sRPole_Q1B2gn8v;
  SignalDel1 sDel1_WCa5STtc;
  SignalRPole sRPole_An9BZzhy;
  SignalRPole sRPole_xZcoyoIn;
  SignalDel1 sDel1_mPTONbHq;
  SignalBiquad_k sBiquad_k_FxC68ObO;
  SignalBiquad_k sBiquad_k_AgTiC5Gv;
  SignalBiquad_k sBiquad_k_tzqzTTOk;
  SignalBiquad_k sBiquad_k_Cr3Mw7j0;
  SignalRPole sRPole_rFJviXIV;
  SignalDel1 sDel1_RqC7y7mx;
  ControlBinop cBinop_T3D9WP0T;
  ControlRandom cRandom_5nWZQcDN;
  ControlSlice cSlice_234COR5G;
  SignalVari sVari_O3Zehwxf;
  ControlVar cVar_a7Pr3ynb;
  ControlBinop cBinop_5FwpCmkn;
  ControlBinop cBinop_bnjozLQI;
  SignalVarf sVarf_zXyLoEmy;
  ControlBinop cBinop_8ljSdYn1;
  ControlBinop cBinop_iKHPnr5V;
  ControlBinop cBinop_UKMVkzDq;
  SignalVarf sVarf_cmtoTfAD;
  ControlBinop cBinop_ly3Cleuz;
  ControlRandom cRandom_YHzPfeyg;
  ControlSlice cSlice_ZWWPubRD;
  SignalVari sVari_wFAtrzqu;
  ControlBinop cBinop_ZeltXdYl;
  ControlBinop cBinop_eO82OYwo;
  SignalVarf sVarf_b6QrnJnd;
  ControlVar cVar_K0xAkcsu;
  ControlBinop cBinop_KUCbjdQq;
  ControlBinop cBinop_2HZSzdqP;
  ControlBinop cBinop_d5MT1BRr;
  ControlBinop cBinop_zZd7UdyF;
  ControlBinop cBinop_LMijW9t6;
  ControlBinop cBinop_V4YMauBh;
  ControlBinop cBinop_9Xj146vh;
  SignalVarf sVarf_FMZ2e5hY;
  ControlBinop cBinop_w1hE4Sf7;
  ControlBinop cBinop_naBk8SXt;
  SignalVarf sVarf_2BcUSbcd;
  ControlVar cVar_EPM0uxY1;
  ControlBinop cBinop_GeeJoa8H;
  ControlBinop cBinop_oFVmAFTI;
  ControlBinop cBinop_DCoUvz6k;
  ControlBinop cBinop_8oXV92kJ;
  ControlBinop cBinop_3XUKeG8E;
  ControlBinop cBinop_R7LwDtL7;
  ControlBinop cBinop_6zKqgPit;
  SignalVarf sVarf_ojPk0OLa;
  ControlBinop cBinop_CVA13iVy;
  ControlBinop cBinop_3fEdOoEe;
  SignalVarf sVarf_gqHo07xE;
  ControlVar cVar_Nf6V4irR;
  ControlBinop cBinop_ARY6I290;
  ControlBinop cBinop_mrDzd98p;
  ControlBinop cBinop_0GhuiCaU;
  ControlBinop cBinop_8fRnBt7u;
  ControlBinop cBinop_cHSGcu8B;
  ControlBinop cBinop_rHMariRo;
  ControlBinop cBinop_EMtpmEzK;
  SignalVarf sVarf_pPksuo0m;
  ControlVar cVar_fe1llnWZ;
  ControlVar cVar_JmTYoMOq;
  ControlBinop cBinop_yX2EssM4;
  ControlBinop cBinop_P1H8LnlX;
  ControlBinop cBinop_8fAAbmIs;
  ControlBinop cBinop_EEgG7SLT;
  ControlBinop cBinop_DS95vVZ6;
  ControlBinop cBinop_cdV9ObqW;
  ControlBinop cBinop_DaOAlcWb;
  ControlBinop cBinop_bCkag7k9;
  ControlBinop cBinop_KWClFaAh;
  ControlBinop cBinop_mtiJeyBK;
  ControlBinop cBinop_40VqsAEw;
  ControlBinop cBinop_eavcgE79;
  ControlBinop cBinop_EjQnJU0l;
  ControlBinop cBinop_HnNq09mi;
  ControlBinop cBinop_NqcmPKzG;
  ControlBinop cBinop_N5P7faUc;
  ControlBinop cBinop_eyRaYZUp;
  ControlVar cVar_vxtzZofc;
  ControlBinop cBinop_TyZQbpZZ;
  ControlVar cVar_phhDZezP;
  ControlVar cVar_gZsjGG8m;
  ControlBinop cBinop_H06Xrfrv;
  ControlBinop cBinop_3izcfcJE;
  ControlBinop cBinop_qw9h4een;
  ControlBinop cBinop_MaRIBQ8D;
  ControlBinop cBinop_4HBvcxdR;
  ControlBinop cBinop_FetmbTOA;
  ControlBinop cBinop_WMw88fw7;
  ControlBinop cBinop_e9aAkm0b;
  ControlBinop cBinop_9h53m92m;
  ControlBinop cBinop_LrDndiKG;
  ControlBinop cBinop_eYIQDaER;
  ControlBinop cBinop_GUm4OA1w;
  ControlBinop cBinop_dXJYD3Rx;
  ControlBinop cBinop_fwnrITos;
  ControlBinop cBinop_oRs7XSZz;
  ControlBinop cBinop_7Dgel7c1;
  ControlBinop cBinop_WgtTBnbs;
  ControlVar cVar_5Jcr7Wau;
  ControlVar cVar_8pT5ytYD;
  ControlBinop cBinop_BA9W1ivF;
  ControlBinop cBinop_VaS8sdnf;
  ControlBinop cBinop_1cyox1Ky;
  ControlBinop cBinop_nkw7U2KR;
  ControlBinop cBinop_tB1Zvlhz;
  ControlBinop cBinop_LMhtwnhv;
  ControlBinop cBinop_1x8ePwSC;
  ControlBinop cBinop_iwJdxSN1;
  ControlBinop cBinop_xr40uHgd;
  ControlBinop cBinop_UrENTr3v;
  ControlBinop cBinop_wKnPuBYh;
  ControlBinop cBinop_6yYfGNtQ;
  ControlBinop cBinop_btS6rfLV;
  ControlBinop cBinop_f8qf0c1B;
  ControlBinop cBinop_g79cFRpE;
  ControlBinop cBinop_M6nWCzzy;
  ControlBinop cBinop_Mr6lSgLX;
  ControlVar cVar_SFPCAMqc;
  ControlVar cVar_mJWHiWwD;
  ControlBinop cBinop_05wGDoPT;
  ControlBinop cBinop_71kFcMZJ;
  ControlBinop cBinop_h2ejVXyR;
  ControlBinop cBinop_CF62f9pZ;
  ControlBinop cBinop_sSAj6Rd4;
  ControlBinop cBinop_6z3mC3hT;
  ControlBinop cBinop_B4XKyIoc;
  ControlBinop cBinop_2ie8dJPw;
  ControlBinop cBinop_ufO8v0uH;
  ControlBinop cBinop_0QIuEYvV;
  ControlBinop cBinop_r71iJ36g;
  ControlBinop cBinop_vj5qxOm9;
  ControlBinop cBinop_qgXddseD;
  ControlBinop cBinop_lw3OldBr;
  ControlBinop cBinop_xCjfByKK;
  ControlBinop cBinop_t8wlALBp;
  ControlBinop cBinop_FXLgxl96;
  ControlVar cVar_bcIWuHyQ;
  ControlVar cVar_KK7wIYVa;
  ControlBinop cBinop_hpglZouU;
  ControlBinop cBinop_yfDiFV3m;
  ControlBinop cBinop_BfMPV9ra;
  ControlBinop cBinop_xz2Mi2j7;
  ControlBinop cBinop_1wiTWhJA;
  ControlBinop cBinop_SgPzOo02;
  ControlBinop cBinop_L5A47ckl;
  ControlBinop cBinop_bMDK1Aee;
  ControlBinop cBinop_VJXJH7un;
  ControlBinop cBinop_8xtrfE5t;
  ControlBinop cBinop_IgmqTH7V;
  ControlBinop cBinop_uOl04jYd;
  ControlBinop cBinop_SDU9pRFq;
  ControlBinop cBinop_WO9wq9ym;
  ControlBinop cBinop_09ITJWZ5;
  ControlBinop cBinop_cB4fXX3s;
  ControlBinop cBinop_NxvDLh8I;
  ControlBinop cBinop_2ugXq8xf;
  SignalVarf sVarf_49zLxcfh;
  SignalVarf sVarf_ySe8QKAd;
};

#endif // _HEAVY_CONTEXT_000_EXPERIMENT_BROKEN_ENGINE_HPP_
