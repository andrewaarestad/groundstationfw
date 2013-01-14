
#include "debugQueue.h"



// Global variables
//static const rom char* debugFifoBuffer[DEBUG_FIFO_SIZE];
int debugFifoBuffer[DEBUG_FIFO_SIZE];
char debugFifoBytes[DEBUG_FIFO_SIZE];

int debugFifoNumItemsInQueue;


void initQueue()
{
    debugFifoNumItemsInQueue = 0;
}


void addToQueue(static const rom char *msg)
{
    int length;
    char myChar;

    //char ramString[80];
    //int ramStringPointer;

    int pointerSize = sizeof(char*);

    char testString[80] = "ThisIsAString";
    int testPointer = (int)&testString;
    
    //length = strlenpgm(msg);

    length = 0;
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
            debugFifoBuffer[debugFifoNumItemsInQueue] = testPointer;
            //debugFifoBytes[debugFifoNumItemsInQueue] = ramStringPointer;
            debugFifoNumItemsInQueue++;
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

    if (debugFifoNumItemsInQueue > 0)
    {
        debugFifoNumItemsInQueue--;
        return (char*)debugFifoBuffer[debugFifoNumItemsInQueue];
    }
    else
    {
        // Queue empty
        return 0;
    }

}
