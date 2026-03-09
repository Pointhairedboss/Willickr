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

#include "Heavy_shaping_differentiation.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_differentiation *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_differentiation_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_differentiation));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_differentiation(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_differentiation_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_differentiation));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_differentiation(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_differentiation_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_differentiation();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_differentiation::Heavy_shaping_differentiation(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_6Yygueok, -670.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_EdFOvAZi, &hTable_vgjLf1yx);
  numBytes += sDel1_init(&sDel1_xTVuXzpY);
  numBytes += sTabwrite_init(&sTabwrite_j2cygHDq, &hTable_YrkR6NU4);
  numBytes += sTabwrite_init(&sTabwrite_YQOU89sw, &hTable_ZoothvoL);
  numBytes += sDel1_init(&sDel1_TFvoZ0ck);
  numBytes += sTabwrite_init(&sTabwrite_URfiSrmB, &hTable_Qv9OPxJL);
  numBytes += hTable_init(&hTable_vgjLf1yx, 100);
  numBytes += cDelay_init(this, &cDelay_CSsUKjW0, 0.0f);
  numBytes += cVar_init_s(&cVar_qlARrarP, "A");
  numBytes += cSlice_init(&cSlice_Ot7n02is, 1, 1);
  numBytes += cSlice_init(&cSlice_VfMoc2Xm, 1, 1);
  numBytes += cBinop_init(&cBinop_P9nzbruF, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_PcthOgEk, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_szZOaSWZ, 0.0f);
  numBytes += cVar_init_f(&cVar_gBgRrP6N, 200.0f);
  numBytes += cBinop_init(&cBinop_kHdqtNIz, 0.0f); // __mul
  numBytes += hTable_init(&hTable_YrkR6NU4, 100);
  numBytes += cDelay_init(this, &cDelay_gcpjvaPN, 0.0f);
  numBytes += cVar_init_s(&cVar_tNlALIOc, "B");
  numBytes += cSlice_init(&cSlice_nzXhGACZ, 1, 1);
  numBytes += cSlice_init(&cSlice_nttYJjhG, 1, 1);
  numBytes += cBinop_init(&cBinop_eeGGtQ1M, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_TwpZvDig, 0.0f); // __sub
  numBytes += hTable_init(&hTable_ZoothvoL, 100);
  numBytes += cDelay_init(this, &cDelay_DyzVy4Qe, 0.0f);
  numBytes += cVar_init_s(&cVar_O9McjCkU, "C");
  numBytes += cSlice_init(&cSlice_NFwPuJ8o, 1, 1);
  numBytes += cSlice_init(&cSlice_LwKGPlsU, 1, 1);
  numBytes += cBinop_init(&cBinop_M5Tt5ffO, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_k1XYScWt, 0.0f); // __sub
  numBytes += hTable_init(&hTable_Qv9OPxJL, 100);
  numBytes += cDelay_init(this, &cDelay_oxkoejTT, 0.0f);
  numBytes += cVar_init_s(&cVar_kUzvyOyA, "D");
  numBytes += cSlice_init(&cSlice_iDcKAw0R, 1, 1);
  numBytes += cSlice_init(&cSlice_jkDE4AHS, 1, 1);
  numBytes += cBinop_init(&cBinop_H9tuLBAK, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_xf9tQF6J, 0.0f); // __sub
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_differentiation::~Heavy_shaping_differentiation() {
  hTable_free(&hTable_vgjLf1yx);
  hTable_free(&hTable_YrkR6NU4);
  hTable_free(&hTable_ZoothvoL);
  hTable_free(&hTable_Qv9OPxJL);
}

HvTable *Heavy_shaping_differentiation::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_vgjLf1yx; // A
    case 0xD961DF96: return &hTable_YrkR6NU4; // B
    case 0x7F1A5B02: return &hTable_ZoothvoL; // C
    case 0xB0C12D6E: return &hTable_Qv9OPxJL; // D
    default: return nullptr;
  }
}

