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
#define SEG_EN1_Pin GPIO_PIN_5
#define SEG_EN1_GPIO_Port GPIOA
#define SEG_EN2_Pin GPIO_PIN_6
#define SEG_EN2_GPIO_Port GPIOA
#define SEG_EN3_Pin GPIO_PIN_7
#define SEG_EN3_GPIO_Port GPIOA
#define RED_EAST_Pin GPIO_PIN_10
#define RED_EAST_GPIO_Port GPIOB
#define YELLOW_EAST_Pin GPIO_PIN_11
#define YELLOW_EAST_GPIO_Port GPIOB
#define GREEN_EAST_Pin GPIO_PIN_12
#define GREEN_EAST_GPIO_Port GPIOB
#define RED_NORTH_Pin GPIO_PIN_13
#define RED_NORTH_GPIO_Port GPIOB
#define YELLOW_NORTH_Pin GPIO_PIN_14
#define YELLOW_NORTH_GPIO_Port GPIOB
#define GREEN_NORTH_Pin GPIO_PIN_15
#define GREEN_NORTH_GPIO_Port GPIOB
#define SEG_EN4_Pin GPIO_PIN_8
#define SEG_EN4_GPIO_Port GPIOA
#define SEG0_Pin GPIO_PIN_9
#define SEG0_GPIO_Port GPIOA
#define SEG1_Pin GPIO_PIN_10
#define SEG1_GPIO_Port GPIOA
#define SEG2_Pin GPIO_PIN_11
#define SEG2_GPIO_Port GPIOA
#define SEG3_Pin GPIO_PIN_12
#define SEG3_GPIO_Port GPIOA
#define SEG4_Pin GPIO_PIN_13
#define SEG4_GPIO_Port GPIOA
#define SEG5_Pin GPIO_PIN_14
#define SEG5_GPIO_Port GPIOA
#define SEG6_Pin GPIO_PIN_15
#define SEG6_GPIO_Port GPIOA
#define RED_SOUTH_Pin GPIO_PIN_4
#define RED_SOUTH_GPIO_Port GPIOB
#define YELLOW_SOUTH_Pin GPIO_PIN_5
#define YELLOW_SOUTH_GPIO_Port GPIOB
#define GREEN_SOUTH_Pin GPIO_PIN_6
#define GREEN_SOUTH_GPIO_Port GPIOB
#define RED_WEST_Pin GPIO_PIN_7
#define RED_WEST_GPIO_Port GPIOB
#define YELLOW_WEST_Pin GPIO_PIN_8
#define YELLOW_WEST_GPIO_Port GPIOB
#define GREEN_WEST_Pin GPIO_PIN_9
#define GREEN_WEST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
