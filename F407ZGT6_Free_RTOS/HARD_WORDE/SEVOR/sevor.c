#include "sevor.h"

float time_pwm=0;
void sevor_1_angle(float angle)
{
	
	time_pwm=((100*angle/9)+500);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,time_pwm);//angle業

}

void sevor_2_angle(float angle)
{
	
	time_pwm=((100*angle/9)+500);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,time_pwm);//angle業

}
void sevor_3_angle(float angle)
{
	
	time_pwm=((100*angle/9)+500);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,time_pwm);//angle業

}
void sevor_4_angle(float angle)
{
	
	time_pwm=((100*angle/9)+500);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,time_pwm);//angle業

}



