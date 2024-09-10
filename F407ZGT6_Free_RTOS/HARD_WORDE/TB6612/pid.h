#ifndef __PID_H
#define __PID_H

//����һ���ṹ������
typedef struct 
{
	float target_val;//Ŀ��ֵ
	float actual_val;//ʵ��ֵ
	float err;//��ǰƫ��
	float err_last;//�ϴ�ƫ��
	float err_sum;//����ۼ�ֵ
	float Kp,Ki,Kd;//���������֣�΢��ϵ��
	
} tPid;
typedef struct 
{
	float A_target_val;//Ŀ��ֵ
	float A_actual_val;//ʵ��ֵ
	float A_err;//��ǰƫ��
	float A_err_last;//�ϴ�ƫ��
	float A_err_sum;//����ۼ�ֵ
	float A_Kp,A_Ki,A_Kd;//���������֣�΢��ϵ��
	
} APid;

//��������
float P_realize(tPid * pid,float actual_val);
void PID_init(void);
float PI_realize(tPid * pid,float actual_val);
float PID_realize(tPid * pid,float actual_val);


float A_PID_realize(APid*pid,float A_actual_val);
#endif

