/**
  ******************************************************************************
  * @file    Modbus_RTU_Slave.c
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    15-November-2016
  * @brief   Modbus RTU Slave Application Layer File
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include "Modbus_RTU_Slave.h"
#include "menu_definitions.h"

//mein

#include "Modbus_Map.h"


/* User Variables ------------------------------------------------------------*/
uint16_t rtu_modbusRxFrameLen;
extern uint16_t rtu_ModbusRxIndex;
uint16_t crcRecieved, crcCalculated;
extern unsigned char rtu_modbusRxBuffer[RX_BUFFER_LIMIT];
unsigned char rtu_modbusTxBuffer[TX_BUFFER_LIMIT];
int32_t rtu_modbusWriteBuffer[WRITE_MULTIPLE_BUFFER_LIMIT];
int32_t rtu_modbusSingleWriteBuffer[WRITE_SINGLE_BUFFER_LIMIT];
uint16_t rtu_modbusRegAdress, rtu_modbusDataLen, rtu_modbusTxLen;
uint16_t rtu_selectedSlaveID;
uint16_t rtu_txBufferIndex;
uint32_t rtu_modbusStartingAdress, rtu_modbusEndingAdress;
uint32_t rtu_deviceSlaveID[10];
uint8_t rtu_sendFlag;
uint8_t rtu_softwareReset = 0;
uint32_t RELAY_LATCH_TIMEOUT;
uint32_t  LATCH_TYPE;
uint8_t flashSaveAll = 0;
uint8_t rtuMasterSlaveID = 0;
uint8_t masterModeOp = 0;
extern uint32_t fckcnt;
extern uint8_t comErrorFlag;
extern HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
extern UART_HandleTypeDef huart3;
/* Typedefs ------------------------------------------------------------------*/
Typedef_rtuCRC rtuCRC;
Typedef_dummyTestData dummyTestData;


//mein

union dummy_float{

float dm_f;
unsigned char dm_uch[4];	

};


union dummy_u32{

uint32_t dm_u;
unsigned char dm_uch[4];	

};

union dummy_float df={3.1f};
union dummy_u32 du={0};

uint32_t dummy_write=0;

/**
  * @brief  This function performs Modbus CRC16 generation.  
  * @param  crcBuf:Input buffer that contains related registers to be calculated
  * @param  crcLength: CRC16 length
  * @retval None
  */

void rtu_crcCalculation(unsigned char *crcBuf, uint16_t crcLength)
{
   uint16_t crcTemp, crcRes;
   uint16_t i, j;
   crcRes = 0xFFFF;

    for (i = 0; i < crcLength; i++)
    {
      crcRes = crcRes ^ crcBuf[i];
      for ( j = 0; j < 8; j++)
      {
        crcTemp = crcRes & 0x0001;
        crcRes = crcRes >> 1;
        if (crcTemp)
        {
            crcRes = crcRes ^ 0xa001;
        }
      }
    }
    rtuCRC.calculated = crcRes;
    rtuCRC.calculated_L = (crcRes & 0XFF00) >> 8 ;
    rtuCRC.calculated_H = (crcRes & 0X00FF);
}

/**
  * @brief  This function performs incoming RTU data frame processing and
  			extracts all modbus master requests and returns from function when
  			unexpected frame is received.
  * @note   After debug operation, DEBUG flag should be reset in header file 
  			not to add additional delay to real-time process.
  * @param  none
  * @retval None
  */

