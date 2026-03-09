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

#include "Heavy_fan5.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_fan5 *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_fan5_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_fan5));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_fan5(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_fan5_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_fan5));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_fan5(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_fan5_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_fan5();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_fan5::Heavy_fan5(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sRPole_init(&sRPole_DXCRdDUm);
  numBytes += sPhasor_init(&sPhasor_bAUgZhoj, sampleRate);
  numBytes += sBiquad_k_init(&sBiquad_k_odBNp9ay, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sTabwrite_init(&sTabwrite_zXqGyPkz, &hTable_p4I42NaM);
  numBytes += sTabwrite_init(&sTabwrite_Vo79vvID, &hTable_qX8CbISf);
  numBytes += sTabwrite_init(&sTabwrite_IJtdaUda, &hTable_S1Yo1Ism);
  numBytes += sBiquad_k_init(&sBiquad_k_Fy314rNR, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sTabwrite_init(&sTabwrite_yGPAHk6D, &hTable_sl8X6nxd);
  numBytes += sTabwrite_init(&sTabwrite_VaKhSsAL, &hTable_LXuTqM7q);
  numBytes += sTabread_init(&sTabread_xO4pdvLF, &hTable_sl8X6nxd, true);
  numBytes += sTabread_init(&sTabread_wck5v1Vg, &hTable_LXuTqM7q, true);
  numBytes += cRandom_init(&cRandom_x9X5khnD, 728660042);
  numBytes += cSlice_init(&cSlice_HTnt8L9i, 1, 1);
  numBytes += sVari_init(&sVari_jmppcbIl, 0, 0, false);
  numBytes += cVar_init_f(&cVar_6vXtjVAS, 700.0f);
  numBytes += cVar_init_f(&cVar_QjWkAbu5, 1.0f);
  numBytes += cBinop_init(&cBinop_3tU0MzFm, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_kEM5Stdi, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_dcwJfTnf, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_apQUdgNE, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_lA2eClXw, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_tJePAhUC, 0.0f); // __mul
  numBytes += hTable_init(&hTable_p4I42NaM, 100);
  numBytes += cDelay_init(this, &cDelay_ahsXfXjs, 0.0f);
  numBytes += cVar_init_s(&cVar_BdtZ5ui2, "A");
  numBytes += cSlice_init(&cSlice_TXF6eu0E, 1, 1);
  numBytes += cSlice_init(&cSlice_TO23cAXF, 1, 1);
  numBytes += cBinop_init(&cBinop_99P2SU3T, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_JQcgdGKO, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_pIhRgbyL, 0.0f);
  numBytes += cVar_init_f(&cVar_0L2WoE4W, 200.0f);
  numBytes += cBinop_init(&cBinop_8I4lCzhb, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_tevNQiUa, 1.0f);
  numBytes += sVarf_init(&sVarf_NYvmHLRP, 0.2f, 0.0f, false);
  numBytes += cRandom_init(&cRandom_EfUaOpOz, -1133649665);
  numBytes += cSlice_init(&cSlice_xT7Alqbi, 1, 1);
  numBytes += sVari_init(&sVari_rwKe0k3n, 0, 0, false);
  numBytes += cVar_init_f(&cVar_rkCkqlnf, 4000.0f);
  numBytes += cVar_init_f(&cVar_rUDxfvhO, 1.0f);
  numBytes += cBinop_init(&cBinop_a2yxDYkk, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_phcxbz80, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_HTazhCcs, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_n0YU7EJp, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_KUOh206v, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_aNEdcUx3, 0.0f); // __mul
  numBytes += hTable_init(&hTable_qX8CbISf, 100);
  numBytes += cDelay_init(this, &cDelay_mRcBzT6L, 0.0f);
  numBytes += cVar_init_s(&cVar_EiaycPXl, "B");
  numBytes += cSlice_init(&cSlice_Svb34gWM, 1, 1);
  numBytes += cSlice_init(&cSlice_4NWAf18y, 1, 1);
  numBytes += cBinop_init(&cBinop_giNuAwkF, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_hUbH6J0h, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_jZVxDLLO, 0.0f, 0.0f, false);
  numBytes += hTable_init(&hTable_S1Yo1Ism, 100);
  numBytes += cDelay_init(this, &cDelay_3WE0LFgw, 0.0f);
  numBytes += cVar_init_s(&cVar_4QTxSalu, "C");
  numBytes += cSlice_init(&cSlice_PYJYliG6, 1, 1);
  numBytes += cSlice_init(&cSlice_e4DN5W2C, 1, 1);
  numBytes += cBinop_init(&cBinop_r7oEZDdv, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_UZk1pxZJ, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_UTsplJWF, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_VpHfd1O2, 0.0f, 0.0f, false);
  numBytes += cTabhead_init(&cTabhead_KA4ReXLP, &hTable_sl8X6nxd);
  numBytes += cVar_init_s(&cVar_Bt6ZXVH1, "del-a");
  numBytes += cDelay_init(this, &cDelay_CabsyshW, 22.0f);
  numBytes += cDelay_init(this, &cDelay_wrpYU0pn, 0.0f);
  numBytes += cBinop_init(&cBinop_UR7bOPUs, 22.0f); // __mul
  numBytes += cBinop_init(&cBinop_Irt3ug2E, 0.0f); // __sub
  numBytes += cBinop_init(&cBinop_z4Lxgga2, 0.0f); // __max
  numBytes += cBinop_init(&cBinop_2q0K6HEn, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_QqfRh0nR, 0.0f);
  numBytes += cDelay_init(this, &cDelay_PZSVi8YR, 0.0f);
  numBytes += hTable_init(&hTable_sl8X6nxd, 256);
  numBytes += cDelay_init(this, &cDelay_s1gmYAv7, 0.0f);
  numBytes += cDelay_init(this, &cDelay_AA16GBek, 0.0f);
  numBytes += hTable_init(&hTable_LXuTqM7q, 256);
  numBytes += cTabhead_init(&cTabhead_9tIVRY0Z, &hTable_LXuTqM7q);
  numBytes += cVar_init_s(&cVar_tabHvzGG, "del-b");
  numBytes += cDelay_init(this, &cDelay_nthuiEXL, 70.0f);
  numBytes += cDelay_init(this, &cDelay_Ony0ykKn, 0.0f);
  numBytes += cBinop_init(&cBinop_jf051dJF, 70.0f); // __mul
  numBytes += cBinop_init(&cBinop_YufXSgr3, 0.0f); // __sub
  numBytes += cBinop_init(&cBinop_uJtVIwrx, 0.0f); // __max
  numBytes += cBinop_init(&cBinop_iu2hDlXC, 0.0f); // __sub
  numBytes += cVar_init_f(&cVar_t7Fs3oHP, 0.1f);
  numBytes += cBinop_init(&cBinop_bKdWNsFq, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_I2erwRBn, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_d3me7osH, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_trz2L29X, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_yhDp3E8n, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_7nRpGgjH, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_tZpUyHg9, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_6hkgItsS, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_i25aRqqe, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_VPHZMRCn, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_fan5::~Heavy_fan5() {
  hTable_free(&hTable_p4I42NaM);
  hTable_free(&hTable_qX8CbISf);
  hTable_free(&hTable_S1Yo1Ism);
  hTable_free(&hTable_sl8X6nxd);
  hTable_free(&hTable_LXuTqM7q);
}

HvTable *Heavy_fan5::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_p4I42NaM; // A
    case 0xD961DF96: return &hTable_qX8CbISf; // B
    case 0x7F1A5B02: return &hTable_S1Yo1Ism; // C
    case 0x1839FFA2: return &hTable_sl8X6nxd; // del-a
    case 0xE6B501FD: return &hTable_LXuTqM7q; // del-b
    default: return nullptr;
  }
}

void Heavy_fan5::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_GbHYyzUQ_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_9EZlkex4_sendMessage);
      break;
    }
    case 0xF75BA5C5: { // brush-level
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_lXLrfsgd_sendMessage);
      break;
    }
    case 0xD63D1A: { // fan-level
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_K8vgUG5Q_sendMessage);
      break;
    }
    case 0x92F66DB2: { // fan-noise
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_yuSmtrGr_sendMessage);
      break;
    }
    case 0xEC7CF572: { // fan-pulsewidth
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_PV4bzj8A_sendMessage);
      break;
    }
    case 0x3DFC4E6: { // main-speed
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_wpKlYFLL_sendMessage);
      break;
    }
    case 0xD00B203: { // motor-level
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_9zwj0MKN_sendMessage);
      break;
    }
    case 0x85EE1430: { // motor-ratio
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_bX3xsffC_sendMessage);
      break;
    }
    case 0x1FB2797F: { // rotor-level
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_Iw7k4Je5_sendMessage);
      break;
    }
    case 0x3CA3E830: { // shutdown-ventilator
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_TFDYJPsV_sendMessage);
      break;
    }
    case 0x12B9F86A: { // stator-level
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_KThKoCZd_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_fan5::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_fan5::cSwitchcase_14puOi6D_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_HTnt8L9i, 0, m, &cSlice_HTnt8L9i_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_x9X5khnD, 0, m, &cRandom_x9X5khnD_sendMessage);
      break;
    }
  }
}

