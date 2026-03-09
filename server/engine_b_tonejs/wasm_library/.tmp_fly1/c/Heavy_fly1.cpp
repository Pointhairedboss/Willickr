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

#include "Heavy_fly1.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_fly1 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_fly1_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_fly1));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_fly1(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_fly1_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_fly1));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_fly1(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_fly1_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_fly1();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_fly1::Heavy_fly1(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_tz4Plguy, 0.0f, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_GwhtcM2T, &hTable_Pvro5czw);
  numBytes += sTabwrite_init(&sTabwrite_oohy4Zsc, &hTable_Cf6ptvy3);
  numBytes += sTabwrite_init(&sTabwrite_NGZXgHpn, &hTable_bPdQxkoi);
  numBytes += sTabwrite_init(&sTabwrite_wbN09ZOy, &hTable_aiBzM6bW);
  numBytes += sRPole_init(&sRPole_qST1ApRr);
  numBytes += sDel1_init(&sDel1_V6sRg3jX);
  numBytes += sTabwrite_init(&sTabwrite_9SJaraAz, &hTable_EnHQk7d0);
  numBytes += cVar_init_f(&cVar_FscvEiDf, 0.0f);
  numBytes += sVarf_init(&sVarf_8tpg2s8p, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_lq3VDEzs, 700.0f);
  numBytes += cBinop_init(&cBinop_DL35KU6o, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_EYY0DrXZ, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_zRtCE5R4, 0.0f);
  numBytes += hTable_init(&hTable_Pvro5czw, 100);
  numBytes += cDelay_init(this, &cDelay_LBCg28hU, 0.0f);
  numBytes += cVar_init_s(&cVar_vhzazwWF, "A");
  numBytes += cSlice_init(&cSlice_g2MJJ4mM, 1, 1);
  numBytes += cSlice_init(&cSlice_vtaRrDMe, 1, 1);
  numBytes += cBinop_init(&cBinop_37OH0qLQ, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_k3HmGgEK, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_LhVF2i9n, 0.0f);
  numBytes += cVar_init_f(&cVar_7X9OtB0Y, 50.0f);
  numBytes += cBinop_init(&cBinop_sYczhr8e, 0.0f); // __mul
  numBytes += hTable_init(&hTable_Cf6ptvy3, 100);
  numBytes += cDelay_init(this, &cDelay_jEt9h5FX, 0.0f);
  numBytes += cVar_init_s(&cVar_MjUKg1lG, "B");
  numBytes += cSlice_init(&cSlice_5UxknBrR, 1, 1);
  numBytes += cSlice_init(&cSlice_O7YVyjS6, 1, 1);
  numBytes += cBinop_init(&cBinop_QrVLahKJ, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_W0EHI4EL, 0.0f); // __sub
  numBytes += hTable_init(&hTable_bPdQxkoi, 100);
  numBytes += cDelay_init(this, &cDelay_fE0xv6iW, 0.0f);
  numBytes += cVar_init_s(&cVar_z5l7Sxv0, "C");
  numBytes += cSlice_init(&cSlice_pgM10CMO, 1, 1);
  numBytes += cSlice_init(&cSlice_icrr9XOK, 1, 1);
  numBytes += cBinop_init(&cBinop_bb5kKs3B, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_lSEDa4wg, 0.0f); // __sub
  numBytes += hTable_init(&hTable_aiBzM6bW, 100);
  numBytes += cDelay_init(this, &cDelay_kmhLKMoY, 0.0f);
  numBytes += cVar_init_s(&cVar_dRDN6XBE, "D");
  numBytes += cSlice_init(&cSlice_9pvMWQqM, 1, 1);
  numBytes += cSlice_init(&cSlice_SZIFtoGl, 1, 1);
  numBytes += cBinop_init(&cBinop_8iz8fBZv, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_g8wJ8QxE, 0.0f); // __sub
  numBytes += hTable_init(&hTable_EnHQk7d0, 100);
  numBytes += cDelay_init(this, &cDelay_A9FwP2lj, 0.0f);
  numBytes += cVar_init_s(&cVar_be6rmBRc, "E");
  numBytes += cSlice_init(&cSlice_72ci4kZk, 1, 1);
  numBytes += cSlice_init(&cSlice_KJLJ8ieD, 1, 1);
  numBytes += cBinop_init(&cBinop_ePLOraPT, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_lxUuBviD, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_IpE1q8uJ, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_fly1::~Heavy_fly1() {
  hTable_free(&hTable_Pvro5czw);
  hTable_free(&hTable_Cf6ptvy3);
  hTable_free(&hTable_bPdQxkoi);
  hTable_free(&hTable_aiBzM6bW);
  hTable_free(&hTable_EnHQk7d0);
}

HvTable *Heavy_fly1::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_Pvro5czw; // A
    case 0xD961DF96: return &hTable_Cf6ptvy3; // B
    case 0x7F1A5B02: return &hTable_bPdQxkoi; // C
    case 0xB0C12D6E: return &hTable_aiBzM6bW; // D
    case 0x48BA38A1: return &hTable_EnHQk7d0; // E
    default: return nullptr;
  }
}

