#ifndef TB6612_H_
#define TB6612_H_

#include "main.h"

#define AIN1_RESET  HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);//设置AIN1 PB13为 低电平
#define AIN1_SET    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平
#define AIN2_RESET  HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);//设置AIN1 PB13为 低电平
#define AIN2_SET    HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平

#define BIN1_RESET 	HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);  //设置BIN1 PB3为低电平
#define BIN1_SET    HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平
#define BIN2_RESET 	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);  //设置BIN1 PB3为低电平
#define BIN2_SET    HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平

#define CIN1_RESET  HAL_GPIO_WritePin(CIN1_GPIO_Port,CIN1_Pin,GPIO_PIN_RESET);//设置AIN1 PB13为 低电平
#define CIN1_SET    HAL_GPIO_WritePin(CIN1_GPIO_Port,CIN1_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平
#define CIN2_RESET  HAL_GPIO_WritePin(CIN2_GPIO_Port,CIN2_Pin,GPIO_PIN_RESET);//设置AIN1 PB13为 低电平
#define CIN2_SET    HAL_GPIO_WritePin(CIN2_GPIO_Port,CIN2_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平

#define DIN1_RESET 	HAL_GPIO_WritePin(DIN1_GPIO_Port,DIN1_Pin,GPIO_PIN_RESET);  //设置BIN1 PB3为低电平
#define DIN1_SET    HAL_GPIO_WritePin(DIN1_GPIO_Port,DIN1_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平
#define DIN2_RESET 	HAL_GPIO_WritePin(DIN2_GPIO_Port,DIN2_Pin,GPIO_PIN_RESET);  //设置BIN1 PB3为低电平
#define DIN2_SET    HAL_GPIO_WritePin(DIN2_GPIO_Port,DIN2_Pin,GPIO_PIN_SET);//设置AIN1 PB13为 高电平


void Motor_Set2 (int motorC,int motorD);
void Motor_Set4 (int motorD,int motorB,int motorC,int motorA);
void motorPidSetSpeed2(float Motor4SetSpeed,float Motor3SetSpeed);
void motorPidSetSpeed4(float Motor1SetSpeed,float Motor2SetSpeed,float Motor3SetSpeed,float Motor4SetSpeed);
void motorPidSetStup2(int Angle4,int Angle3);
void motorPidSetStup_Speed2(void);
#endif


