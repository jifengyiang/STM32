#include "pid.h"
#include "stdbool.h"

extern bool motor_Angle;
int ERRO=0;

tPid pid1_speed;//电机1的转速控制
tPid pid2_speed;//电机2的转速控制
tPid pid3_speed;//电机3的转速控制
tPid pid4_speed;//电机4的转速控制

APid pid3_Angle;//电机3的角度控制
APid pid4_Angle;//电机4的角度控制
//给结构体类型变量赋初值
void PID_init()
{
/**********速度环pid****************/
pid1_speed.actual_val=0.0;//初始化电机1转速PID 结构体
pid1_speed.target_val=0.0;
pid1_speed.err=0.0;
pid1_speed.err_last=0.0;
pid1_speed.err_sum=0.0;
pid1_speed.Kp=50;			//23
pid1_speed.Ki=5.0;			//15
pid1_speed.Kd=0.0;
	
pid2_speed.actual_val=0.0;//初始化电机2转速PID 结构体
pid2_speed.target_val=0.0;
pid2_speed.err=0.0;
pid2_speed.err_last=0.0;
pid2_speed.err_sum=0.0;
pid2_speed.Kp=50;				//35
pid2_speed.Ki=5;				//18
pid2_speed.Kd=0.0;
	
pid3_speed.actual_val=0.0;//初始化电机1转速PID 结构体
pid3_speed.target_val=0.0;
pid3_speed.err=0.0;
pid3_speed.err_last=0.0;
pid3_speed.err_sum=0.0;
pid3_speed.Kp=50;			//23
pid3_speed.Ki=2.5;			//15
pid3_speed.Kd=0.0;

pid4_speed.actual_val=0.0;//初始化电机2转速PID 结构体
pid4_speed.target_val=0.0;
pid4_speed.err=0.0;
pid4_speed.err_last=0.0;
pid4_speed.err_sum=0.0;
pid4_speed.Kp=50;				//35
pid4_speed.Ki=3;				//18
pid4_speed.Kd=0.0;	

/**********位置环pid****************/
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
//比例p调节控制函数
float P_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//传递真实值
	pid->err = pid->target_val - pid->actual_val;//目标值减去实际值等于误差值
	//比例控制调节
	pid->actual_val = pid->Kp*pid->err;
	return pid->actual_val;
}
//比例P 积分I 控制函数
float PI_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//传递真实值
	pid->err = pid->target_val - pid->actual_val;//当前误差=目标值-真实值
	pid->err_sum += pid->err;//误差累计值 = 当前误差累计和
	//使用PI控制 输出=Kp*当前误差+Ki*误差累计值
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum;
	
	return pid->actual_val;
}
// PID控制函数
float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//传递真实值
	pid->err = pid->target_val - pid->actual_val;////当前误差=目标值-真实值
	pid->err_sum += pid->err;//误差累计值 = 当前误差累计和
	//使用PID控制 输出 = Kp*当前误差  +  Ki*误差累计值 + Kd*(当前误差-上次误差)
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
	//保存上次误差: 这次误差赋值给上次误差
	pid->err_last = pid->err;

	return pid->actual_val;
}

float A_PID_realize(APid*pid,float actual_val)
{
	pid->A_actual_val = actual_val;//传递真实值
	pid->A_err=pid->A_target_val-pid->A_actual_val;//当前误差=目标值-真实值
	if(pid->A_err>=180)
	{
		pid->A_err=180;
	}
	pid->A_err_sum+=pid->A_err;
	pid->A_actual_val = pid->A_Kp*pid->A_err + pid->A_Ki*pid->A_err_sum + pid->A_Kd*(pid->A_err - pid->A_err_last);
	pid->A_err_last = pid->A_err;

	return pid->A_actual_val;
}	

