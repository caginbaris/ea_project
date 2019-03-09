	
#include <stdint.h>
	
	
/*init data for single supply 3.3V with internal booster on*/	
const uint8_t LCD_batch_init_array[]={
	
0x40,	// Send hex 40 to the display: Display start line = 0
0xA1,	// Send hex A1 to the display: ADC reverse, 6 o'clock viewing direction
0xC0,	// Send hex C0 to the display: COM0 – COM63 in normal scan mode
0xA6,	// Send hex A6 to the display: Display normal, not mirrored
0xA2,	// Send hex A2 to the display: Set bias 1/9 (Duty 1/65)
0x2F,	// Send hex 2F to the display: Booster, regulator and follower on
0xF8,	// Send hex F8 to the display: Set internal booster to 4x
0x0,	// Send hex 00 to the display: Set internal booster to 4x
0x27,	// Send hex 27 to the display: Contrast set
0x81,	// Send hex 81 to the display: Contrast set
0x16,	// Send hex 16 to the display: Contrast set
0xAC,	// Send hex AC to the display: No indicator
0x0,	// Send hex 00 to the display: No indicator
0xAF	// Send hex AF to the display: No indicator

};


uint8_t display_buffer[8][128]={0x00};

