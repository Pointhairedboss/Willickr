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

#include "Heavy_shaping_triangle2.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_triangle2 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_triangle2_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_triangle2));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_triangle2(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_triangle2_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_triangle2));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_triangle2(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_triangle2_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_triangle2();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_triangle2::Heavy_shaping_triangle2(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_XtgFaQpz, &hTable_GMEHKzIL);
  numBytes += sTabwrite_init(&sTabwrite_J5J90O6S, &hTable_DqV5UWOl);
  numBytes += sTabwrite_init(&sTabwrite_vb4o7aOS, &hTable_P8i2qxAT);
  numBytes += sTabwrite_init(&sTabwrite_8QJGNRs7, &hTable_QKLcogBJ);
  numBytes += sPhasor_k_init(&sPhasor_Vzu3ra0X, 1290.0f, sampleRate);
  numBytes += hTable_init(&hTable_GMEHKzIL, 100);
  numBytes += cDelay_init(this, &cDelay_ZMFAZ6dt, 0.0f);
  numBytes += cVar_init_s(&cVar_7HRBEbAF, "A");
  numBytes += cSlice_init(&cSlice_61hIdMPF, 1, 1);
  numBytes += cSlice_init(&cSlice_NtI1zjIV, 1, 1);
  numBytes += cBinop_init(&cBinop_vltMA1hK, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_OafTGz5I, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_fufNtvRL, 0.0f);
  numBytes += cVar_init_f(&cVar_P70HOU3Z, 200.0f);
  numBytes += cBinop_init(&cBinop_xNLHnrmy, 0.0f); // __mul
  numBytes += hTable_init(&hTable_DqV5UWOl, 100);
  numBytes += cDelay_init(this, &cDelay_t1wEGPJz, 0.0f);
  numBytes += cVar_init_s(&cVar_f9jfwxMb, "B");
  numBytes += cSlice_init(&cSlice_lIL7fhJF, 1, 1);
  numBytes += cSlice_init(&cSlice_NeRQZ67v, 1, 1);
  numBytes += cBinop_init(&cBinop_R0dKBHaq, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_Of7krYgq, 0.0f); // __sub
  numBytes += hTable_init(&hTable_P8i2qxAT, 100);
  numBytes += cDelay_init(this, &cDelay_Ucnwuy1A, 0.0f);
  numBytes += cVar_init_s(&cVar_Hm4HzID2, "C");
  numBytes += cSlice_init(&cSlice_7Lm4RIvH, 1, 1);
  numBytes += cSlice_init(&cSlice_QaC8oRdZ, 1, 1);
  numBytes += cBinop_init(&cBinop_M6WBHBRq, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_t6zUAGE0, 0.0f); // __sub
  numBytes += hTable_init(&hTable_QKLcogBJ, 100);
  numBytes += cDelay_init(this, &cDelay_BLhWKZ77, 0.0f);
  numBytes += cVar_init_s(&cVar_tj3Z1CSQ, "D");
  numBytes += cSlice_init(&cSlice_77fPIGr7, 1, 1);
  numBytes += cSlice_init(&cSlice_PRQ0LT1O, 1, 1);
  numBytes += cBinop_init(&cBinop_726WQON9, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_psWQk0R6, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_7APsJZeK, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_oexnJTep, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_GZ6nAkBL, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_PQ7DwCqP, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_triangle2::~Heavy_shaping_triangle2() {
  hTable_free(&hTable_GMEHKzIL);
  hTable_free(&hTable_DqV5UWOl);
  hTable_free(&hTable_P8i2qxAT);
  hTable_free(&hTable_QKLcogBJ);
}

HvTable *Heavy_shaping_triangle2::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_GMEHKzIL; // A
    case 0xD961DF96: return &hTable_DqV5UWOl; // B
    case 0x7F1A5B02: return &hTable_P8i2qxAT; // C
    case 0xB0C12D6E: return &hTable_QKLcogBJ; // D
    default: return nullptr;
  }
}

