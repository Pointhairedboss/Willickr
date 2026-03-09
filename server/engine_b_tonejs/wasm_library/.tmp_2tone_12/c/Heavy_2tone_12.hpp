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

#ifndef _HEAVY_CONTEXT_2TONE_12_HPP_
#define _HEAVY_CONTEXT_2TONE_12_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlSystem.h"
#include "HvControlBinop.h"
#include "HvControlCast.h"
#include "HvControlDelay.h"
#include "HvSignalRPole.h"
#include "HvControlVar.h"
#include "HvSignalDel1.h"
#include "HvMath.h"

class Heavy_2tone_12 : public HeavyContext {

 public:
  Heavy_2tone_12(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_2tone_12();

  const char *getName() override { return "2tone_12"; }
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
  static void cVar_tnIm8Tb2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZVubnIcM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_jaqFVNVk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_n0hAf4UE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_L6fUbmSE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QUW5n5El_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wF5Lg2LQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0hWUHMqx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7iJjqqkk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_xwavDevN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2xbssXw2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_mdR3yv2N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1yuxnJg1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_NhrqvHTT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Gog5rQQJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lq20aG8y_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wqxkRP8O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DLpEPOs3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_hxJrbjRo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_tkUHb4Zr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_GUyuwMyK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JRykUHdr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7L6EeZE5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DkmmY7rm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vgdJFsmg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jYaefxWk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_enStkEw6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_RcRXRLkq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_bfPU716U_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_kt74U0iH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_irbRTSfo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QPwiljPx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_r2GVoclO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_AsaaLNr3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KIbRWrP0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Svlb7Vr8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_23CPjzv6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_n55Y0OtU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ob2TQVM1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0vxXL69k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6VptXnt1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EGiIU5xh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_OVc6XJnZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_AkuDP4EO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_0D2bVVpm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_KcQNJfwe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_map2Ta7U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5pDVKC3U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_8j9wNufl_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_oluRzgi5;
  SignalRPole sRPole_ruPxbT1S;
  SignalPhasor sPhasor_ozhg9yiu;
  SignalRPole sRPole_hOKTun2x;
  SignalPhasor sPhasor_Btg9TBrc;
  SignalRPole sRPole_UpoU5Zwo;
  ControlVar cVar_tnIm8Tb2;
  ControlBinop cBinop_n0hAf4UE;
  ControlBinop cBinop_L6fUbmSE;
  SignalVarf sVarf_ZXCcGevu;
  ControlBinop cBinop_wF5Lg2LQ;
  ControlBinop cBinop_0hWUHMqx;
  ControlBinop cBinop_7iJjqqkk;
  SignalVarf sVarf_V6NfLYFj;
  ControlVar cVar_xwavDevN;
  ControlBinop cBinop_1yuxnJg1;
  ControlBinop cBinop_NhrqvHTT;
  SignalVarf sVarf_xafsAHvl;
  ControlBinop cBinop_lq20aG8y;
  ControlBinop cBinop_wqxkRP8O;
  ControlBinop cBinop_DLpEPOs3;
  SignalVarf sVarf_maYDJQrU;
  ControlVar cVar_hxJrbjRo;
  ControlBinop cBinop_JRykUHdr;
  ControlBinop cBinop_7L6EeZE5;
  SignalVarf sVarf_O3ypvnYy;
  ControlBinop cBinop_vgdJFsmg;
  ControlBinop cBinop_jYaefxWk;
  ControlBinop cBinop_enStkEw6;
  SignalVarf sVarf_Pyc2t3d5;
  SignalVarf sVarf_kxXl8wcT;
  SignalVarf sVarf_DT6E0doz;
  SignalVarf sVarf_aDX8JmMH;
  ControlVar cVar_RcRXRLkq;
  ControlDelay cDelay_kt74U0iH;
  ControlVar cVar_AsaaLNr3;
  ControlBinop cBinop_Svlb7Vr8;
  ControlBinop cBinop_23CPjzv6;
  ControlBinop cBinop_n55Y0OtU;
  ControlVar cVar_ob2TQVM1;
  ControlBinop cBinop_0vxXL69k;
  ControlBinop cBinop_6VptXnt1;
  ControlBinop cBinop_OVc6XJnZ;
  ControlBinop cBinop_map2Ta7U;
  ControlBinop cBinop_5pDVKC3U;
};

#endif // _HEAVY_CONTEXT_2TONE_12_HPP_
