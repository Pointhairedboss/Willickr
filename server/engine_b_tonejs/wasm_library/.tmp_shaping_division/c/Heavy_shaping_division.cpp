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

#include "Heavy_shaping_division.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_division *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_division_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_division));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_division(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_division_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_division));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_division(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_division_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_division();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_division::Heavy_shaping_division(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_L3oHnMdf, 1371.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_EG1pq8ZG, &hTable_7wzGNwE9);
  numBytes += sPhasor_k_init(&sPhasor_yfHANcLI, 670.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_fodSLJVl, &hTable_TpDLXU7D);
  numBytes += sTabwrite_init(&sTabwrite_SbQYDNwh, &hTable_45T7hXbE);
  numBytes += hTable_init(&hTable_7wzGNwE9, 100);
  numBytes += cDelay_init(this, &cDelay_nScyR1lV, 0.0f);
  numBytes += cVar_init_s(&cVar_bQBUrccI, "A");
  numBytes += cSlice_init(&cSlice_xTq6PDDm, 1, 1);
  numBytes += cSlice_init(&cSlice_9bLBHTgP, 1, 1);
  numBytes += cBinop_init(&cBinop_vnGzkq8m, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_mGuUv8kf, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_K0aVZBMh, 0.0f);
  numBytes += cVar_init_f(&cVar_nuQAxm4F, 200.0f);
  numBytes += cBinop_init(&cBinop_es73s0KG, 0.0f); // __mul
  numBytes += hTable_init(&hTable_TpDLXU7D, 100);
  numBytes += cDelay_init(this, &cDelay_TZX5XV7c, 0.0f);
  numBytes += cVar_init_s(&cVar_08g0VMp2, "B");
  numBytes += cSlice_init(&cSlice_ek6XMBWG, 1, 1);
  numBytes += cSlice_init(&cSlice_It4EP8c7, 1, 1);
  numBytes += cBinop_init(&cBinop_PiRFDp2N, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_KKx0xyjn, 0.0f); // __sub
  numBytes += hTable_init(&hTable_45T7hXbE, 100);
  numBytes += cDelay_init(this, &cDelay_JxrsaphK, 0.0f);
  numBytes += cVar_init_s(&cVar_fDSoP790, "C");
  numBytes += cSlice_init(&cSlice_nRtzy4SD, 1, 1);
  numBytes += cSlice_init(&cSlice_9wYGsmrf, 1, 1);
  numBytes += cBinop_init(&cBinop_IUBzu7uB, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_w9KBhe63, 0.0f); // __sub
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_division::~Heavy_shaping_division() {
  hTable_free(&hTable_7wzGNwE9);
  hTable_free(&hTable_TpDLXU7D);
  hTable_free(&hTable_45T7hXbE);
}

HvTable *Heavy_shaping_division::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_7wzGNwE9; // A
    case 0xD961DF96: return &hTable_TpDLXU7D; // B
    case 0x7F1A5B02: return &hTable_45T7hXbE; // C
    default: return nullptr;
  }
}

void Heavy_shaping_division::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_mYvheMEJ_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_qBeWyX4E_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_division::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_division::hTable_7wzGNwE9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_division::cSwitchcase_DVv4fTAS_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_9bLBHTgP, 0, m, &cSlice_9bLBHTgP_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_osrVR2sL_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_xTq6PDDm, 0, m, &cSlice_xTq6PDDm_sendMessage);
      break;
    }
    default: {
      cMsg_bNSvEZRM_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_division::cDelay_nScyR1lV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_nScyR1lV, m);
  cMsg_osrVR2sL_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cVar_bQBUrccI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_l8mIVAZH_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cSlice_xTq6PDDm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EG1pq8ZG, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_bQBUrccI, 0, m, &cVar_bQBUrccI_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_division::cSlice_9bLBHTgP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EG1pq8ZG, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_mGuUv8kf, HV_BINOP_SUBTRACT, 0, m, &cBinop_mGuUv8kf_sendMessage);
      break;
    }
    case 1: {
      cMsg_bdqoQ8pN_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_division::cBinop_0Ha6mXzS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vnGzkq8m, HV_BINOP_DIVIDE, 1, m, &cBinop_vnGzkq8m_sendMessage);
}

