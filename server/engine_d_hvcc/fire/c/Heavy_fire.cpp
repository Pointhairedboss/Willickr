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

#include "Heavy_fire.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_fire *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_fire_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_fire));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_fire(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_fire_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_fire));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_fire(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_fire_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_fire();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_fire::Heavy_fire(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sRPole_init(&sRPole_Zvm60JXX);
  numBytes += sDel1_init(&sDel1_d0qSJz2T);
  numBytes += sRPole_init(&sRPole_teg7J78G);
  numBytes += sRPole_init(&sRPole_WXiBm1BV);
  numBytes += sEnv_init(&sEnv_HcRaBufw, 1024, 512);
  numBytes += sBiquad_k_init(&sBiquad_k_Kqj4RjMj, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sLine_init(&sLine_ujk2TaCN);
  numBytes += sBiquad_k_init(&sBiquad_k_zjTNP8bO, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sRPole_init(&sRPole_b3LENND6);
  numBytes += sDel1_init(&sDel1_Wtvk7aa5);
  numBytes += sRPole_init(&sRPole_igciWS8Y);
  numBytes += sDel1_init(&sDel1_mGwraXOm);
  numBytes += sRPole_init(&sRPole_4SXzyKj7);
  numBytes += sDel1_init(&sDel1_ip21GDmS);
  numBytes += sRPole_init(&sRPole_1Nq4fDcG);
  numBytes += sDel1_init(&sDel1_SH95fq5n);
  numBytes += sRPole_init(&sRPole_Z3f6KqpI);
  numBytes += sRPole_init(&sRPole_dl1j1F86);
  numBytes += sEnv_init(&sEnv_pbcOLK2k, 1024, 512);
  numBytes += sBiquad_k_init(&sBiquad_k_iiXEOgZC, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sLine_init(&sLine_9Jrwqhtg);
  numBytes += sBiquad_k_init(&sBiquad_k_fkvUbsvR, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sRPole_init(&sRPole_i30l2Q1z);
  numBytes += sDel1_init(&sDel1_gyuRVh9c);
  numBytes += sRPole_init(&sRPole_82ggxPOT);
  numBytes += sDel1_init(&sDel1_bQ9Mzt19);
  numBytes += sBiquad_k_init(&sBiquad_k_ojWLoQVU, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sRPole_init(&sRPole_58i9pni3);
  numBytes += sDel1_init(&sDel1_siSjl8RL);
  numBytes += sRPole_init(&sRPole_BAAyUlkr);
  numBytes += sRPole_init(&sRPole_4cRr6HOc);
  numBytes += sEnv_init(&sEnv_eKpodMzB, 1024, 512);
  numBytes += sBiquad_k_init(&sBiquad_k_OMztWFw8, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sLine_init(&sLine_1VO2mmzz);
  numBytes += sBiquad_k_init(&sBiquad_k_IrUyVvQ5, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sRPole_init(&sRPole_c15qA2wZ);
  numBytes += sDel1_init(&sDel1_TGq1yCe7);
  numBytes += sRPole_init(&sRPole_9lxN9iWN);
  numBytes += sDel1_init(&sDel1_dShGt7Vn);
  numBytes += sBiquad_k_init(&sBiquad_k_L14V5tqI, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sRPole_init(&sRPole_vBCjLGUm);
  numBytes += sDel1_init(&sDel1_QyQPtba2);
  numBytes += sRPole_init(&sRPole_jOLaKpmC);
  numBytes += sRPole_init(&sRPole_na8JVF1C);
  numBytes += sEnv_init(&sEnv_5hb5TGQh, 1024, 512);
  numBytes += sBiquad_k_init(&sBiquad_k_gSadOs7Q, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sLine_init(&sLine_4xUtNnbF);
  numBytes += sBiquad_k_init(&sBiquad_k_JAO8SSKE, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sRPole_init(&sRPole_Xf7ktnoR);
  numBytes += sDel1_init(&sDel1_9xjY62G0);
  numBytes += sRPole_init(&sRPole_GTOgJonj);
  numBytes += sDel1_init(&sDel1_Wcmt6orU);
  numBytes += sBiquad_k_init(&sBiquad_k_X9hDAJPC, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sVarf_init(&sVarf_Yiuu6ozd, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_ktV61nl5, 1000.0f);
  numBytes += cBinop_init(&cBinop_Sk70Os6i, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_IsaB45V5, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_uzJLoGmk, 1200.0f);
  numBytes += cVar_init_f(&cVar_NYOeA9Xu, 0.6f);
  numBytes += cBinop_init(&cBinop_2n9Nr9ND, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_wysaDxTi, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_0fRvwedA, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_qUitYe4d, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_WBg9Bm2v, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_6gQd2jS4, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_ujKljZq6, 2600.0f);
  numBytes += cVar_init_f(&cVar_CpYthQ1A, 0.4f);
  numBytes += cBinop_init(&cBinop_AWrzCNRf, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_SFkIRGN9, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_KH1CxqFK, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_FekRTZxI, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_LesUlzUy, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_lGv7ntYQ, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_duUaHnF2, 600.0f);
  numBytes += cVar_init_f(&cVar_ogzujkvo, 0.2f);
  numBytes += cBinop_init(&cBinop_mD5EenWC, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_XCSgJyqA, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_JML8sHPy, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_akdynrup, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_Lbq5QavF, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_0mxqrHqz, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_RDJ6WgRc, 1.0f);
  numBytes += cBinop_init(&cBinop_2dd91691, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_B6litlPZ, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_TBlgpnmT, 0.0f, 0.0f, false);
  numBytes += cIf_init(&cIf_4psTJNrD, false);
  numBytes += cIf_init(&cIf_VGAlVGyK, false);
  numBytes += cRandom_init(&cRandom_BoRUpZCD, -1700118871);
  numBytes += cSlice_init(&cSlice_21BSarpc, 1, 1);
  numBytes += cVar_init_f(&cVar_Ds8MHzqi, 4000.0f);
  numBytes += cVar_init_f(&cVar_5hwv5XFn, 1.0f);
  numBytes += cBinop_init(&cBinop_aeFjYY0w, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_xI4vSBqY, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_Mb2um8tE, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_tgJro4nS, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_hxzlK71F, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_NRbVv8z9, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_PcB1Qch2, 1.0f);
  numBytes += cBinop_init(&cBinop_RqTsVaib, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_VY3VvNQd, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_5rn0X7FY, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_UCDbV3Ks, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_tXak5h1S, 1000.0f);
  numBytes += cBinop_init(&cBinop_yspEIK2f, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_puRdoxX1, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_ZFCRxAqE, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_BtMSkQX1, 25.0f);
  numBytes += cBinop_init(&cBinop_BWHHrn4b, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_nu3rDj1z, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_mgvuRGEU, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_j4kFBEUB, 25.0f);
  numBytes += cBinop_init(&cBinop_mkHkINK5, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_2U6cRxgG, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_uDnroDkH, 30.0f);
  numBytes += cVar_init_f(&cVar_ALfL3XkX, 5.0f);
  numBytes += cBinop_init(&cBinop_T8pNSkyg, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_dnV3lCdT, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_WxYuVJTW, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_FdoBALEA, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_JFvy313Y, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_49zXwDei, 0.0f); // __mul
  numBytes += cRandom_init(&cRandom_fe6yB2Rk, 1669531385);
  numBytes += cSlice_init(&cSlice_eP9WUev1, 1, 1);
  numBytes += sVari_init(&sVari_YzFhuSTd, 0, 0, false);
  numBytes += cVar_init_f(&cVar_eLbPwBo7, 1.0f);
  numBytes += cBinop_init(&cBinop_KWGgKsWM, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_H3kcSvxt, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_XEPszT7W, 0.0f, 0.0f, false);
  numBytes += cIf_init(&cIf_N4tG4ms5, false);
  numBytes += cIf_init(&cIf_jvhUP8Ik, false);
  numBytes += cRandom_init(&cRandom_W3mXrSg3, -956596597);
  numBytes += cSlice_init(&cSlice_h6zOYGps, 1, 1);
  numBytes += cVar_init_f(&cVar_kiIdpTTW, 4000.0f);
  numBytes += cVar_init_f(&cVar_W0RQm2D4, 1.0f);
  numBytes += cBinop_init(&cBinop_Y1bW4Jou, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_KAqZqxxO, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_ZxmxLTnx, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_OuFshthK, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_rOb4WOFl, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_0DWp3BHI, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_5Wh1CsDl, 1.0f);
  numBytes += cBinop_init(&cBinop_KC4usSCU, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_0dYrl7FO, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_GD043OAS, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_AMRxcpjc, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_U6GnOpjA, 1000.0f);
  numBytes += cBinop_init(&cBinop_9fXP8yNn, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_1rjhk7qK, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Khyo4hbJ, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_D6hJFHaU, 25.0f);
  numBytes += cBinop_init(&cBinop_KKI6M1sS, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_TqcYUCVk, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Kt5jfBka, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_rAuH50bg, 25.0f);
  numBytes += cBinop_init(&cBinop_LJ97TWq3, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_kltPtssX, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_I7CgNizg, 30.0f);
  numBytes += cVar_init_f(&cVar_PHeZJtX8, 5.0f);
  numBytes += cBinop_init(&cBinop_GIPW78FU, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_OUaQhrxN, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_GgpIyTdC, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_oJX2IMo4, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_Hn1ILxe3, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_ko5cAvCr, 0.0f); // __mul
  numBytes += cRandom_init(&cRandom_TcdOhLAi, 1231181294);
  numBytes += cSlice_init(&cSlice_632nHA3e, 1, 1);
  numBytes += sVari_init(&sVari_nuYriN0y, 0, 0, false);
  numBytes += cVar_init_f(&cVar_4BZNbotf, 1.0f);
  numBytes += cBinop_init(&cBinop_vFW7VYo4, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_nmdUWfy1, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_h8aysor1, 0.0f, 0.0f, false);
  numBytes += cIf_init(&cIf_klQ1zrb5, false);
  numBytes += cIf_init(&cIf_JGRLTcxZ, false);
  numBytes += cRandom_init(&cRandom_4CHljkBM, -1409203602);
  numBytes += cSlice_init(&cSlice_ippYlQHs, 1, 1);
  numBytes += cVar_init_f(&cVar_xrsNY2oL, 4000.0f);
  numBytes += cVar_init_f(&cVar_jzL2fq5k, 1.0f);
  numBytes += cBinop_init(&cBinop_U1eFR49c, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_vCIoBZhZ, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_cO4xGMml, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_Uxm3YhWH, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_j7e5Pwe1, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_nz3G5SzZ, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_mH3YG7FV, 1.0f);
  numBytes += cBinop_init(&cBinop_dPWfTCFL, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_IMApKRie, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_YcXGKuJk, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_PVIoNJOJ, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_zLVXEUcc, 1000.0f);
  numBytes += cBinop_init(&cBinop_ikNrgpie, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_90tUBjOm, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_sOVZYGy6, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_MDkU5uw8, 25.0f);
  numBytes += cBinop_init(&cBinop_XVRjkNYN, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_MarQsZfY, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_149JAOIb, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_644RmxHP, 25.0f);
  numBytes += cBinop_init(&cBinop_sh2HjxYR, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_cHjnRVyS, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_0GiTFN2C, 30.0f);
  numBytes += cVar_init_f(&cVar_UEBpqTCP, 5.0f);
  numBytes += cBinop_init(&cBinop_7RlBxJNN, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_tHgUBqo4, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_BTfX7uhJ, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_7JYjNMW8, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_v6CjUCp7, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_qAaewJSe, 0.0f); // __mul
  numBytes += cRandom_init(&cRandom_zxVmNHcK, 713286695);
  numBytes += cSlice_init(&cSlice_8iY3tdnO, 1, 1);
  numBytes += sVari_init(&sVari_70GcWyXx, 0, 0, false);
  numBytes += cVar_init_f(&cVar_y62pPsWp, 1.0f);
  numBytes += cBinop_init(&cBinop_mWgRwiYs, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_iM1VJNgd, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_7jJNCH7z, 0.0f, 0.0f, false);
  numBytes += cIf_init(&cIf_yltFyPnL, false);
  numBytes += cIf_init(&cIf_03Egk6J5, false);
  numBytes += cRandom_init(&cRandom_y1RlGIkm, 1885378683);
  numBytes += cSlice_init(&cSlice_fEfGU8mn, 1, 1);
  numBytes += cVar_init_f(&cVar_gLtQgsPZ, 4000.0f);
  numBytes += cVar_init_f(&cVar_ZFEV08tM, 1.0f);
  numBytes += cBinop_init(&cBinop_wJWGzawN, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_gZ1VmC7b, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_snElBdDo, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_dEVMQ0AF, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_qa389xcx, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_8V6BxHYi, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_gkUnCDgN, 1.0f);
  numBytes += cBinop_init(&cBinop_GKFtNljN, 0.0f); // __mul
  numBytes += sVarf_init(&sVarf_f27ahSRi, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_pRnoQSnW, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Mu1DaNN9, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_PJpd1ScB, 1000.0f);
  numBytes += cBinop_init(&cBinop_v3mvBKFj, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_OpTRDeab, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_Ht7WEy23, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_YKk785Yz, 25.0f);
  numBytes += cBinop_init(&cBinop_hJW4b4CP, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_amBDLITl, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_ztmXlqss, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_ru05PzHe, 25.0f);
  numBytes += cBinop_init(&cBinop_anzgb48f, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_CMFL5gw2, 0.0f, 0.0f, false);
  numBytes += cVar_init_f(&cVar_WbRfCgvw, 30.0f);
  numBytes += cVar_init_f(&cVar_FEEXGm1N, 5.0f);
  numBytes += cBinop_init(&cBinop_7zPOCAwo, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_7B90G5dK, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_6PN9qwml, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_BpWr8g9i, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_E31UEUhA, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_l4TIgls4, 0.0f); // __mul
  numBytes += cRandom_init(&cRandom_U5wakTjg, -2103565432);
  numBytes += cSlice_init(&cSlice_mdkx9ITY, 1, 1);
  numBytes += sVari_init(&sVari_ikEfWqJc, 0, 0, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_fire::~Heavy_fire() {
  sEnv_free(&sEnv_HcRaBufw);
  sEnv_free(&sEnv_pbcOLK2k);
  sEnv_free(&sEnv_eKpodMzB);
  sEnv_free(&sEnv_5hb5TGQh);
}

HvTable *Heavy_fire::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_fire::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_uNgTd9wt_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_fire::getParameterInfo(int index, HvParameterInfo *info) {
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


void Heavy_fire::cBinop_UCBetF4j_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_lcW9qr6W_sendMessage);
}

void Heavy_fire::cBinop_lcW9qr6W_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_ODutFEXg_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_cRiwOsxi_sendMessage);
}

void Heavy_fire::cVar_ktV61nl5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_pT748lfQ_sendMessage);
}

void Heavy_fire::cMsg_aG75Gsly_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_gTh6yeaR_sendMessage);
}

void Heavy_fire::cSystem_gTh6yeaR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Sk70Os6i, HV_BINOP_DIVIDE, 1, m, &cBinop_Sk70Os6i_sendMessage);
}

void Heavy_fire::cBinop_ODutFEXg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_UcfCk9OP_sendMessage);
}

void Heavy_fire::cBinop_UcfCk9OP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_IsaB45V5, m);
}

