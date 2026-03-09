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

#ifndef _HEAVY_CONTEXT_SHAPING_ARITHMETIC_HPP_
#define _HEAVY_CONTEXT_SHAPING_ARITHMETIC_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlCast.h"
#include "HvSignalTabwrite.h"
#include "HvControlVar.h"
#include "HvControlDelay.h"
#include "HvControlSlice.h"
#include "HvSignalVar.h"
#include "HvControlBinop.h"
#include "HvTable.h"
#include "HvMath.h"
#include "HvControlSystem.h"
#include "HvSignalPhasor.h"

class Heavy_shaping_arithmetic : public HeavyContext {

 public:
  Heavy_shaping_arithmetic(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_shaping_arithmetic();

  const char *getName() override { return "shaping_arithmetic"; }
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
  static void hTable_VJJlRKSW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_dUHwUjYJ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_6mBSsaVf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_TYw3icps_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_shyBH2w3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_JdDPI3ut_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JhsWAYzU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MrYPIC58_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iQLiYz9v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_G72rBSJo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_yHhJ6IZE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_42gz9sYg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ohzbdfnv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_thJBTF4t_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xeSY0X4u_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_drJq3fv9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_yWSKwLwn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_wVbJx25b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ttvLXpYL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_nAnarSG7_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_kZllJBHN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_bLX0lYaf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_r8H3Kcy6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_K686x0aK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_OoLyn2Zv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_pcS04dep_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UmXyi6mZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_BKnO8ZFt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_c3A71x1L_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_Box8vbSC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_TA0IJxo8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Ff6wqynS_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_o7ZQInRa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ewZjqBmo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_QQlAQmja_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_784IR5RW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZHJpv8az_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_XErN7KDI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_s2473X6N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ZJ8mlWbO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_uedHmZrA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Qg6x6PQM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Bo2KAVHU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_mTjajhjK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ob7X2AIm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iVii3yeV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_hmTgXZsj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_W6CJardL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_s3F0vgGD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_vWVuw5vo_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_DjUBgWeY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_5ZPTZXVO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_QVbcbnVV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_HbbarJlX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_kFQkuYQl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bnZ6pT25_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_7YYbaUxq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_4R2jjKh3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FcjQz7MG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mcXHULw7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_G5P39B3j_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_p4DNH4lt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8pDnonA8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_5Ny4o2QQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_kWp03dfq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_cpHYKlhq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_DxH6ymhd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_i1UVkuTn_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_kPTuHsvi;
  SignalTabwrite sTabwrite_Cnb3dSuL;
  SignalTabwrite sTabwrite_J4IwyiRh;
  SignalTabwrite sTabwrite_Mm1pauLl;
  HvTable hTable_VJJlRKSW;
  ControlDelay cDelay_6mBSsaVf;
  ControlVar cVar_TYw3icps;
  ControlSlice cSlice_shyBH2w3;
  ControlSlice cSlice_JdDPI3ut;
  ControlBinop cBinop_JhsWAYzU;
  ControlBinop cBinop_MrYPIC58;
  ControlBinop cBinop_42gz9sYg;
  ControlBinop cBinop_Ohzbdfnv;
  ControlDelay cDelay_kZllJBHN;
  ControlVar cVar_OoLyn2Zv;
  ControlBinop cBinop_UmXyi6mZ;
  ControlBinop cBinop_BKnO8ZFt;
  ControlBinop cBinop_c3A71x1L;
  HvTable hTable_TA0IJxo8;
  ControlDelay cDelay_o7ZQInRa;
  ControlVar cVar_ewZjqBmo;
  ControlSlice cSlice_QQlAQmja;
  ControlSlice cSlice_784IR5RW;
  ControlBinop cBinop_ZHJpv8az;
  ControlBinop cBinop_XErN7KDI;
  ControlBinop cBinop_Qg6x6PQM;
  ControlBinop cBinop_Bo2KAVHU;
  HvTable hTable_s3F0vgGD;
  ControlDelay cDelay_DjUBgWeY;
  ControlVar cVar_5ZPTZXVO;
  ControlSlice cSlice_QVbcbnVV;
  ControlSlice cSlice_HbbarJlX;
  ControlBinop cBinop_kFQkuYQl;
  ControlBinop cBinop_bnZ6pT25;
  ControlBinop cBinop_mcXHULw7;
  ControlBinop cBinop_G5P39B3j;
};

#endif // _HEAVY_CONTEXT_SHAPING_ARITHMETIC_HPP_
