/* USER CODE BEGIN Header */
/**
  **********
  * @file           : main.c
  * @brief          : Main program body
  **********
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "fonts.h"



#define LED1_PIN GPIO_PIN_7
#define LED1_GPIO_PORT GPIOC
#define LED2_PIN GPIO_PIN_6
#define LED2_GPIO_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_10
#define BUTTON_GPIO_PORT GPIOB



uint32_t reaction_time = 0;
char reaction_time_str[16];  // Buffer

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
TIM_HandleTypeDef htim2;
void SystemClock_Config(void);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  SSD1306_Init ();



        SSD1306_GotoXY(10, 10);
        SSD1306_Puts("Press to ", &Font_11x18, 1);
        SSD1306_GotoXY (10, 30);
        SSD1306_Puts ("start", &Font_11x18, 1);
        SSD1306_UpdateScreen();
  /* USER CODE END 2 */





  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_SET);

                SSD1306_Clear();
                              SSD1306_UpdateScreen();



                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
                HAL_Delay(2000);
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);


                HAL_TIM_Base_Start(&htim2);


                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_SET);


                reaction_time = __HAL_TIM_GET_COUNTER(&htim2);
                HAL_TIM_Base_Stop(&htim2);
                __HAL_TIM_SET_COUNTER(&htim2, 0);


                SSD1306_Clear();
                SSD1306_GotoXY(10, 10);
                sprintf(reaction_time_str, "Time: %lu ms", reaction_time);
                SSD1306_Puts(reaction_time_str, &Font_11x18, 1);
                SSD1306_GotoXY (10, 30);
                 SSD1306_Puts ("ms", &Font_11x18, 1);
                SSD1306_UpdateScreen();


                HAL_Delay(2000);


                SSD1306_Clear();
                SSD1306_GotoXY(10, 10);
                SSD1306_Puts("Press to", &Font_11x18, 1);
                SSD1306_GotoXY(10, 30);
                SSD1306_Puts("start", &Font_11x18, 1);
                SSD1306_UpdateScreen();
            }
        }

  /* USER CODE END 3 */


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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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

}
  /* USER CODE END Error_Handler_Debug */


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
