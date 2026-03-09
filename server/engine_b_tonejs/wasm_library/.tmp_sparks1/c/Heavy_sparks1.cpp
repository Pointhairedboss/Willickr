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

#include "Heavy_sparks1.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_sparks1 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_sparks1_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_sparks1));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_sparks1(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_sparks1_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_sparks1));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_sparks1(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_sparks1_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_sparks1();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_sparks1::Heavy_sparks1(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_SGV61dpE, -100.0f, sampleRate);
  numBytes += sRPole_init(&sRPole_W3i6yULt);
  numBytes += sRPole_init(&sRPole_HVtQKBgG);
  numBytes += sRPole_init(&sRPole_IZ0U55zx);
  numBytes += sDel1_init(&sDel1_muBne6Eu);
  numBytes += sTabwrite_init(&sTabwrite_rA5oFaRI, &hTable_Ovk4XTR3);
  numBytes += sTabwrite_init(&sTabwrite_AVsLwLdO, &hTable_vC8rnniw);
  numBytes += sTabwrite_init(&sTabwrite_mpsDhAtv, &hTable_5sMpYNmV);
  numBytes += sRPole_init(&sRPole_HCeOCHeK);
  numBytes += sRPole_init(&sRPole_QsK9DAVs);
  numBytes += sRPole_init(&sRPole_IGZ5oC4v);
  numBytes += cRandom_init(&cRandom_SuomrmVr, -1700066447);
  numBytes += cSlice_init(&cSlice_jorbmrrf, 1, 1);
  numBytes += sVari_init(&sVari_a62orTAj, 0, 0, false);
  numBytes += cVar_init_f(&cVar_a8xA8XOb, 30.0f);
  numBytes += cBinop_init(&cBinop_xMr2DZrf, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_B28WTaWh, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_ile4bqFX, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_uOYL5zo5, 3.0f);
  numBytes += cBinop_init(&cBinop_Yi6NLAYc, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_zzUc3rJU, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_JyGAIWyL, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_3Cky9xh8, 3.0f);
  numBytes += cBinop_init(&cBinop_oF0gD4S8, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_bG4CSF4l, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_6SXzzG0k, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_WMEodz6D, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_lMln8v7c, 300.0f);
  numBytes += cBinop_init(&cBinop_LZwcROyp, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_6zg8Cd2I, 0.0f, 0.0f, false);
  numBytes += hTable_init(&hTable_Ovk4XTR3, 100);
  numBytes += cDelay_init(this, &cDelay_M95PKX6H, 0.0f);
  numBytes += cVar_init_s(&cVar_Xql09hiw, "A");
  numBytes += cSlice_init(&cSlice_Kb8L22Za, 1, 1);
  numBytes += cSlice_init(&cSlice_QOam4WXU, 1, 1);
  numBytes += cBinop_init(&cBinop_GqzCIVxf, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_BagOA9xa, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_Px1N2ud9, 0.0f);
  numBytes += cVar_init_f(&cVar_ccBGNSYX, 200.0f);
  numBytes += cBinop_init(&cBinop_dSpMYeYk, 0.0f); // __mul
  numBytes += hTable_init(&hTable_vC8rnniw, 100);
  numBytes += cDelay_init(this, &cDelay_3oUch8Al, 0.0f);
  numBytes += cVar_init_s(&cVar_xt4LPfd9, "B");
  numBytes += cSlice_init(&cSlice_Eu3bLyuN, 1, 1);
  numBytes += cSlice_init(&cSlice_H8wjqMR2, 1, 1);
  numBytes += cBinop_init(&cBinop_GHL9rfvP, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_hWSqYjJx, 0.0f); // __sub
  numBytes += hTable_init(&hTable_5sMpYNmV, 100);
  numBytes += cDelay_init(this, &cDelay_cjhQ5Mkw, 0.0f);
  numBytes += cVar_init_s(&cVar_yWBHAHNz, "C");
  numBytes += cSlice_init(&cSlice_FVKFFD6D, 1, 1);
  numBytes += cSlice_init(&cSlice_kQe9X6DR, 1, 1);
  numBytes += cBinop_init(&cBinop_rgQnwTAX, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_d7QRjK9v, 0.0f); // __sub
  numBytes += cRandom_init(&cRandom_K8hJT5R7, 91412463);
  numBytes += cSlice_init(&cSlice_opoknvYc, 1, 1);
  numBytes += sVari_init(&sVari_KIys9Mzu, 0, 0, false);
  numBytes += cVar_init_f(&cVar_5AMuUuoQ, 0.1f);
  numBytes += cBinop_init(&cBinop_lGwTbdc7, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_hcxSySvJ, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_igfdKqu0, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_TPiSkgvz, 0.1f);
  numBytes += cBinop_init(&cBinop_jBUDbrQS, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_yLh16ugo, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_O5QRGrVw, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_sparks1::~Heavy_sparks1() {
  hTable_free(&hTable_Ovk4XTR3);
  hTable_free(&hTable_vC8rnniw);
  hTable_free(&hTable_5sMpYNmV);
}

HvTable *Heavy_sparks1::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_Ovk4XTR3; // A
    case 0xD961DF96: return &hTable_vC8rnniw; // B
    case 0x7F1A5B02: return &hTable_5sMpYNmV; // C
    default: return nullptr;
  }
}

