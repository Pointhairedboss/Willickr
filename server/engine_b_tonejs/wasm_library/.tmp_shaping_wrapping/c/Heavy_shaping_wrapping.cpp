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

#include "Heavy_shaping_wrapping.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_wrapping *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_wrapping_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_wrapping));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_wrapping(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_wrapping_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_wrapping));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_wrapping(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_wrapping_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_wrapping();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_wrapping::Heavy_shaping_wrapping(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_FierNd0G, 670.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_TCfmZD0E, &hTable_3QklcXLI);
  numBytes += sTabwrite_init(&sTabwrite_kbEl4u23, &hTable_GjoAqeRn);
  numBytes += hTable_init(&hTable_3QklcXLI, 100);
  numBytes += cDelay_init(this, &cDelay_SJ0gB1yJ, 0.0f);
  numBytes += cVar_init_s(&cVar_iVwfhTXR, "A");
  numBytes += cSlice_init(&cSlice_rWj1TqZe, 1, 1);
  numBytes += cSlice_init(&cSlice_DDajsr7b, 1, 1);
  numBytes += cBinop_init(&cBinop_6H081qgv, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_sbrlGjid, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_YJMnFHSW, 0.0f);
  numBytes += cVar_init_f(&cVar_bxruSGW2, 200.0f);
  numBytes += cBinop_init(&cBinop_DtzaaSvi, 0.0f); // __mul
  numBytes += hTable_init(&hTable_GjoAqeRn, 100);
  numBytes += cDelay_init(this, &cDelay_5aiMAhLk, 0.0f);
  numBytes += cVar_init_s(&cVar_FrSavYkm, "B");
  numBytes += cSlice_init(&cSlice_gcwFR7qH, 1, 1);
  numBytes += cSlice_init(&cSlice_7d3oCMTp, 1, 1);
  numBytes += cBinop_init(&cBinop_0KmvbAr8, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_J8Sw5Xrl, 0.0f); // __sub
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_wrapping::~Heavy_shaping_wrapping() {
  hTable_free(&hTable_3QklcXLI);
  hTable_free(&hTable_GjoAqeRn);
}

HvTable *Heavy_shaping_wrapping::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_3QklcXLI; // A
    case 0xD961DF96: return &hTable_GjoAqeRn; // B
    default: return nullptr;
  }
}

void Heavy_shaping_wrapping::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_ccSMjGO2_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_KGXizcKQ_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_wrapping::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_wrapping::hTable_3QklcXLI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_wrapping::cSwitchcase_F9g5Wy8E_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_DDajsr7b, 0, m, &cSlice_DDajsr7b_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_KGLHLrMX_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_rWj1TqZe, 0, m, &cSlice_rWj1TqZe_sendMessage);
      break;
    }
    default: {
      cMsg_X5eYrenJ_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_wrapping::cDelay_SJ0gB1yJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_SJ0gB1yJ, m);
  cMsg_KGLHLrMX_sendMessage(_c, 0, m);
}

void Heavy_shaping_wrapping::cVar_iVwfhTXR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_aFwgU9x2_sendMessage(_c, 0, m);
}

void Heavy_shaping_wrapping::cSlice_rWj1TqZe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_TCfmZD0E, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_iVwfhTXR, 0, m, &cVar_iVwfhTXR_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_wrapping::cSlice_DDajsr7b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_TCfmZD0E, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_sbrlGjid, HV_BINOP_SUBTRACT, 0, m, &cBinop_sbrlGjid_sendMessage);
      break;
    }
    case 1: {
      cMsg_FBg0xaKm_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_wrapping::cBinop_lhq9dOSM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6H081qgv, HV_BINOP_DIVIDE, 1, m, &cBinop_6H081qgv_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_6H081qgv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_sLxpRxHw_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_SJ0gB1yJ, 1, m, &cDelay_SJ0gB1yJ_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_SJ0gB1yJ, 0, m, &cDelay_SJ0gB1yJ_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_X5eYrenJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_TCfmZD0E, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_sbrlGjid, HV_BINOP_SUBTRACT, 0, m, &cBinop_sbrlGjid_sendMessage);
}

void Heavy_shaping_wrapping::cSystem_wcWf7DpM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sbrlGjid, HV_BINOP_SUBTRACT, 1, m, &cBinop_sbrlGjid_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_aFwgU9x2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_wcWf7DpM_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_sbrlGjid_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_sh2P58S6_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_sh2P58S6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6H081qgv, HV_BINOP_DIVIDE, 0, m, &cBinop_6H081qgv_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_sLxpRxHw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_SJ0gB1yJ, 0, m, &cDelay_SJ0gB1yJ_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_KGLHLrMX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_TCfmZD0E, 1, m, NULL);
}

void Heavy_shaping_wrapping::cMsg_ySXyNRRE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_OkMvjctW_sendMessage);
}

void Heavy_shaping_wrapping::cSystem_OkMvjctW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_lhq9dOSM_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_FBg0xaKm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_TCfmZD0E, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_sbrlGjid, HV_BINOP_SUBTRACT, 0, m, &cBinop_sbrlGjid_sendMessage);
}

void Heavy_shaping_wrapping::cCast_9TinTlOK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_4pnFzDn9_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_wrapping::cSwitchcase_4pnFzDn9_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_TKHjdNg2_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_TKHjdNg2_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_YUhHYvtj_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_wrapping::cDelay_YJMnFHSW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_YJMnFHSW, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_YJMnFHSW, 0, m, &cDelay_YJMnFHSW_sendMessage);
  cSwitchcase_F9g5Wy8E_onMessage(_c, NULL, 0, m, NULL);
  cSend_Xsg6dePe_sendMessage(_c, 0, m);
}