void Heavy_fan5::cBinop_AsqxdsEQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_0xCpQDWA_sendMessage);
}

void Heavy_fan5::cUnop_0xCpQDWA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_o6QuYzO5_sendMessage(_c, 0, m);
}

void Heavy_fan5::cRandom_x9X5khnD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_AsqxdsEQ_sendMessage);
}

void Heavy_fan5::cSlice_HTnt8L9i_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_x9X5khnD, 1, m, &cRandom_x9X5khnD_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cMsg_o6QuYzO5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_jmppcbIl, m);
}

void Heavy_fan5::cMsg_uCWHRy1Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_vsrSRFIv_sendMessage);
}

void Heavy_fan5::cSystem_vsrSRFIv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_3tU0MzFm, HV_BINOP_DIVIDE, 1, m, &cBinop_3tU0MzFm_sendMessage);
}

void Heavy_fan5::cVar_6vXtjVAS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_TtadUZVu_sendMessage);
}

void Heavy_fan5::cVar_QjWkAbu5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_Keo0LtRs_sendMessage);
}

void Heavy_fan5::cUnop_lNppuZKb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_EfgKzjjt_sendMessage);
}

void Heavy_fan5::cBinop_3tU0MzFm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_apQUdgNE, HV_BINOP_MULTIPLY, 1, m, &cBinop_apQUdgNE_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_lNppuZKb_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_kEM5Stdi, HV_BINOP_DIVIDE, 0, m, &cBinop_kEM5Stdi_sendMessage);
}

void Heavy_fan5::cBinop_TtadUZVu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_3tU0MzFm, HV_BINOP_DIVIDE, 0, m, &cBinop_3tU0MzFm_sendMessage);
}

void Heavy_fan5::cBinop_kEM5Stdi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_ey95eUqD_sendMessage);
}

void Heavy_fan5::cBinop_Tji6jSdj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_PeI6wtnx_sendMessage);
}

void Heavy_fan5::cBinop_PeI6wtnx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_gGo7I3ze_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_dcwJfTnf, HV_BINOP_MULTIPLY, 0, m, &cBinop_dcwJfTnf_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_apQUdgNE, HV_BINOP_MULTIPLY, 0, m, &cBinop_apQUdgNE_sendMessage);
}

void Heavy_fan5::cBinop_EfgKzjjt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dcwJfTnf, HV_BINOP_MULTIPLY, 1, m, &cBinop_dcwJfTnf_sendMessage);
}

void Heavy_fan5::cBinop_dcwJfTnf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_QMaDJQb0_sendMessage);
}

void Heavy_fan5::cCast_vGiZaC6q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_6vXtjVAS, 0, m, &cVar_6vXtjVAS_sendMessage);
}

void Heavy_fan5::cBinop_wqq5GpAH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_JYPHPFKL_sendMessage);
}

void Heavy_fan5::cBinop_JYPHPFKL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Fy314rNR, 5, m);
}

void Heavy_fan5::cBinop_QMaDJQb0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Fy314rNR, 4, m);
}

void Heavy_fan5::cBinop_WvachQzr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_tJePAhUC, HV_BINOP_MULTIPLY, 0, m, &cBinop_tJePAhUC_sendMessage);
}

void Heavy_fan5::cBinop_apQUdgNE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lA2eClXw, HV_BINOP_ADD, 1, m, &cBinop_lA2eClXw_sendMessage);
}

void Heavy_fan5::cBinop_gGo7I3ze_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_wqq5GpAH_sendMessage);
}

void Heavy_fan5::cBinop_lA2eClXw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_tJePAhUC, HV_BINOP_MULTIPLY, 1, m, &cBinop_tJePAhUC_sendMessage);
}

void Heavy_fan5::cBinop_tJePAhUC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Fy314rNR, 1, m);
}

void Heavy_fan5::cBinop_Keo0LtRs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_kEM5Stdi, HV_BINOP_DIVIDE, 1, m, &cBinop_kEM5Stdi_sendMessage);
}

void Heavy_fan5::cBinop_ey95eUqD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Tji6jSdj_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_lA2eClXw, HV_BINOP_ADD, 0, m, &cBinop_lA2eClXw_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_WvachQzr_sendMessage);
}

void Heavy_fan5::hTable_p4I42NaM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fan5::cSwitchcase_Eo9Nu4LB_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_TO23cAXF, 0, m, &cSlice_TO23cAXF_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_tZ3FtU1J_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_TXF6eu0E, 0, m, &cSlice_TXF6eu0E_sendMessage);
      break;
    }
    default: {
      cMsg_18qS0dvq_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fan5::cDelay_ahsXfXjs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_ahsXfXjs, m);
  cMsg_tZ3FtU1J_sendMessage(_c, 0, m);
}

void Heavy_fan5::cVar_BdtZ5ui2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_VtwlACzi_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSlice_TXF6eu0E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zXqGyPkz, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_BdtZ5ui2, 0, m, &cVar_BdtZ5ui2_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cSlice_TO23cAXF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zXqGyPkz, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_JQcgdGKO, HV_BINOP_SUBTRACT, 0, m, &cBinop_JQcgdGKO_sendMessage);
      break;
    }
    case 1: {
      cMsg_GjH79a8o_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cBinop_LVtckAVd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_99P2SU3T, HV_BINOP_DIVIDE, 1, m, &cBinop_99P2SU3T_sendMessage);
}

