#include "TB6612.h"
#include "main.h"
#include "pid.h"
#include "tim.h"
#include "stdbool.h"

extern tPid pid1_speed;
extern tPid pid2_speed;
extern tPid pid3_speed;
extern tPid pid4_speed;

extern APid pid3_Angle;//���3�ĽǶȿ���
extern APid pid4_Angle;//���4�ĽǶȿ���

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
	//���ݲ������� ����ѡ����
	
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
		if(motorC < -99) motorC = -99;//����PWM��ֵ
		//����ʱ�����ֵԽС  PWMռ�ձ�Խ��
		//���ڵ�motor1      -1   -99
		//���Ĵ������ߺ���  99  1 
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, (-motorC));//�޸Ķ�ʱ��1 ͨ��1 PA8 Pulse�ı�ռ�ձ�
	}
	else
		{
		if(motorC> 99) motorC = 99;
		//������   0 1  99
		//���Ǹ�ֵ 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, motorC);//�޸Ķ�ʱ��1 ͨ��1 PA8 Pulse�ı�ռ�ձ�
	}
	
	//motor2 ���õ��A��ת��
	if(motorD < 0)
	{
		if(motorD < -99) motorD = -99;//����PWM��ֵ
		//����ʱ�����ֵԽС  PWMռ�ձ�Խ��
		//���ڵ�motor2      -1   -99
		//���Ĵ������ߺ���   99  1 
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, (-motorD));//�޸Ķ�ʱ��1 ͨ��4 PA11 Pulse�ı�ռ�ձ�
	}
	else{
		if(motorD > 99) motorD = 99;
		//������   0 1 99
		//���Ǹ�ֵ 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, motorD);//�޸Ķ�ʱ��1 ͨ��4 PA11 Pulse�ı�ռ�ձ�

	}
}  
/*******************
*  @brief  �����������ת�ٺͷ���
*  @param  motor1:���B���ò�����motor2:���ò���
*  @param  motor1: ����1~100 ��Ӧ����B����������ٶ���1%-100%������-1~-100 ��Ӧ����B����������ٶ���1%-100%��motor2ͬ��
*  @return  ��
*
*******************/
void Motor_Set4(int motorD,int motorB,int motorC,int motorA)
{
	HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin,GPIO_PIN_SET);
	//���ݲ������� ����ѡ����
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
	
	//motor1 ���õ��B��ת��
	if(motorA < 0)
	{
		if(motorA < -99) motorA = -99;//����PWM��ֵ
		//����ʱ�����ֵԽС  PWMռ�ձ�Խ��
		//���ڵ�motor1      -1   -99
		//���Ĵ������ߺ���  99  1 
		 __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (-motorA));//�޸Ķ�ʱ��1 ͨ��1 PA8 Pulse�ı�ռ�ձ�
	}
	else
		{
		if(motorA > 99) motorB = 99;
		//������   0 1  99
		//���Ǹ�ֵ 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,motorA);//angle��
	}
	
	//motor2 ���õ��A��ת��
	if(motorB < 0)
	{
		if(motorB < -99) motorB = -99;//����PWM��ֵ
		//����ʱ�����ֵԽС  PWMռ�ձ�Խ��
		//���ڵ�motor2      -1   -99
		//���Ĵ������ߺ���   99  1 
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, (-motorB));//�޸Ķ�ʱ��1 ͨ��4 PA11 Pulse�ı�ռ�ձ�
	}
	else{
		if(motorB > 99) motorB = 99;
		//������   0 1 99
		//���Ǹ�ֵ 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, motorB);//�޸Ķ�ʱ��1 ͨ��4 PA11 Pulse�ı�ռ�ձ�

	}
	if(motorC < 0)
	{
		if(motorC < -99) motorC = -99;//����PWM��ֵ
		//����ʱ�����ֵԽС  PWMռ�ձ�Խ��
		//���ڵ�motor1      -1   -99
		//���Ĵ������ߺ���  99  1 
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, (-motorC));//�޸Ķ�ʱ��1 ͨ��1 PA8 Pulse�ı�ռ�ձ�
	}
	else
		{
		if(motorC> 99) motorC = 99;
		//������   0 1  99
		//���Ǹ�ֵ 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, motorC);//�޸Ķ�ʱ��1 ͨ��1 PA8 Pulse�ı�ռ�ձ�
	}
	
	//motor2 ���õ��A��ת��
	if(motorD < 0)
	{
		if(motorD < -99) motorD = -99;//����PWM��ֵ
		//����ʱ�����ֵԽС  PWMռ�ձ�Խ��
		//���ڵ�motor2      -1   -99
		//���Ĵ������ߺ���   99  1 
		__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, (-motorD));//�޸Ķ�ʱ��1 ͨ��4 PA11 Pulse�ı�ռ�ձ�
	}
	else{
		if(motorD > 99) motorD = 99;
		//������   0 1 99
		//���Ǹ�ֵ 0 1 99
		 __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, motorD);//�޸Ķ�ʱ��1 ͨ��4 PA11 Pulse�ı�ռ�ձ�

	}
}  

void motorPidSetSpeed4(float Motor1SetSpeed,float Motor2SetSpeed,float Motor3SetSpeed,float Motor4SetSpeed)
{
//�ı���PID������Ŀ���ٶ�
pid1_speed.target_val = Motor1SetSpeed;
pid2_speed.target_val = Motor2SetSpeed;
pid3_speed.target_val = Motor3SetSpeed;
pid4_speed.target_val = Motor4SetSpeed;
//����PID���� ��������ڵ��
Motor_Set4(PID_realize(&pid1_speed,Motor1Speed),PID_realize(&pid2_speed,Motor2Speed),PID_realize(&pid3_speed,Motor3Speed),PID_realize(&pid4_speed,Motor4Speed));
}

void motorPidSetSpeed2(float Motor4SetSpeed,float Motor3SetSpeed)
{
	motor_Angle=0;
//�ı���PID������Ŀ���ٶ�
pid3_speed.target_val = Motor3SetSpeed;
pid4_speed.target_val = Motor4SetSpeed;
//����PID���� ��������ڵ��
Motor_Set2(PID_realize(&pid3_speed,Motor3Speed),PID_realize(&pid4_speed,Motor4Speed));
}


void motorPidSetStup2(int Angle4,int Angle3)
{
//�ı���PID������Ŀ���ٶ�
motor_Angle=1;
AngleL=Angle4;
AngleR=Angle3;
}

void motorPidSetStup_Speed2(void)
{
	motor_Angle=1;
//�ı���PID������Ŀ���ٶ�
pid4_Angle.A_target_val=AngleL;
pid3_Angle.A_target_val=AngleR;
	
pid3_speed.target_val = A_PID_realize(&pid3_Angle,Motor3Angle);
pid4_speed.target_val = A_PID_realize(&pid4_Angle,Motor4Angle);

//����PID���� ��������ڵ��
Motor_Set2(PID_realize(&pid3_speed,Motor3Speed),PID_realize(&pid4_speed,Motor4Speed));
}



