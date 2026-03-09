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

#include "Heavy_shaping_shift.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_shift *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_shift_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_shift));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_shift(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_shift_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_shift));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_shift(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_shift_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_shift();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_shift::Heavy_shaping_shift(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_hQbqFoKd, &hTable_ZC5SMNV5);
  numBytes += sTabwrite_init(&sTabwrite_HuVX7t2f, &hTable_AfS0zmEk);
  numBytes += sPhasor_k_init(&sPhasor_0Wuq8x0a, 640.0f, sampleRate);
  numBytes += hTable_init(&hTable_ZC5SMNV5, 100);
  numBytes += cDelay_init(this, &cDelay_4ihzedU0, 0.0f);
  numBytes += cVar_init_s(&cVar_1tJ2QfoU, "A");
  numBytes += cSlice_init(&cSlice_QvnCfSJv, 1, 1);
  numBytes += cSlice_init(&cSlice_J6R2TWG0, 1, 1);
  numBytes += cBinop_init(&cBinop_oJXM0mLX, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_3IvKRgmP, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_0DdJPKkH, 0.0f);
  numBytes += cVar_init_f(&cVar_iQjbTzqt, 200.0f);
  numBytes += cBinop_init(&cBinop_g12Mgfku, 0.0f); // __mul
  numBytes += hTable_init(&hTable_AfS0zmEk, 100);
  numBytes += cDelay_init(this, &cDelay_Y9Cwq3AV, 0.0f);
  numBytes += cVar_init_s(&cVar_VIWEBpMv, "B");
  numBytes += cSlice_init(&cSlice_Q96rdGG8, 1, 1);
  numBytes += cSlice_init(&cSlice_Toe3GEg4, 1, 1);
  numBytes += cBinop_init(&cBinop_ZgI2PN54, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_uGdpHnqi, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_WhOvrml8, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_ybMfaxwA, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_shift::~Heavy_shaping_shift() {
  hTable_free(&hTable_ZC5SMNV5);
  hTable_free(&hTable_AfS0zmEk);
}

HvTable *Heavy_shaping_shift::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_ZC5SMNV5; // A
    case 0xD961DF96: return &hTable_AfS0zmEk; // B
    default: return nullptr;
  }
}

void Heavy_shaping_shift::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_ODNuj8ml_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_xJXx7zLM_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_shift::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_shift::hTable_ZC5SMNV5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_shift::cSwitchcase_1RiKpKGP_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_J6R2TWG0, 0, m, &cSlice_J6R2TWG0_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_Kv9Kz00H_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_QvnCfSJv, 0, m, &cSlice_QvnCfSJv_sendMessage);
      break;
    }
    default: {
      cMsg_UYZ9efGm_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_shift::cDelay_4ihzedU0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_4ihzedU0, m);
  cMsg_Kv9Kz00H_sendMessage(_c, 0, m);
}

void Heavy_shaping_shift::cVar_1tJ2QfoU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_p0GQ5C4G_sendMessage(_c, 0, m);
}

void Heavy_shaping_shift::cSlice_QvnCfSJv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_hQbqFoKd, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_1tJ2QfoU, 0, m, &cVar_1tJ2QfoU_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_shift::cSlice_J6R2TWG0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_hQbqFoKd, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_3IvKRgmP, HV_BINOP_SUBTRACT, 0, m, &cBinop_3IvKRgmP_sendMessage);
      break;
    }
    case 1: {
      cMsg_D04NunoV_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_shift::cBinop_7a5Id9qJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_oJXM0mLX, HV_BINOP_DIVIDE, 1, m, &cBinop_oJXM0mLX_sendMessage);
}

void Heavy_shaping_shift::cBinop_oJXM0mLX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_97Xs8FJl_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_4ihzedU0, 1, m, &cDelay_4ihzedU0_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_4ihzedU0, 0, m, &cDelay_4ihzedU0_sendMessage);
}

void Heavy_shaping_shift::cMsg_UYZ9efGm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_hQbqFoKd, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_3IvKRgmP, HV_BINOP_SUBTRACT, 0, m, &cBinop_3IvKRgmP_sendMessage);
}

