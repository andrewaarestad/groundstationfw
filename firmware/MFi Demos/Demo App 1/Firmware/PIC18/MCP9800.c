/******************************************************************************

File Name:       MCP9800.c
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

#define MCP9800_C
#include "MCP9800.h"


// *****************************************************************************
// Section: Macros
// *****************************************************************************

#define I2C_OperationTimeout(t)         ((TickGet() - t) > (2 * dwTicksPerSecond))


// *****************************************************************************
// Section: Global Variables
// *****************************************************************************

I2C_MODULE              MCP9800_I2C;
TEMPERATURE_READ_STATES MCP9800_state;


/****************************************************************************
  Function:
    UINT8       MCP9800_Initialize ( I2C_MODULE selectedI2C )

  Description:
    This function initializes information needed to communicate with the
    MCP9800.

  Precondition:
    None

  Parameters:
    I2C_MODULE selectedI2C - The I2C module to use to talk to the MCP9800.

  Return Values:
    MCP9800_SUCCESS - Initialization was successful.

  Remarks:
    None.
  ***************************************************************************/

UINT8       MCP9800_Initialize ( I2C_MODULE selectedI2C )
{
    MCP9800_I2C     = selectedI2C;
    MCP9800_state   = TEMPERATURE_READ_WAIT;

    return MCP9800_SUCCESS;
}


/****************************************************************************
  Function:
    void MCP9800_StartRead( void )

  Description:
    This function starts a temperature read, if one is not currently in
    progress.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void MCP9800_StartRead( void )
{
    if (MCP9800_state == TEMPERATURE_READ_WAIT)
    {
        MCP9800_state = TEMPERATURE_READ_START;
    }
}


/****************************************************************************
  Function:
    void MCP9800_Tasks( INTERFACE_DATA *interfaceData )

  Description:
    This function gets the temperature reading from the sensor and converts it
    to the required format.  Since the reading is done over I2C, which can be
    slow, it is done in a state machine.

  Precondition:
    None

  Parameters:
    INTERFACE_DATA *interfaceData   - Pointer to interface data.

  Return Values:
    None

  Remarks:
    The temperature sensor on the iPod Accessory Development Board for 8-bit
    PIC MCUs is an MCP9800.  The temperature sensor on the Explorer 16 is a
    TC1047, but its analog output signal, indicating the temperature, is
    on RB4, which is also used as the ACCESSORY_DETECT signal.  So temperature
    reading is not supported on the Explorer 16.
  ***************************************************************************/

