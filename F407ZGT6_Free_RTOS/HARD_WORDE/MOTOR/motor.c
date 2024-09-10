#include "motor.h"




extern int DIRX;
extern int DIRY;
extern int DIRZ;


uint16_t SUPT_X=0;
uint16_t SUPT_Y=0;
uint16_t SUPT_Z=0;

uint16_t STEP_X=0;
uint16_t STEP_Y=0;
uint16_t STEP_Z=0;

void Motor_init(void)
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

void MotorX_step(int speed,int dir,uint16_t step)//speed~1-100,dir 1正转 0反转
{
	X_Motor_ON();
	DIRX=dir;
	STEP_X=step;
	OC_Channel1_Pulse=SPEED_N/speed;
	if(dir==1)
	X_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	X_STEPMOTOR_DIR_REVERSAL();

}


void MotorY_step(int speed,int dir,uint16_t step)//speed~1-100,dir 1正转 0反转
{
	Y_Motor_ON();
	DIRY=dir;
	STEP_Y=step;
	OC_Channel2_Pulse=SPEED_N/speed;
	if(dir==1)
	Y_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Y_STEPMOTOR_DIR_REVERSAL();

}


void MotorZ_step(int speed,int dir ,uint16_t step)//speed~1-100,dir 1正转 0反转
{
	Z_Motor_ON();
	DIRZ=dir;
	STEP_Z=step;
	OC_Channel3_Pulse=SPEED_N/speed;
	if(dir==1)
	Z_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Z_STEPMOTOR_DIR_REVERSAL();

}

void MotorX_speed(int speed,int dir)//speed~1-100,dir 1正转 0反转
{
	X_Motor_ON();
	DIRX=dir;
	
	OC_Channel1_Pulse=SPEED_N/speed;
	if(dir==1)
	X_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	X_STEPMOTOR_DIR_REVERSAL();

}


void MotorY_speed(int speed,int dir)//speed~1-100,dir 1正转 0反转
{
	Y_Motor_ON();
	DIRY=dir;
	OC_Channel2_Pulse=SPEED_N/speed;
	if(dir==1)
	Y_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Y_STEPMOTOR_DIR_REVERSAL();

}


void MotorZ_speed(int speed,int dir )//speed~1-100,dir 1正转 0反转
{
	Z_Motor_ON();
	DIRZ=dir;
	OC_Channel3_Pulse=SPEED_N/speed;
	if(dir==1)
	Z_STEPMOTOR_DIR_FORWARD();
	else if(dir==0)
	Z_STEPMOTOR_DIR_REVERSAL();

}



void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint16_t OC_Capture = 0;
	
  if(htim->Instance == TIM1)//判断发生输出比较中断的定时器
  {
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)//判断发生输出比较中断的通道
    {
		if(DIRX==1)
			SUPT_X++;
		else if(DIRX==0)
			SUPT_X--;
		OC_Capture = __HAL_TIM_GetCompare(htim, TIM_CHANNEL_1);//读取捕获值(CCR)
		
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,OC_Capture + OC_Channel1_Pulse);		
    }
		
    else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)//判断发生输出比较中断的通道
    {
		if(DIRY==1)
			SUPT_Y++;
		else if(DIRY==0)
			SUPT_Y--;
		OC_Capture = __HAL_TIM_GetCompare(htim, TIM_CHANNEL_2);//读取捕获值(CCR)
		
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,OC_Capture + OC_Channel2_Pulse);		
    }
    else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)//判断发生输出比较中断的通道
    {
		if(DIRZ==1)
			SUPT_Z++;
		else if(DIRZ==0)
			SUPT_Z--;
		OC_Capture = __HAL_TIM_GetCompare(htim, TIM_CHANNEL_3);//读取捕获值(CCR)
		
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,OC_Capture + OC_Channel3_Pulse);		
    }
		if(STEP_X==SUPT_X)
		{
			SUPT_X=0;
			X_Motor_OFF() ;
		}
		if(STEP_Y==SUPT_Y)
		{
			SUPT_Y=0;
			Y_Motor_OFF() ;
		}
		if(STEP_Z==SUPT_Z)
		{
			SUPT_Z=0;
			Z_Motor_OFF() ;
		}
  }

	if(SUPT_X==65535||SUPT_Y==65535||SUPT_Z==65535)
	{
		if(SUPT_X==65535)
			SUPT_X=0;
		if(SUPT_Y==65535)
			SUPT_Y=0;
		if(SUPT_Z==65535)
			SUPT_Z=0;
	
	}
}







