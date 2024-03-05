/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define DEFAULT_ANGLE 90
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

uint8_t angle;
uint8_t angle_def;
uint8_t mode = 0;
uint32_t last_button_press = 0; // Zmienna przechowująca czas ostatniego naciśnięcia przycisku
uint8_t flag = 1; // flaga do jednorazowego odpalenia mode==2, bo nie chcialo mi sie do timera juz tego wkladac tylko do petli while dalem funkcje "czlapania"

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include "pca9685.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim2) {
	  if (mode==0) {
		  angle_def=0;
//		  Zakladam, ze na poczatku po uruchomieniu zasilania jest sytuacja dla mode=1 - czyli robot sobie lezy
		  if (angle<=45)
		  {
//		  PCA9685_SetServoAngle(0, DEFAULT_ANGLE);	// Serwa, ktorych puki co nie uzywamy (s0,s3,s6,s9)
		  PCA9685_SetServoAngle(3, DEFAULT_ANGLE);	// Bo skupiamy sie na sterowaniu nogami w 2D
		  PCA9685_SetServoAngle(6, DEFAULT_ANGLE);
//		  PCA9685_SetServoAngle(9, DEFAULT_ANGLE); 	// WYJATEK: przy bazowaniu s0 i s9 uzywam, zeby robot mniej miejsca zajmowal w pudelku
		  PCA9685_SetServoAngle(0, 0+angle*2);
		  PCA9685_SetServoAngle(9, 180-angle*2);
		  PCA9685_SetServoAngle(1, angle*2);
		  PCA9685_SetServoAngle(2, 67.5+angle*0.5);
		  if (angle<=30) {PCA9685_SetServoAngle(4, 120-angle);} // rozne wartosci przez niesymetrycznosc od strony sprzetu
		  if (angle<=37) {PCA9685_SetServoAngle(7, 53+angle);}	// po prostu serwa s4 i s7 troszeczke innych kątów wymagały do zrobienia tego samego

		  PCA9685_SetServoAngle(5, 157.5-angle*1.5);
		  PCA9685_SetServoAngle(8, 22.5+angle*1.5);

		  PCA9685_SetServoAngle(10, 180-angle*2);
		  PCA9685_SetServoAngle(11, 112.5-angle*0.5);
		  angle++;
		  }
	  }
	  if (mode==1)
	  {
		  angle=0; // zerowanie potrzebne po to, aby jeszcze raz ruch wykonac przy kolejnych przelaczaniach trybow
		  if (angle_def<=45){
			  PCA9685_SetServoAngle(0, DEFAULT_ANGLE-angle_def*2);
			  PCA9685_SetServoAngle(9, DEFAULT_ANGLE+angle_def*2);


			  PCA9685_SetServoAngle(1, DEFAULT_ANGLE-angle_def*2);			//end_angle=0
			  PCA9685_SetServoAngle(2, DEFAULT_ANGLE-angle_def*0.5);		//end_angle=67.5

			  if (angle_def<=30) {PCA9685_SetServoAngle(4, DEFAULT_ANGLE+angle_def);}	//end_angle=120
			  if (angle_def<=37) {PCA9685_SetServoAngle(7, DEFAULT_ANGLE-angle_def);}	//end_angle=53
			  PCA9685_SetServoAngle(5, DEFAULT_ANGLE+angle_def*1.5);		//end_angle=157,5
			  PCA9685_SetServoAngle(8, DEFAULT_ANGLE-angle_def*1.5);		//end_angle=22,5

			  PCA9685_SetServoAngle(10, DEFAULT_ANGLE+angle_def*2);			//end_angle=180
			  PCA9685_SetServoAngle(11, DEFAULT_ANGLE+angle_def*0.5);		//end_angle=112.5
			  angle_def++;
		  }
	}
  }
}
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

