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

#ifndef _HEAVY_CONTEXT_SHAPING_MINMAX_HPP_
#define _HEAVY_CONTEXT_SHAPING_MINMAX_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalTabwrite.h"
#include "HvControlDelay.h"
#include "HvSignalVar.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvTable.h"
#include "HvControlSystem.h"
#include "HvControlCast.h"
#include "HvSignalPhasor.h"
#include "HvControlBinop.h"
#include "HvControlSlice.h"

class Heavy_shaping_minmax : public HeavyContext {

 public:
  Heavy_shaping_minmax(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_minmax();

  const char *getName() override { return "shaping_minmax"; }
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
  static void hTable_zRgtrRFe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_vfHT71x5_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_OqNQHyjn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_NG42awh6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_yUStepZk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_jvpwvXuJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gjLQuAb9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jesNHJvD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_PWh0gHXD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_vZmtieSt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_A8pBAU9d_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Lw3Qz9S4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GtGDv4w4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ef7hivBn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Ew4LyEmp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_J9ow7ZDr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_L6AIDGvF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gseBLFvM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_n1BkASix_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_hzxxVjuc_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_eEowUXGD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_MVjAPUvZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_e1Oszhj1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_MK7PUN6B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_3HXsJROJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_chwSCauL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1fneS8rT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_McKoLDQp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ADvNjijF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_EOJrUMh0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_0wJkfi7m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_DSmaujap_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_aFkJg6kC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_iT7Bd6qM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_iCeIPI9o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_6FkNmg20_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qrTYYS65_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ufbFxF3I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ryzfrCRa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_lNHZ8Soe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jUnGEw9P_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_o9xNF5Wo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6b4gHhp9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_cgh00ws1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_7KLdRNcE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FLGmOMtD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Hai640cq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_K9AvwhVh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_Bn3FxGBI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_xdvVulS7_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_9BWh6mRm;
  SignalTabwrite sTabwrite_tcZTL4kw;
  SignalPhasor sPhasor_iGxycpBm;
  HvTable hTable_zRgtrRFe;
  ControlDelay cDelay_OqNQHyjn;
  ControlVar cVar_NG42awh6;
  ControlSlice cSlice_yUStepZk;
  ControlSlice cSlice_jvpwvXuJ;
  ControlBinop cBinop_gjLQuAb9;
  ControlBinop cBinop_jesNHJvD;
  ControlBinop cBinop_Lw3Qz9S4;
  ControlBinop cBinop_GtGDv4w4;
  ControlDelay cDelay_eEowUXGD;
  ControlVar cVar_3HXsJROJ;
  ControlBinop cBinop_1fneS8rT;
  ControlBinop cBinop_McKoLDQp;
  ControlBinop cBinop_ADvNjijF;
  HvTable hTable_0wJkfi7m;
  ControlDelay cDelay_aFkJg6kC;
  ControlVar cVar_iT7Bd6qM;
  ControlSlice cSlice_iCeIPI9o;
  ControlSlice cSlice_6FkNmg20;
  ControlBinop cBinop_qrTYYS65;
  ControlBinop cBinop_ufbFxF3I;
  ControlBinop cBinop_o9xNF5Wo;
  ControlBinop cBinop_6b4gHhp9;
  SignalVarf sVarf_FEQOBaS1;
  SignalVarf sVarf_DKuS3nQZ;
};

#endif // _HEAVY_CONTEXT_SHAPING_MINMAX_HPP_
