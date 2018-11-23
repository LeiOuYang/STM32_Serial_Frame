
#ifndef USER_TASK_H
#define USER_TASK_H
	#include "HardwareConfig.h"
	#include "stm32f1xx_hal.h"
	#include "cmsis_os.h"
	
	static xSemaphoreHandle mutex_usart1_tx;
	static xSemaphoreHandle mutex_usart1_rx;
	static xSemaphoreHandle mutex_usart2_tx;
	static xSemaphoreHandle mutex_usart3_tx;
	
	void app_run(void);   /* 所有任务初始化 */
		
	extern IWDG_HandleTypeDef hiwdg;
	extern UART_HandleTypeDef huart1;
	extern UART_HandleTypeDef huart2;
	extern UART_HandleTypeDef huart3;
	extern TIM_HandleTypeDef htim2;

#endif
