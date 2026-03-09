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

#ifndef _HEAVY_CONTEXT_SHAPING_INTEGRATION_HPP_
#define _HEAVY_CONTEXT_SHAPING_INTEGRATION_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalVar.h"
#include "HvControlCast.h"
#include "HvSignalPhasor.h"
#include "HvControlBinop.h"
#include "HvControlDelay.h"
#include "HvSignalDel1.h"
#include "HvSignalTabwrite.h"
#include "HvControlSystem.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvSignalRPole.h"
#include "HvTable.h"
#include "HvControlSlice.h"

class Heavy_shaping_integration : public HeavyContext {

 public:
  Heavy_shaping_integration(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_integration();

  const char *getName() override { return "shaping_integration"; }
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
  static void hTable_wF4HL79s_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_9lIdtJ1l_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_dXQPtzdF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ND6GZqjI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_sEv0yABX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_vzub0wBe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_b7y3L56U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WA0HSiS2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_TkZnsl2a_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ITsDXwX5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ELxjfhRN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SrbS7L6a_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6XRfYz6O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_OVMUWDdb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_TK82tBQh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VuFUrDDr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_z3YErL6o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Q3offrj7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Nh2CEYPp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_1Eur89e0_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_ru552Ysx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_FA5ioBUv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jZrAy2bh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_m8yhxDN0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_wFBv9XHo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8cH52XLZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5m2DUD8Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ij9xjcTT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_K9FqzQ9P_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_Iu7uW8Zs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_UCoAEAvo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_612GOvZ8_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_SzD5BKKY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_xdyh4txj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_VApKN59i_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_vlE9c4Rr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EGNq4E1L_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wrArK890_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_eISPJ3A9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_GYMGSlTG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_7tomVcNr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_yuRRnwyM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6E2ELEou_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jFSIUiKF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9Hazk9TG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_lXBtaVBW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_BaPN4o7w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gC04Yk43_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_Pi0mrkmG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_QyjmQOi7_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_4OxWslWw;
  SignalTabwrite sTabwrite_v7TbbVee;
  SignalRPole sRPole_FNoadToK;
  SignalTabwrite sTabwrite_Gz1sVCTC;
  HvTable hTable_wF4HL79s;
  ControlDelay cDelay_dXQPtzdF;
  ControlVar cVar_ND6GZqjI;
  ControlSlice cSlice_sEv0yABX;
  ControlSlice cSlice_vzub0wBe;
  ControlBinop cBinop_b7y3L56U;
  ControlBinop cBinop_WA0HSiS2;
  ControlBinop cBinop_SrbS7L6a;
  ControlBinop cBinop_6XRfYz6O;
  ControlDelay cDelay_ru552Ysx;
  ControlVar cVar_wFBv9XHo;
  ControlBinop cBinop_5m2DUD8Q;
  ControlBinop cBinop_Ij9xjcTT;
  ControlBinop cBinop_K9FqzQ9P;
  HvTable hTable_UCoAEAvo;
  ControlDelay cDelay_SzD5BKKY;
  ControlVar cVar_xdyh4txj;
  ControlSlice cSlice_VApKN59i;
  ControlSlice cSlice_vlE9c4Rr;
  ControlBinop cBinop_EGNq4E1L;
  ControlBinop cBinop_wrArK890;
  ControlBinop cBinop_yuRRnwyM;
  ControlBinop cBinop_6E2ELEou;
};

#endif // _HEAVY_CONTEXT_SHAPING_INTEGRATION_HPP_