void Heavy_shaping_division::cBinop_vnGzkq8m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_DAnepnnx_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_nScyR1lV, 1, m, &cDelay_nScyR1lV_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_nScyR1lV, 0, m, &cDelay_nScyR1lV_sendMessage);
}

void Heavy_shaping_division::cMsg_bNSvEZRM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EG1pq8ZG, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_mGuUv8kf, HV_BINOP_SUBTRACT, 0, m, &cBinop_mGuUv8kf_sendMessage);
}

void Heavy_shaping_division::cSystem_W9wzgs8o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mGuUv8kf, HV_BINOP_SUBTRACT, 1, m, &cBinop_mGuUv8kf_sendMessage);
}

void Heavy_shaping_division::cMsg_l8mIVAZH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_W9wzgs8o_sendMessage);
}

void Heavy_shaping_division::cBinop_mGuUv8kf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_SG7b6sK4_sendMessage);
}

void Heavy_shaping_division::cBinop_SG7b6sK4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vnGzkq8m, HV_BINOP_DIVIDE, 0, m, &cBinop_vnGzkq8m_sendMessage);
}

void Heavy_shaping_division::cMsg_DAnepnnx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_nScyR1lV, 0, m, &cDelay_nScyR1lV_sendMessage);
}

void Heavy_shaping_division::cMsg_osrVR2sL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EG1pq8ZG, 1, m, NULL);
}

void Heavy_shaping_division::cMsg_udO0pVp5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Mgz16kIi_sendMessage);
}

void Heavy_shaping_division::cSystem_Mgz16kIi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_0Ha6mXzS_sendMessage);
}

void Heavy_shaping_division::cMsg_bdqoQ8pN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EG1pq8ZG, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_mGuUv8kf, HV_BINOP_SUBTRACT, 0, m, &cBinop_mGuUv8kf_sendMessage);
}

void Heavy_shaping_division::cCast_RXfIe5V8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_UZ8AuaDt_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_division::cSwitchcase_UZ8AuaDt_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_N87979ce_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_N87979ce_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_Rj0pMk9I_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_division::cDelay_K0aVZBMh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_K0aVZBMh, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_K0aVZBMh, 0, m, &cDelay_K0aVZBMh_sendMessage);
  cSwitchcase_DVv4fTAS_onMessage(_c, NULL, 0, m, NULL);
  cSend_zRANnLt9_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cCast_Rj0pMk9I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_N87979ce_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_K0aVZBMh, 0, m, &cDelay_K0aVZBMh_sendMessage);
  cSwitchcase_DVv4fTAS_onMessage(_c, NULL, 0, m, NULL);
  cSend_zRANnLt9_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cMsg_r2p8fSdV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Uywu5qBx_sendMessage);
}

void Heavy_shaping_division::cSystem_Uywu5qBx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_CHuubXX5_sendMessage);
}

void Heavy_shaping_division::cVar_nuQAxm4F_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_es73s0KG, HV_BINOP_MULTIPLY, 0, m, &cBinop_es73s0KG_sendMessage);
}

void Heavy_shaping_division::cMsg_N87979ce_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_K0aVZBMh, 0, m, &cDelay_K0aVZBMh_sendMessage);
}

void Heavy_shaping_division::cBinop_qEydQWUJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_K0aVZBMh, 2, m, &cDelay_K0aVZBMh_sendMessage);
}

void Heavy_shaping_division::cBinop_CHuubXX5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_es73s0KG, HV_BINOP_MULTIPLY, 1, m, &cBinop_es73s0KG_sendMessage);
}

void Heavy_shaping_division::cBinop_es73s0KG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_qEydQWUJ_sendMessage);
}

