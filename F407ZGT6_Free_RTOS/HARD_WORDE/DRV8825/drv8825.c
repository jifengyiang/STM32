#include "drv8825.h"

extern int DIRX;
extern int DIRY;
extern int DIRZ;

extern int date;

void Subdivide_Init(void)//32ϸ��
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_14,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_15,GPIO_PIN_SET);
}

void MotorX_off(void)
{
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);//������ʱ��1 ͨ��1 PWM���
}
void MotorY_off(void)
{
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//������ʱ��1 ͨ��1 PWM���
}
void MotorZ_off(void)
{
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);//������ʱ��1 ͨ��1 PWM���
}

void MotorX_on(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//������ʱ��1 ͨ��1 PWM���
}
void MotorY_on(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//������ʱ��1 ͨ��1 PWM���
}
void MotorZ_on(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);//������ʱ��1 ͨ��1 PWM���
}

void MotorX_Speed(int	Speed,int dir)
{
	MotorX_on();
	DIRX=dir;
	if(dir==1)
	X_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	X_STEPMOTOR_DIR_REVERSAL();
	__HAL_TIM_SET_AUTORELOAD(&htim1, Speed);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed/2);
}

void MotorY_Speed(int	Speed,int dir)
{
	MotorY_on();
	DIRY=dir;
	if(dir==1)
	Y_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Y_STEPMOTOR_DIR_REVERSAL();
	__HAL_TIM_SET_AUTORELOAD(&htim1, Speed);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,Speed/2);

}


void MotorZ_Speed(int	Speed,int dir)
{
	MotorZ_on();
	DIRY=dir;
	if(dir==1)
	Z_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Z_STEPMOTOR_DIR_REVERSAL();
	__HAL_TIM_SET_AUTORELOAD(&htim1, Speed);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,Speed/2);

}

void MotorX_steps(int speed,int dir,uint16_t step)//speed~1-100,dir 1��ת 0��ת
{
	date=1;
	MotorX_on();
	HAL_TIM_Base_Start_IT(&htim1);	// �жϿ���
	DIRX=dir;
	road_PWMX_num=step;
	if(dir==1)
	X_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	X_STEPMOTOR_DIR_REVERSAL();
	__HAL_TIM_SET_AUTORELOAD(&htim1, speed);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,speed/2);
}

void MotorY_steps(int speed,int dir,uint16_t step)//speed~1-100,dir 1��ת 0��ת
{
	date=2;
	MotorY_on();
	HAL_TIM_Base_Start_IT(&htim1);	// �жϿ���
	DIRY=dir;
	road_PWMY_num=step;
	if(dir==1)
	Y_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Y_STEPMOTOR_DIR_REVERSAL();
	__HAL_TIM_SET_AUTORELOAD(&htim1, speed);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,speed/2);

}


void MotorZ_steps(int speed,int dir,uint16_t step)//speed~1-100,dir 1��ת 0��ת
{
	date=3;
	MotorZ_on();
	HAL_TIM_Base_Start_IT(&htim1);	// �жϿ���
	DIRZ=dir;
	road_PWMZ_num=step;
	if(dir==1)
	Z_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Z_STEPMOTOR_DIR_REVERSAL();
	__HAL_TIM_SET_AUTORELOAD(&htim1, speed);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,speed/2);

}


