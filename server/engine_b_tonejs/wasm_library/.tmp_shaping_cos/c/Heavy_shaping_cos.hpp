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

#ifndef _HEAVY_CONTEXT_SHAPING_COS_HPP_
#define _HEAVY_CONTEXT_SHAPING_COS_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlVar.h"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvControlBinop.h"
#include "HvSignalPhasor.h"
#include "HvTable.h"
#include "HvControlCast.h"
#include "HvMath.h"
#include "HvSignalTabwrite.h"
#include "HvSignalVar.h"
#include "HvControlSlice.h"

class Heavy_shaping_cos : public HeavyContext {

 public:
  Heavy_shaping_cos(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_cos();

  const char *getName() override { return "shaping_cos"; }
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
  static void hTable_ZPZNjWIr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Dy2V9Zek_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_UwZKvJaa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Fz52Epbb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9NMcrN82_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_TPK1aeVI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QkneCh6q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_RRMTctOk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_OK2bSLD4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_s4FDWlSX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_AIfAsYsK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_AZptgzv9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_YNjMBMB4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_TguYCDN7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_AkvjANAG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_EEP1Hd1N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_PuBC25Pq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_i3q63lR5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_EbtcP5Zs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_GL9DXvc7_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_9MP2e4hx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_lsISyKs6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2a8gt8XZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_UGs5afen_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_JXOwe2sD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KHJNzUja_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UhHCBHnm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6Wr47AED_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_cmxouXzu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_V84dIRHH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_4tDIvDgb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_g9mn3STD_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_6BuXSQI9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_sDvwzQqr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_W1TZdhWx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_HUab98Sx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SrxeMjYC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_385kjnyR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ouH2HBfn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_tMTJPHlg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vhVdBNzi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9yOOdNHW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_18zsH4ZR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UdSycGJw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_5oKCU3lu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wqAPjqhU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_uYJYO18w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_s0WVa6ZM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_0hA7OsBp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_MLROCkdX_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_FGg60cqE;
  SignalTabwrite sTabwrite_kE7bC30H;
  SignalTabwrite sTabwrite_JOY4KGq1;
  HvTable hTable_ZPZNjWIr;
  ControlDelay cDelay_UwZKvJaa;
  ControlVar cVar_Fz52Epbb;
  ControlSlice cSlice_9NMcrN82;
  ControlSlice cSlice_TPK1aeVI;
  ControlBinop cBinop_QkneCh6q;
  ControlBinop cBinop_RRMTctOk;
  ControlBinop cBinop_AZptgzv9;
  ControlBinop cBinop_YNjMBMB4;
  ControlDelay cDelay_9MP2e4hx;
  ControlVar cVar_JXOwe2sD;
  ControlBinop cBinop_UhHCBHnm;
  ControlBinop cBinop_6Wr47AED;
  ControlBinop cBinop_cmxouXzu;
  HvTable hTable_4tDIvDgb;
  ControlDelay cDelay_6BuXSQI9;
  ControlVar cVar_sDvwzQqr;
  ControlSlice cSlice_W1TZdhWx;
  ControlSlice cSlice_HUab98Sx;
  ControlBinop cBinop_SrxeMjYC;
  ControlBinop cBinop_385kjnyR;
  ControlBinop cBinop_9yOOdNHW;
  ControlBinop cBinop_18zsH4ZR;
};

#endif // _HEAVY_CONTEXT_SHAPING_COS_HPP_