void Heavy_shaping_differentiation::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_GIThdFdU_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_901voABB_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_differentiation::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_differentiation::hTable_vgjLf1yx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_differentiation::cSwitchcase_4yto3r1j_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_VfMoc2Xm, 0, m, &cSlice_VfMoc2Xm_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_xT4yAOrm_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Ot7n02is, 0, m, &cSlice_Ot7n02is_sendMessage);
      break;
    }
    default: {
      cMsg_B4e7HTqU_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_differentiation::cDelay_CSsUKjW0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_CSsUKjW0, m);
  cMsg_xT4yAOrm_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cVar_qlARrarP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_olvCS106_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cSlice_Ot7n02is_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EdFOvAZi, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_qlARrarP, 0, m, &cVar_qlARrarP_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cSlice_VfMoc2Xm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EdFOvAZi, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_PcthOgEk, HV_BINOP_SUBTRACT, 0, m, &cBinop_PcthOgEk_sendMessage);
      break;
    }
    case 1: {
      cMsg_oKHR0Ilu_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cBinop_jRHRZUOY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_P9nzbruF, HV_BINOP_DIVIDE, 1, m, &cBinop_P9nzbruF_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_P9nzbruF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_zWuZEPen_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_CSsUKjW0, 1, m, &cDelay_CSsUKjW0_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_CSsUKjW0, 0, m, &cDelay_CSsUKjW0_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_B4e7HTqU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EdFOvAZi, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_PcthOgEk, HV_BINOP_SUBTRACT, 0, m, &cBinop_PcthOgEk_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_jL6wYlD3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_PcthOgEk, HV_BINOP_SUBTRACT, 1, m, &cBinop_PcthOgEk_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_olvCS106_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_jL6wYlD3_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_PcthOgEk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_gZO6uuvp_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_gZO6uuvp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_P9nzbruF, HV_BINOP_DIVIDE, 0, m, &cBinop_P9nzbruF_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_zWuZEPen_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_CSsUKjW0, 0, m, &cDelay_CSsUKjW0_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_xT4yAOrm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EdFOvAZi, 1, m, NULL);
}

void Heavy_shaping_differentiation::cMsg_Qy1LqfAK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_w5ktd0Jf_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_w5ktd0Jf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_jRHRZUOY_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_oKHR0Ilu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_EdFOvAZi, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_PcthOgEk, HV_BINOP_SUBTRACT, 0, m, &cBinop_PcthOgEk_sendMessage);
}

void Heavy_shaping_differentiation::cCast_izyrCKNG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_4YXK0jKs_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_differentiation::cSwitchcase_4YXK0jKs_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_FuTiDtWS_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_FuTiDtWS_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_A4uB6g9l_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_differentiation::cDelay_szZOaSWZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_szZOaSWZ, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_szZOaSWZ, 0, m, &cDelay_szZOaSWZ_sendMessage);
  cSwitchcase_4yto3r1j_onMessage(_c, NULL, 0, m, NULL);
  cSend_SYJerNPh_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cCast_A4uB6g9l_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_FuTiDtWS_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_szZOaSWZ, 0, m, &cDelay_szZOaSWZ_sendMessage);
  cSwitchcase_4yto3r1j_onMessage(_c, NULL, 0, m, NULL);
  cSend_SYJerNPh_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cMsg_ptZM8KyL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_hhekCkNu_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_hhekCkNu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_YhZTVcy1_sendMessage);
}

void Heavy_shaping_differentiation::cVar_gBgRrP6N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_kHdqtNIz, HV_BINOP_MULTIPLY, 0, m, &cBinop_kHdqtNIz_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_FuTiDtWS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_szZOaSWZ, 0, m, &cDelay_szZOaSWZ_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_wgkMrf6Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_szZOaSWZ, 2, m, &cDelay_szZOaSWZ_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_YhZTVcy1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_kHdqtNIz, HV_BINOP_MULTIPLY, 1, m, &cBinop_kHdqtNIz_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_kHdqtNIz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_wgkMrf6Z_sendMessage);
}

void Heavy_shaping_differentiation::cSend_SYJerNPh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_901voABB_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::hTable_YrkR6NU4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_differentiation::cSwitchcase_K3Dyfvve_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_nttYJjhG, 0, m, &cSlice_nttYJjhG_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_16Lzeh1r_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_nzXhGACZ, 0, m, &cSlice_nzXhGACZ_sendMessage);
      break;
    }
    default: {
      cMsg_C4HXwb9h_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_differentiation::cDelay_gcpjvaPN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_gcpjvaPN, m);
  cMsg_16Lzeh1r_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cVar_tNlALIOc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_MXE2Xpiw_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cSlice_nzXhGACZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_j2cygHDq, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_tNlALIOc, 0, m, &cVar_tNlALIOc_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cSlice_nttYJjhG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_j2cygHDq, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_TwpZvDig, HV_BINOP_SUBTRACT, 0, m, &cBinop_TwpZvDig_sendMessage);
      break;
    }
    case 1: {
      cMsg_Xf7NzomM_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cBinop_mX7OTQdn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_eeGGtQ1M, HV_BINOP_DIVIDE, 1, m, &cBinop_eeGGtQ1M_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_eeGGtQ1M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_iHxegBgy_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_gcpjvaPN, 1, m, &cDelay_gcpjvaPN_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_gcpjvaPN, 0, m, &cDelay_gcpjvaPN_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_C4HXwb9h_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_j2cygHDq, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_TwpZvDig, HV_BINOP_SUBTRACT, 0, m, &cBinop_TwpZvDig_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_jZVFGa8d_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_TwpZvDig, HV_BINOP_SUBTRACT, 1, m, &cBinop_TwpZvDig_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_MXE2Xpiw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_jZVFGa8d_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_TwpZvDig_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_8vvrCEIF_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_8vvrCEIF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_eeGGtQ1M, HV_BINOP_DIVIDE, 0, m, &cBinop_eeGGtQ1M_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_iHxegBgy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_gcpjvaPN, 0, m, &cDelay_gcpjvaPN_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_16Lzeh1r_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_j2cygHDq, 1, m, NULL);
}