void rtu_ModbusFrameProcessing(void)
{
      if ((rtu_modbusRxBuffer[SLAVE_ID] == rtu_deviceSlaveID[0]) || rtu_modbusRxBuffer[SLAVE_ID] == DI1000_UI_SLAVE_ID)
      {
        rtu_selectedSlaveID = rtu_deviceSlaveID[0];
        #if DEBUG
        printf("Selected device is me \n");
        printf("Request device id is %d \n", rtu_selectedSlaveID);
        #endif
      }

      else
      {
        #if DEBUG
        printf("Selected device is not me \n");
        #endif

        return;
      }
    

    rtu_modbusRegAdress = (rtu_modbusRxBuffer[REG_ADRESS_HIGH] << 8) | rtu_modbusRxBuffer[REG_ADRESS_LOW]; //jj 16bitlik bir dataya aktaraliyor adres bilgisi
	
    if (rtu_modbusRegAdress >= MODBUS_LOWER_LIMIT_ADRESS && rtu_modbusRegAdress <= MODBUS_UPPER_LIMIT_ADRESS)
    {
      #if DEBUG
      printf("Modbus RTU starting adress is in the range \n");
      printf("Modbus RTU starting adress is %d \n", rtu_modbusRegAdress);
      #endif
    }
		
    else
    {
      #if DEBUG
      printf("Modbus RTU starting adress is out of range of device \n");
      #endif

      return;
    }
		
    rtu_modbusDataLen = (rtu_modbusRxBuffer[DATA_LEN_HIGH] << 8) | rtu_modbusRxBuffer[DATA_LEN_LOW];

    if(rtu_modbusDataLen <= MODBUS_MAX_DATA_LEN)
    {
      #if DEBUG
      printf("Modbus RTU requested data length is in the range \n");
      printf("Modbus RTU requested data length is %d \n", rtu_modbusDataLen);
      #endif
    }

    else
    {
      #if DEBUG
      printf("Modbus RTU requested data length is out of the range \n");
      #endif

      return;
    }

    rtuCRC.received_H = rtu_modbusRxBuffer[rtu_ModbusRxIndex - 2];
    rtuCRC.received_L = rtu_modbusRxBuffer[rtu_ModbusRxIndex - 1];
    rtu_modbusRxFrameLen = rtu_ModbusRxIndex - 2;
    rtu_crcCalculation(rtu_modbusRxBuffer, rtu_modbusRxFrameLen);

    if ((rtuCRC.received_L == rtuCRC.calculated_L) && (rtuCRC.received_H == rtuCRC.calculated_H))
    {
      #if DEBUG
      printf("CRC Check is OK \n");
      #endif
    }

    else
    {
      #if DEBUG
      printf("CRC Check is not OK \n");
      #endif
      return;
    }

    rtu_modbusStartingAdress = rtu_modbusRegAdress;
    rtu_modbusEndingAdress = rtu_modbusStartingAdress + rtu_modbusDataLen;

		
    switch(rtu_modbusRxBuffer[FUNCODE])
    {
      case READ_HOLDING_REGISTER:   
			{
				if(rtu_modbusEndingAdress > READ_HOLDING_REGISTER_ADRESS_LIMIT )
				{
					#if DEBUG
					printf("Requested data adress and length is not satisfied \n");
					#endif
		
					return;
				}
				rtu_readHoldingRegister(); //jj frame adjusted, sent data transmitted in nested funcs
				break;
			}
			
			case WRITE_SINGLE_REGISTER:
			{
				#if DEBUG
        printf("I am in Single Write function \n");
        printf("rtu_modbusRegAdress is %d \n",rtu_modbusRegAdress);
        printf("rtu_modbusStartingAdress is %d \n",rtu_modbusStartingAdress);
        printf("rtu_modbusEndingAdress is %d \n",rtu_modbusEndingAdress);
        printf("rtu_modbusDataLen is %d \n",rtu_modbusDataLen);
        printf("Selected ID is %d \n",rtu_selectedSlaveID);
				#endif
				rtu_writeSingleRegister();//jj not functional care
				break;
			}
				
      case WRITE_MULTIPLE_REGISTER: 
      {
				if(rtu_modbusEndingAdress > WRITE_MULTIPLE_REGISTER_ADRESS_LIMIT)
				{
					#if DEBUG
					printf("Requested data adress and length is not satisfied \n");
					#endif		
					return;
				}
				
				#if DEBUG
        printf("I am in Multiple Write function \n");
        printf("rtu_modbusRegAdress is %d \n",rtu_modbusRegAdress);
        printf("rtu_modbusStartingAdress is %d \n",rtu_modbusStartingAdress);
        printf("rtu_modbusEndingAdress is %d \n",rtu_modbusEndingAdress);
        printf("rtu_modbusDataLen is %d \n",rtu_modbusDataLen);
        printf("Selected ID is %d \n",rtu_selectedSlaveID);
				#endif
        rtu_writeMultipleRegisters(); // data set-write and send op.
        break;
      }
			
			case UNIQUE_FUNCTION_REGISTER:
			{
				#if DEBUG
				printf("I am in Unique Read function \n");
        printf("rtu_modbusRegAdress is %d \n",rtu_modbusRegAdress);
        printf("rtu_modbusStartingAdress is %d \n",rtu_modbusStartingAdress);
        printf("rtu_modbusEndingAdress is %d \n",rtu_modbusEndingAdress);
        printf("rtu_modbusDataLen is %d \n",rtu_modbusDataLen);
        printf("Selected ID is %d \n",rtu_selectedSlaveID);
				#endif
				rtu_readUniqueRegisters();
				break;
			}
			
      default: 
      {
				
				//jj exception code on illegal fc should be sent
        #if DEBUG
        printf("Modbus rtu function code is wrong !\n");
        #endif

        break;
      } 
    }

}

