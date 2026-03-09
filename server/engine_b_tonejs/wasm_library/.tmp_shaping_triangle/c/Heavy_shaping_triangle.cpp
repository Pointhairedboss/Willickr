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

#include "Heavy_shaping_triangle.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_triangle *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_triangle_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_triangle));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_triangle(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_triangle_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_triangle));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_triangle(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_triangle_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_triangle();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_triangle::Heavy_shaping_triangle(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_KSTKyBbo, &hTable_PuWFNHLH);
  numBytes += sTabwrite_init(&sTabwrite_WWn8hI6u, &hTable_R24cwQB5);
  numBytes += sTabwrite_init(&sTabwrite_EM9scoWf, &hTable_SSWmBs6j);
  numBytes += sTabwrite_init(&sTabwrite_wnUOdEVt, &hTable_mmE8TNXC);
  numBytes += sPhasor_k_init(&sPhasor_8TbNCTjc, 1290.0f, sampleRate);
  numBytes += hTable_init(&hTable_PuWFNHLH, 100);
  numBytes += cDelay_init(this, &cDelay_LmPMWKna, 0.0f);
  numBytes += cVar_init_s(&cVar_evavdJvI, "A");
  numBytes += cSlice_init(&cSlice_sgXAlODo, 1, 1);
  numBytes += cSlice_init(&cSlice_jgPOP7cV, 1, 1);
  numBytes += cBinop_init(&cBinop_du1o8cQ1, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_JrTQhWw8, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_9WG0zgNe, 0.0f);
  numBytes += cVar_init_f(&cVar_rFfSJGuf, 200.0f);
  numBytes += cBinop_init(&cBinop_YFgiFHsw, 0.0f); // __mul
  numBytes += hTable_init(&hTable_R24cwQB5, 100);
  numBytes += cDelay_init(this, &cDelay_WhpkqLI8, 0.0f);
  numBytes += cVar_init_s(&cVar_fopEutFu, "B");
  numBytes += cSlice_init(&cSlice_5R7YJ0f3, 1, 1);
  numBytes += cSlice_init(&cSlice_j5ePV7rz, 1, 1);
  numBytes += cBinop_init(&cBinop_t0cSRj6B, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_E6jxy9nd, 0.0f); // __sub
  numBytes += hTable_init(&hTable_SSWmBs6j, 100);
  numBytes += cDelay_init(this, &cDelay_94pOkH3x, 0.0f);
  numBytes += cVar_init_s(&cVar_IAMZZc2b, "C");
  numBytes += cSlice_init(&cSlice_NxqIRZtR, 1, 1);
  numBytes += cSlice_init(&cSlice_xQJx80bV, 1, 1);
  numBytes += cBinop_init(&cBinop_OSJM3kWJ, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_XJeMes0o, 0.0f); // __sub
  numBytes += hTable_init(&hTable_mmE8TNXC, 100);
  numBytes += cDelay_init(this, &cDelay_hhRfvzJA, 0.0f);
  numBytes += cVar_init_s(&cVar_ipSlSNem, "D");
  numBytes += cSlice_init(&cSlice_X1fzVmg5, 1, 1);
  numBytes += cSlice_init(&cSlice_XJ1CtmnF, 1, 1);
  numBytes += cBinop_init(&cBinop_wfuIaTF2, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_LVka6UmO, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_i8i0mi18, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Fcy6PSa9, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_4s3gLK0b, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_FAkBb17d, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_triangle::~Heavy_shaping_triangle() {
  hTable_free(&hTable_PuWFNHLH);
  hTable_free(&hTable_R24cwQB5);
  hTable_free(&hTable_SSWmBs6j);
  hTable_free(&hTable_mmE8TNXC);
}

HvTable *Heavy_shaping_triangle::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_PuWFNHLH; // A
    case 0xD961DF96: return &hTable_R24cwQB5; // B
    case 0x7F1A5B02: return &hTable_SSWmBs6j; // C
    case 0xB0C12D6E: return &hTable_mmE8TNXC; // D
    default: return nullptr;
  }
}

