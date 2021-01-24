/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define OUT_LED_PWR_Pin GPIO_PIN_12
#define OUT_LED_PWR_GPIO_Port GPIOD
#define OUT_LED_PROC_Pin GPIO_PIN_13
#define OUT_LED_PROC_GPIO_Port GPIOD
#define OUT_LED_1_Pin GPIO_PIN_14
#define OUT_LED_1_GPIO_Port GPIOD
#define OUT_LED_2_Pin GPIO_PIN_15
#define OUT_LED_2_GPIO_Port GPIOD
#define EXT_IO_EXP_Pin GPIO_PIN_0
#define EXT_IO_EXP_GPIO_Port GPIOD
#define EXT_IO_EXP_EXTI_IRQn EXTI0_IRQn
#define EXT_KEYPAD_Pin GPIO_PIN_1
#define EXT_KEYPAD_GPIO_Port GPIOD
#define EXT_KEYPAD_EXTI_IRQn EXTI1_IRQn
#define EXT_USER_BTN_1_Pin GPIO_PIN_2
#define EXT_USER_BTN_1_GPIO_Port GPIOD
#define EXT_USER_BTN_2_Pin GPIO_PIN_3
#define EXT_USER_BTN_2_GPIO_Port GPIOD
#define EXT_USER_BTN_3_Pin GPIO_PIN_4
#define EXT_USER_BTN_3_GPIO_Port GPIOD
#define EXT_USER_BTN_4_Pin GPIO_PIN_5
#define EXT_USER_BTN_4_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
