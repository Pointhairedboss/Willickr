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

#include "Heavy_2tone_25.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_2tone_25 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_2tone_25_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_2tone_25));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_2tone_25(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_2tone_25_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_2tone_25));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_2tone_25(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_2tone_25_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_2tone_25();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_2tone_25::Heavy_2tone_25(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_9dDm4VtH, 0.0f, sampleRate);
  numBytes += sLine_init(&sLine_fossO5ok);
  numBytes += sPhasor_k_init(&sPhasor_QDCRQZtF, 0.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_e4mqTWBX, 0.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_eu4rH2iT, 0.0f, sampleRate);
  numBytes += sRPole_init(&sRPole_LoCCV2YG);
  numBytes += sDel1_init(&sDel1_0VF57fVm);
  numBytes += cVar_init_f(&cVar_M2NuhSj9, 0.0f);
  numBytes += cVar_init_f(&cVar_Abp5IEv2, 0.0f);
  numBytes += cVar_init_f(&cVar_fX6MUcN8, 0.0f);
  numBytes += cVar_init_f(&cVar_aH08IhCI, 0.0f);
  numBytes += cDelay_init(this, &cDelay_tjzobjv1, 0.0f);
  numBytes += sVarf_init(&sVarf_VP1NysCn, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_NyRQA8cR, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_1a78a3Ae, 50.0f);
  numBytes += cBinop_init(&cBinop_QfDxgSYj, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_RcaVUIst, 0.0f, 0.0f, false);
  numBytes += cSlice_init(&cSlice_hJeN5G0e, 6, 1);
  numBytes += cSlice_init(&cSlice_C68kM6c8, 5, 1);
  numBytes += cSlice_init(&cSlice_xOTh6r7D, 4, 1);
  numBytes += cSlice_init(&cSlice_4T0LpNgK, 3, 1);
  numBytes += cSlice_init(&cSlice_GBNk5LrH, 2, 1);
  numBytes += cSlice_init(&cSlice_Tlf13kRU, 1, 1);
  numBytes += cSlice_init(&cSlice_j5KJBVf5, 0, 1);
  numBytes += sVarf_init(&sVarf_WRoUlq73, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_2QIoH1NQ, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_MAskURAF, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Lq9xVsMf, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_FqTgLtmM, 0.0f);
  numBytes += cVar_init_f(&cVar_GTRI2xmJ, 0.0f);
  numBytes += cVar_init_f(&cVar_fY9Aj55c, 0.0f);
  numBytes += cPack_init(&cPack_Ct9kBjsE, 7, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += cVar_init_f(&cVar_LcncBpQD, 0.0f);
  numBytes += cIf_init(&cIf_9bo0l9fI, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_2tone_25::~Heavy_2tone_25() {
  cPack_free(&cPack_Ct9kBjsE);
}

HvTable *Heavy_2tone_25::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_2tone_25::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_D8zULkkO_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_2tone_25::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_2tone_25::cVar_M2NuhSj9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MKWrwQii_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_XY6VXG9E_sendMessage);
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 2, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cVar_Abp5IEv2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MKWrwQii_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_XY6VXG9E_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_LcncBpQD, 0, m, &cVar_LcncBpQD_sendMessage);
}

void Heavy_2tone_25::cVar_fX6MUcN8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 0, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cVar_aH08IhCI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MKWrwQii_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_XY6VXG9E_sendMessage);
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 3, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cSwitchcase_J2qzjDYz_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7A5B032D: { // "stop"
      cMsg_q2FnP6tV_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cMsg_q2FnP6tV_sendMessage(_c, 0, m);
      cDelay_onMessage(_c, &Context(_c)->cDelay_tjzobjv1, 1, m, &cDelay_tjzobjv1_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_WdLl6yZn_sendMessage);
      break;
    }
  }
}

void Heavy_2tone_25::cDelay_tjzobjv1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_tjzobjv1, m);
  cMsg_39RXF6mt_sendMessage(_c, 0, m);
}