void Heavy_sparks1::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_nZAYo7pb_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_iTQog7KE_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_sparks1::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_sparks1::cSwitchcase_1NggNnye_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_jorbmrrf, 0, m, &cSlice_jorbmrrf_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_SuomrmVr, 0, m, &cRandom_SuomrmVr_sendMessage);
      break;
    }
  }
}

void Heavy_sparks1::cBinop_yWaklT4T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_qbwFq4h2_sendMessage);
}

void Heavy_sparks1::cUnop_qbwFq4h2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_3a1zLt13_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cRandom_SuomrmVr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_yWaklT4T_sendMessage);
}

void Heavy_sparks1::cSlice_jorbmrrf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_SuomrmVr, 1, m, &cRandom_SuomrmVr_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cMsg_3a1zLt13_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_a62orTAj, m);
}

void Heavy_sparks1::cVar_a8xA8XOb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xMr2DZrf, HV_BINOP_MULTIPLY, 0, m, &cBinop_xMr2DZrf_sendMessage);
}

void Heavy_sparks1::cMsg_86QhSULN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_V627o2yZ_sendMessage);
}

void Heavy_sparks1::cSystem_V627o2yZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_wNT68zic_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cBinop_xMr2DZrf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_wN2gzfdf_sendMessage);
}

void Heavy_sparks1::cBinop_pOdg35y1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xMr2DZrf, HV_BINOP_MULTIPLY, 1, m, &cBinop_xMr2DZrf_sendMessage);
}

void Heavy_sparks1::cMsg_wNT68zic_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_pOdg35y1_sendMessage);
}

void Heavy_sparks1::cBinop_wN2gzfdf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_vr6acgRQ_sendMessage);
}

void Heavy_sparks1::cBinop_vr6acgRQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_Xl2T8bUt_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_ile4bqFX, m);
}

void Heavy_sparks1::cBinop_Xl2T8bUt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_B28WTaWh, m);
}

void Heavy_sparks1::cVar_uOYL5zo5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Yi6NLAYc, HV_BINOP_MULTIPLY, 0, m, &cBinop_Yi6NLAYc_sendMessage);
}

void Heavy_sparks1::cMsg_kgZO27Fw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_du9FeVsH_sendMessage);
}

void Heavy_sparks1::cSystem_du9FeVsH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_eYJUOKNm_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cBinop_Yi6NLAYc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_ROkzlUGp_sendMessage);
}

void Heavy_sparks1::cBinop_aA2ju1mj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Yi6NLAYc, HV_BINOP_MULTIPLY, 1, m, &cBinop_Yi6NLAYc_sendMessage);
}

void Heavy_sparks1::cMsg_eYJUOKNm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_aA2ju1mj_sendMessage);
}

void Heavy_sparks1::cBinop_ROkzlUGp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_oqh0ExWh_sendMessage);
}

void Heavy_sparks1::cBinop_oqh0ExWh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_06YwPxOZ_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_JyGAIWyL, m);
}

void Heavy_sparks1::cBinop_06YwPxOZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_zzUc3rJU, m);
}

