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

#include "Heavy_shaping_antiphase.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_antiphase *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_antiphase_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_antiphase));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_antiphase(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_antiphase_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_antiphase));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_antiphase(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_antiphase_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_antiphase();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_antiphase::Heavy_shaping_antiphase(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_tw5En2RY, 670.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_DWBkCHEL, &hTable_OnSSKNGe);
  numBytes += sTabhead_init(&sTabhead_IHira7ZX, &hTable_Letgajgb);
  numBytes += sTabread_init(&sTabread_hIkXsKXc, &hTable_Letgajgb, false);
  numBytes += sTabread_init(&sTabread_rmdJflzp, &hTable_Letgajgb, false);
  numBytes += sTabwrite_init(&sTabwrite_nK03YFPf, &hTable_QR2FbsGH);
  numBytes += sTabwrite_init(&sTabwrite_SHSkGHvV, &hTable_zBXIaPW2);
  numBytes += sTabwrite_init(&sTabwrite_Uyn3e8MU, &hTable_Letgajgb);
  numBytes += hTable_init(&hTable_OnSSKNGe, 100);
  numBytes += cDelay_init(this, &cDelay_EpvZt1cv, 0.0f);
  numBytes += cVar_init_s(&cVar_6RzMDb9w, "A");
  numBytes += cSlice_init(&cSlice_elSgZlJW, 1, 1);
  numBytes += cSlice_init(&cSlice_j6tapito, 1, 1);
  numBytes += cBinop_init(&cBinop_a3T8uVE6, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_RSCXg6Zp, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_1mLa5FjA, 0.0f);
  numBytes += cVar_init_f(&cVar_ingYMZKt, 200.0f);
  numBytes += cBinop_init(&cBinop_LCsUyGxK, 0.0f); // __mul
  numBytes += hTable_init(&hTable_QR2FbsGH, 100);
  numBytes += cDelay_init(this, &cDelay_qyEA7ORp, 0.0f);
  numBytes += cVar_init_s(&cVar_iqjn2LzZ, "B");
  numBytes += cSlice_init(&cSlice_JLAPK8FA, 1, 1);
  numBytes += cSlice_init(&cSlice_FIeviGzh, 1, 1);
  numBytes += cBinop_init(&cBinop_BrhoeTgg, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_lb7niaB7, 0.0f); // __sub
  numBytes += hTable_init(&hTable_zBXIaPW2, 100);
  numBytes += cDelay_init(this, &cDelay_CouNlwYn, 0.0f);
  numBytes += cVar_init_s(&cVar_L126blV9, "C");
  numBytes += cSlice_init(&cSlice_YMFoalMF, 1, 1);
  numBytes += cSlice_init(&cSlice_rbJvrcb4, 1, 1);
  numBytes += cBinop_init(&cBinop_zRSMWQ6k, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_DLgA10kt, 0.0f); // __sub
  numBytes += cVar_init_s(&cVar_X5nuE080, "del-d1");
  numBytes += sVarf_init(&sVarf_N09yXvo7, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_uQMCIw2K, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_ZyLx5Kcr, 0.0f, 0.0f, false);
  numBytes += cDelay_init(this, &cDelay_AyxpUdTu, 0.0f);
  numBytes += cDelay_init(this, &cDelay_utRgvsYX, 0.0f);
  numBytes += hTable_init(&hTable_Letgajgb, 256);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_antiphase::~Heavy_shaping_antiphase() {
  hTable_free(&hTable_OnSSKNGe);
  hTable_free(&hTable_QR2FbsGH);
  hTable_free(&hTable_zBXIaPW2);
  hTable_free(&hTable_Letgajgb);
}

HvTable *Heavy_shaping_antiphase::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_OnSSKNGe; // A
    case 0xD961DF96: return &hTable_QR2FbsGH; // B
    case 0x7F1A5B02: return &hTable_zBXIaPW2; // C
    case 0x53B53393: return &hTable_Letgajgb; // del-d1
    default: return nullptr;
  }
}

