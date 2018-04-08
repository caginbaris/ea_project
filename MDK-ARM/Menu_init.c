#include "menu_definitions.h"
#include "lcd_definitions.h"



enum menu_list current_menu=Vpn_true;
enum menu_list next_menu=Vpn_true;
enum input pressed;


struct display_menu_handles Vpn_Menu= {
	
	/*dynamicData*/	{0.0f,0.0f,0.0f},
	
	/*title*/      	{0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, 
	
	/*fist line*/ 	{0,0,0},
	/*second line*/ {0,0,0},
	/*third line*/ 	{0,0,0},
	
	/*symbols*/			{0,0,0,0,0},
	/*button*/			0,
	
	/*functionPointers*/ font_transfer,
	/*functionPointers*/ font_transfer2 // cau




};


// menu transition


struct MENU_TRANSITION menu_transItion[][3]={
	
	//	current menu----input-----------next menu
	
		{	Vpn_true,				right_pressed,	Vpn_fund},
		{	Vpn_fund,				left_pressed,		Vpn_true},
		{	Vpn_true,				down_pressed,		Vpp_true},
		{	Vpn_fund,				down_pressed,		Vpp_fund},
		
		{	Vpp_true,				right_pressed,	Vpp_fund},
		{	Vpp_fund,				left_pressed,		Vpp_true},
		{	Vpp_true,				down_pressed,		Ip_true},
		{	Vpp_fund,				down_pressed,		Ip_fund},
		{	Vpp_true,				up_pressed,			Vpn_true},
		{	Vpp_fund,				up_pressed,		  Vpn_fund},
		
		{	Ip_true,				right_pressed,	Ip_fund},
		{	Ip_fund,				left_pressed,		Ip_true},
		{	Ip_true,				up_pressed,			Ip_true},
		{	Ip_fund,				up_pressed,			Ip_fund},
		

};











