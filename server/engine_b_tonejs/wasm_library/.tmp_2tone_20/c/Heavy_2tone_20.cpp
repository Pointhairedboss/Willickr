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

#include "Heavy_2tone_20.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_2tone_20 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_2tone_20_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_2tone_20));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_2tone_20(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_2tone_20_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_2tone_20));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_2tone_20(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_2tone_20_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_2tone_20();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_2tone_20::Heavy_2tone_20(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_9ZP8j2dg, 0.5f, sampleRate);
  numBytes += sRPole_init(&sRPole_PobEBZuf);
  numBytes += sPhasor_k_init(&sPhasor_qmD0A5Zm, 0.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_zpbfVUrk, 0.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_0kfnL0rA, 0.0f, sampleRate);
  numBytes += sPhasor_k_init(&sPhasor_E9yVHxje, 0.0f, sampleRate);
  numBytes += sRPole_init(&sRPole_ol4rDE3i);
  numBytes += sDel1_init(&sDel1_DXMWtpzV);
  numBytes += cVar_init_f(&cVar_0kjvkmt4, 0.0f);
  numBytes += cVar_init_f(&cVar_jChkGRpr, 0.0f);
  numBytes += cVar_init_f(&cVar_Drk2xaH8, 0.0f);
  numBytes += cVar_init_f(&cVar_i5okpbHR, 0.0f);
  numBytes += cVar_init_f(&cVar_bMIQeHos, 0.0f);
  numBytes += cVar_init_f(&cVar_2xMTzrO4, 0.0f);
  numBytes += cVar_init_f(&cVar_03c4kUJK, 0.0f);
  numBytes += cVar_init_f(&cVar_htIUl6Tb, 0.0f);
  numBytes += cSlice_init(&cSlice_mDtca8Ri, 1, 1);
  numBytes += cSlice_init(&cSlice_oMCXK523, 0, 1);
  numBytes += sVarf_init(&sVarf_tFvCoT2w, 0.0f, 0.0f, false);
  numBytes += cPack_init(&cPack_1UFAExeO, 2, 0.0f, 0.0f);
  numBytes += cPack_init(&cPack_9kEnESpi, 2, 0.0f, 0.0f);
  numBytes += cPack_init(&cPack_7445UdKJ, 2, 0.0f, 0.0f);
  numBytes += cSlice_init(&cSlice_9Y2fpVCB, 1, 1);
  numBytes += cSlice_init(&cSlice_vx4rzgXC, 0, 1);
  numBytes += sVarf_init(&sVarf_P3jZSEGI, 0.0f, 0.0f, false);
  numBytes += cSlice_init(&cSlice_irYxSuHb, 1, 1);
  numBytes += cSlice_init(&cSlice_g3oMqRPd, 0, 1);
  numBytes += sVarf_init(&sVarf_TpNybESq, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_imDlcvHY, 100.0f);
  numBytes += cBinop_init(&cBinop_nodTO8Sm, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_FDghQdDA, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_I5MdycSC, 0.0f, 0.0f, false);
  numBytes += cSlice_init(&cSlice_X7ALEfVC, 7, 1);
  numBytes += cSlice_init(&cSlice_n50EIq21, 6, 1);
  numBytes += cSlice_init(&cSlice_RlcRSxI0, 5, 1);
  numBytes += cSlice_init(&cSlice_glou201g, 4, 1);
  numBytes += cSlice_init(&cSlice_SyBOOAui, 3, 1);
  numBytes += cSlice_init(&cSlice_xY6h08oE, 2, 1);
  numBytes += cSlice_init(&cSlice_6UGDeWwA, 1, 1);
  numBytes += cSlice_init(&cSlice_54uviXs8, 0, 1);
  numBytes += sVarf_init(&sVarf_Hiok0H9n, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_eNRKlm3M, 50.0f);
  numBytes += cBinop_init(&cBinop_kaEEwbwj, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_TP3AeMhX, 0.0f, 0.0f, false);
  numBytes += cPack_init(&cPack_iI5ce5L5, 8, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_2tone_20::~Heavy_2tone_20() {
  cPack_free(&cPack_1UFAExeO);
  cPack_free(&cPack_9kEnESpi);
  cPack_free(&cPack_7445UdKJ);
  cPack_free(&cPack_iI5ce5L5);
}

HvTable *Heavy_2tone_20::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_2tone_20::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_fSqdCCNa_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_2tone_20::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_2tone_20::cVar_0kjvkmt4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 2, m, &cPack_iI5ce5L5_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mpquhSbO_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0TaNRAg0_sendMessage);
}

