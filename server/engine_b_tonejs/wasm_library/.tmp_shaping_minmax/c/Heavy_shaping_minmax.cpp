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

#include "Heavy_shaping_minmax.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_minmax *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_minmax_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_minmax));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_minmax(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_minmax_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_minmax));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_minmax(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_minmax_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_minmax();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_minmax::Heavy_shaping_minmax(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_9BWh6mRm, &hTable_zRgtrRFe);
  numBytes += sTabwrite_init(&sTabwrite_tcZTL4kw, &hTable_0wJkfi7m);
  numBytes += sPhasor_k_init(&sPhasor_iGxycpBm, 640.0f, sampleRate);
  numBytes += hTable_init(&hTable_zRgtrRFe, 100);
  numBytes += cDelay_init(this, &cDelay_OqNQHyjn, 0.0f);
  numBytes += cVar_init_s(&cVar_NG42awh6, "A");
  numBytes += cSlice_init(&cSlice_yUStepZk, 1, 1);
  numBytes += cSlice_init(&cSlice_jvpwvXuJ, 1, 1);
  numBytes += cBinop_init(&cBinop_jesNHJvD, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_Lw3Qz9S4, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_eEowUXGD, 0.0f);
  numBytes += cVar_init_f(&cVar_3HXsJROJ, 200.0f);
  numBytes += cBinop_init(&cBinop_ADvNjijF, 0.0f); // __mul
  numBytes += hTable_init(&hTable_0wJkfi7m, 100);
  numBytes += cDelay_init(this, &cDelay_aFkJg6kC, 0.0f);
  numBytes += cVar_init_s(&cVar_iT7Bd6qM, "B");
  numBytes += cSlice_init(&cSlice_iCeIPI9o, 1, 1);
  numBytes += cSlice_init(&cSlice_6FkNmg20, 1, 1);
  numBytes += cBinop_init(&cBinop_ufbFxF3I, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_o9xNF5Wo, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_FEQOBaS1, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_DKuS3nQZ, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_minmax::~Heavy_shaping_minmax() {
  hTable_free(&hTable_zRgtrRFe);
  hTable_free(&hTable_0wJkfi7m);
}

HvTable *Heavy_shaping_minmax::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_zRgtrRFe; // A
    case 0xD961DF96: return &hTable_0wJkfi7m; // B
    default: return nullptr;
  }
}

void Heavy_shaping_minmax::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_Bn3FxGBI_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_xdvVulS7_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_minmax::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_minmax::hTable_zRgtrRFe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_minmax::cSwitchcase_vfHT71x5_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_jvpwvXuJ, 0, m, &cSlice_jvpwvXuJ_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_Ew4LyEmp_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_yUStepZk, 0, m, &cSlice_yUStepZk_sendMessage);
      break;
    }
    default: {
      cMsg_PWh0gHXD_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_minmax::cDelay_OqNQHyjn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_OqNQHyjn, m);
  cMsg_Ew4LyEmp_sendMessage(_c, 0, m);
}

void Heavy_shaping_minmax::cVar_NG42awh6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_A8pBAU9d_sendMessage(_c, 0, m);
}

void Heavy_shaping_minmax::cSlice_yUStepZk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9BWh6mRm, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_NG42awh6, 0, m, &cVar_NG42awh6_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_minmax::cSlice_jvpwvXuJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9BWh6mRm, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_Lw3Qz9S4, HV_BINOP_SUBTRACT, 0, m, &cBinop_Lw3Qz9S4_sendMessage);
      break;
    }
    case 1: {
      cMsg_gseBLFvM_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_minmax::cBinop_gjLQuAb9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jesNHJvD, HV_BINOP_DIVIDE, 1, m, &cBinop_jesNHJvD_sendMessage);
}

void Heavy_shaping_minmax::cBinop_jesNHJvD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ef7hivBn_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_OqNQHyjn, 1, m, &cDelay_OqNQHyjn_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_OqNQHyjn, 0, m, &cDelay_OqNQHyjn_sendMessage);
}

void Heavy_shaping_minmax::cMsg_PWh0gHXD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9BWh6mRm, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Lw3Qz9S4, HV_BINOP_SUBTRACT, 0, m, &cBinop_Lw3Qz9S4_sendMessage);
}

