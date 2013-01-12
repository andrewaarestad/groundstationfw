/******************************************************************************

File Name:       MCP9800.h
Dependencies:    None
Processor:       PIC18, PIC24/dsPIC, PIC32
Company:         Microchip Technology, Inc.

Copyright ? 2009-2010 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*******************************************************************************/

#ifndef MCP9800_H
#define MCP9800_H

////////////////////////////////////////////////////////////////////////////////
// Common

#include "system.h"
#include "main.h"

////////////////////////////////////////////////////////////////////////////////

#ifdef MCP9800_C

    ////////////////////////////////////////////////////////////////////////////////
    // Private

    // *****************************************************************************
    // Section: Constants
    // *****************************************************************************

    //------------------------------------------------------------------------------
    // MCP9800 Temperature Sensor Constants

    #define MCP9800_ADDRESS_READ                0x91
    #define MCP9800_ADDRESS_WRITE               0x90
    #define MCP9800_MAX_I2C_FREQUENCY           400000
    #define MCP9800_SUCCESS                     0
    #define MCP9800_TEMPERATURE                 0x00

    // *****************************************************************************
    // Section: Data Structures and Enumerations
    // *****************************************************************************

    // *****************************************************************************
    /* MCP9800 I2C Temperature Read States

    These states are used in the state machine that reads the temperature from
    the MCP9800.
    */
    typedef enum {
        TEMPERATURE_READ_WAIT                   = 0,
        TEMPERATURE_READ_START,
        TEMPERATURE_READ_SEND_CHIP_ADDRESS,
        TEMPERATURE_READ_SEND_REGISTER_ADDRESS,
        TEMPERATURE_READ_REPEAT_START,
        TEMPERATURE_READ_SEND_READ_ADDRESS,
        TEMPERATURE_READ_RECEIVE_HIGH_BYTE,
        TEMPERATURE_READ_GET_HIGH_BYTE,
        TEMPERATURE_READ_RECEIVE_LOW_BYTE,
        TEMPERATURE_READ_GET_LOW_BYTE,
        TEMPERATURE_READ_STOP,
        TEMPERATURE_READ_COMPLETE
    } TEMPERATURE_READ_STATES;


#else
    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif


// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************

UINT8       MCP9800_Initialize ( I2C_MODULE selectedI2C );
void        MCP9800_StartRead( void );
void        MCP9800_Tasks ( INTERFACE_DATA *interfaceData );


#endif