void Heavy_2tone_25::cMsg_q2FnP6tV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_tjzobjv1, 0, m, &cDelay_tjzobjv1_sendMessage);
}

void Heavy_2tone_25::cCast_WdLl6yZn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_tjzobjv1, 0, m, &cDelay_tjzobjv1_sendMessage);
}

void Heavy_2tone_25::cMsg_DFqc5uw4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  sLine_onMessage(_c, &Context(_c)->sLine_fossO5ok, 0, m, NULL);
}

void Heavy_2tone_25::cMsg_39RXF6mt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setFloat(m, 1, 0.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_fossO5ok, 0, m, NULL);
}

void Heavy_2tone_25::cMsg_FBfulPbC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_fossO5ok, 0, m, NULL);
}

void Heavy_2tone_25::cCast_ndV04Tci_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_DFqc5uw4_sendMessage(_c, 0, m);
}

void Heavy_2tone_25::cCast_Vo9WL5NN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_J2qzjDYz_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_2tone_25::cCast_kDWWV5GQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_FBfulPbC_sendMessage(_c, 0, m);
}

void Heavy_2tone_25::cBinop_O9ZPli7u_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_eGP3Oe2m_sendMessage);
}

void Heavy_2tone_25::cBinop_eGP3Oe2m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_svJgaGxX_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_2OHwI9Bz_sendMessage);
}

void Heavy_2tone_25::cVar_1a78a3Ae_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_yUM8sr6e_sendMessage);
}

void Heavy_2tone_25::cMsg_1qg2Sv5u_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Z4ycocde_sendMessage);
}

void Heavy_2tone_25::cSystem_Z4ycocde_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_QfDxgSYj, HV_BINOP_DIVIDE, 1, m, &cBinop_QfDxgSYj_sendMessage);
}

void Heavy_2tone_25::cBinop_svJgaGxX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_I7rPN5g4_sendMessage);
}

void Heavy_2tone_25::cBinop_I7rPN5g4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_RcaVUIst, m);
}

void Heavy_2tone_25::cMsg_2NLaCwBi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_AhB2FNjf_sendMessage);
}

void Heavy_2tone_25::cBinop_AhB2FNjf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_O9ZPli7u_sendMessage);
}

void Heavy_2tone_25::cBinop_2OHwI9Bz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_NyRQA8cR, m);
}

void Heavy_2tone_25::cBinop_yUM8sr6e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_ZO6zPdcP_sendMessage);
}

void Heavy_2tone_25::cBinop_ZO6zPdcP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_QfDxgSYj, HV_BINOP_DIVIDE, 0, m, &cBinop_QfDxgSYj_sendMessage);
}

void Heavy_2tone_25::cBinop_QfDxgSYj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_2NLaCwBi_sendMessage(_c, 0, m);
}

void Heavy_2tone_25::cSlice_hJeN5G0e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.25f, 0, m, &cBinop_5mAqKfJW_sendMessage);
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.25f, 0, m, &cBinop_HtkvosXL_sendMessage);
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.25f, 0, m, &cBinop_9668A7Um_sendMessage);
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.25f, 0, m, &cBinop_rCuQxOaj_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cSlice_C68kM6c8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_9dDm4VtH, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cSlice_xOTh6r7D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_eu4rH2iT, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cSlice_4T0LpNgK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_e4mqTWBX, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cSlice_GBNk5LrH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_QDCRQZtF, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cSlice_Tlf13kRU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sVarf_onMessage(_c, &Context(_c)->sVarf_VP1NysCn, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cSlice_j5KJBVf5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_kDWWV5GQ_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Vo9WL5NN_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_ndV04Tci_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cBinop_rCuQxOaj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_WRoUlq73, m);
}

void Heavy_2tone_25::cBinop_9668A7Um_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_2QIoH1NQ, m);
}

void Heavy_2tone_25::cBinop_HtkvosXL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_MAskURAF, m);
}

void Heavy_2tone_25::cBinop_5mAqKfJW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Lq9xVsMf, m);
}

