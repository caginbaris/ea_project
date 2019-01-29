#ifndef __phaseCompensation_H
#define __phaseCompensation_H


extern float pc_b1 ,pc_b2;
extern float pc_b12,pc_b22;

void pLagDef(float lag,float samp, float* b1,float* b2);
float pDiffer(float in,float coeff1, float coeff2, float* xback );

#endif