void Heavy_fan5::cBinop_99P2SU3T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_KfJ7hliM_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_ahsXfXjs, 1, m, &cDelay_ahsXfXjs_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_ahsXfXjs, 0, m, &cDelay_ahsXfXjs_sendMessage);
}

void Heavy_fan5::cMsg_18qS0dvq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zXqGyPkz, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_JQcgdGKO, HV_BINOP_SUBTRACT, 0, m, &cBinop_JQcgdGKO_sendMessage);
}

void Heavy_fan5::cSystem_836dOjfS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JQcgdGKO, HV_BINOP_SUBTRACT, 1, m, &cBinop_JQcgdGKO_sendMessage);
}

void Heavy_fan5::cMsg_VtwlACzi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_836dOjfS_sendMessage);
}

void Heavy_fan5::cBinop_JQcgdGKO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_hxM6JgOK_sendMessage);
}

void Heavy_fan5::cBinop_hxM6JgOK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_99P2SU3T, HV_BINOP_DIVIDE, 0, m, &cBinop_99P2SU3T_sendMessage);
}

void Heavy_fan5::cMsg_KfJ7hliM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_ahsXfXjs, 0, m, &cDelay_ahsXfXjs_sendMessage);
}

void Heavy_fan5::cMsg_tZ3FtU1J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zXqGyPkz, 1, m, NULL);
}

void Heavy_fan5::cMsg_dtNTwlQR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_T9Pt7BjR_sendMessage);
}

void Heavy_fan5::cSystem_T9Pt7BjR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_LVtckAVd_sendMessage);
}

void Heavy_fan5::cMsg_GjH79a8o_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zXqGyPkz, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_JQcgdGKO, HV_BINOP_SUBTRACT, 0, m, &cBinop_JQcgdGKO_sendMessage);
}

void Heavy_fan5::cSwitchcase_Cq7gacxD_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_0IFYE7QV_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_0IFYE7QV_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_d1jIkVFp_sendMessage);
      break;
    }
  }
}

void Heavy_fan5::cDelay_pIhRgbyL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_pIhRgbyL, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_pIhRgbyL, 0, m, &cDelay_pIhRgbyL_sendMessage);
  cSwitchcase_Eo9Nu4LB_onMessage(_c, NULL, 0, m, NULL);
  cSend_hSFkF9EM_sendMessage(_c, 0, m);
}

void Heavy_fan5::cCast_d1jIkVFp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_0IFYE7QV_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_pIhRgbyL, 0, m, &cDelay_pIhRgbyL_sendMessage);
  cSwitchcase_Eo9Nu4LB_onMessage(_c, NULL, 0, m, NULL);
  cSend_hSFkF9EM_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_d7whLdaT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_193VLGXc_sendMessage);
}

void Heavy_fan5::cSystem_193VLGXc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_AsZP6Jq0_sendMessage);
}

void Heavy_fan5::cVar_0L2WoE4W_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8I4lCzhb, HV_BINOP_MULTIPLY, 0, m, &cBinop_8I4lCzhb_sendMessage);
}

void Heavy_fan5::cMsg_0IFYE7QV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_pIhRgbyL, 0, m, &cDelay_pIhRgbyL_sendMessage);
}

void Heavy_fan5::cBinop_aBt1wuRa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_pIhRgbyL, 2, m, &cDelay_pIhRgbyL_sendMessage);
}

void Heavy_fan5::cBinop_AsZP6Jq0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8I4lCzhb, HV_BINOP_MULTIPLY, 1, m, &cBinop_8I4lCzhb_sendMessage);
}

void Heavy_fan5::cBinop_8I4lCzhb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_aBt1wuRa_sendMessage);
}

void Heavy_fan5::cVar_tevNQiUa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_7t8lEzn0_sendMessage);
  cSwitchcase_Cq7gacxD_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fan5::cBinop_7t8lEzn0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_tevNQiUa, 1, m, &cVar_tevNQiUa_sendMessage);
}

void Heavy_fan5::cSend_hSFkF9EM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_9EZlkex4_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSwitchcase_dOQmVsEl_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_xT7Alqbi, 0, m, &cSlice_xT7Alqbi_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_EfUaOpOz, 0, m, &cRandom_EfUaOpOz_sendMessage);
      break;
    }
  }
}

void Heavy_fan5::cBinop_GygHAOF7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_ebkGscwg_sendMessage);
}

void Heavy_fan5::cUnop_ebkGscwg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Gw6cng97_sendMessage(_c, 0, m);
}

void Heavy_fan5::cRandom_EfUaOpOz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_GygHAOF7_sendMessage);
}

void Heavy_fan5::cSlice_xT7Alqbi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_EfUaOpOz, 1, m, &cRandom_EfUaOpOz_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cMsg_Gw6cng97_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_rwKe0k3n, m);
}

void Heavy_fan5::cMsg_b3R9fHt1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_HRl6DIil_sendMessage);
}

void Heavy_fan5::cSystem_HRl6DIil_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_a2yxDYkk, HV_BINOP_DIVIDE, 1, m, &cBinop_a2yxDYkk_sendMessage);
}

void Heavy_fan5::cVar_rkCkqlnf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_mva9y7kM_sendMessage);
}

void Heavy_fan5::cVar_rUDxfvhO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_Lvtc9vou_sendMessage);
}

void Heavy_fan5::cUnop_qKOiARcS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_cjgQLieB_sendMessage);
}

void Heavy_fan5::cBinop_a2yxDYkk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_n0YU7EJp, HV_BINOP_MULTIPLY, 1, m, &cBinop_n0YU7EJp_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_qKOiARcS_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_phcxbz80, HV_BINOP_DIVIDE, 0, m, &cBinop_phcxbz80_sendMessage);
}

void Heavy_fan5::cBinop_mva9y7kM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_a2yxDYkk, HV_BINOP_DIVIDE, 0, m, &cBinop_a2yxDYkk_sendMessage);
}

void Heavy_fan5::cBinop_phcxbz80_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_hf8QQWTD_sendMessage);
}

void Heavy_fan5::cBinop_xlzqAk1P_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_BgrkAUUG_sendMessage);
}

void Heavy_fan5::cBinop_BgrkAUUG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_CKn5psfC_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_HTazhCcs, HV_BINOP_MULTIPLY, 0, m, &cBinop_HTazhCcs_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_n0YU7EJp, HV_BINOP_MULTIPLY, 0, m, &cBinop_n0YU7EJp_sendMessage);
}

void Heavy_fan5::cBinop_cjgQLieB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_HTazhCcs, HV_BINOP_MULTIPLY, 1, m, &cBinop_HTazhCcs_sendMessage);
}

void Heavy_fan5::cBinop_HTazhCcs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Ibx0kLxl_sendMessage);
}

void Heavy_fan5::cCast_LEqS40yW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_rkCkqlnf, 0, m, &cVar_rkCkqlnf_sendMessage);
}

void Heavy_fan5::cBinop_C8cKombn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_VFa1fYYp_sendMessage);
}