void Heavy_shaping_antiphase::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_wLqBFMbr_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_m2nqZwfk_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_antiphase::getParameterInfo(int index, HvParameterInfo *info) {
  if (info != nullptr) {
    switch (index) {
      default: {
        info->name = "invalid parameter index";
        info->hash = 0;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 0.0f;
        info->defaultVal = 0.0f;
        break;
      }
    }
  }
  return 0;
}



/*
 * Send Function Implementations
 */


void Heavy_shaping_antiphase::hTable_OnSSKNGe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_antiphase::cSwitchcase_cDec39zX_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_j6tapito, 0, m, &cSlice_j6tapito_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_lerw2eug_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_elSgZlJW, 0, m, &cSlice_elSgZlJW_sendMessage);
      break;
    }
    default: {
      cMsg_EDYkSJSw_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_antiphase::cDelay_EpvZt1cv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_EpvZt1cv, m);
  cMsg_lerw2eug_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cVar_6RzMDb9w_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_s4qc71wm_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cSlice_elSgZlJW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_DWBkCHEL, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_6RzMDb9w, 0, m, &cVar_6RzMDb9w_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_antiphase::cSlice_j6tapito_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_DWBkCHEL, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_RSCXg6Zp, HV_BINOP_SUBTRACT, 0, m, &cBinop_RSCXg6Zp_sendMessage);
      break;
    }
    case 1: {
      cMsg_ZgglqEel_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_antiphase::cBinop_gkZmtWCy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_a3T8uVE6, HV_BINOP_DIVIDE, 1, m, &cBinop_a3T8uVE6_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_a3T8uVE6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_mtiuWA1d_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_EpvZt1cv, 1, m, &cDelay_EpvZt1cv_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_EpvZt1cv, 0, m, &cDelay_EpvZt1cv_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_EDYkSJSw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_DWBkCHEL, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_RSCXg6Zp, HV_BINOP_SUBTRACT, 0, m, &cBinop_RSCXg6Zp_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_aLCRWAwh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_RSCXg6Zp, HV_BINOP_SUBTRACT, 1, m, &cBinop_RSCXg6Zp_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_s4qc71wm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_aLCRWAwh_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_RSCXg6Zp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_lo4EdVoV_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_lo4EdVoV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_a3T8uVE6, HV_BINOP_DIVIDE, 0, m, &cBinop_a3T8uVE6_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_mtiuWA1d_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_EpvZt1cv, 0, m, &cDelay_EpvZt1cv_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_lerw2eug_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_DWBkCHEL, 1, m, NULL);
}

void Heavy_shaping_antiphase::cMsg_5TdifJNd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_1xGyOxlq_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_1xGyOxlq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_gkZmtWCy_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_ZgglqEel_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_DWBkCHEL, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_RSCXg6Zp, HV_BINOP_SUBTRACT, 0, m, &cBinop_RSCXg6Zp_sendMessage);
}

void Heavy_shaping_antiphase::cCast_UUR22lls_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_m8j8usye_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_antiphase::cSwitchcase_m8j8usye_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_4tj1xLZG_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_4tj1xLZG_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_6KaKn1mm_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_antiphase::cDelay_1mLa5FjA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_1mLa5FjA, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_1mLa5FjA, 0, m, &cDelay_1mLa5FjA_sendMessage);
  cSwitchcase_cDec39zX_onMessage(_c, NULL, 0, m, NULL);
  cSend_qRDGmQs3_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cCast_6KaKn1mm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_4tj1xLZG_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_1mLa5FjA, 0, m, &cDelay_1mLa5FjA_sendMessage);
  cSwitchcase_cDec39zX_onMessage(_c, NULL, 0, m, NULL);
  cSend_qRDGmQs3_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cMsg_LkkFB7F8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Ml5vq1Ws_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_Ml5vq1Ws_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_pfjSM6d8_sendMessage);
}

void Heavy_shaping_antiphase::cVar_ingYMZKt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LCsUyGxK, HV_BINOP_MULTIPLY, 0, m, &cBinop_LCsUyGxK_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_4tj1xLZG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_1mLa5FjA, 0, m, &cDelay_1mLa5FjA_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_sQ3Os5hr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_1mLa5FjA, 2, m, &cDelay_1mLa5FjA_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_pfjSM6d8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LCsUyGxK, HV_BINOP_MULTIPLY, 1, m, &cBinop_LCsUyGxK_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_LCsUyGxK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_sQ3Os5hr_sendMessage);
}

