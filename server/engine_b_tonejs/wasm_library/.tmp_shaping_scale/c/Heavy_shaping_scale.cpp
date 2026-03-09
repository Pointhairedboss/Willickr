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

#include "Heavy_shaping_scale.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_scale *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_scale_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_scale));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_scale(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_scale_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_scale));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_scale(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_scale_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_scale();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_scale::Heavy_shaping_scale(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_l3lvSd7g, &hTable_BKtkdr3o);
  numBytes += sTabwrite_init(&sTabwrite_h2joczml, &hTable_RzEs5gag);
  numBytes += sPhasor_k_init(&sPhasor_PSFD79zi, 640.0f, sampleRate);
  numBytes += hTable_init(&hTable_BKtkdr3o, 100);
  numBytes += cDelay_init(this, &cDelay_apjhorFX, 0.0f);
  numBytes += cVar_init_s(&cVar_veFQVRD0, "A");
  numBytes += cSlice_init(&cSlice_UYE2CVi2, 1, 1);
  numBytes += cSlice_init(&cSlice_l3ukp85G, 1, 1);
  numBytes += cBinop_init(&cBinop_rL4eeXi5, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_HUYk0fJX, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_T2aEvwZt, 0.0f);
  numBytes += cVar_init_f(&cVar_HxeNwGVX, 200.0f);
  numBytes += cBinop_init(&cBinop_guEAUAhY, 0.0f); // __mul
  numBytes += hTable_init(&hTable_RzEs5gag, 100);
  numBytes += cDelay_init(this, &cDelay_6tyBXYHA, 0.0f);
  numBytes += cVar_init_s(&cVar_qcAY2LZK, "B");
  numBytes += cSlice_init(&cSlice_G3WqOkth, 1, 1);
  numBytes += cSlice_init(&cSlice_4fR39kNt, 1, 1);
  numBytes += cBinop_init(&cBinop_9PDbWciS, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_Kh197dYT, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_08lNsmUZ, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_VSeOgGfg, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_scale::~Heavy_shaping_scale() {
  hTable_free(&hTable_BKtkdr3o);
  hTable_free(&hTable_RzEs5gag);
}

HvTable *Heavy_shaping_scale::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_BKtkdr3o; // A
    case 0xD961DF96: return &hTable_RzEs5gag; // B
    default: return nullptr;
  }
}

void Heavy_shaping_scale::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_mEWN4yVB_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_uRLdBtrD_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_scale::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_scale::hTable_BKtkdr3o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_scale::cSwitchcase_M88sYfVl_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_l3ukp85G, 0, m, &cSlice_l3ukp85G_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_BxbIFJSX_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_UYE2CVi2, 0, m, &cSlice_UYE2CVi2_sendMessage);
      break;
    }
    default: {
      cMsg_bPrkLOYk_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_scale::cDelay_apjhorFX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_apjhorFX, m);
  cMsg_BxbIFJSX_sendMessage(_c, 0, m);
}

void Heavy_shaping_scale::cVar_veFQVRD0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_SVAE04K8_sendMessage(_c, 0, m);
}

void Heavy_shaping_scale::cSlice_UYE2CVi2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_l3lvSd7g, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_veFQVRD0, 0, m, &cVar_veFQVRD0_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_scale::cSlice_l3ukp85G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_l3lvSd7g, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_HUYk0fJX, HV_BINOP_SUBTRACT, 0, m, &cBinop_HUYk0fJX_sendMessage);
      break;
    }
    case 1: {
      cMsg_WJrTA2Kh_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_scale::cBinop_QawBjEU8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_rL4eeXi5, HV_BINOP_DIVIDE, 1, m, &cBinop_rL4eeXi5_sendMessage);
}

void Heavy_shaping_scale::cBinop_rL4eeXi5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_EXv798vv_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_apjhorFX, 1, m, &cDelay_apjhorFX_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_apjhorFX, 0, m, &cDelay_apjhorFX_sendMessage);
}

