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

#include "Heavy_shaping_polynomials.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_polynomials *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_polynomials_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_polynomials));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_polynomials(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_polynomials_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_polynomials));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_polynomials(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_polynomials_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_polynomials();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_polynomials::Heavy_shaping_polynomials(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_JzWtciKz, 670.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_AQKrmlxS, &hTable_uLEB3iXt);
  numBytes += sPhasor_k_init(&sPhasor_Rl27cmrt, 670.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_dtOA06Ri, &hTable_N6jJgR9w);
  numBytes += hTable_init(&hTable_uLEB3iXt, 100);
  numBytes += cDelay_init(this, &cDelay_YVAtVmjL, 0.0f);
  numBytes += cVar_init_s(&cVar_NKqvBAyS, "A");
  numBytes += cSlice_init(&cSlice_YdgQkJZU, 1, 1);
  numBytes += cSlice_init(&cSlice_couov11r, 1, 1);
  numBytes += cBinop_init(&cBinop_P2y8uHL7, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_dBITvYdU, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_KXT9Eo7W, 0.0f);
  numBytes += cVar_init_f(&cVar_1uE7sXbd, 200.0f);
  numBytes += cBinop_init(&cBinop_Ajy04p1X, 0.0f); // __mul
  numBytes += hTable_init(&hTable_N6jJgR9w, 100);
  numBytes += cDelay_init(this, &cDelay_m9rz4tJ5, 0.0f);
  numBytes += cVar_init_s(&cVar_4o80gi6M, "B");
  numBytes += cSlice_init(&cSlice_dBDZolMV, 1, 1);
  numBytes += cSlice_init(&cSlice_0LZXnlK4, 1, 1);
  numBytes += cBinop_init(&cBinop_gZ9yqUTW, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_aCx5h5A5, 0.0f); // __sub
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_polynomials::~Heavy_shaping_polynomials() {
  hTable_free(&hTable_uLEB3iXt);
  hTable_free(&hTable_N6jJgR9w);
}

HvTable *Heavy_shaping_polynomials::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_uLEB3iXt; // A
    case 0xD961DF96: return &hTable_N6jJgR9w; // B
    default: return nullptr;
  }
}

void Heavy_shaping_polynomials::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_fCMASi7V_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_fS3FOPcB_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_polynomials::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_polynomials::hTable_uLEB3iXt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_polynomials::cSwitchcase_zKb3EYuF_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_couov11r, 0, m, &cSlice_couov11r_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_578IDl2X_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_YdgQkJZU, 0, m, &cSlice_YdgQkJZU_sendMessage);
      break;
    }
    default: {
      cMsg_Fvuc2Ws9_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_polynomials::cDelay_YVAtVmjL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_YVAtVmjL, m);
  cMsg_578IDl2X_sendMessage(_c, 0, m);
}

void Heavy_shaping_polynomials::cVar_NKqvBAyS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_alZDTBVr_sendMessage(_c, 0, m);
}

void Heavy_shaping_polynomials::cSlice_YdgQkJZU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AQKrmlxS, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_NKqvBAyS, 0, m, &cVar_NKqvBAyS_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_polynomials::cSlice_couov11r_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AQKrmlxS, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_dBITvYdU, HV_BINOP_SUBTRACT, 0, m, &cBinop_dBITvYdU_sendMessage);
      break;
    }
    case 1: {
      cMsg_WrJvITcT_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_polynomials::cBinop_HqacsxJA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_P2y8uHL7, HV_BINOP_DIVIDE, 1, m, &cBinop_P2y8uHL7_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_P2y8uHL7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_NvXjx7Nx_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_YVAtVmjL, 1, m, &cDelay_YVAtVmjL_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_YVAtVmjL, 0, m, &cDelay_YVAtVmjL_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_Fvuc2Ws9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AQKrmlxS, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_dBITvYdU, HV_BINOP_SUBTRACT, 0, m, &cBinop_dBITvYdU_sendMessage);
}

void Heavy_shaping_polynomials::cSystem_nmCMHJlu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dBITvYdU, HV_BINOP_SUBTRACT, 1, m, &cBinop_dBITvYdU_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_alZDTBVr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_nmCMHJlu_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_dBITvYdU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_ElBnoNZb_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_ElBnoNZb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_P2y8uHL7, HV_BINOP_DIVIDE, 0, m, &cBinop_P2y8uHL7_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_NvXjx7Nx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_YVAtVmjL, 0, m, &cDelay_YVAtVmjL_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_578IDl2X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AQKrmlxS, 1, m, NULL);
}

void Heavy_shaping_polynomials::cMsg_7m70zddh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_orBDRQPi_sendMessage);
}

void Heavy_shaping_polynomials::cSystem_orBDRQPi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_HqacsxJA_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_WrJvITcT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AQKrmlxS, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_dBITvYdU, HV_BINOP_SUBTRACT, 0, m, &cBinop_dBITvYdU_sendMessage);
}

void Heavy_shaping_polynomials::cCast_yXqCHHOL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_bNmpS2l8_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_polynomials::cSwitchcase_bNmpS2l8_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_nO4fQIOF_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_nO4fQIOF_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_TL488OXd_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_polynomials::cDelay_KXT9Eo7W_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_KXT9Eo7W, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_KXT9Eo7W, 0, m, &cDelay_KXT9Eo7W_sendMessage);
  cSwitchcase_zKb3EYuF_onMessage(_c, NULL, 0, m, NULL);
  cSend_jBflMECh_sendMessage(_c, 0, m);
}

void Heavy_shaping_polynomials::cCast_TL488OXd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_nO4fQIOF_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_KXT9Eo7W, 0, m, &cDelay_KXT9Eo7W_sendMessage);
  cSwitchcase_zKb3EYuF_onMessage(_c, NULL, 0, m, NULL);
  cSend_jBflMECh_sendMessage(_c, 0, m);
}

