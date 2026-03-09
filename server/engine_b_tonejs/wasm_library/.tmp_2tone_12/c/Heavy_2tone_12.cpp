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

#include "Heavy_2tone_12.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_2tone_12 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_2tone_12_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_2tone_12));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_2tone_12(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_2tone_12_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_2tone_12));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_2tone_12(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_2tone_12_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_2tone_12();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_2tone_12::Heavy_2tone_12(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_oluRzgi5, 723.0f, sampleRate);
  numBytes += sRPole_init(&sRPole_ruPxbT1S);
  numBytes += sPhasor_k_init(&sPhasor_ozhg9yiu, 932.0f, sampleRate);
  numBytes += sRPole_init(&sRPole_hOKTun2x);
  numBytes += sPhasor_k_init(&sPhasor_Btg9TBrc, 1012.0f, sampleRate);
  numBytes += sRPole_init(&sRPole_UpoU5Zwo);
  numBytes += cVar_init_f(&cVar_tnIm8Tb2, 70.0f);
  numBytes += cBinop_init(&cBinop_n0hAf4UE, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_ZXCcGevu, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_V6NfLYFj, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_xwavDevN, 70.0f);
  numBytes += cBinop_init(&cBinop_1yuxnJg1, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_xafsAHvl, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_maYDJQrU, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_hxJrbjRo, 70.0f);
  numBytes += cBinop_init(&cBinop_JRykUHdr, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_O3ypvnYy, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Pyc2t3d5, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_kxXl8wcT, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_DT6E0doz, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_aDX8JmMH, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_RcRXRLkq, 0.0f);
  numBytes += cDelay_init(this, &cDelay_kt74U0iH, 0.0f);
  numBytes += cVar_init_f(&cVar_AsaaLNr3, 500.0f);
  numBytes += cBinop_init(&cBinop_n55Y0OtU, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_ob2TQVM1, 1.0f);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_2tone_12::~Heavy_2tone_12() {
  // nothing to free
}

HvTable *Heavy_2tone_12::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_2tone_12::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_8j9wNufl_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_2tone_12::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_2tone_12::cVar_tnIm8Tb2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_n0hAf4UE, HV_BINOP_MULTIPLY, 0, m, &cBinop_n0hAf4UE_sendMessage);
}

void Heavy_2tone_12::cMsg_ZVubnIcM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_jaqFVNVk_sendMessage);
}

void Heavy_2tone_12::cSystem_jaqFVNVk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_QUW5n5El_sendMessage(_c, 0, m);
}

void Heavy_2tone_12::cBinop_n0hAf4UE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_wF5Lg2LQ_sendMessage);
}

void Heavy_2tone_12::cBinop_L6fUbmSE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_n0hAf4UE, HV_BINOP_MULTIPLY, 1, m, &cBinop_n0hAf4UE_sendMessage);
}

void Heavy_2tone_12::cMsg_QUW5n5El_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_L6fUbmSE_sendMessage);
}

void Heavy_2tone_12::cBinop_wF5Lg2LQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_0hWUHMqx_sendMessage);
}

void Heavy_2tone_12::cBinop_0hWUHMqx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_7iJjqqkk_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_V6NfLYFj, m);
}

void Heavy_2tone_12::cBinop_7iJjqqkk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ZXCcGevu, m);
}

void Heavy_2tone_12::cVar_xwavDevN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_1yuxnJg1, HV_BINOP_MULTIPLY, 0, m, &cBinop_1yuxnJg1_sendMessage);
}

void Heavy_2tone_12::cMsg_2xbssXw2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_mdR3yv2N_sendMessage);
}

void Heavy_2tone_12::cSystem_mdR3yv2N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Gog5rQQJ_sendMessage(_c, 0, m);
}

void Heavy_2tone_12::cBinop_1yuxnJg1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_lq20aG8y_sendMessage);
}

void Heavy_2tone_12::cBinop_NhrqvHTT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_1yuxnJg1, HV_BINOP_MULTIPLY, 1, m, &cBinop_1yuxnJg1_sendMessage);
}