void Heavy_shaping_triangle::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_je35nvvc_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_CWAiIkPO_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_triangle::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_triangle::hTable_PuWFNHLH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle::cSwitchcase_uZKpTsfu_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_jgPOP7cV, 0, m, &cSlice_jgPOP7cV_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_Qi9LmQGk_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_sgXAlODo, 0, m, &cSlice_sgXAlODo_sendMessage);
      break;
    }
    default: {
      cMsg_ypJgCZ2k_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle::cDelay_LmPMWKna_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_LmPMWKna, m);
  cMsg_Qi9LmQGk_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cVar_evavdJvI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_zIeHnlV3_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cSlice_sgXAlODo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_KSTKyBbo, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_evavdJvI, 0, m, &cVar_evavdJvI_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cSlice_jgPOP7cV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_KSTKyBbo, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_JrTQhWw8, HV_BINOP_SUBTRACT, 0, m, &cBinop_JrTQhWw8_sendMessage);
      break;
    }
    case 1: {
      cMsg_nVXscBWj_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cBinop_PgAfJ2z5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_du1o8cQ1, HV_BINOP_DIVIDE, 1, m, &cBinop_du1o8cQ1_sendMessage);
}

void Heavy_shaping_triangle::cBinop_du1o8cQ1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_c3b6JSGl_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LmPMWKna, 1, m, &cDelay_LmPMWKna_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LmPMWKna, 0, m, &cDelay_LmPMWKna_sendMessage);
}

void Heavy_shaping_triangle::cMsg_ypJgCZ2k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_KSTKyBbo, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_JrTQhWw8, HV_BINOP_SUBTRACT, 0, m, &cBinop_JrTQhWw8_sendMessage);
}

void Heavy_shaping_triangle::cSystem_qn9Vs4Y7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JrTQhWw8, HV_BINOP_SUBTRACT, 1, m, &cBinop_JrTQhWw8_sendMessage);
}

void Heavy_shaping_triangle::cMsg_zIeHnlV3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_qn9Vs4Y7_sendMessage);
}

void Heavy_shaping_triangle::cBinop_JrTQhWw8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_birpo0g5_sendMessage);
}

void Heavy_shaping_triangle::cBinop_birpo0g5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_du1o8cQ1, HV_BINOP_DIVIDE, 0, m, &cBinop_du1o8cQ1_sendMessage);
}

void Heavy_shaping_triangle::cMsg_c3b6JSGl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_LmPMWKna, 0, m, &cDelay_LmPMWKna_sendMessage);
}

void Heavy_shaping_triangle::cMsg_Qi9LmQGk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_KSTKyBbo, 1, m, NULL);
}

void Heavy_shaping_triangle::cMsg_xeBYkEmG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_llFzvK6B_sendMessage);
}

void Heavy_shaping_triangle::cSystem_llFzvK6B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_PgAfJ2z5_sendMessage);
}

void Heavy_shaping_triangle::cMsg_nVXscBWj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_KSTKyBbo, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_JrTQhWw8, HV_BINOP_SUBTRACT, 0, m, &cBinop_JrTQhWw8_sendMessage);
}

void Heavy_shaping_triangle::cCast_D0C0FSYd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_nfWdeskQ_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_triangle::cSwitchcase_nfWdeskQ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_0Yt7cBQu_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_0Yt7cBQu_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_2mOXvdYv_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_triangle::cDelay_9WG0zgNe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_9WG0zgNe, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_9WG0zgNe, 0, m, &cDelay_9WG0zgNe_sendMessage);
  cSwitchcase_uZKpTsfu_onMessage(_c, NULL, 0, m, NULL);
  cSend_DfBlvnTh_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cCast_2mOXvdYv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_0Yt7cBQu_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_9WG0zgNe, 0, m, &cDelay_9WG0zgNe_sendMessage);
  cSwitchcase_uZKpTsfu_onMessage(_c, NULL, 0, m, NULL);
  cSend_DfBlvnTh_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cMsg_x5bKISI1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_EEtDRAeE_sendMessage);
}

void Heavy_shaping_triangle::cSystem_EEtDRAeE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_UtESpiKu_sendMessage);
}

