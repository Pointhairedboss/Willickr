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

#include "Heavy_shaping_complement.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_complement *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_complement_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_complement));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_complement(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_complement_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_complement));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_complement(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_complement_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_complement();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_complement::Heavy_shaping_complement(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_umzVZH7q, &hTable_e3w5D7xF);
  numBytes += sTabwrite_init(&sTabwrite_enf9Wm34, &hTable_0oNBEAOt);
  numBytes += sPhasor_k_init(&sPhasor_WyalQe6W, 640.0f, sampleRate);
  numBytes += hTable_init(&hTable_e3w5D7xF, 100);
  numBytes += cDelay_init(this, &cDelay_XpOm5ORv, 0.0f);
  numBytes += cVar_init_s(&cVar_Xh0NKrLM, "A");
  numBytes += cSlice_init(&cSlice_XKnUeSfM, 1, 1);
  numBytes += cSlice_init(&cSlice_EFEKrJpN, 1, 1);
  numBytes += cBinop_init(&cBinop_hV6Tmfc1, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_jDecEOFF, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_Z9x3FIeT, 0.0f);
  numBytes += cVar_init_f(&cVar_z9uy4t3w, 200.0f);
  numBytes += cBinop_init(&cBinop_MhjBpD0V, 0.0f); // __mul
  numBytes += hTable_init(&hTable_0oNBEAOt, 100);
  numBytes += cDelay_init(this, &cDelay_xZP64MBH, 0.0f);
  numBytes += cVar_init_s(&cVar_ePvMJDYd, "B");
  numBytes += cSlice_init(&cSlice_U7JcEUiW, 1, 1);
  numBytes += cSlice_init(&cSlice_14L10zOK, 1, 1);
  numBytes += cBinop_init(&cBinop_fdWXW9v1, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_1wRkxaxJ, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_cMrgoGQU, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_K8tsVDOW, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_complement::~Heavy_shaping_complement() {
  hTable_free(&hTable_e3w5D7xF);
  hTable_free(&hTable_0oNBEAOt);
}

HvTable *Heavy_shaping_complement::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_e3w5D7xF; // A
    case 0xD961DF96: return &hTable_0oNBEAOt; // B
    default: return nullptr;
  }
}

void Heavy_shaping_complement::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_wGt892rq_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_yO3Q6UXe_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_complement::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_complement::hTable_e3w5D7xF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_complement::cSwitchcase_e2f4Yn7s_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_EFEKrJpN, 0, m, &cSlice_EFEKrJpN_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_ItA6BF4z_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_XKnUeSfM, 0, m, &cSlice_XKnUeSfM_sendMessage);
      break;
    }
    default: {
      cMsg_o2bAU2jd_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_complement::cDelay_XpOm5ORv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_XpOm5ORv, m);
  cMsg_ItA6BF4z_sendMessage(_c, 0, m);
}

void Heavy_shaping_complement::cVar_Xh0NKrLM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_HPAjxX5B_sendMessage(_c, 0, m);
}

void Heavy_shaping_complement::cSlice_XKnUeSfM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_umzVZH7q, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_Xh0NKrLM, 0, m, &cVar_Xh0NKrLM_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_complement::cSlice_EFEKrJpN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_umzVZH7q, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_jDecEOFF, HV_BINOP_SUBTRACT, 0, m, &cBinop_jDecEOFF_sendMessage);
      break;
    }
    case 1: {
      cMsg_pPooawgx_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_complement::cBinop_QQ2ufCgb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hV6Tmfc1, HV_BINOP_DIVIDE, 1, m, &cBinop_hV6Tmfc1_sendMessage);
}

void Heavy_shaping_complement::cBinop_hV6Tmfc1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_bXs1diS1_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_XpOm5ORv, 1, m, &cDelay_XpOm5ORv_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_XpOm5ORv, 0, m, &cDelay_XpOm5ORv_sendMessage);
}

void Heavy_shaping_complement::cMsg_o2bAU2jd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_umzVZH7q, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_jDecEOFF, HV_BINOP_SUBTRACT, 0, m, &cBinop_jDecEOFF_sendMessage);
}