void MCP9800_Tasks( INTERFACE_DATA *interfaceData )
{
    static UINT32                   operationStartTime;
    static UINT8                    rawReadingH = 0;
    static UINT8                    rawReadingL = 0;

    switch ( MCP9800_state )
    {
        case TEMPERATURE_READ_WAIT:
            break;

        case TEMPERATURE_READ_START:
            if (interfaceData->inUseI2C.value == 0)
            {
                operationStartTime = TickGet();
                I2CConfigure( MCP9800_I2C, I2C_MODE_MASTER | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE );
                I2CSetFrequency( MCP9800_I2C, GetInstructionClock(), MCP9800_MAX_I2C_FREQUENCY );
                I2CEnable( MCP9800_I2C, TRUE );
                interfaceData->inUseI2C.bits.inUseI2C_MCP9800 = 1;

                I2CStart( MCP9800_I2C );
                MCP9800_state = TEMPERATURE_READ_SEND_CHIP_ADDRESS;
            }
            break;

        case TEMPERATURE_READ_SEND_CHIP_ADDRESS:
            if (I2CTransmitterIsReady( MCP9800_I2C ))
            {
                I2CSendByte( MCP9800_I2C, MCP9800_ADDRESS_WRITE );
                MCP9800_state = TEMPERATURE_READ_SEND_REGISTER_ADDRESS;
            }
            break;

        case TEMPERATURE_READ_SEND_REGISTER_ADDRESS:
            if (I2CTransmissionHasCompleted( MCP9800_I2C ))
            {
                I2CSendByte( MCP9800_I2C, MCP9800_TEMPERATURE );
                MCP9800_state = TEMPERATURE_READ_REPEAT_START;
            }
            break;

        case TEMPERATURE_READ_REPEAT_START:
            if (I2CTransmissionHasCompleted( MCP9800_I2C ))
            {
                I2CRepeatStart( MCP9800_I2C );
                MCP9800_state = TEMPERATURE_READ_SEND_READ_ADDRESS;
            }
            break;

        case TEMPERATURE_READ_SEND_READ_ADDRESS:
            if (I2CTransmitterIsReady( MCP9800_I2C ))
            {
                I2CSendByte( MCP9800_I2C, MCP9800_ADDRESS_READ );
                MCP9800_state = TEMPERATURE_READ_RECEIVE_HIGH_BYTE;
            }
            break;

        case TEMPERATURE_READ_RECEIVE_HIGH_BYTE:
            if (I2CTransmissionHasCompleted( MCP9800_I2C ))
            {
                I2CReceiverEnable( MCP9800_I2C, TRUE );
                MCP9800_state = TEMPERATURE_READ_GET_HIGH_BYTE;
            }
            break;

        case TEMPERATURE_READ_GET_HIGH_BYTE:
            if (I2CReceivedDataIsAvailable(MCP9800_I2C))
            {
                rawReadingH = I2CGetByte( MCP9800_I2C );
                I2CAcknowledgeByte( MCP9800_I2C, TRUE );
                MCP9800_state = TEMPERATURE_READ_RECEIVE_LOW_BYTE;
            }
            break;

        case TEMPERATURE_READ_RECEIVE_LOW_BYTE:
            if (I2CAcknowledgeHasCompleted( MCP9800_I2C ))
            {
                I2CReceiverEnable( MCP9800_I2C, TRUE );
                MCP9800_state = TEMPERATURE_READ_GET_LOW_BYTE;
            }
            break;

        case TEMPERATURE_READ_GET_LOW_BYTE:
            if (I2CReceivedDataIsAvailable(MCP9800_I2C))
            {
                rawReadingL = I2CGetByte( MCP9800_I2C );

                rawReadingL >>= 4;

                if(rawReadingH > 127)
                {
                    // If the upper 8 bytes were greater than 127, the value is negative.
                    // Set the sign bit and get the absolute value of the temperature.
                    interfaceData->temperatureSign = 1;
                    rawReadingH = (~rawReadingH + 1);
                    rawReadingL = (~rawReadingL + 1);
                }
                else
                {
                     // Temperature is positive.
                    interfaceData->temperatureSign = 0;
                }

                interfaceData->temperatureDegrees = rawReadingH;
                interfaceData->temperatureTenths  = rawReadingL;

                I2CAcknowledgeByte( MCP9800_I2C, FALSE );
                MCP9800_state = TEMPERATURE_READ_STOP;
            }
            break;

        case TEMPERATURE_READ_STOP:
            if (I2CAcknowledgeHasCompleted( MCP9800_I2C ))
            {
                I2CStop( MCP9800_I2C );
                MCP9800_state = TEMPERATURE_READ_COMPLETE;
            }
            break;

        case TEMPERATURE_READ_COMPLETE:
            if (I2CBusIsIdle( MCP9800_I2C ))
            {
                I2CEnable( MCP9800_I2C, FALSE );
                interfaceData->inUseI2C.bits.inUseI2C_MCP9800 = 0;
                MCP9800_state = TEMPERATURE_READ_WAIT;
            }
            break;
    }

    if ((MCP9800_state != TEMPERATURE_READ_WAIT) && I2C_OperationTimeout( operationStartTime ))
    {
        I2CEnable( MCP9800_I2C, FALSE );
        interfaceData->inUseI2C.bits.inUseI2C_MCP9800 = 0;
        MCP9800_state = TEMPERATURE_READ_WAIT;
    }
}