void Heavy_fly1::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_8SmdVsCr_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_iTNkiuhZ_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_fly1::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_fly1::cVar_FscvEiDf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 100.0f, 0, m, &cBinop_TmeE09Fq_sendMessage);
}

void Heavy_fly1::cBinop_PSPnePpx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_sFJOLY8W_sendMessage);
}

void Heavy_fly1::cBinop_sFJOLY8W_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_5ZCBEGGs_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_WH1mmw3U_sendMessage);
}

void Heavy_fly1::cVar_lq3VDEzs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_ZCqfWhNt_sendMessage);
}

void Heavy_fly1::cMsg_DI97FRsV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_BBGfvBm8_sendMessage);
}

void Heavy_fly1::cSystem_BBGfvBm8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_DL35KU6o, HV_BINOP_DIVIDE, 1, m, &cBinop_DL35KU6o_sendMessage);
}

void Heavy_fly1::cBinop_5ZCBEGGs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_yA5ZvjJh_sendMessage);
}

void Heavy_fly1::cBinop_yA5ZvjJh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_EYY0DrXZ, m);
}

void Heavy_fly1::cMsg_MziFSBzj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_o8njDEnK_sendMessage);
}

void Heavy_fly1::cBinop_o8njDEnK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_PSPnePpx_sendMessage);
}

void Heavy_fly1::cBinop_WH1mmw3U_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_8tpg2s8p, m);
}

void Heavy_fly1::cBinop_ZCqfWhNt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_FNMzbwAN_sendMessage);
}

void Heavy_fly1::cBinop_FNMzbwAN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_DL35KU6o, HV_BINOP_DIVIDE, 0, m, &cBinop_DL35KU6o_sendMessage);
}

void Heavy_fly1::cBinop_DL35KU6o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_MziFSBzj_sendMessage(_c, 0, m);
}

void Heavy_fly1::cVar_zRtCE5R4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_tz4Plguy, 0, m);
}

void Heavy_fly1::hTable_Pvro5czw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fly1::cSwitchcase_2mCltRkf_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_vtaRrDMe, 0, m, &cSlice_vtaRrDMe_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_3rb1W2yD_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_g2MJJ4mM, 0, m, &cSlice_g2MJJ4mM_sendMessage);
      break;
    }
    default: {
      cMsg_M7ox2dKd_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fly1::cDelay_LBCg28hU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_LBCg28hU, m);
  cMsg_3rb1W2yD_sendMessage(_c, 0, m);
}

void Heavy_fly1::cVar_vhzazwWF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_xDZLpIJQ_sendMessage(_c, 0, m);
}

void Heavy_fly1::cSlice_g2MJJ4mM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_GwhtcM2T, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_vhzazwWF, 0, m, &cVar_vhzazwWF_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cSlice_vtaRrDMe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_GwhtcM2T, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_k3HmGgEK, HV_BINOP_SUBTRACT, 0, m, &cBinop_k3HmGgEK_sendMessage);
      break;
    }
    case 1: {
      cMsg_eei5R8H4_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cBinop_l0aGGGJg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_37OH0qLQ, HV_BINOP_DIVIDE, 1, m, &cBinop_37OH0qLQ_sendMessage);
}