void Heavy_shaping_differentiation::cMsg_M0kOvjzq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_muMBaOHl_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_muMBaOHl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_mX7OTQdn_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_Xf7NzomM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_j2cygHDq, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_TwpZvDig, HV_BINOP_SUBTRACT, 0, m, &cBinop_TwpZvDig_sendMessage);
}

void Heavy_shaping_differentiation::hTable_ZoothvoL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_differentiation::cSwitchcase_MSFlkM1m_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_LwKGPlsU, 0, m, &cSlice_LwKGPlsU_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_3hCz0gAL_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_NFwPuJ8o, 0, m, &cSlice_NFwPuJ8o_sendMessage);
      break;
    }
    default: {
      cMsg_1pkRKLET_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_differentiation::cDelay_DyzVy4Qe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_DyzVy4Qe, m);
  cMsg_3hCz0gAL_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cVar_O9McjCkU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_rmUAQQOq_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cSlice_NFwPuJ8o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YQOU89sw, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_O9McjCkU, 0, m, &cVar_O9McjCkU_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cSlice_LwKGPlsU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YQOU89sw, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_k1XYScWt, HV_BINOP_SUBTRACT, 0, m, &cBinop_k1XYScWt_sendMessage);
      break;
    }
    case 1: {
      cMsg_UmZR5dWJ_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cBinop_F2b4LL4Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_M5Tt5ffO, HV_BINOP_DIVIDE, 1, m, &cBinop_M5Tt5ffO_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_M5Tt5ffO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_c5pjYMWo_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_DyzVy4Qe, 1, m, &cDelay_DyzVy4Qe_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_DyzVy4Qe, 0, m, &cDelay_DyzVy4Qe_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_1pkRKLET_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YQOU89sw, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_k1XYScWt, HV_BINOP_SUBTRACT, 0, m, &cBinop_k1XYScWt_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_4y384Zop_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_k1XYScWt, HV_BINOP_SUBTRACT, 1, m, &cBinop_k1XYScWt_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_rmUAQQOq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_4y384Zop_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_k1XYScWt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_S2n6royc_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_S2n6royc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_M5Tt5ffO, HV_BINOP_DIVIDE, 0, m, &cBinop_M5Tt5ffO_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_c5pjYMWo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_DyzVy4Qe, 0, m, &cDelay_DyzVy4Qe_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_3hCz0gAL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YQOU89sw, 1, m, NULL);
}

void Heavy_shaping_differentiation::cMsg_gqWbg9mf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_I5ZU60sk_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_I5ZU60sk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_F2b4LL4Q_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_UmZR5dWJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_YQOU89sw, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_k1XYScWt, HV_BINOP_SUBTRACT, 0, m, &cBinop_k1XYScWt_sendMessage);
}

void Heavy_shaping_differentiation::hTable_Qv9OPxJL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_differentiation::cSwitchcase_QiXiGI69_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_jkDE4AHS, 0, m, &cSlice_jkDE4AHS_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_9xLSacO3_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_iDcKAw0R, 0, m, &cSlice_iDcKAw0R_sendMessage);
      break;
    }
    default: {
      cMsg_NDCt7CL8_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_differentiation::cDelay_oxkoejTT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_oxkoejTT, m);
  cMsg_9xLSacO3_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cVar_kUzvyOyA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_k34id42H_sendMessage(_c, 0, m);
}