void Heavy_2tone_20::cVar_jChkGRpr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 3, m, &cPack_iI5ce5L5_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mpquhSbO_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0TaNRAg0_sendMessage);
}

void Heavy_2tone_20::cVar_Drk2xaH8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 4, m, &cPack_iI5ce5L5_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mpquhSbO_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0TaNRAg0_sendMessage);
}

void Heavy_2tone_20::cVar_i5okpbHR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 5, m, &cPack_iI5ce5L5_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mpquhSbO_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0TaNRAg0_sendMessage);
}

void Heavy_2tone_20::cVar_bMIQeHos_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 6, m, &cPack_iI5ce5L5_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mpquhSbO_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0TaNRAg0_sendMessage);
}

void Heavy_2tone_20::cVar_2xMTzrO4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 7, m, &cPack_iI5ce5L5_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mpquhSbO_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0TaNRAg0_sendMessage);
}

void Heavy_2tone_20::cVar_03c4kUJK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 1, m, &cPack_iI5ce5L5_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mpquhSbO_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0TaNRAg0_sendMessage);
}

void Heavy_2tone_20::cVar_htIUl6Tb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 0, m, &cPack_iI5ce5L5_sendMessage);
}

void Heavy_2tone_20::cBinop_OdNCGeBN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_zpbfVUrk, 0, m);
}

void Heavy_2tone_20::cSlice_mDtca8Ri_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.25f, 0, m, &cBinop_87WbZycv_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_oMCXK523_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 1000.0f, 0, m, &cBinop_o8LNHM6L_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cBinop_87WbZycv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_tFvCoT2w, m);
}

void Heavy_2tone_20::cBinop_o8LNHM6L_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_qmD0A5Zm, 0, m);
}

void Heavy_2tone_20::cPack_1UFAExeO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSlice_onMessage(_c, &Context(_c)->cSlice_mDtca8Ri, 0, m, &cSlice_mDtca8Ri_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_oMCXK523, 0, m, &cSlice_oMCXK523_sendMessage);
}

void Heavy_2tone_20::cPack_9kEnESpi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSlice_onMessage(_c, &Context(_c)->cSlice_9Y2fpVCB, 0, m, &cSlice_9Y2fpVCB_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_vx4rzgXC, 0, m, &cSlice_vx4rzgXC_sendMessage);
}

void Heavy_2tone_20::cPack_7445UdKJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSlice_onMessage(_c, &Context(_c)->cSlice_irYxSuHb, 0, m, &cSlice_irYxSuHb_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_g3oMqRPd, 0, m, &cSlice_g3oMqRPd_sendMessage);
}

void Heavy_2tone_20::cSlice_9Y2fpVCB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.25f, 0, m, &cBinop_T7PAqnt5_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_vx4rzgXC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 1000.0f, 0, m, &cBinop_ldhDM8zL_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cBinop_T7PAqnt5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_P3jZSEGI, m);
}

void Heavy_2tone_20::cBinop_ldhDM8zL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_0kfnL0rA, 0, m);
}

void Heavy_2tone_20::cSlice_irYxSuHb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.25f, 0, m, &cBinop_kcxBC1qP_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_g3oMqRPd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 1000.0f, 0, m, &cBinop_ZJ5aR7QN_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cBinop_kcxBC1qP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_TpNybESq, m);
}

void Heavy_2tone_20::cBinop_ZJ5aR7QN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_E9yVHxje, 0, m);
}

void Heavy_2tone_20::cVar_imDlcvHY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_nodTO8Sm, HV_BINOP_MULTIPLY, 0, m, &cBinop_nodTO8Sm_sendMessage);
}

void Heavy_2tone_20::cMsg_uQusyC3c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_9iIcRVTA_sendMessage);
}

