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

#ifndef _HEAVY_CONTEXT_SHAPING_SQUAREWAVE_HPP_
#define _HEAVY_CONTEXT_SHAPING_SQUAREWAVE_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalPhasor.h"
#include "HvControlSlice.h"
#include "HvControlBinop.h"
#include "HvMath.h"
#include "HvControlCast.h"
#include "HvSignalTabwrite.h"
#include "HvTable.h"
#include "HvSignalVar.h"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvControlVar.h"

class Heavy_shaping_squarewave : public HeavyContext {

 public:
  Heavy_shaping_squarewave(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_squarewave();

  const char *getName() override { return "shaping_squarewave"; }
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
  static void hTable_4jAtn8tP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_TzimgNrI_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_afct70Nl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_3uYjzO2K_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_stG23Jyb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_hUzv6vtn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_zgg7Zh8u_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_L8TqI1H1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_YAZ2roJg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_HRPKIsM7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_aBVCBvc1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_g8pvp12Y_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kqRHk37T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Uz6HjJIS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_a8e4OTcF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_rwPH6q3H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oz9ehQwT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8kE0UKWB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_XfquoWje_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_CZSMje2H_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_LkO3b3eA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ebndbBO7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_6womY9iY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_6Ww8kNpi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_pERz1Z8B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VHKNQqTD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mFyTNv3m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_F69rAwpX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_F1MDL2uX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_lgXzGQVD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_GNOtH8rg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_uiStSDa4_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_vdlmljij_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_XRn19iTC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_ECk1SlOx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_kGDVRfKK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CwoVmq3A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sdSdr7CX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MNY0j8y9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_rW2fUzgp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_El1Se6MI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ywGgXDoY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vnSczODr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_C9eeuKWH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3SpGs8hG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8czSgMab_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_14TmWyjd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2IDFZwex_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_ljXcPCCj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_v8cTjs22_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_XidChdno;
  SignalTabwrite sTabwrite_y9cSE7Ka;
  SignalPhasor sPhasor_mIF9jYVo;
  HvTable hTable_4jAtn8tP;
  ControlDelay cDelay_afct70Nl;
  ControlVar cVar_3uYjzO2K;
  ControlSlice cSlice_stG23Jyb;
  ControlSlice cSlice_hUzv6vtn;
  ControlBinop cBinop_zgg7Zh8u;
  ControlBinop cBinop_L8TqI1H1;
  ControlBinop cBinop_g8pvp12Y;
  ControlBinop cBinop_kqRHk37T;
  ControlDelay cDelay_LkO3b3eA;
  ControlVar cVar_pERz1Z8B;
  ControlBinop cBinop_mFyTNv3m;
  ControlBinop cBinop_F69rAwpX;
  ControlBinop cBinop_F1MDL2uX;
  HvTable hTable_GNOtH8rg;
  ControlDelay cDelay_vdlmljij;
  ControlVar cVar_XRn19iTC;
  ControlSlice cSlice_ECk1SlOx;
  ControlSlice cSlice_kGDVRfKK;
  ControlBinop cBinop_CwoVmq3A;
  ControlBinop cBinop_sdSdr7CX;
  ControlBinop cBinop_ywGgXDoY;
  ControlBinop cBinop_vnSczODr;
  SignalVarf sVarf_R7a7Mrc1;
  SignalVarf sVarf_d7Qr80S6;
};

#endif // _HEAVY_CONTEXT_SHAPING_SQUAREWAVE_HPP_
