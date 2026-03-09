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

#ifndef _HEAVY_CONTEXT_2TONE_25_HPP_
#define _HEAVY_CONTEXT_2TONE_25_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalRPole.h"
#include "HvSignalVar.h"
#include "HvControlUnop.h"
#include "HvControlPack.h"
#include "HvSignalLine.h"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvSignalPhasor.h"
#include "HvControlIf.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvSignalDel1.h"
#include "HvControlBinop.h"
#include "HvControlCast.h"
#include "HvControlSlice.h"

class Heavy_2tone_25 : public HeavyContext {

 public:
  Heavy_2tone_25(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_2tone_25();

  const char *getName() override { return "2tone_25"; }
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
  static void cVar_M2NuhSj9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Abp5IEv2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_fX6MUcN8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_aH08IhCI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_J2qzjDYz_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_tjzobjv1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_q2FnP6tV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_WdLl6yZn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DFqc5uw4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_39RXF6mt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FBfulPbC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ndV04Tci_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Vo9WL5NN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_kDWWV5GQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_O9ZPli7u_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eGP3Oe2m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_1a78a3Ae_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1qg2Sv5u_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_Z4ycocde_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_svJgaGxX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_I7rPN5g4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2NLaCwBi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_AhB2FNjf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2OHwI9Bz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_yUM8sr6e_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZO6zPdcP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_QfDxgSYj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_hJeN5G0e_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_C68kM6c8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_xOTh6r7D_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_4T0LpNgK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_GBNk5LrH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Tlf13kRU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_j5KJBVf5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rCuQxOaj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9668A7Um_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HtkvosXL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5mAqKfJW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_FqTgLtmM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_GTRI2xmJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_fY9Aj55c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_Ct9kBjsE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_LcncBpQD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_GVio9dCL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_R7mbhvdX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_9bo0l9fI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wQknrIww_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_XY6VXG9E_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_MKWrwQii_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8zNcqOu9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_e41wm9Cm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MO3nalNJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_SQ99D8Vh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wyRO5kBg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_pdqn7AA0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gLfqNVBc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iMLHQtSY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_0xRmNDs0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GeNMM97p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8BXtKm2K_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_WqG3urDI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_D8zULkkO_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_9dDm4VtH;
  SignalLine sLine_fossO5ok;
  SignalPhasor sPhasor_QDCRQZtF;
  SignalPhasor sPhasor_e4mqTWBX;
  SignalPhasor sPhasor_eu4rH2iT;
  SignalRPole sRPole_LoCCV2YG;
  SignalDel1 sDel1_0VF57fVm;
  ControlVar cVar_M2NuhSj9;
  ControlVar cVar_Abp5IEv2;
  ControlVar cVar_fX6MUcN8;
  ControlVar cVar_aH08IhCI;
  ControlDelay cDelay_tjzobjv1;
  SignalVarf sVarf_VP1NysCn;
  ControlBinop cBinop_O9ZPli7u;
  ControlBinop cBinop_eGP3Oe2m;
  SignalVarf sVarf_NyRQA8cR;
  ControlVar cVar_1a78a3Ae;
  ControlBinop cBinop_svJgaGxX;
  ControlBinop cBinop_I7rPN5g4;
  ControlBinop cBinop_AhB2FNjf;
  ControlBinop cBinop_2OHwI9Bz;
  ControlBinop cBinop_yUM8sr6e;
  ControlBinop cBinop_ZO6zPdcP;
  ControlBinop cBinop_QfDxgSYj;
  SignalVarf sVarf_RcaVUIst;
  ControlSlice cSlice_hJeN5G0e;
  ControlSlice cSlice_C68kM6c8;
  ControlSlice cSlice_xOTh6r7D;
  ControlSlice cSlice_4T0LpNgK;
  ControlSlice cSlice_GBNk5LrH;
  ControlSlice cSlice_Tlf13kRU;
  ControlSlice cSlice_j5KJBVf5;
  ControlBinop cBinop_rCuQxOaj;
  SignalVarf sVarf_WRoUlq73;
  ControlBinop cBinop_9668A7Um;
  SignalVarf sVarf_2QIoH1NQ;
  ControlBinop cBinop_HtkvosXL;
  SignalVarf sVarf_MAskURAF;
  ControlBinop cBinop_5mAqKfJW;
  SignalVarf sVarf_Lq9xVsMf;
  ControlVar cVar_FqTgLtmM;
  ControlVar cVar_GTRI2xmJ;
  ControlVar cVar_fY9Aj55c;
  ControlPack cPack_Ct9kBjsE;
  ControlVar cVar_LcncBpQD;
  ControlIf cIf_9bo0l9fI;
  ControlBinop cBinop_wQknrIww;
};

#endif // _HEAVY_CONTEXT_2TONE_25_HPP_