void Heavy_shaping_minmax::cSystem_vZmtieSt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Lw3Qz9S4, HV_BINOP_SUBTRACT, 1, m, &cBinop_Lw3Qz9S4_sendMessage);
}

void Heavy_shaping_minmax::cMsg_A8pBAU9d_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_vZmtieSt_sendMessage);
}

void Heavy_shaping_minmax::cBinop_Lw3Qz9S4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_GtGDv4w4_sendMessage);
}

void Heavy_shaping_minmax::cBinop_GtGDv4w4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jesNHJvD, HV_BINOP_DIVIDE, 0, m, &cBinop_jesNHJvD_sendMessage);
}

void Heavy_shaping_minmax::cMsg_ef7hivBn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_OqNQHyjn, 0, m, &cDelay_OqNQHyjn_sendMessage);
}

void Heavy_shaping_minmax::cMsg_Ew4LyEmp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9BWh6mRm, 1, m, NULL);
}

void Heavy_shaping_minmax::cMsg_J9ow7ZDr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_L6AIDGvF_sendMessage);
}

void Heavy_shaping_minmax::cSystem_L6AIDGvF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_gjLQuAb9_sendMessage);
}

void Heavy_shaping_minmax::cMsg_gseBLFvM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9BWh6mRm, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Lw3Qz9S4, HV_BINOP_SUBTRACT, 0, m, &cBinop_Lw3Qz9S4_sendMessage);
}

void Heavy_shaping_minmax::cCast_n1BkASix_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_hzxxVjuc_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_minmax::cSwitchcase_hzxxVjuc_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_chwSCauL_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_chwSCauL_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MVjAPUvZ_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_minmax::cDelay_eEowUXGD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_eEowUXGD, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_eEowUXGD, 0, m, &cDelay_eEowUXGD_sendMessage);
  cSwitchcase_vfHT71x5_onMessage(_c, NULL, 0, m, NULL);
  cSend_EOJrUMh0_sendMessage(_c, 0, m);
}

void Heavy_shaping_minmax::cCast_MVjAPUvZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_chwSCauL_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_eEowUXGD, 0, m, &cDelay_eEowUXGD_sendMessage);
  cSwitchcase_vfHT71x5_onMessage(_c, NULL, 0, m, NULL);
  cSend_EOJrUMh0_sendMessage(_c, 0, m);
}

void Heavy_shaping_minmax::cMsg_e1Oszhj1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_MK7PUN6B_sendMessage);
}

void Heavy_shaping_minmax::cSystem_MK7PUN6B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_McKoLDQp_sendMessage);
}

void Heavy_shaping_minmax::cVar_3HXsJROJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ADvNjijF, HV_BINOP_MULTIPLY, 0, m, &cBinop_ADvNjijF_sendMessage);
}

void Heavy_shaping_minmax::cMsg_chwSCauL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_eEowUXGD, 0, m, &cDelay_eEowUXGD_sendMessage);
}

void Heavy_shaping_minmax::cBinop_1fneS8rT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_eEowUXGD, 2, m, &cDelay_eEowUXGD_sendMessage);
}

void Heavy_shaping_minmax::cBinop_McKoLDQp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ADvNjijF, HV_BINOP_MULTIPLY, 1, m, &cBinop_ADvNjijF_sendMessage);
}

void Heavy_shaping_minmax::cBinop_ADvNjijF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_1fneS8rT_sendMessage);
}

void Heavy_shaping_minmax::cSend_EOJrUMh0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_xdvVulS7_sendMessage(_c, 0, m);
}

void Heavy_shaping_minmax::hTable_0wJkfi7m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_minmax::cSwitchcase_DSmaujap_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_6FkNmg20, 0, m, &cSlice_6FkNmg20_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_7KLdRNcE_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_iCeIPI9o, 0, m, &cSlice_iCeIPI9o_sendMessage);
      break;
    }
    default: {
      cMsg_ryzfrCRa_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_minmax::cDelay_aFkJg6kC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_aFkJg6kC, m);
  cMsg_7KLdRNcE_sendMessage(_c, 0, m);
}

