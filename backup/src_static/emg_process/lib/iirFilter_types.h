/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: iirFilter_types.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 10-Jul-2022 17:29:38
 */

#ifndef IIRFILTER_TYPES_H
#define IIRFILTER_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_dsp_BiquadFilter_0
#define typedef_dsp_BiquadFilter_0
typedef struct {
  int S0_isInitialized;
  double W0_FILT_STATES[4];
  int W1_PreviousNumChannels;
  double P0_ICRTP;
  double P1_RTP1COEFF[6];
  double P2_RTP2COEFF[4];
  double P3_RTP3COEFF[3];
  boolean_T P4_RTP_COEFF3_BOOL[3];
} dsp_BiquadFilter_0;
#endif /* typedef_dsp_BiquadFilter_0 */

#ifndef typedef_dspcodegen_BiquadFilter
#define typedef_dspcodegen_BiquadFilter
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  boolean_T isSetupComplete;
  dsp_BiquadFilter_0 cSFunObject;
} dspcodegen_BiquadFilter;
#endif /* typedef_dspcodegen_BiquadFilter */

#endif
/*
 * File trailer for iirFilter_types.h
 *
 * [EOF]
 */
