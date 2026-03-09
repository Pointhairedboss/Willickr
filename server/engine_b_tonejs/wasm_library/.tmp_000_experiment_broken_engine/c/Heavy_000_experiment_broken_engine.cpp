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

#include "Heavy_000_experiment_broken_engine.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_000_experiment_broken_engine *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_000_experiment_broken_engine_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_000_experiment_broken_engine));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_000_experiment_broken_engine(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_000_experiment_broken_engine_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_000_experiment_broken_engine));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_000_experiment_broken_engine(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_000_experiment_broken_engine_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_000_experiment_broken_engine();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_000_experiment_broken_engine::Heavy_000_experiment_broken_engine(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sBiquad_k_init(&sBiquad_k_vGu1wr0T, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sPhasor_k_init(&sPhasor_GuywKxJc, 9.0f, sampleRate);
  numBytes += sRPole_init(&sRPole_Q1B2gn8v);
  numBytes += sDel1_init(&sDel1_WCa5STtc);
  numBytes += sRPole_init(&sRPole_An9BZzhy);
  numBytes += sRPole_init(&sRPole_xZcoyoIn);
  numBytes += sDel1_init(&sDel1_mPTONbHq);
  numBytes += sBiquad_k_init(&sBiquad_k_FxC68ObO, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sBiquad_k_init(&sBiquad_k_AgTiC5Gv, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sBiquad_k_init(&sBiquad_k_tzqzTTOk, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sBiquad_k_init(&sBiquad_k_Cr3Mw7j0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sRPole_init(&sRPole_rFJviXIV);
  numBytes += sDel1_init(&sDel1_RqC7y7mx);
  numBytes += cRandom_init(&cRandom_5nWZQcDN, -81238928);
  numBytes += cSlice_init(&cSlice_234COR5G, 1, 1);
  numBytes += sVari_init(&sVari_O3Zehwxf, 0, 0, false);
  numBytes += cVar_init_f(&cVar_a7Pr3ynb, 30.0f);
  numBytes += cBinop_init(&cBinop_5FwpCmkn, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_zXyLoEmy, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_cmtoTfAD, 0.0f, 0.0f, false);
  numBytes += cRandom_init(&cRandom_YHzPfeyg, -916358097);
  numBytes += cSlice_init(&cSlice_ZWWPubRD, 1, 1);
  numBytes += sVari_init(&sVari_wFAtrzqu, 0, 0, false);
  numBytes += sVarf_init(&sVarf_b6QrnJnd, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_K0xAkcsu, 1000.0f);
  numBytes += cBinop_init(&cBinop_9Xj146vh, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_FMZ2e5hY, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_2BcUSbcd, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_EPM0uxY1, 100.0f);
  numBytes += cBinop_init(&cBinop_6zKqgPit, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_ojPk0OLa, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_gqHo07xE, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_Nf6V4irR, 10.0f);
  numBytes += cBinop_init(&cBinop_EMtpmEzK, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_pPksuo0m, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_fe1llnWZ, 9.0f);
  numBytes += cVar_init_f(&cVar_JmTYoMOq, 15.0f);
  numBytes += cBinop_init(&cBinop_yX2EssM4, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_8fAAbmIs, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_DaOAlcWb, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_eavcgE79, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_HnNq09mi, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_NqcmPKzG, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_vxtzZofc, 1.0f);
  numBytes += cVar_init_f(&cVar_phhDZezP, 590.0f);
  numBytes += cVar_init_f(&cVar_gZsjGG8m, 4.0f);
  numBytes += cBinop_init(&cBinop_H06Xrfrv, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_qw9h4een, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_WMw88fw7, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_GUm4OA1w, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_fwnrITos, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_oRs7XSZz, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_5Jcr7Wau, 470.0f);
  numBytes += cVar_init_f(&cVar_8pT5ytYD, 8.0f);
  numBytes += cBinop_init(&cBinop_BA9W1ivF, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_1cyox1Ky, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_1x8ePwSC, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_6yYfGNtQ, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_f8qf0c1B, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_g79cFRpE, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_SFPCAMqc, 780.0f);
  numBytes += cVar_init_f(&cVar_mJWHiWwD, 9.0f);
  numBytes += cBinop_init(&cBinop_05wGDoPT, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_h2ejVXyR, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_B4XKyIoc, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_vj5qxOm9, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_lw3OldBr, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_xCjfByKK, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_bcIWuHyQ, 1024.0f);
  numBytes += cVar_init_f(&cVar_KK7wIYVa, 10.0f);
  numBytes += cBinop_init(&cBinop_hpglZouU, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_BfMPV9ra, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_L5A47ckl, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_uOl04jYd, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_WO9wq9ym, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_09ITJWZ5, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_49zLxcfh, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_ySe8QKAd, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_000_experiment_broken_engine::~Heavy_000_experiment_broken_engine() {
  // nothing to free
}

HvTable *Heavy_000_experiment_broken_engine::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_000_experiment_broken_engine::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_f4a3q2gU_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_000_experiment_broken_engine::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_000_experiment_broken_engine::cSwitchcase_v6XOwBbk_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_234COR5G, 0, m, &cSlice_234COR5G_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_5nWZQcDN, 0, m, &cRandom_5nWZQcDN_sendMessage);
      break;
    }
  }
}

void Heavy_000_experiment_broken_engine::cBinop_T3D9WP0T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_SPm4cHpd_sendMessage);
}

