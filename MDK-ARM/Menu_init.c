#include "menu_definitions.h"
#include "lcd_definitions.h"
#include "measurement_definitions.h"







enum menu_list current_menu=Vpn_true;
enum menu_list next_menu=Vpn_true;
enum input pressed;

union display_menu_union MENU={0};




struct display_menu_handles Vpn_true_Menu= {
	
	/*dynamic data*/ &(rms.AN.Vpn_true_a),
	
	/*title*/      	{v,_,f,a,z,_,n,o,t,r,_,g,e,r,c,e,k}, 
	
	/*fist line*/ 	{V,A,N},
	/*second line*/ {V,B,N},
	/*third line*/ 	{V,C,N},
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,0},
	/*menu units*/	{m_V,m_,m_,m_},

	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Vpn_fund_Menu= {
	
	/*dynamic data*/ &(rms.AN.Vpn_fund_a),
	
	/*title*/      	{v,_,f,a,z,_,n,o,t,r,_,a,n,a,_,_,_}, 
	
	/*fist line*/ 	{V,A,N},
	/*second line*/ {V,B,N},
	/*third line*/ 	{V,C,N},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,0},
	/*menu units*/	{m_V,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};



struct display_menu_handles Vpp_true_Menu= {
	
	/*dynamic data*/ &(rms.AN.Vpp_true_a),
	
	/*title*/      	{v,_,_,f,a,z,_,f,a,z,_,g,e,r,c,e,k}, 
	
	/*fist line*/ 	{V,A,B},
	/*second line*/ {V,B,C},
	/*third line*/ 	{V,C,A},
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,0},
	/*menu units*/	{m_V,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Vpp_fund_Menu= {
	
	/*dynamic data*/ &(rms.AN.Vpp_fund_a),
	
	/*title*/      	{v,_,_,f,a,z,_,f,a,z,_,a,n,a,_,_,_}, 
	
	/*fist line*/ 	{V,A,B},
	/*second line*/ {V,B,C},
	/*third line*/ 	{V,C,A},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,0},
	/*menu units*/	{m_V,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


// menu transition









const struct MENU_TRANSITION menu_transition[]={
	
	//	current menu----input-----------next menu
	
		{	Vpn_true,				right_pressed,	Vpn_fund},
		{	Vpn_true,				down_pressed,		Vpp_true},
		
		{	Vpn_fund,				left_pressed,		Vpn_true},
		{	Vpn_fund,				down_pressed,		Vpp_fund},
		
		{	Vpp_true,				right_pressed,	Vpp_fund},
		{	Vpp_true,				down_pressed,		Ip_true},
		{	Vpp_true,				up_pressed,			Vpn_true},
		
		{	Vpp_fund,				down_pressed,		Ip_fund},
		{	Vpp_fund,				up_pressed,		  Vpn_fund},
		{	Vpp_fund,				left_pressed,		Vpp_true},
		
		{	Ip_true,				right_pressed,	Ip_fund},
		{	Ip_fund,				left_pressed,		Ip_true},
		{	Ip_true,				up_pressed,			Ip_true},
		{	Ip_fund,				up_pressed,			Ip_fund},
		

};






void init_Menu(){
	
	
	MENU.handle.Vpn_true=	Vpn_true_Menu;
	MENU.handle.Vpn_fund=	Vpn_fund_Menu;
	
	MENU.handle.Vpp_true=	Vpp_true_Menu;
	MENU.handle.Vpp_true=	Vpp_fund_Menu;

	


}






