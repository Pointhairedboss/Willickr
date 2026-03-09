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

#include "Heavy_engine001.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_engine001 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_engine001_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_engine001));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_engine001(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_engine001_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_engine001));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_engine001(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_engine001_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_engine001();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_engine001::Heavy_engine001(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_hl86fsLb, 0.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_YjAfboUp, &hTable_ZpweBxzN);
  numBytes += sTabwrite_init(&sTabwrite_36FSP8kv, &hTable_bzGz0ns5);
  numBytes += hTable_init(&hTable_ZpweBxzN, 100);
  numBytes += cDelay_init(this, &cDelay_TKUzT7rN, 0.0f);
  numBytes += cVar_init_s(&cVar_4YOMvOxh, "A");
  numBytes += cSlice_init(&cSlice_zPe7Mmqc, 1, 1);
  numBytes += cSlice_init(&cSlice_JMOCBOM8, 1, 1);
  numBytes += cBinop_init(&cBinop_JpPq9aLM, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_MzFd42hq, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_ClBLURpb, 0.0f);
  numBytes += cVar_init_f(&cVar_lLr76hED, 200.0f);
  numBytes += cBinop_init(&cBinop_1yghyHTD, 0.0f); // __mul
  numBytes += hTable_init(&hTable_bzGz0ns5, 100);
  numBytes += cDelay_init(this, &cDelay_LLh93VqV, 0.0f);
  numBytes += cVar_init_s(&cVar_2K2LYfgf, "B");
  numBytes += cSlice_init(&cSlice_IctiKfRe, 1, 1);
  numBytes += cSlice_init(&cSlice_urVxCrDe, 1, 1);
  numBytes += cBinop_init(&cBinop_qvAhOCUF, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_S2pQ6Whf, 0.0f); // __sub
  numBytes += cVar_init_f(&cVar_9JI9eEg5, 0.0f);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_engine001::~Heavy_engine001() {
  hTable_free(&hTable_ZpweBxzN);
  hTable_free(&hTable_bzGz0ns5);
}

HvTable *Heavy_engine001::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_ZpweBxzN; // A
    case 0xD961DF96: return &hTable_bzGz0ns5; // B
    default: return nullptr;
  }
}

void Heavy_engine001::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_AqOYTY95_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_xMsqjdRF_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_engine001::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_engine001::hTable_ZpweBxzN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_engine001::cSwitchcase_eXrXauuD_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_JMOCBOM8, 0, m, &cSlice_JMOCBOM8_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_iEpsEW5P_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_zPe7Mmqc, 0, m, &cSlice_zPe7Mmqc_sendMessage);
      break;
    }
    default: {
      cMsg_EnZAjazE_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_engine001::cDelay_TKUzT7rN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_TKUzT7rN, m);
  cMsg_iEpsEW5P_sendMessage(_c, 0, m);
}

void Heavy_engine001::cVar_4YOMvOxh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_K0iiE0He_sendMessage(_c, 0, m);
}

void Heavy_engine001::cSlice_zPe7Mmqc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YjAfboUp, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_4YOMvOxh, 0, m, &cVar_4YOMvOxh_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_engine001::cSlice_JMOCBOM8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YjAfboUp, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_MzFd42hq, HV_BINOP_SUBTRACT, 0, m, &cBinop_MzFd42hq_sendMessage);
      break;
    }
    case 1: {
      cMsg_E0n6oXEP_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_engine001::cBinop_7W6GDSnQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JpPq9aLM, HV_BINOP_DIVIDE, 1, m, &cBinop_JpPq9aLM_sendMessage);
}

void Heavy_engine001::cBinop_JpPq9aLM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_azVDFt31_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_TKUzT7rN, 1, m, &cDelay_TKUzT7rN_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_TKUzT7rN, 0, m, &cDelay_TKUzT7rN_sendMessage);
}

void Heavy_engine001::cMsg_EnZAjazE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YjAfboUp, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_MzFd42hq, HV_BINOP_SUBTRACT, 0, m, &cBinop_MzFd42hq_sendMessage);
}

