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

#ifndef _HEAVY_CONTEXT_2TONE_15_HPP_
#define _HEAVY_CONTEXT_2TONE_15_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalVar.h"
#include "HvSignalDel1.h"
#include "HvSignalRPole.h"
#include "HvControlSystem.h"
#include "HvSignalLine.h"
#include "HvControlCast.h"
#include "HvSignalPhasor.h"
#include "HvMath.h"
#include "HvControlBinop.h"
#include "HvControlDelay.h"
#include "HvControlVar.h"

class Heavy_2tone_15 : public HeavyContext {

 public:
  Heavy_2tone_15(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_2tone_15();

  const char *getName() override { return "2tone_15"; }
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
  static void cVar_FTqucBSC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Sy90krqc_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_wqOAjN6Z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_KWJE2qWm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_7jhG5B9p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VUCuV84A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_PleEyFof_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wqxKW3Zy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_vm2rEcfs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_QJho6J7I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Mhsu2WHX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_6NlJQdF2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_EX3VhMDD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_6dPhPkt1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_8QBews55_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sZyoRuS9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JpIPJQ4U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_RFdd731p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_XgNExud1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_186CA248_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bkwpjVCK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gxMVy8Mr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_H5Ulroee_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9n0jxkdU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6Bzki5P2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0SoP7CMA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lrPrlPNC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vMevLBLq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_b7rXOPo1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_abvOajIA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_nmSx3k8z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_x8T1RSJa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_v6AggQ4u_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_m8Eh4eah_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MCWaF56R_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_cVg0sOIm_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalLine sLine_fUqPN3z4;
  SignalPhasor sPhasor_mLxGyyKH;
  SignalPhasor sPhasor_Jr8hpzzM;
  SignalPhasor sPhasor_tAM4k0dw;
  SignalPhasor sPhasor_wM9GauHW;
  SignalRPole sRPole_akDI6yiM;
  SignalDel1 sDel1_kdDG1Uqh;
  ControlVar cVar_FTqucBSC;
  ControlDelay cDelay_wqOAjN6Z;
  SignalVarf sVarf_mG1qm3z5;
  ControlVar cVar_6NlJQdF2;
  ControlVar cVar_EX3VhMDD;
  ControlVar cVar_6dPhPkt1;
  ControlBinop cBinop_sZyoRuS9;
  ControlBinop cBinop_JpIPJQ4U;
  SignalVarf sVarf_GLy33lxR;
  ControlVar cVar_RFdd731p;
  ControlBinop cBinop_bkwpjVCK;
  ControlBinop cBinop_gxMVy8Mr;
  ControlBinop cBinop_9n0jxkdU;
  ControlBinop cBinop_6Bzki5P2;
  ControlBinop cBinop_0SoP7CMA;
  ControlBinop cBinop_lrPrlPNC;
  ControlBinop cBinop_vMevLBLq;
  SignalVarf sVarf_P0eW1cTo;
  ControlVar cVar_b7rXOPo1;
  ControlVar cVar_abvOajIA;
  ControlVar cVar_nmSx3k8z;
  ControlBinop cBinop_x8T1RSJa;
  SignalVarf sVarf_1d4MFeLe;
  ControlBinop cBinop_v6AggQ4u;
  SignalVarf sVarf_fLO0FZ64;
  ControlBinop cBinop_m8Eh4eah;
  SignalVarf sVarf_emlXx8Sj;
  ControlBinop cBinop_MCWaF56R;
  SignalVarf sVarf_PmJ68K1E;
};

#endif // _HEAVY_CONTEXT_2TONE_15_HPP_
