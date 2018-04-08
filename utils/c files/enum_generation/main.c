

#include <stdio.h>


int main(){

char c;



FILE *f = fopen("enumerated_letters.h", "w");
const char *text1= "enum letter_codes_8pt{\n";
const char *text2= "}; //\enum for lowercase letters";

printf("enumareted array generation...\n");

fprintf(f,"%s",text1);


    for(c = 'a'; c <= 'z'; c++){
      
	 fprintf(f, "%c,\n",c);
    }

	fprintf(f, "%s", text2);
	fclose(f);
	

}

	


    








