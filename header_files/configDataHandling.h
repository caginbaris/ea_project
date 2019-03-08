#ifndef __configDataHandling_H
#define __configDataHandling_H

#define VT_limit_primer_limit 	250000
#define VT_limit_seconder_limit 400

#define CT_limit_primer_limit 	250000
#define CT_limit_seconder_limit 5

#define phase_shift_limit 5

#define pulse_period_limit 100
#define inc_factor_limit 100

#define adress_limit 5

#define output_energy_pulse_source_limit 7

#define comm_baud_rate_limit 7
#define commMode_limit 4


void configDataHandling(void);
void MX_USART3_UART_Init(void);

#endif