void Heavy_shaping_triangle::cVar_rFfSJGuf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_YFgiFHsw, HV_BINOP_MULTIPLY, 0, m, &cBinop_YFgiFHsw_sendMessage);
}

void Heavy_shaping_triangle::cMsg_0Yt7cBQu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_9WG0zgNe, 0, m, &cDelay_9WG0zgNe_sendMessage);
}

void Heavy_shaping_triangle::cBinop_zbYgLpVY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_9WG0zgNe, 2, m, &cDelay_9WG0zgNe_sendMessage);
}

void Heavy_shaping_triangle::cBinop_UtESpiKu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_YFgiFHsw, HV_BINOP_MULTIPLY, 1, m, &cBinop_YFgiFHsw_sendMessage);
}

void Heavy_shaping_triangle::cBinop_YFgiFHsw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_zbYgLpVY_sendMessage);
}

void Heavy_shaping_triangle::cSend_DfBlvnTh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_CWAiIkPO_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::hTable_R24cwQB5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle::cSwitchcase_7u6TJyxQ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_j5ePV7rz, 0, m, &cSlice_j5ePV7rz_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_1pWrY1rN_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_5R7YJ0f3, 0, m, &cSlice_5R7YJ0f3_sendMessage);
      break;
    }
    default: {
      cMsg_kAx27zwi_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle::cDelay_WhpkqLI8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_WhpkqLI8, m);
  cMsg_1pWrY1rN_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cVar_fopEutFu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_3LG5KxFA_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cSlice_5R7YJ0f3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WWn8hI6u, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_fopEutFu, 0, m, &cVar_fopEutFu_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cSlice_j5ePV7rz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WWn8hI6u, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_E6jxy9nd, HV_BINOP_SUBTRACT, 0, m, &cBinop_E6jxy9nd_sendMessage);
      break;
    }
    case 1: {
      cMsg_xY2OoaMl_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cBinop_J9Sdn6UL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_t0cSRj6B, HV_BINOP_DIVIDE, 1, m, &cBinop_t0cSRj6B_sendMessage);
}

void Heavy_shaping_triangle::cBinop_t0cSRj6B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ucTcGIV9_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_WhpkqLI8, 1, m, &cDelay_WhpkqLI8_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_WhpkqLI8, 0, m, &cDelay_WhpkqLI8_sendMessage);
}

void Heavy_shaping_triangle::cMsg_kAx27zwi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WWn8hI6u, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_E6jxy9nd, HV_BINOP_SUBTRACT, 0, m, &cBinop_E6jxy9nd_sendMessage);
}

void Heavy_shaping_triangle::cSystem_DY3aTqzN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_E6jxy9nd, HV_BINOP_SUBTRACT, 1, m, &cBinop_E6jxy9nd_sendMessage);
}

void Heavy_shaping_triangle::cMsg_3LG5KxFA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_DY3aTqzN_sendMessage);
}

void Heavy_shaping_triangle::cBinop_E6jxy9nd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_BiuEO54M_sendMessage);
}

void Heavy_shaping_triangle::cBinop_BiuEO54M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_t0cSRj6B, HV_BINOP_DIVIDE, 0, m, &cBinop_t0cSRj6B_sendMessage);
}

void Heavy_shaping_triangle::cMsg_ucTcGIV9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_WhpkqLI8, 0, m, &cDelay_WhpkqLI8_sendMessage);
}

void Heavy_shaping_triangle::cMsg_1pWrY1rN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WWn8hI6u, 1, m, NULL);
}

void Heavy_shaping_triangle::cMsg_vty6sSdD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_wtjmILjk_sendMessage);
}

void Heavy_shaping_triangle::cSystem_wtjmILjk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_J9Sdn6UL_sendMessage);
}

void Heavy_shaping_triangle::cMsg_xY2OoaMl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_WWn8hI6u, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_E6jxy9nd, HV_BINOP_SUBTRACT, 0, m, &cBinop_E6jxy9nd_sendMessage);
}