void Heavy_2tone_12::cMsg_Gog5rQQJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_NhrqvHTT_sendMessage);
}

void Heavy_2tone_12::cBinop_lq20aG8y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_wqxkRP8O_sendMessage);
}

void Heavy_2tone_12::cBinop_wqxkRP8O_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_DLpEPOs3_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_maYDJQrU, m);
}

void Heavy_2tone_12::cBinop_DLpEPOs3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_xafsAHvl, m);
}

void Heavy_2tone_12::cVar_hxJrbjRo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JRykUHdr, HV_BINOP_MULTIPLY, 0, m, &cBinop_JRykUHdr_sendMessage);
}

void Heavy_2tone_12::cMsg_tkUHb4Zr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_GUyuwMyK_sendMessage);
}

void Heavy_2tone_12::cSystem_GUyuwMyK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_DkmmY7rm_sendMessage(_c, 0, m);
}

void Heavy_2tone_12::cBinop_JRykUHdr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_vgdJFsmg_sendMessage);
}

void Heavy_2tone_12::cBinop_7L6EeZE5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JRykUHdr, HV_BINOP_MULTIPLY, 1, m, &cBinop_JRykUHdr_sendMessage);
}

void Heavy_2tone_12::cMsg_DkmmY7rm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_7L6EeZE5_sendMessage);
}

void Heavy_2tone_12::cBinop_vgdJFsmg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_jYaefxWk_sendMessage);
}

void Heavy_2tone_12::cBinop_jYaefxWk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_enStkEw6_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_Pyc2t3d5, m);
}

void Heavy_2tone_12::cBinop_enStkEw6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_O3ypvnYy, m);
}

void Heavy_2tone_12::cVar_RcRXRLkq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_6VptXnt1_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MOD_UNIPOLAR, 3.0f, 0, m, &cBinop_EGiIU5xh_sendMessage);
}

void Heavy_2tone_12::cSwitchcase_bfPU716U_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_KIbRWrP0_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_KIbRWrP0_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_irbRTSfo_sendMessage);
      break;
    }
  }
}

void Heavy_2tone_12::cDelay_kt74U0iH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_kt74U0iH, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kt74U0iH, 0, m, &cDelay_kt74U0iH_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_RcRXRLkq, 0, m, &cVar_RcRXRLkq_sendMessage);
}

void Heavy_2tone_12::cCast_irbRTSfo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_KIbRWrP0_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kt74U0iH, 0, m, &cDelay_kt74U0iH_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_RcRXRLkq, 0, m, &cVar_RcRXRLkq_sendMessage);
}

void Heavy_2tone_12::cMsg_QPwiljPx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_r2GVoclO_sendMessage);
}

void Heavy_2tone_12::cSystem_r2GVoclO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_23CPjzv6_sendMessage);
}

void Heavy_2tone_12::cVar_AsaaLNr3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_n55Y0OtU, HV_BINOP_MULTIPLY, 0, m, &cBinop_n55Y0OtU_sendMessage);
}

void Heavy_2tone_12::cMsg_KIbRWrP0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_kt74U0iH, 0, m, &cDelay_kt74U0iH_sendMessage);
}

void Heavy_2tone_12::cBinop_Svlb7Vr8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_kt74U0iH, 2, m, &cDelay_kt74U0iH_sendMessage);
}

void Heavy_2tone_12::cBinop_23CPjzv6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_n55Y0OtU, HV_BINOP_MULTIPLY, 1, m, &cBinop_n55Y0OtU_sendMessage);
}

void Heavy_2tone_12::cBinop_n55Y0OtU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_Svlb7Vr8_sendMessage);
}

void Heavy_2tone_12::cVar_ob2TQVM1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_0vxXL69k_sendMessage);
  cSwitchcase_bfPU716U_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_2tone_12::cBinop_0vxXL69k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_ob2TQVM1, 1, m, &cVar_ob2TQVM1_sendMessage);
}

void Heavy_2tone_12::cBinop_6VptXnt1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_RcRXRLkq, 1, m, &cVar_RcRXRLkq_sendMessage);
}