void Heavy_000_experiment_broken_engine::cUnop_SPm4cHpd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_qM8qsvLa_sendMessage(_c, 0, m);
}

void Heavy_000_experiment_broken_engine::cRandom_5nWZQcDN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_T3D9WP0T_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSlice_234COR5G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_5nWZQcDN, 1, m, &cRandom_5nWZQcDN_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_000_experiment_broken_engine::cMsg_qM8qsvLa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_O3Zehwxf, m);
}

void Heavy_000_experiment_broken_engine::cVar_a7Pr3ynb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_5FwpCmkn, HV_BINOP_MULTIPLY, 0, m, &cBinop_5FwpCmkn_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_nBaLG8DT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_RPCLfPWr_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_RPCLfPWr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_h5Keofm6_sendMessage(_c, 0, m);
}

void Heavy_000_experiment_broken_engine::cBinop_5FwpCmkn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_8ljSdYn1_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_bnjozLQI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_5FwpCmkn, HV_BINOP_MULTIPLY, 1, m, &cBinop_5FwpCmkn_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_h5Keofm6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_bnjozLQI_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_8ljSdYn1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_iKHPnr5V_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_iKHPnr5V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_UKMVkzDq_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_cmtoTfAD, m);
}

void Heavy_000_experiment_broken_engine::cBinop_UKMVkzDq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_zXyLoEmy, m);
}

void Heavy_000_experiment_broken_engine::cSwitchcase_h9VMBtjC_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_ZWWPubRD, 0, m, &cSlice_ZWWPubRD_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_YHzPfeyg, 0, m, &cRandom_YHzPfeyg_sendMessage);
      break;
    }
  }
}

void Heavy_000_experiment_broken_engine::cBinop_ly3Cleuz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_12yt8k65_sendMessage);
}

void Heavy_000_experiment_broken_engine::cUnop_12yt8k65_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_90VZULAM_sendMessage(_c, 0, m);
}

void Heavy_000_experiment_broken_engine::cRandom_YHzPfeyg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_ly3Cleuz_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSlice_ZWWPubRD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_YHzPfeyg, 1, m, &cRandom_YHzPfeyg_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_000_experiment_broken_engine::cMsg_90VZULAM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_wFAtrzqu, m);
}

void Heavy_000_experiment_broken_engine::cBinop_ZeltXdYl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_eO82OYwo_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_eO82OYwo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_KUCbjdQq_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_zZd7UdyF_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_K0xAkcsu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_LMijW9t6_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_bV4CI3E4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_61g9Ad0K_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_61g9Ad0K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_9Xj146vh, HV_BINOP_DIVIDE, 1, m, &cBinop_9Xj146vh_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_KUCbjdQq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_2HZSzdqP_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_2HZSzdqP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_FMZ2e5hY, m);
}

void Heavy_000_experiment_broken_engine::cMsg_wZ5c7iFf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_d5MT1BRr_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_d5MT1BRr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_ZeltXdYl_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_zZd7UdyF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_b6QrnJnd, m);
}

