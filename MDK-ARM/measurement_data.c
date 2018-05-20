
#include "measurement_definitions.h"

union RMS rms={5911,321442,41,6111,6,7,5,3};

//10 khz, k=1 
//coefficents for SOGI integs b1----b2----b3----a2----a3----

const float inphase_coeffs[]={

 0.015389671404524f,
-0.000158728429331f,
-0.015230942975193f,
-1.968424561991035f,
 0.969376917213154f

};

 
 
const float quad_coeffs[]={

 0.000159966471496193f,
-0.000634890686255913f,
-0.000159966471496193f,
-1.968424561991035f,
 0.969376917213154f

};