void Heavy_shaping_antiphase::cSend_qRDGmQs3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_m2nqZwfk_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::hTable_QR2FbsGH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_antiphase::cSwitchcase_z2cI05cG_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_FIeviGzh, 0, m, &cSlice_FIeviGzh_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_SuE9lMe7_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_JLAPK8FA, 0, m, &cSlice_JLAPK8FA_sendMessage);
      break;
    }
    default: {
      cMsg_rXnOJeC5_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_antiphase::cDelay_qyEA7ORp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_qyEA7ORp, m);
  cMsg_SuE9lMe7_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cVar_iqjn2LzZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_o2iJvKrP_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cSlice_JLAPK8FA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_nK03YFPf, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_iqjn2LzZ, 0, m, &cVar_iqjn2LzZ_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_antiphase::cSlice_FIeviGzh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_nK03YFPf, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_lb7niaB7, HV_BINOP_SUBTRACT, 0, m, &cBinop_lb7niaB7_sendMessage);
      break;
    }
    case 1: {
      cMsg_dAfvO4L0_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_antiphase::cBinop_iQCtZBhy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BrhoeTgg, HV_BINOP_DIVIDE, 1, m, &cBinop_BrhoeTgg_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_BrhoeTgg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_WR3SAEUz_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_qyEA7ORp, 1, m, &cDelay_qyEA7ORp_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_qyEA7ORp, 0, m, &cDelay_qyEA7ORp_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_rXnOJeC5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_nK03YFPf, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lb7niaB7, HV_BINOP_SUBTRACT, 0, m, &cBinop_lb7niaB7_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_qmsI0AWb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lb7niaB7, HV_BINOP_SUBTRACT, 1, m, &cBinop_lb7niaB7_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_o2iJvKrP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_qmsI0AWb_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_lb7niaB7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_KyB2waXZ_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_KyB2waXZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BrhoeTgg, HV_BINOP_DIVIDE, 0, m, &cBinop_BrhoeTgg_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_WR3SAEUz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_qyEA7ORp, 0, m, &cDelay_qyEA7ORp_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_SuE9lMe7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_nK03YFPf, 1, m, NULL);
}

void Heavy_shaping_antiphase::cMsg_pXkHJKUZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Up4c6SPQ_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_Up4c6SPQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_iQCtZBhy_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_dAfvO4L0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_nK03YFPf, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lb7niaB7, HV_BINOP_SUBTRACT, 0, m, &cBinop_lb7niaB7_sendMessage);
}

void Heavy_shaping_antiphase::hTable_zBXIaPW2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_antiphase::cSwitchcase_qxBVyhfu_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_rbJvrcb4, 0, m, &cSlice_rbJvrcb4_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_ZDLokTkM_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_YMFoalMF, 0, m, &cSlice_YMFoalMF_sendMessage);
      break;
    }
    default: {
      cMsg_ZosCtV8N_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_antiphase::cDelay_CouNlwYn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_CouNlwYn, m);
  cMsg_ZDLokTkM_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cVar_L126blV9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ASmMQaQ8_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cSlice_YMFoalMF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SHSkGHvV, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_L126blV9, 0, m, &cVar_L126blV9_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_antiphase::cSlice_rbJvrcb4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SHSkGHvV, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_DLgA10kt, HV_BINOP_SUBTRACT, 0, m, &cBinop_DLgA10kt_sendMessage);
      break;
    }
    case 1: {
      cMsg_LUzZnzD9_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_antiphase::cBinop_ZZ6HFV4g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_zRSMWQ6k, HV_BINOP_DIVIDE, 1, m, &cBinop_zRSMWQ6k_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_zRSMWQ6k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_RY1JNCk9_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_CouNlwYn, 1, m, &cDelay_CouNlwYn_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_CouNlwYn, 0, m, &cDelay_CouNlwYn_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_ZosCtV8N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SHSkGHvV, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_DLgA10kt, HV_BINOP_SUBTRACT, 0, m, &cBinop_DLgA10kt_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_c23vatsB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_DLgA10kt, HV_BINOP_SUBTRACT, 1, m, &cBinop_DLgA10kt_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_ASmMQaQ8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_c23vatsB_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_DLgA10kt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_YZx6sEIU_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_YZx6sEIU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_zRSMWQ6k, HV_BINOP_DIVIDE, 0, m, &cBinop_zRSMWQ6k_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_RY1JNCk9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_CouNlwYn, 0, m, &cDelay_CouNlwYn_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_ZDLokTkM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SHSkGHvV, 1, m, NULL);
}