void Heavy_sparks1::cVar_3Cky9xh8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_oF0gD4S8, HV_BINOP_MULTIPLY, 0, m, &cBinop_oF0gD4S8_sendMessage);
}

void Heavy_sparks1::cMsg_Mu3tFzNj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_84hXiBZp_sendMessage);
}

void Heavy_sparks1::cSystem_84hXiBZp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_nZMxBDhx_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cBinop_oF0gD4S8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_uW6y21VK_sendMessage);
}

void Heavy_sparks1::cBinop_9Ds2hW8a_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_oF0gD4S8, HV_BINOP_MULTIPLY, 1, m, &cBinop_oF0gD4S8_sendMessage);
}

void Heavy_sparks1::cMsg_nZMxBDhx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_9Ds2hW8a_sendMessage);
}

void Heavy_sparks1::cBinop_uW6y21VK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_k4lJol4A_sendMessage);
}

void Heavy_sparks1::cBinop_k4lJol4A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_q5y9Nqv5_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_6SXzzG0k, m);
}

void Heavy_sparks1::cBinop_q5y9Nqv5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_bG4CSF4l, m);
}

void Heavy_sparks1::cBinop_OFBsFTl0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_bMf3eqNy_sendMessage);
}

void Heavy_sparks1::cBinop_bMf3eqNy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_Td9jo79W_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_8dDTGfWE_sendMessage);
}

void Heavy_sparks1::cVar_lMln8v7c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_1uzTX8Ee_sendMessage);
}

void Heavy_sparks1::cMsg_KzuiE9bI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_z64uc01b_sendMessage);
}

void Heavy_sparks1::cSystem_z64uc01b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LZwcROyp, HV_BINOP_DIVIDE, 1, m, &cBinop_LZwcROyp_sendMessage);
}

void Heavy_sparks1::cBinop_Td9jo79W_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_4DIOBouu_sendMessage);
}

void Heavy_sparks1::cBinop_4DIOBouu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_6zg8Cd2I, m);
}

void Heavy_sparks1::cMsg_JW4NUGeG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_YchwG2ID_sendMessage);
}

void Heavy_sparks1::cBinop_YchwG2ID_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_OFBsFTl0_sendMessage);
}

void Heavy_sparks1::cBinop_8dDTGfWE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_WMEodz6D, m);
}

void Heavy_sparks1::cBinop_1uzTX8Ee_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_OjEUUhBI_sendMessage);
}

void Heavy_sparks1::cBinop_OjEUUhBI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LZwcROyp, HV_BINOP_DIVIDE, 0, m, &cBinop_LZwcROyp_sendMessage);
}

void Heavy_sparks1::cBinop_LZwcROyp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_JW4NUGeG_sendMessage(_c, 0, m);
}

void Heavy_sparks1::hTable_Ovk4XTR3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_sparks1::cSwitchcase_Q0EK0Ei0_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_QOam4WXU, 0, m, &cSlice_QOam4WXU_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_UpWfvdgJ_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Kb8L22Za, 0, m, &cSlice_Kb8L22Za_sendMessage);
      break;
    }
    default: {
      cMsg_ZdcjMvvc_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_sparks1::cDelay_M95PKX6H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_M95PKX6H, m);
  cMsg_UpWfvdgJ_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cVar_Xql09hiw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_wRduhgCa_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cSlice_Kb8L22Za_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_rA5oFaRI, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_Xql09hiw, 0, m, &cVar_Xql09hiw_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cSlice_QOam4WXU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_rA5oFaRI, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_BagOA9xa, HV_BINOP_SUBTRACT, 0, m, &cBinop_BagOA9xa_sendMessage);
      break;
    }
    case 1: {
      cMsg_4KXXiHRV_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cBinop_dkQASNnV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GqzCIVxf, HV_BINOP_DIVIDE, 1, m, &cBinop_GqzCIVxf_sendMessage);
}

void Heavy_sparks1::cBinop_GqzCIVxf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_8UE4pSH3_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_M95PKX6H, 1, m, &cDelay_M95PKX6H_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_M95PKX6H, 0, m, &cDelay_M95PKX6H_sendMessage);
}