void Heavy_engine001::cSystem_Ow5tONNj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MzFd42hq, HV_BINOP_SUBTRACT, 1, m, &cBinop_MzFd42hq_sendMessage);
}

void Heavy_engine001::cMsg_K0iiE0He_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Ow5tONNj_sendMessage);
}

void Heavy_engine001::cBinop_MzFd42hq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_7muUNmae_sendMessage);
}

void Heavy_engine001::cBinop_7muUNmae_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JpPq9aLM, HV_BINOP_DIVIDE, 0, m, &cBinop_JpPq9aLM_sendMessage);
}

void Heavy_engine001::cMsg_azVDFt31_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_TKUzT7rN, 0, m, &cDelay_TKUzT7rN_sendMessage);
}

void Heavy_engine001::cMsg_iEpsEW5P_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YjAfboUp, 1, m, NULL);
}

void Heavy_engine001::cMsg_BTWsLS5K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_GhJ0Vut3_sendMessage);
}

void Heavy_engine001::cSystem_GhJ0Vut3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_7W6GDSnQ_sendMessage);
}

void Heavy_engine001::cMsg_E0n6oXEP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YjAfboUp, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_MzFd42hq, HV_BINOP_SUBTRACT, 0, m, &cBinop_MzFd42hq_sendMessage);
}

void Heavy_engine001::cCast_YakH2wmK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_CUlO9YyT_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_engine001::cSwitchcase_CUlO9YyT_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_dHxWzgYE_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_dHxWzgYE_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_waoK0naR_sendMessage);
      break;
    }
  }
}

void Heavy_engine001::cDelay_ClBLURpb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_ClBLURpb, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_ClBLURpb, 0, m, &cDelay_ClBLURpb_sendMessage);
  cSwitchcase_eXrXauuD_onMessage(_c, NULL, 0, m, NULL);
  cSend_AG1Q1XY7_sendMessage(_c, 0, m);
}

void Heavy_engine001::cCast_waoK0naR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_dHxWzgYE_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_ClBLURpb, 0, m, &cDelay_ClBLURpb_sendMessage);
  cSwitchcase_eXrXauuD_onMessage(_c, NULL, 0, m, NULL);
  cSend_AG1Q1XY7_sendMessage(_c, 0, m);
}

void Heavy_engine001::cMsg_34BMo2O2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Ivim4OYt_sendMessage);
}

void Heavy_engine001::cSystem_Ivim4OYt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_eSVIQ549_sendMessage);
}

void Heavy_engine001::cVar_lLr76hED_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_1yghyHTD, HV_BINOP_MULTIPLY, 0, m, &cBinop_1yghyHTD_sendMessage);
}

void Heavy_engine001::cMsg_dHxWzgYE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_ClBLURpb, 0, m, &cDelay_ClBLURpb_sendMessage);
}

void Heavy_engine001::cBinop_sdfFFWpC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_ClBLURpb, 2, m, &cDelay_ClBLURpb_sendMessage);
}

void Heavy_engine001::cBinop_eSVIQ549_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_1yghyHTD, HV_BINOP_MULTIPLY, 1, m, &cBinop_1yghyHTD_sendMessage);
}

void Heavy_engine001::cBinop_1yghyHTD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_sdfFFWpC_sendMessage);
}

void Heavy_engine001::cSend_AG1Q1XY7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_xMsqjdRF_sendMessage(_c, 0, m);
}

void Heavy_engine001::hTable_bzGz0ns5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_engine001::cSwitchcase_YfNuxGyr_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_urVxCrDe, 0, m, &cSlice_urVxCrDe_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_ntGpbrKW_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_IctiKfRe, 0, m, &cSlice_IctiKfRe_sendMessage);
      break;
    }
    default: {
      cMsg_tT7aN9E8_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_engine001::cDelay_LLh93VqV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_LLh93VqV, m);
  cMsg_ntGpbrKW_sendMessage(_c, 0, m);
}

void Heavy_engine001::cVar_2K2LYfgf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_yecQvNlp_sendMessage(_c, 0, m);
}