void Heavy_fly1::cBinop_37OH0qLQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_XfHID6KD_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LBCg28hU, 1, m, &cDelay_LBCg28hU_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LBCg28hU, 0, m, &cDelay_LBCg28hU_sendMessage);
}

void Heavy_fly1::cMsg_M7ox2dKd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_GwhtcM2T, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_k3HmGgEK, HV_BINOP_SUBTRACT, 0, m, &cBinop_k3HmGgEK_sendMessage);
}

void Heavy_fly1::cSystem_XUUgCycg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_k3HmGgEK, HV_BINOP_SUBTRACT, 1, m, &cBinop_k3HmGgEK_sendMessage);
}

void Heavy_fly1::cMsg_xDZLpIJQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_XUUgCycg_sendMessage);
}

void Heavy_fly1::cBinop_k3HmGgEK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_FV3hd8Gq_sendMessage);
}

void Heavy_fly1::cBinop_FV3hd8Gq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_37OH0qLQ, HV_BINOP_DIVIDE, 0, m, &cBinop_37OH0qLQ_sendMessage);
}

void Heavy_fly1::cMsg_XfHID6KD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_LBCg28hU, 0, m, &cDelay_LBCg28hU_sendMessage);
}

void Heavy_fly1::cMsg_3rb1W2yD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_GwhtcM2T, 1, m, NULL);
}

void Heavy_fly1::cMsg_LHhFdRuW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_4S3eQ4HQ_sendMessage);
}

void Heavy_fly1::cSystem_4S3eQ4HQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_l0aGGGJg_sendMessage);
}

void Heavy_fly1::cMsg_eei5R8H4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_GwhtcM2T, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_k3HmGgEK, HV_BINOP_SUBTRACT, 0, m, &cBinop_k3HmGgEK_sendMessage);
}

void Heavy_fly1::cCast_DLpTh3l3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_HdrVv0cn_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fly1::cSwitchcase_HdrVv0cn_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_hODYm5xm_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_hODYm5xm_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_kfAcB895_sendMessage);
      break;
    }
  }
}

void Heavy_fly1::cDelay_LhVF2i9n_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_LhVF2i9n, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LhVF2i9n, 0, m, &cDelay_LhVF2i9n_sendMessage);
  cSwitchcase_2mCltRkf_onMessage(_c, NULL, 0, m, NULL);
  cSend_xKJ38eOW_sendMessage(_c, 0, m);
}

void Heavy_fly1::cCast_kfAcB895_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_hODYm5xm_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_LhVF2i9n, 0, m, &cDelay_LhVF2i9n_sendMessage);
  cSwitchcase_2mCltRkf_onMessage(_c, NULL, 0, m, NULL);
  cSend_xKJ38eOW_sendMessage(_c, 0, m);
}

void Heavy_fly1::cMsg_XwUlFWbn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_yiTUmE29_sendMessage);
}

void Heavy_fly1::cSystem_yiTUmE29_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_6cjiJyIR_sendMessage);
}

void Heavy_fly1::cVar_7X9OtB0Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sYczhr8e, HV_BINOP_MULTIPLY, 0, m, &cBinop_sYczhr8e_sendMessage);
}

void Heavy_fly1::cMsg_hODYm5xm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_LhVF2i9n, 0, m, &cDelay_LhVF2i9n_sendMessage);
}

void Heavy_fly1::cBinop_a62DpukI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_LhVF2i9n, 2, m, &cDelay_LhVF2i9n_sendMessage);
}

void Heavy_fly1::cBinop_6cjiJyIR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sYczhr8e, HV_BINOP_MULTIPLY, 1, m, &cBinop_sYczhr8e_sendMessage);
}

void Heavy_fly1::cBinop_sYczhr8e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_a62DpukI_sendMessage);
}

void Heavy_fly1::cSend_xKJ38eOW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_iTNkiuhZ_sendMessage(_c, 0, m);
}