void Heavy_000_experiment_broken_engine::cBinop_LMijW9t6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_V4YMauBh_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_V4YMauBh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_9Xj146vh, HV_BINOP_DIVIDE, 0, m, &cBinop_9Xj146vh_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_9Xj146vh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_wZ5c7iFf_sendMessage(_c, 0, m);
}

void Heavy_000_experiment_broken_engine::cBinop_w1hE4Sf7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_naBk8SXt_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_naBk8SXt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_GeeJoa8H_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_8oXV92kJ_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_EPM0uxY1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_3XUKeG8E_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_ToZ0IIPU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_fZ7LknsL_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_fZ7LknsL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6zKqgPit, HV_BINOP_DIVIDE, 1, m, &cBinop_6zKqgPit_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_GeeJoa8H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_oFVmAFTI_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_oFVmAFTI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ojPk0OLa, m);
}

void Heavy_000_experiment_broken_engine::cMsg_UFaUmt1Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_DCoUvz6k_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_DCoUvz6k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_w1hE4Sf7_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_8oXV92kJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_2BcUSbcd, m);
}

void Heavy_000_experiment_broken_engine::cBinop_3XUKeG8E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_R7LwDtL7_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_R7LwDtL7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6zKqgPit, HV_BINOP_DIVIDE, 0, m, &cBinop_6zKqgPit_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_6zKqgPit_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_UFaUmt1Q_sendMessage(_c, 0, m);
}

void Heavy_000_experiment_broken_engine::cBinop_CVA13iVy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_3fEdOoEe_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_3fEdOoEe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_ARY6I290_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_8fRnBt7u_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_Nf6V4irR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_cHSGcu8B_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_2SMrRWpt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_QWM9Ayp0_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_QWM9Ayp0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_EMtpmEzK, HV_BINOP_DIVIDE, 1, m, &cBinop_EMtpmEzK_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_ARY6I290_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_mrDzd98p_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_mrDzd98p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_pPksuo0m, m);
}

void Heavy_000_experiment_broken_engine::cMsg_XnN2VOQj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_0GhuiCaU_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_0GhuiCaU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_CVA13iVy_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_8fRnBt7u_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_gqHo07xE, m);
}

void Heavy_000_experiment_broken_engine::cBinop_cHSGcu8B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_rHMariRo_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_rHMariRo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_EMtpmEzK, HV_BINOP_DIVIDE, 0, m, &cBinop_EMtpmEzK_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_EMtpmEzK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_XnN2VOQj_sendMessage(_c, 0, m);
}

void Heavy_000_experiment_broken_engine::cMsg_MG8hzyW0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_ElS3KQXw_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_ElS3KQXw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_yX2EssM4, HV_BINOP_DIVIDE, 1, m, &cBinop_yX2EssM4_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_fe1llnWZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_P1H8LnlX_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_JmTYoMOq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_N5P7faUc_sendMessage);
}

void Heavy_000_experiment_broken_engine::cUnop_eTog3xFP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_cdV9ObqW_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_yX2EssM4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_eavcgE79, HV_BINOP_MULTIPLY, 1, m, &cBinop_eavcgE79_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_eTog3xFP_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_8fAAbmIs, HV_BINOP_DIVIDE, 0, m, &cBinop_8fAAbmIs_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_P1H8LnlX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_yX2EssM4, HV_BINOP_DIVIDE, 0, m, &cBinop_yX2EssM4_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_8fAAbmIs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_eyRaYZUp_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_EEgG7SLT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_DS95vVZ6_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_DS95vVZ6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_EjQnJU0l_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_DaOAlcWb, HV_BINOP_MULTIPLY, 0, m, &cBinop_DaOAlcWb_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_eavcgE79, HV_BINOP_MULTIPLY, 0, m, &cBinop_eavcgE79_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_cdV9ObqW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_DaOAlcWb, HV_BINOP_MULTIPLY, 1, m, &cBinop_DaOAlcWb_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_DaOAlcWb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_mtiJeyBK_sendMessage);
}

void Heavy_000_experiment_broken_engine::cCast_O0o2xfzT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_fe1llnWZ, 0, m, &cVar_fe1llnWZ_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_bCkag7k9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_KWClFaAh_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_KWClFaAh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_vGu1wr0T, 5, m);
}

void Heavy_000_experiment_broken_engine::cBinop_mtiJeyBK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_vGu1wr0T, 4, m);
}