void Heavy_2tone_20::cSystem_9iIcRVTA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Yg7pIsp4_sendMessage(_c, 0, m);
}

void Heavy_2tone_20::cBinop_nodTO8Sm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_PJnj0tv3_sendMessage);
}

void Heavy_2tone_20::cBinop_Ar2cfKfb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_nodTO8Sm, HV_BINOP_MULTIPLY, 1, m, &cBinop_nodTO8Sm_sendMessage);
}

void Heavy_2tone_20::cMsg_Yg7pIsp4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_Ar2cfKfb_sendMessage);
}

void Heavy_2tone_20::cBinop_PJnj0tv3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_W2GAvVrH_sendMessage);
}

void Heavy_2tone_20::cBinop_W2GAvVrH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_KJIbHGxc_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_I5MdycSC, m);
}

void Heavy_2tone_20::cBinop_KJIbHGxc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_FDghQdDA, m);
}

void Heavy_2tone_20::cSlice_X7ALEfVC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_7445UdKJ, 1, m, &cPack_7445UdKJ_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_n50EIq21_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_7445UdKJ, 0, m, &cPack_7445UdKJ_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_RlcRSxI0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_9kEnESpi, 1, m, &cPack_9kEnESpi_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_glou201g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_9kEnESpi, 0, m, &cPack_9kEnESpi_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_SyBOOAui_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_1UFAExeO, 1, m, &cPack_1UFAExeO_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_xY6h08oE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_1UFAExeO, 0, m, &cPack_1UFAExeO_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_6UGDeWwA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 24.0f, 0, m, &cBinop_OdNCGeBN_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cSlice_54uviXs8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 4.0f, 0, m, &cBinop_dg7BsvOU_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_2tone_20::cBinop_NF41T0la_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_laAbUYsE_sendMessage);
}

void Heavy_2tone_20::cBinop_laAbUYsE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_Kpxur5Em_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_33gP6RGR_sendMessage);
}

void Heavy_2tone_20::cVar_eNRKlm3M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_2SUsTwaH_sendMessage);
}

void Heavy_2tone_20::cMsg_tYl9h0tJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_gd3g8ob9_sendMessage);
}

void Heavy_2tone_20::cSystem_gd3g8ob9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_kaEEwbwj, HV_BINOP_DIVIDE, 1, m, &cBinop_kaEEwbwj_sendMessage);
}

void Heavy_2tone_20::cBinop_Kpxur5Em_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_VR03n9cV_sendMessage);
}

void Heavy_2tone_20::cBinop_VR03n9cV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_TP3AeMhX, m);
}

void Heavy_2tone_20::cMsg_jmS8ZB4x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_7psX8oTj_sendMessage);
}

void Heavy_2tone_20::cBinop_7psX8oTj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_NF41T0la_sendMessage);
}

void Heavy_2tone_20::cBinop_33gP6RGR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Hiok0H9n, m);
}

void Heavy_2tone_20::cBinop_2SUsTwaH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_EGUORPT2_sendMessage);
}

void Heavy_2tone_20::cBinop_EGUORPT2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_kaEEwbwj, HV_BINOP_DIVIDE, 0, m, &cBinop_kaEEwbwj_sendMessage);
}

void Heavy_2tone_20::cBinop_kaEEwbwj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jmS8ZB4x_sendMessage(_c, 0, m);
}

void Heavy_2tone_20::cBinop_dg7BsvOU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_9ZP8j2dg, 0, m);
}

void Heavy_2tone_20::cPack_iI5ce5L5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_of1Lkwag_sendMessage(_c, 0, m);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cCast_mpquhSbO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_2tone_20::cCast_0TaNRAg0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_iI5ce5L5, 0, m, &cPack_iI5ce5L5_sendMessage);
}

void Heavy_2tone_20::cMsg_of1Lkwag_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(9);
  msg_init(m, 9, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "set");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setElementToFrom(m, 2, n, 1);
  msg_setElementToFrom(m, 3, n, 2);
  msg_setElementToFrom(m, 4, n, 3);
  msg_setElementToFrom(m, 5, n, 4);
  msg_setElementToFrom(m, 6, n, 5);
  msg_setElementToFrom(m, 7, n, 6);
  msg_setElementToFrom(m, 8, n, 7);
}