void Heavy_fly1::hTable_Cf6ptvy3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fly1::cSwitchcase_11snfWnE_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_O7YVyjS6, 0, m, &cSlice_O7YVyjS6_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_1xT99EpG_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_5UxknBrR, 0, m, &cSlice_5UxknBrR_sendMessage);
      break;
    }
    default: {
      cMsg_4uytPlY9_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fly1::cDelay_jEt9h5FX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_jEt9h5FX, m);
  cMsg_1xT99EpG_sendMessage(_c, 0, m);
}

void Heavy_fly1::cVar_MjUKg1lG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_FqKuiuxQ_sendMessage(_c, 0, m);
}

void Heavy_fly1::cSlice_5UxknBrR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_oohy4Zsc, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_MjUKg1lG, 0, m, &cVar_MjUKg1lG_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cSlice_O7YVyjS6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_oohy4Zsc, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_W0EHI4EL, HV_BINOP_SUBTRACT, 0, m, &cBinop_W0EHI4EL_sendMessage);
      break;
    }
    case 1: {
      cMsg_PZqkHeC8_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cBinop_cUxe6INp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_QrVLahKJ, HV_BINOP_DIVIDE, 1, m, &cBinop_QrVLahKJ_sendMessage);
}

void Heavy_fly1::cBinop_QrVLahKJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_qqUS7SoP_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_jEt9h5FX, 1, m, &cDelay_jEt9h5FX_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_jEt9h5FX, 0, m, &cDelay_jEt9h5FX_sendMessage);
}

void Heavy_fly1::cMsg_4uytPlY9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_oohy4Zsc, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_W0EHI4EL, HV_BINOP_SUBTRACT, 0, m, &cBinop_W0EHI4EL_sendMessage);
}

void Heavy_fly1::cSystem_zf7UqAi9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_W0EHI4EL, HV_BINOP_SUBTRACT, 1, m, &cBinop_W0EHI4EL_sendMessage);
}

void Heavy_fly1::cMsg_FqKuiuxQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_zf7UqAi9_sendMessage);
}

void Heavy_fly1::cBinop_W0EHI4EL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_6YlNJl1S_sendMessage);
}

void Heavy_fly1::cBinop_6YlNJl1S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_QrVLahKJ, HV_BINOP_DIVIDE, 0, m, &cBinop_QrVLahKJ_sendMessage);
}

void Heavy_fly1::cMsg_qqUS7SoP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_jEt9h5FX, 0, m, &cDelay_jEt9h5FX_sendMessage);
}

void Heavy_fly1::cMsg_1xT99EpG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_oohy4Zsc, 1, m, NULL);
}

void Heavy_fly1::cMsg_LLpiTgWZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_QPVbfsTG_sendMessage);
}

void Heavy_fly1::cSystem_QPVbfsTG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_cUxe6INp_sendMessage);
}

void Heavy_fly1::cMsg_PZqkHeC8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_oohy4Zsc, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_W0EHI4EL, HV_BINOP_SUBTRACT, 0, m, &cBinop_W0EHI4EL_sendMessage);
}

void Heavy_fly1::hTable_bPdQxkoi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fly1::cSwitchcase_05bjHDSD_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_icrr9XOK, 0, m, &cSlice_icrr9XOK_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_6i7Cbaje_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_pgM10CMO, 0, m, &cSlice_pgM10CMO_sendMessage);
      break;
    }
    default: {
      cMsg_YPQjRMQp_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fly1::cDelay_fE0xv6iW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_fE0xv6iW, m);
  cMsg_6i7Cbaje_sendMessage(_c, 0, m);
}

void Heavy_fly1::cVar_z5l7Sxv0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_GYcVOske_sendMessage(_c, 0, m);
}

void Heavy_fly1::cSlice_pgM10CMO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_NGZXgHpn, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_z5l7Sxv0, 0, m, &cVar_z5l7Sxv0_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cSlice_icrr9XOK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_NGZXgHpn, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_lSEDa4wg, HV_BINOP_SUBTRACT, 0, m, &cBinop_lSEDa4wg_sendMessage);
      break;
    }
    case 1: {
      cMsg_pq4B9lsq_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cBinop_MwRm49Ri_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_bb5kKs3B, HV_BINOP_DIVIDE, 1, m, &cBinop_bb5kKs3B_sendMessage);
}