void Heavy_shaping_triangle2::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_ahMXR32m_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_1vEi3zu3_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_triangle2::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_triangle2::hTable_GMEHKzIL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle2::cSwitchcase_u3WLVEnK_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_NtI1zjIV, 0, m, &cSlice_NtI1zjIV_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_HGc5N64a_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_61hIdMPF, 0, m, &cSlice_61hIdMPF_sendMessage);
      break;
    }
    default: {
      cMsg_cpEf5TxO_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle2::cDelay_ZMFAZ6dt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_ZMFAZ6dt, m);
  cMsg_HGc5N64a_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cVar_7HRBEbAF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_8VEvpJEe_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cSlice_61hIdMPF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XtgFaQpz, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_7HRBEbAF, 0, m, &cVar_7HRBEbAF_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cSlice_NtI1zjIV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XtgFaQpz, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_OafTGz5I, HV_BINOP_SUBTRACT, 0, m, &cBinop_OafTGz5I_sendMessage);
      break;
    }
    case 1: {
      cMsg_uf9PELUp_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cBinop_PBRD9SVE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vltMA1hK, HV_BINOP_DIVIDE, 1, m, &cBinop_vltMA1hK_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_vltMA1hK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jn8IDNGu_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_ZMFAZ6dt, 1, m, &cDelay_ZMFAZ6dt_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_ZMFAZ6dt, 0, m, &cDelay_ZMFAZ6dt_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_cpEf5TxO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XtgFaQpz, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_OafTGz5I, HV_BINOP_SUBTRACT, 0, m, &cBinop_OafTGz5I_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_1LW8BjkW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_OafTGz5I, HV_BINOP_SUBTRACT, 1, m, &cBinop_OafTGz5I_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_8VEvpJEe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_1LW8BjkW_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_OafTGz5I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_8omIYtP9_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_8omIYtP9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vltMA1hK, HV_BINOP_DIVIDE, 0, m, &cBinop_vltMA1hK_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_jn8IDNGu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_ZMFAZ6dt, 0, m, &cDelay_ZMFAZ6dt_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_HGc5N64a_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XtgFaQpz, 1, m, NULL);
}

void Heavy_shaping_triangle2::cMsg_u9ZQtoFy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_zm40AcRF_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_zm40AcRF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_PBRD9SVE_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_uf9PELUp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XtgFaQpz, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_OafTGz5I, HV_BINOP_SUBTRACT, 0, m, &cBinop_OafTGz5I_sendMessage);
}

void Heavy_shaping_triangle2::cCast_qalIxo5m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_6YYEaU1G_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_triangle2::cSwitchcase_6YYEaU1G_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_qBxExFhC_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_qBxExFhC_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0h7FoCTV_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_triangle2::cDelay_fufNtvRL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_fufNtvRL, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_fufNtvRL, 0, m, &cDelay_fufNtvRL_sendMessage);
  cSwitchcase_u3WLVEnK_onMessage(_c, NULL, 0, m, NULL);
  cSend_YMPLGQs4_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cCast_0h7FoCTV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_qBxExFhC_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_fufNtvRL, 0, m, &cDelay_fufNtvRL_sendMessage);
  cSwitchcase_u3WLVEnK_onMessage(_c, NULL, 0, m, NULL);
  cSend_YMPLGQs4_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cMsg_g1NuZQnu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_r3S5MddD_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_r3S5MddD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_OQ8Lbha5_sendMessage);
}

void Heavy_shaping_triangle2::cVar_P70HOU3Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xNLHnrmy, HV_BINOP_MULTIPLY, 0, m, &cBinop_xNLHnrmy_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_qBxExFhC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_fufNtvRL, 0, m, &cDelay_fufNtvRL_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_fgha1lIm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_fufNtvRL, 2, m, &cDelay_fufNtvRL_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_OQ8Lbha5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xNLHnrmy, HV_BINOP_MULTIPLY, 1, m, &cBinop_xNLHnrmy_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_xNLHnrmy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_fgha1lIm_sendMessage);
}