void Heavy_fan5::cBinop_VFa1fYYp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_odBNp9ay, 5, m);
}

void Heavy_fan5::cBinop_Ibx0kLxl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_odBNp9ay, 4, m);
}

void Heavy_fan5::cBinop_Hgx1wZbC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_aNEdcUx3, HV_BINOP_MULTIPLY, 0, m, &cBinop_aNEdcUx3_sendMessage);
}

void Heavy_fan5::cBinop_n0YU7EJp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KUOh206v, HV_BINOP_ADD, 1, m, &cBinop_KUOh206v_sendMessage);
}

void Heavy_fan5::cBinop_CKn5psfC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_C8cKombn_sendMessage);
}

void Heavy_fan5::cBinop_KUOh206v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_aNEdcUx3, HV_BINOP_MULTIPLY, 1, m, &cBinop_aNEdcUx3_sendMessage);
}

void Heavy_fan5::cBinop_aNEdcUx3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_odBNp9ay, 1, m);
}

void Heavy_fan5::cBinop_Lvtc9vou_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_phcxbz80, HV_BINOP_DIVIDE, 1, m, &cBinop_phcxbz80_sendMessage);
}

void Heavy_fan5::cBinop_hf8QQWTD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_xlzqAk1P_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_KUOh206v, HV_BINOP_ADD, 0, m, &cBinop_KUOh206v_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_Hgx1wZbC_sendMessage);
}

void Heavy_fan5::hTable_qX8CbISf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fan5::cSwitchcase_0QNuDMbG_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_4NWAf18y, 0, m, &cSlice_4NWAf18y_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_yn0LtXv1_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Svb34gWM, 0, m, &cSlice_Svb34gWM_sendMessage);
      break;
    }
    default: {
      cMsg_ChnvYq0s_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fan5::cDelay_mRcBzT6L_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_mRcBzT6L, m);
  cMsg_yn0LtXv1_sendMessage(_c, 0, m);
}

void Heavy_fan5::cVar_EiaycPXl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_i3bDGP5p_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSlice_Svb34gWM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Vo79vvID, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_EiaycPXl, 0, m, &cVar_EiaycPXl_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cSlice_4NWAf18y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Vo79vvID, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_hUbH6J0h, HV_BINOP_SUBTRACT, 0, m, &cBinop_hUbH6J0h_sendMessage);
      break;
    }
    case 1: {
      cMsg_cwe7DdDS_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cBinop_c5prK4kl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_giNuAwkF, HV_BINOP_DIVIDE, 1, m, &cBinop_giNuAwkF_sendMessage);
}

void Heavy_fan5::cBinop_giNuAwkF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_dlccti6N_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_mRcBzT6L, 1, m, &cDelay_mRcBzT6L_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_mRcBzT6L, 0, m, &cDelay_mRcBzT6L_sendMessage);
}

void Heavy_fan5::cMsg_ChnvYq0s_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Vo79vvID, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hUbH6J0h, HV_BINOP_SUBTRACT, 0, m, &cBinop_hUbH6J0h_sendMessage);
}

void Heavy_fan5::cSystem_aT5MmDY3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hUbH6J0h, HV_BINOP_SUBTRACT, 1, m, &cBinop_hUbH6J0h_sendMessage);
}

void Heavy_fan5::cMsg_i3bDGP5p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_aT5MmDY3_sendMessage);
}

void Heavy_fan5::cBinop_hUbH6J0h_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_IZVCE1u8_sendMessage);
}

void Heavy_fan5::cBinop_IZVCE1u8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_giNuAwkF, HV_BINOP_DIVIDE, 0, m, &cBinop_giNuAwkF_sendMessage);
}

void Heavy_fan5::cMsg_dlccti6N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_mRcBzT6L, 0, m, &cDelay_mRcBzT6L_sendMessage);
}

void Heavy_fan5::cMsg_yn0LtXv1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Vo79vvID, 1, m, NULL);
}

void Heavy_fan5::cMsg_864sEK0m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_XqOmfTkF_sendMessage);
}

void Heavy_fan5::cSystem_XqOmfTkF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_c5prK4kl_sendMessage);
}

void Heavy_fan5::cMsg_cwe7DdDS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_Vo79vvID, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hUbH6J0h, HV_BINOP_SUBTRACT, 0, m, &cBinop_hUbH6J0h_sendMessage);
}

void Heavy_fan5::hTable_S1Yo1Ism_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_fan5::cSwitchcase_dFISdY8s_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_e4DN5W2C, 0, m, &cSlice_e4DN5W2C_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_aMtxITIt_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_PYJYliG6, 0, m, &cSlice_PYJYliG6_sendMessage);
      break;
    }
    default: {
      cMsg_fz4MsRXm_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_fan5::cDelay_3WE0LFgw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_3WE0LFgw, m);
  cMsg_aMtxITIt_sendMessage(_c, 0, m);
}

void Heavy_fan5::cVar_4QTxSalu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_uqpIHkfJ_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSlice_PYJYliG6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_IJtdaUda, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_4QTxSalu, 0, m, &cVar_4QTxSalu_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cSlice_e4DN5W2C_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_IJtdaUda, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_UZk1pxZJ, HV_BINOP_SUBTRACT, 0, m, &cBinop_UZk1pxZJ_sendMessage);
      break;
    }
    case 1: {
      cMsg_wWymkIaa_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cBinop_MPefJjxo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_r7oEZDdv, HV_BINOP_DIVIDE, 1, m, &cBinop_r7oEZDdv_sendMessage);
}

void Heavy_fan5::cBinop_r7oEZDdv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_slArbZbC_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3WE0LFgw, 1, m, &cDelay_3WE0LFgw_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_3WE0LFgw, 0, m, &cDelay_3WE0LFgw_sendMessage);
}

void Heavy_fan5::cMsg_fz4MsRXm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_IJtdaUda, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_UZk1pxZJ, HV_BINOP_SUBTRACT, 0, m, &cBinop_UZk1pxZJ_sendMessage);
}

void Heavy_fan5::cSystem_RIL8vVMV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_UZk1pxZJ, HV_BINOP_SUBTRACT, 1, m, &cBinop_UZk1pxZJ_sendMessage);
}

void Heavy_fan5::cMsg_uqpIHkfJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_RIL8vVMV_sendMessage);
}

void Heavy_fan5::cBinop_UZk1pxZJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_NNP48sub_sendMessage);
}

void Heavy_fan5::cBinop_NNP48sub_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_r7oEZDdv, HV_BINOP_DIVIDE, 0, m, &cBinop_r7oEZDdv_sendMessage);
}

void Heavy_fan5::cMsg_slArbZbC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_3WE0LFgw, 0, m, &cDelay_3WE0LFgw_sendMessage);
}

void Heavy_fan5::cMsg_aMtxITIt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_IJtdaUda, 1, m, NULL);
}

void Heavy_fan5::cMsg_d34Bo8tz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Lz4XJ86e_sendMessage);
}

void Heavy_fan5::cSystem_Lz4XJ86e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_MPefJjxo_sendMessage);
}

void Heavy_fan5::cMsg_wWymkIaa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_IJtdaUda, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_UZk1pxZJ, HV_BINOP_SUBTRACT, 0, m, &cBinop_UZk1pxZJ_sendMessage);
}

