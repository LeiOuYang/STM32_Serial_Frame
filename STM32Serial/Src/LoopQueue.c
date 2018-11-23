#include "LoopQueue.h"

#include "FreeRTOS.h"
#include "task.h"

/* init the loop queue */
unsigned char init_loop_queue(LoopQueue* plp, DATA_TYPE* p_data, unsigned int len) 
{
	unsigned int i = 0;
	
	if((void*)0==plp || 0==len || (void*)0==p_data) return 0;
	
	plp->insert_index = 0;
	plp->read_index = 0;
	plp->count = 0;
	plp->max_len = len;
	plp->buffer = p_data;
	
	for( i=0; i<plp->max_len; ++i )
	{
		plp->buffer[i] = 0;
	}
	
	return 1;
}

/* insert a data to loop queue */ 
unsigned char insert_element_loop_queue(LoopQueue* plp, DATA_TYPE ele)
{
	if((void*)0==plp) return 0;
	
	if(0==space_loop_queue(plp)) return 0;
	
	if(plp->insert_index>=plp->max_len)
		plp->insert_index = 0;
	
	plp->buffer[plp->insert_index] = ele;
	
	++plp->insert_index;  		/* the next data buffer index */ 
	
	taskDISABLE_INTERRUPTS();
	++plp->count;  		        /* wait process data count */
	taskENABLE_INTERRUPTS();
	
	//if(plp->count >= plp->max_len)  plp->count = plp->max_len;
	
	return 1;
}

/* read a data from loop queue */ 
DATA_TYPE read_element_loop_queue(LoopQueue* plp)
{
	DATA_TYPE ele;
	
	if((void*)0==plp) return 0;
	
	//if( 0==plp->count ) return 0;	
	
	if(plp->read_index>=plp->max_len)
		plp->read_index = 0;

	ele = plp->buffer[plp->read_index];
	
	++plp->read_index;
	
	taskDISABLE_INTERRUPTS();
	--plp->count;
	taskENABLE_INTERRUPTS();
	
	return ele;
}

/* clear the loop queue */
unsigned char clean_loop_queue(LoopQueue* plp) 
{
	if((void*)0==plp) return 0;
	
	plp->insert_index = 0;
	plp->read_index = 0;
	plp->count = 0;
	
	return 1;
}

/* return valid data count */ 
unsigned int count_loop_queue(LoopQueue* plp)
{
	if((void*)0==plp) return 0;
	
	return plp->count;
}

/* return queue space */ 
unsigned int space_loop_queue(LoopQueue* plp)
{
	if((void*)0==plp) return 0;
	
	if(plp->count>=plp->max_len) return 0;
	
	return (plp->max_len - plp->count);
}

