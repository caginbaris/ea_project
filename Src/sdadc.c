/**
  ******************************************************************************
  * File Name          : SDADC.c
  * Description        : This file provides code for the configuration
  *                      of the SDADC instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "sdadc.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SDADC_HandleTypeDef hsdadc1;
SDADC_HandleTypeDef hsdadc2;
SDADC_HandleTypeDef hsdadc3;

/* SDADC1 init function */
void MX_SDADC1_Init(void)
{
  SDADC_ConfParamTypeDef ConfParamStruct;

    /**Configure the SDADC low power mode, fast conversion mode,
    slow clock mode and SDADC1 reference voltage 
    */
  hsdadc1.Instance = SDADC1;
  hsdadc1.Init.IdleLowPowerMode = SDADC_LOWPOWER_NONE;
  hsdadc1.Init.FastConversionMode = SDADC_FAST_CONV_DISABLE;
  hsdadc1.Init.SlowClockMode = SDADC_SLOW_CLOCK_DISABLE;
  hsdadc1.Init.ReferenceVoltage = SDADC_VREF_EXT;
  hsdadc1.InjectedTrigger = SDADC_EXTERNAL_TRIGGER;
  hsdadc1.ExtTriggerEdge = SDADC_EXT_TRIG_RISING_EDGE;
  if (HAL_SDADC_Init(&hsdadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Injected Mode 
    */
  if (HAL_SDADC_SelectInjectedDelay(&hsdadc1, SDADC_INJECTED_DELAY_NONE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_SDADC_SelectInjectedExtTrigger(&hsdadc1, SDADC_EXT_TRIG_TIM19_CC2, SDADC_EXT_TRIG_RISING_EDGE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_SDADC_SelectInjectedTrigger(&hsdadc1, SDADC_EXTERNAL_TRIGGER) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_SDADC_InjectedConfigChannel(&hsdadc1, SDADC_CHANNEL_4, SDADC_CONTINUOUS_CONV_OFF) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Set parameters for SDADC configuration 0 Register 
    */
  ConfParamStruct.InputMode = SDADC_INPUT_MODE_SE_ZERO_REFERENCE;
  ConfParamStruct.Gain = SDADC_GAIN_1;
  ConfParamStruct.CommonMode = SDADC_COMMON_MODE_VSSA;
  ConfParamStruct.Offset = 0;
  if (HAL_SDADC_PrepareChannelConfig(&hsdadc1, SDADC_CONF_INDEX_0, &ConfParamStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Injected Channel 
    */
  if (HAL_SDADC_AssociateChannelConfig(&hsdadc1, SDADC_CHANNEL_4, SDADC_CONF_INDEX_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* SDADC2 init function */
void MX_SDADC2_Init(void)
{
  SDADC_ConfParamTypeDef ConfParamStruct;

    /**Configure the SDADC low power mode, fast conversion mode,
    slow clock mode and SDADC1 reference voltage 
    */
  hsdadc2.Instance = SDADC2;
  hsdadc2.Init.IdleLowPowerMode = SDADC_LOWPOWER_NONE;
  hsdadc2.Init.FastConversionMode = SDADC_FAST_CONV_DISABLE;
  hsdadc2.Init.SlowClockMode = SDADC_SLOW_CLOCK_DISABLE;
  hsdadc2.Init.ReferenceVoltage = SDADC_VREF_EXT;
  hsdadc2.InjectedTrigger = SDADC_SYNCHRONOUS_TRIGGER;
  if (HAL_SDADC_Init(&hsdadc2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Injected Mode 
    */
  if (HAL_SDADC_SelectInjectedDelay(&hsdadc2, SDADC_INJECTED_DELAY_NONE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_SDADC_SelectInjectedTrigger(&hsdadc2, SDADC_SYNCHRONOUS_TRIGGER) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_SDADC_InjectedConfigChannel(&hsdadc2, SDADC_CHANNEL_7, SDADC_CONTINUOUS_CONV_OFF) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Set parameters for SDADC configuration 0 Register 
    */
  ConfParamStruct.InputMode = SDADC_INPUT_MODE_SE_ZERO_REFERENCE;
  ConfParamStruct.Gain = SDADC_GAIN_1;
  ConfParamStruct.CommonMode = SDADC_COMMON_MODE_VSSA;
  ConfParamStruct.Offset = 0;
  if (HAL_SDADC_PrepareChannelConfig(&hsdadc2, SDADC_CONF_INDEX_0, &ConfParamStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Injected Channel 
    */
  if (HAL_SDADC_AssociateChannelConfig(&hsdadc2, SDADC_CHANNEL_7, SDADC_CONF_INDEX_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* SDADC3 init function */
void MX_SDADC3_Init(void)
{
  SDADC_ConfParamTypeDef ConfParamStruct;

    /**Configure the SDADC low power mode, fast conversion mode,
    slow clock mode and SDADC1 reference voltage 
    */
  hsdadc3.Instance = SDADC3;
  hsdadc3.Init.IdleLowPowerMode = SDADC_LOWPOWER_NONE;
  hsdadc3.Init.FastConversionMode = SDADC_FAST_CONV_DISABLE;
  hsdadc3.Init.SlowClockMode = SDADC_SLOW_CLOCK_DISABLE;
  hsdadc3.Init.ReferenceVoltage = SDADC_VREF_EXT;
  hsdadc3.InjectedTrigger = SDADC_SYNCHRONOUS_TRIGGER;
  if (HAL_SDADC_Init(&hsdadc3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Injected Mode 
    */
  if (HAL_SDADC_SelectInjectedDelay(&hsdadc3, SDADC_INJECTED_DELAY_NONE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_SDADC_SelectInjectedTrigger(&hsdadc3, SDADC_SYNCHRONOUS_TRIGGER) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_SDADC_InjectedConfigChannel(&hsdadc3, SDADC_CHANNEL_8, SDADC_CONTINUOUS_CONV_OFF) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Set parameters for SDADC configuration 0 Register 
    */
  ConfParamStruct.InputMode = SDADC_INPUT_MODE_SE_ZERO_REFERENCE;
  ConfParamStruct.Gain = SDADC_GAIN_1;
  ConfParamStruct.CommonMode = SDADC_COMMON_MODE_VSSA;
  ConfParamStruct.Offset = 0;
  if (HAL_SDADC_PrepareChannelConfig(&hsdadc3, SDADC_CONF_INDEX_0, &ConfParamStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Injected Channel 
    */
  if (HAL_SDADC_AssociateChannelConfig(&hsdadc3, SDADC_CHANNEL_8, SDADC_CONF_INDEX_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_SDADC_MspInit(SDADC_HandleTypeDef* sdadcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(sdadcHandle->Instance==SDADC1)
  {
  /* USER CODE BEGIN SDADC1_MspInit 0 */

  /* USER CODE END SDADC1_MspInit 0 */
    /* SDADC1 clock enable */
    __HAL_RCC_SDADC1_CLK_ENABLE();
  
    /**SDADC1 GPIO Configuration    
    PB2     ------> SDADC1_AIN4P 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SDADC1 interrupt Init */
    HAL_NVIC_SetPriority(SDADC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SDADC1_IRQn);
  /* USER CODE BEGIN SDADC1_MspInit 1 */

  /* USER CODE END SDADC1_MspInit 1 */
  }
  else if(sdadcHandle->Instance==SDADC2)
  {
  /* USER CODE BEGIN SDADC2_MspInit 0 */

  /* USER CODE END SDADC2_MspInit 0 */
    /* SDADC2 clock enable */
    __HAL_RCC_SDADC2_CLK_ENABLE();
  
    /**SDADC2 GPIO Configuration    
    PE9     ------> SDADC2_AIN7P 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* SDADC2 interrupt Init */
    HAL_NVIC_SetPriority(SDADC2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SDADC2_IRQn);
  /* USER CODE BEGIN SDADC2_MspInit 1 */

  /* USER CODE END SDADC2_MspInit 1 */
  }
  else if(sdadcHandle->Instance==SDADC3)
  {
  /* USER CODE BEGIN SDADC3_MspInit 0 */

  /* USER CODE END SDADC3_MspInit 0 */
    /* SDADC3 clock enable */
    __HAL_RCC_SDADC3_CLK_ENABLE();
  
    /**SDADC3 GPIO Configuration    
    PB14     ------> SDADC3_AIN8P 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SDADC3 interrupt Init */
    HAL_NVIC_SetPriority(SDADC3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SDADC3_IRQn);
  /* USER CODE BEGIN SDADC3_MspInit 1 */

  /* USER CODE END SDADC3_MspInit 1 */
  }
}

void HAL_SDADC_MspDeInit(SDADC_HandleTypeDef* sdadcHandle)
{

  if(sdadcHandle->Instance==SDADC1)
  {
  /* USER CODE BEGIN SDADC1_MspDeInit 0 */

  /* USER CODE END SDADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDADC1_CLK_DISABLE();
  
    /**SDADC1 GPIO Configuration    
    PB2     ------> SDADC1_AIN4P 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

    /* SDADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SDADC1_IRQn);
  /* USER CODE BEGIN SDADC1_MspDeInit 1 */

  /* USER CODE END SDADC1_MspDeInit 1 */
  }
  else if(sdadcHandle->Instance==SDADC2)
  {
  /* USER CODE BEGIN SDADC2_MspDeInit 0 */

  /* USER CODE END SDADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDADC2_CLK_DISABLE();
  
    /**SDADC2 GPIO Configuration    
    PE9     ------> SDADC2_AIN7P 
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_9);

    /* SDADC2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SDADC2_IRQn);
  /* USER CODE BEGIN SDADC2_MspDeInit 1 */

  /* USER CODE END SDADC2_MspDeInit 1 */
  }
  else if(sdadcHandle->Instance==SDADC3)
  {
  /* USER CODE BEGIN SDADC3_MspDeInit 0 */

  /* USER CODE END SDADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDADC3_CLK_DISABLE();
  
    /**SDADC3 GPIO Configuration    
    PB14     ------> SDADC3_AIN8P 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14);

    /* SDADC3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SDADC3_IRQn);
  /* USER CODE BEGIN SDADC3_MspDeInit 1 */

  /* USER CODE END SDADC3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