void Heavy_000_experiment_broken_engine::cBinop_40VqsAEw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_NqcmPKzG, HV_BINOP_MULTIPLY, 0, m, &cBinop_NqcmPKzG_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_eavcgE79_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_HnNq09mi, HV_BINOP_ADD, 1, m, &cBinop_HnNq09mi_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_EjQnJU0l_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_bCkag7k9_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_HnNq09mi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_NqcmPKzG, HV_BINOP_MULTIPLY, 1, m, &cBinop_NqcmPKzG_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_NqcmPKzG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_vGu1wr0T, 1, m);
}

void Heavy_000_experiment_broken_engine::cBinop_N5P7faUc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8fAAbmIs, HV_BINOP_DIVIDE, 1, m, &cBinop_8fAAbmIs_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_eyRaYZUp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_EEgG7SLT_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_HnNq09mi, HV_BINOP_ADD, 0, m, &cBinop_HnNq09mi_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_40VqsAEw_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_vxtzZofc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_TyZQbpZZ_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_2ugXq8xf_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_49zLxcfh, m);
}

void Heavy_000_experiment_broken_engine::cBinop_TyZQbpZZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_vxtzZofc, 1, m, &cVar_vxtzZofc_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_EP6lfuvw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oCItwuPF_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_oCItwuPF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_H06Xrfrv, HV_BINOP_DIVIDE, 1, m, &cBinop_H06Xrfrv_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_phhDZezP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_3izcfcJE_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_gZsjGG8m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_7Dgel7c1_sendMessage);
}

void Heavy_000_experiment_broken_engine::cUnop_1kMXPiX6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_FetmbTOA_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_H06Xrfrv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GUm4OA1w, HV_BINOP_MULTIPLY, 1, m, &cBinop_GUm4OA1w_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_1kMXPiX6_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_qw9h4een, HV_BINOP_DIVIDE, 0, m, &cBinop_qw9h4een_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_3izcfcJE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_H06Xrfrv, HV_BINOP_DIVIDE, 0, m, &cBinop_H06Xrfrv_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_qw9h4een_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_WgtTBnbs_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_MaRIBQ8D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_4HBvcxdR_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_4HBvcxdR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_dXJYD3Rx_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_WMw88fw7, HV_BINOP_MULTIPLY, 0, m, &cBinop_WMw88fw7_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_GUm4OA1w, HV_BINOP_MULTIPLY, 0, m, &cBinop_GUm4OA1w_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_FetmbTOA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_WMw88fw7, HV_BINOP_MULTIPLY, 1, m, &cBinop_WMw88fw7_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_WMw88fw7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_LrDndiKG_sendMessage);
}

void Heavy_000_experiment_broken_engine::cCast_Fm5reskv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_phhDZezP, 0, m, &cVar_phhDZezP_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_e9aAkm0b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_9h53m92m_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_9h53m92m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_FxC68ObO, 5, m);
}

void Heavy_000_experiment_broken_engine::cBinop_LrDndiKG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_FxC68ObO, 4, m);
}

void Heavy_000_experiment_broken_engine::cBinop_eYIQDaER_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_oRs7XSZz, HV_BINOP_MULTIPLY, 0, m, &cBinop_oRs7XSZz_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_GUm4OA1w_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_fwnrITos, HV_BINOP_ADD, 1, m, &cBinop_fwnrITos_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_dXJYD3Rx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_e9aAkm0b_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_fwnrITos_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_oRs7XSZz, HV_BINOP_MULTIPLY, 1, m, &cBinop_oRs7XSZz_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_oRs7XSZz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_FxC68ObO, 1, m);
}

void Heavy_000_experiment_broken_engine::cBinop_7Dgel7c1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_qw9h4een, HV_BINOP_DIVIDE, 1, m, &cBinop_qw9h4een_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_WgtTBnbs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_MaRIBQ8D_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_fwnrITos, HV_BINOP_ADD, 0, m, &cBinop_fwnrITos_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_eYIQDaER_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_UDpctZNa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_HnmukeFs_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_HnmukeFs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BA9W1ivF, HV_BINOP_DIVIDE, 1, m, &cBinop_BA9W1ivF_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_5Jcr7Wau_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_VaS8sdnf_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_8pT5ytYD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_M6nWCzzy_sendMessage);
}