void Heavy_shaping_antiphase::cMsg_Jm45uCNf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_gqUOi8Mz_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_gqUOi8Mz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_ZZ6HFV4g_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_LUzZnzD9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SHSkGHvV, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_DLgA10kt, HV_BINOP_SUBTRACT, 0, m, &cBinop_DLgA10kt_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_y1QMXfpz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_ZqVVsL9O_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_ZqVVsL9O_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_wpTC7L04_sendMessage);
}

void Heavy_shaping_antiphase::cVar_X5nuE080_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_mKi1V1dV_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cSystem_XnxO7mTU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_n1AVCy5L_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_N09yXvo7, m);
}

void Heavy_shaping_antiphase::cBinop_wpTC7L04_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_uQMCIw2K, m);
}

void Heavy_shaping_antiphase::cMsg_mKi1V1dV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_XnxO7mTU_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_n1AVCy5L_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ZyLx5Kcr, m);
}

void Heavy_shaping_antiphase::cMsg_FWf20nxx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_VZ5Epm5o_sendMessage);
}

void Heavy_shaping_antiphase::cSystem_VZ5Epm5o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_47FEbxRW_sendMessage);
}

void Heavy_shaping_antiphase::cDelay_AyxpUdTu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_AyxpUdTu, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_utRgvsYX, 0, m, &cDelay_utRgvsYX_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_AyxpUdTu, 0, m, &cDelay_AyxpUdTu_sendMessage);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Uyn3e8MU, 1, m, NULL);
}

void Heavy_shaping_antiphase::cDelay_utRgvsYX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_utRgvsYX, m);
  cMsg_Cj6VzcvR_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cSwitchcase_EAFI3ABL_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x47BE8354: { // "clear"
      cMsg_du3lz2fS_sendMessage(_c, 0, m);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_shaping_antiphase::cBinop_nFpq1YcW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jhm71FHe_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::hTable_Letgajgb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_2eyarZPi_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_AyxpUdTu, 2, m, &cDelay_AyxpUdTu_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_JQAkCeSj_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_jhm71FHe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "resize");
  msg_setElementToFrom(m, 1, n, 0);
  hTable_onMessage(_c, &Context(_c)->hTable_Letgajgb, 0, m, &hTable_Letgajgb_sendMessage);
}

void Heavy_shaping_antiphase::cBinop_47FEbxRW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 200.0f, 0, m, &cBinop_nFpq1YcW_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_Cj6VzcvR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "mirror");
  hTable_onMessage(_c, &Context(_c)->hTable_Letgajgb, 0, m, &hTable_Letgajgb_sendMessage);
}

void Heavy_shaping_antiphase::cCast_JQAkCeSj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_AyxpUdTu, 0, m, &cDelay_AyxpUdTu_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_2eyarZPi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cDelay_onMessage(_c, &Context(_c)->cDelay_utRgvsYX, 2, m, &cDelay_utRgvsYX_sendMessage);
}

void Heavy_shaping_antiphase::cMsg_du3lz2fS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Uyn3e8MU, 1, m, NULL);
}

void Heavy_shaping_antiphase::cMsg_Fn7Xg5TT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 2.24f);
}

