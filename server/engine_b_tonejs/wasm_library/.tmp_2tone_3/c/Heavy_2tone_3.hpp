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

#ifndef _HEAVY_CONTEXT_2TONE_3_HPP_
#define _HEAVY_CONTEXT_2TONE_3_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalDel1.h"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlBinop.h"
#include "HvControlSystem.h"
#include "HvSignalRPole.h"
#include "HvMath.h"
#include "HvControlVar.h"

class Heavy_2tone_3 : public HeavyContext {

 public:
  Heavy_2tone_3(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_2tone_3();

  const char *getName() override { return "2tone_3"; }
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
  static void cVar_NbquS7he_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8lp4yof2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_mAq4i3jf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_pICgESgN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_e2o1B5Q6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sGPZtO0Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_T7PO35CK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZPD5Rfp5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UnyLK0Rg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_C0dhl2u1_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_sVLne9c8;
  SignalPhasor sPhasor_6Ms38uN8;
  SignalRPole sRPole_dn2Qc5P2;
  ControlVar cVar_NbquS7he;
  ControlBinop cBinop_pICgESgN;
  ControlBinop cBinop_e2o1B5Q6;
  SignalVarf sVarf_wOV6q4Bj;
  ControlBinop cBinop_T7PO35CK;
  ControlBinop cBinop_ZPD5Rfp5;
  ControlBinop cBinop_UnyLK0Rg;
  SignalVarf sVarf_K0kjg2RB;
};

#endif // _HEAVY_CONTEXT_2TONE_3_HPP_