void Heavy_2tone_12::cBinop_EGiIU5xh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_AkuDP4EO_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_KcQNJfwe_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_0D2bVVpm_sendMessage);
}

void Heavy_2tone_12::cBinop_OVc6XJnZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_DT6E0doz, m);
}

void Heavy_2tone_12::cCast_AkuDP4EO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 2.0f, 0, m, &cBinop_5pDVKC3U_sendMessage);
}

void Heavy_2tone_12::cCast_0D2bVVpm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_map2Ta7U_sendMessage);
}

void Heavy_2tone_12::cCast_KcQNJfwe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 1.0f, 0, m, &cBinop_OVc6XJnZ_sendMessage);
}

void Heavy_2tone_12::cBinop_map2Ta7U_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_aDX8JmMH, m);
}

void Heavy_2tone_12::cBinop_5pDVKC3U_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_kxXl8wcT, m);
}

void Heavy_2tone_12::cReceive_8j9wNufl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ZVubnIcM_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_tnIm8Tb2, 0, m, &cVar_tnIm8Tb2_sendMessage);
  cMsg_2xbssXw2_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_xwavDevN, 0, m, &cVar_xwavDevN_sendMessage);
  cMsg_tkUHb4Zr_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_hxJrbjRo, 0, m, &cVar_hxJrbjRo_sendMessage);
  cMsg_QPwiljPx_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_AsaaLNr3, 0, m, &cVar_AsaaLNr3_sendMessage);
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

int Heavy_2tone_12::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_phasor_k_f(&sPhasor_oluRzgi5, VOf(Bf0));
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
    __hv_varread_f(&sVarf_aDX8JmMH, VOf(Bf3));
    __hv_varread_f(&sVarf_V6NfLYFj, VOf(Bf0));
    __hv_mul_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_ZXCcGevu, VOf(Bf3));
    __hv_rpole_f(&sRPole_ruPxbT1S, VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_phasor_k_f(&sPhasor_ozhg9yiu, VOf(Bf0));
    __hv_var_k_f(VOf(Bf4), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_abs_f(VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf4), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf4), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf4), VOf(Bf0));
    __hv_mul_f(VIf(Bf4), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf6), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf6), VIf(Bf4), VOf(Bf4));
    __hv_fma_f(VIf(Bf0), VIf(Bf5), VIf(Bf4), VOf(Bf4));
    __hv_varread_f(&sVarf_DT6E0doz, VOf(Bf5));
    __hv_varread_f(&sVarf_maYDJQrU, VOf(Bf0));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_xafsAHvl, VOf(Bf5));
    __hv_rpole_f(&sRPole_hOKTun2x, VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_phasor_k_f(&sPhasor_Btg9TBrc, VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_abs_f(VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf6), VOf(Bf0));
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf7), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf8), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf8), VIf(Bf6), VOf(Bf6));
    __hv_fma_f(VIf(Bf0), VIf(Bf7), VIf(Bf6), VOf(Bf6));
    __hv_varread_f(&sVarf_kxXl8wcT, VOf(Bf7));
    __hv_varread_f(&sVarf_Pyc2t3d5, VOf(Bf0));
    __hv_mul_f(VIf(Bf7), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_O3ypvnYy, VOf(Bf7));
    __hv_rpole_f(&sRPole_UpoU5Zwo, VIf(Bf0), VIf(Bf7), VOf(Bf7));
    __hv_mul_f(VIf(Bf6), VIf(Bf7), VOf(Bf7));
    __hv_fma_f(VIf(Bf4), VIf(Bf5), VIf(Bf7), VOf(Bf7));
    __hv_fma_f(VIf(Bf1), VIf(Bf3), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf3), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_mul_f(VIf(Bf7), VIf(Bf3), VOf(Bf3));
    __hv_add_f(VIf(Bf3), VIf(O0), VOf(O0));
    __hv_add_f(VIf(Bf3), VIf(O1), VOf(O1));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_2tone_12::processInline(float *inputBuffers, float *outputBuffers, int n4) {
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

int Heavy_2tone_12::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
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
