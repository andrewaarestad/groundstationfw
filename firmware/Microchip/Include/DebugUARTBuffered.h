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

#ifndef DEBUGUARTBUFFERED_H
#define DEBUGUARTBUFFERED_H

////////////////////////////////////////////////////////////////////////////////
// Common

//******************************************************************************
// Section: Includes
//******************************************************************************

#include "Compiler.h"
#include "GenericTypedefs.h"
#include "HardwareProfile.h"


#ifdef DEBUGUARTBUFFERED_C

    ////////////////////////////////////////////////////////////////////////////////
    // Private

    //******************************************************************************
    // Section: Constants
    //******************************************************************************

    #define DEBUG_UART_LOG_BUFFER_SIZE_MASK   (DEBUG_UART_LOG_BUFFER_SIZE - 1)


    //******************************************************************************
    // Section: Internal Macros
    //******************************************************************************

    // Macros for accessing debug UART registers
    #define DB_UART(reg)            CONCAT3(U, DEBUG_UART_NUMBER, reg)
    #define _DB_UART(reg)           CONCAT3(_U, DEBUG_UART_NUMBER, reg)

    // Helper macros
    #define CONCAT2(t1, t2)         _CONCAT2_(t1, t2)
    #define _CONCAT2_(t1, t2)       t1##t2
    #define CONCAT3(t1, t2, t3)     _CONCAT3_(t1, t2, t3)
    #define _CONCAT3_(t1, t2, t3)   t1##t2##t3

    #if defined ( __C30__ )

        #define DISABLE_INTERRUPTS() __builtin_disi(0x3FFF)
        #define ENABLE_INTERRUPTS()  __builtin_disi(0x0000)

    #elif defined ( __PIC32MX__ )

        #define DISABLE_INTERRUPTS() asm volatile ( "di" )
        #define ENABLE_INTERRUPTS()  asm volatile ( "ei" )

    #endif

#else

    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif

////////////////////////////////////////////////////////////////////////////////
// Common

void DebugUART_InitializeLogging ( void );
void DebugUART_PrintString ( const char* msg );
void DebugUART_PutChar ( char c );
void DebugUART_PutHex ( int x );
void DebugUART_StartLogging ( void );

#endif

