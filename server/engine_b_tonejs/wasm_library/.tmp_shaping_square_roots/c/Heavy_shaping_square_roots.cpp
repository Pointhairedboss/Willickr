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

#include "Heavy_shaping_square_roots.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_square_roots *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_square_roots_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_square_roots));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_square_roots(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_square_roots_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_square_roots));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_square_roots(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_square_roots_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_square_roots();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_square_roots::Heavy_shaping_square_roots(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_AWnQylR7, &hTable_Yk5esszA);
  numBytes += sTabwrite_init(&sTabwrite_3A4K4qZj, &hTable_7M1aar09);
  numBytes += sTabwrite_init(&sTabwrite_bNNgy9B2, &hTable_8A2KuNxD);
  numBytes += sTabwrite_init(&sTabwrite_J05Gl847, &hTable_IoeVuP0N);
  numBytes += sPhasor_k_init(&sPhasor_9yfgymGv, 1290.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_FukGnbHC, 1290.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_7pUTUikC, 1290.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_iKiZy6h3, 1290.0f, sampleRate);
  numBytes += hTable_init(&hTable_Yk5esszA, 100);
  numBytes += cDelay_init(this, &cDelay_rCuO9v1X, 0.0f);
  numBytes += cVar_init_s(&cVar_djGONbj3, "A");
  numBytes += cSlice_init(&cSlice_9AKLYiNH, 1, 1);
  numBytes += cSlice_init(&cSlice_VME0szSg, 1, 1);
  numBytes += cBinop_init(&cBinop_y63msKHy, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_PjDoXyXq, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_TmPoe2R3, 0.0f);
  numBytes += cVar_init_f(&cVar_tY3075mA, 200.0f);
  numBytes += cBinop_init(&cBinop_M1xIf5mb, 0.0f); // __mul
  numBytes += hTable_init(&hTable_7M1aar09, 100);
  numBytes += cDelay_init(this, &cDelay_wsNPgh9T, 0.0f);
  numBytes += cVar_init_s(&cVar_1HSABbC9, "B");
  numBytes += cSlice_init(&cSlice_9CTD9AfA, 1, 1);
  numBytes += cSlice_init(&cSlice_Sz23q5ya, 1, 1);
  numBytes += cBinop_init(&cBinop_mUxzM022, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_hYlFx4XD, 0.0f); // __sub
  numBytes += hTable_init(&hTable_8A2KuNxD, 100);
  numBytes += cDelay_init(this, &cDelay_CX8AlrEf, 0.0f);
  numBytes += cVar_init_s(&cVar_JeMdcMfa, "C");
  numBytes += cSlice_init(&cSlice_osj53OfY, 1, 1);
  numBytes += cSlice_init(&cSlice_yCVvdqq3, 1, 1);
  numBytes += cBinop_init(&cBinop_QXeltenH, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_ZzNlbM8K, 0.0f); // __sub
  numBytes += hTable_init(&hTable_IoeVuP0N, 100);
  numBytes += cDelay_init(this, &cDelay_aMVmt5uW, 0.0f);
  numBytes += cVar_init_s(&cVar_PjJLbrkB, "D");
  numBytes += cSlice_init(&cSlice_egv7sjma, 1, 1);
  numBytes += cSlice_init(&cSlice_XnSKaKKc, 1, 1);
  numBytes += cBinop_init(&cBinop_mingTh0k, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_iYZrgQjP, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_KGXTa0zK, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_TYXPNpwh, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_9YBlBTWL, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_PuyWc4GD, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_square_roots::~Heavy_shaping_square_roots() {
  hTable_free(&hTable_Yk5esszA);
  hTable_free(&hTable_7M1aar09);
  hTable_free(&hTable_8A2KuNxD);
  hTable_free(&hTable_IoeVuP0N);
}

HvTable *Heavy_shaping_square_roots::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_Yk5esszA; // A
    case 0xD961DF96: return &hTable_7M1aar09; // B
    case 0x7F1A5B02: return &hTable_8A2KuNxD; // C
    case 0xB0C12D6E: return &hTable_IoeVuP0N; // D
    default: return nullptr;
  }
}