void Heavy_2tone_25::cVar_FqTgLtmM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MKWrwQii_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_XY6VXG9E_sendMessage);
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 6, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cVar_GTRI2xmJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MKWrwQii_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_XY6VXG9E_sendMessage);
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 5, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cVar_fY9Aj55c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_MKWrwQii_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_XY6VXG9E_sendMessage);
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 4, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cPack_Ct9kBjsE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_8zNcqOu9_sendMessage(_c, 0, m);
}

void Heavy_2tone_25::cVar_LcncBpQD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 0.0f, 0, m, &cBinop_wQknrIww_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_9bo0l9fI, 0, m, &cIf_9bo0l9fI_sendMessage);
}

void Heavy_2tone_25::cUnop_GVio9dCL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 1, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cUnop_R7mbhvdX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 1, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cIf_9bo0l9fI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cUnop_onMessage(_c, HV_UNOP_CEIL, m, &cUnop_R7mbhvdX_sendMessage);
      break;
    }
    case 1: {
      cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_GVio9dCL_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_2tone_25::cBinop_wQknrIww_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_9bo0l9fI, 1, m, &cIf_9bo0l9fI_sendMessage);
}

void Heavy_2tone_25::cCast_XY6VXG9E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_Ct9kBjsE, 0, m, &cPack_Ct9kBjsE_sendMessage);
}

void Heavy_2tone_25::cCast_MKWrwQii_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_2tone_25::cMsg_8zNcqOu9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(8);
  msg_init(m, 8, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "set");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setElementToFrom(m, 2, n, 1);
  msg_setElementToFrom(m, 3, n, 2);
  msg_setElementToFrom(m, 4, n, 3);
  msg_setElementToFrom(m, 5, n, 4);
  msg_setElementToFrom(m, 6, n, 5);
  msg_setElementToFrom(m, 7, n, 6);
  cMsg_gLfqNVBc_sendMessage(_c, 0, m);
}

void Heavy_2tone_25::cMsg_e41wm9Cm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 317.0f);
  msg_setFloat(m, 1, 7.0f);
  msg_setFloat(m, 2, 300.0f);
  msg_setFloat(m, 3, 125.0f);
  msg_setFloat(m, 4, 0.0f);
  msg_setFloat(m, 5, 0.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_MO3nalNJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1031.0f);
  msg_setFloat(m, 1, 9.0f);
  msg_setFloat(m, 2, 360.0f);
  msg_setFloat(m, 3, 238.0f);
  msg_setFloat(m, 4, 174.0f);
  msg_setFloat(m, 5, 158.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_SQ99D8Vh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1428.0f);
  msg_setFloat(m, 1, 3.0f);
  msg_setFloat(m, 2, 619.0f);
  msg_setFloat(m, 3, 571.0f);
  msg_setFloat(m, 4, 365.0f);
  msg_setFloat(m, 5, 206.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_wyRO5kBg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 450.0f);
  msg_setFloat(m, 1, 1.0f);
  msg_setFloat(m, 2, 365.0f);
  msg_setFloat(m, 3, 571.0f);
  msg_setFloat(m, 4, 619.0f);
  msg_setFloat(m, 5, 206.0f);
  msg_setFloat(m, 6, 0.5f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_pdqn7AA0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 714.0f);
  msg_setFloat(m, 1, 74.0f);
  msg_setFloat(m, 2, 1000.0f);
  msg_setFloat(m, 3, 0.0f);
  msg_setFloat(m, 4, 1000.0f);
  msg_setFloat(m, 5, 0.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_gLfqNVBc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 714.286f);
  msg_setFloat(m, 1, 6.0f);
  msg_setFloat(m, 2, 1000.0f);
  msg_setFloat(m, 3, 1000.0f);
  msg_setFloat(m, 4, 0.0f);
  msg_setFloat(m, 5, 1000.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_iMLHQtSY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 900.0f);
  msg_setFloat(m, 1, 4.0f);
  msg_setFloat(m, 2, 2000.0f);
  msg_setFloat(m, 3, 2010.0f);
  msg_setFloat(m, 4, 2000.0f);
  msg_setFloat(m, 5, 2010.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_0xRmNDs0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 380.0f);
  msg_setFloat(m, 1, 2.0f);
  msg_setFloat(m, 2, 349.0f);
  msg_setFloat(m, 3, 0.0f);
  msg_setFloat(m, 4, 0.0f);
  msg_setFloat(m, 5, 0.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_GeNMM97p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 238.0f);
  msg_setFloat(m, 1, 1.0f);
  msg_setFloat(m, 2, 317.0f);
  msg_setFloat(m, 3, 0.0f);
  msg_setFloat(m, 4, 0.0f);
  msg_setFloat(m, 5, 476.0f);
  msg_setFloat(m, 6, 0.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_8BXtKm2K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 200.0f);
  msg_setFloat(m, 1, 30.0f);
  msg_setFloat(m, 2, 1000.0f);
  msg_setFloat(m, 3, 476.0f);
  msg_setFloat(m, 4, 159.0f);
  msg_setFloat(m, 5, 0.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cMsg_WqG3urDI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 634.0f);
  msg_setFloat(m, 1, 61.0f);
  msg_setFloat(m, 2, 1000.0f);
  msg_setFloat(m, 3, 476.0f);
  msg_setFloat(m, 4, 159.0f);
  msg_setFloat(m, 5, 0.0f);
  msg_setFloat(m, 6, 1.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_hJeN5G0e, 0, m, &cSlice_hJeN5G0e_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_C68kM6c8, 0, m, &cSlice_C68kM6c8_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xOTh6r7D, 0, m, &cSlice_xOTh6r7D_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_4T0LpNgK, 0, m, &cSlice_4T0LpNgK_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_GBNk5LrH, 0, m, &cSlice_GBNk5LrH_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_Tlf13kRU, 0, m, &cSlice_Tlf13kRU_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_j5KJBVf5, 0, m, &cSlice_j5KJBVf5_sendMessage);
}