void Heavy_000_experiment_broken_engine::cUnop_SufMrpLx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_LMhtwnhv_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_BA9W1ivF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6yYfGNtQ, HV_BINOP_MULTIPLY, 1, m, &cBinop_6yYfGNtQ_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_SufMrpLx_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_1cyox1Ky, HV_BINOP_DIVIDE, 0, m, &cBinop_1cyox1Ky_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_VaS8sdnf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BA9W1ivF, HV_BINOP_DIVIDE, 0, m, &cBinop_BA9W1ivF_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_1cyox1Ky_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_Mr6lSgLX_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_nkw7U2KR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_tB1Zvlhz_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_tB1Zvlhz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_btS6rfLV_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_1x8ePwSC, HV_BINOP_MULTIPLY, 0, m, &cBinop_1x8ePwSC_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_6yYfGNtQ, HV_BINOP_MULTIPLY, 0, m, &cBinop_6yYfGNtQ_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_LMhtwnhv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_1x8ePwSC, HV_BINOP_MULTIPLY, 1, m, &cBinop_1x8ePwSC_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_1x8ePwSC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_UrENTr3v_sendMessage);
}

void Heavy_000_experiment_broken_engine::cCast_vgHoYbeF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_5Jcr7Wau, 0, m, &cVar_5Jcr7Wau_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_iwJdxSN1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_xr40uHgd_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_xr40uHgd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_AgTiC5Gv, 5, m);
}

void Heavy_000_experiment_broken_engine::cBinop_UrENTr3v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_AgTiC5Gv, 4, m);
}

void Heavy_000_experiment_broken_engine::cBinop_wKnPuBYh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_g79cFRpE, HV_BINOP_MULTIPLY, 0, m, &cBinop_g79cFRpE_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_6yYfGNtQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_f8qf0c1B, HV_BINOP_ADD, 1, m, &cBinop_f8qf0c1B_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_btS6rfLV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_iwJdxSN1_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_f8qf0c1B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_g79cFRpE, HV_BINOP_MULTIPLY, 1, m, &cBinop_g79cFRpE_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_g79cFRpE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_AgTiC5Gv, 1, m);
}

void Heavy_000_experiment_broken_engine::cBinop_M6nWCzzy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_1cyox1Ky, HV_BINOP_DIVIDE, 1, m, &cBinop_1cyox1Ky_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_Mr6lSgLX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_nkw7U2KR_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_f8qf0c1B, HV_BINOP_ADD, 0, m, &cBinop_f8qf0c1B_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_wKnPuBYh_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_0P9JvNoa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_9Eo3tcrg_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_9Eo3tcrg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_05wGDoPT, HV_BINOP_DIVIDE, 1, m, &cBinop_05wGDoPT_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_SFPCAMqc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_71kFcMZJ_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_mJWHiWwD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_t8wlALBp_sendMessage);
}

void Heavy_000_experiment_broken_engine::cUnop_2eBLKzZC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_6z3mC3hT_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_05wGDoPT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vj5qxOm9, HV_BINOP_MULTIPLY, 1, m, &cBinop_vj5qxOm9_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_2eBLKzZC_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_h2ejVXyR, HV_BINOP_DIVIDE, 0, m, &cBinop_h2ejVXyR_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_71kFcMZJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_05wGDoPT, HV_BINOP_DIVIDE, 0, m, &cBinop_05wGDoPT_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_h2ejVXyR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_FXLgxl96_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_CF62f9pZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_sSAj6Rd4_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_sSAj6Rd4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_qgXddseD_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_B4XKyIoc, HV_BINOP_MULTIPLY, 0, m, &cBinop_B4XKyIoc_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_vj5qxOm9, HV_BINOP_MULTIPLY, 0, m, &cBinop_vj5qxOm9_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_6z3mC3hT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_B4XKyIoc, HV_BINOP_MULTIPLY, 1, m, &cBinop_B4XKyIoc_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_B4XKyIoc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_0QIuEYvV_sendMessage);
}

void Heavy_000_experiment_broken_engine::cCast_Mtqbd0hl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_SFPCAMqc, 0, m, &cVar_SFPCAMqc_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_2ie8dJPw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_ufO8v0uH_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_ufO8v0uH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_tzqzTTOk, 5, m);
}

void Heavy_000_experiment_broken_engine::cBinop_0QIuEYvV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_tzqzTTOk, 4, m);
}