void Heavy_shaping_division::cSend_zRANnLt9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_qBeWyX4E_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::hTable_TpDLXU7D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_division::cSwitchcase_DZuNh0cq_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_It4EP8c7, 0, m, &cSlice_It4EP8c7_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_q53JcDgU_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_ek6XMBWG, 0, m, &cSlice_ek6XMBWG_sendMessage);
      break;
    }
    default: {
      cMsg_CMzf0yRp_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_division::cDelay_TZX5XV7c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_TZX5XV7c, m);
  cMsg_q53JcDgU_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cVar_08g0VMp2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_n9WtDXw9_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cSlice_ek6XMBWG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_fodSLJVl, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_08g0VMp2, 0, m, &cVar_08g0VMp2_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_division::cSlice_It4EP8c7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_fodSLJVl, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_KKx0xyjn, HV_BINOP_SUBTRACT, 0, m, &cBinop_KKx0xyjn_sendMessage);
      break;
    }
    case 1: {
      cMsg_EfE0oiky_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_division::cBinop_TmOZUJsK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_PiRFDp2N, HV_BINOP_DIVIDE, 1, m, &cBinop_PiRFDp2N_sendMessage);
}

void Heavy_shaping_division::cBinop_PiRFDp2N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_3RVKyboM_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_TZX5XV7c, 1, m, &cDelay_TZX5XV7c_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_TZX5XV7c, 0, m, &cDelay_TZX5XV7c_sendMessage);
}

void Heavy_shaping_division::cMsg_CMzf0yRp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_fodSLJVl, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_KKx0xyjn, HV_BINOP_SUBTRACT, 0, m, &cBinop_KKx0xyjn_sendMessage);
}

void Heavy_shaping_division::cSystem_TOrCvTAI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KKx0xyjn, HV_BINOP_SUBTRACT, 1, m, &cBinop_KKx0xyjn_sendMessage);
}

void Heavy_shaping_division::cMsg_n9WtDXw9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_TOrCvTAI_sendMessage);
}

void Heavy_shaping_division::cBinop_KKx0xyjn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_sm3azfzj_sendMessage);
}

void Heavy_shaping_division::cBinop_sm3azfzj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_PiRFDp2N, HV_BINOP_DIVIDE, 0, m, &cBinop_PiRFDp2N_sendMessage);
}

void Heavy_shaping_division::cMsg_3RVKyboM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_TZX5XV7c, 0, m, &cDelay_TZX5XV7c_sendMessage);
}

void Heavy_shaping_division::cMsg_q53JcDgU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_fodSLJVl, 1, m, NULL);
}

void Heavy_shaping_division::cMsg_IWbEWDVn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_fWdu2H97_sendMessage);
}

void Heavy_shaping_division::cSystem_fWdu2H97_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_TmOZUJsK_sendMessage);
}

void Heavy_shaping_division::cMsg_EfE0oiky_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_fodSLJVl, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_KKx0xyjn, HV_BINOP_SUBTRACT, 0, m, &cBinop_KKx0xyjn_sendMessage);
}

void Heavy_shaping_division::hTable_45T7hXbE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_division::cSwitchcase_d7DJxcG6_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_9wYGsmrf, 0, m, &cSlice_9wYGsmrf_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_IjBEeNOH_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_nRtzy4SD, 0, m, &cSlice_nRtzy4SD_sendMessage);
      break;
    }
    default: {
      cMsg_INyVXtbc_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_division::cDelay_JxrsaphK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_JxrsaphK, m);
  cMsg_IjBEeNOH_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cVar_fDSoP790_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_sYeTpzB1_sendMessage(_c, 0, m);
}

void Heavy_shaping_division::cSlice_nRtzy4SD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SbQYDNwh, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_fDSoP790, 0, m, &cVar_fDSoP790_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_division::cSlice_9wYGsmrf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SbQYDNwh, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_w9KBhe63, HV_BINOP_SUBTRACT, 0, m, &cBinop_w9KBhe63_sendMessage);
      break;
    }
    case 1: {
      cMsg_ebfbEHiV_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_division::cBinop_iqEqH7RD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_IUBzu7uB, HV_BINOP_DIVIDE, 1, m, &cBinop_IUBzu7uB_sendMessage);
}

