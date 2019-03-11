#include "menu_definitions.h"
#include "measurement_definitions.h"
#include "flashUpdate.h"
#include "phaseCompensation.h"
#include "stm32f3xx_hal.h"


uint16_t comm_baud=19200;

extern uint32_t rtu_deviceSlaveID[10];
extern UART_HandleTypeDef huart3;

void UART3_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = comm_baud;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_ENABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
  huart3.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  huart3.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
	
	__disable_irq();
	
  if (HAL_RS485Ex_Init(&huart3, UART_DE_POLARITY_HIGH, 0, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	
	__enable_irq();

}



void flashUpdate(void){
	
	TR.VT=(flash.data.vt_seconder!=0)?(flash.data.vt_primer/flash.data.vt_seconder):(TR.VT);
	TR.CT=(flash.data.ct_seconder!=0)?(flash.data.ct_primer/flash.data.ct_seconder):(TR.CT);
	TR.PT=TR.VT*TR.CT;
	
	
	rtu_deviceSlaveID[0] = flash.data.modbusAddress; //cau
	
	switch(flash.data.configBit.commBaudRate){
	
		case 0:comm_baud=4800;break;
		case 1:comm_baud=9600;break;
		case 2:comm_baud=19200;break;
		case 3:comm_baud=38400;break;
		case 4:comm_baud=57600;break;
		
		default:comm_baud=19200;break;
	}
	
	
		switch(flash.data.configBit.commMode){
	

		case 0:    huart3.Init.StopBits = UART_STOPBITS_2;
							 huart3.Init.Parity = UART_PARITY_NONE;			break;

		case 1:    huart3.Init.StopBits = UART_STOPBITS_1;
							 huart3.Init.Parity = UART_PARITY_EVEN;			break;

		case 2:    huart3.Init.StopBits = UART_STOPBITS_1;
							 huart3.Init.Parity = UART_PARITY_ODD;			break;

		case 3:    huart3.Init.StopBits = UART_STOPBITS_1;
							 huart3.Init.Parity = UART_PARITY_NONE;			break;					
			
		default:   huart3.Init.StopBits = UART_STOPBITS_2;
							 huart3.Init.Parity = UART_PARITY_NONE;			break;
			
	}
	
	UART3_Init();
	
	pLagDef(flash.data.ct_phase_shift*0.1f,10000,&pc_b12,&pc_b22); // applied to voltage 		
	
}