void SystemClock_Config(void);
HAL_TIM_Base_Start_IT(&htim2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//		(D).....................(A)
//		 |.......................|
//		(s11)...................(s2)
//		|.........................|
//		(s10)--(s9)______(s0)--(s1)
//			  |..............|
//			  |..............|
//			  |.....STM......|
//			  |..............|
//			  |.....PCA......|
//		(s7 )--(s6)______(s3)--(s4)
//		|.........................|
//		(s8)...................(s5)
//		 |.......................|
//		(C).....................(B)
////////////////////////////////////////////////////////////////////////////////////////////////////////

PCA9685_Init(&hi2c1);
//PCA9685_SetServoAngle(0, DEFAULT_ANGLE);	// Serwa, ktorych puki co nie uzywamy (s0,s3,s6,s9)
PCA9685_SetServoAngle(3, DEFAULT_ANGLE);	// Bo skupiamy sie na sterowaniu nogami w 2D
PCA9685_SetServoAngle(6, DEFAULT_ANGLE);	// Serwa tylnie s0 i s9 uzywam tylko do skladania robota
//PCA9685_SetServoAngle(9, DEFAULT_ANGLE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  // Odczyt stanu przycisku - tutaj uzylem prostego sposobu na zminimalizowanie tzw. Debouncingu (drgań styków w przyciskach)
	  // 						  ale i tak czasem po 3 razy "mode" mi inkrementuje
	    if (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_RESET)
	    {
	      // Sprawdzenie, czy przycisk był wcześniej wciśnięty i czy od ostatniego wciśnięcia minął czas debouncingu
	      if ((HAL_GetTick() - last_button_press >= 20) )
	      {
	        last_button_press = HAL_GetTick(); // Zaktualizuj czas ostatniego wcisniecia
	        mode++;

	        if (mode==2) {
				flag=1;// to na szybko flaga do ponownego korzystania z chodzenia w petli while, sredni sposob ale dziala xd
			}
	        if (mode > 2) {
				mode = 0;
			}
	      }
	    }
 /*
  * generalnie jak w timerach robilem, to do timera tez pasuje to dodac,
  * na szybko to robilem to jest jak jest, z reguly nie powinno sie dodawac do timerow
  * funkcji blokujacych typu HAL_DELAY i chyba petle for, ale to tez mozna obserwowac jak
  * sie uklad zachowuje
 */
	    if (mode==2 && flag) {
		PCA9685_SetServoAngle(0, DEFAULT_ANGLE);	// to pasuje dodac, zeby z pozycji lezacej nie kopal
		PCA9685_SetServoAngle(9, DEFAULT_ANGLE);
		for (uint8_t var = 0; var < 5; ++var) {
	    	for (uint8_t Angle = 90; Angle < 125; Angle++) {
	    		  if (Angle<=90+15) {
	    			  PCA9685_SetServoAngle(4, Angle);
	    		  }if (Angle<=90+34) {
	    			  PCA9685_SetServoAngle(5, Angle);
	    		  }
	    	}
	    	for (uint8_t Angle = 90; Angle > 55; Angle--) {
	    		  if (Angle>=90-24) {
	    			  PCA9685_SetServoAngle(10, Angle);
	    		  }if (Angle>=90-34) {
	    			  PCA9685_SetServoAngle(11, Angle);
	    		  }
	    	}
	    	HAL_Delay(100);

	    	for (uint8_t Angle = 125; Angle > 90; Angle--) {
	    		  if (Angle<=90+24) {
	    			  PCA9685_SetServoAngle(4, Angle);
	    		  }if (Angle<=90+34) {
	    			  PCA9685_SetServoAngle(5, Angle);
	    		  }
	    	}
	    	for (uint8_t Angle = 55; Angle < 90; Angle++) {
	    		  if (Angle>=90-24) {
	    			  PCA9685_SetServoAngle(10, Angle);
	    		  }if (Angle>=90-34) {
	    			  PCA9685_SetServoAngle(11, Angle);
	    		  }
	    	}
	    	HAL_Delay(100);

	    	for (uint8_t Angle = 90; Angle < 125; Angle++) {
	    		  if (Angle<=90+24) {
	    			  PCA9685_SetServoAngle(1, Angle);
	    		  }if (Angle<=90+34) {
	    			  PCA9685_SetServoAngle(2, Angle);
	    		  }
	    	}
	    	for (uint8_t Angle = 90; Angle > 55; Angle--) {
	    		  if (Angle>=90-15) {
	    			  PCA9685_SetServoAngle(7, Angle);
	    		  }if (Angle>=90-34) {
	    			  PCA9685_SetServoAngle(8, Angle);
	    		  }
	    	}
	    	HAL_Delay(100);

	    	for (uint8_t Angle = 125; Angle > 90; Angle--) {
	    		  if (Angle<=90+24) {
	    			  PCA9685_SetServoAngle(1, Angle);
	    		  }if (Angle<=90+34) {
	    			  PCA9685_SetServoAngle(2, Angle);
	    		  }
	    	}
	    	for (uint8_t Angle = 55; Angle < 90; Angle++) {
	    		  if (Angle>=90-24) {
	    			  PCA9685_SetServoAngle(7, Angle);
	    		  }if (Angle>=90-34) {
	    			  PCA9685_SetServoAngle(8, Angle);
	    		  }
	    	}
	    	HAL_Delay(100);

	    	}flag=0;
		}

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  htim2.Init.Prescaler = 8399;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_BUTTON_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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

#ifdef  USE_FULL_ASSERT
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
