
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "sdadc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

#include "menu_definitions.h"
#include "lcd_definitions.h"
#include "flash_api.h"
#include "Modbus_RTU_Slave.h"
#include "phaseCompensation.h"
#include "Modbus_Map.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
	uint16_t mp_counter=0;
	uint16_t adc_start=0;
	
	extern uint8_t calibration_completed;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

/* Private function prototypes -----------------------------------------------*/
void init_conversion(void);
void init_LCD(void);
void init_backlight(void);
void init_flashBackRead(void);
void write_lcd(void);
void font_transfer(void);
void font_transfer2(void);

void DISPLAY_MENU(void);
void offline_calculations(void);
enum input  pushButtonHandling(void);

extern uint16_t center_leds;
extern uint16_t side_leds;
extern uint8_t flow_completed;

uint16_t refresh_counter=0;

float dummy_lag=0;

uint8_t dummy_send=4;

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

//comm side entries---start

uint8_t RX_Buffer[100], ReceiveData, ReceiveData2 , RX_Index = 0;
unsigned char rtu_modbusRxBuffer[RX_BUFFER_LIMIT];
extern uint8_t recComp;

uint16_t rtu_ModbusRxIndex = 0;

uint16_t recTimeOut=0, recFlag, transmitComp=0,success = 0;

uint8_t testData[10] = {0,1,2,3,4,5,6,7,8,9};
uint8_t rtuWriteTimerFlag = 0;
extern uint32_t rtuWriteTimerCnt;
extern uint32_t rtu_deviceSlaveID[10];

extern uint8_t rtuMasterSlaveID;
extern uint32_t comErrorCounter;
uint32_t fckcnt = 0;
uint8_t comErrorFlag = 0;
extern uint32_t commErrorTimeOut;
extern uint8_t masterModeOp;
uint32_t uart3_sentinel=0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	

		
	  if (huart->Instance == USART3)	
		{
		HAL_UART_Receive_IT(&huart3,&ReceiveData, 1);	
		rtu_modbusRxBuffer[rtu_ModbusRxIndex++] = ReceiveData;
    recTimeOut = 0;
    recFlag = 1;
	  transmitComp = 0;
			
		uart3_sentinel=0;	
			
		}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

		
    if (huart->Instance == USART3)  
    {

			transmitComp = 1;
    }
}


//comm side entries---end

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  //MX_RTC_Init();
  MX_SDADC1_Init();
  MX_SDADC2_Init();
  MX_SDADC3_Init();
  //MX_SPI1_Init();
  MX_SPI3_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  //MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM19_Init();
  /* USER CODE BEGIN 2 */
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	

	
	flashRead();
	flashReadRec();
	init_flashBackRead();
	
	pLagDef(0.6352f,10000,&pc_b1, &pc_b2);   // applied to voltage, //cau fs is wrong
	pLagDef(0.0f,10000,&pc_b12,&pc_b22); // applied to voltage //cau	
	
	init_conversion();
	init_LCD();
	init_backlight();
	init_Menu();
	init_Map();
	
	
	//rtu_transmitDisable_receiveEnable(); //cau auto de
  HAL_UART_Receive_IT(&huart3,&ReceiveData, 1);	//activate UART receive interrupt every time
	rtu_deviceSlaveID[0] = 1; //cau

	

  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		
		mp_counter++;
		
		
		//HAL_Delay(1); //cau
		
		offline_calculations();
		
		pressed_button=pushButtonHandling();		
			
	  if(pressed_button!=invalid){
			
	  current_menu=SELECT_MENU(current_menu,pressed_button);	
			
	  }
		

		DISPLAY_MENU();

		
		if(refresh_counter>2500){
			
		
		write_lcd();
			
			
		refresh_counter=0;
			
		}
		
		
		//comm side start
		
		if(recComp == 1 && recFlag == 1) 
		{
    rtu_ModbusFrameProcessing();
    rtu_ModbusRxIndex = 0;
    recComp = 0;
    recFlag = 0;
		}
		
		
		
		
		if(comErrorFlag == 1) fckcnt++;
		if(commErrorTimeOut >= 200) fckcnt++;
		
		//comm side end
		
		
		
		
		

		

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure LSE Drive Capability 
    */
  HAL_PWR_EnableBkUpAccess();

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC1
                              |RCC_PERIPHCLK_SDADC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.SdadcClockSelection = RCC_SDADCSYSCLK_DIV12;
  PeriphClkInit.Adc1ClockSelection = RCC_ADC1PCLK2_DIV2;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_PWREx_EnableSDADC(PWR_SDADC_ANALOG1);

  HAL_PWREx_EnableSDADC(PWR_SDADC_ANALOG2);

  HAL_PWREx_EnableSDADC(PWR_SDADC_ANALOG3);

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