void Heavy_shaping_triangle::hTable_SSWmBs6j_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle::cSwitchcase_IzqKRnvU_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_xQJx80bV, 0, m, &cSlice_xQJx80bV_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_IA87yviA_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_NxqIRZtR, 0, m, &cSlice_NxqIRZtR_sendMessage);
      break;
    }
    default: {
      cMsg_9eb1xOJO_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle::cDelay_94pOkH3x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_94pOkH3x, m);
  cMsg_IA87yviA_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cVar_IAMZZc2b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_JBuhgIex_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cSlice_NxqIRZtR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EM9scoWf, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_IAMZZc2b, 0, m, &cVar_IAMZZc2b_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cSlice_xQJx80bV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EM9scoWf, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_XJeMes0o, HV_BINOP_SUBTRACT, 0, m, &cBinop_XJeMes0o_sendMessage);
      break;
    }
    case 1: {
      cMsg_9SyEqoNv_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cBinop_7Q2amRe6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_OSJM3kWJ, HV_BINOP_DIVIDE, 1, m, &cBinop_OSJM3kWJ_sendMessage);
}

void Heavy_shaping_triangle::cBinop_OSJM3kWJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_vbG9eo1A_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_94pOkH3x, 1, m, &cDelay_94pOkH3x_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_94pOkH3x, 0, m, &cDelay_94pOkH3x_sendMessage);
}

void Heavy_shaping_triangle::cMsg_9eb1xOJO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EM9scoWf, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_XJeMes0o, HV_BINOP_SUBTRACT, 0, m, &cBinop_XJeMes0o_sendMessage);
}

void Heavy_shaping_triangle::cSystem_FxM0rXs4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_XJeMes0o, HV_BINOP_SUBTRACT, 1, m, &cBinop_XJeMes0o_sendMessage);
}

void Heavy_shaping_triangle::cMsg_JBuhgIex_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_FxM0rXs4_sendMessage);
}

void Heavy_shaping_triangle::cBinop_XJeMes0o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_kzMPeujv_sendMessage);
}

void Heavy_shaping_triangle::cBinop_kzMPeujv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_OSJM3kWJ, HV_BINOP_DIVIDE, 0, m, &cBinop_OSJM3kWJ_sendMessage);
}

void Heavy_shaping_triangle::cMsg_vbG9eo1A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_94pOkH3x, 0, m, &cDelay_94pOkH3x_sendMessage);
}

void Heavy_shaping_triangle::cMsg_IA87yviA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EM9scoWf, 1, m, NULL);
}

void Heavy_shaping_triangle::cMsg_xC94Kzuk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_MFNZ4f9p_sendMessage);
}

void Heavy_shaping_triangle::cSystem_MFNZ4f9p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_7Q2amRe6_sendMessage);
}

void Heavy_shaping_triangle::cMsg_9SyEqoNv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EM9scoWf, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_XJeMes0o, HV_BINOP_SUBTRACT, 0, m, &cBinop_XJeMes0o_sendMessage);
}

void Heavy_shaping_triangle::hTable_mmE8TNXC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_triangle::cSwitchcase_yJbCyNoY_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_XJ1CtmnF, 0, m, &cSlice_XJ1CtmnF_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_wf6YpRUd_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_X1fzVmg5, 0, m, &cSlice_X1fzVmg5_sendMessage);
      break;
    }
    default: {
      cMsg_TmjmwLoJ_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_triangle::cDelay_hhRfvzJA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_hhRfvzJA, m);
  cMsg_wf6YpRUd_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cVar_ipSlSNem_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_yGLaYXTx_sendMessage(_c, 0, m);
}

void Heavy_shaping_triangle::cSlice_X1fzVmg5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wnUOdEVt, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_ipSlSNem, 0, m, &cVar_ipSlSNem_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cSlice_XJ1CtmnF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wnUOdEVt, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_LVka6UmO, HV_BINOP_SUBTRACT, 0, m, &cBinop_LVka6UmO_sendMessage);
      break;
    }
    case 1: {
      cMsg_hsHrHURg_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_triangle::cBinop_SP86onZ3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wfuIaTF2, HV_BINOP_DIVIDE, 1, m, &cBinop_wfuIaTF2_sendMessage);
}