void Heavy_fire::cMsg_SHSKV1c9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_XCdw8eyi_sendMessage);
}

void Heavy_fire::cBinop_XCdw8eyi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_UCBetF4j_sendMessage);
}

void Heavy_fire::cBinop_cRiwOsxi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Yiuu6ozd, m);
}

void Heavy_fire::cBinop_pT748lfQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_6CF6mkUC_sendMessage);
}

void Heavy_fire::cBinop_6CF6mkUC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Sk70Os6i, HV_BINOP_DIVIDE, 0, m, &cBinop_Sk70Os6i_sendMessage);
}

void Heavy_fire::cBinop_Sk70Os6i_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_SHSKV1c9_sendMessage(_c, 0, m);
}

void Heavy_fire::cMsg_f5B4hNhT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_L3deCEex_sendMessage);
}

void Heavy_fire::cSystem_L3deCEex_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_2n9Nr9ND, HV_BINOP_DIVIDE, 1, m, &cBinop_2n9Nr9ND_sendMessage);
}

void Heavy_fire::cVar_uzJLoGmk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_yXl9xXkZ_sendMessage);
}

void Heavy_fire::cVar_NYOeA9Xu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_5Y1mPhL6_sendMessage);
}

void Heavy_fire::cUnop_dB0NQHnC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_yqVeoSJl_sendMessage);
}

void Heavy_fire::cBinop_2n9Nr9ND_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_qUitYe4d, HV_BINOP_MULTIPLY, 1, m, &cBinop_qUitYe4d_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_dB0NQHnC_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_wysaDxTi, HV_BINOP_DIVIDE, 0, m, &cBinop_wysaDxTi_sendMessage);
}

void Heavy_fire::cBinop_yXl9xXkZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_2n9Nr9ND, HV_BINOP_DIVIDE, 0, m, &cBinop_2n9Nr9ND_sendMessage);
}

void Heavy_fire::cBinop_wysaDxTi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_XvUa5AZR_sendMessage);
}

void Heavy_fire::cBinop_4MU2QGUv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_ylxiSddm_sendMessage);
}

void Heavy_fire::cBinop_ylxiSddm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_0DlijdYA_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_0fRvwedA, HV_BINOP_MULTIPLY, 0, m, &cBinop_0fRvwedA_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_qUitYe4d, HV_BINOP_MULTIPLY, 0, m, &cBinop_qUitYe4d_sendMessage);
}

void Heavy_fire::cBinop_yqVeoSJl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0fRvwedA, HV_BINOP_MULTIPLY, 1, m, &cBinop_0fRvwedA_sendMessage);
}

void Heavy_fire::cBinop_0fRvwedA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_mIOVktfX_sendMessage);
}

void Heavy_fire::cCast_pv390Gjw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_uzJLoGmk, 0, m, &cVar_uzJLoGmk_sendMessage);
}

void Heavy_fire::cBinop_RoGIueo2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_belFUTNv_sendMessage);
}

void Heavy_fire::cBinop_belFUTNv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_ojWLoQVU, 5, m);
}

void Heavy_fire::cBinop_mIOVktfX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_ojWLoQVU, 4, m);
}

void Heavy_fire::cBinop_KnQLuizr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6gQd2jS4, HV_BINOP_MULTIPLY, 0, m, &cBinop_6gQd2jS4_sendMessage);
}

void Heavy_fire::cBinop_qUitYe4d_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_WBg9Bm2v, HV_BINOP_ADD, 1, m, &cBinop_WBg9Bm2v_sendMessage);
}

void Heavy_fire::cBinop_0DlijdYA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_RoGIueo2_sendMessage);
}

void Heavy_fire::cBinop_WBg9Bm2v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6gQd2jS4, HV_BINOP_MULTIPLY, 1, m, &cBinop_6gQd2jS4_sendMessage);
}

void Heavy_fire::cBinop_6gQd2jS4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_ojWLoQVU, 1, m);
}

void Heavy_fire::cBinop_5Y1mPhL6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wysaDxTi, HV_BINOP_DIVIDE, 1, m, &cBinop_wysaDxTi_sendMessage);
}

void Heavy_fire::cBinop_XvUa5AZR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_4MU2QGUv_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_WBg9Bm2v, HV_BINOP_ADD, 0, m, &cBinop_WBg9Bm2v_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_KnQLuizr_sendMessage);
}

void Heavy_fire::cMsg_ylm5mWQk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_4DA93A7m_sendMessage);
}

void Heavy_fire::cSystem_4DA93A7m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_AWrzCNRf, HV_BINOP_DIVIDE, 1, m, &cBinop_AWrzCNRf_sendMessage);
}

void Heavy_fire::cVar_ujKljZq6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_a1RxS0g8_sendMessage);
}

void Heavy_fire::cVar_CpYthQ1A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_DyNQo7il_sendMessage);
}

void Heavy_fire::cUnop_UaGSc11G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_dns8G7gS_sendMessage);
}

void Heavy_fire::cBinop_AWrzCNRf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_FekRTZxI, HV_BINOP_MULTIPLY, 1, m, &cBinop_FekRTZxI_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_UaGSc11G_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_SFkIRGN9, HV_BINOP_DIVIDE, 0, m, &cBinop_SFkIRGN9_sendMessage);
}

void Heavy_fire::cBinop_a1RxS0g8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_AWrzCNRf, HV_BINOP_DIVIDE, 0, m, &cBinop_AWrzCNRf_sendMessage);
}

void Heavy_fire::cBinop_SFkIRGN9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_6pHK6zKZ_sendMessage);
}

void Heavy_fire::cBinop_J6gQQOeG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_EzaHFsl7_sendMessage);
}

void Heavy_fire::cBinop_EzaHFsl7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_VWD1JWjT_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_KH1CxqFK, HV_BINOP_MULTIPLY, 0, m, &cBinop_KH1CxqFK_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_FekRTZxI, HV_BINOP_MULTIPLY, 0, m, &cBinop_FekRTZxI_sendMessage);
}

void Heavy_fire::cBinop_dns8G7gS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KH1CxqFK, HV_BINOP_MULTIPLY, 1, m, &cBinop_KH1CxqFK_sendMessage);
}

void Heavy_fire::cBinop_KH1CxqFK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_iTpRomP6_sendMessage);
}

void Heavy_fire::cCast_P1ePbVo3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_ujKljZq6, 0, m, &cVar_ujKljZq6_sendMessage);
}

void Heavy_fire::cBinop_BOoPIVTW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_ZxMupEvd_sendMessage);
}

void Heavy_fire::cBinop_ZxMupEvd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_L14V5tqI, 5, m);
}

void Heavy_fire::cBinop_iTpRomP6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_L14V5tqI, 4, m);
}

void Heavy_fire::cBinop_l0hZUgjS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lGv7ntYQ, HV_BINOP_MULTIPLY, 0, m, &cBinop_lGv7ntYQ_sendMessage);
}

void Heavy_fire::cBinop_FekRTZxI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LesUlzUy, HV_BINOP_ADD, 1, m, &cBinop_LesUlzUy_sendMessage);
}

void Heavy_fire::cBinop_VWD1JWjT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_BOoPIVTW_sendMessage);
}

void Heavy_fire::cBinop_LesUlzUy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lGv7ntYQ, HV_BINOP_MULTIPLY, 1, m, &cBinop_lGv7ntYQ_sendMessage);
}

void Heavy_fire::cBinop_lGv7ntYQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_L14V5tqI, 1, m);
}

void Heavy_fire::cBinop_DyNQo7il_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_SFkIRGN9, HV_BINOP_DIVIDE, 1, m, &cBinop_SFkIRGN9_sendMessage);
}

void Heavy_fire::cBinop_6pHK6zKZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_J6gQQOeG_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_LesUlzUy, HV_BINOP_ADD, 0, m, &cBinop_LesUlzUy_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_l0hZUgjS_sendMessage);
}

void Heavy_fire::cMsg_9usCBUnn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_UuMrS08Q_sendMessage);
}

void Heavy_fire::cSystem_UuMrS08Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mD5EenWC, HV_BINOP_DIVIDE, 1, m, &cBinop_mD5EenWC_sendMessage);
}

void Heavy_fire::cVar_duUaHnF2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_8T7CXVfP_sendMessage);
}

void Heavy_fire::cVar_ogzujkvo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_8TvPxFAM_sendMessage);
}

void Heavy_fire::cUnop_UOQbK1Dp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_l3ta7fPq_sendMessage);
}

void Heavy_fire::cBinop_mD5EenWC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_akdynrup, HV_BINOP_MULTIPLY, 1, m, &cBinop_akdynrup_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_UOQbK1Dp_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_XCSgJyqA, HV_BINOP_DIVIDE, 0, m, &cBinop_XCSgJyqA_sendMessage);
}

void Heavy_fire::cBinop_8T7CXVfP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mD5EenWC, HV_BINOP_DIVIDE, 0, m, &cBinop_mD5EenWC_sendMessage);
}

void Heavy_fire::cBinop_XCSgJyqA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_R8Dh5wrr_sendMessage);
}

void Heavy_fire::cBinop_0SVtHz29_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_EBVcI1MC_sendMessage);
}

void Heavy_fire::cBinop_EBVcI1MC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_MWxwbmtD_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_JML8sHPy, HV_BINOP_MULTIPLY, 0, m, &cBinop_JML8sHPy_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_akdynrup, HV_BINOP_MULTIPLY, 0, m, &cBinop_akdynrup_sendMessage);
}

void Heavy_fire::cBinop_l3ta7fPq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JML8sHPy, HV_BINOP_MULTIPLY, 1, m, &cBinop_JML8sHPy_sendMessage);
}

void Heavy_fire::cBinop_JML8sHPy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_8B0GvIjf_sendMessage);
}

void Heavy_fire::cCast_ouQNTyS6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_duUaHnF2, 0, m, &cVar_duUaHnF2_sendMessage);
}

void Heavy_fire::cBinop_RAMXop3X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_bJBDt7wQ_sendMessage);
}

void Heavy_fire::cBinop_bJBDt7wQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_X9hDAJPC, 5, m);
}

void Heavy_fire::cBinop_8B0GvIjf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_X9hDAJPC, 4, m);
}

void Heavy_fire::cBinop_ND7VJS17_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0mxqrHqz, HV_BINOP_MULTIPLY, 0, m, &cBinop_0mxqrHqz_sendMessage);
}

void Heavy_fire::cBinop_akdynrup_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Lbq5QavF, HV_BINOP_ADD, 1, m, &cBinop_Lbq5QavF_sendMessage);
}

void Heavy_fire::cBinop_MWxwbmtD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_RAMXop3X_sendMessage);
}

void Heavy_fire::cBinop_Lbq5QavF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0mxqrHqz, HV_BINOP_MULTIPLY, 1, m, &cBinop_0mxqrHqz_sendMessage);
}

void Heavy_fire::cBinop_0mxqrHqz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_X9hDAJPC, 1, m);
}

void Heavy_fire::cBinop_8TvPxFAM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_XCSgJyqA, HV_BINOP_DIVIDE, 1, m, &cBinop_XCSgJyqA_sendMessage);
}

void Heavy_fire::cBinop_R8Dh5wrr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_0SVtHz29_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Lbq5QavF, HV_BINOP_ADD, 0, m, &cBinop_Lbq5QavF_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_ND7VJS17_sendMessage);
}

void Heavy_fire::sEnv_pbcOLK2k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 50.0f, 0, m, &cBinop_r9LH3lqI_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_4psTJNrD, 0, m, &cIf_4psTJNrD_sendMessage);
}

void Heavy_fire::cVar_RDJ6WgRc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_2dd91691, HV_BINOP_MULTIPLY, 0, m, &cBinop_2dd91691_sendMessage);
}

void Heavy_fire::cMsg_0E8Iy6iy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_17wClMu0_sendMessage);
}

void Heavy_fire::cSystem_17wClMu0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_cS6QwRQ6_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_2dd91691_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_gZEbEpKJ_sendMessage);
}