void Heavy_fan5::cTabhead_KA4ReXLP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Irt3ug2E, HV_BINOP_SUBTRACT, 0, m, &cBinop_Irt3ug2E_sendMessage);
}

void Heavy_fan5::cMsg_MwyaLCiN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_kR75ssGV_sendMessage);
}

void Heavy_fan5::cSystem_kR75ssGV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_qYadZgWc_sendMessage);
}

void Heavy_fan5::cVar_Bt6ZXVH1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ObEGHBci_sendMessage(_c, 0, m);
}

void Heavy_fan5::cDelay_CabsyshW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_CabsyshW, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_wrpYU0pn, 0, m, &cDelay_wrpYU0pn_sendMessage);
  sTabread_onMessage(_c, &Context(_c)->sTabread_xO4pdvLF, 0, m, &sTabread_xO4pdvLF_sendMessage);
}

void Heavy_fan5::cDelay_wrpYU0pn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_wrpYU0pn, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_xO4pdvLF, 0, m, &sTabread_xO4pdvLF_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_wrpYU0pn, 0, m, &cDelay_wrpYU0pn_sendMessage);
}

void Heavy_fan5::sTabread_xO4pdvLF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_onMessage(_c, &Context(_c)->cBinop_2q0K6HEn, HV_BINOP_SUBTRACT, 0, m, &cBinop_2q0K6HEn_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cBinop_UR7bOPUs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_z4Lxgga2, HV_BINOP_MAX, 0, m, &cBinop_z4Lxgga2_sendMessage);
}

void Heavy_fan5::cBinop_qYadZgWc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_UR7bOPUs, HV_BINOP_MULTIPLY, 0, m, &cBinop_UR7bOPUs_sendMessage);
}

void Heavy_fan5::cBinop_Irt3ug2E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jxhyekJF_sendMessage(_c, 0, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_xO4pdvLF, 0, m, &sTabread_xO4pdvLF_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_7UdUiGNS_sendMessage);
}

void Heavy_fan5::cSystem_fr4FDjke_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_2q0K6HEn, HV_BINOP_SUBTRACT, 1, m, &cBinop_2q0K6HEn_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_wrpYU0pn, 2, m, &cDelay_wrpYU0pn_sendMessage);
}

void Heavy_fan5::cMsg_ObEGHBci_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_fr4FDjke_sendMessage);
}

void Heavy_fan5::cMsg_jxhyekJF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_CabsyshW, 0, m, &cDelay_CabsyshW_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_wrpYU0pn, 0, m, &cDelay_wrpYU0pn_sendMessage);
}

void Heavy_fan5::cMsg_KM3bPnwS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cBinop_onMessage(_c, &Context(_c)->cBinop_z4Lxgga2, HV_BINOP_MAX, 1, m, &cBinop_z4Lxgga2_sendMessage);
}

void Heavy_fan5::cBinop_z4Lxgga2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Irt3ug2E, HV_BINOP_SUBTRACT, 1, m, &cBinop_Irt3ug2E_sendMessage);
}

void Heavy_fan5::cCast_7UdUiGNS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_CabsyshW, 0, m, &cDelay_CabsyshW_sendMessage);
}

void Heavy_fan5::cBinop_LSKFu6gS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_CabsyshW, 2, m, &cDelay_CabsyshW_sendMessage);
}

void Heavy_fan5::cBinop_2q0K6HEn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_LSKFu6gS_sendMessage);
}

void Heavy_fan5::cCast_6kwPeeib_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Bt6ZXVH1, 0, m, &cVar_Bt6ZXVH1_sendMessage);
  cMsg_MwyaLCiN_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_KA4ReXLP, 0, m, &cTabhead_KA4ReXLP_sendMessage);
}

void Heavy_fan5::cMsg_qgYRmlVZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_FqiGH3TU_sendMessage);
}

void Heavy_fan5::cSystem_FqiGH3TU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_RybWbieL_sendMessage);
}

void Heavy_fan5::cDelay_QqfRh0nR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_QqfRh0nR, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_PZSVi8YR, 0, m, &cDelay_PZSVi8YR_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_QqfRh0nR, 0, m, &cDelay_QqfRh0nR_sendMessage);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_yGPAHk6D, 1, m, NULL);
}

void Heavy_fan5::cDelay_PZSVi8YR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_PZSVi8YR, m);
  cMsg_GexnjT3Q_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSwitchcase_O9IWSrYQ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x47BE8354: { // "clear"
      cMsg_dNap4IFv_sendMessage(_c, 0, m);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_fan5::cBinop_yUh77zFW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_QBsmNU31_sendMessage(_c, 0, m);
}

void Heavy_fan5::hTable_sl8X6nxd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_kmCl6KzI_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_QqfRh0nR, 2, m, &cDelay_QqfRh0nR_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_pOFrja9I_sendMessage);
}

void Heavy_fan5::cMsg_QBsmNU31_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "resize");
  msg_setElementToFrom(m, 1, n, 0);
  hTable_onMessage(_c, &Context(_c)->hTable_sl8X6nxd, 0, m, &hTable_sl8X6nxd_sendMessage);
}

void Heavy_fan5::cBinop_RybWbieL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 22.0f, 0, m, &cBinop_yUh77zFW_sendMessage);
}

void Heavy_fan5::cMsg_GexnjT3Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "mirror");
  hTable_onMessage(_c, &Context(_c)->hTable_sl8X6nxd, 0, m, &hTable_sl8X6nxd_sendMessage);
}

void Heavy_fan5::cCast_pOFrja9I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_QqfRh0nR, 0, m, &cDelay_QqfRh0nR_sendMessage);
}

void Heavy_fan5::cMsg_kmCl6KzI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cDelay_onMessage(_c, &Context(_c)->cDelay_PZSVi8YR, 2, m, &cDelay_PZSVi8YR_sendMessage);
}

void Heavy_fan5::cMsg_dNap4IFv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_yGPAHk6D, 1, m, NULL);
}

void Heavy_fan5::cMsg_D2nV0uLT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_B00rsnLx_sendMessage);
}

void Heavy_fan5::cSystem_B00rsnLx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_xKXCU0YI_sendMessage);
}

void Heavy_fan5::cDelay_s1gmYAv7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_s1gmYAv7, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_AA16GBek, 0, m, &cDelay_AA16GBek_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_s1gmYAv7, 0, m, &cDelay_s1gmYAv7_sendMessage);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_VaKhSsAL, 1, m, NULL);
}

void Heavy_fan5::cDelay_AA16GBek_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_AA16GBek, m);
  cMsg_m8xY29Cx_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSwitchcase_cu6P8gsQ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x47BE8354: { // "clear"
      cMsg_lGt5osVl_sendMessage(_c, 0, m);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_fan5::cBinop_wPxs2UTl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_gVrbkFcG_sendMessage(_c, 0, m);
}

void Heavy_fan5::hTable_LXuTqM7q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_BTrtl8wc_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_s1gmYAv7, 2, m, &cDelay_s1gmYAv7_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_0lo4ecSr_sendMessage);
}

