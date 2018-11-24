/********************* STM32_Serial_Frame *************************	

	项目基于STM32F103C8T6芯片，可移植到其他芯片中。

	项目基于FreeRTOS和STM32 CubeMX工具包，其中有修改stm32f1xx_hal_uart.c(文件在根目录下)文件，针对STM32CUBEMX工具自动生成的代码，只需将\Drivers\STM32F1xx_HAL_Driver\Src中的同名文件替换即可。

	项目中采用循环队列方式存储收发数据，队列空间大小可在UsartDriver.c中进行修改。

	项目代码可免费使用。

	如有Bug，望反馈交流（QQ：2281280195）。

	用户代码在文件 /src/UserTask.c， 用户可针对修改

	作者：Awesome

	时间： 2018-11-23
****************************************************************/


#include "UserTask.h"

#define DEBUG 1   /* 选择打开Debug调试模式  串口接收数据->将数据返回 */

/* 任务函数和静态函数声明 */
static void init_system(void);
static void restart_usart(UART_HandleTypeDef *huart);
/* 任务函数 */
static void initUsartIT(UART_HandleTypeDef *huart);
static void usart1_send_task(void const* arg);
static void usart1_receive_task(void const* arg);
static void usart2_send_task(void const* arg);
static void usart2_receive_task(void const* arg);
static void usart3_receive_task(void const* arg);
static void usart3_send_task(void const* arg);

static void task_50ms(void const* arg);
static void run_led_fun(void);
static void feed_dog_fun(void);
static void beep_fun(void);
/* 结束函数声明 */

void app_run(void)
{
	init_system();
	
	/* 喂狗、系统运行灯控制任务  50ms调用一次 */
	osThreadDef(Task50MSThread, task_50ms, osPriorityIdle, 0, 128);
	osThreadCreate(osThread(Task50MSThread), NULL);	
	
	/* 串口1接收数据处理任务 */
	osThreadDef(UART1RXTask, usart1_receive_task, osPriorityRealtime, 0, 512);
	osThreadCreate(osThread(UART1RXTask), NULL);
	
	/* 串口2接收数据处理任务 */
	osThreadDef(UART2RXTask, usart2_receive_task, osPriorityLow, 0, 512);
	osThreadCreate(osThread(UART2RXTask), NULL);
	
	/* 串口3接收数据处理任务 */
	osThreadDef(UART3RXTask, usart3_receive_task, osPriorityHigh, 0, 512);
	osThreadCreate(osThread(UART3RXTask), NULL);
	
	/* 串口1发送数据处理任务 */
	osThreadDef(UART1TXTask, usart1_send_task, osPriorityBelowNormal, 0, 256);
	osThreadCreate(osThread(UART1TXTask), NULL);
	
	/* 串口2发送数据处理任务 */
	osThreadDef(UART2TXTask, usart2_send_task, osPriorityNormal, 0, 256);
	osThreadCreate(osThread(UART2TXTask), NULL);
	
	/* 串口3发送数据处理任务 */
	osThreadDef(UART3TXTask, usart3_send_task, osPriorityLow, 0, 256);
	osThreadCreate(osThread(UART3TXTask), NULL);
	
}

/* function code end */

/* 串口1接收处理任务 */
static void usart1_receive_task(void const* arg)
{
	unsigned int data_len = 0;
	unsigned int i = 0;
	char data = 0;
	
	while(1)
	{
		/* 10ms 115200全速模式下为144个字节	*/
		osDelay(10);
		
		restart_usart(&huart1);
		
		data_len = readBuffLen(USART1_ID); /* 读取串口1缓冲队列中的数据长度 */
		if(data_len>0)
		{
			for( i=0; i<data_len; ++i )
			{
				data = read_char(USART1_ID);
				
				#if DEBUG
					write_char(USART1_ID, data);
				#endif
			}
		}
	}
}
/* function code end */