void Heavy_fly1::cBinop_bb5kKs3B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_setbk8th_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_fE0xv6iW, 1, m, &cDelay_fE0xv6iW_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_fE0xv6iW, 0, m, &cDelay_fE0xv6iW_sendMessage);
}

void Heavy_fly1::cMsg_YPQjRMQp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_NGZXgHpn, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lSEDa4wg, HV_BINOP_SUBTRACT, 0, m, &cBinop_lSEDa4wg_sendMessage);
}

void Heavy_fly1::cSystem_l14ihcIO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lSEDa4wg, HV_BINOP_SUBTRACT, 1, m, &cBinop_lSEDa4wg_sendMessage);
}

void Heavy_fly1::cMsg_GYcVOske_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_l14ihcIO_sendMessage);
}

void Heavy_fly1::cBinop_lSEDa4wg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_bpboy8Pj_sendMessage);
}

void Heavy_fly1::cBinop_bpboy8Pj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_bb5kKs3B, HV_BINOP_DIVIDE, 0, m, &cBinop_bb5kKs3B_sendMessage);
}

void Heavy_fly1::cMsg_setbk8th_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_fE0xv6iW, 0, m, &cDelay_fE0xv6iW_sendMessage);
}

void Heavy_fly1::cMsg_6i7Cbaje_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_NGZXgHpn, 1, m, NULL);
}

void Heavy_fly1::cMsg_F0y4NQmX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_qQSUGCZJ_sendMessage);
}

void Heavy_fly1::cSystem_qQSUGCZJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_MwRm49Ri_sendMessage);
}

void Heavy_fly1::cMsg_pq4B9lsq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_NGZXgHpn, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lSEDa4wg, HV_BINOP_SUBTRACT, 0, m, &cBinop_lSEDa4wg_sendMessage);
}

void Heavy_fly1::hTable_aiBzM6bW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fly1::cSwitchcase_EpSYHmaB_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_SZIFtoGl, 0, m, &cSlice_SZIFtoGl_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_CykuCGdT_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_9pvMWQqM, 0, m, &cSlice_9pvMWQqM_sendMessage);
      break;
    }
    default: {
      cMsg_Cdxs5ODg_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fly1::cDelay_kmhLKMoY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_kmhLKMoY, m);
  cMsg_CykuCGdT_sendMessage(_c, 0, m);
}

void Heavy_fly1::cVar_dRDN6XBE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_b4dbRCV5_sendMessage(_c, 0, m);
}

void Heavy_fly1::cSlice_9pvMWQqM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wbN09ZOy, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_dRDN6XBE, 0, m, &cVar_dRDN6XBE_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cSlice_SZIFtoGl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wbN09ZOy, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_g8wJ8QxE, HV_BINOP_SUBTRACT, 0, m, &cBinop_g8wJ8QxE_sendMessage);
      break;
    }
    case 1: {
      cMsg_vuUreMyj_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cBinop_PX5iHND2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8iz8fBZv, HV_BINOP_DIVIDE, 1, m, &cBinop_8iz8fBZv_sendMessage);
}

void Heavy_fly1::cBinop_8iz8fBZv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_xHW2QAPy_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kmhLKMoY, 1, m, &cDelay_kmhLKMoY_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kmhLKMoY, 0, m, &cDelay_kmhLKMoY_sendMessage);
}

void Heavy_fly1::cMsg_Cdxs5ODg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wbN09ZOy, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_g8wJ8QxE, HV_BINOP_SUBTRACT, 0, m, &cBinop_g8wJ8QxE_sendMessage);
}

void Heavy_fly1::cSystem_OFSKp5eL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_g8wJ8QxE, HV_BINOP_SUBTRACT, 1, m, &cBinop_g8wJ8QxE_sendMessage);
}

void Heavy_fly1::cMsg_b4dbRCV5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_OFSKp5eL_sendMessage);
}

void Heavy_fly1::cBinop_g8wJ8QxE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_SrhFFFDe_sendMessage);
}

