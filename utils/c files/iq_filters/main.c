

#include <stdio.h>
#include <math.h>


struct SOS{
	
	float xz2;
	float xz1;
	float yz2;		
	
	
};

struct SOS quad_sos={0}; 		// for inphase parameters
struct SOS inphase_sos={0}; 	// for inphase parameters


float sos_implementation(float x ,float yBack, const float *coeffs, struct SOS *back){

	float y;
	


	
	y=x*(coeffs[0])	+	(back->xz1)	*(coeffs[1])		+	(back->xz2)*(coeffs[2])
					- 	(yBack)		*(coeffs[3])		-	(back->yz2)*(coeffs[4]);

	
	back->yz2=yBack;
	back->xz2=back->xz1;
	back->xz1=x;
	
	return y;
	
}


int main(){

const float inphase_coeffs[]={

 0.015389671404524f,
-0.000158728429331f,
-0.015230942975193f,
-1.968424561991035f,
 0.969376917213154f

};

const float quad_coeffs[]={

 0.000159966471496193f,
 0.000634890686255913f,
 0.000157498064366761f,
-1.968424561991035f,
 0.969376917213154f

};

int i;
float input[800];
float output_i[800]={0};
float output_q[800]={0};
float	output;

for(i=1;i<800;i++){


	input[i]=2*sin(2.0f*3.14159f*(float)i/200.0f);
	output_i[i]=sos_implementation(input[i],output_i[i-1],inphase_coeffs	,&inphase_sos);
	output_q[i]=sos_implementation(input[i],output_q[i-1],quad_coeffs		,&quad_sos);
	
	printf("ended val:%f\n",sqrtf(output_i[i]*output_i[i]+output_q[i]*output_q[i]));
	}

	i--;













}