void Heavy_2tone_25::cReceive_D8zULkkO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_1qg2Sv5u_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_1a78a3Ae, 0, m, &cVar_1a78a3Ae_sendMessage);
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

int Heavy_2tone_25::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6, Bf7, Bf8, Bf9, Bf10, Bf11, Bf12, Bf13, Bf14;

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
    __hv_phasor_k_f(&sPhasor_9dDm4VtH, VOf(Bf0));
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
    __hv_varread_f(&sVarf_Lq9xVsMf, VOf(Bf3));
    __hv_add_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_floor_f(VIf(Bf3), VOf(Bf1));
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_abs_f(VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf3), VOf(Bf1));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf6), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf7), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf0), VIf(Bf7), VOf(Bf7));
    __hv_sub_f(VIf(Bf3), VIf(Bf7), VOf(Bf7));
    __hv_fma_f(VIf(Bf4), VIf(Bf6), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf6), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf2), VIf(Bf6), VOf(Bf6));
    __hv_sub_f(VIf(Bf7), VIf(Bf6), VOf(Bf6));
    __hv_fma_f(VIf(Bf1), VIf(Bf5), VIf(Bf6), VOf(Bf6));
    __hv_line_f(&sLine_fossO5ok, VOf(Bf5));
    __hv_varread_f(&sVarf_VP1NysCn, VOf(Bf1));
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_floor_f(VIf(Bf1), VOf(Bf5));
    __hv_sub_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_zero_f(VOf(Bf7));
    __hv_max_f(VIf(Bf5), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf5), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_var_k_f(VOf(Bf2), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_fms_f(VIf(Bf7), VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_floor_f(VIf(Bf2), VOf(Bf5));
    __hv_sub_f(VIf(Bf2), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_abs_f(VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf5), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf2), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf2), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf5));
    __hv_mul_f(VIf(Bf2), VIf(Bf5), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf5), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf5), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf8), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf9), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf7), VIf(Bf9), VOf(Bf9));
    __hv_sub_f(VIf(Bf2), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf4), VIf(Bf8), VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf8), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_sub_f(VIf(Bf9), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf5), VIf(Bf0), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf0), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_min_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_max_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_sub_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_var_k_f(VOf(Bf9), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_fms_f(VIf(Bf0), VIf(Bf5), VIf(Bf9), VOf(Bf9));
    __hv_floor_f(VIf(Bf9), VOf(Bf5));
    __hv_sub_f(VIf(Bf9), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf9), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf5), VIf(Bf9), VOf(Bf9));
    __hv_abs_f(VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf5), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf9), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf9), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf5), VIf(Bf9), VOf(Bf9));
    __hv_mul_f(VIf(Bf9), VIf(Bf9), VOf(Bf5));
    __hv_mul_f(VIf(Bf9), VIf(Bf5), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf2), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf7), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf10), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf0), VIf(Bf10), VOf(Bf10));
    __hv_sub_f(VIf(Bf9), VIf(Bf10), VOf(Bf10));
    __hv_fma_f(VIf(Bf3), VIf(Bf7), VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf7), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf4), VIf(Bf7), VOf(Bf7));
    __hv_sub_f(VIf(Bf10), VIf(Bf7), VOf(Bf7));
    __hv_fma_f(VIf(Bf5), VIf(Bf2), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf2), 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f);
    __hv_min_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf5), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_max_f(VIf(Bf2), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf2), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_sub_f(VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf5), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_var_k_f(VOf(Bf10), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_fms_f(VIf(Bf2), VIf(Bf5), VIf(Bf10), VOf(Bf10));
    __hv_floor_f(VIf(Bf10), VOf(Bf5));
    __hv_sub_f(VIf(Bf10), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf10), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf5), VIf(Bf10), VOf(Bf10));
    __hv_abs_f(VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf5), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf10), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf10), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf5), VIf(Bf10), VOf(Bf10));
    __hv_mul_f(VIf(Bf10), VIf(Bf10), VOf(Bf5));
    __hv_mul_f(VIf(Bf10), VIf(Bf5), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf5), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf5), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf9), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf0), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf11), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf2), VIf(Bf11), VOf(Bf11));
    __hv_sub_f(VIf(Bf10), VIf(Bf11), VOf(Bf11));
    __hv_fma_f(VIf(Bf4), VIf(Bf0), VIf(Bf11), VOf(Bf11));
    __hv_var_k_f(VOf(Bf0), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_sub_f(VIf(Bf11), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf5), VIf(Bf9), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf9), 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f);
    __hv_min_f(VIf(Bf1), VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf1), 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f);
    __hv_max_f(VIf(Bf9), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf9), 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f);
    __hv_sub_f(VIf(Bf1), VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_var_k_f(VOf(Bf5), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_fms_f(VIf(Bf9), VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_floor_f(VIf(Bf5), VOf(Bf1));
    __hv_sub_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_abs_f(VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf5), VOf(Bf1));
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf9));
    __hv_mul_f(VIf(Bf9), VIf(Bf1), VOf(Bf11));
    __hv_mul_f(VIf(Bf11), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf4), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf10), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf2), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf9), VIf(Bf2), VOf(Bf2));
    __hv_sub_f(VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_fma_f(VIf(Bf11), VIf(Bf10), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf10), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf3), VIf(Bf10), VOf(Bf10));
    __hv_sub_f(VIf(Bf2), VIf(Bf10), VOf(Bf10));
    __hv_fma_f(VIf(Bf1), VIf(Bf4), VIf(Bf10), VOf(Bf10));
    __hv_phasor_k_f(&sPhasor_QDCRQZtF, VOf(Bf4));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf4), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf4));
    __hv_mul_f(VIf(Bf1), VIf(Bf4), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf3), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf11), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf11), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf4), VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_WRoUlq73, VOf(Bf3));
    __hv_add_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_floor_f(VIf(Bf3), VOf(Bf1));
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_abs_f(VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf3), VOf(Bf1));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf11));
    __hv_mul_f(VIf(Bf11), VIf(Bf1), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf9), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf12), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf4), VIf(Bf12), VOf(Bf12));
    __hv_sub_f(VIf(Bf3), VIf(Bf12), VOf(Bf12));
    __hv_fma_f(VIf(Bf11), VIf(Bf9), VIf(Bf12), VOf(Bf12));
    __hv_var_k_f(VOf(Bf9), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf2), VIf(Bf9), VOf(Bf9));
    __hv_sub_f(VIf(Bf12), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf1), VIf(Bf5), VIf(Bf9), VOf(Bf9));
    __hv_phasor_k_f(&sPhasor_e4mqTWBX, VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf5));
    __hv_mul_f(VIf(Bf1), VIf(Bf5), VOf(Bf12));
    __hv_mul_f(VIf(Bf12), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf2), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf11), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf12), VIf(Bf11), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf5), VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_2QIoH1NQ, VOf(Bf2));
    __hv_add_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_floor_f(VIf(Bf2), VOf(Bf1));
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_abs_f(VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf1));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf11));
    __hv_mul_f(VIf(Bf11), VIf(Bf1), VOf(Bf12));
    __hv_mul_f(VIf(Bf12), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf4), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf13), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf5), VIf(Bf13), VOf(Bf13));
    __hv_sub_f(VIf(Bf2), VIf(Bf13), VOf(Bf13));
    __hv_fma_f(VIf(Bf11), VIf(Bf4), VIf(Bf13), VOf(Bf13));
    __hv_var_k_f(VOf(Bf4), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf12), VIf(Bf4), VOf(Bf4));
    __hv_sub_f(VIf(Bf13), VIf(Bf4), VOf(Bf4));
    __hv_fma_f(VIf(Bf1), VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_phasor_k_f(&sPhasor_eu4rH2iT, VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf13));
    __hv_mul_f(VIf(Bf13), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf12), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf11), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf13), VIf(Bf11), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf3), VIf(Bf12), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_MAskURAF, VOf(Bf12));
    __hv_add_f(VIf(Bf1), VIf(Bf12), VOf(Bf12));
    __hv_floor_f(VIf(Bf12), VOf(Bf1));
    __hv_sub_f(VIf(Bf12), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf12), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf12), VOf(Bf12));
    __hv_abs_f(VIf(Bf12), VOf(Bf12));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf12), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf12), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf1), VIf(Bf12), VOf(Bf12));
    __hv_mul_f(VIf(Bf12), VIf(Bf12), VOf(Bf1));
    __hv_mul_f(VIf(Bf12), VIf(Bf1), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf11));
    __hv_mul_f(VIf(Bf11), VIf(Bf1), VOf(Bf13));
    __hv_mul_f(VIf(Bf13), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf5), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf14), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf3), VIf(Bf14), VOf(Bf14));
    __hv_sub_f(VIf(Bf12), VIf(Bf14), VOf(Bf14));
    __hv_fma_f(VIf(Bf11), VIf(Bf5), VIf(Bf14), VOf(Bf14));
    __hv_var_k_f(VOf(Bf5), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf13), VIf(Bf5), VOf(Bf5));
    __hv_sub_f(VIf(Bf14), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf1), VIf(Bf2), VIf(Bf5), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf4), VIf(Bf7), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf9), VIf(Bf8), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf6), VIf(Bf10), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf10), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_mul_f(VIf(Bf0), VIf(Bf10), VOf(Bf10));
    __hv_varread_f(&sVarf_NyRQA8cR, VOf(Bf0));
    __hv_rpole_f(&sRPole_LoCCV2YG, VIf(Bf10), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf10), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_0VF57fVm, VIf(Bf0), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf10), VOf(Bf10));
    __hv_sub_f(VIf(Bf0), VIf(Bf10), VOf(Bf10));
    __hv_varread_f(&sVarf_RcaVUIst, VOf(Bf0));
    __hv_mul_f(VIf(Bf10), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf10), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf0), VIf(Bf10), VOf(Bf10));
    __hv_add_f(VIf(Bf10), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf10), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_2tone_25::processInline(float *inputBuffers, float *outputBuffers, int n4) {
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

int Heavy_2tone_25::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
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