void Heavy_shaping_wrapping::cCast_YUhHYvtj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_TKHjdNg2_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_YJMnFHSW, 0, m, &cDelay_YJMnFHSW_sendMessage);
  cSwitchcase_F9g5Wy8E_onMessage(_c, NULL, 0, m, NULL);
  cSend_Xsg6dePe_sendMessage(_c, 0, m);
}

void Heavy_shaping_wrapping::cMsg_UIDfjPBu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_QsnquvaL_sendMessage);
}

void Heavy_shaping_wrapping::cSystem_QsnquvaL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_N3y0tGbS_sendMessage);
}

void Heavy_shaping_wrapping::cVar_bxruSGW2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_DtzaaSvi, HV_BINOP_MULTIPLY, 0, m, &cBinop_DtzaaSvi_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_TKHjdNg2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_YJMnFHSW, 0, m, &cDelay_YJMnFHSW_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_wekSdVih_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_YJMnFHSW, 2, m, &cDelay_YJMnFHSW_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_N3y0tGbS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_DtzaaSvi, HV_BINOP_MULTIPLY, 1, m, &cBinop_DtzaaSvi_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_DtzaaSvi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_wekSdVih_sendMessage);
}

void Heavy_shaping_wrapping::cSend_Xsg6dePe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_KGXizcKQ_sendMessage(_c, 0, m);
}

void Heavy_shaping_wrapping::hTable_GjoAqeRn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_wrapping::cSwitchcase_Tno1EbYr_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_7d3oCMTp, 0, m, &cSlice_7d3oCMTp_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_MQBooOgD_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_gcwFR7qH, 0, m, &cSlice_gcwFR7qH_sendMessage);
      break;
    }
    default: {
      cMsg_vvXy7tye_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_wrapping::cDelay_5aiMAhLk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_5aiMAhLk, m);
  cMsg_MQBooOgD_sendMessage(_c, 0, m);
}

void Heavy_shaping_wrapping::cVar_FrSavYkm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_8fS7edd7_sendMessage(_c, 0, m);
}

void Heavy_shaping_wrapping::cSlice_gcwFR7qH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_kbEl4u23, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_FrSavYkm, 0, m, &cVar_FrSavYkm_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_wrapping::cSlice_7d3oCMTp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_kbEl4u23, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_J8Sw5Xrl, HV_BINOP_SUBTRACT, 0, m, &cBinop_J8Sw5Xrl_sendMessage);
      break;
    }
    case 1: {
      cMsg_20D7MJYs_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_wrapping::cBinop_rbSA88YS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0KmvbAr8, HV_BINOP_DIVIDE, 1, m, &cBinop_0KmvbAr8_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_0KmvbAr8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Gskz0pNt_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_5aiMAhLk, 1, m, &cDelay_5aiMAhLk_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_5aiMAhLk, 0, m, &cDelay_5aiMAhLk_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_vvXy7tye_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_kbEl4u23, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_J8Sw5Xrl, HV_BINOP_SUBTRACT, 0, m, &cBinop_J8Sw5Xrl_sendMessage);
}

void Heavy_shaping_wrapping::cSystem_oBtGaAH6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_J8Sw5Xrl, HV_BINOP_SUBTRACT, 1, m, &cBinop_J8Sw5Xrl_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_8fS7edd7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oBtGaAH6_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_J8Sw5Xrl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_qFnPtwk7_sendMessage);
}

void Heavy_shaping_wrapping::cBinop_qFnPtwk7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0KmvbAr8, HV_BINOP_DIVIDE, 0, m, &cBinop_0KmvbAr8_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_Gskz0pNt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_5aiMAhLk, 0, m, &cDelay_5aiMAhLk_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_MQBooOgD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_kbEl4u23, 1, m, NULL);
}

void Heavy_shaping_wrapping::cMsg_Zhsji135_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_1Stx8dlK_sendMessage);
}

void Heavy_shaping_wrapping::cSystem_1Stx8dlK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_rbSA88YS_sendMessage);
}

void Heavy_shaping_wrapping::cMsg_20D7MJYs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_kbEl4u23, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_J8Sw5Xrl, HV_BINOP_SUBTRACT, 0, m, &cBinop_J8Sw5Xrl_sendMessage);
}

void Heavy_shaping_wrapping::cReceive_ccSMjGO2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_iVwfhTXR, 0, m, &cVar_iVwfhTXR_sendMessage);
  cMsg_ySXyNRRE_sendMessage(_c, 0, m);
  cMsg_KGLHLrMX_sendMessage(_c, 0, m);
  cMsg_UIDfjPBu_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_bxruSGW2, 0, m, &cVar_bxruSGW2_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_FrSavYkm, 0, m, &cVar_FrSavYkm_sendMessage);
  cMsg_Zhsji135_sendMessage(_c, 0, m);
  cMsg_MQBooOgD_sendMessage(_c, 0, m);
  cSwitchcase_4pnFzDn9_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_wrapping::cReceive_KGXizcKQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_Tno1EbYr_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_wrapping::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1;

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
    __hv_phasor_k_f(&sPhasor_FierNd0G, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_TCfmZD0E, VIf(Bf0));
    __hv_var_k_f(VOf(Bf1), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_floor_f(VIf(Bf1), VOf(Bf0));
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_kbEl4u23, VIf(Bf0));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_wrapping::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_wrapping::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
