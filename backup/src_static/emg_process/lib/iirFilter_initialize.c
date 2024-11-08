/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: iirFilter_initialize.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 10-Jul-2022 17:29:38
 */

/* Include Files */
#include "iirFilter_initialize.h"
#include "iirFilter.h"
#include "iirFilter_data.h"
#include "iirFilter_types.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void iirFilter_initialize(void)
{
  static const signed char iv[6] = {1, 2, 1, 1, 2, 1};
  int i;
  iirFilter_init();
  /*  设计滤波器系数时使用了以下代码: */
  /*  */
  /*  N    = 4;    % Order */
  /*  F3dB = 4;    % 3-dB Frequency */
  /*  Fs   = 100;  % Sampling Frequency */
  /*  */
  /*  h = fdesign.lowpass('n,f3db', N, F3dB, Fs); */
  /*  */
  /*  Hd = design(h, 'butter', ... */
  /*      'SystemObject', true); */
  /* System object Constructor function: dsp.BiquadFilter */
  Hd.cSFunObject.P0_ICRTP = 0.0;
  for (i = 0; i < 6; i++) {
    Hd.cSFunObject.P1_RTP1COEFF[i] = iv[i];
  }
  Hd.cSFunObject.P2_RTP2COEFF[0] = -1.76882785992372;
  Hd.cSFunObject.P2_RTP2COEFF[1] = 0.826201332947616;
  Hd.cSFunObject.P2_RTP2COEFF[2] = -1.57523997778815;
  Hd.cSFunObject.P2_RTP2COEFF[3] = 0.626334259159141;
  Hd.cSFunObject.P3_RTP3COEFF[0] = 0.0143433682559736;
  Hd.cSFunObject.P4_RTP_COEFF3_BOOL[0] = true;
  Hd.cSFunObject.P3_RTP3COEFF[1] = 0.0127735703427475;
  Hd.cSFunObject.P4_RTP_COEFF3_BOOL[1] = true;
  Hd.cSFunObject.P3_RTP3COEFF[2] = 0.0;
  Hd.cSFunObject.P4_RTP_COEFF3_BOOL[2] = false;
  Hd.matlabCodegenIsDeleted = false;
  /* System object Initialization function: dsp.BiquadFilter */
  Hd.cSFunObject.W0_FILT_STATES[0] = 0.0;
  Hd.cSFunObject.W0_FILT_STATES[1] = 0.0;
  Hd.cSFunObject.W0_FILT_STATES[2] = 0.0;
  Hd.cSFunObject.W0_FILT_STATES[3] = 0.0;
  isInitialized_iirFilter = true;
}

/*
 * File trailer for iirFilter_initialize.c
 *
 * [EOF]
 */