void Heavy_shaping_polynomials::cMsg_B5vUrP6n_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oFYlKAMk_sendMessage);
}

void Heavy_shaping_polynomials::cSystem_oFYlKAMk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_iTrPu4hH_sendMessage);
}

void Heavy_shaping_polynomials::cVar_1uE7sXbd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Ajy04p1X, HV_BINOP_MULTIPLY, 0, m, &cBinop_Ajy04p1X_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_nO4fQIOF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_KXT9Eo7W, 0, m, &cDelay_KXT9Eo7W_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_7CsP4WZ2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_KXT9Eo7W, 2, m, &cDelay_KXT9Eo7W_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_iTrPu4hH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Ajy04p1X, HV_BINOP_MULTIPLY, 1, m, &cBinop_Ajy04p1X_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_Ajy04p1X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_7CsP4WZ2_sendMessage);
}

void Heavy_shaping_polynomials::cSend_jBflMECh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_fS3FOPcB_sendMessage(_c, 0, m);
}

void Heavy_shaping_polynomials::hTable_N6jJgR9w_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_polynomials::cSwitchcase_yJnRTS7e_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_0LZXnlK4, 0, m, &cSlice_0LZXnlK4_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_2ZyIErCa_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_dBDZolMV, 0, m, &cSlice_dBDZolMV_sendMessage);
      break;
    }
    default: {
      cMsg_PUA2YDuW_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_polynomials::cDelay_m9rz4tJ5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_m9rz4tJ5, m);
  cMsg_2ZyIErCa_sendMessage(_c, 0, m);
}

void Heavy_shaping_polynomials::cVar_4o80gi6M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_IdbT1Ge6_sendMessage(_c, 0, m);
}

void Heavy_shaping_polynomials::cSlice_dBDZolMV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_dtOA06Ri, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_4o80gi6M, 0, m, &cVar_4o80gi6M_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_polynomials::cSlice_0LZXnlK4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_dtOA06Ri, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_aCx5h5A5, HV_BINOP_SUBTRACT, 0, m, &cBinop_aCx5h5A5_sendMessage);
      break;
    }
    case 1: {
      cMsg_phmFNyMc_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_polynomials::cBinop_SXG8kcGt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_gZ9yqUTW, HV_BINOP_DIVIDE, 1, m, &cBinop_gZ9yqUTW_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_gZ9yqUTW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_fGP5GKFU_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_m9rz4tJ5, 1, m, &cDelay_m9rz4tJ5_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_m9rz4tJ5, 0, m, &cDelay_m9rz4tJ5_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_PUA2YDuW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_dtOA06Ri, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_aCx5h5A5, HV_BINOP_SUBTRACT, 0, m, &cBinop_aCx5h5A5_sendMessage);
}

void Heavy_shaping_polynomials::cSystem_bQUer7Wh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_aCx5h5A5, HV_BINOP_SUBTRACT, 1, m, &cBinop_aCx5h5A5_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_IdbT1Ge6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_bQUer7Wh_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_aCx5h5A5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_bxhZFYa0_sendMessage);
}

void Heavy_shaping_polynomials::cBinop_bxhZFYa0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_gZ9yqUTW, HV_BINOP_DIVIDE, 0, m, &cBinop_gZ9yqUTW_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_fGP5GKFU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_m9rz4tJ5, 0, m, &cDelay_m9rz4tJ5_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_2ZyIErCa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_dtOA06Ri, 1, m, NULL);
}

void Heavy_shaping_polynomials::cMsg_WVRNit4o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_nPCyxaLh_sendMessage);
}

void Heavy_shaping_polynomials::cSystem_nPCyxaLh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_SXG8kcGt_sendMessage);
}

void Heavy_shaping_polynomials::cMsg_phmFNyMc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_dtOA06Ri, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_aCx5h5A5, HV_BINOP_SUBTRACT, 0, m, &cBinop_aCx5h5A5_sendMessage);
}

void Heavy_shaping_polynomials::cReceive_fCMASi7V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_NKqvBAyS, 0, m, &cVar_NKqvBAyS_sendMessage);
  cMsg_7m70zddh_sendMessage(_c, 0, m);
  cMsg_578IDl2X_sendMessage(_c, 0, m);
  cMsg_B5vUrP6n_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_1uE7sXbd, 0, m, &cVar_1uE7sXbd_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_4o80gi6M, 0, m, &cVar_4o80gi6M_sendMessage);
  cMsg_WVRNit4o_sendMessage(_c, 0, m);
  cMsg_2ZyIErCa_sendMessage(_c, 0, m);
  cSwitchcase_bNmpS2l8_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_polynomials::cReceive_fS3FOPcB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_yJnRTS7e_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_polynomials::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5;

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
    __hv_phasor_k_f(&sPhasor_JzWtciKz, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_AQKrmlxS, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_Rl27cmrt, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), -5.0f, -5.0f, -5.0f, -5.0f, -5.0f, -5.0f, -5.0f, -5.0f);
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf0), VIf(Bf2), VOf(Bf3));
    __hv_var_k_f(VOf(Bf4), -18.0f, -18.0f, -18.0f, -18.0f, -18.0f, -18.0f, -18.0f, -18.0f);
    __hv_var_k_f(VOf(Bf5), 23.0f, 23.0f, 23.0f, 23.0f, 23.0f, 23.0f, 23.0f, 23.0f);
    __hv_mul_f(VIf(Bf2), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf3), VIf(Bf4), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf0), VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f);
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_tabwrite_stoppable_f(&sTabwrite_dtOA06Ri, VIf(Bf1));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_polynomials::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_polynomials::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