void Heavy_shaping_minmax::cVar_iT7Bd6qM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jUnGEw9P_sendMessage(_c, 0, m);
}

void Heavy_shaping_minmax::cSlice_iCeIPI9o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_tcZTL4kw, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_iT7Bd6qM, 0, m, &cVar_iT7Bd6qM_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_minmax::cSlice_6FkNmg20_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_tcZTL4kw, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_o9xNF5Wo, HV_BINOP_SUBTRACT, 0, m, &cBinop_o9xNF5Wo_sendMessage);
      break;
    }
    case 1: {
      cMsg_K9AvwhVh_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_minmax::cBinop_qrTYYS65_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ufbFxF3I, HV_BINOP_DIVIDE, 1, m, &cBinop_ufbFxF3I_sendMessage);
}

void Heavy_shaping_minmax::cBinop_ufbFxF3I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_cgh00ws1_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_aFkJg6kC, 1, m, &cDelay_aFkJg6kC_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_aFkJg6kC, 0, m, &cDelay_aFkJg6kC_sendMessage);
}

void Heavy_shaping_minmax::cMsg_ryzfrCRa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_tcZTL4kw, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_o9xNF5Wo, HV_BINOP_SUBTRACT, 0, m, &cBinop_o9xNF5Wo_sendMessage);
}

void Heavy_shaping_minmax::cSystem_lNHZ8Soe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_o9xNF5Wo, HV_BINOP_SUBTRACT, 1, m, &cBinop_o9xNF5Wo_sendMessage);
}

void Heavy_shaping_minmax::cMsg_jUnGEw9P_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_lNHZ8Soe_sendMessage);
}

void Heavy_shaping_minmax::cBinop_o9xNF5Wo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_6b4gHhp9_sendMessage);
}

void Heavy_shaping_minmax::cBinop_6b4gHhp9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ufbFxF3I, HV_BINOP_DIVIDE, 0, m, &cBinop_ufbFxF3I_sendMessage);
}

void Heavy_shaping_minmax::cMsg_cgh00ws1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_aFkJg6kC, 0, m, &cDelay_aFkJg6kC_sendMessage);
}

void Heavy_shaping_minmax::cMsg_7KLdRNcE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_tcZTL4kw, 1, m, NULL);
}

void Heavy_shaping_minmax::cMsg_FLGmOMtD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Hai640cq_sendMessage);
}

void Heavy_shaping_minmax::cSystem_Hai640cq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_qrTYYS65_sendMessage);
}

void Heavy_shaping_minmax::cMsg_K9AvwhVh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_tcZTL4kw, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_o9xNF5Wo, HV_BINOP_SUBTRACT, 0, m, &cBinop_o9xNF5Wo_sendMessage);
}

void Heavy_shaping_minmax::cReceive_Bn3FxGBI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_NG42awh6, 0, m, &cVar_NG42awh6_sendMessage);
  cMsg_J9ow7ZDr_sendMessage(_c, 0, m);
  cMsg_Ew4LyEmp_sendMessage(_c, 0, m);
  cMsg_e1Oszhj1_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_3HXsJROJ, 0, m, &cVar_3HXsJROJ_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_iT7Bd6qM, 0, m, &cVar_iT7Bd6qM_sendMessage);
  cMsg_FLGmOMtD_sendMessage(_c, 0, m);
  cMsg_7KLdRNcE_sendMessage(_c, 0, m);
  cSwitchcase_hzxxVjuc_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_minmax::cReceive_xdvVulS7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_DSmaujap_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_minmax::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_FEQOBaS1, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_9BWh6mRm, VIf(Bf0));
    __hv_varread_f(&sVarf_DKuS3nQZ, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_tcZTL4kw, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_iGxycpBm, VOf(Bf0));
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
    __hv_zero_f(VOf(Bf3));
    __hv_min_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_f(&sVarf_FEQOBaS1, VIf(Bf3));
    __hv_zero_f(VOf(Bf3));
    __hv_max_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_f(&sVarf_DKuS3nQZ, VIf(Bf3));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_minmax::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_minmax::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
