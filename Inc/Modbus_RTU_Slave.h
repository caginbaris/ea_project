/**
  ******************************************************************************
  * @file    Modbus_RTU_Slave.h
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    15-November-2016
  * @brief   Modbus RTU Slave Application Layer Header File
  ******************************************************************************
  */

#include "stdint.h"

#ifndef MODBUS_RTU_SLAVE_H
#define MODBUS_RTU_SLAVE_H


#define DEBUG                      0

#define RX_BUFFER_LIMIT            300
#define TX_BUFFER_LIMIT            300//cau
#define WRITE_MULTIPLE_BUFFER_LIMIT 100
#define WRITE_SINGLE_BUFFER_LIMIT   4


#define DI1000_UI_SLAVE_ID         250
#define SLAVE_ID                   0
#define TOT_NUM_OF_INT_SLAVE_DEVICES 10
#define MODBUS_STARTING_ADRESS     1000
#define MODBUS_UPPER_LIMIT_ADRESS  3000
#define MODBUS_LOWER_LIMIT_ADRESS  1000
#define READ_HOLDING_REGISTER_ADRESS_LIMIT 1900
#define WRITE_MULTIPLE_REGISTER_ADRESS_LIMIT 2100
#define MODBUS_MAX_DATA_LEN        40000


#define FUNCODE                    1
#define REG_ADRESS_HIGH            2
#define REG_ADRESS_LOW             3
#define DATA_LEN_HIGH              4
#define DATA_LEN_LOW               5
#define RES_BYTE_COUNT             2

#define READ_HOLDING_REGISTER      3
#define READ_DISCRETE_INPUT        2
#define WRITE_MULTIPLE_REGISTER    16
#define WRITE_SINGLE_REGISTER      6
#define UNIQUE_FUNCTION_REGISTER   0X31


#define READ_TEST1                 1000
#define READ_TEST2                 1002
#define READ_TEST3                 1004

#define WRITE_TEST1                 1000
#define WRITE_TEST2                 1002
#define WRITE_TEST3                 1004

#define WRITE_SINGLE_TEST1          1000
#define WRITE_SINGLE_TEST2          1001
#define WRITE_SINGLE_TEST3          1002

#define READ_IN_CH1                 1000
#define READ_IN_CH2                 1002
#define READ_IN_CH3                 1004
#define READ_IN_CH4                 1003
#define READ_IN_CH5                 1004
#define READ_IN_CH6                 1005
#define READ_IN_CH7                 1006
#define READ_IN_CH8                 1007
#define READ_IN_CH9                 1008
#define READ_IN_CH10                 1009
#define READ_IN_CH11                 1010
#define READ_IN_CH12                 1011
#define READ_IN_CH13                 1012
#define READ_IN_CH14                 1013
#define READ_IN_CH15                 1014
#define READ_IN_CH16                 1015
#define READ_IN_ALL                  1016
#define READ_OUT_ALL                 1017
#define READ_RELAY_LATCH_TIMEOUT1    1018
#define READ_RELAY_LATCH_TIMEOUT2    1019
#define READ_RELAY_LATCH_TIMEOUT3    1020
#define READ_RELAY_LATCH_TIMEOUT4    1021
#define READ_RELAY_LATCH_TIMEOUT5    1022
#define READ_RELAY_LATCH_TIMEOUT6    1023
#define READ_RELAY_LATCH_TIMEOUT7    1024
#define READ_RELAY_LATCH_TIMEOUT8    1025
#define READ_RELAY_LATCHTYPE_ALL     1026
#define READ_IN_TEST_MODE            1027
#define READ_IN_INVERSE_POL_ALL      1028
#define READ_SLAVE_ID                1029


#define WRITE_OUT_CH1                1000
#define WRITE_OUT_CH2                1001
#define WRITE_OUT_CH3                1002
#define WRITE_OUT_CH4                1003
#define WRITE_OUT_CH5                1004
#define WRITE_OUT_CH6                1005
#define WRITE_OUT_CH7                1006
#define WRITE_OUT_CH8                1007
#define WRITE_LATCH_TIMEOUT          1008
#define WRITE_LATCH_TYPE             1009
#define WRITE_SOFTWARE_RESET         1010   
#define FLASH_SAVE_ALL               1011
#define CHANGE_INPUT_TEST_SINGLE     1012