void Heavy_2tone_20::cMsg_k514posP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(8);
  msg_init(m, 8, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.52381f);
  msg_setFloat(m, 1, 0.52381f);
  msg_setFloat(m, 2, 0.0f);
  msg_setFloat(m, 3, 0.52381f);
  msg_setFloat(m, 4, 0.857143f);
  msg_setFloat(m, 5, 0.492063f);
  msg_setFloat(m, 6, 0.888889f);
  msg_setFloat(m, 7, 0.15873f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cMsg_ovusyvQR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(8);
  msg_init(m, 8, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.492063f);
  msg_setFloat(m, 1, 0.460317f);
  msg_setFloat(m, 2, 0.555556f);
  msg_setFloat(m, 3, 0.52381f);
  msg_setFloat(m, 4, 0.460317f);
  msg_setFloat(m, 5, 0.492063f);
  msg_setFloat(m, 6, 0.396825f);
  msg_setFloat(m, 7, 0.492063f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cMsg_Ldh5Ng89_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(8);
  msg_init(m, 8, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.174603f);
  msg_setFloat(m, 1, 0.396825f);
  msg_setFloat(m, 2, 0.619048f);
  msg_setFloat(m, 3, 0.587302f);
  msg_setFloat(m, 4, 0.428571f);
  msg_setFloat(m, 5, 0.460317f);
  msg_setFloat(m, 6, 0.492063f);
  msg_setFloat(m, 7, 0.396825f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cMsg_BN2fAO32_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(8);
  msg_init(m, 8, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.126984f);
  msg_setFloat(m, 1, 0.333333f);
  msg_setFloat(m, 2, 0.619048f);
  msg_setFloat(m, 3, 0.126984f);
  msg_setFloat(m, 4, 0.412698f);
  msg_setFloat(m, 5, 0.460317f);
  msg_setFloat(m, 6, 0.507937f);
  msg_setFloat(m, 7, 0.396825f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cMsg_vhJJio04_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(8);
  msg_init(m, 8, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.126984f);
  msg_setFloat(m, 1, 0.190476f);
  msg_setFloat(m, 2, 0.730159f);
  msg_setFloat(m, 3, 0.0793651f);
  msg_setFloat(m, 4, 0.0f);
  msg_setFloat(m, 5, 0.460317f);
  msg_setFloat(m, 6, 0.507937f);
  msg_setFloat(m, 7, 0.0634921f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cMsg_WMn78hY6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(8);
  msg_init(m, 8, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.793651f);
  msg_setFloat(m, 1, 0.793651f);
  msg_setFloat(m, 2, 0.793651f);
  msg_setFloat(m, 3, 0.0f);
  msg_setFloat(m, 4, 0.0634921f);
  msg_setFloat(m, 5, 0.460317f);
  msg_setFloat(m, 6, 0.269841f);
  msg_setFloat(m, 7, 0.0634921f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cMsg_tcyly44U_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(7);
  msg_init(m, 7, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setFloat(m, 1, 0.0f);
  msg_setFloat(m, 2, 0.0f);
  msg_setFloat(m, 3, 0.0f);
  msg_setFloat(m, 4, 0.0f);
  msg_setFloat(m, 5, 0.0f);
  msg_setFloat(m, 6, 0.0f);
  cSlice_onMessage(_c, &Context(_c)->cSlice_X7ALEfVC, 0, m, &cSlice_X7ALEfVC_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_n50EIq21, 0, m, &cSlice_n50EIq21_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_RlcRSxI0, 0, m, &cSlice_RlcRSxI0_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_glou201g, 0, m, &cSlice_glou201g_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_SyBOOAui, 0, m, &cSlice_SyBOOAui_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_xY6h08oE, 0, m, &cSlice_xY6h08oE_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6UGDeWwA, 0, m, &cSlice_6UGDeWwA_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_54uviXs8, 0, m, &cSlice_54uviXs8_sendMessage);
}

void Heavy_2tone_20::cReceive_fSqdCCNa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_uQusyC3c_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_imDlcvHY, 0, m, &cVar_imDlcvHY_sendMessage);
  cMsg_tYl9h0tJ_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_eNRKlm3M, 0, m, &cVar_eNRKlm3M_sendMessage);
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

int Heavy_2tone_20::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6, Bf7, Bf8, Bf9, Bf10, Bf11, Bf12, Bf13;

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
    __hv_phasor_k_f(&sPhasor_9ZP8j2dg, VOf(Bf0));
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
    __hv_var_k_f(VOf(Bf3), 10000.0f, 10000.0f, 10000.0f, 10000.0f, 10000.0f, 10000.0f, 10000.0f, 10000.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_zero_f(VOf(Bf3));
    __hv_max_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_I5MdycSC, VOf(Bf1));
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_FDghQdDA, VOf(Bf3));
    __hv_rpole_f(&sRPole_PobEBZuf, VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_phasor_k_f(&sPhasor_qmD0A5Zm, VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_abs_f(VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf5), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf4), VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf1), VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_tFvCoT2w, VOf(Bf2));
    __hv_add_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_floor_f(VIf(Bf2), VOf(Bf0));
    __hv_sub_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_abs_f(VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf0));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf7), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf8), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf1), VIf(Bf8), VOf(Bf8));
    __hv_sub_f(VIf(Bf2), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf5), VIf(Bf7), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf7), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf4), VIf(Bf7), VOf(Bf7));
    __hv_sub_f(VIf(Bf8), VIf(Bf7), VOf(Bf7));
    __hv_fma_f(VIf(Bf0), VIf(Bf6), VIf(Bf7), VOf(Bf7));
    __hv_phasor_k_f(&sPhasor_zpbfVUrk, VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f);
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_min_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_zero_f(VOf(Bf8));
    __hv_max_f(VIf(Bf6), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf6), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_var_k_f(VOf(Bf4), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_fms_f(VIf(Bf8), VIf(Bf6), VIf(Bf4), VOf(Bf4));
    __hv_floor_f(VIf(Bf4), VOf(Bf6));
    __hv_sub_f(VIf(Bf4), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf4), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf6), VIf(Bf4), VOf(Bf4));
    __hv_abs_f(VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf6), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf4), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf4), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf6), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf4), VOf(Bf6));
    __hv_mul_f(VIf(Bf4), VIf(Bf6), VOf(Bf8));
    __hv_mul_f(VIf(Bf8), VIf(Bf6), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf6), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf1), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf9), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf10), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf8), VIf(Bf10), VOf(Bf10));
    __hv_sub_f(VIf(Bf4), VIf(Bf10), VOf(Bf10));
    __hv_fma_f(VIf(Bf5), VIf(Bf9), VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf9), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf2), VIf(Bf9), VOf(Bf9));
    __hv_sub_f(VIf(Bf10), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf6), VIf(Bf1), VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf1), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_min_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf6), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_max_f(VIf(Bf1), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_sub_f(VIf(Bf6), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf6), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_var_k_f(VOf(Bf10), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_fms_f(VIf(Bf1), VIf(Bf6), VIf(Bf10), VOf(Bf10));
    __hv_floor_f(VIf(Bf10), VOf(Bf6));
    __hv_sub_f(VIf(Bf10), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf10), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf6), VIf(Bf10), VOf(Bf10));
    __hv_abs_f(VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf6), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf10), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf10), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf6), VIf(Bf10), VOf(Bf10));
    __hv_mul_f(VIf(Bf10), VIf(Bf10), VOf(Bf6));
    __hv_mul_f(VIf(Bf10), VIf(Bf6), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf6), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf6), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf4), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf8), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf11), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf1), VIf(Bf11), VOf(Bf11));
    __hv_sub_f(VIf(Bf10), VIf(Bf11), VOf(Bf11));
    __hv_fma_f(VIf(Bf2), VIf(Bf8), VIf(Bf11), VOf(Bf11));
    __hv_var_k_f(VOf(Bf8), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf5), VIf(Bf8), VOf(Bf8));
    __hv_sub_f(VIf(Bf11), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf6), VIf(Bf4), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf4), 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f);
    __hv_min_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf0), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_max_f(VIf(Bf4), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf4), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_sub_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_var_k_f(VOf(Bf6), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_fms_f(VIf(Bf4), VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_floor_f(VIf(Bf6), VOf(Bf0));
    __hv_sub_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_abs_f(VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf6), VOf(Bf0));
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf0), VOf(Bf11));
    __hv_mul_f(VIf(Bf11), VIf(Bf0), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf10), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf1), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_sub_f(VIf(Bf6), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf11), VIf(Bf10), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf10), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf5), VIf(Bf10), VOf(Bf10));
    __hv_sub_f(VIf(Bf1), VIf(Bf10), VOf(Bf10));
    __hv_fma_f(VIf(Bf0), VIf(Bf2), VIf(Bf10), VOf(Bf10));
    __hv_phasor_k_f(&sPhasor_0kfnL0rA, VOf(Bf2));
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_abs_f(VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf0), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf0), VIf(Bf2), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf5), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf11), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf1), VIf(Bf11), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf2), VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_P3jZSEGI, VOf(Bf5));
    __hv_add_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_floor_f(VIf(Bf5), VOf(Bf0));
    __hv_sub_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_abs_f(VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf5), VOf(Bf0));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf11));
    __hv_mul_f(VIf(Bf11), VIf(Bf0), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf4), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf12), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf2), VIf(Bf12), VOf(Bf12));
    __hv_sub_f(VIf(Bf5), VIf(Bf12), VOf(Bf12));
    __hv_fma_f(VIf(Bf11), VIf(Bf4), VIf(Bf12), VOf(Bf12));
    __hv_var_k_f(VOf(Bf4), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf1), VIf(Bf4), VOf(Bf4));
    __hv_sub_f(VIf(Bf12), VIf(Bf4), VOf(Bf4));
    __hv_fma_f(VIf(Bf0), VIf(Bf6), VIf(Bf4), VOf(Bf4));
    __hv_phasor_k_f(&sPhasor_E9yVHxje, VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_abs_f(VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf6));
    __hv_mul_f(VIf(Bf0), VIf(Bf6), VOf(Bf12));
    __hv_mul_f(VIf(Bf12), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf1), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf11), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf12), VIf(Bf11), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf6), VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_TpNybESq, VOf(Bf1));
    __hv_add_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_floor_f(VIf(Bf1), VOf(Bf0));
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf11));
    __hv_mul_f(VIf(Bf11), VIf(Bf0), VOf(Bf12));
    __hv_mul_f(VIf(Bf12), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf2), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf13), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf6), VIf(Bf13), VOf(Bf13));
    __hv_sub_f(VIf(Bf1), VIf(Bf13), VOf(Bf13));
    __hv_fma_f(VIf(Bf11), VIf(Bf2), VIf(Bf13), VOf(Bf13));
    __hv_var_k_f(VOf(Bf2), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf12), VIf(Bf2), VOf(Bf2));
    __hv_sub_f(VIf(Bf13), VIf(Bf2), VOf(Bf2));
    __hv_fma_f(VIf(Bf0), VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf10), VOf(Bf10));
    __hv_fma_f(VIf(Bf4), VIf(Bf8), VIf(Bf10), VOf(Bf10));
    __hv_fma_f(VIf(Bf7), VIf(Bf9), VIf(Bf10), VOf(Bf10));
    __hv_mul_f(VIf(Bf3), VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf3), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_mul_f(VIf(Bf10), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_Hiok0H9n, VOf(Bf10));
    __hv_rpole_f(&sRPole_ol4rDE3i, VIf(Bf3), VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_DXMWtpzV, VIf(Bf10), VOf(Bf9));
    __hv_mul_f(VIf(Bf9), VIf(Bf3), VOf(Bf3));
    __hv_sub_f(VIf(Bf10), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_TP3AeMhX, VOf(Bf10));
    __hv_mul_f(VIf(Bf3), VIf(Bf10), VOf(Bf10));
    __hv_add_f(VIf(Bf10), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf10), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_2tone_20::processInline(float *inputBuffers, float *outputBuffers, int n4) {
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

int Heavy_2tone_20::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
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
