/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#include "drv8825.h"
#define Speed_X	3000
#define Speed_Y	3000
#define Speed_Z	3000
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
#define LCD_CS_Pin GPIO_PIN_9
#define LCD_CS_GPIO_Port GPIOD
#define LCD_DC_Pin GPIO_PIN_10
#define LCD_DC_GPIO_Port GPIOD
#define LCD_RESET_Pin GPIO_PIN_11
#define LCD_RESET_GPIO_Port GPIOD
#define DIN1_Pin GPIO_PIN_11
#define DIN1_GPIO_Port GPIOC
#define DIN2_Pin GPIO_PIN_12
#define DIN2_GPIO_Port GPIOC
#define AIN1_Pin GPIO_PIN_0
#define AIN1_GPIO_Port GPIOD
#define AIN2_Pin GPIO_PIN_1
#define AIN2_GPIO_Port GPIOD
#define STBY_Pin GPIO_PIN_2
#define STBY_GPIO_Port GPIOD
#define BIN1_Pin GPIO_PIN_3
#define BIN1_GPIO_Port GPIOD
#define BIN2_Pin GPIO_PIN_4
#define BIN2_GPIO_Port GPIOD
#define CIN1_Pin GPIO_PIN_5
#define CIN1_GPIO_Port GPIOD
#define CIN2_Pin GPIO_PIN_6
#define CIN2_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
