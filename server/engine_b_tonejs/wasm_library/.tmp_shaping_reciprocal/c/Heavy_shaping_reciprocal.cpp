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

#include "Heavy_shaping_reciprocal.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_shaping_reciprocal *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_shaping_reciprocal_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_reciprocal));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_reciprocal(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_shaping_reciprocal_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_shaping_reciprocal));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_shaping_reciprocal(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_shaping_reciprocal_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_shaping_reciprocal();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_shaping_reciprocal::Heavy_shaping_reciprocal(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sTabwrite_init(&sTabwrite_CSYcispo, &hTable_tef62hQG);
  numBytes += sTabwrite_init(&sTabwrite_uxT82hlB, &hTable_HYSVlqIQ);
  numBytes += sPhasor_k_init(&sPhasor_AwCnZv0T, 640.0f, sampleRate);
  numBytes += hTable_init(&hTable_tef62hQG, 100);
  numBytes += cDelay_init(this, &cDelay_YJiP10kQ, 0.0f);
  numBytes += cVar_init_s(&cVar_EAeYZX0S, "A");
  numBytes += cSlice_init(&cSlice_oj283eDn, 1, 1);
  numBytes += cSlice_init(&cSlice_lAlS2KLh, 1, 1);
  numBytes += cBinop_init(&cBinop_wg4zwBe4, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_hAXXLvFK, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_vzOABrQs, 0.0f);
  numBytes += cVar_init_f(&cVar_ZBvb3AmE, 200.0f);
  numBytes += cBinop_init(&cBinop_SwQt4PId, 0.0f); // __mul
  numBytes += hTable_init(&hTable_HYSVlqIQ, 100);
  numBytes += cDelay_init(this, &cDelay_zzWKaqGz, 0.0f);
  numBytes += cVar_init_s(&cVar_Ogo9KK2H, "B");
  numBytes += cSlice_init(&cSlice_VFds4idg, 1, 1);
  numBytes += cSlice_init(&cSlice_0PNnRG2g, 1, 1);
  numBytes += cBinop_init(&cBinop_0jgO8JGd, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_PyJs15UW, 0.0f); // __sub
  numBytes += sVarf_init(&sVarf_0ZJAzFUg, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_W0pawAJA, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_shaping_reciprocal::~Heavy_shaping_reciprocal() {
  hTable_free(&hTable_tef62hQG);
  hTable_free(&hTable_HYSVlqIQ);
}

HvTable *Heavy_shaping_reciprocal::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x25F31569: return &hTable_tef62hQG; // A
    case 0xD961DF96: return &hTable_HYSVlqIQ; // B
    default: return nullptr;
  }
}

void Heavy_shaping_reciprocal::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_meOve4GM_sendMessage);
      break;
    }
    case 0x86B7B9F4: { // b
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_VN2Ukm1R_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_shaping_reciprocal::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_shaping_reciprocal::hTable_tef62hQG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_reciprocal::cSwitchcase_rV9kT2FS_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_lAlS2KLh, 0, m, &cSlice_lAlS2KLh_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_v3mAGA6n_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_oj283eDn, 0, m, &cSlice_oj283eDn_sendMessage);
      break;
    }
    default: {
      cMsg_6GWYtjpk_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_reciprocal::cDelay_YJiP10kQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_YJiP10kQ, m);
  cMsg_v3mAGA6n_sendMessage(_c, 0, m);
}

void Heavy_shaping_reciprocal::cVar_EAeYZX0S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_mOAclbc2_sendMessage(_c, 0, m);
}

void Heavy_shaping_reciprocal::cSlice_oj283eDn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_CSYcispo, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_EAeYZX0S, 0, m, &cVar_EAeYZX0S_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_reciprocal::cSlice_lAlS2KLh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_CSYcispo, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_hAXXLvFK, HV_BINOP_SUBTRACT, 0, m, &cBinop_hAXXLvFK_sendMessage);
      break;
    }
    case 1: {
      cMsg_nJ7KUw71_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_reciprocal::cBinop_HDKDC7eO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wg4zwBe4, HV_BINOP_DIVIDE, 1, m, &cBinop_wg4zwBe4_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_wg4zwBe4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_1PJrR324_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_YJiP10kQ, 1, m, &cDelay_YJiP10kQ_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_YJiP10kQ, 0, m, &cDelay_YJiP10kQ_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_6GWYtjpk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_CSYcispo, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hAXXLvFK, HV_BINOP_SUBTRACT, 0, m, &cBinop_hAXXLvFK_sendMessage);
}