void Heavy_shaping_triangle2::cSend_YMPLGQs4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_1vEi3zu3_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::hTable_DqV5UWOl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle2::cSwitchcase_rXolPKVN_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_NeRQZ67v, 0, m, &cSlice_NeRQZ67v_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_v5dfdMCL_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_lIL7fhJF, 0, m, &cSlice_lIL7fhJF_sendMessage);
      break;
    }
    default: {
      cMsg_t29YIrnb_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle2::cDelay_t1wEGPJz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_t1wEGPJz, m);
  cMsg_v5dfdMCL_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cVar_f9jfwxMb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_MxWZZGvQ_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cSlice_lIL7fhJF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J5J90O6S, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_f9jfwxMb, 0, m, &cVar_f9jfwxMb_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cSlice_NeRQZ67v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J5J90O6S, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_Of7krYgq, HV_BINOP_SUBTRACT, 0, m, &cBinop_Of7krYgq_sendMessage);
      break;
    }
    case 1: {
      cMsg_bQ4PeirU_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cBinop_vJAvyeEF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_R0dKBHaq, HV_BINOP_DIVIDE, 1, m, &cBinop_R0dKBHaq_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_R0dKBHaq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_vXJ2DeBT_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_t1wEGPJz, 1, m, &cDelay_t1wEGPJz_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_t1wEGPJz, 0, m, &cDelay_t1wEGPJz_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_t29YIrnb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J5J90O6S, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Of7krYgq, HV_BINOP_SUBTRACT, 0, m, &cBinop_Of7krYgq_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_udKEfoZd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Of7krYgq, HV_BINOP_SUBTRACT, 1, m, &cBinop_Of7krYgq_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_MxWZZGvQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_udKEfoZd_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_Of7krYgq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_CSO7q6iE_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_CSO7q6iE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_R0dKBHaq, HV_BINOP_DIVIDE, 0, m, &cBinop_R0dKBHaq_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_vXJ2DeBT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_t1wEGPJz, 0, m, &cDelay_t1wEGPJz_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_v5dfdMCL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J5J90O6S, 1, m, NULL);
}

void Heavy_shaping_triangle2::cMsg_NM1Nr6zY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_fzOSjH3J_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_fzOSjH3J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_vJAvyeEF_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_bQ4PeirU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J5J90O6S, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Of7krYgq, HV_BINOP_SUBTRACT, 0, m, &cBinop_Of7krYgq_sendMessage);
}

void Heavy_shaping_triangle2::hTable_P8i2qxAT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle2::cSwitchcase_Jbbz37Hk_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_QaC8oRdZ, 0, m, &cSlice_QaC8oRdZ_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_Fn0XJClY_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_7Lm4RIvH, 0, m, &cSlice_7Lm4RIvH_sendMessage);
      break;
    }
    default: {
      cMsg_JqckFzWv_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle2::cDelay_Ucnwuy1A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_Ucnwuy1A, m);
  cMsg_Fn0XJClY_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cVar_Hm4HzID2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_BvCT1Jcs_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cSlice_7Lm4RIvH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_vb4o7aOS, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_Hm4HzID2, 0, m, &cVar_Hm4HzID2_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cSlice_QaC8oRdZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_vb4o7aOS, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_t6zUAGE0, HV_BINOP_SUBTRACT, 0, m, &cBinop_t6zUAGE0_sendMessage);
      break;
    }
    case 1: {
      cMsg_IgGPNXYt_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cBinop_SIsnok9x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_M6WBHBRq, HV_BINOP_DIVIDE, 1, m, &cBinop_M6WBHBRq_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_M6WBHBRq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_P3ZhRAsN_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Ucnwuy1A, 1, m, &cDelay_Ucnwuy1A_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Ucnwuy1A, 0, m, &cDelay_Ucnwuy1A_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_JqckFzWv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_vb4o7aOS, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_t6zUAGE0, HV_BINOP_SUBTRACT, 0, m, &cBinop_t6zUAGE0_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_1tN2edwp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_t6zUAGE0, HV_BINOP_SUBTRACT, 1, m, &cBinop_t6zUAGE0_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_BvCT1Jcs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_1tN2edwp_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_t6zUAGE0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_1n46z0xt_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_1n46z0xt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_M6WBHBRq, HV_BINOP_DIVIDE, 0, m, &cBinop_M6WBHBRq_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_P3ZhRAsN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_Ucnwuy1A, 0, m, &cDelay_Ucnwuy1A_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_Fn0XJClY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_vb4o7aOS, 1, m, NULL);
}

void Heavy_shaping_triangle2::cMsg_Vj6LFcgI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_4x4U6wIV_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_4x4U6wIV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_SIsnok9x_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_IgGPNXYt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_vb4o7aOS, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_t6zUAGE0, HV_BINOP_SUBTRACT, 0, m, &cBinop_t6zUAGE0_sendMessage);
}

