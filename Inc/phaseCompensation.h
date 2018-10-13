#ifndef __phaseCompensation_H
#define __phaseCompensation_H

void  pLagDef(float lag,float fs, float* b1,float* b2);
float pDiffer(float in,float coeff1, float coeff2, float* xback );

#endif