void Heavy_engine001::cSlice_IctiKfRe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_36FSP8kv, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_2K2LYfgf, 0, m, &cVar_2K2LYfgf_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_engine001::cSlice_urVxCrDe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_36FSP8kv, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_S2pQ6Whf, HV_BINOP_SUBTRACT, 0, m, &cBinop_S2pQ6Whf_sendMessage);
      break;
    }
    case 1: {
      cMsg_WDotHt2g_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_engine001::cBinop_iyyDXHeN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_qvAhOCUF, HV_BINOP_DIVIDE, 1, m, &cBinop_qvAhOCUF_sendMessage);
}

void Heavy_engine001::cBinop_qvAhOCUF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_geL2lfyv_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LLh93VqV, 1, m, &cDelay_LLh93VqV_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LLh93VqV, 0, m, &cDelay_LLh93VqV_sendMessage);
}

void Heavy_engine001::cMsg_tT7aN9E8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_36FSP8kv, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_S2pQ6Whf, HV_BINOP_SUBTRACT, 0, m, &cBinop_S2pQ6Whf_sendMessage);
}

void Heavy_engine001::cSystem_dS11NMcb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_S2pQ6Whf, HV_BINOP_SUBTRACT, 1, m, &cBinop_S2pQ6Whf_sendMessage);
}

void Heavy_engine001::cMsg_yecQvNlp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_dS11NMcb_sendMessage);
}

void Heavy_engine001::cBinop_S2pQ6Whf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_49WjPTxe_sendMessage);
}

void Heavy_engine001::cBinop_49WjPTxe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_qvAhOCUF, HV_BINOP_DIVIDE, 0, m, &cBinop_qvAhOCUF_sendMessage);
}

void Heavy_engine001::cMsg_geL2lfyv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_LLh93VqV, 0, m, &cDelay_LLh93VqV_sendMessage);
}

void Heavy_engine001::cMsg_ntGpbrKW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_36FSP8kv, 1, m, NULL);
}

void Heavy_engine001::cMsg_zh5phfib_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_KDKlDp6v_sendMessage);
}

void Heavy_engine001::cSystem_KDKlDp6v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_iyyDXHeN_sendMessage);
}

void Heavy_engine001::cMsg_WDotHt2g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_36FSP8kv, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_S2pQ6Whf, HV_BINOP_SUBTRACT, 0, m, &cBinop_S2pQ6Whf_sendMessage);
}

void Heavy_engine001::cVar_9JI9eEg5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 700.0f, 0, m, &cBinop_810FpEDx_sendMessage);
}

void Heavy_engine001::cBinop_810FpEDx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_hl86fsLb, 0, m);
}

void Heavy_engine001::cReceive_AqOYTY95_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_4YOMvOxh, 0, m, &cVar_4YOMvOxh_sendMessage);
  cMsg_BTWsLS5K_sendMessage(_c, 0, m);
  cMsg_iEpsEW5P_sendMessage(_c, 0, m);
  cMsg_34BMo2O2_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_lLr76hED, 0, m, &cVar_lLr76hED_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_2K2LYfgf, 0, m, &cVar_2K2LYfgf_sendMessage);
  cMsg_zh5phfib_sendMessage(_c, 0, m);
  cMsg_ntGpbrKW_sendMessage(_c, 0, m);
  cSwitchcase_CUlO9YyT_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_engine001::cReceive_xMsqjdRF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_YfNuxGyr_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_engine001::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3;

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
    __hv_phasor_k_f(&sPhasor_hl86fsLb, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_zero_f(VOf(Bf2));
    __hv_max_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), -4.0f, -4.0f, -4.0f, -4.0f, -4.0f, -4.0f, -4.0f, -4.0f);
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_fma_f(VIf(Bf0), VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_tabwrite_stoppable_f(&sTabwrite_YjAfboUp, VIf(Bf2));
    __hv_var_k_f(VOf(Bf2), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_min_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_max_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), -4.0f, -4.0f, -4.0f, -4.0f, -4.0f, -4.0f, -4.0f, -4.0f);
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_fma_f(VIf(Bf1), VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_tabwrite_stoppable_f(&sTabwrite_36FSP8kv, VIf(Bf2));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_engine001::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_engine001::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
