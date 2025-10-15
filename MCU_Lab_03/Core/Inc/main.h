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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "timer.h"
#include "led_display.h"
#include "input_processing.h"
#include "input_reading.h"
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
#define LED_RED_Pin GPIO_PIN_1
#define LED_RED_GPIO_Port GPIOA
#define BTN1_Pin GPIO_PIN_2
#define BTN1_GPIO_Port GPIOA
#define BTN2_Pin GPIO_PIN_3
#define BTN2_GPIO_Port GPIOA
#define BTN3_Pin GPIO_PIN_4
#define BTN3_GPIO_Port GPIOA
#define SEG0_0_Pin GPIO_PIN_5
#define SEG0_0_GPIO_Port GPIOA
#define SEG0_1_Pin GPIO_PIN_6
#define SEG0_1_GPIO_Port GPIOA
#define SEG0_2_Pin GPIO_PIN_7
#define SEG0_2_GPIO_Port GPIOA
#define SEG2_3_Pin GPIO_PIN_0
#define SEG2_3_GPIO_Port GPIOB
#define SEG3_0_Pin GPIO_PIN_1
#define SEG3_0_GPIO_Port GPIOB
#define SEG3_1_Pin GPIO_PIN_2
#define SEG3_1_GPIO_Port GPIOB
#define RED_EW_Pin GPIO_PIN_10
#define RED_EW_GPIO_Port GPIOB
#define YELLOW_EW_Pin GPIO_PIN_11
#define YELLOW_EW_GPIO_Port GPIOB
#define GREEN_EW_Pin GPIO_PIN_12
#define GREEN_EW_GPIO_Port GPIOB
#define RED_NS_Pin GPIO_PIN_13
#define RED_NS_GPIO_Port GPIOB
#define YELLOW_NS_Pin GPIO_PIN_14
#define YELLOW_NS_GPIO_Port GPIOB
#define GREEN_NS_Pin GPIO_PIN_15
#define GREEN_NS_GPIO_Port GPIOB
#define SEG0_3_Pin GPIO_PIN_8
#define SEG0_3_GPIO_Port GPIOA
#define SEG1_0_Pin GPIO_PIN_9
#define SEG1_0_GPIO_Port GPIOA
#define SEG1_1_Pin GPIO_PIN_10
#define SEG1_1_GPIO_Port GPIOA
#define SEG1_2_Pin GPIO_PIN_11
#define SEG1_2_GPIO_Port GPIOA
#define SEG1_3_Pin GPIO_PIN_12
#define SEG1_3_GPIO_Port GPIOA
#define SEG2_0_Pin GPIO_PIN_13
#define SEG2_0_GPIO_Port GPIOA
#define SEG2_1_Pin GPIO_PIN_14
#define SEG2_1_GPIO_Port GPIOA
#define SEG2_2_Pin GPIO_PIN_15
#define SEG2_2_GPIO_Port GPIOA
#define SEG3_2_Pin GPIO_PIN_3
#define SEG3_2_GPIO_Port GPIOB
#define SEG3_3_Pin GPIO_PIN_4
#define SEG3_3_GPIO_Port GPIOB
#define SEG4_0_Pin GPIO_PIN_5
#define SEG4_0_GPIO_Port GPIOB
#define SEG4_1_Pin GPIO_PIN_6
#define SEG4_1_GPIO_Port GPIOB
#define SEG4_2_Pin GPIO_PIN_7
#define SEG4_2_GPIO_Port GPIOB
#define SEG4_3_Pin GPIO_PIN_8
#define SEG4_3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