/* 串口1发送任务 */
static void usart1_send_task(void const* arg)
{
	uint16_t data_len = 0;
	LoopQueue* sendQueue;
	unsigned int i = 0;
	char send_buff[200];
	TickType_t old_time = 0;
	old_time = xTaskGetTickCount();
	
	while(1)
	{
		osDelay(10);	
		
		while(huart1.gState==HAL_UART_STATE_BUSY_TX && xTaskGetTickCount()-old_time<=3);
		
		sendQueue = getUsartSendLoopQueue(USART1_ID); /* get send queue */
		if(sendQueue!=NULL)
		{	
			data_len = writeBuffLen(USART1_ID); /* send queue data count */
			
			if(data_len>0)
			{
				if(data_len>=200) data_len = 200;
				
				for( i=0; i<data_len; ++i)
				{
					send_buff[i] = read_element_loop_queue(sendQueue);
				}				
				
				HAL_UART_Transmit_DMA(&huart1, (uint8_t *)send_buff, (uint16_t)data_len); /* DMA send	*/
			}
		}			
	}
}
/* function code end */

/* 串口2接收处理任务 */
static void usart2_receive_task(void const* arg)
{
	unsigned int data_len = 0;
	unsigned int i = 0;
	char data = 0;
	
	while(1)
	{
		/* 10ms 115200全速模式下为144个字节	*/
		osDelay(10);
		
		restart_usart(&huart2);
		data_len = readBuffLen(USART2_ID); /* 读取串口1缓冲队列中的数据长度 */
		if(data_len>0)
		{
			for( i=0; i<data_len; ++i )
			{
				data = read_char(USART2_ID);
				
				#if DEBUG
					write_char(USART2_ID, data);
				#endif
			}
		}
	}
}
/* function code end */

/* 串口2发送任务 */
static void usart2_send_task(void const* arg)
{
	uint16_t data_len = 0;
	LoopQueue* sendQueue;
	unsigned int i = 0;
	char send_buff[160];
	TickType_t old_time = 0;
	old_time = xTaskGetTickCount();
	
	while(1)
	{
		osDelay(10);	
		
		while(huart2.gState==HAL_UART_STATE_BUSY_TX && xTaskGetTickCount()-old_time<=3);
			
		sendQueue = getUsartSendLoopQueue(USART2_ID); /* get send queue */
		if(sendQueue!=NULL)
		{		
			data_len = writeBuffLen(USART2_ID); /* send queue data count */
			if(data_len>0)
			{
				if(data_len>=160) data_len=160;
				
				for( i=0; i<data_len; ++i)
				{
					send_buff[i] = read_element_loop_queue(sendQueue);
				}
				
				HAL_UART_Transmit_DMA(&huart2, (uint8_t *)send_buff, (uint16_t)data_len); /* DMA send	*/
			}
		}			
	}
}
/* function code end */

/* 串口3接收处理任务 */
static void usart3_receive_task(void const* arg)
{
	unsigned int data_len = 0;
	unsigned int i = 0;
	char data = 0;
	
	while(1)
	{
		/* 10ms 115200全速模式下为144个字节	*/
		osDelay(10);
		
		restart_usart(&huart3);
		
		data_len = readBuffLen(USART3_ID); /* 读取串口1缓冲队列中的数据长度 */
		if(data_len>0)
		{
			for( i=0; i<data_len; ++i )
			{
				data = read_char(USART3_ID);
				
				#if DEBUG
					write_char(USART3_ID, data);
				#endif
			}
		}
	}
}
/* function code end */

