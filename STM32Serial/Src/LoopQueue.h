#ifndef LOOP_QUEUE_H
#define LOOP_QUEUE_H

typedef char DATA_TYPE;

typedef struct _loop_queue
{
	DATA_TYPE* buffer;
	unsigned int max_len;
	volatile unsigned int insert_index;
	volatile unsigned int read_index;
	volatile unsigned int count;
}LoopQueue;

unsigned char init_loop_queue(LoopQueue* plp, DATA_TYPE* p_data, unsigned int max_len);  /* init the queue,point the buffer and data len */
unsigned char insert_element_loop_queue(LoopQueue* plp, DATA_TYPE ele);  /* insert a data to queue */ 
DATA_TYPE read_element_loop_queue(LoopQueue* plp);  /* read a data from queue */ 


unsigned char clean_loop_queue(LoopQueue* plp);     /* cean the queue */ 
unsigned int count_loop_queue(LoopQueue* plp);		/* read the queue the count of data */ 
unsigned int space_loop_queue(LoopQueue* plp);      /* return the queue the space of buffer, max_len-count */ 

#endif 
