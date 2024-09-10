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
#include "cmsis_os.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "drv8825.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "oled.h" 
#include "sevor.h"
#include "pid.h"
#include "TB6612.h"
#include "lcd.h"
#include "mpu6050.h" 
#include "imu.h"

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

float Motor1Speed = 0.00;
float Motor2Speed = 0.00;
float Motor3Speed = 0.00;
float Motor4Speed = 0.00;

int Motor3Angle=0;
int Motor4Angle=0;

int AngleL=0;
int AngleR=0;

short Encode1Count = 0;//编码器计数器值
short Encode2Count = 0;
short Encode3Count = 0;//编码器计数器值
short Encode4Count = 0;

extern double  Encode4_stup;
extern double  Encode3_stup;
double Encode3Count_ALL = 0;//编码器计数器值
double Encode4Count_ALL = 0;

int flag=0;
int left=0,right=0;

extern int action;
extern int capture;
extern int mode;
extern bool motor_Angle;
extern int star;

extern tPid pid1_speed;
extern tPid pid2_speed;

extern APid pid3_Angle;//电机3的角度控制
extern APid pid4_Angle;//电机4的角度控制

extern float Motor1Speed;
extern float Motor2Speed;
extern tPid pid3_speed;
extern tPid pid4_speed;
extern float Motor3Speed;
extern float Motor4Speed;
uint16_t TimerCount=0;

uint8_t RxBuff2[10];
uint8_t RxByte1;//串口每接收一个数据，就存入RxByte中
uint8_t RxBuff1[9];
uint16_t Rx_Count1;

extern uint8_t RxByte3;//串口每接收一个数据，就存入RxByte中

bool motor_Angle=false;





int DIRX;
int DIRY; 
int DIRZ;

int MotorX_PWM_num = 0;		// 电机1当前脉冲数
int MotorY_PWM_num = 0;		// 电机2当前脉冲数
int MotorZ_PWM_num = 0;		// 电机3当前脉冲数

int road_PWMX_num = 0;	// 步进电机目标脉冲数(一圈6400脉冲)
int road_PWMY_num = 0;	// 步进电机目标脉冲数(一圈6400脉冲)
int road_PWMZ_num = 0;	// 步进电机目标脉冲数(一圈6400脉冲)

int date;

//Y
 uint16_t OC_Channel2_Pulse=0;
 uint16_t OC_Channel2_Duty=50;
 //X
 uint16_t OC_Channel1_Pulse=0;
 uint16_t OC_Channel1_Duty=50;
 //Z
 uint16_t OC_Channel3_Pulse=0;
 uint16_t OC_Channel3_Duty=50;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM9_Init();
  MX_TIM12_Init();
  MX_SPI1_Init();
  MX_I2C2_Init();
  MX_TIM7_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	Subdivide_Init();
	PID_init();
	HAL_Delay(20);
	OLED_init();
	LCD_Init();
	
	MPU_Init();//陀螺仪
	
	X_STEPMOTOR_DIR_FORWARD();
	Y_STEPMOTOR_DIR_FORWARD();
	Z_STEPMOTOR_DIR_FORWARD();
	
  X_STEPMOTOR_OUTPUT_ENABLE();
  Y_STEPMOTOR_OUTPUT_ENABLE();
	Z_STEPMOTOR_OUTPUT_ENABLE();
	
	HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_1);
	HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_2);
	HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);//开启定时器8 通道1 PWM输出
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);//开启定时器8 通道2 PWM输出
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);//开启定时器8 通道3 PWM输出
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);//开启定时器8 通道3 PWM输出
	
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);//开启定时器8 通道1 PWM输出
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);//开启定时器8 通道2 PWM输出
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);//开启定时器8 通道3 PWM输出
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);//开启定时器8 通道3 PWM输出
	
  HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);//开启定时器2
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);//开启定时器2
  HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);//开启定时器4
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);//开启定时器4
	
	HAL_TIM_Base_Start_IT(&htim2);				//开启定时器2 中断
  HAL_TIM_Base_Start_IT(&htim3);        //开启定时器4 中断
	HAL_TIM_Base_Start_IT(&htim4);				//开启定时器2 中断
  HAL_TIM_Base_Start_IT(&htim5);        //开启定时器4 中断
	HAL_TIM_Base_Start_IT(&htim9);				//开启定时器2 中断
	
	HAL_UART_Receive_DMA(&huart1,RxBuff1,8);//串口2每接收到一个数据存入RxByte中，并调用一次回调函数
	HAL_UART_Receive_DMA(&huart2,RxBuff2,1);//串口2每接收到一个数据存入RxByte中，并调用一次回调函数
	HAL_UART_Receive_IT(&huart3,&RxByte3,1);//串口2每接收到一个数据存入RxByte中，并调用一次回调函数

	MotorX_off();
	MotorY_off();
	MotorZ_off();
	Z_STEPMOTOR_OUTPUT_DISABLE();