void Heavy_fly1::cBinop_SrhFFFDe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8iz8fBZv, HV_BINOP_DIVIDE, 0, m, &cBinop_8iz8fBZv_sendMessage);
}

void Heavy_fly1::cMsg_xHW2QAPy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_kmhLKMoY, 0, m, &cDelay_kmhLKMoY_sendMessage);
}

void Heavy_fly1::cMsg_CykuCGdT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wbN09ZOy, 1, m, NULL);
}

void Heavy_fly1::cMsg_tlmFnjB2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_RLZeVpj2_sendMessage);
}

void Heavy_fly1::cSystem_RLZeVpj2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_PX5iHND2_sendMessage);
}

void Heavy_fly1::cMsg_vuUreMyj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_wbN09ZOy, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_g8wJ8QxE, HV_BINOP_SUBTRACT, 0, m, &cBinop_g8wJ8QxE_sendMessage);
}

void Heavy_fly1::hTable_EnHQk7d0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fly1::cSwitchcase_9GJLnqGH_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_KJLJ8ieD, 0, m, &cSlice_KJLJ8ieD_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_ilm2GS3t_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_72ci4kZk, 0, m, &cSlice_72ci4kZk_sendMessage);
      break;
    }
    default: {
      cMsg_FkALE6TU_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fly1::cDelay_A9FwP2lj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_A9FwP2lj, m);
  cMsg_ilm2GS3t_sendMessage(_c, 0, m);
}

void Heavy_fly1::cVar_be6rmBRc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_y0FJJRub_sendMessage(_c, 0, m);
}

void Heavy_fly1::cSlice_72ci4kZk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9SJaraAz, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_be6rmBRc, 0, m, &cVar_be6rmBRc_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cSlice_KJLJ8ieD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9SJaraAz, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_lxUuBviD, HV_BINOP_SUBTRACT, 0, m, &cBinop_lxUuBviD_sendMessage);
      break;
    }
    case 1: {
      cMsg_d8eEp8US_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fly1::cBinop_TIN53ZXr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ePLOraPT, HV_BINOP_DIVIDE, 1, m, &cBinop_ePLOraPT_sendMessage);
}

void Heavy_fly1::cBinop_ePLOraPT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_DrljkDI5_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_A9FwP2lj, 1, m, &cDelay_A9FwP2lj_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_A9FwP2lj, 0, m, &cDelay_A9FwP2lj_sendMessage);
}

void Heavy_fly1::cMsg_FkALE6TU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9SJaraAz, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lxUuBviD, HV_BINOP_SUBTRACT, 0, m, &cBinop_lxUuBviD_sendMessage);
}

void Heavy_fly1::cSystem_plteolKF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lxUuBviD, HV_BINOP_SUBTRACT, 1, m, &cBinop_lxUuBviD_sendMessage);
}

void Heavy_fly1::cMsg_y0FJJRub_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_plteolKF_sendMessage);
}

void Heavy_fly1::cBinop_lxUuBviD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Fll9vTJ4_sendMessage);
}

void Heavy_fly1::cBinop_Fll9vTJ4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ePLOraPT, HV_BINOP_DIVIDE, 0, m, &cBinop_ePLOraPT_sendMessage);
}

void Heavy_fly1::cMsg_DrljkDI5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_A9FwP2lj, 0, m, &cDelay_A9FwP2lj_sendMessage);
}

void Heavy_fly1::cMsg_ilm2GS3t_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9SJaraAz, 1, m, NULL);
}

void Heavy_fly1::cMsg_nRCZfrmq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Oh4GRRPp_sendMessage);
}

void Heavy_fly1::cSystem_Oh4GRRPp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_TIN53ZXr_sendMessage);
}

void Heavy_fly1::cMsg_d8eEp8US_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_9SJaraAz, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lxUuBviD, HV_BINOP_SUBTRACT, 0, m, &cBinop_lxUuBviD_sendMessage);
}

void Heavy_fly1::cBinop_TmeE09Fq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_IpE1q8uJ, m);
}