/* 串口3发送任务 */
static void usart3_send_task(void const* arg)
{
	uint16_t data_len = 0;
	LoopQueue* sendQueue;
	char send_buff[160];
	TickType_t old_time = 0;
	old_time = xTaskGetTickCount();
	
	while(1)
	{
		osDelay(10);	
		
		while( huart3.gState==HAL_UART_STATE_BUSY_TX  && xTaskGetTickCount()-old_time<=3 );	
		
		sendQueue = getUsartSendLoopQueue(USART3_ID); /* get send queue */
		if(sendQueue!=NULL)
		{		
			data_len = writeBuffLen(USART3_ID); /* send queue data count */
			if(data_len>0)
			{
				unsigned int i = 0;
				if(data_len>=160) data_len=160;
				for( i=0; i<data_len; ++i)
				{
					send_buff[i] = read_element_loop_queue(sendQueue);
				}
				
				HAL_UART_Transmit_DMA(&huart3, (uint8_t *)send_buff, (uint16_t)data_len); /* DMA send	*/
			}
		}			
	}
}
/* function code end */



/* 每50ms调用一次任务： LED、BEEP和喂狗操作 */
static void task_50ms(void const* arg)
{
	while(1)
	{
		osDelay(50);
		
		run_led_fun();
		beep_fun();
		feed_dog_fun();
	}
}
/* end the function */

/* 初始化系统函数 */
static void init_system(void)
{
	initUsartBuff(USART1_ID);
	initUsartBuff(USART2_ID);
	initUsartBuff(USART3_ID);

	mutex_usart1_tx = xSemaphoreCreateMutex();
	mutex_usart2_tx = xSemaphoreCreateMutex();
	mutex_usart3_tx =  xSemaphoreCreateMutex();
	
	mutex_usart1_rx = xSemaphoreCreateMutex();
		
	initUsartIT(&huart1);
	initUsartIT(&huart2);
	initUsartIT(&huart3);
	
	write(USART1_ID, "USART1 ENBALE\n", sizeof("USART1 ENBALE\n")/sizeof(char));
	write(USART2_ID, "USART2 ENBALE\n", sizeof("USART2 ENBALE\n")/sizeof(char));
	write(USART3_ID, "USART3 ENBALE\n", sizeof("USART3 ENBALE\n")/sizeof(char));
}
/* function code end */

static void restart_usart(UART_HandleTypeDef *huart)
{
	if(huart==0) return;
	
	if((huart->ErrorCode |= HAL_UART_ERROR_ORE)!=RESET)
	{
		huart->ErrorCode = HAL_UART_ERROR_NONE;
		huart->RxState = HAL_UART_STATE_BUSY_RX;
		
		//SET_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
		//SET_BIT(huart->Instance->CR3, USART_CR3_EIE);

		/* Process Unlocked */
		__HAL_UNLOCK(huart);

		/* Enable the UART Parity Error Interrupt */
		__HAL_UART_ENABLE_IT(huart, UART_IT_PE);

		/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
		__HAL_UART_ENABLE_IT(huart, UART_IT_ERR);

		/* Enable the UART Data Register not empty Interrupt */
		__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
		return;
	}
}

/* 初始化串口接收中断 */
static void initUsartIT(UART_HandleTypeDef *huart)
{
		huart->ErrorCode = HAL_UART_ERROR_NONE;
		huart->RxState = HAL_UART_STATE_BUSY_RX;
			/* Process Unlocked */
		__HAL_UNLOCK(huart);

		/* Enable the UART Parity Error Interrupt */
		__HAL_UART_ENABLE_IT(huart, UART_IT_PE);

		/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
		__HAL_UART_ENABLE_IT(huart, UART_IT_ERR);

		/* Enable the UART Data Register not empty Interrupt */
		__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}

/* led 控制函数 50ms任务 */
static void run_led_fun(void)
{
	static unsigned int step = 0;
	
	++step;
	
	if(step<=20)
	{
		set_run_led();
	}else if(step<=40)
	{
		reset_run_led();
	}else
	{
		step = 0;
	}
	
}

static void feed_dog_fun(void)
{
	static unsigned int step = 0;
	
	++step;
	
	if(2==step)
	{
		step = 0;
		HAL_IWDG_Refresh(&hiwdg);
	}
	
}

static void beep_fun(void)
{
	//static unsigned int step = 0;

}
