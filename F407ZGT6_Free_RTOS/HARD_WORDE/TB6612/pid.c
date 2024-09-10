#include "pid.h"
#include "stdbool.h"

extern bool motor_Angle;
int ERRO=0;

tPid pid1_speed;//���1��ת�ٿ���
tPid pid2_speed;//���2��ת�ٿ���
tPid pid3_speed;//���3��ת�ٿ���
tPid pid4_speed;//���4��ת�ٿ���

APid pid3_Angle;//���3�ĽǶȿ���
APid pid4_Angle;//���4�ĽǶȿ���
//���ṹ�����ͱ�������ֵ
void PID_init()
{
/**********�ٶȻ�pid****************/
pid1_speed.actual_val=0.0;//��ʼ�����1ת��PID �ṹ��
pid1_speed.target_val=0.0;
pid1_speed.err=0.0;
pid1_speed.err_last=0.0;
pid1_speed.err_sum=0.0;
pid1_speed.Kp=50;			//23
pid1_speed.Ki=5.0;			//15
pid1_speed.Kd=0.0;
	
pid2_speed.actual_val=0.0;//��ʼ�����2ת��PID �ṹ��
pid2_speed.target_val=0.0;
pid2_speed.err=0.0;
pid2_speed.err_last=0.0;
pid2_speed.err_sum=0.0;
pid2_speed.Kp=50;				//35
pid2_speed.Ki=5;				//18
pid2_speed.Kd=0.0;
	
pid3_speed.actual_val=0.0;//��ʼ�����1ת��PID �ṹ��
pid3_speed.target_val=0.0;
pid3_speed.err=0.0;
pid3_speed.err_last=0.0;
pid3_speed.err_sum=0.0;
pid3_speed.Kp=50;			//23
pid3_speed.Ki=2.5;			//15
pid3_speed.Kd=0.0;

pid4_speed.actual_val=0.0;//��ʼ�����2ת��PID �ṹ��
pid4_speed.target_val=0.0;
pid4_speed.err=0.0;
pid4_speed.err_last=0.0;
pid4_speed.err_sum=0.0;
pid4_speed.Kp=50;				//35
pid4_speed.Ki=3;				//18
pid4_speed.Kd=0.0;	

/**********λ�û�pid****************/
pid3_Angle.A_target_val=0;
pid3_Angle.A_actual_val=0;
pid3_Angle.A_err=0;
pid3_Angle.A_err_last=0;
pid3_Angle.A_err_sum=0;
pid3_Angle.A_Kp=0.01;
pid3_Angle.A_Ki=0.00;
pid3_Angle.A_Kd=0;

pid4_Angle.A_target_val=0;
pid4_Angle.A_actual_val=0;
pid4_Angle.A_err=0;
pid4_Angle.A_err_last=0;
pid4_Angle.A_err_sum=0;
pid4_Angle.A_Kp=0.01;
pid4_Angle.A_Ki=0.00;
pid4_Angle.A_Kd=0;
}
//����p���ڿ��ƺ���
float P_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//������ʵֵ
	pid->err = pid->target_val - pid->actual_val;//Ŀ��ֵ��ȥʵ��ֵ�������ֵ
	//�������Ƶ���
	pid->actual_val = pid->Kp*pid->err;
	return pid->actual_val;
}
//����P ����I ���ƺ���
float PI_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//������ʵֵ
	pid->err = pid->target_val - pid->actual_val;//��ǰ���=Ŀ��ֵ-��ʵֵ
	pid->err_sum += pid->err;//����ۼ�ֵ = ��ǰ����ۼƺ�
	//ʹ��PI���� ���=Kp*��ǰ���+Ki*����ۼ�ֵ
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum;
	
	return pid->actual_val;
}
// PID���ƺ���
float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//������ʵֵ
	pid->err = pid->target_val - pid->actual_val;////��ǰ���=Ŀ��ֵ-��ʵֵ
	pid->err_sum += pid->err;//����ۼ�ֵ = ��ǰ����ۼƺ�
	//ʹ��PID���� ��� = Kp*��ǰ���  +  Ki*����ۼ�ֵ + Kd*(��ǰ���-�ϴ����)
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
	//�����ϴ����: �����ֵ���ϴ����
	pid->err_last = pid->err;

	return pid->actual_val;
}

float A_PID_realize(APid*pid,float actual_val)
{
	pid->A_actual_val = actual_val;//������ʵֵ
	pid->A_err=pid->A_target_val-pid->A_actual_val;//��ǰ���=Ŀ��ֵ-��ʵֵ
	if(pid->A_err>=180)
	{
		pid->A_err=180;
	}
	pid->A_err_sum+=pid->A_err;
	pid->A_actual_val = pid->A_Kp*pid->A_err + pid->A_Ki*pid->A_err_sum + pid->A_Kd*(pid->A_err - pid->A_err_last);
	pid->A_err_last = pid->A_err;

	return pid->A_actual_val;
}	

