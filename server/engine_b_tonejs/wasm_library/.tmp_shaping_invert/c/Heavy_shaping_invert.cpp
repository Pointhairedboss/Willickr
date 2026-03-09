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

#include "Heavy_shaping_invert.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_invert *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_invert_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_invert));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_invert(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_invert_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_invert));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_invert(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_invert_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_invert();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_invert::Heavy_shaping_invert(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_WX0C6DoN, &hTable_jxLhkdQN);
  numBytes += sTabwrite_init(&sTabwrite_frxA4WOu, &hTable_0oLKQM01);
  numBytes += sPhasor_k_init(&sPhasor_vfBW6158, 640.0f, sampleRate);
  numBytes += hTable_init(&hTable_jxLhkdQN, 100);
  numBytes += cDelay_init(this, &cDelay_3hxof349, 0.0f);
  numBytes += cVar_init_s(&cVar_ZmG6RDjN, "A");
  numBytes += cSlice_init(&cSlice_XMp1TAY9, 1, 1);
  numBytes += cSlice_init(&cSlice_hHEgXSRM, 1, 1);
  numBytes += cBinop_init(&cBinop_01LYgceK, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_5qKOGqvd, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_InKsCEk4, 0.0f);
  numBytes += cVar_init_f(&cVar_YHCFUVp2, 200.0f);
  numBytes += cBinop_init(&cBinop_76QhVcxM, 0.0f); // __mul
  numBytes += hTable_init(&hTable_0oLKQM01, 100);
  numBytes += cDelay_init(this, &cDelay_3zKS5DtJ, 0.0f);
  numBytes += cVar_init_s(&cVar_2rX6Na5A, "B");
  numBytes += cSlice_init(&cSlice_bSRHweSM, 1, 1);
  numBytes += cSlice_init(&cSlice_U726Oy8N, 1, 1);
  numBytes += cBinop_init(&cBinop_fEFchBa0, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_jUDUUHe5, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_RbiU3p9B, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_TqXezXGM, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_invert::~Heavy_shaping_invert() {
  hTable_free(&hTable_jxLhkdQN);
  hTable_free(&hTable_0oLKQM01);
}

HvTable *Heavy_shaping_invert::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_jxLhkdQN; // A
    case 0xD961DF96: return &hTable_0oLKQM01; // B
    default: return nullptr;
  }
}

void Heavy_shaping_invert::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_PRlu2O9k_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_Whi7UCOJ_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_invert::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_invert::hTable_jxLhkdQN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_invert::cSwitchcase_tjJmMbRH_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_hHEgXSRM, 0, m, &cSlice_hHEgXSRM_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_fUy3QZOQ_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_XMp1TAY9, 0, m, &cSlice_XMp1TAY9_sendMessage);
      break;
    }
    default: {
      cMsg_pDccOZOQ_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_invert::cDelay_3hxof349_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_3hxof349, m);
  cMsg_fUy3QZOQ_sendMessage(_c, 0, m);
}

void Heavy_shaping_invert::cVar_ZmG6RDjN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_1IPKsKqS_sendMessage(_c, 0, m);
}

void Heavy_shaping_invert::cSlice_XMp1TAY9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WX0C6DoN, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_ZmG6RDjN, 0, m, &cVar_ZmG6RDjN_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_invert::cSlice_hHEgXSRM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WX0C6DoN, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_5qKOGqvd, HV_BINOP_SUBTRACT, 0, m, &cBinop_5qKOGqvd_sendMessage);
      break;
    }
    case 1: {
      cMsg_adBu2Trz_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_invert::cBinop_1Lqlubhs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_01LYgceK, HV_BINOP_DIVIDE, 1, m, &cBinop_01LYgceK_sendMessage);
}

void Heavy_shaping_invert::cBinop_01LYgceK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_NBKxwvD4_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3hxof349, 1, m, &cDelay_3hxof349_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3hxof349, 0, m, &cDelay_3hxof349_sendMessage);
}