void Heavy_shaping_shift::cSystem_uIikE8YR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_3IvKRgmP, HV_BINOP_SUBTRACT, 1, m, &cBinop_3IvKRgmP_sendMessage);
}

void Heavy_shaping_shift::cMsg_p0GQ5C4G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_uIikE8YR_sendMessage);
}

void Heavy_shaping_shift::cBinop_3IvKRgmP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_2AWSecJb_sendMessage);
}

void Heavy_shaping_shift::cBinop_2AWSecJb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_oJXM0mLX, HV_BINOP_DIVIDE, 0, m, &cBinop_oJXM0mLX_sendMessage);
}

void Heavy_shaping_shift::cMsg_97Xs8FJl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_4ihzedU0, 0, m, &cDelay_4ihzedU0_sendMessage);
}

void Heavy_shaping_shift::cMsg_Kv9Kz00H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_hQbqFoKd, 1, m, NULL);
}

void Heavy_shaping_shift::cMsg_tSWNBf0b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_jenMHO3i_sendMessage);
}

void Heavy_shaping_shift::cSystem_jenMHO3i_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_7a5Id9qJ_sendMessage);
}

void Heavy_shaping_shift::cMsg_D04NunoV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_hQbqFoKd, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_3IvKRgmP, HV_BINOP_SUBTRACT, 0, m, &cBinop_3IvKRgmP_sendMessage);
}

void Heavy_shaping_shift::cCast_zG1pOSeq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_aKL8qVQb_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_shift::cSwitchcase_aKL8qVQb_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_B9NjEOyg_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_B9NjEOyg_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_oFwR723z_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_shift::cDelay_0DdJPKkH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_0DdJPKkH, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_0DdJPKkH, 0, m, &cDelay_0DdJPKkH_sendMessage);
  cSwitchcase_1RiKpKGP_onMessage(_c, NULL, 0, m, NULL);
  cSend_5pp9MXUB_sendMessage(_c, 0, m);
}

void Heavy_shaping_shift::cCast_oFwR723z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_B9NjEOyg_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_0DdJPKkH, 0, m, &cDelay_0DdJPKkH_sendMessage);
  cSwitchcase_1RiKpKGP_onMessage(_c, NULL, 0, m, NULL);
  cSend_5pp9MXUB_sendMessage(_c, 0, m);
}

void Heavy_shaping_shift::cMsg_wtdfaff2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_punc9W2A_sendMessage);
}

void Heavy_shaping_shift::cSystem_punc9W2A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_WNgNndwE_sendMessage);
}

void Heavy_shaping_shift::cVar_iQjbTzqt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_g12Mgfku, HV_BINOP_MULTIPLY, 0, m, &cBinop_g12Mgfku_sendMessage);
}

void Heavy_shaping_shift::cMsg_B9NjEOyg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_0DdJPKkH, 0, m, &cDelay_0DdJPKkH_sendMessage);
}

void Heavy_shaping_shift::cBinop_vQYbdX1i_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_0DdJPKkH, 2, m, &cDelay_0DdJPKkH_sendMessage);
}

void Heavy_shaping_shift::cBinop_WNgNndwE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_g12Mgfku, HV_BINOP_MULTIPLY, 1, m, &cBinop_g12Mgfku_sendMessage);
}

void Heavy_shaping_shift::cBinop_g12Mgfku_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_vQYbdX1i_sendMessage);
}

void Heavy_shaping_shift::cSend_5pp9MXUB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_xJXx7zLM_sendMessage(_c, 0, m);
}

void Heavy_shaping_shift::hTable_AfS0zmEk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_shift::cSwitchcase_UP0CdejM_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Toe3GEg4, 0, m, &cSlice_Toe3GEg4_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_t8QQPFW0_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Q96rdGG8, 0, m, &cSlice_Q96rdGG8_sendMessage);
      break;
    }
    default: {
      cMsg_b9NHnV63_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_shift::cDelay_Y9Cwq3AV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_Y9Cwq3AV, m);
  cMsg_t8QQPFW0_sendMessage(_c, 0, m);
}

