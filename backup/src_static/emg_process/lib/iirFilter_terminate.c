/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: iirFilter_terminate.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 10-Jul-2022 17:29:38
 */

/* Include Files */
#include "iirFilter_terminate.h"
#include "iirFilter.h"
#include "iirFilter_data.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void iirFilter_terminate(void)
{
  iirFilter_free();
  isInitialized_iirFilter = false;
}

/*
 * File trailer for iirFilter_terminate.c
 *
 * [EOF]
 */
