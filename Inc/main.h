/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define BTN1_Pin GPIO_PIN_13
#define BTN1_GPIO_Port GPIOC
#define BTN2_Pin GPIO_PIN_0
#define BTN2_GPIO_Port GPIOC
#define BTN3_Pin GPIO_PIN_1
#define BTN3_GPIO_Port GPIOC
#define BTN4_Pin GPIO_PIN_2
#define BTN4_GPIO_Port GPIOC
#define BTN5_Pin GPIO_PIN_3
#define BTN5_GPIO_Port GPIOC
#define SPI_CS2_Pin GPIO_PIN_3
#define SPI_CS2_GPIO_Port GPIOA
#define SPI_CS1_Pin GPIO_PIN_4
#define SPI_CS1_GPIO_Port GPIOA
#define SPI_SCK_Pin GPIO_PIN_5
#define SPI_SCK_GPIO_Port GPIOA
#define SPI_MISO_Pin GPIO_PIN_6
#define SPI_MISO_GPIO_Port GPIOA
#define SPI_MOSI_Pin GPIO_PIN_7
#define SPI_MOSI_GPIO_Port GPIOA
#define Vcn_Pin GPIO_PIN_5
#define Vcn_GPIO_Port GPIOC
#define Van_Pin GPIO_PIN_0
#define Van_GPIO_Port GPIOB
#define Vbn_Pin GPIO_PIN_1
#define Vbn_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_8
#define LED1_GPIO_Port GPIOA
#define UART_TX_Pin GPIO_PIN_9
#define UART_TX_GPIO_Port GPIOA
#define UART_RX_Pin GPIO_PIN_10
#define UART_RX_GPIO_Port GPIOA
#define BACKLIGHT_C_Pin GPIO_PIN_11
#define BACKLIGHT_C_GPIO_Port GPIOA
#define BACKLIGHT_S_Pin GPIO_PIN_12
#define BACKLIGHT_S_GPIO_Port GPIOA
#define JTMS_SWDIO_Pin GPIO_PIN_13
#define JTMS_SWDIO_GPIO_Port GPIOA
#define MODBUS_DE_Pin GPIO_PIN_6
#define MODBUS_DE_GPIO_Port GPIOF
#define MODBUS_TE_Pin GPIO_PIN_7
#define MODBUS_TE_GPIO_Port GPIOF
#define JTCK_SWCLK_Pin GPIO_PIN_14
#define JTCK_SWCLK_GPIO_Port GPIOA
#define LCD_SPI_CS_JTDI_Pin GPIO_PIN_15
#define LCD_SPI_CS_JTDI_GPIO_Port GPIOA
#define LCD_SPI_SCK_Pin GPIO_PIN_10
#define LCD_SPI_SCK_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_11
#define LCD_RST_GPIO_Port GPIOC
#define LCD_SPI_MOSI_Pin GPIO_PIN_12
#define LCD_SPI_MOSI_GPIO_Port GPIOC
#define LCD_A0_Pin GPIO_PIN_2
#define LCD_A0_GPIO_Port GPIOD
#define RELAY_OUTPUT_Pin GPIO_PIN_4
#define RELAY_OUTPUT_GPIO_Port GPIOB
#define RELAY_INPUT_Pin GPIO_PIN_5
#define RELAY_INPUT_GPIO_Port GPIOB
#define MODBUS_TX_Pin GPIO_PIN_8
#define MODBUS_TX_GPIO_Port GPIOB
#define MODBUS_RX_Pin GPIO_PIN_9
#define MODBUS_RX_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
 #define USE_FULL_ASSERT    1U 

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
