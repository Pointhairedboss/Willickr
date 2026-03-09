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

#ifndef _HEAVY_CONTEXT_2TONE_20_HPP_
#define _HEAVY_CONTEXT_2TONE_20_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvMath.h"
#include "HvSignalDel1.h"
#include "HvControlCast.h"
#include "HvControlVar.h"
#include "HvControlSlice.h"
#include "HvControlBinop.h"
#include "HvSignalVar.h"
#include "HvSignalPhasor.h"
#include "HvControlSystem.h"
#include "HvSignalRPole.h"
#include "HvControlPack.h"

class Heavy_2tone_20 : public HeavyContext {

 public:
  Heavy_2tone_20(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_2tone_20();

  const char *getName() override { return "2tone_20"; }
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
  static void cVar_0kjvkmt4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_jChkGRpr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Drk2xaH8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_i5okpbHR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_bMIQeHos_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_2xMTzrO4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_03c4kUJK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_htIUl6Tb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_OdNCGeBN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_mDtca8Ri_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_oMCXK523_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_87WbZycv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_o8LNHM6L_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_1UFAExeO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_9kEnESpi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_7445UdKJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9Y2fpVCB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_vx4rzgXC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_T7PAqnt5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ldhDM8zL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_irYxSuHb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_g3oMqRPd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kcxBC1qP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZJ5aR7QN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_imDlcvHY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_uQusyC3c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_9iIcRVTA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nodTO8Sm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ar2cfKfb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Yg7pIsp4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PJnj0tv3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_W2GAvVrH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_KJIbHGxc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_X7ALEfVC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_n50EIq21_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_RlcRSxI0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_glou201g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_SyBOOAui_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_xY6h08oE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_6UGDeWwA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_54uviXs8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_NF41T0la_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_laAbUYsE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_eNRKlm3M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_tYl9h0tJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_gd3g8ob9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Kpxur5Em_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VR03n9cV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jmS8ZB4x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7psX8oTj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_33gP6RGR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2SUsTwaH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EGUORPT2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kaEEwbwj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dg7BsvOU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_iI5ce5L5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_mpquhSbO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_0TaNRAg0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_of1Lkwag_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_k514posP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ovusyvQR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Ldh5Ng89_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BN2fAO32_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vhJJio04_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WMn78hY6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_tcyly44U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_fSqdCCNa_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_9ZP8j2dg;
  SignalRPole sRPole_PobEBZuf;
  SignalPhasor sPhasor_qmD0A5Zm;
  SignalPhasor sPhasor_zpbfVUrk;
  SignalPhasor sPhasor_0kfnL0rA;
  SignalPhasor sPhasor_E9yVHxje;
  SignalRPole sRPole_ol4rDE3i;
  SignalDel1 sDel1_DXMWtpzV;
  ControlVar cVar_0kjvkmt4;
  ControlVar cVar_jChkGRpr;
  ControlVar cVar_Drk2xaH8;
  ControlVar cVar_i5okpbHR;
  ControlVar cVar_bMIQeHos;
  ControlVar cVar_2xMTzrO4;
  ControlVar cVar_03c4kUJK;
  ControlVar cVar_htIUl6Tb;
  ControlBinop cBinop_OdNCGeBN;
  ControlSlice cSlice_mDtca8Ri;
  ControlSlice cSlice_oMCXK523;
  ControlBinop cBinop_87WbZycv;
  ControlBinop cBinop_o8LNHM6L;
  SignalVarf sVarf_tFvCoT2w;
  ControlPack cPack_1UFAExeO;
  ControlPack cPack_9kEnESpi;
  ControlPack cPack_7445UdKJ;
  ControlSlice cSlice_9Y2fpVCB;
  ControlSlice cSlice_vx4rzgXC;
  ControlBinop cBinop_T7PAqnt5;
  ControlBinop cBinop_ldhDM8zL;
  SignalVarf sVarf_P3jZSEGI;
  ControlSlice cSlice_irYxSuHb;
  ControlSlice cSlice_g3oMqRPd;
  ControlBinop cBinop_kcxBC1qP;
  ControlBinop cBinop_ZJ5aR7QN;
  SignalVarf sVarf_TpNybESq;
  ControlVar cVar_imDlcvHY;
  ControlBinop cBinop_nodTO8Sm;
  ControlBinop cBinop_Ar2cfKfb;
  SignalVarf sVarf_FDghQdDA;
  ControlBinop cBinop_PJnj0tv3;
  ControlBinop cBinop_W2GAvVrH;
  ControlBinop cBinop_KJIbHGxc;
  SignalVarf sVarf_I5MdycSC;
  ControlSlice cSlice_X7ALEfVC;
  ControlSlice cSlice_n50EIq21;
  ControlSlice cSlice_RlcRSxI0;
  ControlSlice cSlice_glou201g;
  ControlSlice cSlice_SyBOOAui;
  ControlSlice cSlice_xY6h08oE;
  ControlSlice cSlice_6UGDeWwA;
  ControlSlice cSlice_54uviXs8;
  ControlBinop cBinop_NF41T0la;
  ControlBinop cBinop_laAbUYsE;
  SignalVarf sVarf_Hiok0H9n;
  ControlVar cVar_eNRKlm3M;
  ControlBinop cBinop_Kpxur5Em;
  ControlBinop cBinop_VR03n9cV;
  ControlBinop cBinop_7psX8oTj;
  ControlBinop cBinop_33gP6RGR;
  ControlBinop cBinop_2SUsTwaH;
  ControlBinop cBinop_EGUORPT2;
  ControlBinop cBinop_kaEEwbwj;
  SignalVarf sVarf_TP3AeMhX;
  ControlBinop cBinop_dg7BsvOU;
  ControlPack cPack_iI5ce5L5;
};

#endif // _HEAVY_CONTEXT_2TONE_20_HPP_