void Heavy_shaping_scale::cMsg_bPrkLOYk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_l3lvSd7g, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_HUYk0fJX, HV_BINOP_SUBTRACT, 0, m, &cBinop_HUYk0fJX_sendMessage);
}

void Heavy_shaping_scale::cSystem_gOZpQHY5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_HUYk0fJX, HV_BINOP_SUBTRACT, 1, m, &cBinop_HUYk0fJX_sendMessage);
}

void Heavy_shaping_scale::cMsg_SVAE04K8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_gOZpQHY5_sendMessage);
}

void Heavy_shaping_scale::cBinop_HUYk0fJX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Zxci2mSe_sendMessage);
}

void Heavy_shaping_scale::cBinop_Zxci2mSe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_rL4eeXi5, HV_BINOP_DIVIDE, 0, m, &cBinop_rL4eeXi5_sendMessage);
}

void Heavy_shaping_scale::cMsg_EXv798vv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_apjhorFX, 0, m, &cDelay_apjhorFX_sendMessage);
}

void Heavy_shaping_scale::cMsg_BxbIFJSX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_l3lvSd7g, 1, m, NULL);
}

void Heavy_shaping_scale::cMsg_8AlRonzY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_n3wNGA7M_sendMessage);
}

void Heavy_shaping_scale::cSystem_n3wNGA7M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_QawBjEU8_sendMessage);
}

void Heavy_shaping_scale::cMsg_WJrTA2Kh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_l3lvSd7g, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_HUYk0fJX, HV_BINOP_SUBTRACT, 0, m, &cBinop_HUYk0fJX_sendMessage);
}

void Heavy_shaping_scale::cCast_m6FSpWlZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_C3ajnhqx_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_scale::cSwitchcase_C3ajnhqx_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_4Xzn0nlk_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_4Xzn0nlk_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mYF6bgXq_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_scale::cDelay_T2aEvwZt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_T2aEvwZt, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_T2aEvwZt, 0, m, &cDelay_T2aEvwZt_sendMessage);
  cSwitchcase_M88sYfVl_onMessage(_c, NULL, 0, m, NULL);
  cSend_U8hucmZ7_sendMessage(_c, 0, m);
}

void Heavy_shaping_scale::cCast_mYF6bgXq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_4Xzn0nlk_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_T2aEvwZt, 0, m, &cDelay_T2aEvwZt_sendMessage);
  cSwitchcase_M88sYfVl_onMessage(_c, NULL, 0, m, NULL);
  cSend_U8hucmZ7_sendMessage(_c, 0, m);
}

void Heavy_shaping_scale::cMsg_lOLOKoAQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_U4zTWo9L_sendMessage);
}

void Heavy_shaping_scale::cSystem_U4zTWo9L_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_rx3PTrZt_sendMessage);
}

void Heavy_shaping_scale::cVar_HxeNwGVX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_guEAUAhY, HV_BINOP_MULTIPLY, 0, m, &cBinop_guEAUAhY_sendMessage);
}

void Heavy_shaping_scale::cMsg_4Xzn0nlk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_T2aEvwZt, 0, m, &cDelay_T2aEvwZt_sendMessage);
}

void Heavy_shaping_scale::cBinop_yIxmPbea_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_T2aEvwZt, 2, m, &cDelay_T2aEvwZt_sendMessage);
}

void Heavy_shaping_scale::cBinop_rx3PTrZt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_guEAUAhY, HV_BINOP_MULTIPLY, 1, m, &cBinop_guEAUAhY_sendMessage);
}

void Heavy_shaping_scale::cBinop_guEAUAhY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_yIxmPbea_sendMessage);
}

void Heavy_shaping_scale::cSend_U8hucmZ7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_uRLdBtrD_sendMessage(_c, 0, m);
}

void Heavy_shaping_scale::hTable_RzEs5gag_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_scale::cSwitchcase_EKYkXFDS_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_4fR39kNt, 0, m, &cSlice_4fR39kNt_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_6FiqHwB4_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_G3WqOkth, 0, m, &cSlice_G3WqOkth_sendMessage);
      break;
    }
    default: {
      cMsg_IDykBWhn_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_scale::cDelay_6tyBXYHA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_6tyBXYHA, m);
  cMsg_6FiqHwB4_sendMessage(_c, 0, m);
}