#define CHANGE_INPUT_TEST            2000
#define CHANGE_INPUT_CH1             2001
#define CHANGE_INPUT_CH2             2002
#define CHANGE_INPUT_CH3             2003
#define CHANGE_INPUT_CH4             2004
#define CHANGE_INPUT_CH5             2005
#define CHANGE_INPUT_CH6             2006
#define CHANGE_INPUT_CH7             2007
#define CHANGE_INPUT_CH8             2008
#define CHANGE_INPUT_CH9             2009
#define CHANGE_INPUT_CH10            2010
#define CHANGE_INPUT_CH11            2011
#define CHANGE_INPUT_CH12            2012
#define CHANGE_INPUT_CH13            2013
#define CHANGE_INPUT_CH14            2014
#define CHANGE_INPUT_CH15            2015
#define CHANGE_INPUT_CH16            2016
#define CHANGE_INPUT_POL_CH1         2017
#define CHANGE_INPUT_POL_CH2         2018
#define CHANGE_INPUT_POL_CH3         2019
#define CHANGE_INPUT_POL_CH4         2020
#define CHANGE_INPUT_POL_CH5         2021
#define CHANGE_INPUT_POL_CH6         2022
#define CHANGE_INPUT_POL_CH7         2023
#define CHANGE_INPUT_POL_CH8         2024
#define CHANGE_INPUT_POL_CH9         2025
#define CHANGE_INPUT_POL_CH10        2026
#define CHANGE_INPUT_POL_CH11        2027
#define CHANGE_INPUT_POL_CH12        2028
#define CHANGE_INPUT_POL_CH13        2029
#define CHANGE_INPUT_POL_CH14         2030
#define CHANGE_INPUT_POL_CH15         2031
#define CHANGE_INPUT_POL_CH16         2032
#define CHANGE_INPUT_POL_ALL          2033
#define CHANGE_RELAY_LATCH_TIMEOUT1   2034
#define CHANGE_RELAY_LATCH_TIMEOUT2   2035
#define CHANGE_RELAY_LATCH_TIMEOUT3   2036
#define CHANGE_RELAY_LATCH_TIMEOUT4   2037
#define CHANGE_RELAY_LATCH_TIMEOUT5   2038
#define CHANGE_RELAY_LATCH_TIMEOUT6   2039
#define CHANGE_RELAY_LATCH_TIMEOUT7   2040
#define CHANGE_RELAY_LATCH_TIMEOUT8   2041
#define CHANGE_RELAY_LATCH_TYPEALL    2042
#define CHANGE_UART_BAUDRATE         2043
#define CHANGE_SLAVE_ID              2044
#define CHANGE_OUTPUT_RESET_TYPE     2045


void rtu_crcCalculation(unsigned char *crcBuf, uint16_t crcLength);
void rtu_ModbusFrameProcessing(void);
void rtu_readHoldingRegister(void);
void rtu_Feeder1DataPrep(void);

void rtu_transmitData_readHoldingRegister(void);
void rtu_transmitData_writeMultipleRegisters(void);
void rtu_writeMultipleRegisters(void);
void rtu_getFeeder1_writeMultipleRegisters(void);
void rtu_transmitData_writeSingleRegister(void);
void rtu_getFeeder1_writeSingleRegister(void);
void rtu_writeSingleRegister(void);
void rtu_readUniqueRegisters(void);

typedef struct
{
  uint16_t calculated;
  uint16_t calculated_H;
  uint16_t calculated_L;
  uint16_t received;
  uint16_t received_H;
  uint16_t received_L;
}Typedef_rtuCRC;

typedef struct
{
	uint32_t CH1;
	uint32_t CH2;
	uint32_t CH3;
	uint32_t CH4;
	uint32_t CH5;
	uint32_t CH6;
}Typedef_dummyTestData;



#endif /* MODBUS_RTU_SLAVE_H */