void Heavy_fire::cBinop_UMM07Z7u_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_2dd91691, HV_BINOP_MULTIPLY, 1, m, &cBinop_2dd91691_sendMessage);
}

void Heavy_fire::cMsg_cS6QwRQ6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_UMM07Z7u_sendMessage);
}

void Heavy_fire::cBinop_gZEbEpKJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_O6y5SHFC_sendMessage);
}

void Heavy_fire::cBinop_O6y5SHFC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_QjB20gTh_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_TBlgpnmT, m);
}

void Heavy_fire::cBinop_QjB20gTh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_B6litlPZ, m);
}

void Heavy_fire::cIf_4psTJNrD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 51.0f, 0, m, &cBinop_PhD1MYZa_sendMessage);
      cIf_onMessage(_c, &Context(_c)->cIf_VGAlVGyK, 0, m, &cIf_VGAlVGyK_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_r9LH3lqI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_4psTJNrD, 1, m, &cIf_4psTJNrD_sendMessage);
}

void Heavy_fire::cIf_VGAlVGyK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cMsg_eOKEEY15_sendMessage(_c, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_PhD1MYZa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_VGAlVGyK, 1, m, &cIf_VGAlVGyK_sendMessage);
}

void Heavy_fire::cSwitchcase_WnzgZhu5_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_21BSarpc, 0, m, &cSlice_21BSarpc_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_BoRUpZCD, 0, m, &cRandom_BoRUpZCD_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_QzkhKgzr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_UI3BLknC_sendMessage);
}

void Heavy_fire::cUnop_UI3BLknC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Njj0RSKi_sendMessage(_c, 0, m);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 500.0f, 0, m, &cBinop_4iTVMlDv_sendMessage);
}

void Heavy_fire::cRandom_BoRUpZCD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 30.0f, 0, m, &cBinop_QzkhKgzr_sendMessage);
}

void Heavy_fire::cSlice_21BSarpc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_BoRUpZCD, 1, m, &cRandom_BoRUpZCD_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_awRGtLg0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_in9DHGXQ_sendMessage);
}

void Heavy_fire::cSystem_in9DHGXQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_aeFjYY0w, HV_BINOP_DIVIDE, 1, m, &cBinop_aeFjYY0w_sendMessage);
}

void Heavy_fire::cVar_Ds8MHzqi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_xl2I3c0x_sendMessage);
}

void Heavy_fire::cVar_5hwv5XFn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_eqEALwpc_sendMessage);
}

void Heavy_fire::cUnop_tjcjqhAC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_Yeigk3yF_sendMessage);
}

void Heavy_fire::cBinop_aeFjYY0w_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_tgJro4nS, HV_BINOP_MULTIPLY, 1, m, &cBinop_tgJro4nS_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_tjcjqhAC_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_xI4vSBqY, HV_BINOP_DIVIDE, 0, m, &cBinop_xI4vSBqY_sendMessage);
}

void Heavy_fire::cBinop_xl2I3c0x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_aeFjYY0w, HV_BINOP_DIVIDE, 0, m, &cBinop_aeFjYY0w_sendMessage);
}

void Heavy_fire::cBinop_xI4vSBqY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_XTHy7vDM_sendMessage);
}

void Heavy_fire::cBinop_0kuo6plj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_V7fTNnFW_sendMessage);
}

void Heavy_fire::cBinop_V7fTNnFW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_Yx45rYoP_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Mb2um8tE, HV_BINOP_MULTIPLY, 0, m, &cBinop_Mb2um8tE_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_tgJro4nS, HV_BINOP_MULTIPLY, 0, m, &cBinop_tgJro4nS_sendMessage);
}

void Heavy_fire::cBinop_Yeigk3yF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Mb2um8tE, HV_BINOP_MULTIPLY, 1, m, &cBinop_Mb2um8tE_sendMessage);
}

void Heavy_fire::cBinop_Mb2um8tE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_4hjRhKPL_sendMessage);
}

void Heavy_fire::cCast_aq5rKzqI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Ds8MHzqi, 0, m, &cVar_Ds8MHzqi_sendMessage);
}

void Heavy_fire::cBinop_cMbrIIZE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_MCUqLZ5E_sendMessage);
}

void Heavy_fire::cBinop_MCUqLZ5E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_iiXEOgZC, 5, m);
}

void Heavy_fire::cBinop_4hjRhKPL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_iiXEOgZC, 4, m);
}

void Heavy_fire::cBinop_vukHbCqg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_NRbVv8z9, HV_BINOP_MULTIPLY, 0, m, &cBinop_NRbVv8z9_sendMessage);
}

void Heavy_fire::cBinop_tgJro4nS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hxzlK71F, HV_BINOP_ADD, 1, m, &cBinop_hxzlK71F_sendMessage);
}

void Heavy_fire::cBinop_Yx45rYoP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_cMbrIIZE_sendMessage);
}

void Heavy_fire::cBinop_hxzlK71F_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_NRbVv8z9, HV_BINOP_MULTIPLY, 1, m, &cBinop_NRbVv8z9_sendMessage);
}

void Heavy_fire::cBinop_NRbVv8z9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_iiXEOgZC, 1, m);
}

void Heavy_fire::cBinop_eqEALwpc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_xI4vSBqY, HV_BINOP_DIVIDE, 1, m, &cBinop_xI4vSBqY_sendMessage);
}

void Heavy_fire::cBinop_XTHy7vDM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_0kuo6plj_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_hxzlK71F, HV_BINOP_ADD, 0, m, &cBinop_hxzlK71F_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_vukHbCqg_sendMessage);
}

void Heavy_fire::cMsg_eOKEEY15_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setBang(m, 0);
  cSwitchcase_WnzgZhu5_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fire::cMsg_Njj0RSKi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_9Jrwqhtg, 0, m, NULL);
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setElementToFrom(m, 1, n, 0);
  sLine_onMessage(_c, &Context(_c)->sLine_9Jrwqhtg, 0, m, NULL);
}

void Heavy_fire::cBinop_Qwg53zJU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Ds8MHzqi, 0, m, &cVar_Ds8MHzqi_sendMessage);
}

void Heavy_fire::cBinop_4iTVMlDv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1500.0f, 0, m, &cBinop_Qwg53zJU_sendMessage);
}

void Heavy_fire::cVar_PcB1Qch2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_RqTsVaib, HV_BINOP_MULTIPLY, 0, m, &cBinop_RqTsVaib_sendMessage);
}

void Heavy_fire::cMsg_j8KPxKA2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_IfPgFlc0_sendMessage);
}

void Heavy_fire::cSystem_IfPgFlc0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_fWs8ZbCe_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_RqTsVaib_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_aA5mcD14_sendMessage);
}

void Heavy_fire::cBinop_CJVJShNu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_RqTsVaib, HV_BINOP_MULTIPLY, 1, m, &cBinop_RqTsVaib_sendMessage);
}

void Heavy_fire::cMsg_fWs8ZbCe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_CJVJShNu_sendMessage);
}

void Heavy_fire::cBinop_aA5mcD14_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_ZZC0gU6m_sendMessage);
}

void Heavy_fire::cBinop_ZZC0gU6m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_58WpoMvU_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_5rn0X7FY, m);
}

void Heavy_fire::cBinop_58WpoMvU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_VY3VvNQd, m);
}

void Heavy_fire::cBinop_cbi4NCX1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_tETT7VXg_sendMessage);
}

void Heavy_fire::cBinop_tETT7VXg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_uJyxSqtj_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_qZAHr5Rz_sendMessage);
}

void Heavy_fire::cVar_tXak5h1S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_Qi6DRjdT_sendMessage);
}

void Heavy_fire::cMsg_yMzO2rtq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_bWsXSloy_sendMessage);
}

void Heavy_fire::cSystem_bWsXSloy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_yspEIK2f, HV_BINOP_DIVIDE, 1, m, &cBinop_yspEIK2f_sendMessage);
}

void Heavy_fire::cBinop_uJyxSqtj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_YGrIY0pH_sendMessage);
}

void Heavy_fire::cBinop_YGrIY0pH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_puRdoxX1, m);
}

void Heavy_fire::cMsg_sjcbzl1V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_Hml4Xenf_sendMessage);
}

void Heavy_fire::cBinop_Hml4Xenf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_cbi4NCX1_sendMessage);
}

void Heavy_fire::cBinop_qZAHr5Rz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_UCDbV3Ks, m);
}

void Heavy_fire::cBinop_Qi6DRjdT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_mrb6xpu9_sendMessage);
}

void Heavy_fire::cBinop_mrb6xpu9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_yspEIK2f, HV_BINOP_DIVIDE, 0, m, &cBinop_yspEIK2f_sendMessage);
}

void Heavy_fire::cBinop_yspEIK2f_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_sjcbzl1V_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_4t2ojd7Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_9VvBsWc9_sendMessage);
}

void Heavy_fire::cBinop_9VvBsWc9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_eXnpZkbd_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_VQ3aJl7e_sendMessage);
}

void Heavy_fire::cVar_BtMSkQX1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_0dDivJzX_sendMessage);
}

void Heavy_fire::cMsg_CBhBeLS9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_N1JpwDYo_sendMessage);
}

void Heavy_fire::cSystem_N1JpwDYo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BWHHrn4b, HV_BINOP_DIVIDE, 1, m, &cBinop_BWHHrn4b_sendMessage);
}

void Heavy_fire::cBinop_eXnpZkbd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_HoJ0EoH2_sendMessage);
}

void Heavy_fire::cBinop_HoJ0EoH2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_nu3rDj1z, m);
}

void Heavy_fire::cMsg_ilbl8FGn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_X4toKTdt_sendMessage);
}

void Heavy_fire::cBinop_X4toKTdt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_4t2ojd7Y_sendMessage);
}

void Heavy_fire::cBinop_VQ3aJl7e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ZFCRxAqE, m);
}

void Heavy_fire::cBinop_0dDivJzX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_drBEmhBL_sendMessage);
}

void Heavy_fire::cBinop_drBEmhBL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BWHHrn4b, HV_BINOP_DIVIDE, 0, m, &cBinop_BWHHrn4b_sendMessage);
}

void Heavy_fire::cBinop_BWHHrn4b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ilbl8FGn_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_afWVd30e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_Xy4dMeDg_sendMessage);
}

void Heavy_fire::cBinop_Xy4dMeDg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_47WqwODE_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_NTpYsQuE_sendMessage);
}

void Heavy_fire::cVar_j4kFBEUB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_ygwMuRZn_sendMessage);
}

void Heavy_fire::cMsg_wE1t3B6s_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_pS55zuHx_sendMessage);
}

void Heavy_fire::cSystem_pS55zuHx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mkHkINK5, HV_BINOP_DIVIDE, 1, m, &cBinop_mkHkINK5_sendMessage);
}

void Heavy_fire::cBinop_47WqwODE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_7u8rmVzI_sendMessage);
}

void Heavy_fire::cBinop_7u8rmVzI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_2U6cRxgG, m);
}

void Heavy_fire::cMsg_wpx0tB8Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_0sLvuids_sendMessage);
}

void Heavy_fire::cBinop_0sLvuids_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_afWVd30e_sendMessage);
}

void Heavy_fire::cBinop_NTpYsQuE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_mgvuRGEU, m);
}

void Heavy_fire::cBinop_ygwMuRZn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_qMcX5Pvd_sendMessage);
}

void Heavy_fire::cBinop_qMcX5Pvd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mkHkINK5, HV_BINOP_DIVIDE, 0, m, &cBinop_mkHkINK5_sendMessage);
}

void Heavy_fire::cBinop_mkHkINK5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_wpx0tB8Z_sendMessage(_c, 0, m);
}

void Heavy_fire::cMsg_eFs6TDmP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_7KGlQhv8_sendMessage);
}

void Heavy_fire::cSystem_7KGlQhv8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_T8pNSkyg, HV_BINOP_DIVIDE, 1, m, &cBinop_T8pNSkyg_sendMessage);
}

void Heavy_fire::cVar_uDnroDkH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_ROivRnJy_sendMessage);
}

void Heavy_fire::cVar_ALfL3XkX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_LcyqNdXC_sendMessage);
}

void Heavy_fire::cUnop_10G0lgy2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_C3xRg0t7_sendMessage);
}

void Heavy_fire::cBinop_T8pNSkyg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_FdoBALEA, HV_BINOP_MULTIPLY, 1, m, &cBinop_FdoBALEA_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_10G0lgy2_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_dnV3lCdT, HV_BINOP_DIVIDE, 0, m, &cBinop_dnV3lCdT_sendMessage);
}

void Heavy_fire::cBinop_ROivRnJy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_T8pNSkyg, HV_BINOP_DIVIDE, 0, m, &cBinop_T8pNSkyg_sendMessage);
}

void Heavy_fire::cBinop_dnV3lCdT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_74OXVqhM_sendMessage);
}

void Heavy_fire::cBinop_ddRASXAR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_EVq9rSuh_sendMessage);
}

void Heavy_fire::cBinop_EVq9rSuh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_XJ63EnCQ_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_WxYuVJTW, HV_BINOP_MULTIPLY, 0, m, &cBinop_WxYuVJTW_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_FdoBALEA, HV_BINOP_MULTIPLY, 0, m, &cBinop_FdoBALEA_sendMessage);
}

void Heavy_fire::cBinop_C3xRg0t7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_WxYuVJTW, HV_BINOP_MULTIPLY, 1, m, &cBinop_WxYuVJTW_sendMessage);
}

void Heavy_fire::cBinop_WxYuVJTW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_SoE4JGjt_sendMessage);
}

void Heavy_fire::cCast_NH2P94GZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_uDnroDkH, 0, m, &cVar_uDnroDkH_sendMessage);
}

void Heavy_fire::cBinop_3mFF1Uxz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_a3pTXD91_sendMessage);
}