void Heavy_shaping_invert::cMsg_pDccOZOQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WX0C6DoN, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_5qKOGqvd, HV_BINOP_SUBTRACT, 0, m, &cBinop_5qKOGqvd_sendMessage);
}

void Heavy_shaping_invert::cSystem_d1liANLY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_5qKOGqvd, HV_BINOP_SUBTRACT, 1, m, &cBinop_5qKOGqvd_sendMessage);
}

void Heavy_shaping_invert::cMsg_1IPKsKqS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_d1liANLY_sendMessage);
}

void Heavy_shaping_invert::cBinop_5qKOGqvd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_36bCnqQb_sendMessage);
}

void Heavy_shaping_invert::cBinop_36bCnqQb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_01LYgceK, HV_BINOP_DIVIDE, 0, m, &cBinop_01LYgceK_sendMessage);
}

void Heavy_shaping_invert::cMsg_NBKxwvD4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_3hxof349, 0, m, &cDelay_3hxof349_sendMessage);
}

void Heavy_shaping_invert::cMsg_fUy3QZOQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WX0C6DoN, 1, m, NULL);
}

void Heavy_shaping_invert::cMsg_gJvbDWYw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_EBk94ddc_sendMessage);
}

void Heavy_shaping_invert::cSystem_EBk94ddc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_1Lqlubhs_sendMessage);
}

void Heavy_shaping_invert::cMsg_adBu2Trz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WX0C6DoN, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_5qKOGqvd, HV_BINOP_SUBTRACT, 0, m, &cBinop_5qKOGqvd_sendMessage);
}

void Heavy_shaping_invert::cCast_WWlpf8AV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_9aqfjC1L_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_invert::cSwitchcase_9aqfjC1L_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_r9gsVJUH_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_r9gsVJUH_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_KsYcjffk_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_invert::cDelay_InKsCEk4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_InKsCEk4, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_InKsCEk4, 0, m, &cDelay_InKsCEk4_sendMessage);
  cSwitchcase_tjJmMbRH_onMessage(_c, NULL, 0, m, NULL);
  cSend_BSWbpcif_sendMessage(_c, 0, m);
}

void Heavy_shaping_invert::cCast_KsYcjffk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_r9gsVJUH_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_InKsCEk4, 0, m, &cDelay_InKsCEk4_sendMessage);
  cSwitchcase_tjJmMbRH_onMessage(_c, NULL, 0, m, NULL);
  cSend_BSWbpcif_sendMessage(_c, 0, m);
}

void Heavy_shaping_invert::cMsg_jzbqiQ3j_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_d4XytP80_sendMessage);
}

void Heavy_shaping_invert::cSystem_d4XytP80_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_bdycZYnE_sendMessage);
}

void Heavy_shaping_invert::cVar_YHCFUVp2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_76QhVcxM, HV_BINOP_MULTIPLY, 0, m, &cBinop_76QhVcxM_sendMessage);
}

void Heavy_shaping_invert::cMsg_r9gsVJUH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_InKsCEk4, 0, m, &cDelay_InKsCEk4_sendMessage);
}

void Heavy_shaping_invert::cBinop_uimQyL8b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_InKsCEk4, 2, m, &cDelay_InKsCEk4_sendMessage);
}

void Heavy_shaping_invert::cBinop_bdycZYnE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_76QhVcxM, HV_BINOP_MULTIPLY, 1, m, &cBinop_76QhVcxM_sendMessage);
}

void Heavy_shaping_invert::cBinop_76QhVcxM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_uimQyL8b_sendMessage);
}

void Heavy_shaping_invert::cSend_BSWbpcif_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_Whi7UCOJ_sendMessage(_c, 0, m);
}

void Heavy_shaping_invert::hTable_0oLKQM01_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_invert::cSwitchcase_hdI9fTVY_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_U726Oy8N, 0, m, &cSlice_U726Oy8N_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_x62f07vx_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_bSRHweSM, 0, m, &cSlice_bSRHweSM_sendMessage);
      break;
    }
    default: {
      cMsg_DQj6iAeY_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_invert::cDelay_3zKS5DtJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_3zKS5DtJ, m);
  cMsg_x62f07vx_sendMessage(_c, 0, m);
}