void Heavy_sparks1::cMsg_ZdcjMvvc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_rA5oFaRI, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_BagOA9xa, HV_BINOP_SUBTRACT, 0, m, &cBinop_BagOA9xa_sendMessage);
}

void Heavy_sparks1::cSystem_TU9fnil7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BagOA9xa, HV_BINOP_SUBTRACT, 1, m, &cBinop_BagOA9xa_sendMessage);
}

void Heavy_sparks1::cMsg_wRduhgCa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_TU9fnil7_sendMessage);
}

void Heavy_sparks1::cBinop_BagOA9xa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_P1E17mHV_sendMessage);
}

void Heavy_sparks1::cBinop_P1E17mHV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GqzCIVxf, HV_BINOP_DIVIDE, 0, m, &cBinop_GqzCIVxf_sendMessage);
}

void Heavy_sparks1::cMsg_8UE4pSH3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_M95PKX6H, 0, m, &cDelay_M95PKX6H_sendMessage);
}

void Heavy_sparks1::cMsg_UpWfvdgJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_rA5oFaRI, 1, m, NULL);
}

void Heavy_sparks1::cMsg_sWX7LNl4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_QVL7rSND_sendMessage);
}

void Heavy_sparks1::cSystem_QVL7rSND_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_dkQASNnV_sendMessage);
}

void Heavy_sparks1::cMsg_4KXXiHRV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_rA5oFaRI, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_BagOA9xa, HV_BINOP_SUBTRACT, 0, m, &cBinop_BagOA9xa_sendMessage);
}

void Heavy_sparks1::cCast_5ra9YbPc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_4LTBNCvJ_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_sparks1::cSwitchcase_4LTBNCvJ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_HAnjkGrC_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_HAnjkGrC_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MSZAreUi_sendMessage);
      break;
    }
  }
}

void Heavy_sparks1::cDelay_Px1N2ud9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_Px1N2ud9, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Px1N2ud9, 0, m, &cDelay_Px1N2ud9_sendMessage);
  cSwitchcase_Q0EK0Ei0_onMessage(_c, NULL, 0, m, NULL);
  cSend_5cBJ4t5M_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cCast_MSZAreUi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_HAnjkGrC_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Px1N2ud9, 0, m, &cDelay_Px1N2ud9_sendMessage);
  cSwitchcase_Q0EK0Ei0_onMessage(_c, NULL, 0, m, NULL);
  cSend_5cBJ4t5M_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cMsg_WwWOrjUe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_BTVuIWs0_sendMessage);
}

void Heavy_sparks1::cSystem_BTVuIWs0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_2bHMM2gu_sendMessage);
}

void Heavy_sparks1::cVar_ccBGNSYX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dSpMYeYk, HV_BINOP_MULTIPLY, 0, m, &cBinop_dSpMYeYk_sendMessage);
}

void Heavy_sparks1::cMsg_HAnjkGrC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_Px1N2ud9, 0, m, &cDelay_Px1N2ud9_sendMessage);
}

void Heavy_sparks1::cBinop_qDfw3C5t_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_Px1N2ud9, 2, m, &cDelay_Px1N2ud9_sendMessage);
}

void Heavy_sparks1::cBinop_2bHMM2gu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dSpMYeYk, HV_BINOP_MULTIPLY, 1, m, &cBinop_dSpMYeYk_sendMessage);
}

void Heavy_sparks1::cBinop_dSpMYeYk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_qDfw3C5t_sendMessage);
}

void Heavy_sparks1::cSend_5cBJ4t5M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_iTQog7KE_sendMessage(_c, 0, m);
}

void Heavy_sparks1::hTable_vC8rnniw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_sparks1::cSwitchcase_UFQr19ny_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_H8wjqMR2, 0, m, &cSlice_H8wjqMR2_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_3nzRdeh3_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Eu3bLyuN, 0, m, &cSlice_Eu3bLyuN_sendMessage);
      break;
    }
    default: {
      cMsg_Bglf3ydV_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_sparks1::cDelay_3oUch8Al_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_3oUch8Al, m);
  cMsg_3nzRdeh3_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cVar_xt4LPfd9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_X7ncficS_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cSlice_Eu3bLyuN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AVsLwLdO, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_xt4LPfd9, 0, m, &cVar_xt4LPfd9_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cSlice_H8wjqMR2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AVsLwLdO, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_hWSqYjJx, HV_BINOP_SUBTRACT, 0, m, &cBinop_hWSqYjJx_sendMessage);
      break;
    }
    case 1: {
      cMsg_DIFFx5Eb_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cBinop_fCqT1K8S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GHL9rfvP, HV_BINOP_DIVIDE, 1, m, &cBinop_GHL9rfvP_sendMessage);
}

