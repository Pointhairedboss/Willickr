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

#include "Heavy_shaping_squarewave.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_squarewave *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_squarewave_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_squarewave));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_squarewave(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_squarewave_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_squarewave));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_squarewave(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_squarewave_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_squarewave();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_squarewave::Heavy_shaping_squarewave(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_XidChdno, &hTable_4jAtn8tP);
  numBytes += sTabwrite_init(&sTabwrite_y9cSE7Ka, &hTable_GNOtH8rg);
  numBytes += sPhasor_k_init(&sPhasor_mIF9jYVo, 640.0f, sampleRate);
  numBytes += hTable_init(&hTable_4jAtn8tP, 100);
  numBytes += cDelay_init(this, &cDelay_afct70Nl, 0.0f);
  numBytes += cVar_init_s(&cVar_3uYjzO2K, "A");
  numBytes += cSlice_init(&cSlice_stG23Jyb, 1, 1);
  numBytes += cSlice_init(&cSlice_hUzv6vtn, 1, 1);
  numBytes += cBinop_init(&cBinop_L8TqI1H1, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_g8pvp12Y, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_LkO3b3eA, 0.0f);
  numBytes += cVar_init_f(&cVar_pERz1Z8B, 200.0f);
  numBytes += cBinop_init(&cBinop_F1MDL2uX, 0.0f); // __mul
  numBytes += hTable_init(&hTable_GNOtH8rg, 100);
  numBytes += cDelay_init(this, &cDelay_vdlmljij, 0.0f);
  numBytes += cVar_init_s(&cVar_XRn19iTC, "B");
  numBytes += cSlice_init(&cSlice_ECk1SlOx, 1, 1);
  numBytes += cSlice_init(&cSlice_kGDVRfKK, 1, 1);
  numBytes += cBinop_init(&cBinop_sdSdr7CX, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_ywGgXDoY, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_R7a7Mrc1, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_d7Qr80S6, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_squarewave::~Heavy_shaping_squarewave() {
  hTable_free(&hTable_4jAtn8tP);
  hTable_free(&hTable_GNOtH8rg);
}

HvTable *Heavy_shaping_squarewave::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_4jAtn8tP; // A
    case 0xD961DF96: return &hTable_GNOtH8rg; // B
    default: return nullptr;
  }
}

void Heavy_shaping_squarewave::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_ljXcPCCj_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_v8cTjs22_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_squarewave::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_squarewave::hTable_4jAtn8tP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_squarewave::cSwitchcase_TzimgNrI_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_hUzv6vtn, 0, m, &cSlice_hUzv6vtn_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_a8e4OTcF_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_stG23Jyb, 0, m, &cSlice_stG23Jyb_sendMessage);
      break;
    }
    default: {
      cMsg_YAZ2roJg_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_squarewave::cDelay_afct70Nl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_afct70Nl, m);
  cMsg_a8e4OTcF_sendMessage(_c, 0, m);
}

void Heavy_shaping_squarewave::cVar_3uYjzO2K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_aBVCBvc1_sendMessage(_c, 0, m);
}

void Heavy_shaping_squarewave::cSlice_stG23Jyb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XidChdno, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_3uYjzO2K, 0, m, &cVar_3uYjzO2K_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_squarewave::cSlice_hUzv6vtn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XidChdno, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_g8pvp12Y, HV_BINOP_SUBTRACT, 0, m, &cBinop_g8pvp12Y_sendMessage);
      break;
    }
    case 1: {
      cMsg_8kE0UKWB_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_squarewave::cBinop_zgg7Zh8u_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_L8TqI1H1, HV_BINOP_DIVIDE, 1, m, &cBinop_L8TqI1H1_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_L8TqI1H1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Uz6HjJIS_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_afct70Nl, 1, m, &cDelay_afct70Nl_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_afct70Nl, 0, m, &cDelay_afct70Nl_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_YAZ2roJg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XidChdno, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_g8pvp12Y, HV_BINOP_SUBTRACT, 0, m, &cBinop_g8pvp12Y_sendMessage);
}

void Heavy_shaping_squarewave::cSystem_HRPKIsM7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_g8pvp12Y, HV_BINOP_SUBTRACT, 1, m, &cBinop_g8pvp12Y_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_aBVCBvc1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_HRPKIsM7_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_g8pvp12Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_kqRHk37T_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_kqRHk37T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_L8TqI1H1, HV_BINOP_DIVIDE, 0, m, &cBinop_L8TqI1H1_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_Uz6HjJIS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_afct70Nl, 0, m, &cDelay_afct70Nl_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_a8e4OTcF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XidChdno, 1, m, NULL);
}

void Heavy_shaping_squarewave::cMsg_rwPH6q3H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oz9ehQwT_sendMessage);
}

void Heavy_shaping_squarewave::cSystem_oz9ehQwT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_zgg7Zh8u_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_8kE0UKWB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_XidChdno, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_g8pvp12Y, HV_BINOP_SUBTRACT, 0, m, &cBinop_g8pvp12Y_sendMessage);
}

void Heavy_shaping_squarewave::cCast_XfquoWje_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_CZSMje2H_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_squarewave::cSwitchcase_CZSMje2H_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_VHKNQqTD_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_VHKNQqTD_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ebndbBO7_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_squarewave::cDelay_LkO3b3eA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_LkO3b3eA, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LkO3b3eA, 0, m, &cDelay_LkO3b3eA_sendMessage);
  cSwitchcase_TzimgNrI_onMessage(_c, NULL, 0, m, NULL);
  cSend_lgXzGQVD_sendMessage(_c, 0, m);
}