//	motorPidSetSpeed(-1,-1,-1,-1);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
if(htim == &htim9)//htim1 500HZ  2ms 中断一次
	{
		TimerCount++;
		if(TimerCount %5 == 0)//每10ms执行一次
		{
//			if(pid1_speed.target_val>=0)
//			{
//				Encode1Count = (short)__HAL_TIM_GET_COUNTER(&htim2);
//				Motor1Speed = (float)Encode1Count*100/30/13/4;
//			}
//			else if(pid1_speed.target_val<0)
//			{
//				Encode1Count = -(short)__HAL_TIM_GET_COUNTER(&htim2);
//				Motor1Speed = -(float)Encode1Count*100/30/13/4;
//			}
//			if(pid2_speed.target_val>=0)
//			{
//				Encode2Count = -(short)__HAL_TIM_GET_COUNTER(&htim3);
//				Motor2Speed = (float)Encode4Count*100/30/13/4;
//			}
//			else if(pid2_speed.target_val<0)
//			{
//				Encode2Count = (short)__HAL_TIM_GET_COUNTER(&htim3);
//				Motor2Speed = -(float)Encode2Count*100/30/13/4;
//			}
			
				Encode3Count = (short)__HAL_TIM_GET_COUNTER(&htim4);
				Motor3Speed = (float)Encode3Count*100/30/13/4;
				Encode4Count = -(short)__HAL_TIM_GET_COUNTER(&htim5);
				Motor4Speed = (float)Encode4Count*100/30/13/4;
				
			if(motor_Angle==1)
			{
			Encode3Count_ALL=Encode3Count_ALL+Encode3Count;
			Encode4Count_ALL=Encode4Count_ALL+Encode4Count;
			Motor3Angle=Encode3Count_ALL*360/30/13/4;
			Motor4Angle=Encode4Count_ALL*360/30/13/4;
			}
//			__HAL_TIM_SET_COUNTER(&htim2,0);
//			__HAL_TIM_SET_COUNTER(&htim3,0);
			__HAL_TIM_SET_COUNTER(&htim4,0);
			__HAL_TIM_SET_COUNTER(&htim5,0);
			
			
		if(TimerCount %10 ==0)//每20ms一次
		{
			if(motor_Angle==0)
			{
			 Motor_Set2(PID_realize(&pid3_speed,Motor3Speed),PID_realize(&pid4_speed,Motor4Speed));
			}
			else if(motor_Angle==1)
			{
				motorPidSetStup_Speed2();
				if((Motor3Angle<=AngleR+5)&&(Motor3Angle>=AngleR-5)&&(Motor4Angle>=AngleL-5)&&(Motor4Angle<=AngleL+5))
				{
					Encode3Count_ALL=0;
					Encode4Count_ALL=0;
					pid3_speed.target_val=0;
					pid4_speed.target_val=0;
					motor_Angle=0;
				}
				
			}
			 TimerCount=0;
		}
		}
	}

	else if(htim->Instance == TIM1)	// 定时器2(步进电机1PWM)
	{
	if(date==1)
	{
			MotorX_PWM_num ++;
			if(MotorX_PWM_num >= road_PWMX_num)
			{
				MotorX_PWM_num = 0;
				HAL_TIM_Base_Stop_IT(&htim1);
				HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);	// 停止输出PWM
				
			}
		}
		else if(date==2)
		{
			MotorY_PWM_num ++;
			if(MotorY_PWM_num >= road_PWMY_num)
			{
				MotorY_PWM_num = 0;
				HAL_TIM_Base_Stop_IT(&htim1);
				HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);	// 停止输出PWM
			}
		}
		else if(date==3)
		{
	
			MotorZ_PWM_num ++;
			if(MotorZ_PWM_num >= road_PWMZ_num)
			{
				MotorZ_PWM_num = 0;
				HAL_TIM_Base_Stop_IT(&htim1);
				HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);	// 停止输出PWM
				
			}
		}
		}
	

  /* USER CODE END Callback 1 */
}

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
