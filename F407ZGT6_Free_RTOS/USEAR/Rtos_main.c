/*2024年9月10日 A-ha master_frist*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "rtos_main.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "motor.h"
#include "oled.h"
#include "TB6612.h"
#include "pid.h"
#include "lcd.h"
#include "test.h"
#include "gui.h"
#include "pic.h"
#include "mpu6050.h" 
#include "imu.h"
#include "sevor.h"

/*****************************************************************************

START_TASK_PRIO 0~15	数字越大任务优先级越高

*****************************************************************************/
int  i=0;

extern float Angle_2;

extern float Motor1Speed ;
extern float Motor2Speed ;
extern float Motor3Speed ;
extern float Motor4Speed ;

extern int Motor3Angle;
extern int Motor4Angle;

extern int num ;
extern int ERRO;

extern uint16_t SUPT_X;
extern uint16_t SUPT_Y;
extern uint16_t SUPT_Z;

extern uint16_t STEP_X;
extern uint16_t STEP_Y;
extern uint16_t STEP_Z;

extern float pitch,roll,yaw; // 俯仰角 横滚角 航向角

//int DIRZ;

//任务优先级
#define START_TASK_PRIO		0
//任务堆栈大小	
#define START_TSTK_SIZE 		128
//任务句柄
TaskHandle_t STARTTask_Handler;
//任务函数
void start_init(void);

//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

//任务优先级
#define OLED_TASK_PRIO		3
//任务堆栈大小	
#define OLED_STK_SIZE 		128  
//任务句柄
TaskHandle_t OLEDTask_Handler;
//任务函数
void oled_task(void *pvParameters);

//任务优先级
#define LCD_TASK_PRIO		1
//任务堆栈大小	
#define LCD_STK_SIZE 		128  
//任务句柄
TaskHandle_t LCDTask_Handler;
//任务函数
void lcd_task(void *pvParameters);

//任务优先级
#define XJ_TASK_PRIO		5
//任务堆栈大小	
#define XJ_STK_SIZE 		128  
//任务句柄
TaskHandle_t XJTask_Handler;
//任务函数
void xj_task(void *pvParameters);

//任务优先级
#define GPY_TASK_PRIO		4
//任务堆栈大小	
#define GPY_STK_SIZE 		128
//任务句柄
TaskHandle_t GPYTask_Handler;
//任务函数
void gpy_task(void *pvParameters);

//任务优先级
#define KEY_TASK_PRIO		3
//任务堆栈大小	
#define KEY_STK_SIZE 		128
//任务句柄
TaskHandle_t KEYTask_Handler;
//任务函数
void key_task(void *pvParameters);

void start_init(void)
{
	 taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);
		
		xTaskCreate((TaskFunction_t )oled_task,     	
                (const char*    )"oled_task",   	
                (uint16_t       )OLED_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )OLED_TASK_PRIO,	
                (TaskHandle_t*  )&OLEDTask_Handler);
								
		xTaskCreate((TaskFunction_t )lcd_task,     	
                (const char*    )"lcd_task",   	
                (uint16_t       )LCD_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LCD_TASK_PRIO,	
                (TaskHandle_t*  )&LCDTask_Handler);
								
		xTaskCreate((TaskFunction_t )xj_task,     	
                (const char*    )"xj_task",   	
                (uint16_t       )XJ_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )XJ_TASK_PRIO,	
                (TaskHandle_t*  )&XJTask_Handler);
		xTaskCreate((TaskFunction_t )gpy_task,     	
                (const char*    )"gpy_task",   	
                (uint16_t       )GPY_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )GPY_TASK_PRIO,	
                (TaskHandle_t*  )&GPYTask_Handler);
								
		xTaskCreate((TaskFunction_t )key_task,     	
                (const char*    )"key_task",   	
                (uint16_t       )KEY_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )KEY_TASK_PRIO,	
                (TaskHandle_t*  )&KEYTask_Handler);
								
    taskEXIT_CRITICAL();            //退出临界区
}

/********************************
LED一秒钟反转闪烁任务
********************************/
void led0_task(void *pvParameters)
{

    while(1)
    {
      HAL_GPIO_TogglePin(GPIOD ,GPIO_PIN_14);
			printf("angle_2:%f\r\n",Angle_2);
			vTaskDelay(2000);
    }
}   

/********************************
OLED刷新任务
********************************/
void oled_task(void *pvParameters)
{
    while(1)
   {
		 i++;
		OLED_operate_gram(PEN_CLEAR);//清缓存
		OLED_show_string(0,0,"time:");
		OLED_show_string(1,0,"yaw:");
		OLED_show_string(2,0,"S_L:");
		OLED_show_string(2,10,"S_R:");
		OLED_show_string(3,0,"A_L:");
		OLED_show_string(3,10,"A_R:");
		 if(yaw>=0)
		 {	 
			OLED_show_string(1,5,"+:");
			OLED_show_num(1,6, yaw, 1,3);
		 }
		 else
		 {
		 OLED_show_string(1,5,"-:");
		 OLED_show_num(1,6,(-yaw), 1,3);
		 }
		OLED_show_num(0,5,i,1,3);
		OLED_show_floatnum(2,4,Motor4Speed,1);
		OLED_show_floatnum(2,14,Motor3Speed,1);  	
		 
		OLED_show_num(3,4,Motor4Angle,1,5);
		OLED_show_num(3,14,Motor3Angle,1,5);	
		OLED_show_floatnum(4,14,Angle_2,1);	
		 	 
		OLED_refresh_gram();//全局刷新
		vTaskDelay(50);
   }
}   

/********************************
LCD显示任务
********************************/
void lcd_task(void *pvParameters)
{
while(1)
	{
//	Gui_Drawbmp128(0,0,gImage_bc);
	vTaskDelay(3000);
}


}   
/********************************
陀螺仪采样任务
********************************/
void gpy_task(void *pvParameters)
{
	while(1)
	{
		MpuGetData();
		GetAngle(&MPU6050,&Angle, 0.003f);
		vTaskDelay(3);
	}

}
/********************************
串口巡线任务
********************************/
void xj_task(void *pvParameters)
{
	while(1)
	{
		if(num==8||num==12||num==10||num==16)motorPidSetSpeed2(1.5,1.5);
		else if(num==64)motorPidSetSpeed2(1.5,0.8);
		else if(num==32||num==48)motorPidSetSpeed2(1.5,1.3);
		else if(num==2||num==6||num==7||num==15||num==14||num==12||num==54)motorPidSetSpeed2(1.3,1.5);
		else if(num==1)motorPidSetSpeed2(0.8,1.5);
		else if(num==9||num==5||num==17||num==33)motorPidSetSpeed2(1,1.5);	    
		vTaskDelay(30);
	}
}   

/********************************
按键扫描任务
********************************/
void key_task(void *pvParameters)
{
	while(1)
	{
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_1)==0)
		{		
			while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_1)==0);
			motorPidSetSpeed2(1.5,1.5);
		}
	else if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==0)
		{		
			while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==0);
			motorPidSetStup2(185,-185);
		}
	else if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0)
		{		
			while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0);
			motorPidSetSpeed2(0,0);
		}
	else if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0)
		{		
			while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0);
			motorPidSetStup2(2000,2000);
		}
		vTaskDelay(100);
	}
}

