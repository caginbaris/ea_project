#include "menu_definitions.h"
#include "lcd_definitions.h"





	
void dynamicDataTripple(float* val){
	
	float first,second,third;
	enum units first_unit,second_unit,third_unit;
	
	
	first=*val++;
	second=*val++;
	third=*val;
	
	
	//format
	
	
	if(first>1000.0f && first<10000.0f){first=first*0.001f;first_unit=u_K;}
	if(first>1000.0f && first<10000.0f){first=first*0.001f;first_unit=u_K;}

	
	
	//unit

};
	



void DISPLAY_MENU( struct display_menu_handles menu_item){

	uint8_t page=1;

	// define function for title data
	
	menu_item.staticDataTransfer();
	menu_item.dynamicDataTransfer();

	
	//define function for button definition symbols
	
	// befor transferring real dynamic data it should be formatted accordingly)

	
	// define function for button evaluation for transition between menus
	
	
	
	


};