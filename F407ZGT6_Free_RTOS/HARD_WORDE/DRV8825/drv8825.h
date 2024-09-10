#ifndef DRV8825_H
#define DRV8825_H

#include "tim.h"
#include "gpio.h"

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


extern int road_PWMX_num;
extern int road_PWMY_num;
extern int road_PWMZ_num;

void Subdivide_Init(void);//32细分

void MotorX_off(void);
void MotorY_off(void);
void MotorZ_off(void);
void MotorX_on(void);
void MotorY_on(void);
void MotorZ_on(void);

void MotorX_Speed(int	Speed,int dir);
void MotorY_Speed(int	Speed,int dir);
void MotorZ_Speed(int	Speed,int dir);

void MotorX_steps(int speed,int dir,uint16_t step);//speed~1-100,dir 1正转 0反转
void MotorY_steps(int speed,int dir,uint16_t step);//speed~1-100,dir 1正转 0反转
void MotorZ_steps(int speed,int dir,uint16_t step);//speed~1-100,dir 1正转 0反转

#endif

