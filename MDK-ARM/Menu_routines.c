#include "menu_definitions.h"
#include "lcd_definitions.h"

float values[3]={0};
enum units unit=V;


	
void dynamicData(float* val,enum units unit){


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