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

#ifndef _HEAVY_CONTEXT_SHAPING_POLYNOMIALS_HPP_
#define _HEAVY_CONTEXT_SHAPING_POLYNOMIALS_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvTable.h"
#include "HvMath.h"
#include "HvControlSlice.h"
#include "HvControlSystem.h"
#include "HvControlDelay.h"
#include "HvSignalVar.h"
#include "HvSignalPhasor.h"
#include "HvControlVar.h"
#include "HvControlBinop.h"
#include "HvSignalTabwrite.h"
#include "HvControlCast.h"

class Heavy_shaping_polynomials : public HeavyContext {

 public:
  Heavy_shaping_polynomials(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_polynomials();

  const char *getName() override { return "shaping_polynomials"; }
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
  static void hTable_uLEB3iXt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_zKb3EYuF_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_YVAtVmjL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_NKqvBAyS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_YdgQkJZU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_couov11r_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HqacsxJA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_P2y8uHL7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Fvuc2Ws9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_nmCMHJlu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_alZDTBVr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dBITvYdU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ElBnoNZb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_NvXjx7Nx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_578IDl2X_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_7m70zddh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_orBDRQPi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WrJvITcT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_yXqCHHOL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_bNmpS2l8_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_KXT9Eo7W_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_TL488OXd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_B5vUrP6n_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oFYlKAMk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_1uE7sXbd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_nO4fQIOF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_7CsP4WZ2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iTrPu4hH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ajy04p1X_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_jBflMECh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_N6jJgR9w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_yJnRTS7e_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_m9rz4tJ5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_4o80gi6M_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_dBDZolMV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_0LZXnlK4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_SXG8kcGt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gZ9yqUTW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_PUA2YDuW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_bQUer7Wh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_IdbT1Ge6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_aCx5h5A5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bxhZFYa0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_fGP5GKFU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2ZyIErCa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WVRNit4o_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_nPCyxaLh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_phmFNyMc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_fCMASi7V_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_fS3FOPcB_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_JzWtciKz;
  SignalTabwrite sTabwrite_AQKrmlxS;
  SignalPhasor sPhasor_Rl27cmrt;
  SignalTabwrite sTabwrite_dtOA06Ri;
  HvTable hTable_uLEB3iXt;
  ControlDelay cDelay_YVAtVmjL;
  ControlVar cVar_NKqvBAyS;
  ControlSlice cSlice_YdgQkJZU;
  ControlSlice cSlice_couov11r;
  ControlBinop cBinop_HqacsxJA;
  ControlBinop cBinop_P2y8uHL7;
  ControlBinop cBinop_dBITvYdU;
  ControlBinop cBinop_ElBnoNZb;
  ControlDelay cDelay_KXT9Eo7W;
  ControlVar cVar_1uE7sXbd;
  ControlBinop cBinop_7CsP4WZ2;
  ControlBinop cBinop_iTrPu4hH;
  ControlBinop cBinop_Ajy04p1X;
  HvTable hTable_N6jJgR9w;
  ControlDelay cDelay_m9rz4tJ5;
  ControlVar cVar_4o80gi6M;
  ControlSlice cSlice_dBDZolMV;
  ControlSlice cSlice_0LZXnlK4;
  ControlBinop cBinop_SXG8kcGt;
  ControlBinop cBinop_gZ9yqUTW;
  ControlBinop cBinop_aCx5h5A5;
  ControlBinop cBinop_bxhZFYa0;
};

#endif // _HEAVY_CONTEXT_SHAPING_POLYNOMIALS_HPP_
