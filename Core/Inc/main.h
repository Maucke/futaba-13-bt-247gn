/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define SPI1_SCS_Pin GPIO_PIN_4
#define SPI1_SCS_GPIO_Port GPIOA
#define SPI1_SCS_EXTI_IRQn EXTI4_IRQn
#define HV2_BLANK_Pin GPIO_PIN_13
#define HV2_BLANK_GPIO_Port GPIOB
#define HV2_LOAD_Pin GPIO_PIN_14
#define HV2_LOAD_GPIO_Port GPIOB
#define HV2_CLK_Pin GPIO_PIN_15
#define HV2_CLK_GPIO_Port GPIOB
#define HV2_DIN_Pin GPIO_PIN_8
#define HV2_DIN_GPIO_Port GPIOA
#define HV_DIN4_Pin GPIO_PIN_15
#define HV_DIN4_GPIO_Port GPIOA
#define HV_DIN3_Pin GPIO_PIN_3
#define HV_DIN3_GPIO_Port GPIOB
#define HV_DIN2_Pin GPIO_PIN_4
#define HV_DIN2_GPIO_Port GPIOB
#define HV_DIN1_Pin GPIO_PIN_5
#define HV_DIN1_GPIO_Port GPIOB
#define HV_LE_Pin GPIO_PIN_6
#define HV_LE_GPIO_Port GPIOB
#define HV_CLK_Pin GPIO_PIN_7
#define HV_CLK_GPIO_Port GPIOB
#define HV_POL_Pin GPIO_PIN_8
#define HV_POL_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
