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

#include "Heavy_shaping_arithmetic.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_arithmetic *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_arithmetic_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_arithmetic));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_arithmetic(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_arithmetic_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_arithmetic));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_arithmetic(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_arithmetic_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_arithmetic();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_arithmetic::Heavy_shaping_arithmetic(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_kPTuHsvi, 670.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_Cnb3dSuL, &hTable_VJJlRKSW);
  numBytes += sTabwrite_init(&sTabwrite_J4IwyiRh, &hTable_TA0IJxo8);
  numBytes += sTabwrite_init(&sTabwrite_Mm1pauLl, &hTable_s3F0vgGD);
  numBytes += hTable_init(&hTable_VJJlRKSW, 100);
  numBytes += cDelay_init(this, &cDelay_6mBSsaVf, 0.0f);
  numBytes += cVar_init_s(&cVar_TYw3icps, "A");
  numBytes += cSlice_init(&cSlice_shyBH2w3, 1, 1);
  numBytes += cSlice_init(&cSlice_JdDPI3ut, 1, 1);
  numBytes += cBinop_init(&cBinop_MrYPIC58, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_42gz9sYg, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_kZllJBHN, 0.0f);
  numBytes += cVar_init_f(&cVar_OoLyn2Zv, 200.0f);
  numBytes += cBinop_init(&cBinop_c3A71x1L, 0.0f); // __mul
  numBytes += hTable_init(&hTable_TA0IJxo8, 100);
  numBytes += cDelay_init(this, &cDelay_o7ZQInRa, 0.0f);
  numBytes += cVar_init_s(&cVar_ewZjqBmo, "B");
  numBytes += cSlice_init(&cSlice_QQlAQmja, 1, 1);
  numBytes += cSlice_init(&cSlice_784IR5RW, 1, 1);
  numBytes += cBinop_init(&cBinop_XErN7KDI, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_Qg6x6PQM, 0.0f); // __sub
  numBytes += hTable_init(&hTable_s3F0vgGD, 100);
  numBytes += cDelay_init(this, &cDelay_DjUBgWeY, 0.0f);
  numBytes += cVar_init_s(&cVar_5ZPTZXVO, "C");
  numBytes += cSlice_init(&cSlice_QVbcbnVV, 1, 1);
  numBytes += cSlice_init(&cSlice_HbbarJlX, 1, 1);
  numBytes += cBinop_init(&cBinop_bnZ6pT25, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_mcXHULw7, 0.0f); // __sub
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_arithmetic::~Heavy_shaping_arithmetic() {
  hTable_free(&hTable_VJJlRKSW);
  hTable_free(&hTable_TA0IJxo8);
  hTable_free(&hTable_s3F0vgGD);
}

HvTable *Heavy_shaping_arithmetic::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_VJJlRKSW; // A
    case 0xD961DF96: return &hTable_TA0IJxo8; // B
    case 0x7F1A5B02: return &hTable_s3F0vgGD; // C
    default: return nullptr;
  }
}

void Heavy_shaping_arithmetic::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_DxH6ymhd_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_i1UVkuTn_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_arithmetic::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_arithmetic::hTable_VJJlRKSW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_arithmetic::cSwitchcase_dUHwUjYJ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_JdDPI3ut, 0, m, &cSlice_JdDPI3ut_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_xeSY0X4u_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_shyBH2w3, 0, m, &cSlice_shyBH2w3_sendMessage);
      break;
    }
    default: {
      cMsg_iQLiYz9v_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_arithmetic::cDelay_6mBSsaVf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_6mBSsaVf, m);
  cMsg_xeSY0X4u_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cVar_TYw3icps_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_yHhJ6IZE_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cSlice_shyBH2w3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Cnb3dSuL, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_TYw3icps, 0, m, &cVar_TYw3icps_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_arithmetic::cSlice_JdDPI3ut_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Cnb3dSuL, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_42gz9sYg, HV_BINOP_SUBTRACT, 0, m, &cBinop_42gz9sYg_sendMessage);
      break;
    }
    case 1: {
      cMsg_wVbJx25b_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_arithmetic::cBinop_JhsWAYzU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MrYPIC58, HV_BINOP_DIVIDE, 1, m, &cBinop_MrYPIC58_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_MrYPIC58_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_thJBTF4t_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_6mBSsaVf, 1, m, &cDelay_6mBSsaVf_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_6mBSsaVf, 0, m, &cDelay_6mBSsaVf_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_iQLiYz9v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Cnb3dSuL, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_42gz9sYg, HV_BINOP_SUBTRACT, 0, m, &cBinop_42gz9sYg_sendMessage);
}