void Heavy_fire::cBinop_a3pTXD91_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_fkvUbsvR, 5, m);
}

void Heavy_fire::cBinop_SoE4JGjt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_fkvUbsvR, 4, m);
}

void Heavy_fire::cBinop_017VKIO8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_49zXwDei, HV_BINOP_MULTIPLY, 0, m, &cBinop_49zXwDei_sendMessage);
}

void Heavy_fire::cBinop_FdoBALEA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_JFvy313Y, HV_BINOP_ADD, 1, m, &cBinop_JFvy313Y_sendMessage);
}

void Heavy_fire::cBinop_XJ63EnCQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_3mFF1Uxz_sendMessage);
}

void Heavy_fire::cBinop_JFvy313Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_49zXwDei, HV_BINOP_MULTIPLY, 1, m, &cBinop_49zXwDei_sendMessage);
}

void Heavy_fire::cBinop_49zXwDei_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_fkvUbsvR, 1, m);
}

void Heavy_fire::cBinop_LcyqNdXC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dnV3lCdT, HV_BINOP_DIVIDE, 1, m, &cBinop_dnV3lCdT_sendMessage);
}

void Heavy_fire::cBinop_74OXVqhM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_ddRASXAR_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_JFvy313Y, HV_BINOP_ADD, 0, m, &cBinop_JFvy313Y_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_017VKIO8_sendMessage);
}

void Heavy_fire::cSwitchcase_hOBdudiM_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_eP9WUev1, 0, m, &cSlice_eP9WUev1_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_fe6yB2Rk, 0, m, &cRandom_fe6yB2Rk_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_yJ11qdjZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_7flBlQ6U_sendMessage);
}

void Heavy_fire::cUnop_7flBlQ6U_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_YqkTN53m_sendMessage(_c, 0, m);
}

void Heavy_fire::cRandom_fe6yB2Rk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_yJ11qdjZ_sendMessage);
}

void Heavy_fire::cSlice_eP9WUev1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_fe6yB2Rk, 1, m, &cRandom_fe6yB2Rk_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_YqkTN53m_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_YzFhuSTd, m);
}

void Heavy_fire::sEnv_eKpodMzB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 50.0f, 0, m, &cBinop_EmzCpBox_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_N4tG4ms5, 0, m, &cIf_N4tG4ms5_sendMessage);
}

void Heavy_fire::cVar_eLbPwBo7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KWGgKsWM, HV_BINOP_MULTIPLY, 0, m, &cBinop_KWGgKsWM_sendMessage);
}

void Heavy_fire::cMsg_9Xw6TJxK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_1cNnloMj_sendMessage);
}

void Heavy_fire::cSystem_1cNnloMj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_5ibQZ2go_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_KWGgKsWM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_mZKFAEtV_sendMessage);
}

void Heavy_fire::cBinop_TiweMN17_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KWGgKsWM, HV_BINOP_MULTIPLY, 1, m, &cBinop_KWGgKsWM_sendMessage);
}

void Heavy_fire::cMsg_5ibQZ2go_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_TiweMN17_sendMessage);
}

void Heavy_fire::cBinop_mZKFAEtV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_rvaiiM7z_sendMessage);
}

void Heavy_fire::cBinop_rvaiiM7z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_jfRySu02_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_XEPszT7W, m);
}

void Heavy_fire::cBinop_jfRySu02_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_H3kcSvxt, m);
}

void Heavy_fire::cIf_N4tG4ms5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 51.0f, 0, m, &cBinop_VTlEkQmL_sendMessage);
      cIf_onMessage(_c, &Context(_c)->cIf_jvhUP8Ik, 0, m, &cIf_jvhUP8Ik_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_EmzCpBox_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_N4tG4ms5, 1, m, &cIf_N4tG4ms5_sendMessage);
}

void Heavy_fire::cIf_jvhUP8Ik_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cMsg_ocfPt5Jb_sendMessage(_c, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_VTlEkQmL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_jvhUP8Ik, 1, m, &cIf_jvhUP8Ik_sendMessage);
}

void Heavy_fire::cSwitchcase_wLKOJ86C_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_h6zOYGps, 0, m, &cSlice_h6zOYGps_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_W3mXrSg3, 0, m, &cRandom_W3mXrSg3_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_vIMlWSgK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_2u3rVeo9_sendMessage);
}

void Heavy_fire::cUnop_2u3rVeo9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_XiGJYexE_sendMessage(_c, 0, m);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 500.0f, 0, m, &cBinop_djYQYHFE_sendMessage);
}

void Heavy_fire::cRandom_W3mXrSg3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 30.0f, 0, m, &cBinop_vIMlWSgK_sendMessage);
}

void Heavy_fire::cSlice_h6zOYGps_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_W3mXrSg3, 1, m, &cRandom_W3mXrSg3_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_HsP9fwKH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_VgzqxYlj_sendMessage);
}

void Heavy_fire::cSystem_VgzqxYlj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Y1bW4Jou, HV_BINOP_DIVIDE, 1, m, &cBinop_Y1bW4Jou_sendMessage);
}

void Heavy_fire::cVar_kiIdpTTW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_zD7Hz7eV_sendMessage);
}

void Heavy_fire::cVar_W0RQm2D4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_1Y8VqjfP_sendMessage);
}

void Heavy_fire::cUnop_7cP8SM9F_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_4UWqRZBw_sendMessage);
}

void Heavy_fire::cBinop_Y1bW4Jou_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_OuFshthK, HV_BINOP_MULTIPLY, 1, m, &cBinop_OuFshthK_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_7cP8SM9F_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_KAqZqxxO, HV_BINOP_DIVIDE, 0, m, &cBinop_KAqZqxxO_sendMessage);
}

void Heavy_fire::cBinop_zD7Hz7eV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Y1bW4Jou, HV_BINOP_DIVIDE, 0, m, &cBinop_Y1bW4Jou_sendMessage);
}

void Heavy_fire::cBinop_KAqZqxxO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_Tfu9Syh5_sendMessage);
}

void Heavy_fire::cBinop_7Wl8NJ4i_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_dcSR5L3G_sendMessage);
}

void Heavy_fire::cBinop_dcSR5L3G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_s7U7hr99_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZxmxLTnx, HV_BINOP_MULTIPLY, 0, m, &cBinop_ZxmxLTnx_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_OuFshthK, HV_BINOP_MULTIPLY, 0, m, &cBinop_OuFshthK_sendMessage);
}

void Heavy_fire::cBinop_4UWqRZBw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZxmxLTnx, HV_BINOP_MULTIPLY, 1, m, &cBinop_ZxmxLTnx_sendMessage);
}

void Heavy_fire::cBinop_ZxmxLTnx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_RcRs4zag_sendMessage);
}

void Heavy_fire::cCast_QYxifxlR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_kiIdpTTW, 0, m, &cVar_kiIdpTTW_sendMessage);
}

void Heavy_fire::cBinop_ZDMJmiFu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_cJy0kyTQ_sendMessage);
}

void Heavy_fire::cBinop_cJy0kyTQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_OMztWFw8, 5, m);
}

void Heavy_fire::cBinop_RcRs4zag_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_OMztWFw8, 4, m);
}

void Heavy_fire::cBinop_WAQZB6kU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0DWp3BHI, HV_BINOP_MULTIPLY, 0, m, &cBinop_0DWp3BHI_sendMessage);
}

void Heavy_fire::cBinop_OuFshthK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_rOb4WOFl, HV_BINOP_ADD, 1, m, &cBinop_rOb4WOFl_sendMessage);
}

void Heavy_fire::cBinop_s7U7hr99_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_ZDMJmiFu_sendMessage);
}

void Heavy_fire::cBinop_rOb4WOFl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0DWp3BHI, HV_BINOP_MULTIPLY, 1, m, &cBinop_0DWp3BHI_sendMessage);
}

void Heavy_fire::cBinop_0DWp3BHI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_OMztWFw8, 1, m);
}

void Heavy_fire::cBinop_1Y8VqjfP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KAqZqxxO, HV_BINOP_DIVIDE, 1, m, &cBinop_KAqZqxxO_sendMessage);
}

void Heavy_fire::cBinop_Tfu9Syh5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_7Wl8NJ4i_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_rOb4WOFl, HV_BINOP_ADD, 0, m, &cBinop_rOb4WOFl_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_WAQZB6kU_sendMessage);
}

void Heavy_fire::cMsg_ocfPt5Jb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setBang(m, 0);
  cSwitchcase_wLKOJ86C_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fire::cMsg_XiGJYexE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_1VO2mmzz, 0, m, NULL);
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setElementToFrom(m, 1, n, 0);
  sLine_onMessage(_c, &Context(_c)->sLine_1VO2mmzz, 0, m, NULL);
}

void Heavy_fire::cBinop_oeknvxPz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_kiIdpTTW, 0, m, &cVar_kiIdpTTW_sendMessage);
}

void Heavy_fire::cBinop_djYQYHFE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1500.0f, 0, m, &cBinop_oeknvxPz_sendMessage);
}

void Heavy_fire::cVar_5Wh1CsDl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KC4usSCU, HV_BINOP_MULTIPLY, 0, m, &cBinop_KC4usSCU_sendMessage);
}

void Heavy_fire::cMsg_993eTq5K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_BsdWpbI2_sendMessage);
}

void Heavy_fire::cSystem_BsdWpbI2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_SvkxPMU0_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_KC4usSCU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_AFqOsBQi_sendMessage);
}

void Heavy_fire::cBinop_URj6gxnh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KC4usSCU, HV_BINOP_MULTIPLY, 1, m, &cBinop_KC4usSCU_sendMessage);
}

void Heavy_fire::cMsg_SvkxPMU0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_URj6gxnh_sendMessage);
}

void Heavy_fire::cBinop_AFqOsBQi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_TtFBWUXN_sendMessage);
}

void Heavy_fire::cBinop_TtFBWUXN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_ZC2lHrSw_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_GD043OAS, m);
}

void Heavy_fire::cBinop_ZC2lHrSw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_0dYrl7FO, m);
}

void Heavy_fire::cBinop_mH3PF9eO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_R9dwsCDS_sendMessage);
}

void Heavy_fire::cBinop_R9dwsCDS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_JmznA2cC_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_3Kpsl1Kw_sendMessage);
}

void Heavy_fire::cVar_U6GnOpjA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_IXT7RAMs_sendMessage);
}

void Heavy_fire::cMsg_Ilt0iGk8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_QQ6Hm7Pc_sendMessage);
}

void Heavy_fire::cSystem_QQ6Hm7Pc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_9fXP8yNn, HV_BINOP_DIVIDE, 1, m, &cBinop_9fXP8yNn_sendMessage);
}

void Heavy_fire::cBinop_JmznA2cC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_1aqm7f21_sendMessage);
}

void Heavy_fire::cBinop_1aqm7f21_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_1rjhk7qK, m);
}

void Heavy_fire::cMsg_Bfq9DEsf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_vMHwWW7k_sendMessage);
}

void Heavy_fire::cBinop_vMHwWW7k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_mH3PF9eO_sendMessage);
}

void Heavy_fire::cBinop_3Kpsl1Kw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_AMRxcpjc, m);
}

void Heavy_fire::cBinop_IXT7RAMs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_SeeOuMjC_sendMessage);
}

void Heavy_fire::cBinop_SeeOuMjC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_9fXP8yNn, HV_BINOP_DIVIDE, 0, m, &cBinop_9fXP8yNn_sendMessage);
}

void Heavy_fire::cBinop_9fXP8yNn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Bfq9DEsf_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_VW0TBU06_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_sOyHkUYp_sendMessage);
}

void Heavy_fire::cBinop_sOyHkUYp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_ssHohYDm_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_9fyzaIIq_sendMessage);
}

void Heavy_fire::cVar_D6hJFHaU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_7XwUPD3S_sendMessage);
}

void Heavy_fire::cMsg_3ZhotAh5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_lOHg8lJg_sendMessage);
}

void Heavy_fire::cSystem_lOHg8lJg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KKI6M1sS, HV_BINOP_DIVIDE, 1, m, &cBinop_KKI6M1sS_sendMessage);
}

void Heavy_fire::cBinop_ssHohYDm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_FCpzoAFc_sendMessage);
}

void Heavy_fire::cBinop_FCpzoAFc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_TqcYUCVk, m);
}

void Heavy_fire::cMsg_EUhUNmRq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_POGhEgrp_sendMessage);
}

void Heavy_fire::cBinop_POGhEgrp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_VW0TBU06_sendMessage);
}

void Heavy_fire::cBinop_9fyzaIIq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Khyo4hbJ, m);
}

void Heavy_fire::cBinop_7XwUPD3S_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_xBh3PGbR_sendMessage);
}

void Heavy_fire::cBinop_xBh3PGbR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_KKI6M1sS, HV_BINOP_DIVIDE, 0, m, &cBinop_KKI6M1sS_sendMessage);
}

void Heavy_fire::cBinop_KKI6M1sS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_EUhUNmRq_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_5C7RaHm7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_AwLBHJ4B_sendMessage);
}

void Heavy_fire::cBinop_AwLBHJ4B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_W9jACkXm_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_5yVkBxlm_sendMessage);
}

void Heavy_fire::cVar_rAuH50bg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_FX4uGGrI_sendMessage);
}

void Heavy_fire::cMsg_iODYILiT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_NUT3Oal1_sendMessage);
}

void Heavy_fire::cSystem_NUT3Oal1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LJ97TWq3, HV_BINOP_DIVIDE, 1, m, &cBinop_LJ97TWq3_sendMessage);
}

void Heavy_fire::cBinop_W9jACkXm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_nm0aERsY_sendMessage);
}