void rtu_readUniqueRegisters(void)
{
	  #if 0 
	  rtu_txBufferIndex = 3;
    rtu_modbusTxBuffer[SLAVE_ID] = rtu_modbusRxBuffer[SLAVE_ID];
    rtu_modbusTxBuffer[FUNCODE] = rtu_modbusRxBuffer[FUNCODE];
    rtu_modbusTxBuffer[RES_BYTE_COUNT] = 2 * rtu_modbusDataLen;

  if (rtu_modbusRegAdress == READ_IN_CH1)
  {
      rtu_modbusTxBuffer[rtu_txBufferIndex++] = (0x0000FF00 & (uint32_t)(rtu_deviceSlaveID[0])) >> 8;
      rtu_modbusTxBuffer[rtu_txBufferIndex++] = (0x000000FF & (uint32_t)(rtu_deviceSlaveID[0]));
      rtu_modbusRegAdress += 1;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
  }
	
	rtu_transmitData_readHoldingRegister();
	#endif
}
/**
  * @brief  This function includes Modbus RTU Holding Register function 
            implementation.
  * @note   This function is written for multiple slave devices in one
            device. Making this function for only one slave ID makes this
            function generic for other platforms.
  * @param  none
  * @retval None
  */

void rtu_readHoldingRegister(void)
{
    rtu_txBufferIndex = 3;
    rtu_modbusTxBuffer[SLAVE_ID] = rtu_modbusRxBuffer[SLAVE_ID];
    rtu_modbusTxBuffer[FUNCODE] = rtu_modbusRxBuffer[FUNCODE];
    rtu_modbusTxBuffer[RES_BYTE_COUNT] = 2 * rtu_modbusDataLen;

    if(rtu_selectedSlaveID == rtu_deviceSlaveID[0]) rtu_Feeder1DataPrep();
}

/**
  * @brief  This function includes Modbus RTU Holding Register function 
            implementation.
  * @note   This function is written for multiple slave devices in one
            device. Making this function for only one slave ID makes this
            function generic for other platforms.
  * @param  none
  * @retval None
  */

void rtu_writeMultipleRegisters(void)
{
    if(rtu_selectedSlaveID == rtu_deviceSlaveID[0]) rtu_getFeeder1_writeMultipleRegisters();
}


/**
  * @brief  This function includes Modbus RTU Holding Register function 
            implementation.
  * @note   This function is written for multiple slave devices in one
            device. Making this function for only one slave ID makes this
            function generic for other platforms.
  * @param  none
  * @retval None
  */
