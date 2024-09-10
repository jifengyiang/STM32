#include "TB6612.h"
#include "main.h"
#include "pid.h"
#include "tim.h"
#include "stdbool.h"

extern tPid pid1_speed;
extern tPid pid2_speed;
extern tPid pid3_speed;
extern tPid pid4_speed;

extern APid pid3_Angle;//电机3的角度控制
extern APid pid4_Angle;//电机4的角度控制

extern int AngleL;
extern int AngleR;

extern float Motor1Speed;
extern float Motor2Speed;

extern float Motor3Speed;
extern float Motor4Speed;

extern int Motor3Angle;
extern int Motor4Angle;

extern int flag;
int capture=0;
extern int action;
extern bool motor_Angle;


void Motor_Set2(int motorC,int motorD)
{
	HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin,GPIO_PIN_SET);
	//根据参数正负 设置选择方向
	
	if(motorC < 0) 
	{
		CIN1_RESET;
		CIN2_SET;
	}
	 else      
	{
		CIN1_SET;
		CIN2_RESET;
	}
		if(motorD < 0) 
	{
		DIN1_RESET;
		DIN2_SET;
	}
	 else      
	{
		DIN1_SET;
		DIN2_RESET;
	}
	

	if(motorC < 0)
	{
		if(motorC < -99) motorC = -99;//超过PWM幅值
		//负的时候绝对值越小  PWM占空比越大
		//现在的motor1      -1   -99
		//给寄存器或者函数  99  1 
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, (-motorC));//修改定时器1 通道1 PA8 Pulse改变占空比
	}
	else
		{
		if(motorC> 99) motorC = 99;
		//现在是   0 1  99
		//我们赋值 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, motorC);//修改定时器1 通道1 PA8 Pulse改变占空比
	}
	
	//motor2 设置电机A的转速
	if(motorD < 0)
	{
		if(motorD < -99) motorD = -99;//超过PWM幅值
		//负的时候绝对值越小  PWM占空比越大
		//现在的motor2      -1   -99
		//给寄存器或者函数   99  1 
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, (-motorD));//修改定时器1 通道4 PA11 Pulse改变占空比
	}
	else{
		if(motorD > 99) motorD = 99;
		//现在是   0 1 99
		//我们赋值 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, motorD);//修改定时器1 通道4 PA11 Pulse改变占空比

	}
}  
/*******************
*  @brief  设置两个电机转速和方向
*  @param  motor1:电机B设置参数、motor2:设置参数
*  @param  motor1: 输入1~100 对应控制B电机正方向速度在1%-100%、输入-1~-100 对应控制B电机反方向速度在1%-100%、motor2同理
*  @return  无
*
*******************/
void Motor_Set4(int motorD,int motorB,int motorC,int motorA)
{
	HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin,GPIO_PIN_SET);
	//根据参数正负 设置选择方向
	if(motorA < 0) 
	{
		AIN1_RESET;
		AIN2_SET;
	}
	 else      
	{
		AIN1_SET;
		AIN2_RESET;
	}
		if(motorB < 0) 
	{
		BIN1_SET;
		BIN2_RESET;
	}
	 else      
	{
		BIN1_RESET;
		BIN2_SET;
	}
	if(motorC < 0) 
	{
		CIN1_SET;
		CIN2_RESET;
	}
	 else      
	{
		CIN1_RESET;
		CIN2_SET;
	}
		if(motorD < 0) 
	{
		DIN1_RESET;
		DIN2_SET;
	}
	 else      
	{
		DIN1_SET;
		DIN2_RESET;
	}
	
	//motor1 设置电机B的转速
	if(motorA < 0)
	{
		if(motorA < -99) motorA = -99;//超过PWM幅值
		//负的时候绝对值越小  PWM占空比越大
		//现在的motor1      -1   -99
		//给寄存器或者函数  99  1 
		 __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (-motorA));//修改定时器1 通道1 PA8 Pulse改变占空比
	}
	else
		{
		if(motorA > 99) motorB = 99;
		//现在是   0 1  99
		//我们赋值 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,motorA);//angle度
	}
	
	//motor2 设置电机A的转速
	if(motorB < 0)
	{
		if(motorB < -99) motorB = -99;//超过PWM幅值
		//负的时候绝对值越小  PWM占空比越大
		//现在的motor2      -1   -99
		//给寄存器或者函数   99  1 
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, (-motorB));//修改定时器1 通道4 PA11 Pulse改变占空比
	}
	else{
		if(motorB > 99) motorB = 99;
		//现在是   0 1 99
		//我们赋值 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, motorB);//修改定时器1 通道4 PA11 Pulse改变占空比

	}
	if(motorC < 0)
	{
		if(motorC < -99) motorC = -99;//超过PWM幅值
		//负的时候绝对值越小  PWM占空比越大
		//现在的motor1      -1   -99
		//给寄存器或者函数  99  1 
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, (-motorC));//修改定时器1 通道1 PA8 Pulse改变占空比
	}
	else
		{
		if(motorC> 99) motorC = 99;
		//现在是   0 1  99
		//我们赋值 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, motorC);//修改定时器1 通道1 PA8 Pulse改变占空比
	}
	
	//motor2 设置电机A的转速
	if(motorD < 0)
	{
		if(motorD < -99) motorD = -99;//超过PWM幅值
		//负的时候绝对值越小  PWM占空比越大
		//现在的motor2      -1   -99
		//给寄存器或者函数   99  1 
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, (-motorD));//修改定时器1 通道4 PA11 Pulse改变占空比
	}
	else{
		if(motorD > 99) motorD = 99;
		//现在是   0 1 99
		//我们赋值 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, motorD);//修改定时器1 通道4 PA11 Pulse改变占空比

	}
}  

void motorPidSetSpeed4(float Motor1SetSpeed,float Motor2SetSpeed,float Motor3SetSpeed,float Motor4SetSpeed)
{
//改变电机PID参数的目标速度
pid1_speed.target_val = Motor1SetSpeed;
pid2_speed.target_val = Motor2SetSpeed;
pid3_speed.target_val = Motor3SetSpeed;
pid4_speed.target_val = Motor4SetSpeed;
//根据PID计算 输出作用于电机
Motor_Set4(PID_realize(&pid1_speed,Motor1Speed),PID_realize(&pid2_speed,Motor2Speed),PID_realize(&pid3_speed,Motor3Speed),PID_realize(&pid4_speed,Motor4Speed));
}

void motorPidSetSpeed2(float Motor4SetSpeed,float Motor3SetSpeed)
{
	motor_Angle=0;
//改变电机PID参数的目标速度
pid3_speed.target_val = Motor3SetSpeed;
pid4_speed.target_val = Motor4SetSpeed;
//根据PID计算 输出作用于电机
Motor_Set2(PID_realize(&pid3_speed,Motor3Speed),PID_realize(&pid4_speed,Motor4Speed));
}


void motorPidSetStup2(int Angle4,int Angle3)
{
//改变电机PID参数的目标速度
motor_Angle=1;
AngleL=Angle4;
AngleR=Angle3;
}

void motorPidSetStup_Speed2(void)
{
	motor_Angle=1;
//改变电机PID参数的目标速度
pid4_Angle.A_target_val=AngleL;
pid3_Angle.A_target_val=AngleR;
	
pid3_speed.target_val = A_PID_realize(&pid3_Angle,Motor3Angle);
pid4_speed.target_val = A_PID_realize(&pid4_Angle,Motor4Angle);

//根据PID计算 输出作用于电机
Motor_Set2(PID_realize(&pid3_speed,Motor3Speed),PID_realize(&pid4_speed,Motor4Speed));
}