void Heavy_fire::cBinop_nm0aERsY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_kltPtssX, m);
}

void Heavy_fire::cMsg_Q9Z58P3I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_Pyki2qo3_sendMessage);
}

void Heavy_fire::cBinop_Pyki2qo3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_5C7RaHm7_sendMessage);
}

void Heavy_fire::cBinop_5yVkBxlm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Kt5jfBka, m);
}

void Heavy_fire::cBinop_FX4uGGrI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_KeRNbQtq_sendMessage);
}

void Heavy_fire::cBinop_KeRNbQtq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LJ97TWq3, HV_BINOP_DIVIDE, 0, m, &cBinop_LJ97TWq3_sendMessage);
}

void Heavy_fire::cBinop_LJ97TWq3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Q9Z58P3I_sendMessage(_c, 0, m);
}

void Heavy_fire::cMsg_sfiybO3p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_VEpQHpRS_sendMessage);
}

void Heavy_fire::cSystem_VEpQHpRS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GIPW78FU, HV_BINOP_DIVIDE, 1, m, &cBinop_GIPW78FU_sendMessage);
}

void Heavy_fire::cVar_I7CgNizg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_fTm9RpfZ_sendMessage);
}

void Heavy_fire::cVar_PHeZJtX8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_8GOP10iA_sendMessage);
}

void Heavy_fire::cUnop_H9174bvE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_8VTUFxsV_sendMessage);
}

void Heavy_fire::cBinop_GIPW78FU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_oJX2IMo4, HV_BINOP_MULTIPLY, 1, m, &cBinop_oJX2IMo4_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_H9174bvE_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_OUaQhrxN, HV_BINOP_DIVIDE, 0, m, &cBinop_OUaQhrxN_sendMessage);
}

void Heavy_fire::cBinop_fTm9RpfZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GIPW78FU, HV_BINOP_DIVIDE, 0, m, &cBinop_GIPW78FU_sendMessage);
}

void Heavy_fire::cBinop_OUaQhrxN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_Kp4nkNRD_sendMessage);
}

void Heavy_fire::cBinop_bdZ5oPYK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_FWWyeYAr_sendMessage);
}

void Heavy_fire::cBinop_FWWyeYAr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_GVr2HZn3_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_GgpIyTdC, HV_BINOP_MULTIPLY, 0, m, &cBinop_GgpIyTdC_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_oJX2IMo4, HV_BINOP_MULTIPLY, 0, m, &cBinop_oJX2IMo4_sendMessage);
}

void Heavy_fire::cBinop_8VTUFxsV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GgpIyTdC, HV_BINOP_MULTIPLY, 1, m, &cBinop_GgpIyTdC_sendMessage);
}

void Heavy_fire::cBinop_GgpIyTdC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_JDUIrHxY_sendMessage);
}

void Heavy_fire::cCast_INBQ4M7b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_I7CgNizg, 0, m, &cVar_I7CgNizg_sendMessage);
}

void Heavy_fire::cBinop_fia4HDyW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_81mttI3Y_sendMessage);
}

void Heavy_fire::cBinop_81mttI3Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_IrUyVvQ5, 5, m);
}

void Heavy_fire::cBinop_JDUIrHxY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_IrUyVvQ5, 4, m);
}

void Heavy_fire::cBinop_snAz4xKK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ko5cAvCr, HV_BINOP_MULTIPLY, 0, m, &cBinop_ko5cAvCr_sendMessage);
}

void Heavy_fire::cBinop_oJX2IMo4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Hn1ILxe3, HV_BINOP_ADD, 1, m, &cBinop_Hn1ILxe3_sendMessage);
}

void Heavy_fire::cBinop_GVr2HZn3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_fia4HDyW_sendMessage);
}

void Heavy_fire::cBinop_Hn1ILxe3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ko5cAvCr, HV_BINOP_MULTIPLY, 1, m, &cBinop_ko5cAvCr_sendMessage);
}

void Heavy_fire::cBinop_ko5cAvCr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_IrUyVvQ5, 1, m);
}

void Heavy_fire::cBinop_8GOP10iA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_OUaQhrxN, HV_BINOP_DIVIDE, 1, m, &cBinop_OUaQhrxN_sendMessage);
}

void Heavy_fire::cBinop_Kp4nkNRD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_bdZ5oPYK_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Hn1ILxe3, HV_BINOP_ADD, 0, m, &cBinop_Hn1ILxe3_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_snAz4xKK_sendMessage);
}

void Heavy_fire::cSwitchcase_wZldlNJi_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_632nHA3e, 0, m, &cSlice_632nHA3e_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_TcdOhLAi, 0, m, &cRandom_TcdOhLAi_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_WLgi9qC8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_G9YISozB_sendMessage);
}

void Heavy_fire::cUnop_G9YISozB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_RHQp5VB0_sendMessage(_c, 0, m);
}

void Heavy_fire::cRandom_TcdOhLAi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_WLgi9qC8_sendMessage);
}

void Heavy_fire::cSlice_632nHA3e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_TcdOhLAi, 1, m, &cRandom_TcdOhLAi_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_RHQp5VB0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_nuYriN0y, m);
}

void Heavy_fire::sEnv_HcRaBufw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 50.0f, 0, m, &cBinop_gwIDA9lJ_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_klQ1zrb5, 0, m, &cIf_klQ1zrb5_sendMessage);
}

void Heavy_fire::cVar_4BZNbotf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vFW7VYo4, HV_BINOP_MULTIPLY, 0, m, &cBinop_vFW7VYo4_sendMessage);
}

void Heavy_fire::cMsg_bfH2ps9e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_JoXIUquT_sendMessage);
}

void Heavy_fire::cSystem_JoXIUquT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_SsytIWEC_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_vFW7VYo4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_fG8LDCv6_sendMessage);
}

void Heavy_fire::cBinop_HWoW5nhx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vFW7VYo4, HV_BINOP_MULTIPLY, 1, m, &cBinop_vFW7VYo4_sendMessage);
}

void Heavy_fire::cMsg_SsytIWEC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_HWoW5nhx_sendMessage);
}

void Heavy_fire::cBinop_fG8LDCv6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_7uqBk7lf_sendMessage);
}

void Heavy_fire::cBinop_7uqBk7lf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_BbJnm1vK_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_h8aysor1, m);
}

void Heavy_fire::cBinop_BbJnm1vK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_nmdUWfy1, m);
}

void Heavy_fire::cIf_klQ1zrb5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 51.0f, 0, m, &cBinop_CpABvYvb_sendMessage);
      cIf_onMessage(_c, &Context(_c)->cIf_JGRLTcxZ, 0, m, &cIf_JGRLTcxZ_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_gwIDA9lJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_klQ1zrb5, 1, m, &cIf_klQ1zrb5_sendMessage);
}

void Heavy_fire::cIf_JGRLTcxZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cMsg_JZFu3cs0_sendMessage(_c, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_CpABvYvb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_JGRLTcxZ, 1, m, &cIf_JGRLTcxZ_sendMessage);
}

void Heavy_fire::cSwitchcase_ytk4CaSS_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_ippYlQHs, 0, m, &cSlice_ippYlQHs_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_4CHljkBM, 0, m, &cRandom_4CHljkBM_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_x3sxdMTB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_q4gqWDPu_sendMessage);
}

void Heavy_fire::cUnop_q4gqWDPu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_NP9TqytL_sendMessage(_c, 0, m);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 500.0f, 0, m, &cBinop_N9vZqQiQ_sendMessage);
}

void Heavy_fire::cRandom_4CHljkBM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 30.0f, 0, m, &cBinop_x3sxdMTB_sendMessage);
}

void Heavy_fire::cSlice_ippYlQHs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_4CHljkBM, 1, m, &cRandom_4CHljkBM_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_yIu0JafT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_8xTA83Fk_sendMessage);
}

void Heavy_fire::cSystem_8xTA83Fk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_U1eFR49c, HV_BINOP_DIVIDE, 1, m, &cBinop_U1eFR49c_sendMessage);
}

void Heavy_fire::cVar_xrsNY2oL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_2LrjZlMK_sendMessage);
}

void Heavy_fire::cVar_jzL2fq5k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_cQC8tOzN_sendMessage);
}

void Heavy_fire::cUnop_uNLlI8Ll_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_Vw5wseOm_sendMessage);
}

void Heavy_fire::cBinop_U1eFR49c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Uxm3YhWH, HV_BINOP_MULTIPLY, 1, m, &cBinop_Uxm3YhWH_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_uNLlI8Ll_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_vCIoBZhZ, HV_BINOP_DIVIDE, 0, m, &cBinop_vCIoBZhZ_sendMessage);
}

void Heavy_fire::cBinop_2LrjZlMK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_U1eFR49c, HV_BINOP_DIVIDE, 0, m, &cBinop_U1eFR49c_sendMessage);
}

void Heavy_fire::cBinop_vCIoBZhZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_CMQCGZNF_sendMessage);
}

void Heavy_fire::cBinop_zFcwa157_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_iMgIVkCl_sendMessage);
}

void Heavy_fire::cBinop_iMgIVkCl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_ZBbUoGxL_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_cO4xGMml, HV_BINOP_MULTIPLY, 0, m, &cBinop_cO4xGMml_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Uxm3YhWH, HV_BINOP_MULTIPLY, 0, m, &cBinop_Uxm3YhWH_sendMessage);
}

void Heavy_fire::cBinop_Vw5wseOm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_cO4xGMml, HV_BINOP_MULTIPLY, 1, m, &cBinop_cO4xGMml_sendMessage);
}

void Heavy_fire::cBinop_cO4xGMml_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_NG9yGdXq_sendMessage);
}

void Heavy_fire::cCast_0Eh0YxMU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_xrsNY2oL, 0, m, &cVar_xrsNY2oL_sendMessage);
}

void Heavy_fire::cBinop_E1nL2w9N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_4XZtKOE1_sendMessage);
}

void Heavy_fire::cBinop_4XZtKOE1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Kqj4RjMj, 5, m);
}

void Heavy_fire::cBinop_NG9yGdXq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Kqj4RjMj, 4, m);
}

void Heavy_fire::cBinop_4nh5zmDL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_nz3G5SzZ, HV_BINOP_MULTIPLY, 0, m, &cBinop_nz3G5SzZ_sendMessage);
}

void Heavy_fire::cBinop_Uxm3YhWH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_j7e5Pwe1, HV_BINOP_ADD, 1, m, &cBinop_j7e5Pwe1_sendMessage);
}

void Heavy_fire::cBinop_ZBbUoGxL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_E1nL2w9N_sendMessage);
}

void Heavy_fire::cBinop_j7e5Pwe1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_nz3G5SzZ, HV_BINOP_MULTIPLY, 1, m, &cBinop_nz3G5SzZ_sendMessage);
}

void Heavy_fire::cBinop_nz3G5SzZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_Kqj4RjMj, 1, m);
}

void Heavy_fire::cBinop_cQC8tOzN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vCIoBZhZ, HV_BINOP_DIVIDE, 1, m, &cBinop_vCIoBZhZ_sendMessage);
}

void Heavy_fire::cBinop_CMQCGZNF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_zFcwa157_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_j7e5Pwe1, HV_BINOP_ADD, 0, m, &cBinop_j7e5Pwe1_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_4nh5zmDL_sendMessage);
}

void Heavy_fire::cMsg_JZFu3cs0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setBang(m, 0);
  cSwitchcase_ytk4CaSS_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fire::cMsg_NP9TqytL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_ujk2TaCN, 0, m, NULL);
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setElementToFrom(m, 1, n, 0);
  sLine_onMessage(_c, &Context(_c)->sLine_ujk2TaCN, 0, m, NULL);
}

void Heavy_fire::cBinop_svIsP8kH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_xrsNY2oL, 0, m, &cVar_xrsNY2oL_sendMessage);
}

void Heavy_fire::cBinop_N9vZqQiQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1500.0f, 0, m, &cBinop_svIsP8kH_sendMessage);
}

void Heavy_fire::cVar_mH3YG7FV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dPWfTCFL, HV_BINOP_MULTIPLY, 0, m, &cBinop_dPWfTCFL_sendMessage);
}

void Heavy_fire::cMsg_0MqNxu9M_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_NffOZV3H_sendMessage);
}

void Heavy_fire::cSystem_NffOZV3H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_uJ4TsiNJ_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_dPWfTCFL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_Pepx1rxZ_sendMessage);
}

void Heavy_fire::cBinop_0myDGx9D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dPWfTCFL, HV_BINOP_MULTIPLY, 1, m, &cBinop_dPWfTCFL_sendMessage);
}

void Heavy_fire::cMsg_uJ4TsiNJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_0myDGx9D_sendMessage);
}

void Heavy_fire::cBinop_Pepx1rxZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_i8o7OrUY_sendMessage);
}

void Heavy_fire::cBinop_i8o7OrUY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_RxuIjNyx_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_YcXGKuJk, m);
}

void Heavy_fire::cBinop_RxuIjNyx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_IMApKRie, m);
}

void Heavy_fire::cBinop_PsfJxfkh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_Kf6LMYbb_sendMessage);
}

void Heavy_fire::cBinop_Kf6LMYbb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_XwY7YKmj_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_j5U25pGu_sendMessage);
}

void Heavy_fire::cVar_zLVXEUcc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_FTdY6jX3_sendMessage);
}

void Heavy_fire::cMsg_MrmU8eCw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_X3x1lxiL_sendMessage);
}

void Heavy_fire::cSystem_X3x1lxiL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ikNrgpie, HV_BINOP_DIVIDE, 1, m, &cBinop_ikNrgpie_sendMessage);
}

void Heavy_fire::cBinop_XwY7YKmj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_0Du1xVlf_sendMessage);
}

