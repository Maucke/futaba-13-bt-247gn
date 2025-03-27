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
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "13-bt-247gn.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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
int testMode = 0;
#define BUFFER_SIZE 256
uint8_t rx_buffer[BUFFER_SIZE];
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
  MX_SPI1_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  //  HAL_SPI_Receive_DMA(&hspi1, rx_buffer, BUFFER_SIZE);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, BUFFER_SIZE);
  init_screen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
                    if (testMode)
      test();
    scan_screen();
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
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

/* USER CODE BEGIN 4 */

void Data_RxIntCpltCallback(uint8_t *recv_buff, int count)
{
  uint8_t *pGram = (uint8_t *)&internalGram;
  {
    testMode = 0;
    //		if(recv_buff[0] == 0xFF)
    //			NVIC_SystemReset();
// 		printf("%02X ", recv_buff[0]);
    if (recv_buff[0] < 0x20) // range:0x00-0x0D
    {
      for (size_t i = 0; i < (count - 1) && (recv_buff[0] * 9 + i) < (9 * 13); i++)
      {
        pGram[recv_buff[0] * 9 + i] = recv_buff[i + 1];
        //			printf("%02X ", recv_buff[i + 1]);
      }
    }
    else if (recv_buff[0] < 0x40) // bit 4-2:x, bit 0:y range:0x20-0x3F
    {
      for (size_t i = 0; i < (count - 1); i+=5)
      {
//        printf("ascii_show(%d,%d,%X)", ((recv_buff[0] & 0x1E) >> 1) + i/5, recv_buff[0] & 1, recv_buff[i + 1]);
        ascii_show(((recv_buff[0] & 0x1E) >> 1) + i/5, recv_buff[0] & 1, recv_buff + i + 1);
      }
    }
    else if (recv_buff[0] < 0x60) // bit 4-2:x, bit 0:y range:0x40-0x5F
    {
      for (size_t i = 0; i < (count - 1); i++)
      {
        num_show((recv_buff[0] & 0x1F) + i, recv_buff[i + 1]);
      }
    }
    else if (recv_buff[0] == 0x60) // bit 4-2:x, bit 0:y range:0x60
    {
      for (size_t i = 0; i < (count - 2); i++)
      {
        icon_show((Icon_e)(recv_buff[1] + i), recv_buff[i + 2]);
      }
    }
    else if (recv_buff[0] < 0xA0) // bit 4-2:x, bit 0:y range:0x80-0x9F
    {
      for (size_t i = 0; i < (count - 1); i++)
      {
        num_show((recv_buff[0] & 0x1F) + i, num_hex_codes[recv_buff[i + 1] - ' ']);
      }
    }
    else if (recv_buff[0] < 0xB0) // bit 4-2:x, bit 0:y range:0xA0-0xAF
    {
      for (size_t i = 0; i < (count - 1); i++)
      {
//        printf("ascii_show(%d,%d,%X)", ((recv_buff[0] & 0x1E) >> 1) + i/5, recv_buff[0] & 1, recv_buff[i + 1]);
        ascii_show(((recv_buff[0] & 0x1E) >> 1) + i, recv_buff[0] & 1, hex_codes[recv_buff[i + 1] - ' ']);
      }
    }
    else if (recv_buff[0] < 0xC0) // bit 4-2:x, bit 0:y range:0xB0-0xBF
		{
      if (recv_buff[0] == 0xB0)
        setdimming(recv_buff[1]);
		}
    //		printf("count: %d\n", count);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    //    for (i = 0; i < 13; i++)
    //		{
    //			for (j = 0; j < 9; j++)
    //				printf("%02X ", internalGram[i][j]);
    //			printf("\n");
    //		}
  }
  memset(recv_buff, 0, BUFFER_SIZE);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size)
{
  if(&huart1 == huart)
  {
    Data_RxIntCpltCallback(rx_buffer, Size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, BUFFER_SIZE);
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint16_t remaining_count = hdma_spi1_rx.Instance->NDTR;
  uint16_t current_count = BUFFER_SIZE - remaining_count;
  HAL_SPI_DMAStop(&hspi1);
  __HAL_SPI_CLEAR_OVRFLAG(&hspi1);
  __HAL_SPI_CLEAR_CRCERRFLAG(&hspi1);
  HAL_SPI_Init(&hspi1);

  Data_RxIntCpltCallback(rx_buffer, current_count);

  HAL_SPI_Receive_DMA(&hspi1, rx_buffer, BUFFER_SIZE);

  // printf("%d --> %d", GPIO_Pin, HAL_GPIO_ReadPin(SPI1_SCS_GPIO_Port, SPI1_SCS_Pin));
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
