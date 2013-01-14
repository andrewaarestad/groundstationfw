
#include "debugQueue.h"



// Global variables
//static const rom char* debugFifoBuffer[DEBUG_FIFO_SIZE];
int debugFifoBuffer[DEBUG_FIFO_SIZE];
char debugFifoBytes[DEBUG_FIFO_SIZE];

int debugFifoNumItemsInQueue;

char testString[80] = "ThisIsAString";

void initQueue()
{
    debugFifoNumItemsInQueue = 0;
}


void addToQueue(char *msg)
{
    //int length;
    //char myChar;

    //char ramString[80];
    //int ramStringPointer;

    //int pointerSize = sizeof(char*);

    
    int msgPointer = (int)msg;
    
    //length = strlenpgm(msg);

    
    //puts2USART((char*)testPointer);

    //length = 0;
    if (msg)
    {
        //str2ram(ramString,msg);
        //ramStringPointer = (int)&ramString;
        //do
        //{
        //    myChar = *msg;
        //    length++;
        //}
        //while (*msg++);
        

            if (debugFifoNumItemsInQueue < DEBUG_FIFO_SIZE)
        {
            debugFifoBuffer[debugFifoNumItemsInQueue] = msgPointer;
            //debugFifoBytes[debugFifoNumItemsInQueue] = ramStringPointer;
            debugFifoNumItemsInQueue++;
            //puts2USART((char*)debugFifoBuffer[debugFifoNumItemsInQueue-1]);
        }
        else
        {
            // Queue full!  Message gets dropped on the floor.
        }
    }
}

void str2ram(static char *dest, static char rom *src)
{
    while((*dest++ = *src++) != '\0');
}


char* getQueueItem()
{
    // FIXME: This is currently implemented as a LIFO - prefer a FIFO
    //char* returnVal;
    //putrs2USART("getQueueItem: ");
    if (debugFifoNumItemsInQueue > 0)
    {
        debugFifoNumItemsInQueue--;
        //returnVal = (char*)debugFifoBuffer[debugFifoNumItemsInQueue];
        
        //puts2USART(returnVal);
        //debugFifoBuffer[debugFifoNumItemsInQueue] = 0;
        return (char*)debugFifoBuffer[debugFifoNumItemsInQueue];
    }
    else
    {
        // Queue empty
        //putrs2USART("Queue empty");
        return 0;
    }

}