void Heavy_shaping_triangle2::hTable_QKLcogBJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle2::cSwitchcase_VF5qmoPV_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_PRQ0LT1O, 0, m, &cSlice_PRQ0LT1O_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_njeu2U10_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_77fPIGr7, 0, m, &cSlice_77fPIGr7_sendMessage);
      break;
    }
    default: {
      cMsg_XrCs2qTc_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle2::cDelay_BLhWKZ77_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_BLhWKZ77, m);
  cMsg_njeu2U10_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cVar_tj3Z1CSQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_DKVj1VYH_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle2::cSlice_77fPIGr7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_8QJGNRs7, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_tj3Z1CSQ, 0, m, &cVar_tj3Z1CSQ_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cSlice_PRQ0LT1O_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_8QJGNRs7, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_psWQk0R6, HV_BINOP_SUBTRACT, 0, m, &cBinop_psWQk0R6_sendMessage);
      break;
    }
    case 1: {
      cMsg_VmUA0sOY_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle2::cBinop_xgb4ha6S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_726WQON9, HV_BINOP_DIVIDE, 1, m, &cBinop_726WQON9_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_726WQON9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_KaCgXfoy_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_BLhWKZ77, 1, m, &cDelay_BLhWKZ77_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_BLhWKZ77, 0, m, &cDelay_BLhWKZ77_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_XrCs2qTc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_8QJGNRs7, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_psWQk0R6, HV_BINOP_SUBTRACT, 0, m, &cBinop_psWQk0R6_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_KCUniw3v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_psWQk0R6, HV_BINOP_SUBTRACT, 1, m, &cBinop_psWQk0R6_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_DKVj1VYH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_KCUniw3v_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_psWQk0R6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_bqLXLDTA_sendMessage);
}

void Heavy_shaping_triangle2::cBinop_bqLXLDTA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_726WQON9, HV_BINOP_DIVIDE, 0, m, &cBinop_726WQON9_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_KaCgXfoy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_BLhWKZ77, 0, m, &cDelay_BLhWKZ77_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_njeu2U10_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_8QJGNRs7, 1, m, NULL);
}

void Heavy_shaping_triangle2::cMsg_iW8KulTG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_xq4ukfC2_sendMessage);
}

void Heavy_shaping_triangle2::cSystem_xq4ukfC2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_xgb4ha6S_sendMessage);
}

void Heavy_shaping_triangle2::cMsg_VmUA0sOY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_8QJGNRs7, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_psWQk0R6, HV_BINOP_SUBTRACT, 0, m, &cBinop_psWQk0R6_sendMessage);
}

void Heavy_shaping_triangle2::cReceive_ahMXR32m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_7HRBEbAF, 0, m, &cVar_7HRBEbAF_sendMessage);
  cMsg_u9ZQtoFy_sendMessage(_c, 0, m);
  cMsg_HGc5N64a_sendMessage(_c, 0, m);
  cMsg_g1NuZQnu_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_P70HOU3Z, 0, m, &cVar_P70HOU3Z_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_f9jfwxMb, 0, m, &cVar_f9jfwxMb_sendMessage);
  cMsg_NM1Nr6zY_sendMessage(_c, 0, m);
  cMsg_v5dfdMCL_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_Hm4HzID2, 0, m, &cVar_Hm4HzID2_sendMessage);
  cMsg_Vj6LFcgI_sendMessage(_c, 0, m);
  cMsg_Fn0XJClY_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_tj3Z1CSQ, 0, m, &cVar_tj3Z1CSQ_sendMessage);
  cMsg_iW8KulTG_sendMessage(_c, 0, m);
  cMsg_njeu2U10_sendMessage(_c, 0, m);
  cSwitchcase_6YYEaU1G_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_triangle2::cReceive_1vEi3zu3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_rXolPKVN_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_Jbbz37Hk_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_VF5qmoPV_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_triangle2::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2;

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
    __hv_varread_f(&sVarf_7APsJZeK, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_XtgFaQpz, VIf(Bf0));
    __hv_varread_f(&sVarf_oexnJTep, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_J5J90O6S, VIf(Bf0));
    __hv_varread_f(&sVarf_GZ6nAkBL, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_vb4o7aOS, VIf(Bf0));
    __hv_varread_f(&sVarf_PQ7DwCqP, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_8QJGNRs7, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_Vzu3ra0X, VOf(Bf0));
    __hv_varwrite_f(&sVarf_7APsJZeK, VIf(Bf0));
    __hv_neg_f(VIf(Bf0), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_add_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_varwrite_f(&sVarf_oexnJTep, VIf(Bf2));
    __hv_min_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_varwrite_f(&sVarf_GZ6nAkBL, VIf(Bf2));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
    __hv_mul_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_varwrite_f(&sVarf_PQ7DwCqP, VIf(Bf2));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_triangle2::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_triangle2::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
