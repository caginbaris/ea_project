#ifndef __aux_functions_H__
#define __aux_functions_H__

#include <stdint.h>

uint8_t on_delay			(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count);
uint8_t off_delay			(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count);
uint8_t on_off_delay	(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count);
void  i_limiter( int8_t down_limit, int8_t up_limit, int8_t *value );
void ui_limiter(uint8_t down_limit,uint8_t up_limit,uint8_t *value );
#endif