void Heavy_shaping_invert::cVar_2rX6Na5A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Q7qxvIsP_sendMessage(_c, 0, m);
}

void Heavy_shaping_invert::cSlice_bSRHweSM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_frxA4WOu, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_2rX6Na5A, 0, m, &cVar_2rX6Na5A_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_invert::cSlice_U726Oy8N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_frxA4WOu, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_jUDUUHe5, HV_BINOP_SUBTRACT, 0, m, &cBinop_jUDUUHe5_sendMessage);
      break;
    }
    case 1: {
      cMsg_PQLJjZ4I_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_invert::cBinop_ACT4eDql_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_fEFchBa0, HV_BINOP_DIVIDE, 1, m, &cBinop_fEFchBa0_sendMessage);
}

void Heavy_shaping_invert::cBinop_fEFchBa0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_7cGm5KJQ_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3zKS5DtJ, 1, m, &cDelay_3zKS5DtJ_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3zKS5DtJ, 0, m, &cDelay_3zKS5DtJ_sendMessage);
}

void Heavy_shaping_invert::cMsg_DQj6iAeY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_frxA4WOu, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_jUDUUHe5, HV_BINOP_SUBTRACT, 0, m, &cBinop_jUDUUHe5_sendMessage);
}

void Heavy_shaping_invert::cSystem_8RjeOd5M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jUDUUHe5, HV_BINOP_SUBTRACT, 1, m, &cBinop_jUDUUHe5_sendMessage);
}

void Heavy_shaping_invert::cMsg_Q7qxvIsP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_8RjeOd5M_sendMessage);
}

void Heavy_shaping_invert::cBinop_jUDUUHe5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_58zuMeuP_sendMessage);
}

void Heavy_shaping_invert::cBinop_58zuMeuP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_fEFchBa0, HV_BINOP_DIVIDE, 0, m, &cBinop_fEFchBa0_sendMessage);
}

void Heavy_shaping_invert::cMsg_7cGm5KJQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_3zKS5DtJ, 0, m, &cDelay_3zKS5DtJ_sendMessage);
}

void Heavy_shaping_invert::cMsg_x62f07vx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_frxA4WOu, 1, m, NULL);
}

void Heavy_shaping_invert::cMsg_3ebEaRyO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_mylelkhN_sendMessage);
}

void Heavy_shaping_invert::cSystem_mylelkhN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_ACT4eDql_sendMessage);
}

void Heavy_shaping_invert::cMsg_PQLJjZ4I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_frxA4WOu, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_jUDUUHe5, HV_BINOP_SUBTRACT, 0, m, &cBinop_jUDUUHe5_sendMessage);
}

void Heavy_shaping_invert::cReceive_PRlu2O9k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_ZmG6RDjN, 0, m, &cVar_ZmG6RDjN_sendMessage);
  cMsg_gJvbDWYw_sendMessage(_c, 0, m);
  cMsg_fUy3QZOQ_sendMessage(_c, 0, m);
  cMsg_jzbqiQ3j_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_YHCFUVp2, 0, m, &cVar_YHCFUVp2_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_2rX6Na5A, 0, m, &cVar_2rX6Na5A_sendMessage);
  cMsg_3ebEaRyO_sendMessage(_c, 0, m);
  cMsg_x62f07vx_sendMessage(_c, 0, m);
  cSwitchcase_9aqfjC1L_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_invert::cReceive_Whi7UCOJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_hdI9fTVY_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_invert::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_RbiU3p9B, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_WX0C6DoN, VIf(Bf0));
    __hv_varread_f(&sVarf_TqXezXGM, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_frxA4WOu, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_vfBW6158, VOf(Bf0));
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
    __hv_varwrite_f(&sVarf_RbiU3p9B, VIf(Bf1));
    __hv_neg_f(VIf(Bf1), VOf(Bf1));
    __hv_varwrite_f(&sVarf_TqXezXGM, VIf(Bf1));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_invert::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_invert::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
