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

#ifndef _HEAVY_CONTEXT_SHAPING_SCALE_HPP_
#define _HEAVY_CONTEXT_SHAPING_SCALE_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalPhasor.h"
#include "HvControlDelay.h"
#include "HvTable.h"
#include "HvControlCast.h"
#include "HvSignalVar.h"
#include "HvControlVar.h"
#include "HvControlSystem.h"
#include "HvSignalTabwrite.h"
#include "HvControlBinop.h"
#include "HvMath.h"
#include "HvControlSlice.h"

class Heavy_shaping_scale : public HeavyContext {

 public:
  Heavy_shaping_scale(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_scale();

  const char *getName() override { return "shaping_scale"; }
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
  static void hTable_BKtkdr3o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_M88sYfVl_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_apjhorFX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_veFQVRD0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_UYE2CVi2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_l3ukp85G_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QawBjEU8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rL4eeXi5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_bPrkLOYk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_gOZpQHY5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_SVAE04K8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HUYk0fJX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Zxci2mSe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_EXv798vv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BxbIFJSX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8AlRonzY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_n3wNGA7M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WJrTA2Kh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_m6FSpWlZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_C3ajnhqx_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_T2aEvwZt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_mYF6bgXq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_lOLOKoAQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_U4zTWo9L_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_HxeNwGVX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4Xzn0nlk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_yIxmPbea_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rx3PTrZt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_guEAUAhY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_U8hucmZ7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_RzEs5gag_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_EKYkXFDS_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_6tyBXYHA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_qcAY2LZK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_G3WqOkth_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_4fR39kNt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1O3WAFXX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9PDbWciS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_IDykBWhn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Z4PtjNsp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_SHYLOwks_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Kh197dYT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_oHho8WhX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UugzFohA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_6FiqHwB4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VVvJwlX3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_V7ooEsCh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_HbwEey29_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_mEWN4yVB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_uRLdBtrD_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabwrite sTabwrite_l3lvSd7g;
  SignalTabwrite sTabwrite_h2joczml;
  SignalPhasor sPhasor_PSFD79zi;
  HvTable hTable_BKtkdr3o;
  ControlDelay cDelay_apjhorFX;
  ControlVar cVar_veFQVRD0;
  ControlSlice cSlice_UYE2CVi2;
  ControlSlice cSlice_l3ukp85G;
  ControlBinop cBinop_QawBjEU8;
  ControlBinop cBinop_rL4eeXi5;
  ControlBinop cBinop_HUYk0fJX;
  ControlBinop cBinop_Zxci2mSe;
  ControlDelay cDelay_T2aEvwZt;
  ControlVar cVar_HxeNwGVX;
  ControlBinop cBinop_yIxmPbea;
  ControlBinop cBinop_rx3PTrZt;
  ControlBinop cBinop_guEAUAhY;
  HvTable hTable_RzEs5gag;
  ControlDelay cDelay_6tyBXYHA;
  ControlVar cVar_qcAY2LZK;
  ControlSlice cSlice_G3WqOkth;
  ControlSlice cSlice_4fR39kNt;
  ControlBinop cBinop_1O3WAFXX;
  ControlBinop cBinop_9PDbWciS;
  ControlBinop cBinop_Kh197dYT;
  ControlBinop cBinop_oHho8WhX;
  SignalVarf sVarf_08lNsmUZ;
  SignalVarf sVarf_VSeOgGfg;
};

#endif // _HEAVY_CONTEXT_SHAPING_SCALE_HPP_