void Heavy_shaping_arithmetic::cSystem_G72rBSJo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_42gz9sYg, HV_BINOP_SUBTRACT, 1, m, &cBinop_42gz9sYg_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_yHhJ6IZE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_G72rBSJo_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_42gz9sYg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Ohzbdfnv_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_Ohzbdfnv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MrYPIC58, HV_BINOP_DIVIDE, 0, m, &cBinop_MrYPIC58_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_thJBTF4t_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_6mBSsaVf, 0, m, &cDelay_6mBSsaVf_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_xeSY0X4u_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Cnb3dSuL, 1, m, NULL);
}

void Heavy_shaping_arithmetic::cMsg_drJq3fv9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_yWSKwLwn_sendMessage);
}

void Heavy_shaping_arithmetic::cSystem_yWSKwLwn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_JhsWAYzU_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_wVbJx25b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Cnb3dSuL, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_42gz9sYg, HV_BINOP_SUBTRACT, 0, m, &cBinop_42gz9sYg_sendMessage);
}

void Heavy_shaping_arithmetic::cCast_ttvLXpYL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_nAnarSG7_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_arithmetic::cSwitchcase_nAnarSG7_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_pcS04dep_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_pcS04dep_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_bLX0lYaf_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_arithmetic::cDelay_kZllJBHN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_kZllJBHN, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kZllJBHN, 0, m, &cDelay_kZllJBHN_sendMessage);
  cSwitchcase_dUHwUjYJ_onMessage(_c, NULL, 0, m, NULL);
  cSend_Box8vbSC_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cCast_bLX0lYaf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_pcS04dep_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kZllJBHN, 0, m, &cDelay_kZllJBHN_sendMessage);
  cSwitchcase_dUHwUjYJ_onMessage(_c, NULL, 0, m, NULL);
  cSend_Box8vbSC_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cMsg_r8H3Kcy6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_K686x0aK_sendMessage);
}

void Heavy_shaping_arithmetic::cSystem_K686x0aK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_BKnO8ZFt_sendMessage);
}

void Heavy_shaping_arithmetic::cVar_OoLyn2Zv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_c3A71x1L, HV_BINOP_MULTIPLY, 0, m, &cBinop_c3A71x1L_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_pcS04dep_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_kZllJBHN, 0, m, &cDelay_kZllJBHN_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_UmXyi6mZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_kZllJBHN, 2, m, &cDelay_kZllJBHN_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_BKnO8ZFt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_c3A71x1L, HV_BINOP_MULTIPLY, 1, m, &cBinop_c3A71x1L_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_c3A71x1L_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_UmXyi6mZ_sendMessage);
}

void Heavy_shaping_arithmetic::cSend_Box8vbSC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_i1UVkuTn_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::hTable_TA0IJxo8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_arithmetic::cSwitchcase_Ff6wqynS_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_784IR5RW, 0, m, &cSlice_784IR5RW_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_ob7X2AIm_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_QQlAQmja, 0, m, &cSlice_QQlAQmja_sendMessage);
      break;
    }
    default: {
      cMsg_s2473X6N_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_arithmetic::cDelay_o7ZQInRa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_o7ZQInRa, m);
  cMsg_ob7X2AIm_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cVar_ewZjqBmo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_uedHmZrA_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cSlice_QQlAQmja_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J4IwyiRh, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_ewZjqBmo, 0, m, &cVar_ewZjqBmo_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_arithmetic::cSlice_784IR5RW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J4IwyiRh, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_Qg6x6PQM, HV_BINOP_SUBTRACT, 0, m, &cBinop_Qg6x6PQM_sendMessage);
      break;
    }
    case 1: {
      cMsg_W6CJardL_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_arithmetic::cBinop_ZHJpv8az_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_XErN7KDI, HV_BINOP_DIVIDE, 1, m, &cBinop_XErN7KDI_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_XErN7KDI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_mTjajhjK_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_o7ZQInRa, 1, m, &cDelay_o7ZQInRa_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_o7ZQInRa, 0, m, &cDelay_o7ZQInRa_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_s2473X6N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J4IwyiRh, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Qg6x6PQM, HV_BINOP_SUBTRACT, 0, m, &cBinop_Qg6x6PQM_sendMessage);
}

void Heavy_shaping_arithmetic::cSystem_ZJ8mlWbO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Qg6x6PQM, HV_BINOP_SUBTRACT, 1, m, &cBinop_Qg6x6PQM_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_uedHmZrA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_ZJ8mlWbO_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_Qg6x6PQM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Bo2KAVHU_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_Bo2KAVHU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_XErN7KDI, HV_BINOP_DIVIDE, 0, m, &cBinop_XErN7KDI_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_mTjajhjK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_o7ZQInRa, 0, m, &cDelay_o7ZQInRa_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_ob7X2AIm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J4IwyiRh, 1, m, NULL);
}