void Heavy_shaping_scale::cVar_qcAY2LZK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_SHYLOwks_sendMessage(_c, 0, m);
}

void Heavy_shaping_scale::cSlice_G3WqOkth_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_h2joczml, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_qcAY2LZK, 0, m, &cVar_qcAY2LZK_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_scale::cSlice_4fR39kNt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_h2joczml, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_Kh197dYT, HV_BINOP_SUBTRACT, 0, m, &cBinop_Kh197dYT_sendMessage);
      break;
    }
    case 1: {
      cMsg_HbwEey29_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_scale::cBinop_1O3WAFXX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_9PDbWciS, HV_BINOP_DIVIDE, 1, m, &cBinop_9PDbWciS_sendMessage);
}

void Heavy_shaping_scale::cBinop_9PDbWciS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_UugzFohA_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_6tyBXYHA, 1, m, &cDelay_6tyBXYHA_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_6tyBXYHA, 0, m, &cDelay_6tyBXYHA_sendMessage);
}

void Heavy_shaping_scale::cMsg_IDykBWhn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_h2joczml, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Kh197dYT, HV_BINOP_SUBTRACT, 0, m, &cBinop_Kh197dYT_sendMessage);
}

void Heavy_shaping_scale::cSystem_Z4PtjNsp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Kh197dYT, HV_BINOP_SUBTRACT, 1, m, &cBinop_Kh197dYT_sendMessage);
}

void Heavy_shaping_scale::cMsg_SHYLOwks_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Z4PtjNsp_sendMessage);
}

void Heavy_shaping_scale::cBinop_Kh197dYT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_oHho8WhX_sendMessage);
}

void Heavy_shaping_scale::cBinop_oHho8WhX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_9PDbWciS, HV_BINOP_DIVIDE, 0, m, &cBinop_9PDbWciS_sendMessage);
}

void Heavy_shaping_scale::cMsg_UugzFohA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_6tyBXYHA, 0, m, &cDelay_6tyBXYHA_sendMessage);
}

void Heavy_shaping_scale::cMsg_6FiqHwB4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_h2joczml, 1, m, NULL);
}

void Heavy_shaping_scale::cMsg_VVvJwlX3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_V7ooEsCh_sendMessage);
}

void Heavy_shaping_scale::cSystem_V7ooEsCh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_1O3WAFXX_sendMessage);
}

void Heavy_shaping_scale::cMsg_HbwEey29_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_h2joczml, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Kh197dYT, HV_BINOP_SUBTRACT, 0, m, &cBinop_Kh197dYT_sendMessage);
}

void Heavy_shaping_scale::cReceive_mEWN4yVB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_veFQVRD0, 0, m, &cVar_veFQVRD0_sendMessage);
  cMsg_8AlRonzY_sendMessage(_c, 0, m);
  cMsg_BxbIFJSX_sendMessage(_c, 0, m);
  cMsg_lOLOKoAQ_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_HxeNwGVX, 0, m, &cVar_HxeNwGVX_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_qcAY2LZK, 0, m, &cVar_qcAY2LZK_sendMessage);
  cMsg_VVvJwlX3_sendMessage(_c, 0, m);
  cMsg_6FiqHwB4_sendMessage(_c, 0, m);
  cSwitchcase_C3ajnhqx_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_scale::cReceive_uRLdBtrD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_EKYkXFDS_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_scale::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_08lNsmUZ, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_l3lvSd7g, VIf(Bf0));
    __hv_varread_f(&sVarf_VSeOgGfg, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_h2joczml, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_PSFD79zi, VOf(Bf0));
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
    __hv_varwrite_f(&sVarf_08lNsmUZ, VIf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_f(&sVarf_VSeOgGfg, VIf(Bf3));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_scale::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_scale::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