void Heavy_fire::cBinop_0Du1xVlf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_90tUBjOm, m);
}

void Heavy_fire::cMsg_1YELgQQR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_BtmYr2m3_sendMessage);
}

void Heavy_fire::cBinop_BtmYr2m3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_PsfJxfkh_sendMessage);
}

void Heavy_fire::cBinop_j5U25pGu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_PVIoNJOJ, m);
}

void Heavy_fire::cBinop_FTdY6jX3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_LzU3C0nP_sendMessage);
}

void Heavy_fire::cBinop_LzU3C0nP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ikNrgpie, HV_BINOP_DIVIDE, 0, m, &cBinop_ikNrgpie_sendMessage);
}

void Heavy_fire::cBinop_ikNrgpie_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_1YELgQQR_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_HUtYdTYQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_DkzhSQaF_sendMessage);
}

void Heavy_fire::cBinop_DkzhSQaF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_uvvQBD2B_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_G3gbz0PU_sendMessage);
}

void Heavy_fire::cVar_MDkU5uw8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_o6cKWuda_sendMessage);
}

void Heavy_fire::cMsg_X77fAG1n_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_OmSbDX7Z_sendMessage);
}

void Heavy_fire::cSystem_OmSbDX7Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_XVRjkNYN, HV_BINOP_DIVIDE, 1, m, &cBinop_XVRjkNYN_sendMessage);
}

void Heavy_fire::cBinop_uvvQBD2B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_wIE4FVFp_sendMessage);
}

void Heavy_fire::cBinop_wIE4FVFp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_MarQsZfY, m);
}

void Heavy_fire::cMsg_VZG2M2Ud_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_BhrVtH1D_sendMessage);
}

void Heavy_fire::cBinop_BhrVtH1D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_HUtYdTYQ_sendMessage);
}

void Heavy_fire::cBinop_G3gbz0PU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_sOVZYGy6, m);
}

void Heavy_fire::cBinop_o6cKWuda_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_AbaNrtkh_sendMessage);
}

void Heavy_fire::cBinop_AbaNrtkh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_XVRjkNYN, HV_BINOP_DIVIDE, 0, m, &cBinop_XVRjkNYN_sendMessage);
}

void Heavy_fire::cBinop_XVRjkNYN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_VZG2M2Ud_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_zlmamsUS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_S0lQa3cI_sendMessage);
}

void Heavy_fire::cBinop_S0lQa3cI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_MDOMBFCF_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_2tZ0tsqz_sendMessage);
}

void Heavy_fire::cVar_644RmxHP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_e60dVid0_sendMessage);
}

void Heavy_fire::cMsg_g6toJQIS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_9OgFpxb3_sendMessage);
}

void Heavy_fire::cSystem_9OgFpxb3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sh2HjxYR, HV_BINOP_DIVIDE, 1, m, &cBinop_sh2HjxYR_sendMessage);
}

void Heavy_fire::cBinop_MDOMBFCF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_niZUAldH_sendMessage);
}

void Heavy_fire::cBinop_niZUAldH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_cHjnRVyS, m);
}

void Heavy_fire::cMsg_4v4CFtNi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_nJMo6mK9_sendMessage);
}

void Heavy_fire::cBinop_nJMo6mK9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_zlmamsUS_sendMessage);
}

void Heavy_fire::cBinop_2tZ0tsqz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_149JAOIb, m);
}

void Heavy_fire::cBinop_e60dVid0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_HsN6X9Pf_sendMessage);
}

void Heavy_fire::cBinop_HsN6X9Pf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sh2HjxYR, HV_BINOP_DIVIDE, 0, m, &cBinop_sh2HjxYR_sendMessage);
}

void Heavy_fire::cBinop_sh2HjxYR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_4v4CFtNi_sendMessage(_c, 0, m);
}

void Heavy_fire::cMsg_XVyCVfw9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_NgKDjbUF_sendMessage);
}

void Heavy_fire::cSystem_NgKDjbUF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_7RlBxJNN, HV_BINOP_DIVIDE, 1, m, &cBinop_7RlBxJNN_sendMessage);
}

void Heavy_fire::cVar_0GiTFN2C_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_oV3giG29_sendMessage);
}

void Heavy_fire::cVar_UEBpqTCP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_PZk8UgZI_sendMessage);
}

void Heavy_fire::cUnop_1kblfi0G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_Sb0qAzMJ_sendMessage);
}

void Heavy_fire::cBinop_7RlBxJNN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_7JYjNMW8, HV_BINOP_MULTIPLY, 1, m, &cBinop_7JYjNMW8_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_1kblfi0G_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_tHgUBqo4, HV_BINOP_DIVIDE, 0, m, &cBinop_tHgUBqo4_sendMessage);
}

void Heavy_fire::cBinop_oV3giG29_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_7RlBxJNN, HV_BINOP_DIVIDE, 0, m, &cBinop_7RlBxJNN_sendMessage);
}

void Heavy_fire::cBinop_tHgUBqo4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_sELR0b8P_sendMessage);
}

void Heavy_fire::cBinop_0tlxJYEW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_bEAA0kmC_sendMessage);
}

void Heavy_fire::cBinop_bEAA0kmC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_GN486koD_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_BTfX7uhJ, HV_BINOP_MULTIPLY, 0, m, &cBinop_BTfX7uhJ_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_7JYjNMW8, HV_BINOP_MULTIPLY, 0, m, &cBinop_7JYjNMW8_sendMessage);
}

void Heavy_fire::cBinop_Sb0qAzMJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BTfX7uhJ, HV_BINOP_MULTIPLY, 1, m, &cBinop_BTfX7uhJ_sendMessage);
}

void Heavy_fire::cBinop_BTfX7uhJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_HoRdAVSW_sendMessage);
}

void Heavy_fire::cCast_Ev7OvdTE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_0GiTFN2C, 0, m, &cVar_0GiTFN2C_sendMessage);
}

void Heavy_fire::cBinop_xZHwvBny_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_ctxxblLX_sendMessage);
}

void Heavy_fire::cBinop_ctxxblLX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_zjTNP8bO, 5, m);
}

void Heavy_fire::cBinop_HoRdAVSW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_zjTNP8bO, 4, m);
}

void Heavy_fire::cBinop_MGzVXPnb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_qAaewJSe, HV_BINOP_MULTIPLY, 0, m, &cBinop_qAaewJSe_sendMessage);
}

void Heavy_fire::cBinop_7JYjNMW8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_v6CjUCp7, HV_BINOP_ADD, 1, m, &cBinop_v6CjUCp7_sendMessage);
}

void Heavy_fire::cBinop_GN486koD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_xZHwvBny_sendMessage);
}

void Heavy_fire::cBinop_v6CjUCp7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_qAaewJSe, HV_BINOP_MULTIPLY, 1, m, &cBinop_qAaewJSe_sendMessage);
}

void Heavy_fire::cBinop_qAaewJSe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_zjTNP8bO, 1, m);
}

void Heavy_fire::cBinop_PZk8UgZI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_tHgUBqo4, HV_BINOP_DIVIDE, 1, m, &cBinop_tHgUBqo4_sendMessage);
}

void Heavy_fire::cBinop_sELR0b8P_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_0tlxJYEW_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_v6CjUCp7, HV_BINOP_ADD, 0, m, &cBinop_v6CjUCp7_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_MGzVXPnb_sendMessage);
}

void Heavy_fire::cSwitchcase_YWsYTCb7_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_8iY3tdnO, 0, m, &cSlice_8iY3tdnO_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_zxVmNHcK, 0, m, &cRandom_zxVmNHcK_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_ZPxr6DGE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_fBkvDED0_sendMessage);
}

void Heavy_fire::cUnop_fBkvDED0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_k0XLuLlv_sendMessage(_c, 0, m);
}

void Heavy_fire::cRandom_zxVmNHcK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_ZPxr6DGE_sendMessage);
}

void Heavy_fire::cSlice_8iY3tdnO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_zxVmNHcK, 1, m, &cRandom_zxVmNHcK_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_k0XLuLlv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_70GcWyXx, m);
}

void Heavy_fire::sEnv_5hb5TGQh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 50.0f, 0, m, &cBinop_Rmu8UuVK_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_yltFyPnL, 0, m, &cIf_yltFyPnL_sendMessage);
}

void Heavy_fire::cVar_y62pPsWp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mWgRwiYs, HV_BINOP_MULTIPLY, 0, m, &cBinop_mWgRwiYs_sendMessage);
}

void Heavy_fire::cMsg_aKZcbQnF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_u0eacTLq_sendMessage);
}

void Heavy_fire::cSystem_u0eacTLq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_yRbtdV8e_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_mWgRwiYs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_mEzQU4dD_sendMessage);
}

void Heavy_fire::cBinop_PnbGM7Fc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_mWgRwiYs, HV_BINOP_MULTIPLY, 1, m, &cBinop_mWgRwiYs_sendMessage);
}

void Heavy_fire::cMsg_yRbtdV8e_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_PnbGM7Fc_sendMessage);
}

void Heavy_fire::cBinop_mEzQU4dD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_ie0c4ZiY_sendMessage);
}

void Heavy_fire::cBinop_ie0c4ZiY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_WKdBObu7_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_7jJNCH7z, m);
}

void Heavy_fire::cBinop_WKdBObu7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_iM1VJNgd, m);
}

void Heavy_fire::cIf_yltFyPnL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 51.0f, 0, m, &cBinop_yNasv4BL_sendMessage);
      cIf_onMessage(_c, &Context(_c)->cIf_03Egk6J5, 0, m, &cIf_03Egk6J5_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_Rmu8UuVK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_yltFyPnL, 1, m, &cIf_yltFyPnL_sendMessage);
}

void Heavy_fire::cIf_03Egk6J5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cMsg_bgP2uZIR_sendMessage(_c, 0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cBinop_yNasv4BL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_03Egk6J5, 1, m, &cIf_03Egk6J5_sendMessage);
}

void Heavy_fire::cSwitchcase_wTuxfJBG_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_fEfGU8mn, 0, m, &cSlice_fEfGU8mn_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_y1RlGIkm, 0, m, &cRandom_y1RlGIkm_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_n8Q6uLn8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_BpUrqsNx_sendMessage);
}

void Heavy_fire::cUnop_BpUrqsNx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_wBb3uW3H_sendMessage(_c, 0, m);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 500.0f, 0, m, &cBinop_blxn7iID_sendMessage);
}

void Heavy_fire::cRandom_y1RlGIkm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 30.0f, 0, m, &cBinop_n8Q6uLn8_sendMessage);
}

void Heavy_fire::cSlice_fEfGU8mn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_y1RlGIkm, 1, m, &cRandom_y1RlGIkm_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_8dYuUryI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_kRxiBG5p_sendMessage);
}

void Heavy_fire::cSystem_kRxiBG5p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wJWGzawN, HV_BINOP_DIVIDE, 1, m, &cBinop_wJWGzawN_sendMessage);
}

void Heavy_fire::cVar_gLtQgsPZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_udcF5K4T_sendMessage);
}

void Heavy_fire::cVar_ZFEV08tM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_Gt58Icy0_sendMessage);
}

void Heavy_fire::cUnop_SUJzm5dJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_rBxV7UkY_sendMessage);
}

void Heavy_fire::cBinop_wJWGzawN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_dEVMQ0AF, HV_BINOP_MULTIPLY, 1, m, &cBinop_dEVMQ0AF_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_SUJzm5dJ_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_gZ1VmC7b, HV_BINOP_DIVIDE, 0, m, &cBinop_gZ1VmC7b_sendMessage);
}

void Heavy_fire::cBinop_udcF5K4T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wJWGzawN, HV_BINOP_DIVIDE, 0, m, &cBinop_wJWGzawN_sendMessage);
}

void Heavy_fire::cBinop_gZ1VmC7b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_lfxvQaSb_sendMessage);
}

void Heavy_fire::cBinop_UJaywJFJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_jjCgyfnE_sendMessage);
}

void Heavy_fire::cBinop_jjCgyfnE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_Eit3mevu_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_snElBdDo, HV_BINOP_MULTIPLY, 0, m, &cBinop_snElBdDo_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_dEVMQ0AF, HV_BINOP_MULTIPLY, 0, m, &cBinop_dEVMQ0AF_sendMessage);
}

void Heavy_fire::cBinop_rBxV7UkY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_snElBdDo, HV_BINOP_MULTIPLY, 1, m, &cBinop_snElBdDo_sendMessage);
}

void Heavy_fire::cBinop_snElBdDo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_hdu22PpU_sendMessage);
}

void Heavy_fire::cCast_cgYxSj7N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_gLtQgsPZ, 0, m, &cVar_gLtQgsPZ_sendMessage);
}

void Heavy_fire::cBinop_pcsYy4i7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_4Cve83DT_sendMessage);
}

void Heavy_fire::cBinop_4Cve83DT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_gSadOs7Q, 5, m);
}

void Heavy_fire::cBinop_hdu22PpU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_gSadOs7Q, 4, m);
}

void Heavy_fire::cBinop_RF93sXWF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8V6BxHYi, HV_BINOP_MULTIPLY, 0, m, &cBinop_8V6BxHYi_sendMessage);
}

void Heavy_fire::cBinop_dEVMQ0AF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_qa389xcx, HV_BINOP_ADD, 1, m, &cBinop_qa389xcx_sendMessage);
}

void Heavy_fire::cBinop_Eit3mevu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_pcsYy4i7_sendMessage);
}

void Heavy_fire::cBinop_qa389xcx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8V6BxHYi, HV_BINOP_MULTIPLY, 1, m, &cBinop_8V6BxHYi_sendMessage);
}

void Heavy_fire::cBinop_8V6BxHYi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_gSadOs7Q, 1, m);
}

