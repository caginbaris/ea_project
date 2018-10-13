#include <math.h>

#define pi 3.14159f

void pLagDef(float lag,float fs, float* b1,float* b2){

float shift,D,beta,An,w;

shift=lag*pi/180;
w=(2*pi*50)/fs;
D=shift/w;

beta=-((1-2*D)*cosf(w)-sqrtf(((1-2*D)*cosf(w))*((1-2*D)*cosf(w)) +4*D*(1-D)))/(2*(1-D));
An=sqrtf((cosf(w)+beta)*(cosf(w)+beta) +sinf(w)*sinf(w));

*b1=1/An;
*b2=beta/An;

}


float pDiffer(float in,float coeff1, float coeff2, float* xback ){

 float out;

 out= in*coeff1+ (*xback)*coeff2;
*xback=in;

return out;


}