void Heavy_000_experiment_broken_engine::cBinop_r71iJ36g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xCjfByKK, HV_BINOP_MULTIPLY, 0, m, &cBinop_xCjfByKK_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_vj5qxOm9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lw3OldBr, HV_BINOP_ADD, 1, m, &cBinop_lw3OldBr_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_qgXddseD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_2ie8dJPw_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_lw3OldBr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xCjfByKK, HV_BINOP_MULTIPLY, 1, m, &cBinop_xCjfByKK_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_xCjfByKK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_tzqzTTOk, 1, m);
}

void Heavy_000_experiment_broken_engine::cBinop_t8wlALBp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_h2ejVXyR, HV_BINOP_DIVIDE, 1, m, &cBinop_h2ejVXyR_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_FXLgxl96_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_CF62f9pZ_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lw3OldBr, HV_BINOP_ADD, 0, m, &cBinop_lw3OldBr_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_r71iJ36g_sendMessage);
}

void Heavy_000_experiment_broken_engine::cMsg_CHmYbC2c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_odscMTkT_sendMessage);
}

void Heavy_000_experiment_broken_engine::cSystem_odscMTkT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hpglZouU, HV_BINOP_DIVIDE, 1, m, &cBinop_hpglZouU_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_bcIWuHyQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_yfDiFV3m_sendMessage);
}

void Heavy_000_experiment_broken_engine::cVar_KK7wIYVa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_cB4fXX3s_sendMessage);
}

void Heavy_000_experiment_broken_engine::cUnop_qtx16Bse_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_SgPzOo02_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_hpglZouU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_uOl04jYd, HV_BINOP_MULTIPLY, 1, m, &cBinop_uOl04jYd_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_qtx16Bse_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_BfMPV9ra, HV_BINOP_DIVIDE, 0, m, &cBinop_BfMPV9ra_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_yfDiFV3m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hpglZouU, HV_BINOP_DIVIDE, 0, m, &cBinop_hpglZouU_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_BfMPV9ra_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_NxvDLh8I_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_xz2Mi2j7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_1wiTWhJA_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_1wiTWhJA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_SDU9pRFq_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_L5A47ckl, HV_BINOP_MULTIPLY, 0, m, &cBinop_L5A47ckl_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_uOl04jYd, HV_BINOP_MULTIPLY, 0, m, &cBinop_uOl04jYd_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_SgPzOo02_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_L5A47ckl, HV_BINOP_MULTIPLY, 1, m, &cBinop_L5A47ckl_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_L5A47ckl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_8xtrfE5t_sendMessage);
}

void Heavy_000_experiment_broken_engine::cCast_fSoX6myu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_bcIWuHyQ, 0, m, &cVar_bcIWuHyQ_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_bMDK1Aee_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_VJXJH7un_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_VJXJH7un_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Cr3Mw7j0, 5, m);
}

void Heavy_000_experiment_broken_engine::cBinop_8xtrfE5t_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Cr3Mw7j0, 4, m);
}

void Heavy_000_experiment_broken_engine::cBinop_IgmqTH7V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_09ITJWZ5, HV_BINOP_MULTIPLY, 0, m, &cBinop_09ITJWZ5_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_uOl04jYd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_WO9wq9ym, HV_BINOP_ADD, 1, m, &cBinop_WO9wq9ym_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_SDU9pRFq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_bMDK1Aee_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_WO9wq9ym_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_09ITJWZ5, HV_BINOP_MULTIPLY, 1, m, &cBinop_09ITJWZ5_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_09ITJWZ5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Cr3Mw7j0, 1, m);
}

void Heavy_000_experiment_broken_engine::cBinop_cB4fXX3s_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BfMPV9ra, HV_BINOP_DIVIDE, 1, m, &cBinop_BfMPV9ra_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_NxvDLh8I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_xz2Mi2j7_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_WO9wq9ym, HV_BINOP_ADD, 0, m, &cBinop_WO9wq9ym_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_IgmqTH7V_sendMessage);
}

void Heavy_000_experiment_broken_engine::cBinop_2ugXq8xf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ySe8QKAd, m);
}