void Heavy_sparks1::cBinop_GHL9rfvP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ubdaqBv6_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3oUch8Al, 1, m, &cDelay_3oUch8Al_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3oUch8Al, 0, m, &cDelay_3oUch8Al_sendMessage);
}

void Heavy_sparks1::cMsg_Bglf3ydV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AVsLwLdO, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hWSqYjJx, HV_BINOP_SUBTRACT, 0, m, &cBinop_hWSqYjJx_sendMessage);
}

void Heavy_sparks1::cSystem_MPby37Z0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hWSqYjJx, HV_BINOP_SUBTRACT, 1, m, &cBinop_hWSqYjJx_sendMessage);
}

void Heavy_sparks1::cMsg_X7ncficS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_MPby37Z0_sendMessage);
}

void Heavy_sparks1::cBinop_hWSqYjJx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_2BtQZQfm_sendMessage);
}

void Heavy_sparks1::cBinop_2BtQZQfm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GHL9rfvP, HV_BINOP_DIVIDE, 0, m, &cBinop_GHL9rfvP_sendMessage);
}

void Heavy_sparks1::cMsg_ubdaqBv6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_3oUch8Al, 0, m, &cDelay_3oUch8Al_sendMessage);
}

void Heavy_sparks1::cMsg_3nzRdeh3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AVsLwLdO, 1, m, NULL);
}

void Heavy_sparks1::cMsg_Pan4SPfl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_0M8ZsPKl_sendMessage);
}

void Heavy_sparks1::cSystem_0M8ZsPKl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_fCqT1K8S_sendMessage);
}

void Heavy_sparks1::cMsg_DIFFx5Eb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_AVsLwLdO, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hWSqYjJx, HV_BINOP_SUBTRACT, 0, m, &cBinop_hWSqYjJx_sendMessage);
}

void Heavy_sparks1::hTable_5sMpYNmV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_sparks1::cSwitchcase_RnVGGm8m_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_kQe9X6DR, 0, m, &cSlice_kQe9X6DR_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_0QxsEqA0_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_FVKFFD6D, 0, m, &cSlice_FVKFFD6D_sendMessage);
      break;
    }
    default: {
      cMsg_t4rVQ8Gs_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_sparks1::cDelay_cjhQ5Mkw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_cjhQ5Mkw, m);
  cMsg_0QxsEqA0_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cVar_yWBHAHNz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_pFxQuGg7_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cSlice_FVKFFD6D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_mpsDhAtv, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_yWBHAHNz, 0, m, &cVar_yWBHAHNz_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cSlice_kQe9X6DR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_mpsDhAtv, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_d7QRjK9v, HV_BINOP_SUBTRACT, 0, m, &cBinop_d7QRjK9v_sendMessage);
      break;
    }
    case 1: {
      cMsg_GanpyRFD_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cBinop_5Sa0cuN2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_rgQnwTAX, HV_BINOP_DIVIDE, 1, m, &cBinop_rgQnwTAX_sendMessage);
}

void Heavy_sparks1::cBinop_rgQnwTAX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_KSLeZ21H_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_cjhQ5Mkw, 1, m, &cDelay_cjhQ5Mkw_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_cjhQ5Mkw, 0, m, &cDelay_cjhQ5Mkw_sendMessage);
}

void Heavy_sparks1::cMsg_t4rVQ8Gs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_mpsDhAtv, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_d7QRjK9v, HV_BINOP_SUBTRACT, 0, m, &cBinop_d7QRjK9v_sendMessage);
}

void Heavy_sparks1::cSystem_SZEBuFMh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_d7QRjK9v, HV_BINOP_SUBTRACT, 1, m, &cBinop_d7QRjK9v_sendMessage);
}

void Heavy_sparks1::cMsg_pFxQuGg7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_SZEBuFMh_sendMessage);
}