void Heavy_shaping_reciprocal::cSystem_wIXIowYD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hAXXLvFK, HV_BINOP_SUBTRACT, 1, m, &cBinop_hAXXLvFK_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_mOAclbc2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_wIXIowYD_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_hAXXLvFK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_mb9vcF4H_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_mb9vcF4H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wg4zwBe4, HV_BINOP_DIVIDE, 0, m, &cBinop_wg4zwBe4_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_1PJrR324_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_YJiP10kQ, 0, m, &cDelay_YJiP10kQ_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_v3mAGA6n_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_CSYcispo, 1, m, NULL);
}

void Heavy_shaping_reciprocal::cMsg_3li97a46_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_6NPzS5uh_sendMessage);
}

void Heavy_shaping_reciprocal::cSystem_6NPzS5uh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_HDKDC7eO_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_nJ7KUw71_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_CSYcispo, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hAXXLvFK, HV_BINOP_SUBTRACT, 0, m, &cBinop_hAXXLvFK_sendMessage);
}

void Heavy_shaping_reciprocal::cCast_BfWIvXFk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_xu0quhpW_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_reciprocal::cSwitchcase_xu0quhpW_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x0: { // "0.0"
      cMsg_Jq4MwydP_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_Jq4MwydP_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ov4cQ4w2_sendMessage);
      break;
    }
  }
}

void Heavy_shaping_reciprocal::cDelay_vzOABrQs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_vzOABrQs, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_vzOABrQs, 0, m, &cDelay_vzOABrQs_sendMessage);
  cSwitchcase_rV9kT2FS_onMessage(_c, NULL, 0, m, NULL);
  cSend_xJyMxtZC_sendMessage(_c, 0, m);
}

void Heavy_shaping_reciprocal::cCast_ov4cQ4w2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Jq4MwydP_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_vzOABrQs, 0, m, &cDelay_vzOABrQs_sendMessage);
  cSwitchcase_rV9kT2FS_onMessage(_c, NULL, 0, m, NULL);
  cSend_xJyMxtZC_sendMessage(_c, 0, m);
}

void Heavy_shaping_reciprocal::cMsg_HURYrTOV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_km5vNvAI_sendMessage);
}

void Heavy_shaping_reciprocal::cSystem_km5vNvAI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_6zpnJBQM_sendMessage);
}

void Heavy_shaping_reciprocal::cVar_ZBvb3AmE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_SwQt4PId, HV_BINOP_MULTIPLY, 0, m, &cBinop_SwQt4PId_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_Jq4MwydP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_vzOABrQs, 0, m, &cDelay_vzOABrQs_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_4FZhjprY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_vzOABrQs, 2, m, &cDelay_vzOABrQs_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_6zpnJBQM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_SwQt4PId, HV_BINOP_MULTIPLY, 1, m, &cBinop_SwQt4PId_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_SwQt4PId_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_4FZhjprY_sendMessage);
}

void Heavy_shaping_reciprocal::cSend_xJyMxtZC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_VN2Ukm1R_sendMessage(_c, 0, m);
}

void Heavy_shaping_reciprocal::hTable_HYSVlqIQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_shaping_reciprocal::cSwitchcase_AOXBX0MH_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x6FF57CB4: { // "start"
      cSlice_onMessage(_c, &Context(_c)->cSlice_0PNnRG2g, 0, m, &cSlice_0PNnRG2g_sendMessage);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_GsNVByzl_sendMessage(_c, 0, m);
      break;
    }
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_VFds4idg, 0, m, &cSlice_VFds4idg_sendMessage);
      break;
    }
    default: {
      cMsg_FVogeEPL_sendMessage(_c, 0, m);
      break;
    }
  }
}

void Heavy_shaping_reciprocal::cDelay_zzWKaqGz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_zzWKaqGz, m);
  cMsg_GsNVByzl_sendMessage(_c, 0, m);
}

void Heavy_shaping_reciprocal::cVar_Ogo9KK2H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_lCmiMkzV_sendMessage(_c, 0, m);
}