void Heavy_fire::cBinop_Gt58Icy0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_gZ1VmC7b, HV_BINOP_DIVIDE, 1, m, &cBinop_gZ1VmC7b_sendMessage);
}

void Heavy_fire::cBinop_lfxvQaSb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_UJaywJFJ_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_qa389xcx, HV_BINOP_ADD, 0, m, &cBinop_qa389xcx_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_RF93sXWF_sendMessage);
}

void Heavy_fire::cMsg_bgP2uZIR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setBang(m, 0);
  cSwitchcase_wTuxfJBG_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_fire::cMsg_wBb3uW3H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_4xUtNnbF, 0, m, NULL);
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setElementToFrom(m, 1, n, 0);
  sLine_onMessage(_c, &Context(_c)->sLine_4xUtNnbF, 0, m, NULL);
}

void Heavy_fire::cBinop_WfVVn0oi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_gLtQgsPZ, 0, m, &cVar_gLtQgsPZ_sendMessage);
}

void Heavy_fire::cBinop_blxn7iID_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1500.0f, 0, m, &cBinop_WfVVn0oi_sendMessage);
}

void Heavy_fire::cVar_gkUnCDgN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GKFtNljN, HV_BINOP_MULTIPLY, 0, m, &cBinop_GKFtNljN_sendMessage);
}

void Heavy_fire::cMsg_I2Kxj6l1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_UAJMSlQV_sendMessage);
}

void Heavy_fire::cSystem_UAJMSlQV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_hfFKS9Ze_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_GKFtNljN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_js8DxIV1_sendMessage);
}

void Heavy_fire::cBinop_WX0pWdPG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GKFtNljN, HV_BINOP_MULTIPLY, 1, m, &cBinop_GKFtNljN_sendMessage);
}

void Heavy_fire::cMsg_hfFKS9Ze_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 6.28319f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 0.0f, 0, m, &cBinop_WX0pWdPG_sendMessage);
}

void Heavy_fire::cBinop_js8DxIV1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_zarsNpgH_sendMessage);
}

void Heavy_fire::cBinop_zarsNpgH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_FeCAVQ05_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_pRnoQSnW, m);
}

void Heavy_fire::cBinop_FeCAVQ05_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_f27ahSRi, m);
}

void Heavy_fire::cBinop_fijXImbg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_QSCTqT45_sendMessage);
}

void Heavy_fire::cBinop_QSCTqT45_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_eHD1u3Vu_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_qbdzsVO0_sendMessage);
}

void Heavy_fire::cVar_PJpd1ScB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_iwiuKgXU_sendMessage);
}

void Heavy_fire::cMsg_vhRATarw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_BYDyjqi5_sendMessage);
}

void Heavy_fire::cSystem_BYDyjqi5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_v3mvBKFj, HV_BINOP_DIVIDE, 1, m, &cBinop_v3mvBKFj_sendMessage);
}

void Heavy_fire::cBinop_eHD1u3Vu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_t71HemQq_sendMessage);
}

void Heavy_fire::cBinop_t71HemQq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_OpTRDeab, m);
}

void Heavy_fire::cMsg_r872JdgK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_Np30hElv_sendMessage);
}

void Heavy_fire::cBinop_Np30hElv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_fijXImbg_sendMessage);
}

void Heavy_fire::cBinop_qbdzsVO0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Mu1DaNN9, m);
}

void Heavy_fire::cBinop_iwiuKgXU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_eiuxE74Z_sendMessage);
}

void Heavy_fire::cBinop_eiuxE74Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_v3mvBKFj, HV_BINOP_DIVIDE, 0, m, &cBinop_v3mvBKFj_sendMessage);
}

void Heavy_fire::cBinop_v3mvBKFj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_r872JdgK_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_vzq7IDq7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_TSFHqeiW_sendMessage);
}

void Heavy_fire::cBinop_TSFHqeiW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_BBdamCU7_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_va6si3Xl_sendMessage);
}

void Heavy_fire::cVar_YKk785Yz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_gVRC3974_sendMessage);
}

void Heavy_fire::cMsg_1uePy7VV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_9yzrMvQn_sendMessage);
}

void Heavy_fire::cSystem_9yzrMvQn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hJW4b4CP, HV_BINOP_DIVIDE, 1, m, &cBinop_hJW4b4CP_sendMessage);
}

void Heavy_fire::cBinop_BBdamCU7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_DOwkcwBx_sendMessage);
}

void Heavy_fire::cBinop_DOwkcwBx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_amBDLITl, m);
}

void Heavy_fire::cMsg_TuSJl82V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_jWHRlI1Y_sendMessage);
}

void Heavy_fire::cBinop_jWHRlI1Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_vzq7IDq7_sendMessage);
}

void Heavy_fire::cBinop_va6si3Xl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Ht7WEy23, m);
}

void Heavy_fire::cBinop_gVRC3974_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_ADQNuIoK_sendMessage);
}

void Heavy_fire::cBinop_ADQNuIoK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_hJW4b4CP, HV_BINOP_DIVIDE, 0, m, &cBinop_hJW4b4CP_sendMessage);
}

void Heavy_fire::cBinop_hJW4b4CP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_TuSJl82V_sendMessage(_c, 0, m);
}

void Heavy_fire::cBinop_FaoGtbW9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_88Mi5WNd_sendMessage);
}

void Heavy_fire::cBinop_88Mi5WNd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_8Mwqk3R5_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_wWbTJXxU_sendMessage);
}

void Heavy_fire::cVar_ru05PzHe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_uChLASDG_sendMessage);
}

void Heavy_fire::cMsg_Lc9Oe2V7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Rwdn9fuV_sendMessage);
}

void Heavy_fire::cSystem_Rwdn9fuV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_anzgb48f, HV_BINOP_DIVIDE, 1, m, &cBinop_anzgb48f_sendMessage);
}

void Heavy_fire::cBinop_8Mwqk3R5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 0.5f, 0, m, &cBinop_VOxYie4X_sendMessage);
}

void Heavy_fire::cBinop_VOxYie4X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_CMFL5gw2, m);
}

void Heavy_fire::cMsg_kweYGzeD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  msg_setElementToFrom(m, 1, n, 0);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 0.0f, 0, m, &cBinop_eRZldkgN_sendMessage);
}

void Heavy_fire::cBinop_eRZldkgN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_FaoGtbW9_sendMessage);
}

void Heavy_fire::cBinop_wWbTJXxU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_ztmXlqss, m);
}

void Heavy_fire::cBinop_uChLASDG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_pZpzSIA5_sendMessage);
}

void Heavy_fire::cBinop_pZpzSIA5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_anzgb48f, HV_BINOP_DIVIDE, 0, m, &cBinop_anzgb48f_sendMessage);
}

void Heavy_fire::cBinop_anzgb48f_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_kweYGzeD_sendMessage(_c, 0, m);
}

void Heavy_fire::cMsg_4I3jxPrY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_WKFlQxAq_sendMessage);
}

void Heavy_fire::cSystem_WKFlQxAq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_7zPOCAwo, HV_BINOP_DIVIDE, 1, m, &cBinop_7zPOCAwo_sendMessage);
}

void Heavy_fire::cVar_WbRfCgvw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_gt6qLVJc_sendMessage);
}

void Heavy_fire::cVar_FEEXGm1N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_TLKu2jNe_sendMessage);
}

void Heavy_fire::cUnop_jt9GlduX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_BLqnJzRi_sendMessage);
}

void Heavy_fire::cBinop_7zPOCAwo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_BpWr8g9i, HV_BINOP_MULTIPLY, 1, m, &cBinop_BpWr8g9i_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_jt9GlduX_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_7B90G5dK, HV_BINOP_DIVIDE, 0, m, &cBinop_7B90G5dK_sendMessage);
}

void Heavy_fire::cBinop_gt6qLVJc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_7zPOCAwo, HV_BINOP_DIVIDE, 0, m, &cBinop_7zPOCAwo_sendMessage);
}

void Heavy_fire::cBinop_7B90G5dK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_tNIu0cEc_sendMessage);
}

void Heavy_fire::cBinop_EZ85fjcE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_E2Zprnp4_sendMessage);
}

void Heavy_fire::cBinop_E2Zprnp4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_geBYzesJ_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_6PN9qwml, HV_BINOP_MULTIPLY, 0, m, &cBinop_6PN9qwml_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_BpWr8g9i, HV_BINOP_MULTIPLY, 0, m, &cBinop_BpWr8g9i_sendMessage);
}

void Heavy_fire::cBinop_BLqnJzRi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6PN9qwml, HV_BINOP_MULTIPLY, 1, m, &cBinop_6PN9qwml_sendMessage);
}

void Heavy_fire::cBinop_6PN9qwml_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_waD2pBc3_sendMessage);
}

void Heavy_fire::cCast_qQcEgLCp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_WbRfCgvw, 0, m, &cVar_WbRfCgvw_sendMessage);
}

void Heavy_fire::cBinop_Qu8lEiGc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_urNj0gdi_sendMessage);
}

void Heavy_fire::cBinop_urNj0gdi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_JAO8SSKE, 5, m);
}

void Heavy_fire::cBinop_waD2pBc3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_JAO8SSKE, 4, m);
}

void Heavy_fire::cBinop_Ry2RlX7J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_l4TIgls4, HV_BINOP_MULTIPLY, 0, m, &cBinop_l4TIgls4_sendMessage);
}

void Heavy_fire::cBinop_BpWr8g9i_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_E31UEUhA, HV_BINOP_ADD, 1, m, &cBinop_E31UEUhA_sendMessage);
}

void Heavy_fire::cBinop_geBYzesJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Qu8lEiGc_sendMessage);
}

void Heavy_fire::cBinop_E31UEUhA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_l4TIgls4, HV_BINOP_MULTIPLY, 1, m, &cBinop_l4TIgls4_sendMessage);
}

void Heavy_fire::cBinop_l4TIgls4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_JAO8SSKE, 1, m);
}

void Heavy_fire::cBinop_TLKu2jNe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_7B90G5dK, HV_BINOP_DIVIDE, 1, m, &cBinop_7B90G5dK_sendMessage);
}

void Heavy_fire::cBinop_tNIu0cEc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_EZ85fjcE_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_E31UEUhA, HV_BINOP_ADD, 0, m, &cBinop_E31UEUhA_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_Ry2RlX7J_sendMessage);
}

void Heavy_fire::cSwitchcase_2CtQ9PiM_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_mdkx9ITY, 0, m, &cSlice_mdkx9ITY_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_U5wakTjg, 0, m, &cRandom_U5wakTjg_sendMessage);
      break;
    }
  }
}

void Heavy_fire::cBinop_txdGTZ1Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_BPzEgw73_sendMessage);
}

void Heavy_fire::cUnop_BPzEgw73_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_HX69JGrh_sendMessage(_c, 0, m);
}

void Heavy_fire::cRandom_U5wakTjg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_txdGTZ1Z_sendMessage);
}

void Heavy_fire::cSlice_mdkx9ITY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_U5wakTjg, 1, m, &cRandom_U5wakTjg_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_fire::cMsg_HX69JGrh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_ikEfWqJc, m);
}

void Heavy_fire::cReceive_uNgTd9wt_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_0E8Iy6iy_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_RDJ6WgRc, 0, m, &cVar_RDJ6WgRc_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_5hwv5XFn, 0, m, &cVar_5hwv5XFn_sendMessage);
  cMsg_awRGtLg0_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_Ds8MHzqi, 0, m, &cVar_Ds8MHzqi_sendMessage);
  cMsg_j8KPxKA2_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_PcB1Qch2, 0, m, &cVar_PcB1Qch2_sendMessage);
  cMsg_yMzO2rtq_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_tXak5h1S, 0, m, &cVar_tXak5h1S_sendMessage);
  cMsg_CBhBeLS9_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_BtMSkQX1, 0, m, &cVar_BtMSkQX1_sendMessage);
  cMsg_wE1t3B6s_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_j4kFBEUB, 0, m, &cVar_j4kFBEUB_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_ALfL3XkX, 0, m, &cVar_ALfL3XkX_sendMessage);
  cMsg_eFs6TDmP_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_uDnroDkH, 0, m, &cVar_uDnroDkH_sendMessage);
  cMsg_9Xw6TJxK_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_eLbPwBo7, 0, m, &cVar_eLbPwBo7_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_W0RQm2D4, 0, m, &cVar_W0RQm2D4_sendMessage);
  cMsg_HsP9fwKH_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_kiIdpTTW, 0, m, &cVar_kiIdpTTW_sendMessage);
  cMsg_993eTq5K_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_5Wh1CsDl, 0, m, &cVar_5Wh1CsDl_sendMessage);
  cMsg_Ilt0iGk8_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_U6GnOpjA, 0, m, &cVar_U6GnOpjA_sendMessage);
  cMsg_3ZhotAh5_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_D6hJFHaU, 0, m, &cVar_D6hJFHaU_sendMessage);
  cMsg_iODYILiT_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_rAuH50bg, 0, m, &cVar_rAuH50bg_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_PHeZJtX8, 0, m, &cVar_PHeZJtX8_sendMessage);
  cMsg_sfiybO3p_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_I7CgNizg, 0, m, &cVar_I7CgNizg_sendMessage);
  cMsg_bfH2ps9e_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_4BZNbotf, 0, m, &cVar_4BZNbotf_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_jzL2fq5k, 0, m, &cVar_jzL2fq5k_sendMessage);
  cMsg_yIu0JafT_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_xrsNY2oL, 0, m, &cVar_xrsNY2oL_sendMessage);
  cMsg_0MqNxu9M_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_mH3YG7FV, 0, m, &cVar_mH3YG7FV_sendMessage);
  cMsg_MrmU8eCw_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_zLVXEUcc, 0, m, &cVar_zLVXEUcc_sendMessage);
  cMsg_X77fAG1n_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_MDkU5uw8, 0, m, &cVar_MDkU5uw8_sendMessage);
  cMsg_g6toJQIS_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_644RmxHP, 0, m, &cVar_644RmxHP_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_UEBpqTCP, 0, m, &cVar_UEBpqTCP_sendMessage);
  cMsg_XVyCVfw9_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_0GiTFN2C, 0, m, &cVar_0GiTFN2C_sendMessage);
  cMsg_aKZcbQnF_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_y62pPsWp, 0, m, &cVar_y62pPsWp_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_ZFEV08tM, 0, m, &cVar_ZFEV08tM_sendMessage);
  cMsg_8dYuUryI_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_gLtQgsPZ, 0, m, &cVar_gLtQgsPZ_sendMessage);
  cMsg_I2Kxj6l1_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_gkUnCDgN, 0, m, &cVar_gkUnCDgN_sendMessage);
  cMsg_vhRATarw_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_PJpd1ScB, 0, m, &cVar_PJpd1ScB_sendMessage);
  cMsg_1uePy7VV_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_YKk785Yz, 0, m, &cVar_YKk785Yz_sendMessage);
  cMsg_Lc9Oe2V7_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_ru05PzHe, 0, m, &cVar_ru05PzHe_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_FEEXGm1N, 0, m, &cVar_FEEXGm1N_sendMessage);
  cMsg_4I3jxPrY_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_WbRfCgvw, 0, m, &cVar_WbRfCgvw_sendMessage);
  cSwitchcase_hOBdudiM_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_wZldlNJi_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_YWsYTCb7_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_2CtQ9PiM_onMessage(_c, NULL, 0, m, NULL);
  cMsg_aG75Gsly_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_ktV61nl5, 0, m, &cVar_ktV61nl5_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_NYOeA9Xu, 0, m, &cVar_NYOeA9Xu_sendMessage);
  cMsg_f5B4hNhT_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_uzJLoGmk, 0, m, &cVar_uzJLoGmk_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_CpYthQ1A, 0, m, &cVar_CpYthQ1A_sendMessage);
  cMsg_ylm5mWQk_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_ujKljZq6, 0, m, &cVar_ujKljZq6_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_ogzujkvo, 0, m, &cVar_ogzujkvo_sendMessage);
  cMsg_9usCBUnn_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_duUaHnF2, 0, m, &cVar_duUaHnF2_sendMessage);
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