void Heavy_sparks1::cBinop_d7QRjK9v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_oc4Wok1Z_sendMessage);
}

void Heavy_sparks1::cBinop_oc4Wok1Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_rgQnwTAX, HV_BINOP_DIVIDE, 0, m, &cBinop_rgQnwTAX_sendMessage);
}

void Heavy_sparks1::cMsg_KSLeZ21H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_cjhQ5Mkw, 0, m, &cDelay_cjhQ5Mkw_sendMessage);
}

void Heavy_sparks1::cMsg_0QxsEqA0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_mpsDhAtv, 1, m, NULL);
}

void Heavy_sparks1::cMsg_4z2ntFpa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_YN2tDKuk_sendMessage);
}

void Heavy_sparks1::cSystem_YN2tDKuk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_5Sa0cuN2_sendMessage);
}

void Heavy_sparks1::cMsg_GanpyRFD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_mpsDhAtv, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_d7QRjK9v, HV_BINOP_SUBTRACT, 0, m, &cBinop_d7QRjK9v_sendMessage);
}

void Heavy_sparks1::cSwitchcase_Pnq8Sot7_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_opoknvYc, 0, m, &cSlice_opoknvYc_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_K8hJT5R7, 0, m, &cRandom_K8hJT5R7_sendMessage);
      break;
    }
  }
}

void Heavy_sparks1::cBinop_LWIGsjS3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_WL7DyUm0_sendMessage);
}

void Heavy_sparks1::cUnop_WL7DyUm0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_fULtvESV_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cRandom_K8hJT5R7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_LWIGsjS3_sendMessage);
}

void Heavy_sparks1::cSlice_opoknvYc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_K8hJT5R7, 1, m, &cRandom_K8hJT5R7_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_sparks1::cMsg_fULtvESV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_KIys9Mzu, m);
}

void Heavy_sparks1::cVar_5AMuUuoQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lGwTbdc7, HV_BINOP_MULTIPLY, 0, m, &cBinop_lGwTbdc7_sendMessage);
}

void Heavy_sparks1::cMsg_QKKfvUrP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_WYWMu679_sendMessage);
}

void Heavy_sparks1::cSystem_WYWMu679_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_BGpIVGlG_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cBinop_lGwTbdc7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_ecnKwh7N_sendMessage);
}

void Heavy_sparks1::cBinop_EA6Hwn2j_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lGwTbdc7, HV_BINOP_MULTIPLY, 1, m, &cBinop_lGwTbdc7_sendMessage);
}

void Heavy_sparks1::cMsg_BGpIVGlG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_EA6Hwn2j_sendMessage);
}

void Heavy_sparks1::cBinop_ecnKwh7N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_hmEmEeba_sendMessage);
}

void Heavy_sparks1::cBinop_hmEmEeba_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_XgfxVQpB_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_igfdKqu0, m);
}

void Heavy_sparks1::cBinop_XgfxVQpB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_hcxSySvJ, m);
}

void Heavy_sparks1::cVar_TPiSkgvz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jBUDbrQS, HV_BINOP_MULTIPLY, 0, m, &cBinop_jBUDbrQS_sendMessage);
}

void Heavy_sparks1::cMsg_ISl9PwSJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_ZfvyIMgW_sendMessage);
}

void Heavy_sparks1::cSystem_ZfvyIMgW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_kpuMNnIr_sendMessage(_c, 0, m);
}

void Heavy_sparks1::cBinop_jBUDbrQS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_kRUBi1XL_sendMessage);
}

void Heavy_sparks1::cBinop_TFFsEAWk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jBUDbrQS, HV_BINOP_MULTIPLY, 1, m, &cBinop_jBUDbrQS_sendMessage);
}

void Heavy_sparks1::cMsg_kpuMNnIr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_TFFsEAWk_sendMessage);
}

void Heavy_sparks1::cBinop_kRUBi1XL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_aArakkfr_sendMessage);
}

void Heavy_sparks1::cBinop_aArakkfr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_L57UnDAK_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_O5QRGrVw, m);
}

void Heavy_sparks1::cBinop_L57UnDAK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_yLh16ugo, m);
}