void Heavy_fly1::cReceive_8SmdVsCr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_vhzazwWF, 0, m, &cVar_vhzazwWF_sendMessage);
  cMsg_LHhFdRuW_sendMessage(_c, 0, m);
  cMsg_3rb1W2yD_sendMessage(_c, 0, m);
  cMsg_XwUlFWbn_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_7X9OtB0Y, 0, m, &cVar_7X9OtB0Y_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_MjUKg1lG, 0, m, &cVar_MjUKg1lG_sendMessage);
  cMsg_LLpiTgWZ_sendMessage(_c, 0, m);
  cMsg_1xT99EpG_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_z5l7Sxv0, 0, m, &cVar_z5l7Sxv0_sendMessage);
  cMsg_F0y4NQmX_sendMessage(_c, 0, m);
  cMsg_6i7Cbaje_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_dRDN6XBE, 0, m, &cVar_dRDN6XBE_sendMessage);
  cMsg_tlmFnjB2_sendMessage(_c, 0, m);
  cMsg_CykuCGdT_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_be6rmBRc, 0, m, &cVar_be6rmBRc_sendMessage);
  cMsg_nRCZfrmq_sendMessage(_c, 0, m);
  cMsg_ilm2GS3t_sendMessage(_c, 0, m);
  cMsg_DI97FRsV_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_lq3VDEzs, 0, m, &cVar_lq3VDEzs_sendMessage);
  cSwitchcase_HdrVv0cn_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fly1::cReceive_iTNkiuhZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_11snfWnE_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_05bjHDSD_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_EpSYHmaB_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_9GJLnqGH_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_fly1::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_phasor_k_f(&sPhasor_tz4Plguy, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_neg_f(VIf(Bf0), VOf(Bf2));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_add_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_min_f(VIf(Bf1), VIf(Bf3), VOf(Bf1));
    __hv_min_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_min_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f);
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_tabwrite_stoppable_f(&sTabwrite_GwhtcM2T, VIf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf1), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_mul_f(VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_zero_f(VOf(Bf3));
    __hv_min_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_tabwrite_stoppable_f(&sTabwrite_oohy4Zsc, VIf(Bf3));
    __hv_zero_f(VOf(Bf0));
    __hv_max_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf0), VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_NGZXgHpn, VIf(Bf0));
    __hv_varread_f(&sVarf_IpE1q8uJ, VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf1));
    __hv_floor_f(VIf(Bf1), VOf(Bf2));
    __hv_sub_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
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
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf7), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf8), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf9), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf4), VIf(Bf9), VOf(Bf9));
    __hv_sub_f(VIf(Bf2), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf5), VIf(Bf8), VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf8), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf6), VIf(Bf8), VOf(Bf8));
    __hv_sub_f(VIf(Bf9), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf1), VIf(Bf7), VIf(Bf8), VOf(Bf8));
    __hv_mul_f(VIf(Bf8), VIf(Bf3), VOf(Bf8));
    __hv_var_k_f(VOf(Bf7), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_fma_f(VIf(Bf8), VIf(Bf7), VIf(Bf3), VOf(Bf3));
    __hv_tabwrite_stoppable_f(&sTabwrite_wbN09ZOy, VIf(Bf3));
    __hv_var_k_f(VOf(Bf7), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_fma_f(VIf(Bf0), VIf(Bf7), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_8tpg2s8p, VOf(Bf7));
    __hv_rpole_f(&sRPole_qST1ApRr, VIf(Bf3), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_V6sRg3jX, VIf(Bf7), VOf(Bf0));
    __hv_mul_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_sub_f(VIf(Bf7), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_EYY0DrXZ, VOf(Bf7));
    __hv_mul_f(VIf(Bf3), VIf(Bf7), VOf(Bf7));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_mul_f(VIf(Bf7), VIf(Bf3), VOf(Bf3));
    __hv_tabwrite_stoppable_f(&sTabwrite_9SJaraAz, VIf(Bf3));
    __hv_add_f(VIf(Bf3), VIf(O0), VOf(O0));
    __hv_add_f(VIf(Bf3), VIf(O1), VOf(O1));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_fly1::processInline(float *inputBuffers, float *outputBuffers, int n4) {
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

int Heavy_fly1::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
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