void Heavy_fan5::cMsg_gVrbkFcG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "resize");
  msg_setElementToFrom(m, 1, n, 0);
  hTable_onMessage(_c, &Context(_c)->hTable_LXuTqM7q, 0, m, &hTable_LXuTqM7q_sendMessage);
}

void Heavy_fan5::cBinop_xKXCU0YI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 200.0f, 0, m, &cBinop_wPxs2UTl_sendMessage);
}

void Heavy_fan5::cMsg_m8xY29Cx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "mirror");
  hTable_onMessage(_c, &Context(_c)->hTable_LXuTqM7q, 0, m, &hTable_LXuTqM7q_sendMessage);
}

void Heavy_fan5::cCast_0lo4ecSr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_s1gmYAv7, 0, m, &cDelay_s1gmYAv7_sendMessage);
}

void Heavy_fan5::cMsg_BTrtl8wc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cDelay_onMessage(_c, &Context(_c)->cDelay_AA16GBek, 2, m, &cDelay_AA16GBek_sendMessage);
}

void Heavy_fan5::cMsg_lGt5osVl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_VaKhSsAL, 1, m, NULL);
}

void Heavy_fan5::cTabhead_9tIVRY0Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_YufXSgr3, HV_BINOP_SUBTRACT, 0, m, &cBinop_YufXSgr3_sendMessage);
}

void Heavy_fan5::cMsg_qPHayVsy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_hmV1XsOA_sendMessage);
}

void Heavy_fan5::cSystem_hmV1XsOA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_opHiYehL_sendMessage);
}

void Heavy_fan5::cVar_tabHvzGG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_A89lfZIw_sendMessage(_c, 0, m);
}

void Heavy_fan5::cDelay_nthuiEXL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_nthuiEXL, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Ony0ykKn, 0, m, &cDelay_Ony0ykKn_sendMessage);
  sTabread_onMessage(_c, &Context(_c)->sTabread_wck5v1Vg, 0, m, &sTabread_wck5v1Vg_sendMessage);
}

void Heavy_fan5::cDelay_Ony0ykKn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_Ony0ykKn, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_wck5v1Vg, 0, m, &sTabread_wck5v1Vg_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Ony0ykKn, 0, m, &cDelay_Ony0ykKn_sendMessage);
}

void Heavy_fan5::sTabread_wck5v1Vg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_onMessage(_c, &Context(_c)->cBinop_iu2hDlXC, HV_BINOP_SUBTRACT, 0, m, &cBinop_iu2hDlXC_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_fan5::cBinop_jf051dJF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_uJtVIwrx, HV_BINOP_MAX, 0, m, &cBinop_uJtVIwrx_sendMessage);
}

void Heavy_fan5::cBinop_opHiYehL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jf051dJF, HV_BINOP_MULTIPLY, 0, m, &cBinop_jf051dJF_sendMessage);
}

void Heavy_fan5::cBinop_YufXSgr3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jktS3jRA_sendMessage(_c, 0, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_wck5v1Vg, 0, m, &sTabread_wck5v1Vg_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_BAdRq8Mw_sendMessage);
}

void Heavy_fan5::cSystem_xfkO4j3x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_iu2hDlXC, HV_BINOP_SUBTRACT, 1, m, &cBinop_iu2hDlXC_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Ony0ykKn, 2, m, &cDelay_Ony0ykKn_sendMessage);
}

void Heavy_fan5::cMsg_A89lfZIw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_xfkO4j3x_sendMessage);
}

void Heavy_fan5::cMsg_jktS3jRA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_nthuiEXL, 0, m, &cDelay_nthuiEXL_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_Ony0ykKn, 0, m, &cDelay_Ony0ykKn_sendMessage);
}

void Heavy_fan5::cMsg_x0OunjmE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cBinop_onMessage(_c, &Context(_c)->cBinop_uJtVIwrx, HV_BINOP_MAX, 1, m, &cBinop_uJtVIwrx_sendMessage);
}

void Heavy_fan5::cBinop_uJtVIwrx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_YufXSgr3, HV_BINOP_SUBTRACT, 1, m, &cBinop_YufXSgr3_sendMessage);
}

void Heavy_fan5::cCast_BAdRq8Mw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_nthuiEXL, 0, m, &cDelay_nthuiEXL_sendMessage);
}

void Heavy_fan5::cBinop_joNbTYnt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_nthuiEXL, 2, m, &cDelay_nthuiEXL_sendMessage);
}

void Heavy_fan5::cBinop_iu2hDlXC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_joNbTYnt_sendMessage);
}

void Heavy_fan5::cCast_3hPT7wSN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_tabHvzGG, 0, m, &cVar_tabHvzGG_sendMessage);
  cMsg_qPHayVsy_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_9tIVRY0Z, 0, m, &cTabhead_9tIVRY0Z_sendMessage);
}

void Heavy_fan5::cVar_t7Fs3oHP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_bKdWNsFq, HV_BINOP_MULTIPLY, 0, m, &cBinop_bKdWNsFq_sendMessage);
}

void Heavy_fan5::cMsg_Bh60oeQ8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_tdX3oFZP_sendMessage);
}

void Heavy_fan5::cSystem_tdX3oFZP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_r0NuWM8O_sendMessage(_c, 0, m);
}

void Heavy_fan5::cBinop_bKdWNsFq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_hiB7z0v8_sendMessage);
}

void Heavy_fan5::cBinop_xDlhtGVQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_bKdWNsFq, HV_BINOP_MULTIPLY, 1, m, &cBinop_bKdWNsFq_sendMessage);
}

void Heavy_fan5::cMsg_r0NuWM8O_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_xDlhtGVQ_sendMessage);
}

void Heavy_fan5::cBinop_hiB7z0v8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_somMHHpX_sendMessage);
}

void Heavy_fan5::cBinop_somMHHpX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_wfv7MMoO_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_d3me7osH, m);
}

void Heavy_fan5::cBinop_wfv7MMoO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_I2erwRBn, m);
}

void Heavy_fan5::cMsg_CK2e9VG5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "main-speed");
  msg_setFloat(m, 1, 22.0f);
}

void Heavy_fan5::cMsg_k8fFeCh0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "main-speed");
  msg_setFloat(m, 1, 0.0f);
}

void Heavy_fan5::cMsg_J6CCFvyj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 20.0f);
  cSend_7TWrE3yc_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_7TWrE3yc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_bX3xsffC_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_QW41zO75_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.2f);
  cSend_hgl34Owo_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_hgl34Owo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_9zwj0MKN_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_EIRdPPlY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.05f);
  cSend_0QvtJiQw_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_0QvtJiQw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_lXLrfsgd_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_OQvGabr5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.1f);
  cSend_sCvoJHfb_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_sCvoJHfb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_Iw7k4Je5_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_QHaGG32w_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.3f);
  cSend_rZcFQyg6_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_rZcFQyg6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_KThKoCZd_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_R9WDYAkT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 4.0f);
  cSend_v2Xqvvw6_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_v2Xqvvw6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_PV4bzj8A_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_78pDshN1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.2f);
  cSend_pcZQVIb9_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_pcZQVIb9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_yuSmtrGr_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_kW0CMjy6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.5f);
  cSend_15nsigot_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_15nsigot_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_K8vgUG5Q_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_zavxO3qA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 20.0f);
  cSend_FXzGi5BY_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_FXzGi5BY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_bX3xsffC_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_h4RF5kY6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.2f);
  cSend_NB9m4dA0_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_NB9m4dA0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_9zwj0MKN_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_HMCBP9RY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.05f);
  cSend_gBVAONbf_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_gBVAONbf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_lXLrfsgd_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_Q3Qe88ha_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.1f);
  cSend_OKKFKdqO_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_OKKFKdqO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_Iw7k4Je5_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_GVjr6djF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.3f);
  cSend_pQKnXogO_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_pQKnXogO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_KThKoCZd_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_Kg0G44If_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 4.0f);
  cSend_LiMPtsNx_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_LiMPtsNx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_PV4bzj8A_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_m5x9yO8f_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.2f);
  cSend_y5bT28BD_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_y5bT28BD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_yuSmtrGr_sendMessage(_c, 0, m);
}