void Heavy_shaping_triangle::cBinop_wfuIaTF2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_AWy2aHEp_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_hhRfvzJA, 1, m, &cDelay_hhRfvzJA_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_hhRfvzJA, 0, m, &cDelay_hhRfvzJA_sendMessage);
}

void Heavy_shaping_triangle::cMsg_TmjmwLoJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wnUOdEVt, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_LVka6UmO, HV_BINOP_SUBTRACT, 0, m, &cBinop_LVka6UmO_sendMessage);
}

void Heavy_shaping_triangle::cSystem_BWNA1vTq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LVka6UmO, HV_BINOP_SUBTRACT, 1, m, &cBinop_LVka6UmO_sendMessage);
}

void Heavy_shaping_triangle::cMsg_yGLaYXTx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_BWNA1vTq_sendMessage);
}

void Heavy_shaping_triangle::cBinop_LVka6UmO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_9bqKUHzU_sendMessage);
}

void Heavy_shaping_triangle::cBinop_9bqKUHzU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wfuIaTF2, HV_BINOP_DIVIDE, 0, m, &cBinop_wfuIaTF2_sendMessage);
}

void Heavy_shaping_triangle::cMsg_AWy2aHEp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_hhRfvzJA, 0, m, &cDelay_hhRfvzJA_sendMessage);
}

void Heavy_shaping_triangle::cMsg_wf6YpRUd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wnUOdEVt, 1, m, NULL);
}

void Heavy_shaping_triangle::cMsg_5gcxoKVs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_ykhdDUnb_sendMessage);
}

void Heavy_shaping_triangle::cSystem_ykhdDUnb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_SP86onZ3_sendMessage);
}

void Heavy_shaping_triangle::cMsg_hsHrHURg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wnUOdEVt, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_LVka6UmO, HV_BINOP_SUBTRACT, 0, m, &cBinop_LVka6UmO_sendMessage);
}

void Heavy_shaping_triangle::cReceive_je35nvvc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_evavdJvI, 0, m, &cVar_evavdJvI_sendMessage);
  cMsg_xeBYkEmG_sendMessage(_c, 0, m);
  cMsg_Qi9LmQGk_sendMessage(_c, 0, m);
  cMsg_x5bKISI1_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_rFfSJGuf, 0, m, &cVar_rFfSJGuf_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_fopEutFu, 0, m, &cVar_fopEutFu_sendMessage);
  cMsg_vty6sSdD_sendMessage(_c, 0, m);
  cMsg_1pWrY1rN_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_IAMZZc2b, 0, m, &cVar_IAMZZc2b_sendMessage);
  cMsg_xC94Kzuk_sendMessage(_c, 0, m);
  cMsg_IA87yviA_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_ipSlSNem, 0, m, &cVar_ipSlSNem_sendMessage);
  cMsg_5gcxoKVs_sendMessage(_c, 0, m);
  cMsg_wf6YpRUd_sendMessage(_c, 0, m);
  cSwitchcase_nfWdeskQ_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_triangle::cReceive_CWAiIkPO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_7u6TJyxQ_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_IzqKRnvU_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_yJbCyNoY_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_triangle::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_i8i0mi18, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_KSTKyBbo, VIf(Bf0));
    __hv_varread_f(&sVarf_Fcy6PSa9, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_WWn8hI6u, VIf(Bf0));
    __hv_varread_f(&sVarf_4s3gLK0b, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_EM9scoWf, VIf(Bf0));
    __hv_varread_f(&sVarf_FAkBb17d, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_wnUOdEVt, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_8TbNCTjc, VOf(Bf0));
    __hv_varwrite_f(&sVarf_i8i0mi18, VIf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varwrite_f(&sVarf_Fcy6PSa9, VIf(Bf1));
    __hv_zero_f(VOf(Bf0));
    __hv_min_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f);
    __hv_max_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf0), -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f);
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_varwrite_f(&sVarf_4s3gLK0b, VIf(Bf0));
    __hv_add_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_varwrite_f(&sVarf_FAkBb17d, VIf(Bf0));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_triangle::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_triangle::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