void Heavy_shaping_division::cBinop_IUBzu7uB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_faFO4PzY_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_JxrsaphK, 1, m, &cDelay_JxrsaphK_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_JxrsaphK, 0, m, &cDelay_JxrsaphK_sendMessage);
}

void Heavy_shaping_division::cMsg_INyVXtbc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SbQYDNwh, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_w9KBhe63, HV_BINOP_SUBTRACT, 0, m, &cBinop_w9KBhe63_sendMessage);
}

void Heavy_shaping_division::cSystem_XYctH0SU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_w9KBhe63, HV_BINOP_SUBTRACT, 1, m, &cBinop_w9KBhe63_sendMessage);
}

void Heavy_shaping_division::cMsg_sYeTpzB1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_XYctH0SU_sendMessage);
}

void Heavy_shaping_division::cBinop_w9KBhe63_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_TGAMnrTF_sendMessage);
}

void Heavy_shaping_division::cBinop_TGAMnrTF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_IUBzu7uB, HV_BINOP_DIVIDE, 0, m, &cBinop_IUBzu7uB_sendMessage);
}

void Heavy_shaping_division::cMsg_faFO4PzY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_JxrsaphK, 0, m, &cDelay_JxrsaphK_sendMessage);
}

void Heavy_shaping_division::cMsg_IjBEeNOH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SbQYDNwh, 1, m, NULL);
}

void Heavy_shaping_division::cMsg_3ctNdMtR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_tAZ7gF3z_sendMessage);
}

void Heavy_shaping_division::cSystem_tAZ7gF3z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_iqEqH7RD_sendMessage);
}

void Heavy_shaping_division::cMsg_ebfbEHiV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_SbQYDNwh, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_w9KBhe63, HV_BINOP_SUBTRACT, 0, m, &cBinop_w9KBhe63_sendMessage);
}

void Heavy_shaping_division::cMsg_FHmpkV0L_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_yfHANcLI, 1, m);
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_L3oHnMdf, 1, m);
}

void Heavy_shaping_division::cReceive_mYvheMEJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_bQBUrccI, 0, m, &cVar_bQBUrccI_sendMessage);
  cMsg_udO0pVp5_sendMessage(_c, 0, m);
  cMsg_osrVR2sL_sendMessage(_c, 0, m);
  cMsg_r2p8fSdV_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_nuQAxm4F, 0, m, &cVar_nuQAxm4F_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_08g0VMp2, 0, m, &cVar_08g0VMp2_sendMessage);
  cMsg_IWbEWDVn_sendMessage(_c, 0, m);
  cMsg_q53JcDgU_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_fDSoP790, 0, m, &cVar_fDSoP790_sendMessage);
  cMsg_3ctNdMtR_sendMessage(_c, 0, m);
  cMsg_IjBEeNOH_sendMessage(_c, 0, m);
  cSwitchcase_UZ8AuaDt_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_division::cReceive_qBeWyX4E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_DZuNh0cq_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_d7DJxcG6_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_division::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5;

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
    __hv_phasor_k_f(&sPhasor_L3oHnMdf, VOf(Bf0));
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
    __hv_var_k_f(VOf(Bf3), 0.49f, 0.49f, 0.49f, 0.49f, 0.49f, 0.49f, 0.49f, 0.49f);
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_fma_f(VIf(Bf1), VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_EG1pq8ZG, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_yfHANcLI, VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf5), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf4), VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf3), VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 0.49f, 0.49f, 0.49f, 0.49f, 0.49f, 0.49f, 0.49f, 0.49f);
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_fma_f(VIf(Bf1), VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_tabwrite_stoppable_f(&sTabwrite_fodSLJVl, VIf(Bf3));
    __hv_div_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf3), 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f);
    __hv_mul_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_tabwrite_stoppable_f(&sTabwrite_SbQYDNwh, VIf(Bf3));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_division::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_division::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