void Heavy_shaping_square_roots::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_DvOmgbp8_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_uBkGU3KY_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_square_roots::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_square_roots::hTable_Yk5esszA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_square_roots::cSwitchcase_hC1ZGqiF_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_VME0szSg, 0, m, &cSlice_VME0szSg_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_OJZSOYHp_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_9AKLYiNH, 0, m, &cSlice_9AKLYiNH_sendMessage);
      break;
    }
    default: {
      cMsg_FspRSFbG_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_square_roots::cDelay_rCuO9v1X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_rCuO9v1X, m);
  cMsg_OJZSOYHp_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cVar_djGONbj3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_iRQB4aJO_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cSlice_9AKLYiNH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AWnQylR7, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_djGONbj3, 0, m, &cVar_djGONbj3_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cSlice_VME0szSg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AWnQylR7, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_PjDoXyXq, HV_BINOP_SUBTRACT, 0, m, &cBinop_PjDoXyXq_sendMessage);
      break;
    }
    case 1: {
      cMsg_feaRnQX2_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cBinop_Jxuif0TR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_y63msKHy, HV_BINOP_DIVIDE, 1, m, &cBinop_y63msKHy_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_y63msKHy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_sYPTvT6M_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_rCuO9v1X, 1, m, &cDelay_rCuO9v1X_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_rCuO9v1X, 0, m, &cDelay_rCuO9v1X_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_FspRSFbG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AWnQylR7, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_PjDoXyXq, HV_BINOP_SUBTRACT, 0, m, &cBinop_PjDoXyXq_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_14cTCHH5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_PjDoXyXq, HV_BINOP_SUBTRACT, 1, m, &cBinop_PjDoXyXq_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_iRQB4aJO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_14cTCHH5_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_PjDoXyXq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_hq90dFbh_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_hq90dFbh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_y63msKHy, HV_BINOP_DIVIDE, 0, m, &cBinop_y63msKHy_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_sYPTvT6M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_rCuO9v1X, 0, m, &cDelay_rCuO9v1X_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_OJZSOYHp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AWnQylR7, 1, m, NULL);
}

void Heavy_shaping_square_roots::cMsg_MfuzunyN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_yLJUbnf4_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_yLJUbnf4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_Jxuif0TR_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_feaRnQX2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AWnQylR7, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_PjDoXyXq, HV_BINOP_SUBTRACT, 0, m, &cBinop_PjDoXyXq_sendMessage);
}

void Heavy_shaping_square_roots::cCast_On1CVeIN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_MeBuoEWi_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_square_roots::cSwitchcase_MeBuoEWi_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_9zv5Ko8q_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_9zv5Ko8q_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ldKBdBre_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_square_roots::cDelay_TmPoe2R3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_TmPoe2R3, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_TmPoe2R3, 0, m, &cDelay_TmPoe2R3_sendMessage);
  cSwitchcase_hC1ZGqiF_onMessage(_c, NULL, 0, m, NULL);
  cSend_KZsf51xy_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cCast_ldKBdBre_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_9zv5Ko8q_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_TmPoe2R3, 0, m, &cDelay_TmPoe2R3_sendMessage);
  cSwitchcase_hC1ZGqiF_onMessage(_c, NULL, 0, m, NULL);
  cSend_KZsf51xy_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cMsg_fX8ha2Fk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oYwE9vtl_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_oYwE9vtl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_ApKmEu6g_sendMessage);
}

void Heavy_shaping_square_roots::cVar_tY3075mA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_M1xIf5mb, HV_BINOP_MULTIPLY, 0, m, &cBinop_M1xIf5mb_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_9zv5Ko8q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_TmPoe2R3, 0, m, &cDelay_TmPoe2R3_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_i3a2SsTL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_TmPoe2R3, 2, m, &cDelay_TmPoe2R3_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_ApKmEu6g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_M1xIf5mb, HV_BINOP_MULTIPLY, 1, m, &cBinop_M1xIf5mb_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_M1xIf5mb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_i3a2SsTL_sendMessage);
}

