/* 
 * File:   debugQueue.h
 * Author: andrew
 *
 * Created on January 13, 2013, 2:48 PM
 */
#include "GenericTypeDefs.h"

#ifndef DEBUGQUEUE_H
#define	DEBUGQUEUE_H







// defines
#define             DEBUG_FIFO_SIZE 10

// Function Prototypes
void initQueue();
void addToQueue(char *msg);
char* getQueueItem();
void str2ram(static char *dest, static char rom *src);
BOOL debugQueueHasItems();









#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DEBUGQUEUE_H */