void rtu_getFeeder1_writeMultipleRegisters(void)
{
	
		uint8_t i=0,a=0;
	
    rtu_ModbusRxIndex = 7;
	  
    if (rtu_modbusRegAdress == 1000)
    {
      flashNew.bBuffer[3] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
      flashNew.bBuffer[2] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
			flashNew.bBuffer[1] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
      flashNew.bBuffer[0] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
      
			
			rtu_modbusRegAdress += 2;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
    }
	
		if (rtu_modbusRegAdress == 1002)
    {
      flashNew.bBuffer[7] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
      flashNew.bBuffer[6] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
			flashNew.bBuffer[5] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
      flashNew.bBuffer[4] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
			
      rtu_modbusRegAdress += 2;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;

			
    }
		
		#if 0
		//**alternate-start
		
		
			for(i=0;i<rtu_modbusDataLen;i+=2){
	
			if (rtu_modbusRegAdress == (READ_IN_CH1+i)){
				
			flashNew.bBuffer[a+3] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
      flashNew.bBuffer[a+2] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
			flashNew.bBuffer[a+1] = rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
      flashNew.bBuffer[a] 	= rtu_modbusRxBuffer[rtu_ModbusRxIndex++];
			
			a+=4;
			
				}
			
			}
			
			#endif
		
		//*alternate-end
		
		
		
		
		
    rtu_transmitData_writeMultipleRegisters();
}




/**
  * @brief  This function performs modbus RTU response to Modbus Master's request
        according to appropriate slave ID, function code, data adress and 
        data length.
  * @note   DMA function is platform specific function. It should be changed 
            in other platforms.
  * @param  none
  * @retval None
  */
void rtu_transmitData_writeMultipleRegisters(void)
{
    rtu_modbusTxBuffer[0] = rtu_modbusRxBuffer[0];
    rtu_modbusTxBuffer[1] = rtu_modbusRxBuffer[1];
    rtu_modbusTxBuffer[2] = rtu_modbusRxBuffer[2];
    rtu_modbusTxBuffer[3] = rtu_modbusRxBuffer[3];
    rtu_modbusTxBuffer[4] = rtu_modbusRxBuffer[4];
    rtu_modbusTxBuffer[5] = rtu_modbusRxBuffer[5];
    rtu_crcCalculation(rtu_modbusRxBuffer, 6);
    rtu_modbusTxBuffer[6] = rtuCRC.calculated_H;
    rtu_modbusTxBuffer[7] = rtuCRC.calculated_L;
    HAL_UART_Transmit_IT(&huart3, rtu_modbusTxBuffer, 8);
}

/**
  * @brief  This function performs modbus RTU response to Modbus Master's request
        according to appropriate slave ID, function code, data adress and 
        data length.
  * @note   DMA function is platform specific function. It should be changed 
            in other platforms.
  * @param  none
  * @retval None
  */
void rtu_transmitData_writeSingleRegister(void)
{
    rtu_modbusTxBuffer[0] = rtu_modbusRxBuffer[0];
    rtu_modbusTxBuffer[1] = rtu_modbusRxBuffer[1];
    rtu_modbusTxBuffer[2] = rtu_modbusRxBuffer[2];
    rtu_modbusTxBuffer[3] = rtu_modbusRxBuffer[3];
    rtu_modbusTxBuffer[4] = rtu_modbusRxBuffer[4];
    rtu_modbusTxBuffer[5] = rtu_modbusRxBuffer[5];
    rtu_crcCalculation(rtu_modbusRxBuffer, 6);
    rtu_modbusTxBuffer[6] = rtuCRC.calculated_H;
    rtu_modbusTxBuffer[7] = rtuCRC.calculated_L;
    HAL_UART_Transmit_IT(&huart3, rtu_modbusTxBuffer, 8);
}


/**
  * @brief  This function performs modbus RTU response to Modbus Master's request
  			    according to appropriate slave ID, function code, data adress and 
  			    data length.
  * @note   DMA function is platform specific function. It should be changed 
            in other platforms.
  * @param  none
  * @retval None
  */

