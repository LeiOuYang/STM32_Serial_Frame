
#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

	#include "stm32f1xx_hal.h"
	#include "UsartDriver.h"

	
	/* led io conifg */
	
	#define run_led 0
	#define status_led 1
	
	#define ledAction(led, sta) if(led==run_led)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, sta);else HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, sta);
	
	#define set_run_led() ledAction(run_led, GPIO_PIN_RESET)
	#define reset_run_led() ledAction(run_led, GPIO_PIN_SET)
	
	#define set_status_led() ledAction(status_led, GPIO_PIN_RESET)
	#define reset_status_led() ledAction(status_led, GPIO_PIN_SET)	
		
	/* end led define */
	
	/* RGB1 */
	
	#define RGB1_RLED(sw) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, sw)
	#define RGB1_GLED(sw) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, sw)
	#define RGB1_BLED(sw) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, sw)
	
	#define RGB1_Red() 		{ RGB1_RLED((GPIO_PinState)1); RGB1_GLED((GPIO_PinState)0); RGB1_BLED((GPIO_PinState)0);}
	#define RGB1_Green() 	{ RGB1_RLED((GPIO_PinState)0); RGB1_GLED((GPIO_PinState)1); RGB1_BLED((GPIO_PinState)0);}
	#define RGB1_Blue()		{ RGB1_RLED((GPIO_PinState)0); RGB1_GLED((GPIO_PinState)0); RGB1_BLED((GPIO_PinState)1);}
	#define RGB1_Close()	{ RGB1_RLED((GPIO_PinState)0); RGB1_GLED((GPIO_PinState)0); RGB1_BLED((GPIO_PinState)0);}
	#define RGB1_Yellow()	{ RGB1_RLED((GPIO_PinState)1); RGB1_GLED((GPIO_PinState)1); RGB1_BLED((GPIO_PinState)0);}
	#define RGB1_Purple() { RGB1_RLED((GPIO_PinState)1); RGB1_GLED((GPIO_PinState)1); RGB1_BLED((GPIO_PinState)1);}
	
	/* end RGB1 */
	
	/* RGB2 */
	#define RGB2_RLED(sw) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, sw)
	#define RGB2_GLED(sw) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, sw)
	#define RGB2_BLED(sw) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, sw)
	
	#define RGB2_Red() 		{ RGB2_RLED((GPIO_PinState)1); RGB2_GLED((GPIO_PinState)0); RGB2_BLED((GPIO_PinState)0);}
	#define RGB2_Green() 	{ RGB2_RLED((GPIO_PinState)0); RGB2_GLED((GPIO_PinState)1); RGB2_BLED((GPIO_PinState)0);}
	#define RGB2_Blue()		{ RGB2_RLED((GPIO_PinState)0); RGB2_GLED((GPIO_PinState)0); RGB2_BLED((GPIO_PinState)1);}
	#define RGB2_Close() 	{ RGB2_RLED((GPIO_PinState)0); RGB2_GLED((GPIO_PinState)0); RGB2_BLED((GPIO_PinState)0);}
	#define RGB2_Yellow()	{ RGB2_RLED((GPIO_PinState)1); RGB2_GLED((GPIO_PinState)1); RGB2_BLED((GPIO_PinState)0);}
	#define RGB2_Purple() { RGB2_RLED((GPIO_PinState)1); RGB2_GLED((GPIO_PinState)1); RGB2_BLED((GPIO_PinState)1);}

	/* end RGB2 */
	
	/* beep io config */
	
	#define set_beep() {HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);}
	#define reset_beep() {HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);}	
	
	/* end beep define */	

#endif