void Heavy_shaping_complement::cSystem_eztmg7KT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jDecEOFF, HV_BINOP_SUBTRACT, 1, m, &cBinop_jDecEOFF_sendMessage);
}

void Heavy_shaping_complement::cMsg_HPAjxX5B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_eztmg7KT_sendMessage);
}

void Heavy_shaping_complement::cBinop_jDecEOFF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Ddelnjvo_sendMessage);
}

void Heavy_shaping_complement::cBinop_Ddelnjvo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hV6Tmfc1, HV_BINOP_DIVIDE, 0, m, &cBinop_hV6Tmfc1_sendMessage);
}

void Heavy_shaping_complement::cMsg_bXs1diS1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_XpOm5ORv, 0, m, &cDelay_XpOm5ORv_sendMessage);
}

void Heavy_shaping_complement::cMsg_ItA6BF4z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_umzVZH7q, 1, m, NULL);
}

void Heavy_shaping_complement::cMsg_J5KFAFtd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Oli0OdIU_sendMessage);
}

void Heavy_shaping_complement::cSystem_Oli0OdIU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_QQ2ufCgb_sendMessage);
}

void Heavy_shaping_complement::cMsg_pPooawgx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_umzVZH7q, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_jDecEOFF, HV_BINOP_SUBTRACT, 0, m, &cBinop_jDecEOFF_sendMessage);
}

void Heavy_shaping_complement::cCast_Wjlq1y1W_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_pENtbcl9_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_complement::cSwitchcase_pENtbcl9_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_xthUoIt7_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_xthUoIt7_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_3OPR8Dfb_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_complement::cDelay_Z9x3FIeT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_Z9x3FIeT, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Z9x3FIeT, 0, m, &cDelay_Z9x3FIeT_sendMessage);
  cSwitchcase_e2f4Yn7s_onMessage(_c, NULL, 0, m, NULL);
  cSend_dheML6yA_sendMessage(_c, 0, m);
}

void Heavy_shaping_complement::cCast_3OPR8Dfb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_xthUoIt7_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Z9x3FIeT, 0, m, &cDelay_Z9x3FIeT_sendMessage);
  cSwitchcase_e2f4Yn7s_onMessage(_c, NULL, 0, m, NULL);
  cSend_dheML6yA_sendMessage(_c, 0, m);
}

void Heavy_shaping_complement::cMsg_MwjKoUxK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_5fmQX5no_sendMessage);
}

void Heavy_shaping_complement::cSystem_5fmQX5no_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_tZY1bCQM_sendMessage);
}

void Heavy_shaping_complement::cVar_z9uy4t3w_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MhjBpD0V, HV_BINOP_MULTIPLY, 0, m, &cBinop_MhjBpD0V_sendMessage);
}

void Heavy_shaping_complement::cMsg_xthUoIt7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_Z9x3FIeT, 0, m, &cDelay_Z9x3FIeT_sendMessage);
}

void Heavy_shaping_complement::cBinop_xzBq7nZj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_Z9x3FIeT, 2, m, &cDelay_Z9x3FIeT_sendMessage);
}

void Heavy_shaping_complement::cBinop_tZY1bCQM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MhjBpD0V, HV_BINOP_MULTIPLY, 1, m, &cBinop_MhjBpD0V_sendMessage);
}

void Heavy_shaping_complement::cBinop_MhjBpD0V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_xzBq7nZj_sendMessage);
}

void Heavy_shaping_complement::cSend_dheML6yA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_yO3Q6UXe_sendMessage(_c, 0, m);
}

void Heavy_shaping_complement::hTable_0oNBEAOt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_complement::cSwitchcase_uRF5AUGn_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_14L10zOK, 0, m, &cSlice_14L10zOK_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_v2pC2hMM_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_U7JcEUiW, 0, m, &cSlice_U7JcEUiW_sendMessage);
      break;
    }
    default: {
      cMsg_dDsFGT7I_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_complement::cDelay_xZP64MBH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_xZP64MBH, m);
  cMsg_v2pC2hMM_sendMessage(_c, 0, m);
}