void Heavy_000_experiment_broken_engine::cReceive_f4a3q2gU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_v6XOwBbk_onMessage(_c, NULL, 0, m, NULL);
  cMsg_nBaLG8DT_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_a7Pr3ynb, 0, m, &cVar_a7Pr3ynb_sendMessage);
  cSwitchcase_h9VMBtjC_onMessage(_c, NULL, 0, m, NULL);
  cMsg_bV4CI3E4_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_K0xAkcsu, 0, m, &cVar_K0xAkcsu_sendMessage);
  cMsg_ToZ0IIPU_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_EPM0uxY1, 0, m, &cVar_EPM0uxY1_sendMessage);
  cMsg_2SMrRWpt_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_Nf6V4irR, 0, m, &cVar_Nf6V4irR_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_JmTYoMOq, 0, m, &cVar_JmTYoMOq_sendMessage);
  cMsg_MG8hzyW0_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_fe1llnWZ, 0, m, &cVar_fe1llnWZ_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_gZsjGG8m, 0, m, &cVar_gZsjGG8m_sendMessage);
  cMsg_EP6lfuvw_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_phhDZezP, 0, m, &cVar_phhDZezP_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_8pT5ytYD, 0, m, &cVar_8pT5ytYD_sendMessage);
  cMsg_UDpctZNa_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_5Jcr7Wau, 0, m, &cVar_5Jcr7Wau_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_mJWHiWwD, 0, m, &cVar_mJWHiWwD_sendMessage);
  cMsg_0P9JvNoa_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_SFPCAMqc, 0, m, &cVar_SFPCAMqc_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_KK7wIYVa, 0, m, &cVar_KK7wIYVa_sendMessage);
  cMsg_CHmYbC2c_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_bcIWuHyQ, 0, m, &cVar_bcIWuHyQ_sendMessage);
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

int Heavy_000_experiment_broken_engine::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6;
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
    __hv_varread_i(&sVari_wFAtrzqu, VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_cast_if(VIi(Bi1), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varwrite_i(&sVari_wFAtrzqu, VIi(Bi1));
    __hv_biquad_k_f(&sBiquad_k_vGu1wr0T, VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_49zLxcfh, VOf(Bf0));
    __hv_phasor_k_f(&sPhasor_GuywKxJc, VOf(Bf2));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_abs_f(VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf3), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf3), VOf(Bf2));
    __hv_mul_f(VIf(Bf3), VIf(Bf2), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf5), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf6), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf4), VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf2), VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_ySe8QKAd, VOf(Bf5));
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf1), VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f);
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_zero_f(VOf(Bf0));
    __hv_max_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_gqHo07xE, VOf(Bf5));
    __hv_rpole_f(&sRPole_Q1B2gn8v, VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_WCa5STtc, VIf(Bf5), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_sub_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_pPksuo0m, VOf(Bf5));
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_cmtoTfAD, VOf(Bf0));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_zXyLoEmy, VOf(Bf5));
    __hv_rpole_f(&sRPole_An9BZzhy, VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varread_i(&sVari_O3Zehwxf, VOi(Bi1));
    __hv_var_k_i(VOi(Bi0), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi1), VIi(Bi0), VOi(Bi0));
    __hv_cast_if(VIi(Bi0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varwrite_i(&sVari_O3Zehwxf, VIi(Bi0));
    __hv_varread_f(&sVarf_b6QrnJnd, VOf(Bf0));
    __hv_rpole_f(&sRPole_xZcoyoIn, VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_mPTONbHq, VIf(Bf0), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_FMZ2e5hY, VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_biquad_k_f(&sBiquad_k_FxC68ObO, VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_biquad_k_f(&sBiquad_k_AgTiC5Gv, VIf(Bf0), VOf(Bf5));
    __hv_biquad_k_f(&sBiquad_k_tzqzTTOk, VIf(Bf0), VOf(Bf1));
    __hv_add_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_biquad_k_f(&sBiquad_k_Cr3Mw7j0, VIf(Bf0), VOf(Bf0));
    __hv_add_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_2BcUSbcd, VOf(Bf1));
    __hv_rpole_f(&sRPole_rFJviXIV, VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_RqC7y7mx, VIf(Bf1), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_ojPk0OLa, VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_add_f(VIf(Bf0), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf0), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_000_experiment_broken_engine::processInline(float *inputBuffers, float *outputBuffers, int n4) {
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

int Heavy_000_experiment_broken_engine::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
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