void Heavy_sparks1::cReceive_nZAYo7pb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Xql09hiw, 0, m, &cVar_Xql09hiw_sendMessage);
  cMsg_sWX7LNl4_sendMessage(_c, 0, m);
  cMsg_UpWfvdgJ_sendMessage(_c, 0, m);
  cMsg_WwWOrjUe_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_ccBGNSYX, 0, m, &cVar_ccBGNSYX_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_xt4LPfd9, 0, m, &cVar_xt4LPfd9_sendMessage);
  cMsg_Pan4SPfl_sendMessage(_c, 0, m);
  cMsg_3nzRdeh3_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_yWBHAHNz, 0, m, &cVar_yWBHAHNz_sendMessage);
  cMsg_4z2ntFpa_sendMessage(_c, 0, m);
  cMsg_0QxsEqA0_sendMessage(_c, 0, m);
  cSwitchcase_1NggNnye_onMessage(_c, NULL, 0, m, NULL);
  cMsg_86QhSULN_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_a8xA8XOb, 0, m, &cVar_a8xA8XOb_sendMessage);
  cMsg_kgZO27Fw_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_uOYL5zo5, 0, m, &cVar_uOYL5zo5_sendMessage);
  cMsg_Mu3tFzNj_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_3Cky9xh8, 0, m, &cVar_3Cky9xh8_sendMessage);
  cMsg_KzuiE9bI_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_lMln8v7c, 0, m, &cVar_lMln8v7c_sendMessage);
  cSwitchcase_4LTBNCvJ_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_Pnq8Sot7_onMessage(_c, NULL, 0, m, NULL);
  cMsg_QKKfvUrP_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_5AMuUuoQ, 0, m, &cVar_5AMuUuoQ_sendMessage);
  cMsg_ISl9PwSJ_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_TPiSkgvz, 0, m, &cVar_TPiSkgvz_sendMessage);
}