void Heavy_fan5::cMsg_R5Nr0JsZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.5f);
  cSend_itXpYaX5_sendMessage(_c, 0, m);
}

void Heavy_fan5::cSend_itXpYaX5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_K8vgUG5Q_sendMessage(_c, 0, m);
}

void Heavy_fan5::cReceive_GbHYyzUQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_BdtZ5ui2, 0, m, &cVar_BdtZ5ui2_sendMessage);
  cMsg_dtNTwlQR_sendMessage(_c, 0, m);
  cMsg_tZ3FtU1J_sendMessage(_c, 0, m);
  cMsg_d7whLdaT_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_0L2WoE4W, 0, m, &cVar_0L2WoE4W_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_EiaycPXl, 0, m, &cVar_EiaycPXl_sendMessage);
  cMsg_864sEK0m_sendMessage(_c, 0, m);
  cMsg_yn0LtXv1_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_4QTxSalu, 0, m, &cVar_4QTxSalu_sendMessage);
  cMsg_d34Bo8tz_sendMessage(_c, 0, m);
  cMsg_aMtxITIt_sendMessage(_c, 0, m);
  cSwitchcase_dOQmVsEl_onMessage(_c, NULL, 0, m, NULL);
  cVar_onMessage(_c, &Context(_c)->cVar_rUDxfvhO, 0, m, &cVar_rUDxfvhO_sendMessage);
  cMsg_b3R9fHt1_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_rkCkqlnf, 0, m, &cVar_rkCkqlnf_sendMessage);
  cSwitchcase_14puOi6D_onMessage(_c, NULL, 0, m, NULL);
  cVar_onMessage(_c, &Context(_c)->cVar_QjWkAbu5, 0, m, &cVar_QjWkAbu5_sendMessage);
  cMsg_uCWHRy1Y_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_6vXtjVAS, 0, m, &cVar_6vXtjVAS_sendMessage);
  cMsg_qgYRmlVZ_sendMessage(_c, 0, m);
  cMsg_D2nV0uLT_sendMessage(_c, 0, m);
  cMsg_Bh60oeQ8_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_t7Fs3oHP, 0, m, &cVar_t7Fs3oHP_sendMessage);
  cMsg_CK2e9VG5_sendMessage(_c, 0, m);
  cMsg_J6CCFvyj_sendMessage(_c, 0, m);
  cMsg_QW41zO75_sendMessage(_c, 0, m);
  cMsg_EIRdPPlY_sendMessage(_c, 0, m);
  cMsg_OQvGabr5_sendMessage(_c, 0, m);
  cMsg_QHaGG32w_sendMessage(_c, 0, m);
  cMsg_R9WDYAkT_sendMessage(_c, 0, m);
  cMsg_78pDshN1_sendMessage(_c, 0, m);
  cMsg_kW0CMjy6_sendMessage(_c, 0, m);
  cMsg_KM3bPnwS_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_Bt6ZXVH1, 0, m, &cVar_Bt6ZXVH1_sendMessage);
  cMsg_MwyaLCiN_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_KA4ReXLP, 0, m, &cTabhead_KA4ReXLP_sendMessage);
  cMsg_x0OunjmE_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_tabHvzGG, 0, m, &cVar_tabHvzGG_sendMessage);
  cMsg_qPHayVsy_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_9tIVRY0Z, 0, m, &cTabhead_9tIVRY0Z_sendMessage);
}

void Heavy_fan5::cReceive_9EZlkex4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_0QNuDMbG_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_dFISdY8s_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fan5::cReceive_lXLrfsgd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_jZVxDLLO, m);
}

void Heavy_fan5::cReceive_Iw7k4Je5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_NYvmHLRP, m);
}

void Heavy_fan5::cReceive_KThKoCZd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_UTsplJWF, m);
}

void Heavy_fan5::cReceive_PV4bzj8A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_7nRpGgjH, m);
}

void Heavy_fan5::cReceive_9zwj0MKN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_tZpUyHg9, m);
}

void Heavy_fan5::cReceive_wpKlYFLL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_VpHfd1O2, m);
}

void Heavy_fan5::cReceive_bX3xsffC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_6hkgItsS, m);
}

void Heavy_fan5::cReceive_K8vgUG5Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_i25aRqqe, m);
}

void Heavy_fan5::cReceive_yuSmtrGr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_VPHZMRCn, m);
}

void Heavy_fan5::cReceive_TFDYJPsV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_k8fFeCh0_sendMessage(_c, 0, m);
  cMsg_zavxO3qA_sendMessage(_c, 0, m);
  cMsg_h4RF5kY6_sendMessage(_c, 0, m);
  cMsg_HMCBP9RY_sendMessage(_c, 0, m);
  cMsg_Q3Qe88ha_sendMessage(_c, 0, m);
  cMsg_GVjr6djF_sendMessage(_c, 0, m);
  cMsg_Kg0G44If_sendMessage(_c, 0, m);
  cMsg_m5x9yO8f_sendMessage(_c, 0, m);
  cMsg_R5Nr0JsZ_sendMessage(_c, 0, m);
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