void Heavy_shaping_complement::cVar_ePvMJDYd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_OKfvMhcX_sendMessage(_c, 0, m);
}

void Heavy_shaping_complement::cSlice_U7JcEUiW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_enf9Wm34, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_ePvMJDYd, 0, m, &cVar_ePvMJDYd_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_complement::cSlice_14L10zOK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_enf9Wm34, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_1wRkxaxJ, HV_BINOP_SUBTRACT, 0, m, &cBinop_1wRkxaxJ_sendMessage);
      break;
    }
    case 1: {
      cMsg_3KcSjnXY_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_complement::cBinop_Gq0wYuzM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_fdWXW9v1, HV_BINOP_DIVIDE, 1, m, &cBinop_fdWXW9v1_sendMessage);
}

void Heavy_shaping_complement::cBinop_fdWXW9v1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_vddjBW0T_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_xZP64MBH, 1, m, &cDelay_xZP64MBH_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_xZP64MBH, 0, m, &cDelay_xZP64MBH_sendMessage);
}

void Heavy_shaping_complement::cMsg_dDsFGT7I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_enf9Wm34, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_1wRkxaxJ, HV_BINOP_SUBTRACT, 0, m, &cBinop_1wRkxaxJ_sendMessage);
}

void Heavy_shaping_complement::cSystem_aGkXlpw9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_1wRkxaxJ, HV_BINOP_SUBTRACT, 1, m, &cBinop_1wRkxaxJ_sendMessage);
}

void Heavy_shaping_complement::cMsg_OKfvMhcX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_aGkXlpw9_sendMessage);
}

void Heavy_shaping_complement::cBinop_1wRkxaxJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_56qlsFbc_sendMessage);
}

void Heavy_shaping_complement::cBinop_56qlsFbc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_fdWXW9v1, HV_BINOP_DIVIDE, 0, m, &cBinop_fdWXW9v1_sendMessage);
}

void Heavy_shaping_complement::cMsg_vddjBW0T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_xZP64MBH, 0, m, &cDelay_xZP64MBH_sendMessage);
}

void Heavy_shaping_complement::cMsg_v2pC2hMM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_enf9Wm34, 1, m, NULL);
}

void Heavy_shaping_complement::cMsg_avk5X5YG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_KlnVGKoM_sendMessage);
}

void Heavy_shaping_complement::cSystem_KlnVGKoM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_Gq0wYuzM_sendMessage);
}

void Heavy_shaping_complement::cMsg_3KcSjnXY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_enf9Wm34, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_1wRkxaxJ, HV_BINOP_SUBTRACT, 0, m, &cBinop_1wRkxaxJ_sendMessage);
}

void Heavy_shaping_complement::cReceive_wGt892rq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Xh0NKrLM, 0, m, &cVar_Xh0NKrLM_sendMessage);
  cMsg_J5KFAFtd_sendMessage(_c, 0, m);
  cMsg_ItA6BF4z_sendMessage(_c, 0, m);
  cMsg_MwjKoUxK_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_z9uy4t3w, 0, m, &cVar_z9uy4t3w_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_ePvMJDYd, 0, m, &cVar_ePvMJDYd_sendMessage);
  cMsg_avk5X5YG_sendMessage(_c, 0, m);
  cMsg_v2pC2hMM_sendMessage(_c, 0, m);
  cSwitchcase_pENtbcl9_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_complement::cReceive_yO3Q6UXe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_uRF5AUGn_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_complement::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_cMrgoGQU, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_umzVZH7q, VIf(Bf0));
    __hv_varread_f(&sVarf_K8tsVDOW, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_enf9Wm34, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_WyalQe6W, VOf(Bf0));
    __hv_varwrite_f(&sVarf_cMrgoGQU, VIf(Bf0));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_varwrite_f(&sVarf_K8tsVDOW, VIf(Bf0));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_complement::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_complement::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