void Heavy_sparks1::cReceive_iTQog7KE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_UFQr19ny_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_RnVGGm8m_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_sparks1::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6, Bf7, Bf8, Bf9;
  hv_bufferi_t Bi0, Bi1;

  // input and output vars
  hv_bufferf_t O0, O1;

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

    

    // zero output buffers
    __hv_zero_f(VOf(O0));
    __hv_zero_f(VOf(O1));

    // process all signal functions
    __hv_phasor_k_f(&sPhasor_SGV61dpE, VOf(Bf0));
    __hv_varread_i(&sVari_KIys9Mzu, VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_cast_if(VIi(Bi1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_varwrite_i(&sVari_KIys9Mzu, VIi(Bi1));
    __hv_varread_f(&sVarf_O5QRGrVw, VOf(Bf1));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_yLh16ugo, VOf(Bf2));
    __hv_rpole_f(&sRPole_W3i6yULt, VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_igfdKqu0, VOf(Bf1));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_hcxSySvJ, VOf(Bf2));
    __hv_rpole_f(&sRPole_HVtQKBgG, VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_zero_f(VOf(Bf1));
    __hv_max_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 700.0f, 700.0f, 700.0f, 700.0f, 700.0f, 700.0f, 700.0f, 700.0f);
    __hv_var_k_f(VOf(Bf3), 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
    __hv_fma_f(VIf(Bf1), VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_max_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f);
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_sub_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f);
    __hv_add_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f);
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_floor_f(VIf(Bf1), VOf(Bf2));
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf2));
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf2), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf2), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf7), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf8), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf9), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf4), VIf(Bf9), VOf(Bf9));
    __hv_sub_f(VIf(Bf1), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf5), VIf(Bf8), VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf8), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf6), VIf(Bf8), VOf(Bf8));
    __hv_sub_f(VIf(Bf9), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf2), VIf(Bf7), VIf(Bf8), VOf(Bf8));
    __hv_mul_f(VIf(Bf8), VIf(Bf3), VOf(Bf8));
    __hv_varread_f(&sVarf_WMEodz6D, VOf(Bf7));
    __hv_rpole_f(&sRPole_IZ0U55zx, VIf(Bf8), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf2), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_muBne6Eu, VIf(Bf7), VOf(Bf9));
    __hv_mul_f(VIf(Bf9), VIf(Bf2), VOf(Bf2));
    __hv_sub_f(VIf(Bf7), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_6zg8Cd2I, VOf(Bf7));
    __hv_mul_f(VIf(Bf2), VIf(Bf7), VOf(Bf7));
    __hv_tabwrite_stoppable_f(&sTabwrite_rA5oFaRI, VIf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_AVsLwLdO, VIf(Bf3));
    __hv_tabwrite_stoppable_f(&sTabwrite_mpsDhAtv, VIf(Bf8));
    __hv_varread_i(&sVari_a62orTAj, VOi(Bi1));
    __hv_var_k_i(VOi(Bi0), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi1), VIi(Bi0), VOi(Bi0));
    __hv_cast_if(VIi(Bi0), VOf(Bf8));
    __hv_var_k_f(VOf(Bf3), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf8), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_i(&sVari_a62orTAj, VIi(Bi0));
    __hv_varread_f(&sVarf_JyGAIWyL, VOf(Bf8));
    __hv_mul_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_varread_f(&sVarf_zzUc3rJU, VOf(Bf3));
    __hv_rpole_f(&sRPole_HCeOCHeK, VIf(Bf8), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_6SXzzG0k, VOf(Bf8));
    __hv_mul_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_varread_f(&sVarf_bG4CSF4l, VOf(Bf3));
    __hv_rpole_f(&sRPole_QsK9DAVs, VIf(Bf8), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf8), 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f);
    __hv_max_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf3), 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f, 0.0008f);
    __hv_sub_f(VIf(Bf8), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf8), 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f, 1000000000.0f);
    __hv_mul_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf8), VIf(Bf3), VOf(Bf3));
    __hv_zero_f(VOf(Bf8));
    __hv_max_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_varread_f(&sVarf_ile4bqFX, VOf(Bf3));
    __hv_mul_f(VIf(Bf8), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_B28WTaWh, VOf(Bf8));
    __hv_rpole_f(&sRPole_IGZ5oC4v, VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_mul_f(VIf(Bf7), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf7), 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f);
    __hv_mul_f(VIf(Bf8), VIf(Bf7), VOf(Bf7));
    __hv_add_f(VIf(Bf7), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf7), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_sparks1::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float **const bOut = reinterpret_cast<float **>(hv_alloca(2*sizeof(float *)));
  bOut[0] = outputBuffers+(0*n4);
  bOut[1] = outputBuffers+(1*n4);

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_sparks1::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float *const bOut = reinterpret_cast<float *>(hv_alloca(2*n4*sizeof(float)));

  int n = processInline(bIn, bOut, n4);

  // interleave the heavy output into the output buffer
  #if HV_SIMD_AVX
  for (int i = 0, j = 0; j < n4; j += 8, i += 16) {
    __m256 x = _mm256_load_ps(bOut+j);    // LLLLLLLL
    __m256 y = _mm256_load_ps(bOut+n4+j); // RRRRRRRR
    __m256 a = _mm256_unpacklo_ps(x, y);  // LRLRLRLR
    __m256 b = _mm256_unpackhi_ps(x, y);  // LRLRLRLR
    _mm256_store_ps(outputBuffers+i, a);
    _mm256_store_ps(outputBuffers+8+i, b);
  }
  #elif HV_SIMD_SSE
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    __m128 x = _mm_load_ps(bOut+j);    // LLLL
    __m128 y = _mm_load_ps(bOut+n4+j); // RRRR
    __m128 a = _mm_unpacklo_ps(x, y);  // LRLR
    __m128 b = _mm_unpackhi_ps(x, y);  // LRLR
    _mm_store_ps(outputBuffers+i, a);
    _mm_store_ps(outputBuffers+4+i, b);
  }
  #elif HV_SIMD_NEON
  // https://community.arm.com/groups/processors/blog/2012/03/13/coding-for-neon--part-5-rearranging-vectors
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    float32x4_t x = vld1q_f32(bOut+j);
    float32x4_t y = vld1q_f32(bOut+n4+j);
    float32x4x2_t z = {x, y};
    vst2q_f32(outputBuffers+i, z); // interleave and store
  }
  #else // HV_SIMD_NONE
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < n4; ++j) {
      outputBuffers[i+2*j] = bOut[i*n4+j];
    }
  }
  #endif

  return n;
}
