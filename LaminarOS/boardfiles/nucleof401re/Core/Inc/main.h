/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
void losInit(void);
void losKernelStart(void);
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define GPIO_IN1_Pin GPIO_PIN_0
#define GPIO_IN1_GPIO_Port GPIOC
#define RSSI_Pin GPIO_PIN_1
#define RSSI_GPIO_Port GPIOC
#define SPI2_MISO_Pin GPIO_PIN_2
#define SPI2_MISO_GPIO_Port GPIOC
#define SPI2_MOSI_Pin GPIO_PIN_3
#define SPI2_MOSI_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_0
#define BUZZER_GPIO_Port GPIOA
#define PPM2_Pin GPIO_PIN_1
#define PPM2_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define SPI3_NSS_Pin GPIO_PIN_4
#define SPI3_NSS_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define ADC_IN6_Pin GPIO_PIN_6
#define ADC_IN6_GPIO_Port GPIOA
#define ADC_IN7_Pin GPIO_PIN_7
#define ADC_IN7_GPIO_Port GPIOA
#define GPIO_OUT1_Pin GPIO_PIN_4
#define GPIO_OUT1_GPIO_Port GPIOC
#define GPIO_OUT2_Pin GPIO_PIN_5
#define GPIO_OUT2_GPIO_Port GPIOC
#define ADC_IN8_Pin GPIO_PIN_0
#define ADC_IN8_GPIO_Port GPIOB
#define ADC_IN9_Pin GPIO_PIN_1
#define ADC_IN9_GPIO_Port GPIOB
#define GPIO_IN2_Pin GPIO_PIN_2
#define GPIO_IN2_GPIO_Port GPIOB
#define SPI2_SCK_Pin GPIO_PIN_10
#define SPI2_SCK_GPIO_Port GPIOB
#define SPI2_NSS_Pin GPIO_PIN_12
#define SPI2_NSS_GPIO_Port GPIOB
#define USART6_TX_Pin GPIO_PIN_6
#define USART6_TX_GPIO_Port GPIOC
#define PWM2_Pin GPIO_PIN_7
#define PWM2_GPIO_Port GPIOC
#define PWM3_Pin GPIO_PIN_8
#define PWM3_GPIO_Port GPIOC
#define PWM4_Pin GPIO_PIN_9
#define PWM4_GPIO_Port GPIOC
#define DSHOT4_Pin GPIO_PIN_8
#define DSHOT4_GPIO_Port GPIOA
#define DSHOT3_Pin GPIO_PIN_9
#define DSHOT3_GPIO_Port GPIOA
#define DSHOT2_Pin GPIO_PIN_10
#define DSHOT2_GPIO_Port GPIOA
#define DSHOT1_Pin GPIO_PIN_11
#define DSHOT1_GPIO_Port GPIOA
#define USART6_RX_Pin GPIO_PIN_12
#define USART6_RX_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define PPM_Pin GPIO_PIN_15
#define PPM_GPIO_Port GPIOA
#define SPI3_SCK_Pin GPIO_PIN_10
#define SPI3_SCK_GPIO_Port GPIOC
#define SPI3_MISO_Pin GPIO_PIN_11
#define SPI3_MISO_GPIO_Port GPIOC
#define SPI3_MOSI_Pin GPIO_PIN_12
#define SPI3_MOSI_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define PWM1_Pin GPIO_PIN_4
#define PWM1_GPIO_Port GPIOB
#define USART1_TX_Pin GPIO_PIN_6
#define USART1_TX_GPIO_Port GPIOB
#define USART1_RX_Pin GPIO_PIN_7
#define USART1_RX_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