void Heavy_shaping_reciprocal::cSlice_VFds4idg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_uxT82hlB, 2, m, NULL);
      cVar_onMessage(_c, &Context(_c)->cVar_Ogo9KK2H, 0, m, &cVar_Ogo9KK2H_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_shaping_reciprocal::cSlice_0PNnRG2g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_uxT82hlB, 1, m, NULL);
      cBinop_onMessage(_c, &Context(_c)->cBinop_PyJs15UW, HV_BINOP_SUBTRACT, 0, m, &cBinop_PyJs15UW_sendMessage);
      break;
    }
    case 1: {
      cMsg_6EoqQUMW_sendMessage(_c, 0, m);
      break;
    }
    default: return;
  }
}

void Heavy_shaping_reciprocal::cBinop_BdlfUwn6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0jgO8JGd, HV_BINOP_DIVIDE, 1, m, &cBinop_0jgO8JGd_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_0jgO8JGd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_JzgWekvT_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_zzWKaqGz, 1, m, &cDelay_zzWKaqGz_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_zzWKaqGz, 0, m, &cDelay_zzWKaqGz_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_FVogeEPL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_uxT82hlB, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_PyJs15UW, HV_BINOP_SUBTRACT, 0, m, &cBinop_PyJs15UW_sendMessage);
}

void Heavy_shaping_reciprocal::cSystem_Oh451iNn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_PyJs15UW, HV_BINOP_SUBTRACT, 1, m, &cBinop_PyJs15UW_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_lCmiMkzV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Oh451iNn_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_PyJs15UW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_gX8mCwon_sendMessage);
}

void Heavy_shaping_reciprocal::cBinop_gX8mCwon_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0jgO8JGd, HV_BINOP_DIVIDE, 0, m, &cBinop_0jgO8JGd_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_JzgWekvT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_zzWKaqGz, 0, m, &cDelay_zzWKaqGz_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_GsNVByzl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_uxT82hlB, 1, m, NULL);
}

void Heavy_shaping_reciprocal::cMsg_7owNRPB3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_j7AtWYDZ_sendMessage);
}

void Heavy_shaping_reciprocal::cSystem_j7AtWYDZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_BdlfUwn6_sendMessage);
}

void Heavy_shaping_reciprocal::cMsg_6EoqQUMW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_uxT82hlB, 1, m, NULL);
  cBinop_onMessage(_c, &Context(_c)->cBinop_PyJs15UW, HV_BINOP_SUBTRACT, 0, m, &cBinop_PyJs15UW_sendMessage);
}

void Heavy_shaping_reciprocal::cReceive_meOve4GM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_EAeYZX0S, 0, m, &cVar_EAeYZX0S_sendMessage);
  cMsg_3li97a46_sendMessage(_c, 0, m);
  cMsg_v3mAGA6n_sendMessage(_c, 0, m);
  cMsg_HURYrTOV_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_ZBvb3AmE, 0, m, &cVar_ZBvb3AmE_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_Ogo9KK2H, 0, m, &cVar_Ogo9KK2H_sendMessage);
  cMsg_7owNRPB3_sendMessage(_c, 0, m);
  cMsg_GsNVByzl_sendMessage(_c, 0, m);
  cSwitchcase_xu0quhpW_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_shaping_reciprocal::cReceive_VN2Ukm1R_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_AOXBX0MH_onMessage(_c, NULL, 0, m, NULL);
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

int Heavy_shaping_reciprocal::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2;

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
    __hv_varread_f(&sVarf_0ZJAzFUg, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_CSYcispo, VIf(Bf0));
    __hv_varread_f(&sVarf_W0pawAJA, VOf(Bf0));
    __hv_tabwrite_stoppable_f(&sTabwrite_uxT82hlB, VIf(Bf0));
    __hv_phasor_k_f(&sPhasor_AwCnZv0T, VOf(Bf0));
    __hv_varwrite_f(&sVarf_0ZJAzFUg, VIf(Bf0));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_var_k_f(VOf(Bf2), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_add_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_div_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_varwrite_f(&sVarf_W0pawAJA, VIf(Bf2));

    // save output vars to output buffer
    // no output channels
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_shaping_reciprocal::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float **const bOut = NULL;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_shaping_reciprocal::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 0 channel(s)
  float *const bOut = NULL;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