void Heavy_shaping_differentiation::cSlice_iDcKAw0R_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_URfiSrmB, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_kUzvyOyA, 0, m, &cVar_kUzvyOyA_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cSlice_jkDE4AHS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_URfiSrmB, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_xf9tQF6J, HV_BINOP_SUBTRACT, 0, m, &cBinop_xf9tQF6J_sendMessage);
      break;
    }
    case 1: {
      cMsg_VTklzR4T_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_differentiation::cBinop_lNBRPhIu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_H9tuLBAK, HV_BINOP_DIVIDE, 1, m, &cBinop_H9tuLBAK_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_H9tuLBAK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_w7qghfpA_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_oxkoejTT, 1, m, &cDelay_oxkoejTT_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_oxkoejTT, 0, m, &cDelay_oxkoejTT_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_NDCt7CL8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_URfiSrmB, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_xf9tQF6J, HV_BINOP_SUBTRACT, 0, m, &cBinop_xf9tQF6J_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_oMxJsqic_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xf9tQF6J, HV_BINOP_SUBTRACT, 1, m, &cBinop_xf9tQF6J_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_k34id42H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oMxJsqic_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_xf9tQF6J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_mKoJdzDm_sendMessage);
}

void Heavy_shaping_differentiation::cBinop_mKoJdzDm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_H9tuLBAK, HV_BINOP_DIVIDE, 0, m, &cBinop_H9tuLBAK_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_w7qghfpA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_oxkoejTT, 0, m, &cDelay_oxkoejTT_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_9xLSacO3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_URfiSrmB, 1, m, NULL);
}

void Heavy_shaping_differentiation::cMsg_Cqi9O63H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_JjKBQ5EI_sendMessage);
}

void Heavy_shaping_differentiation::cSystem_JjKBQ5EI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_lNBRPhIu_sendMessage);
}

void Heavy_shaping_differentiation::cMsg_VTklzR4T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_URfiSrmB, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_xf9tQF6J, HV_BINOP_SUBTRACT, 0, m, &cBinop_xf9tQF6J_sendMessage);
}

void Heavy_shaping_differentiation::cReceive_GIThdFdU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_qlARrarP, 0, m, &cVar_qlARrarP_sendMessage);
  cMsg_Qy1LqfAK_sendMessage(_c, 0, m);
  cMsg_xT4yAOrm_sendMessage(_c, 0, m);
  cMsg_ptZM8KyL_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_gBgRrP6N, 0, m, &cVar_gBgRrP6N_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_tNlALIOc, 0, m, &cVar_tNlALIOc_sendMessage);
  cMsg_M0kOvjzq_sendMessage(_c, 0, m);
  cMsg_16Lzeh1r_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_O9McjCkU, 0, m, &cVar_O9McjCkU_sendMessage);
  cMsg_gqWbg9mf_sendMessage(_c, 0, m);
  cMsg_3hCz0gAL_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_kUzvyOyA, 0, m, &cVar_kUzvyOyA_sendMessage);
  cMsg_Cqi9O63H_sendMessage(_c, 0, m);
  cMsg_9xLSacO3_sendMessage(_c, 0, m);
  cSwitchcase_4YXK0jKs_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_differentiation::cReceive_901voABB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_K3Dyfvve_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_MSFlkM1m_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_QiXiGI69_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_differentiation::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6, Bf7, Bf8;

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
    __hv_phasor_k_f(&sPhasor_6Yygueok, VOf(Bf0));
    __hv_floor_f(VIf(Bf0), VOf(Bf1));
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_abs_f(VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf1));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf6), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf7), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf8), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_sub_f(VIf(Bf2), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf4), VIf(Bf7), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf7), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf5), VIf(Bf7), VOf(Bf7));
    __hv_sub_f(VIf(Bf8), VIf(Bf7), VOf(Bf7));
    __hv_fma_f(VIf(Bf1), VIf(Bf6), VIf(Bf7), VOf(Bf7));
    __hv_tabwrite_stoppable_f(&sTabwrite_EdFOvAZi, VIf(Bf7));
    __hv_del1_f(&sDel1_xTVuXzpY, VIf(Bf7), VOf(Bf6));
    __hv_var_k_f(VOf(Bf6), 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f);
    __hv_mul_f(VIf(Bf7), VIf(Bf6), VOf(Bf6));
    __hv_tabwrite_stoppable_f(&sTabwrite_j2cygHDq, VIf(Bf6));
    __hv_var_k_f(VOf(Bf6), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_YQOU89sw, VIf(Bf0));
    __hv_del1_f(&sDel1_TFvoZ0ck, VIf(Bf0), VOf(Bf6));
    __hv_var_k_f(VOf(Bf6), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_tabwrite_stoppable_f(&sTabwrite_URfiSrmB, VIf(Bf6));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_differentiation::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_differentiation::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