void Heavy_shaping_antiphase::cReceive_wLqBFMbr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_6RzMDb9w, 0, m, &cVar_6RzMDb9w_sendMessage);
  cMsg_5TdifJNd_sendMessage(_c, 0, m);
  cMsg_lerw2eug_sendMessage(_c, 0, m);
  cMsg_LkkFB7F8_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_ingYMZKt, 0, m, &cVar_ingYMZKt_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_iqjn2LzZ, 0, m, &cVar_iqjn2LzZ_sendMessage);
  cMsg_pXkHJKUZ_sendMessage(_c, 0, m);
  cMsg_SuE9lMe7_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_L126blV9, 0, m, &cVar_L126blV9_sendMessage);
  cMsg_Jm45uCNf_sendMessage(_c, 0, m);
  cMsg_ZDLokTkM_sendMessage(_c, 0, m);
  cSwitchcase_m8j8usye_onMessage(_c, NULL, 0, m, NULL);
  cMsg_FWf20nxx_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_X5nuE080, 0, m, &cVar_X5nuE080_sendMessage);
  cMsg_y1QMXfpz_sendMessage(_c, 0, m);
}

void Heavy_shaping_antiphase::cReceive_m2nqZwfk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_z2cI05cG_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_qxBVyhfu_onMessage(_c, NULL, 0, m, NULL);
}



/*
 * Code for expr~ implementation
 * Write out the generic implementation code
 */

 // per class code

 // per object code


/*
 * Context Process Implementation
 */

int Heavy_shaping_antiphase::process(float **inputBuffers, float **outputBuffers, int n) {
  while (hLp_hasData(&inQueue)) {
    hv_uint32_t numBytes = 0;
    ReceiverMessagePair *p = reinterpret_cast<ReceiverMessagePair *>(hLp_getReadBuffer(&inQueue, &numBytes));
    hv_assert(numBytes >= sizeof(ReceiverMessagePair));
    scheduleMessageForReceiver(p->receiverHash, &p->msg);
    hLp_consume(&inQueue);
  }

  sendBangToReceiver(0xDD21C0EB); // send to __hv_bang~ on next cycle
  const int n4 = n & ~HV_N_SIMD_MASK; // ensure that the block size is a multiple of HV_N_SIMD

  // temporary signal vars
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4;
  hv_bufferi_t Bi0, Bi1;

  // input and output vars

  // declare and init the zero buffer
  hv_bufferf_t ZERO; __hv_zero_f(VOf(ZERO));

  hv_uint32_t nextBlock = blockStartTimestamp;
  for (int n = 0; n < n4; n += HV_N_SIMD) {

    // process all of the messages for this block
    nextBlock += HV_N_SIMD;
    while (mq_hasMessageBefore(&mq, nextBlock)) {
      MessageNode *const node = mq_peek(&mq);
      node->sendMessage(this, node->let, node->m);
      mq_pop(&mq);
    }

    

    

    // process all signal functions
    __hv_phasor_k_f(&sPhasor_tw5En2RY, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf3), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf4), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf0), VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_tabwrite_stoppable_f(&sTabwrite_DWBkCHEL, VIf(Bf1));
    __hv_tabhead_f(&sTabhead_IHira7ZX, VOf(Bf3));
    __hv_var_k_f_r(VOf(Bf0), -1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f);
    __hv_add_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_uQMCIw2K, VOf(Bf3));
    __hv_mul_f(VIf(ZERO), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_ZyLx5Kcr, VOf(Bf4));
    __hv_min_f(VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_zero_f(VOf(Bf3));
    __hv_max_f(VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_sub_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_floor_f(VIf(Bf3), VOf(Bf0));
    __hv_varread_f(&sVarf_N09yXvo7, VOf(Bf4));
    __hv_zero_f(VOf(Bf2));
    __hv_lt_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_and_f(VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_add_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_cast_fi(VIf(Bf2), VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 1, 1, 1, 1, 1, 1, 1, 1);
    __hv_add_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_tabread_if(&sTabread_hIkXsKXc, VIi(Bi1), VOf(Bf2));
    __hv_tabread_if(&sTabread_rmdJflzp, VIi(Bi0), VOf(Bf4));
    __hv_sub_f(VIf(Bf2), VIf(Bf4), VOf(Bf2));
    __hv_sub_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf2), VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_tabwrite_stoppable_f(&sTabwrite_nK03YFPf, VIf(Bf4));
    __hv_add_f(VIf(Bf1), VIf(Bf4), VOf(Bf4));
    __hv_tabwrite_stoppable_f(&sTabwrite_SHSkGHvV, VIf(Bf4));
    __hv_tabwrite_f(&sTabwrite_Uyn3e8MU, VIf(Bf1));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_antiphase::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_antiphase::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
