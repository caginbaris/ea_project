#ifndef __aux_functions_H__
#define __aux_functions_H__

#include <stdint.h>

uint8_t on_delay			(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count);
uint8_t off_delay			(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count);
uint8_t on_off_delay	(uint8_t input, uint8_t mem, uint16_t qual_sample, uint32_t *count);

#endif