void Heavy_shaping_squarewave::cCast_ebndbBO7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_VHKNQqTD_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LkO3b3eA, 0, m, &cDelay_LkO3b3eA_sendMessage);
  cSwitchcase_TzimgNrI_onMessage(_c, NULL, 0, m, NULL);
  cSend_lgXzGQVD_sendMessage(_c, 0, m);
}

void Heavy_shaping_squarewave::cMsg_6womY9iY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_6Ww8kNpi_sendMessage);
}

void Heavy_shaping_squarewave::cSystem_6Ww8kNpi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_F69rAwpX_sendMessage);
}

void Heavy_shaping_squarewave::cVar_pERz1Z8B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_F1MDL2uX, HV_BINOP_MULTIPLY, 0, m, &cBinop_F1MDL2uX_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_VHKNQqTD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_LkO3b3eA, 0, m, &cDelay_LkO3b3eA_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_mFyTNv3m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_LkO3b3eA, 2, m, &cDelay_LkO3b3eA_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_F69rAwpX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_F1MDL2uX, HV_BINOP_MULTIPLY, 1, m, &cBinop_F1MDL2uX_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_F1MDL2uX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_mFyTNv3m_sendMessage);
}

void Heavy_shaping_squarewave::cSend_lgXzGQVD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_v8cTjs22_sendMessage(_c, 0, m);
}

void Heavy_shaping_squarewave::hTable_GNOtH8rg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_squarewave::cSwitchcase_uiStSDa4_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_kGDVRfKK, 0, m, &cSlice_kGDVRfKK_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_3SpGs8hG_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_ECk1SlOx, 0, m, &cSlice_ECk1SlOx_sendMessage);
      break;
    }
    default: {
      cMsg_MNY0j8y9_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_squarewave::cDelay_vdlmljij_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_vdlmljij, m);
  cMsg_3SpGs8hG_sendMessage(_c, 0, m);
}

void Heavy_shaping_squarewave::cVar_XRn19iTC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_El1Se6MI_sendMessage(_c, 0, m);
}

void Heavy_shaping_squarewave::cSlice_ECk1SlOx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_y9cSE7Ka, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_XRn19iTC, 0, m, &cVar_XRn19iTC_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_squarewave::cSlice_kGDVRfKK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_y9cSE7Ka, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_ywGgXDoY, HV_BINOP_SUBTRACT, 0, m, &cBinop_ywGgXDoY_sendMessage);
      break;
    }
    case 1: {
      cMsg_2IDFZwex_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_squarewave::cBinop_CwoVmq3A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sdSdr7CX, HV_BINOP_DIVIDE, 1, m, &cBinop_sdSdr7CX_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_sdSdr7CX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_C9eeuKWH_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_vdlmljij, 1, m, &cDelay_vdlmljij_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_vdlmljij, 0, m, &cDelay_vdlmljij_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_MNY0j8y9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_y9cSE7Ka, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_ywGgXDoY, HV_BINOP_SUBTRACT, 0, m, &cBinop_ywGgXDoY_sendMessage);
}

void Heavy_shaping_squarewave::cSystem_rW2fUzgp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ywGgXDoY, HV_BINOP_SUBTRACT, 1, m, &cBinop_ywGgXDoY_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_El1Se6MI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_rW2fUzgp_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_ywGgXDoY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_vnSczODr_sendMessage);
}

void Heavy_shaping_squarewave::cBinop_vnSczODr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sdSdr7CX, HV_BINOP_DIVIDE, 0, m, &cBinop_sdSdr7CX_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_C9eeuKWH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_vdlmljij, 0, m, &cDelay_vdlmljij_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_3SpGs8hG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_y9cSE7Ka, 1, m, NULL);
}

void Heavy_shaping_squarewave::cMsg_8czSgMab_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_14TmWyjd_sendMessage);
}

void Heavy_shaping_squarewave::cSystem_14TmWyjd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_CwoVmq3A_sendMessage);
}

void Heavy_shaping_squarewave::cMsg_2IDFZwex_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_y9cSE7Ka, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_ywGgXDoY, HV_BINOP_SUBTRACT, 0, m, &cBinop_ywGgXDoY_sendMessage);
}

void Heavy_shaping_squarewave::cReceive_ljXcPCCj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_3uYjzO2K, 0, m, &cVar_3uYjzO2K_sendMessage);
  cMsg_rwPH6q3H_sendMessage(_c, 0, m);
  cMsg_a8e4OTcF_sendMessage(_c, 0, m);
  cMsg_6womY9iY_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_pERz1Z8B, 0, m, &cVar_pERz1Z8B_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_XRn19iTC, 0, m, &cVar_XRn19iTC_sendMessage);
  cMsg_8czSgMab_sendMessage(_c, 0, m);
  cMsg_3SpGs8hG_sendMessage(_c, 0, m);
  cSwitchcase_CZSMje2H_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_squarewave::cReceive_v8cTjs22_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_uiStSDa4_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_squarewave::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_R7a7Mrc1, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_XidChdno, VIf(Bf0));
    __hv_varread_f(&sVarf_d7Qr80S6, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_y9cSE7Ka, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_mIF9jYVo, VOf(Bf0));
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
    __hv_varwrite_f(&sVarf_R7a7Mrc1, VIf(Bf1));
    __hv_var_k_f(VOf(Bf3), 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f);
    __hv_min_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f);
    __hv_max_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_f(&sVarf_d7Qr80S6, VIf(Bf3));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_squarewave::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_squarewave::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