int Heavy_fire::process(float **inputBuffers, float **outputBuffers, int n) {
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6, Bf7;
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
    __hv_varread_i(&sVari_70GcWyXx, VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_cast_if(VIi(Bi1), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varwrite_i(&sVari_70GcWyXx, VIi(Bi1));
    __hv_varread_f(&sVarf_PVIoNJOJ, VOf(Bf0));
    __hv_rpole_f(&sRPole_Zvm60JXX, VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_d0qSJz2T, VIf(Bf0), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_sub_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_90tUBjOm, VOf(Bf0));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_YcXGKuJk, VOf(Bf2));
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_IMApKRie, VOf(Bf3));
    __hv_rpole_f(&sRPole_teg7J78G, VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f);
    __hv_mul_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf3), 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f);
    __hv_mul_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf0), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_varread_f(&sVarf_h8aysor1, VOf(Bf2));
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_nmdUWfy1, VOf(Bf4));
    __hv_rpole_f(&sRPole_WXiBm1BV, VIf(Bf2), VIf(Bf4), VOf(Bf4));
    sEnv_process(this, &sEnv_HcRaBufw, VIf(Bf4), &sEnv_HcRaBufw_sendMessage);
    __hv_biquad_k_f(&sBiquad_k_Kqj4RjMj, VIf(Bf1), VOf(Bf4));
    __hv_line_f(&sLine_ujk2TaCN, VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf4), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_biquad_k_f(&sBiquad_k_zjTNP8bO, VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_149JAOIb, VOf(Bf1));
    __hv_rpole_f(&sRPole_b3LENND6, VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_Wtvk7aa5, VIf(Bf1), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf5), VOf(Bf5));
    __hv_sub_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_cHjnRVyS, VOf(Bf1));
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f);
    __hv_min_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f);
    __hv_max_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_sOVZYGy6, VOf(Bf5));
    __hv_rpole_f(&sRPole_igciWS8Y, VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_mGwraXOm, VIf(Bf5), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf1), VOf(Bf1));
    __hv_sub_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_MarQsZfY, VOf(Bf5));
    __hv_mul_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf1), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf5), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf5), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf1), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf2), VIf(Bf4), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf3), VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_Yiuu6ozd, VOf(Bf0));
    __hv_rpole_f(&sRPole_4SXzyKj7, VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_ip21GDmS, VIf(Bf0), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_sub_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_IsaB45V5, VOf(Bf0));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_i(&sVari_YzFhuSTd, VOi(Bi1));
    __hv_var_k_i(VOi(Bi0), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi1), VIi(Bi0), VOi(Bi0));
    __hv_cast_if(VIi(Bi0), VOf(Bf5));
    __hv_var_k_f(VOf(Bf3), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_varwrite_i(&sVari_YzFhuSTd, VIi(Bi0));
    __hv_varread_f(&sVarf_UCDbV3Ks, VOf(Bf5));
    __hv_rpole_f(&sRPole_1Nq4fDcG, VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf4), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_SH95fq5n, VIf(Bf5), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf4), VOf(Bf4));
    __hv_sub_f(VIf(Bf5), VIf(Bf4), VOf(Bf4));
    __hv_varread_f(&sVarf_puRdoxX1, VOf(Bf5));
    __hv_mul_f(VIf(Bf4), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_5rn0X7FY, VOf(Bf4));
    __hv_mul_f(VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_varread_f(&sVarf_VY3VvNQd, VOf(Bf2));
    __hv_rpole_f(&sRPole_Z3f6KqpI, VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf4), 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f);
    __hv_mul_f(VIf(Bf2), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf2), 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f);
    __hv_mul_f(VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf5), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_varread_f(&sVarf_TBlgpnmT, VOf(Bf4));
    __hv_mul_f(VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_varread_f(&sVarf_B6litlPZ, VOf(Bf1));
    __hv_rpole_f(&sRPole_dl1j1F86, VIf(Bf4), VIf(Bf1), VOf(Bf1));
    sEnv_process(this, &sEnv_pbcOLK2k, VIf(Bf1), &sEnv_pbcOLK2k_sendMessage);
    __hv_biquad_k_f(&sBiquad_k_iiXEOgZC, VIf(Bf3), VOf(Bf1));
    __hv_line_f(&sLine_9Jrwqhtg, VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf1), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf1), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_biquad_k_f(&sBiquad_k_fkvUbsvR, VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf6), 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f);
    __hv_mul_f(VIf(Bf3), VIf(Bf6), VOf(Bf6));
    __hv_varread_f(&sVarf_mgvuRGEU, VOf(Bf3));
    __hv_rpole_f(&sRPole_i30l2Q1z, VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf6), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_gyuRVh9c, VIf(Bf3), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf6), VOf(Bf6));
    __hv_sub_f(VIf(Bf3), VIf(Bf6), VOf(Bf6));
    __hv_varread_f(&sVarf_2U6cRxgG, VOf(Bf3));
    __hv_mul_f(VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf6), 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f);
    __hv_min_f(VIf(Bf3), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf3), -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f);
    __hv_max_f(VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_ZFCRxAqE, VOf(Bf6));
    __hv_rpole_f(&sRPole_82ggxPOT, VIf(Bf3), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_bQ9Mzt19, VIf(Bf6), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf3), VOf(Bf3));
    __hv_sub_f(VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_nu3rDj1z, VOf(Bf6));
    __hv_mul_f(VIf(Bf3), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf3), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf6), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf3), VIf(Bf6), VOf(Bf6));
    __hv_fma_f(VIf(Bf4), VIf(Bf1), VIf(Bf6), VOf(Bf6));
    __hv_fma_f(VIf(Bf2), VIf(Bf5), VIf(Bf6), VOf(Bf6));
    __hv_biquad_k_f(&sBiquad_k_ojWLoQVU, VIf(Bf6), VOf(Bf6));
    __hv_add_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_varread_i(&sVari_nuYriN0y, VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_cast_if(VIi(Bi1), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varwrite_i(&sVari_nuYriN0y, VIi(Bi1));
    __hv_varread_f(&sVarf_AMRxcpjc, VOf(Bf0));
    __hv_rpole_f(&sRPole_58i9pni3, VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf2), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_siSjl8RL, VIf(Bf0), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_sub_f(VIf(Bf0), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_1rjhk7qK, VOf(Bf0));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_GD043OAS, VOf(Bf2));
    __hv_mul_f(VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_0dYrl7FO, VOf(Bf1));
    __hv_rpole_f(&sRPole_BAAyUlkr, VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf1), 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f);
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_varread_f(&sVarf_XEPszT7W, VOf(Bf2));
    __hv_mul_f(VIf(Bf5), VIf(Bf2), VOf(Bf2));
    __hv_varread_f(&sVarf_H3kcSvxt, VOf(Bf4));
    __hv_rpole_f(&sRPole_4cRr6HOc, VIf(Bf2), VIf(Bf4), VOf(Bf4));
    sEnv_process(this, &sEnv_eKpodMzB, VIf(Bf4), &sEnv_eKpodMzB_sendMessage);
    __hv_biquad_k_f(&sBiquad_k_OMztWFw8, VIf(Bf5), VOf(Bf4));
    __hv_line_f(&sLine_1VO2mmzz, VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf2), VOf(Bf2));
    __hv_mul_f(VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf4), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_biquad_k_f(&sBiquad_k_IrUyVvQ5, VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf3), 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f);
    __hv_mul_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_Kt5jfBka, VOf(Bf5));
    __hv_rpole_f(&sRPole_c15qA2wZ, VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf3), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_TGq1yCe7, VIf(Bf5), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf3), VOf(Bf3));
    __hv_sub_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_kltPtssX, VOf(Bf5));
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf3), 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f);
    __hv_min_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf5), -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f);
    __hv_max_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_Khyo4hbJ, VOf(Bf3));
    __hv_rpole_f(&sRPole_9lxN9iWN, VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_dShGt7Vn, VIf(Bf3), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf5), VOf(Bf5));
    __hv_sub_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_TqcYUCVk, VOf(Bf3));
    __hv_mul_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf5), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf3), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf2), VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf1), VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_biquad_k_f(&sBiquad_k_L14V5tqI, VIf(Bf3), VOf(Bf3));
    __hv_add_f(VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_varread_i(&sVari_ikEfWqJc, VOi(Bi1));
    __hv_var_k_i(VOi(Bi0), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi1), VIi(Bi0), VOi(Bi0));
    __hv_cast_if(VIi(Bi0), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_varwrite_i(&sVari_ikEfWqJc, VIi(Bi0));
    __hv_varread_f(&sVarf_Mu1DaNN9, VOf(Bf6));
    __hv_rpole_f(&sRPole_vBCjLGUm, VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf1), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_QyQPtba2, VIf(Bf6), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_sub_f(VIf(Bf6), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_OpTRDeab, VOf(Bf6));
    __hv_mul_f(VIf(Bf1), VIf(Bf6), VOf(Bf6));
    __hv_varread_f(&sVarf_pRnoQSnW, VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_f27ahSRi, VOf(Bf4));
    __hv_rpole_f(&sRPole_jOLaKpmC, VIf(Bf1), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf1), 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f);
    __hv_mul_f(VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf4), 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f, 600.0f);
    __hv_mul_f(VIf(Bf1), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf6), VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf6), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_varread_f(&sVarf_7jJNCH7z, VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_iM1VJNgd, VOf(Bf2));
    __hv_rpole_f(&sRPole_na8JVF1C, VIf(Bf1), VIf(Bf2), VOf(Bf2));
    sEnv_process(this, &sEnv_5hb5TGQh, VIf(Bf2), &sEnv_5hb5TGQh_sendMessage);
    __hv_biquad_k_f(&sBiquad_k_gSadOs7Q, VIf(Bf0), VOf(Bf2));
    __hv_line_f(&sLine_4xUtNnbF, VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf2), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf2), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_biquad_k_f(&sBiquad_k_JAO8SSKE, VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f);
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_ztmXlqss, VOf(Bf0));
    __hv_rpole_f(&sRPole_Xf7ktnoR, VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_9xjY62G0, VIf(Bf0), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf5), VOf(Bf5));
    __hv_sub_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_CMFL5gw2, VOf(Bf0));
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f);
    __hv_min_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f, -0.9f);
    __hv_max_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_Ht7WEy23, VOf(Bf5));
    __hv_rpole_f(&sRPole_GTOgJonj, VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    __hv_del1_f(&sDel1_Wcmt6orU, VIf(Bf5), VOf(Bf7));
    __hv_mul_f(VIf(Bf7), VIf(Bf0), VOf(Bf0));
    __hv_sub_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_amBDLITl, VOf(Bf5));
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf0), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf5), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_mul_f(VIf(Bf0), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf1), VIf(Bf2), VIf(Bf5), VOf(Bf5));
    __hv_fma_f(VIf(Bf4), VIf(Bf6), VIf(Bf5), VOf(Bf5));
    __hv_biquad_k_f(&sBiquad_k_X9hDAJPC, VIf(Bf5), VOf(Bf5));
    __hv_add_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_var_k_f(VOf(Bf3), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_mul_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_add_f(VIf(Bf3), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf3), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_fire::processInline(float *inputBuffers, float *outputBuffers, int n4) {
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

int Heavy_fire::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
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