int Heavy_fan5::process(float **inputBuffers, float **outputBuffers, int n) {
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
    __hv_varread_f(&sVarf_trz2L29X, VOf(Bf0));
    __hv_varread_f(&sVarf_yhDp3E8n, VOf(Bf1));
    __hv_add_f(VIf(Bf0), VIf(Bf1), VOf(Bf2));
    __hv_varread_f(&sVarf_VpHfd1O2, VOf(Bf3));
    __hv_varread_f(&sVarf_d3me7osH, VOf(Bf4));
    __hv_mul_f(VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_varread_f(&sVarf_I2erwRBn, VOf(Bf3));
    __hv_rpole_f(&sRPole_DXCRdDUm, VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_phasor_f(&sPhasor_bAUgZhoj, VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_6hkgItsS, VOf(Bf4));
    __hv_mul_f(VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_floor_f(VIf(Bf4), VOf(Bf5));
    __hv_sub_f(VIf(Bf4), VIf(Bf5), VOf(Bf5));
    __hv_varread_i(&sVari_rwKe0k3n, VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_cast_if(VIi(Bi1), VOf(Bf4));
    __hv_var_k_f(VOf(Bf6), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf4), VIf(Bf6), VOf(Bf6));
    __hv_varwrite_i(&sVari_rwKe0k3n, VIi(Bi1));
    __hv_biquad_k_f(&sBiquad_k_odBNp9ay, VIf(Bf6), VOf(Bf6));
    __hv_varread_f(&sVarf_jZVxDLLO, VOf(Bf4));
    __hv_varread_f(&sVarf_NYvmHLRP, VOf(Bf7));
    __hv_fma_f(VIf(Bf6), VIf(Bf4), VIf(Bf7), VOf(Bf7));
    __hv_tabwrite_stoppable_f(&sTabwrite_zXqGyPkz, VIf(Bf7));
    __hv_mul_f(VIf(Bf5), VIf(Bf5), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf7), VIf(Bf4), VOf(Bf4));
    __hv_tabwrite_stoppable_f(&sTabwrite_Vo79vvID, VIf(Bf4));
    __hv_var_k_f(VOf(Bf7), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_var_k_f(VOf(Bf6), 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    __hv_mul_f(VIf(Bf5), VIf(Bf6), VOf(Bf6));
    __hv_floor_f(VIf(Bf6), VOf(Bf5));
    __hv_sub_f(VIf(Bf6), VIf(Bf5), VOf(Bf5));
    __hv_floor_f(VIf(Bf5), VOf(Bf6));
    __hv_sub_f(VIf(Bf5), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf5), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf6), VIf(Bf5), VOf(Bf5));
    __hv_abs_f(VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf6), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf5), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf5), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf6), VIf(Bf5), VOf(Bf5));
    __hv_mul_f(VIf(Bf5), VIf(Bf5), VOf(Bf6));
    __hv_mul_f(VIf(Bf5), VIf(Bf6), VOf(Bf8));
    __hv_mul_f(VIf(Bf8), VIf(Bf6), VOf(Bf9));
    __hv_mul_f(VIf(Bf9), VIf(Bf6), VOf(Bf10));
    __hv_mul_f(VIf(Bf10), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf11), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf12), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf13), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf8), VIf(Bf13), VOf(Bf13));
    __hv_sub_f(VIf(Bf5), VIf(Bf13), VOf(Bf13));
    __hv_fma_f(VIf(Bf9), VIf(Bf12), VIf(Bf13), VOf(Bf13));
    __hv_var_k_f(VOf(Bf12), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf10), VIf(Bf12), VOf(Bf12));
    __hv_sub_f(VIf(Bf13), VIf(Bf12), VOf(Bf12));
    __hv_fma_f(VIf(Bf6), VIf(Bf11), VIf(Bf12), VOf(Bf12));
    __hv_var_k_f(VOf(Bf11), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_fma_f(VIf(Bf12), VIf(Bf12), VIf(Bf11), VOf(Bf11));
    __hv_div_f(VIf(Bf7), VIf(Bf11), VOf(Bf11));
    __hv_var_k_f(VOf(Bf7), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf11), VIf(Bf7), VOf(Bf7));
    __hv_tabwrite_stoppable_f(&sTabwrite_IJtdaUda, VIf(Bf7));
    __hv_varread_f(&sVarf_UTsplJWF, VOf(Bf11));
    __hv_mul_f(VIf(Bf7), VIf(Bf11), VOf(Bf11));
    __hv_add_f(VIf(Bf4), VIf(Bf11), VOf(Bf11));
    __hv_varread_f(&sVarf_tZpUyHg9, VOf(Bf4));
    __hv_var_k_f(VOf(Bf7), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_floor_f(VIf(Bf3), VOf(Bf12));
    __hv_sub_f(VIf(Bf3), VIf(Bf12), VOf(Bf12));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf12), VIf(Bf3), VOf(Bf3));
    __hv_abs_f(VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf12), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf3), VIf(Bf12), VOf(Bf12));
    __hv_var_k_f(VOf(Bf3), 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f, 6.28319f);
    __hv_mul_f(VIf(Bf12), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf3), VOf(Bf12));
    __hv_mul_f(VIf(Bf3), VIf(Bf12), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf12), VOf(Bf13));
    __hv_mul_f(VIf(Bf13), VIf(Bf12), VOf(Bf10));
    __hv_mul_f(VIf(Bf10), VIf(Bf12), VOf(Bf12));
    __hv_var_k_f(VOf(Bf9), 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f, 2.75573e-06f);
    __hv_var_k_f(VOf(Bf5), 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f, 0.00833333f);
    __hv_var_k_f(VOf(Bf8), 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f, 0.166667f);
    __hv_mul_f(VIf(Bf6), VIf(Bf8), VOf(Bf8));
    __hv_sub_f(VIf(Bf3), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf13), VIf(Bf5), VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf5), 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f, 0.000198413f);
    __hv_mul_f(VIf(Bf10), VIf(Bf5), VOf(Bf5));
    __hv_sub_f(VIf(Bf8), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf12), VIf(Bf9), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_7nRpGgjH, VOf(Bf9));
    __hv_mul_f(VIf(Bf5), VIf(Bf9), VOf(Bf9));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_fma_f(VIf(Bf9), VIf(Bf9), VIf(Bf5), VOf(Bf5));
    __hv_div_f(VIf(Bf7), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf7), 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f);
    __hv_mul_f(VIf(Bf5), VIf(Bf7), VOf(Bf7));
    __hv_varread_i(&sVari_jmppcbIl, VOi(Bi1));
    __hv_var_k_i(VOi(Bi0), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi1), VIi(Bi0), VOi(Bi0));
    __hv_cast_if(VIi(Bi0), VOf(Bf9));
    __hv_var_k_f(VOf(Bf12), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf9), VIf(Bf12), VOf(Bf12));
    __hv_varwrite_i(&sVari_jmppcbIl, VIi(Bi0));
    __hv_biquad_k_f(&sBiquad_k_Fy314rNR, VIf(Bf12), VOf(Bf12));
    __hv_varread_f(&sVarf_VPHZMRCn, VOf(Bf9));
    __hv_mul_f(VIf(Bf12), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf7), VIf(Bf9), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_i25aRqqe, VOf(Bf9));
    __hv_mul_f(VIf(Bf5), VIf(Bf9), VOf(Bf9));
    __hv_fma_f(VIf(Bf11), VIf(Bf4), VIf(Bf9), VOf(Bf9));
    __hv_add_f(VIf(Bf2), VIf(Bf9), VOf(Bf9));
    __hv_tabwrite_f(&sTabwrite_yGPAHk6D, VIf(Bf9));
    __hv_add_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_tabwrite_f(&sTabwrite_VaKhSsAL, VIf(Bf1));
    __hv_tabread_f(&sTabread_xO4pdvLF, VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_varwrite_f(&sVarf_trz2L29X, VIf(Bf0));
    __hv_tabread_f(&sTabread_wck5v1Vg, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.499f, 0.499f, 0.499f, 0.499f, 0.499f, 0.499f, 0.499f, 0.499f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varwrite_f(&sVarf_yhDp3E8n, VIf(Bf1));
    __hv_add_f(VIf(Bf1), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf1), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_fan5::processInline(float *inputBuffers, float *outputBuffers, int n4) {
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

int Heavy_fan5::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
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