void Heavy_shaping_square_roots::cSend_KZsf51xy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_uBkGU3KY_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::hTable_7M1aar09_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_square_roots::cSwitchcase_ul7PgafA_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Sz23q5ya, 0, m, &cSlice_Sz23q5ya_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_uAp5ZYNa_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_9CTD9AfA, 0, m, &cSlice_9CTD9AfA_sendMessage);
      break;
    }
    default: {
      cMsg_BdMwO2TI_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_square_roots::cDelay_wsNPgh9T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_wsNPgh9T, m);
  cMsg_uAp5ZYNa_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cVar_1HSABbC9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_r1HzEmut_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cSlice_9CTD9AfA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_3A4K4qZj, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_1HSABbC9, 0, m, &cVar_1HSABbC9_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cSlice_Sz23q5ya_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_3A4K4qZj, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_hYlFx4XD, HV_BINOP_SUBTRACT, 0, m, &cBinop_hYlFx4XD_sendMessage);
      break;
    }
    case 1: {
      cMsg_sQwl8xln_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cBinop_GTKmohjr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mUxzM022, HV_BINOP_DIVIDE, 1, m, &cBinop_mUxzM022_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_mUxzM022_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_2rYEGXzc_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_wsNPgh9T, 1, m, &cDelay_wsNPgh9T_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_wsNPgh9T, 0, m, &cDelay_wsNPgh9T_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_BdMwO2TI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_3A4K4qZj, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hYlFx4XD, HV_BINOP_SUBTRACT, 0, m, &cBinop_hYlFx4XD_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_zrGyskNr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hYlFx4XD, HV_BINOP_SUBTRACT, 1, m, &cBinop_hYlFx4XD_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_r1HzEmut_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_zrGyskNr_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_hYlFx4XD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_6xziqyV6_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_6xziqyV6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mUxzM022, HV_BINOP_DIVIDE, 0, m, &cBinop_mUxzM022_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_2rYEGXzc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_wsNPgh9T, 0, m, &cDelay_wsNPgh9T_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_uAp5ZYNa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_3A4K4qZj, 1, m, NULL);
}

void Heavy_shaping_square_roots::cMsg_eDSUGzxQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_WXlb5psE_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_WXlb5psE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_GTKmohjr_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_sQwl8xln_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_3A4K4qZj, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hYlFx4XD, HV_BINOP_SUBTRACT, 0, m, &cBinop_hYlFx4XD_sendMessage);
}

void Heavy_shaping_square_roots::hTable_8A2KuNxD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_square_roots::cSwitchcase_eflaUw9P_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_yCVvdqq3, 0, m, &cSlice_yCVvdqq3_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_QL6LoDvt_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_osj53OfY, 0, m, &cSlice_osj53OfY_sendMessage);
      break;
    }
    default: {
      cMsg_5MSfYfjo_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_square_roots::cDelay_CX8AlrEf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_CX8AlrEf, m);
  cMsg_QL6LoDvt_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cVar_JeMdcMfa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_bZGoVZb3_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cSlice_osj53OfY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_bNNgy9B2, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_JeMdcMfa, 0, m, &cVar_JeMdcMfa_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cSlice_yCVvdqq3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_bNNgy9B2, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_ZzNlbM8K, HV_BINOP_SUBTRACT, 0, m, &cBinop_ZzNlbM8K_sendMessage);
      break;
    }
    case 1: {
      cMsg_ZzlsAC3d_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cBinop_auPKZl26_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_QXeltenH, HV_BINOP_DIVIDE, 1, m, &cBinop_QXeltenH_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_QXeltenH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_JDrc9guQ_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_CX8AlrEf, 1, m, &cDelay_CX8AlrEf_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_CX8AlrEf, 0, m, &cDelay_CX8AlrEf_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_5MSfYfjo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_bNNgy9B2, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZzNlbM8K, HV_BINOP_SUBTRACT, 0, m, &cBinop_ZzNlbM8K_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_KVVjFmVG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZzNlbM8K, HV_BINOP_SUBTRACT, 1, m, &cBinop_ZzNlbM8K_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_bZGoVZb3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_KVVjFmVG_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_ZzNlbM8K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_wyUfU1of_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_wyUfU1of_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_QXeltenH, HV_BINOP_DIVIDE, 0, m, &cBinop_QXeltenH_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_JDrc9guQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_CX8AlrEf, 0, m, &cDelay_CX8AlrEf_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_QL6LoDvt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_bNNgy9B2, 1, m, NULL);
}

void Heavy_shaping_square_roots::cMsg_dobMnlIW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_5NbRWR8c_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_5NbRWR8c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_auPKZl26_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_ZzlsAC3d_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_bNNgy9B2, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZzNlbM8K, HV_BINOP_SUBTRACT, 0, m, &cBinop_ZzNlbM8K_sendMessage);
}

void Heavy_shaping_square_roots::hTable_IoeVuP0N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_square_roots::cSwitchcase_rV86FGJH_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_XnSKaKKc, 0, m, &cSlice_XnSKaKKc_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_yrJxUFsP_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_egv7sjma, 0, m, &cSlice_egv7sjma_sendMessage);
      break;
    }
    default: {
      cMsg_L4vjgqLI_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_square_roots::cDelay_aMVmt5uW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_aMVmt5uW, m);
  cMsg_yrJxUFsP_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cVar_PjJLbrkB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_hjLFrBu2_sendMessage(_c, 0, m);
}