void Heavy_shaping_shift::cVar_VIWEBpMv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_HploVoSh_sendMessage(_c, 0, m);
}

void Heavy_shaping_shift::cSlice_Q96rdGG8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_HuVX7t2f, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_VIWEBpMv, 0, m, &cVar_VIWEBpMv_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_shift::cSlice_Toe3GEg4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_HuVX7t2f, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_uGdpHnqi, HV_BINOP_SUBTRACT, 0, m, &cBinop_uGdpHnqi_sendMessage);
      break;
    }
    case 1: {
      cMsg_73tgoAID_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_shift::cBinop_x0v43EhW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZgI2PN54, HV_BINOP_DIVIDE, 1, m, &cBinop_ZgI2PN54_sendMessage);
}

void Heavy_shaping_shift::cBinop_ZgI2PN54_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_IXsdv1vu_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Y9Cwq3AV, 1, m, &cDelay_Y9Cwq3AV_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Y9Cwq3AV, 0, m, &cDelay_Y9Cwq3AV_sendMessage);
}

void Heavy_shaping_shift::cMsg_b9NHnV63_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_HuVX7t2f, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_uGdpHnqi, HV_BINOP_SUBTRACT, 0, m, &cBinop_uGdpHnqi_sendMessage);
}

void Heavy_shaping_shift::cSystem_NclRA5ry_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_uGdpHnqi, HV_BINOP_SUBTRACT, 1, m, &cBinop_uGdpHnqi_sendMessage);
}

void Heavy_shaping_shift::cMsg_HploVoSh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_NclRA5ry_sendMessage);
}

void Heavy_shaping_shift::cBinop_uGdpHnqi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_GbxDxamz_sendMessage);
}

void Heavy_shaping_shift::cBinop_GbxDxamz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZgI2PN54, HV_BINOP_DIVIDE, 0, m, &cBinop_ZgI2PN54_sendMessage);
}

void Heavy_shaping_shift::cMsg_IXsdv1vu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_Y9Cwq3AV, 0, m, &cDelay_Y9Cwq3AV_sendMessage);
}

void Heavy_shaping_shift::cMsg_t8QQPFW0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_HuVX7t2f, 1, m, NULL);
}

void Heavy_shaping_shift::cMsg_GSlW9Vep_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_jfDSa9ZH_sendMessage);
}

void Heavy_shaping_shift::cSystem_jfDSa9ZH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_x0v43EhW_sendMessage);
}

void Heavy_shaping_shift::cMsg_73tgoAID_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_HuVX7t2f, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_uGdpHnqi, HV_BINOP_SUBTRACT, 0, m, &cBinop_uGdpHnqi_sendMessage);
}

void Heavy_shaping_shift::cReceive_ODNuj8ml_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_1tJ2QfoU, 0, m, &cVar_1tJ2QfoU_sendMessage);
  cMsg_tSWNBf0b_sendMessage(_c, 0, m);
  cMsg_Kv9Kz00H_sendMessage(_c, 0, m);
  cMsg_wtdfaff2_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_iQjbTzqt, 0, m, &cVar_iQjbTzqt_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_VIWEBpMv, 0, m, &cVar_VIWEBpMv_sendMessage);
  cMsg_GSlW9Vep_sendMessage(_c, 0, m);
  cMsg_t8QQPFW0_sendMessage(_c, 0, m);
  cSwitchcase_aKL8qVQb_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_shift::cReceive_xJXx7zLM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_UP0CdejM_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_shift::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_WhOvrml8, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_hQbqFoKd, VIf(Bf0));
    __hv_varread_f(&sVarf_ybMfaxwA, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_HuVX7t2f, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_0Wuq8x0a, VOf(Bf0));
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
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_f(&sVarf_WhOvrml8, VIf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_add_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_varwrite_f(&sVarf_ybMfaxwA, VIf(Bf1));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_shift::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_shift::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
