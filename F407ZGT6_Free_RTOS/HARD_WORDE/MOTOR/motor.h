#ifndef __MOTOR_H
#define __MOTOR_H

#include "tim.h"

 extern uint16_t OC_Channel2_Pulse;
 extern uint16_t OC_Channel2_Duty;
 //X
 extern uint16_t OC_Channel1_Pulse;
 extern uint16_t OC_Channel1_Duty;
 //Z
 extern uint16_t OC_Channel3_Pulse;
 extern uint16_t OC_Channel3_Duty;


#define X_STEPMOTOR_DIR_FORWARD()               HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET)
#define X_STEPMOTOR_DIR_REVERSAL()              HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET)
#define Y_STEPMOTOR_DIR_FORWARD()               HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET)
#define Y_STEPMOTOR_DIR_REVERSAL()              HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_RESET)
#define Z_STEPMOTOR_DIR_FORWARD()               HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET)
#define Z_STEPMOTOR_DIR_REVERSAL()              HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET)
 
#define X_STEPMOTOR_OUTPUT_ENABLE();						HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET)
#define X_STEPMOTOR_OUTPUT_DISABLE();						HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET)
#define Y_STEPMOTOR_OUTPUT_ENABLE();						HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET)
#define Y_STEPMOTOR_OUTPUT_DISABLE();						HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET)
#define Z_STEPMOTOR_OUTPUT_ENABLE();						HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_RESET)
#define Z_STEPMOTOR_OUTPUT_DISABLE();						HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,GPIO_PIN_SET)

#define X_Motor_OFF()          									HAL_TIM_OC_Stop_IT(&htim1,TIM_CHANNEL_1)
#define Y_Motor_OFF()          									HAL_TIM_OC_Stop_IT(&htim1,TIM_CHANNEL_2)
#define Z_Motor_OFF()          									HAL_TIM_OC_Stop_IT(&htim1,TIM_CHANNEL_3)

#define X_Motor_ON()          									HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_1)
#define Y_Motor_ON()          									HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_2)
#define Z_Motor_ON()          									HAL_TIM_OC_Start_IT(&htim1,TIM_CHANNEL_3)
#define SPEED_N  1000

void Motor_init(void);

void MotorX_step(int speed,int dir,uint16_t step);//speed~1-100,dir 1正转 0反转
void MotorY_step(int speed,int dir,uint16_t step);//speed~1-100,dir 1正转 0反转
void MotorZ_step(int speed,int dir,uint16_t step);//speed~1-100,dir 1正转 0反转

void MotorX_speed(int speed,int dir);//speed~1-100,dir 1正转 0反转
void MotorY_speed(int speed,int dir);//speed~1-100,dir 1正转 0反转
void MotorZ_speed(int speed,int dir);//speed~1-100,dir 1正转 0反转

#endif