void Heavy_shaping_square_roots::cSlice_egv7sjma_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J05Gl847, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_PjJLbrkB, 0, m, &cVar_PjJLbrkB_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cSlice_XnSKaKKc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J05Gl847, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_iYZrgQjP, HV_BINOP_SUBTRACT, 0, m, &cBinop_iYZrgQjP_sendMessage);
      break;
    }
    case 1: {
      cMsg_TcUBsjvp_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_square_roots::cBinop_T8JDOruv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mingTh0k, HV_BINOP_DIVIDE, 1, m, &cBinop_mingTh0k_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_mingTh0k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ZfwpkF1s_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_aMVmt5uW, 1, m, &cDelay_aMVmt5uW_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_aMVmt5uW, 0, m, &cDelay_aMVmt5uW_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_L4vjgqLI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J05Gl847, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_iYZrgQjP, HV_BINOP_SUBTRACT, 0, m, &cBinop_iYZrgQjP_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_b6E5y8VK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_iYZrgQjP, HV_BINOP_SUBTRACT, 1, m, &cBinop_iYZrgQjP_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_hjLFrBu2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_b6E5y8VK_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_iYZrgQjP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_dorCxAQx_sendMessage);
}

void Heavy_shaping_square_roots::cBinop_dorCxAQx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mingTh0k, HV_BINOP_DIVIDE, 0, m, &cBinop_mingTh0k_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_ZfwpkF1s_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_aMVmt5uW, 0, m, &cDelay_aMVmt5uW_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_yrJxUFsP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J05Gl847, 1, m, NULL);
}

void Heavy_shaping_square_roots::cMsg_baqLJWth_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_m6sWmPzZ_sendMessage);
}

void Heavy_shaping_square_roots::cSystem_m6sWmPzZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_T8JDOruv_sendMessage);
}

void Heavy_shaping_square_roots::cMsg_TcUBsjvp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J05Gl847, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_iYZrgQjP, HV_BINOP_SUBTRACT, 0, m, &cBinop_iYZrgQjP_sendMessage);
}

void Heavy_shaping_square_roots::cReceive_DvOmgbp8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_djGONbj3, 0, m, &cVar_djGONbj3_sendMessage);
  cMsg_MfuzunyN_sendMessage(_c, 0, m);
  cMsg_OJZSOYHp_sendMessage(_c, 0, m);
  cMsg_fX8ha2Fk_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_tY3075mA, 0, m, &cVar_tY3075mA_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_1HSABbC9, 0, m, &cVar_1HSABbC9_sendMessage);
  cMsg_eDSUGzxQ_sendMessage(_c, 0, m);
  cMsg_uAp5ZYNa_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_JeMdcMfa, 0, m, &cVar_JeMdcMfa_sendMessage);
  cMsg_dobMnlIW_sendMessage(_c, 0, m);
  cMsg_QL6LoDvt_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_PjJLbrkB, 0, m, &cVar_PjJLbrkB_sendMessage);
  cMsg_baqLJWth_sendMessage(_c, 0, m);
  cMsg_yrJxUFsP_sendMessage(_c, 0, m);
  cSwitchcase_MeBuoEWi_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_square_roots::cReceive_uBkGU3KY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_ul7PgafA_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_eflaUw9P_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_rV86FGJH_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_square_roots::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_KGXTa0zK, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_AWnQylR7, VIf(Bf0));
    __hv_varread_f(&sVarf_TYXPNpwh, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_3A4K4qZj, VIf(Bf0));
    __hv_varread_f(&sVarf_9YBlBTWL, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_bNNgy9B2, VIf(Bf0));
    __hv_varread_f(&sVarf_PuyWc4GD, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_J05Gl847, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_9yfgymGv, VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf0));
    __hv_varwrite_f(&sVarf_KGXTa0zK, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_FukGnbHC, VOf(Bf0));
    __hv_zero_f(VOf(Bf1));
    __hv_gt_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_sqrt_f(VIf(Bf0), VOf(Bf0));
    __hv_and_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_varwrite_f(&sVarf_TYXPNpwh, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_7pUTUikC, VOf(Bf0));
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
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf1));
    __hv_varwrite_f(&sVarf_9YBlBTWL, VIf(Bf1));
    __hv_phasor_k_f(&sPhasor_iKiZy6h3, VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_abs_f(VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf3), VOf(Bf1));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf4), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf2), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf0), VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf1), VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_zero_f(VOf(Bf4));
    __hv_gt_f(VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_sqrt_f(VIf(Bf3), VOf(Bf3));
    __hv_and_f(VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_f(&sVarf_PuyWc4GD, VIf(Bf3));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_square_roots::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_square_roots::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