void Heavy_shaping_arithmetic::cMsg_iVii3yeV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_hmTgXZsj_sendMessage);
}

void Heavy_shaping_arithmetic::cSystem_hmTgXZsj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_ZHJpv8az_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_W6CJardL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_J4IwyiRh, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Qg6x6PQM, HV_BINOP_SUBTRACT, 0, m, &cBinop_Qg6x6PQM_sendMessage);
}

void Heavy_shaping_arithmetic::hTable_s3F0vgGD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_arithmetic::cSwitchcase_vWVuw5vo_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_HbbarJlX, 0, m, &cSlice_HbbarJlX_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_8pDnonA8_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_QVbcbnVV, 0, m, &cSlice_QVbcbnVV_sendMessage);
      break;
    }
    default: {
      cMsg_7YYbaUxq_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_arithmetic::cDelay_DjUBgWeY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_DjUBgWeY, m);
  cMsg_8pDnonA8_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cVar_5ZPTZXVO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_FcjQz7MG_sendMessage(_c, 0, m);
}

void Heavy_shaping_arithmetic::cSlice_QVbcbnVV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Mm1pauLl, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_5ZPTZXVO, 0, m, &cVar_5ZPTZXVO_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_arithmetic::cSlice_HbbarJlX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Mm1pauLl, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_mcXHULw7, HV_BINOP_SUBTRACT, 0, m, &cBinop_mcXHULw7_sendMessage);
      break;
    }
    case 1: {
      cMsg_cpHYKlhq_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_arithmetic::cBinop_kFQkuYQl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_bnZ6pT25, HV_BINOP_DIVIDE, 1, m, &cBinop_bnZ6pT25_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_bnZ6pT25_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_p4DNH4lt_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_DjUBgWeY, 1, m, &cDelay_DjUBgWeY_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_DjUBgWeY, 0, m, &cDelay_DjUBgWeY_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_7YYbaUxq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Mm1pauLl, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_mcXHULw7, HV_BINOP_SUBTRACT, 0, m, &cBinop_mcXHULw7_sendMessage);
}

void Heavy_shaping_arithmetic::cSystem_4R2jjKh3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mcXHULw7, HV_BINOP_SUBTRACT, 1, m, &cBinop_mcXHULw7_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_FcjQz7MG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_4R2jjKh3_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_mcXHULw7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_G5P39B3j_sendMessage);
}

void Heavy_shaping_arithmetic::cBinop_G5P39B3j_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_bnZ6pT25, HV_BINOP_DIVIDE, 0, m, &cBinop_bnZ6pT25_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_p4DNH4lt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_DjUBgWeY, 0, m, &cDelay_DjUBgWeY_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_8pDnonA8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Mm1pauLl, 1, m, NULL);
}

void Heavy_shaping_arithmetic::cMsg_5Ny4o2QQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_kWp03dfq_sendMessage);
}

void Heavy_shaping_arithmetic::cSystem_kWp03dfq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_kFQkuYQl_sendMessage);
}

void Heavy_shaping_arithmetic::cMsg_cpHYKlhq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Mm1pauLl, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_mcXHULw7, HV_BINOP_SUBTRACT, 0, m, &cBinop_mcXHULw7_sendMessage);
}

void Heavy_shaping_arithmetic::cReceive_DxH6ymhd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_TYw3icps, 0, m, &cVar_TYw3icps_sendMessage);
  cMsg_drJq3fv9_sendMessage(_c, 0, m);
  cMsg_xeSY0X4u_sendMessage(_c, 0, m);
  cMsg_r8H3Kcy6_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_OoLyn2Zv, 0, m, &cVar_OoLyn2Zv_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_ewZjqBmo, 0, m, &cVar_ewZjqBmo_sendMessage);
  cMsg_iVii3yeV_sendMessage(_c, 0, m);
  cMsg_ob7X2AIm_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_5ZPTZXVO, 0, m, &cVar_5ZPTZXVO_sendMessage);
  cMsg_5Ny4o2QQ_sendMessage(_c, 0, m);
  cMsg_8pDnonA8_sendMessage(_c, 0, m);
  cSwitchcase_nAnarSG7_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_arithmetic::cReceive_i1UVkuTn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_Ff6wqynS_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_vWVuw5vo_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_arithmetic::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_phasor_k_f(&sPhasor_kPTuHsvi, VOf(Bf0));
    __hv_neg_f(VIf(Bf0), VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_Cnb3dSuL, VIf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_add_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_tabwrite_stoppable_f(&sTabwrite_J4IwyiRh, VIf(Bf1));
    __hv_var_k_f(VOf(Bf0), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_Mm1pauLl, VIf(Bf0));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_arithmetic::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_arithmetic::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
