#include "menu_definitions.h" 
#include "lcd_definitions.h"
#include "measurement_definitions.h"
#include <stdlib.h>







enum menu_list current_menu=main_menu;
enum menu_list previous_menu=Vpn_fund;//cau should be different at startup wrt current menu
enum main_menu_list main_menu_entry=Vpp_main;
struct main_menu_rows main_lines;
union display_menu_union MENU={0};

/*for main menu listing*/
enum letter_codes_8pt main_menu_entries[][20]={
{_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
{f,a,z,_,n,o,t,r,_,g,e,r,i,l,i,m,_,r,m,s},
{f,a,z,_,f,a,z,_,_,g,e,r,i,l,i,m,_,r,m,s},
{f,a,z,_,a,k,i,m,_,r,m,s,_,_,_,_,_,_,_,_},
{a,k,t,i,f,_,g,u,c,l,e,r,_,_,_,_,_,_,_,_},
{r,e,a,k,t,i,f,_,g,u,c,l,e,r,_,_,_,_,_,_},
{g,o,r,u,n,e,n,_,g,u,c,l,e,r,_,_,_,_,_,_},
{t,o,p,l,a,m,_,_,g,u,c,l,e,r,_,_,_,_,_,_},
{g,u,c,_,f,a,k,t,o,r,l,e,r,i,_,_,_,_,_,_},
{t,o,p,l,a,m,_,g,u,c,_,f,a,k,t,o,r,u,_,_},		
};



 

struct display_menu_handles Main_Menu={

	/*null pointer*/NULL,
	/*no data for main*/{0},
	/*no data for main*/{0},
	/*no data for main*/{0},
	/*no data for main*/{0},
	/*symbols*/			{menu_enter,0,0,menu_down,menu_up},
	/*no data for main*/{0},
	/*null pointer*/toMainDetect,
	/*null pointer*/atMainOperation,
};

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
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,menu_up},
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
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_V,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};



struct display_menu_handles Ip_true_Menu= {
	
	/*dynamic data*/ &(rms.AN.Ip_true_a),
	
	/*title*/      	{a,k,i,m,_,g,e,r,c,e,k,_,r,m,s,_,_}, 
	
	/*fist line*/ 	{I,A,P},
	/*second line*/ {I,B,P},
	/*third line*/ 	{I,C,P},
	
	/*symbols*/			{menu_escape,0,menu_right,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_,},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Ip_fund_Menu= {
	
	/*dynamic data*/ &(rms.AN.Ip_fund_a),
	
	/*title*/      	{a,k,i,m,_,_,a,n,a,_,_,r,m,s,_,_,_} ,
	
	/*fist line*/ 	{I,A,P},
	/*second line*/ {I,B,P},
	/*third line*/ 	{I,C,P},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Active_Power_Menu= {
	
	/*dynamic data*/ &(rms.AN.Ip_fund_a),
	
	/*title*/      	{a,k,t,i,f,_,g,u,c,_,_,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{I,A,P},
	/*second line*/ {I,B,P},
	/*third line*/ 	{I,C,P},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Reactive_Power_Menu= {
	
	/*dynamic data*/ &(rms.AN.Ip_fund_a),
	
	/*title*/      	{r,e,a,k,t,i,f,_,g,u,c,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{I,A,P},
	/*second line*/ {I,B,P},
	/*third line*/ 	{I,C,P},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};


struct display_menu_handles Apparent_Power_Menu= {
	
	/*dynamic data*/ &(rms.AN.Ip_fund_a),
	
	/*title*/      	{g,o,r,u,n,e,n,_,g,u,c,_,_,_,_,_,_,_} ,
	
	/*fist line*/ 	{I,A,P},
	/*second line*/ {I,B,P},
	/*third line*/ 	{I,C,P},
	
	/*symbols*/			{menu_escape,menu_left,0,menu_down,menu_up},
	/*menu units*/	{m_A,m_,m_,m_},
	/*static data*/  staticDataTripple,
	/*dynamic data*/ dynamicDataTripple
	

};







// menu transition









const struct MENU_TRANSITION menu_transition[]={
	
	//	current menu----input-----------next menu
	
		{	Vpn_true,				right_pressed,	Vpn_fund},
		{	Vpn_true,				down_pressed,		Vpp_true},
		{	Vpn_true,				enter_pressed,	main_menu},
		
		{	Vpn_fund,				left_pressed,		Vpn_true},
		{	Vpn_fund,				down_pressed,		Vpp_fund},
		{	Vpn_true,				enter_pressed,	main_menu},
		
		{	Vpp_true,				right_pressed,	Vpp_fund},
		{	Vpp_true,				down_pressed,		Ip_true},
		{	Vpp_true,				up_pressed,			Vpn_true},
		{	Vpp_true,				enter_pressed,	main_menu},
		
		{	Vpp_fund,				left_pressed,		Vpp_true},
		{	Vpp_fund,				down_pressed,		Ip_fund},
		{	Vpp_fund,				up_pressed,		  Vpn_fund},
		{	Vpp_fund,				enter_pressed,	main_menu},
		
		{	Ip_true,				right_pressed,	Ip_fund},
		{	Ip_true,				up_pressed,			Vpp_true},
		{	Ip_true,				down_pressed,		Active_Power},
		{	Ip_true,				enter_pressed,	main_menu},
		
		{	Ip_fund,				left_pressed,		Ip_true},
		{	Ip_fund,				up_pressed,			Vpp_fund},
		{	Ip_fund,				down_pressed,		Active_Power},
		{	Ip_fund,				enter_pressed,	main_menu},
		
		{	Active_Power,		up_pressed,		Ip_true},
		
		
		
		

};






void init_Menu(){
	
	MENU.handle.main_menu=Main_Menu;
	
	MENU.handle.Vpn_true=	Vpn_true_Menu;
	MENU.handle.Vpn_fund=	Vpn_fund_Menu;
	
	MENU.handle.Vpp_true=	Vpp_true_Menu;
	MENU.handle.Vpp_fund=	Vpp_fund_Menu;

	MENU.handle.Ip_true=	Ip_true_Menu;
	MENU.handle.Ip_fund=	Ip_fund_Menu;
	
	MENU.handle.Active_Power=Active_Power_Menu;
	MENU.handle.Reactive_Power=Reactive_Power_Menu;
	MENU.handle.Apparent_Power=Apparent_Power_Menu;
	
}






