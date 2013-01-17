/********************************************************************************
Software License Agreement

Microchip Technology Inc. ("Microchip") licenses to you the right to use, copy,
modify and distribute the software - including source code - only for use with
Microchip microcontrollers or Microchip digital signal controllers; provided
that no open source or free software is incorporated into the Source Code
without Microchip’s prior written consent in each instance.

The software is owned by Microchip and its licensors, and is protected under
applicable copyright laws.  All rights reserved.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING
BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

********************************************************************************/

#define DEBUGUARTBUFFERED_C

#include "DebugUARTBuffered.h"

#if defined ( DEBUG_UART_AVAILABLE )

    const unsigned char     logCharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    static char             logBuffer[DEBUG_UART_LOG_BUFFER_SIZE];
    static volatile int     logHead;
    static int              logTail;
    static volatile char    logUartBusy;
    static char             logOverflow;

    /****************************************************************************
      ***************************************************************************/

    void DebugUART_InitializeLogging(void)
    {
        logHead = logTail = 0;
        logUartBusy = 0;
        logOverflow = 0;

        DB_UART(MODEbits).BRGH       = 1; // Use high speed baud generator
        DB_UART(MODEbits).STSEL      = 0; // One stop bit
        DB_UART(MODEbits).PDSEL      = 0; // 8 data bits, no parity
        DB_UART(MODEbits).ABAUD      = 0; // Disable auto baud rate
        DB_UART(MODEbits).LPBACK     = 0; // Disable loopback
        DB_UART(MODEbits).WAKE       = 0; // Disable wake up on receive during Sleep mode
        DB_UART(MODEbits).UEN        = 0; // Disable RTS/CTS flow control
        DB_UART(MODEbits).IREN       = 0; // Disable IrDA
        DB_UART(MODEbits).USIDL      = 0; // Continue operation in Idle mode
        DB_UART(MODEbits).UARTEN     = 1; // Enable UART

        DB_UART(BRG)                 = DEBUG_UART_BRG;

        DB_UART(STAbits).UTXEN       = 1; // Enable transmitter.
        DB_UART(STAbits).URXISEL     = 0; // Interrupt on receiving single byte.
        DB_UART(STAbits).UTXISEL0    = 0; // Interrupt when any character is transferred to the Transmit Shift Register
        DB_UART(STAbits).UTXISEL1    = 0; //   (this implies at least one location is empty in the transmit buffer).

        #if defined ( __C30__ )
            _DB_UART(RXIF)               = 0; // clear Rx interrupt flag
            _DB_UART(TXIF)               = 0; // clear Tx interrupt flag
            _DB_UART(RXIP)               = DEBUG_UART_INTERRUPT_PRIORITY;
            _DB_UART(TXIP)               = DEBUG_UART_INTERRUPT_PRIORITY;
        #elif defined ( __PIC32MX__ )
        	INTSetVectorPriority ( INT_VECTOR_UART ( DEBUG_UART ), DEBUG_UART_INTERRUPT_PRIORITY );
        	INTSetVectorSubPriority ( INT_VECTOR_UART ( DEBUG_UART ), DEBUG_UART_INTERRUPT_SUBPRIORITY );
    	    INTClearFlag ( INT_SOURCE_UART_RX ( DEBUG_UART ) );
    	    INTClearFlag ( INT_SOURCE_UART_TX ( DEBUG_UART ) );
        #endif
        
        DB_UART(MODEbits).UARTEN     = 0; // Disable UART
    }

    /****************************************************************************
      ***************************************************************************/

    void DebugUART_PrintString(const char* msg)
    {
        int avail;
        int len = strlen(msg);

        DISABLE_INTERRUPTS();
        // Free space available in the buffer
        avail = DEBUG_UART_LOG_BUFFER_SIZE - 1 - ((logTail - logHead) & DEBUG_UART_LOG_BUFFER_SIZE_MASK);
        ENABLE_INTERRUPTS();
        avail -= 3; // reserve space for the overflow indicator

        if (len > avail)
        {
            if (logOverflow)
                return;
            logOverflow = 1;
            msg = "*\r\n";  // overflow indicator
            len = 3;
        }
        else
        {
            logOverflow = 0;
        }

        if (len > 0)
        {
            if ((DEBUG_UART_LOG_BUFFER_SIZE - logTail) >= len)
            {
                // Whole message can be written at once.
                memcpy(logBuffer + logTail, msg, len);
            }
            else
            {
                // Part of the message is written to the end of the buffer
                // and next part to the begining.

                // Free bytes available from the tail pointer to the end of the buffer
                int avail2 = DEBUG_UART_LOG_BUFFER_SIZE - logTail;
                memcpy(logBuffer + logTail, msg, avail2);
                memcpy(logBuffer, msg + avail2, len - avail2);
            }

            DISABLE_INTERRUPTS();
            logTail = (logTail + len) & DEBUG_UART_LOG_BUFFER_SIZE_MASK;
            if (!logUartBusy)
            {
                logUartBusy = 1;
                DB_UART(TXREG) = logBuffer[logHead];
                logHead = (logHead + 1) & DEBUG_UART_LOG_BUFFER_SIZE_MASK;

                #if defined ( __C30__ )
                    _DB_UART(TXIE) = 1; 
                #elif defined ( __PIC32MX__ )
                    INTEnable ( INT_SOURCE_UART_TX ( DEBUG_UART ), INT_ENABLED );
                #endif
            }
            ENABLE_INTERRUPTS();
        }
    }

    /****************************************************************************
      ***************************************************************************/

    void DebugUART_PutChar ( char c )
    {
        char buffer[2];

        buffer[0] = c;
        buffer[1] = 0;

        DebugUART_PrintString ( buffer );
    }

    /****************************************************************************
      ***************************************************************************/

    void DebugUART_PutHex ( int x )
    {
        char    buffer[3];
        int     printVar;

        printVar = x;
        x = (x >> 4) & 0x0F;
        buffer[0] = logCharacterArray[x];

        x = printVar & 0x0F;
        buffer[1] = logCharacterArray[x];

        buffer[2] = 0;

        DebugUART_PrintString ( buffer );
    }

    /****************************************************************************
      ***************************************************************************/

    void DebugUART_StartLogging(void)
    {
        DB_UART(MODEbits).UARTEN     = 1;  // Enable UART
        DB_UART(STAbits).UTXEN       = 1;  // Enable transmitter
    }

    /****************************************************************************
      ***************************************************************************/

    #if defined ( __C30__ )
    void __attribute__((interrupt, no_auto_psv)) _DB_UART(TXInterrupt)(void)
    #elif defined ( __PIC32MX__ )
    void __attribute((interrupt(DEBUG_UART_IPL), vector(DEBUG_UART_INTERRUPT_VECTOR), nomips16)) DEBUG_UART_ISR( void )
    #endif
    {
        if (logHead != logTail)
        {
            DB_UART(TXREG) = logBuffer[logHead];
            logHead = (logHead + 1) & DEBUG_UART_LOG_BUFFER_SIZE_MASK;
        }
        else
        {
            logUartBusy = 0;

            #if defined( __C30__ )
                _DB_UART(TXIE) = 0;
            #elif defined( __PIC32MX__ )
                INTEnable ( INT_SOURCE_UART_TX ( DEBUG_UART ), INT_DISABLED );
            #endif
        }

        #if defined ( __C30__ )
            _DB_UART(TXIF) = 0; // clear Tx interrupt flag
        #elif defined ( __PIC32MX__ )
            INTClearFlag ( INT_SOURCE_UART_TX ( DEBUG_UART ) );
        #endif
    }

#else

    void DebugUART_InitializeLogging ( void ) {}
    void DebugUART_PrintString ( const char* msg ) 
    {
        //putrs2USART(msg);
    }
    void DebugUART_PutChar ( char c ) {}
    void DebugUART_PutHex ( int x ) {}
    void DebugUART_StartLogging ( void ) {}

#endif