void rtu_transmitData_readHoldingRegister(void)
{
    rtu_crcCalculation(rtu_modbusTxBuffer, rtu_txBufferIndex);
    rtu_modbusTxBuffer[rtu_txBufferIndex++] = rtuCRC.calculated_H;
    rtu_modbusTxBuffer[rtu_txBufferIndex++] = rtuCRC.calculated_L;
    rtu_modbusTxLen = rtu_txBufferIndex;
    HAL_UART_Transmit_IT(&huart3, rtu_modbusTxBuffer, rtu_txBufferIndex);
}



/**
  * @brief  This function prepares all calculated data in device for modbus
  			    response.
  * @note   All data is prepared when the data send over RTU. 
            Be careful that when 32 bit data is sent, rtu_modbusRegAdress is 
            increased by two, when 16 bit data is sent, rtu_modbusRegAdress is 
            increased by one.
  * @param  none
  * @retval None
  */




void rtu_Feeder1DataPrep(void){//jj alternate imp for modbus
	
	uint8_t i=0,inc=0;
	
	
	
	for(i=0;i<rtu_modbusDataLen;i+=2){//jj inc2 @ float data
	
	if (rtu_modbusRegAdress == (READ_IN_CH1+i)){
		
	rtu_modbusTxBuffer[rtu_txBufferIndex++] = *(readHoldingMap.buffer[inc]+3);
  rtu_modbusTxBuffer[rtu_txBufferIndex++] = *(readHoldingMap.buffer[inc]+2);
	rtu_modbusTxBuffer[rtu_txBufferIndex++] = *(readHoldingMap.buffer[inc]+1);	
	rtu_modbusTxBuffer[rtu_txBufferIndex++] = *(readHoldingMap.buffer[inc++]);
		
	rtu_modbusRegAdress += 2;
  if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;	
	
	}
	

	}
	
	rtu_transmitData_readHoldingRegister();

}

void rtu_getFeeder1_writeSingleRegister(void)
{
	  #if 0
    if (rtu_modbusRegAdress == WRITE_OUT_CH1)
    {
      outputStatus.CH1 =  (uint32_t) (rtu_modbusRxBuffer[4]) << 8;
      outputStatus.CH1 |= (uint32_t)(rtu_modbusRxBuffer[5]);
    }
		#endif
	
		rtu_transmitData_writeSingleRegister();
}

void rtu_writeSingleRegister(void)
{
	  if(rtu_selectedSlaveID == rtu_deviceSlaveID[0]) rtu_getFeeder1_writeSingleRegister();
}




void updateModbusConfig(){//cau
	
	//adress
	
	rtu_deviceSlaveID[0]=flash.data.modbusAddress;
	
  //baud rate section
	
	switch(flash.data.configBit.commBaudRate){
		
		case 0	:huart3.Init.BaudRate = 4800;break;
		case 1	:huart3.Init.BaudRate = 9600;break;
		case 2	:huart3.Init.BaudRate = 19200;break;
		case 3	:huart3.Init.BaudRate = 38400;break;
		case 4	:huart3.Init.BaudRate = 57600;break;
		default	:huart3.Init.BaudRate = 19200;break;
		
	}
	
	
	switch(flash.data.configBit.commMode){ //cau
	
		case 0: huart3.Init.Parity = UART_PARITY_NONE ; 
						huart3.Init.StopBits = UART_STOPBITS_2  ;break;
		
		case 1: huart3.Init.Parity = UART_PARITY_EVEN ; 
						huart3.Init.StopBits = UART_STOPBITS_1;break;
		
		case 2: huart3.Init.Parity = UART_PARITY_ODD ; 
						huart3.Init.StopBits = UART_STOPBITS_1  ;break;
		
		case 3: huart3.Init.Parity = UART_PARITY_NONE ; 
						huart3.Init.StopBits = UART_STOPBITS_1  ;break;
		
		default: huart3.Init.Parity = UART_PARITY_NONE ; 
						 huart3.Init.StopBits = UART_STOPBITS_2  ;break;
		
	}
	

}
