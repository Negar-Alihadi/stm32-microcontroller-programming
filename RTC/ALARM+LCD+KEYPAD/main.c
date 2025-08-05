/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
void lcd_init(void);
void send_command(uint8_t data);
void send_Idata(uint8_t data);
void send_data(uint8_t data);
void lcd_puts(uint8_t *str);
void lcd_clear(void);
void lcd_gotoxy(uint8_t x, uint8_t y);
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
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */
RTC_TimeTypeDef time1={0};
RTC_AlarmTypeDef alarm1={0};
char buffer_1[30];
int array[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int ind=0;
int c=300;
int c2=5;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void lcd_init(void)
{
  HAL_Delay(2);
  send_command(0x02);
  send_command(0x28);
  send_command(0x0F);
}

void send_command(uint8_t data)
{
	HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);


	send_Idata(data >>4);
	send_Idata(data);


}

void send_Idata(uint8_t data)
{
	HAL_Delay(10);
	int temp[4];

	for (int i=0; i<4;i++)
	{

		temp[i]=data%2;
		data=data>>1;

	}



	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,temp[0]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,temp[1]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,temp[2]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,temp[3]);

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);

}



void send_data(uint8_t data)
{
	HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);


	send_Idata(data >>4);

	send_Idata(data);


}


void lcd_puts(uint8_t *str)
{
  HAL_Delay(2);
  while(*str !=0x00)
  {
	  send_data(*str);
    str++;
  }
}

void lcd_clear(void)
{
  HAL_Delay(1);
  send_command(0x01);

}


void lcd_gotoxy(uint8_t x, uint8_t y)
{
  HAL_Delay(1);

    switch(y){
    case 0:
      send_command( 0x80 + x );
    break;
    case 1:
      send_command( 0xC0 + x );
      break;

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
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

	 	 HAL_Delay(c);
	 	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==0){
	 		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	 		  while(ind<12){

	 			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	 			 HAL_Delay(c2);
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==0){
	 				  array[ind]=7;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==0){
	 				 array[ind]=4;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0){
	 				 array[ind]=1;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

	 			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	 			 HAL_Delay(c2);
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==0){
	 				 array[ind]=8;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==0){
	 				 array[ind]=5;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0){
	 				 array[ind]=2;
	 				  ind++;
	 			  }
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==0){
	 				 array[ind]=0;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

	 			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	 			 HAL_Delay(c2);
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==0){
	 				 array[ind]=9;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==0){
	 				 array[ind]=6;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0){
	 				 array[ind]=3;
	 				  ind++;
	 				 HAL_Delay(c);
	 			  }
	 			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	 		  }
	 		         time1.Hours=(array[0]*10)+array[1];
	 			 	 time1.Minutes=(array[2]*10)+array[3];
	 			 	 time1.Seconds=(array[4]*10)+array[5];
	 			 	 HAL_RTC_SetTime(&hrtc, &time1,RTC_FORMAT_BCD);
	 			 	 alarm1.AlarmTime.Hours=(array[6]*10)+array[7];
	 			 	 alarm1.AlarmTime.Minutes=(array[8]*10)+array[9];
	 			 	 alarm1.AlarmTime.Seconds=(array[10]*10)+array[11];
	 			     HAL_RTC_SetAlarm(&hrtc, &alarm1, RTC_FORMAT_BCD);
	 	  }

	 HAL_RTC_GetTime(&hrtc,&time1,RTC_FORMAT_BCD);
	 // HAL_RTC_GetDate(&hrtc,&,RTC_FORMAT_BCD);
	  HAL_RTC_GetAlarm(&hrtc, &alarm1, RTC_ALARM_A, RTC_FORMAT_BCD);
	  sprintf(buffer_1,"Time:%02u:%02u:%02u",time1.Hours,time1.Minutes,time1.Seconds);
	  lcd_gotoxy(0, 0);
	  lcd_puts((uint8_t *) buffer_1);
	  sprintf(buffer_1,"Alarm:%02u:%02u:%02u",alarm1.AlarmTime.Hours,alarm1.AlarmTime.Minutes,alarm1.AlarmTime.Seconds);
	  lcd_gotoxy(0, 1);
	  lcd_puts((uint8_t *) buffer_1);
	  HAL_Delay(200);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x1;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_THURSDAY;
  DateToUpdate.Month = RTC_MONTH_NOVEMBER;
  DateToUpdate.Date = 0x30;
  DateToUpdate.Year = 0x23;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0x1;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x30;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RS_Pin|RW_Pin|En_Pin|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RS_Pin RW_Pin En_Pin PB10
                           PB12 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = RS_Pin|RW_Pin|En_Pin|GPIO_PIN_10
                          |GPIO_PIN_12|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	UNUSED(hrtc);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_SET);
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
