/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define INIT        0
#define GREEN       1
#define AMBER       2
#define RED_GREEN   3
#define RED_AMBER 4

#define MODE_RED_LONGER   0		//red = green + amber
#define MODE_GREEN_LONGER 1		//green = red + amber

#define MAX_7SEG_LED 4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
int traffic_state = MODE_RED_LONGER;
int status = INIT;
int counter_NS = 0;
int counter_EW = 0;

int red_cnt = 5;
int amber_cnt = 2;
int green_cnt = 3;

int led_index = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void fsm_run();
void display_counter();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);

  setTimer(0, 1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if (isTimerExpired(0) == 1)
	{
		setTimer(0, 1000);
		led_red_blink();
	}

	fsm_run();
	display_counter();
	//you only need to add the fsm function here
	//fsm_for_input_processing();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|SEG0_Pin|SEG1_Pin|SEG2_Pin
                          |SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SEG_EN1_Pin|SEG_EN2_Pin|SEG_EN3_Pin|SEG_EN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RED_EAST_Pin|YELLOW_EAST_Pin|GREEN_EAST_Pin|RED_NORTH_Pin
                          |YELLOW_NORTH_Pin|GREEN_NORTH_Pin|RED_SOUTH_Pin|YELLOW_SOUTH_Pin
                          |GREEN_SOUTH_Pin|RED_WEST_Pin|YELLOW_WEST_Pin|GREEN_WEST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED_RED_Pin SEG_EN1_Pin SEG_EN2_Pin SEG_EN3_Pin
                           SEG_EN4_Pin SEG0_Pin SEG1_Pin SEG2_Pin
                           SEG3_Pin SEG4_Pin SEG5_Pin SEG6_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|SEG_EN1_Pin|SEG_EN2_Pin|SEG_EN3_Pin
                          |SEG_EN4_Pin|SEG0_Pin|SEG1_Pin|SEG2_Pin
                          |SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN1_Pin BTN2_Pin BTN3_Pin */
  GPIO_InitStruct.Pin = BTN1_Pin|BTN2_Pin|BTN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RED_EAST_Pin YELLOW_EAST_Pin GREEN_EAST_Pin RED_NORTH_Pin
                           YELLOW_NORTH_Pin GREEN_NORTH_Pin RED_SOUTH_Pin YELLOW_SOUTH_Pin
                           GREEN_SOUTH_Pin RED_WEST_Pin YELLOW_WEST_Pin GREEN_WEST_Pin */
  GPIO_InitStruct.Pin = RED_EAST_Pin|YELLOW_EAST_Pin|GREEN_EAST_Pin|RED_NORTH_Pin
                          |YELLOW_NORTH_Pin|GREEN_NORTH_Pin|RED_SOUTH_Pin|YELLOW_SOUTH_Pin
                          |GREEN_SOUTH_Pin|RED_WEST_Pin|YELLOW_WEST_Pin|GREEN_WEST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void traffic_time_init()
{
	if (traffic_state == MODE_RED_LONGER)
	{
		red_cnt = red_cnt;
		green_cnt = green_cnt;
		amber_cnt = red_cnt - green_cnt;
	}
	else if (traffic_state == MODE_GREEN_LONGER)
	{
		red_cnt = red_cnt;
		green_cnt = green_cnt;
		amber_cnt = green_cnt - red_cnt;
	}
}
void fsm_run()
{
	if (isTimerExpired(6) == 1)
	{
		setTimer(6, 1000);
		if (counter_NS > 0)
			counter_NS--;
		if (counter_EW > 0)
			counter_EW--;
	}

	switch (status)
	{
	case INIT:
		status = GREEN;
		setTimer(2, (green_cnt * 1000));
		setTimer(1, 100);
		setTimer(6, 1000);

		counter_NS = green_cnt;
		counter_EW = red_cnt;
		display_counter();
		break;

	case GREEN:
		HAL_GPIO_WritePin(GPIOB, RED_NORTH_Pin|RED_SOUTH_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GREEN_NORTH_Pin|GREEN_SOUTH_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOB, YELLOW_WEST_Pin|YELLOW_EAST_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, RED_WEST_Pin|RED_EAST_Pin, GPIO_PIN_RESET);

		if (isTimerExpired(2) == 1)
		{
			status = AMBER;
			setTimer(3, (amber_cnt * 1000));
			counter_NS = amber_cnt;
			counter_EW = amber_cnt; //đồng bộ với NS
		}
		break;

	case AMBER:
		HAL_GPIO_WritePin(GPIOB, GREEN_NORTH_Pin|GREEN_SOUTH_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, YELLOW_NORTH_Pin|YELLOW_SOUTH_Pin, GPIO_PIN_RESET);

		if (isTimerExpired(3) == 1)
		{
			status = RED_GREEN;
			setTimer(4, (green_cnt * 1000));	//cheat
			counter_NS = red_cnt;
			counter_EW = green_cnt;
		}
		break;

	case RED_GREEN:
		HAL_GPIO_WritePin(GPIOB, YELLOW_NORTH_Pin|YELLOW_SOUTH_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, RED_NORTH_Pin|RED_SOUTH_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOB, RED_WEST_Pin|RED_EAST_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GREEN_WEST_Pin|GREEN_EAST_Pin, GPIO_PIN_RESET);

		if (isTimerExpired(4) == 1)
		{
			status = RED_AMBER;
			setTimer(5, (amber_cnt * 1000));
			counter_NS = amber_cnt;		//cheat
			counter_EW = amber_cnt;
		}
		break;

	case RED_AMBER:
		HAL_GPIO_WritePin(GPIOB, GREEN_WEST_Pin|GREEN_EAST_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, YELLOW_WEST_Pin|YELLOW_EAST_Pin, GPIO_PIN_RESET);

		if (isTimerExpired(5) == 1)
		{
			status = GREEN;
			setTimer(2, (green_cnt * 1000));
			counter_NS = green_cnt;
			counter_EW = red_cnt;
		}
		break;

	default:
		break;
	}
}

void display_counter()
{
	if (isTimerExpired(1) == 1)
	{
		setTimer(1, 100);
		switch (led_index)
		{
		case 0:
			update7SEG(0, (counter_NS / 10));
			break;
		case 1:
			update7SEG(1, (counter_NS % 10));
			break;
		case 2:
			update7SEG(2, (counter_EW / 10));
			break;
		case 3:
			update7SEG(3, (counter_EW % 10));
			break;
		}
		led_index++;
		if (led_index > 3)
			led_index = 0;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
