/******************************************************************************

File Name:       LM49450.c
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

#define LM49450_C
#include "LM49450.h"


// *****************************************************************************
// Section: Macros
// *****************************************************************************

#define I2C_OperationTimeout(t)         ((TickGet() - t) > (2 * dwTicksPerSecond))


// *****************************************************************************
// Section: Global Variables
// *****************************************************************************

I2C_MODULE                  LM49450_I2C;
UINT32                      LM49450_operationStartTime;
UINT8                       LM49450_registerAddress;
LM49450_STATES              LM49450_state;
LM49450_WRITE_BYTE_STATES   LM49450_stateWrite;
UINT8                       LM49450_value;
UINT8                       LM49450_volume;


/****************************************************************************
  Function:
     UINT8 LM49450_Initialize( I2C_MODULE selectedI2C )

  Description:
    This function initializes the LM49450 headphone amplifier.  Note that only
    the 8-bit development board has a headphone amplifier.

  Precondition:
    None

  Parameters:
    I2C_MODULE selectedI2C - The I2C module to use to talk to the LM49450.

  Return Values:
    LM49450_SUCCESS                     0
    LM49450_CANNOT_INITIALIZE           1

  Remarks:
    We are not using the I2S so no MCLK configuration is required.
  ***************************************************************************/

UINT8 LM49450_Initialize( I2C_MODULE selectedI2C )
{
    LM49450_I2C         = selectedI2C;
    LM49450_state       = LM49450_WAITING;
    LM49450_stateWrite  = LM49450_WRITE_BYTE_WAITING;
    LM49450_volume      = LM49450_VOLUME_INITIAL;

    if (!LM49450_WriteByte( LM49450_MODE_CTRL,
            LM49450_INTERNAL_REFERENCE | LM49450_COMPENSATION_DEFAULT | LM49450_OSCILLATOR_SS |
            LM49450_UNMUTE | LM49450_LINE_IN_ENABLE | LM49450_ENABLE ))
    {
        return LM49450_CANNOT_INITIALIZE;
    }

    // Set the LM49450_volumes to an initial value.
    LM49450_WriteByte( LM49450_HEADPHONE_VOLUME_CTRL, LM49450_volume );
    LM49450_WriteByte( LM49450_SPEAKER_VOLUME_CTRL, LM49450_volume );

    return LM49450_SUCCESS;
}


/****************************************************************************
  Function:
     void LM49450_Tasks( INTERFACE_DATA *interfaceData )

  Description:
    This function keeps the primary manipulation of the headphone amplifier
    in a non-blocking state machine.

  Precondition:
    The I2C module must be available for use, or already being used by this
    function, before calling this function.

  Parameters:
    INTERFACE_DATA *interfaceData

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void LM49450_Tasks( INTERFACE_DATA *interfaceData )
{
    //--------------------------------------------------------------------------
    // Monitor the LM49450_volume control state.

    switch ( LM49450_state )
    {
        case LM49450_WAITING:
            if (LM49450_volume != interfaceData->volume)
            {
                LM49450_volume              = interfaceData->volume;
                LM49450_state               = LM49450_VOLUME_ENABLE;
                LM49450_operationStartTime  = TickGet();
            }
            break;

        case LM49450_VOLUME_ENABLE:
            if (interfaceData->inUseI2C.value == 0)
            {
                if (LM49450_stateWrite == LM49450_WRITE_BYTE_WAITING)
                {
                    I2CConfigure( LM49450_I2C, I2C_MODE_MASTER | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE );
                    I2CSetFrequency( LM49450_I2C, GetInstructionClock(), LM49450_MAX_I2C_FREQUENCY );
                    I2CEnable( LM49450_I2C, TRUE );

                    interfaceData->inUseI2C.bits.inUseI2C_LM45490 = 1;
                    LM49450_state = LM49450_VOLUME_SEND_VOLUME_HEADPHONES;
                }
            }
            break;

        case LM49450_VOLUME_SEND_VOLUME_HEADPHONES:
            if (LM49450_stateWrite == LM49450_WRITE_BYTE_WAITING)
            {
                LM49450_registerAddress   = LM49450_HEADPHONE_VOLUME_CTRL;
                LM49450_value             = (~LM49450_volume) >> 3;
                LM49450_stateWrite        = LM49450_WRITE_BYTE_START;

                LM49450_state             = LM49450_VOLUME_SEND_VOLUME_SPEAKER;
            }
            break;

        case LM49450_VOLUME_SEND_VOLUME_SPEAKER:
            if (LM49450_stateWrite == LM49450_WRITE_BYTE_WAITING)
            {
                LM49450_registerAddress   = LM49450_SPEAKER_VOLUME_CTRL;
                LM49450_value             = (~LM49450_volume) >> 3;
                LM49450_stateWrite        = LM49450_WRITE_BYTE_START;

                LM49450_state             = LM49450_VOLUME_COMPLETE;
            }
            break;

        case LM49450_VOLUME_COMPLETE:
            if (LM49450_stateWrite == LM49450_WRITE_BYTE_WAITING)
            {
                I2CEnable( LM49450_I2C, FALSE );

                interfaceData->inUseI2C.bits.inUseI2C_LM45490 = 0;
                LM49450_state = LM49450_WAITING;
            }
            break;
    }

    //--------------------------------------------------------------------------
    // Monitor the I2C write state.

    switch ( LM49450_stateWrite )
    {
        case LM49450_WRITE_BYTE_WAITING:
            break;

        case LM49450_WRITE_BYTE_START:
            I2CStart( LM49450_I2C );
            LM49450_stateWrite = LM49450_WRITE_BYTE_SEND_CHIP_ADDRESS;
            break;

        case LM49450_WRITE_BYTE_SEND_CHIP_ADDRESS:
            if (I2CTransmitterIsReady( LM49450_I2C ))
            {
                I2CSendByte( LM49450_I2C, LM49450_ADDRESS_WRITE );
                LM49450_stateWrite = LM49450_WRITE_BYTE_SEND_REGISTER_ADDRESS;
            }
            break;

        case LM49450_WRITE_BYTE_SEND_REGISTER_ADDRESS:
            if (I2CTransmissionHasCompleted( LM49450_I2C ))
            {
                if (!I2CByteWasAcknowledged( LM49450_I2C ))
                {
                    LM49450_stateWrite = LM49450_WRITE_BYTE_WAITING;
                }
                else
                {
                    I2CSendByte( LM49450_I2C, LM49450_registerAddress );
                    LM49450_stateWrite = LM49450_WRITE_BYTE_SEND_VALUE;
                }
            }
            break;

        case LM49450_WRITE_BYTE_SEND_VALUE:
            if (I2CTransmissionHasCompleted( LM49450_I2C ))
            {
                if (!I2CByteWasAcknowledged( LM49450_I2C ))
                {
                    LM49450_stateWrite = LM49450_WRITE_BYTE_WAITING;
                }
                else
                {
                    I2CSendByte( LM49450_I2C, LM49450_value );
                    LM49450_stateWrite = LM49450_WRITE_BYTE_STOP;
                }
            }
            break;

        case LM49450_WRITE_BYTE_STOP:
            if (I2CTransmissionHasCompleted( LM49450_I2C ))
            {
                if (!I2CByteWasAcknowledged( LM49450_I2C ))
                {
                    LM49450_stateWrite = LM49450_WRITE_BYTE_WAITING;
                }
                else
                {
                    I2CStop( LM49450_I2C );
                    LM49450_stateWrite = LM49450_WRITE_COMPLETE;
                }
            }
            break;

        case LM49450_WRITE_COMPLETE:
            if (I2CBusIsIdle( LM49450_I2C ))
            {
                LM49450_stateWrite = LM49450_WRITE_BYTE_WAITING;
            }
            break;
    }

    // Check for overall operation timeout.
    if ((LM49450_state != LM49450_WAITING) && I2C_OperationTimeout( LM49450_operationStartTime ))
    {
        I2CEnable( LM49450_I2C, FALSE );
        interfaceData->inUseI2C.bits.inUseI2C_LM45490 = 0;

        LM49450_state      = LM49450_WAITING;
        LM49450_stateWrite = LM49450_WRITE_BYTE_WAITING;
    }
}


/****************************************************************************
  Function:
     BOOL LM49450_WriteByte( UINT8 register_address, UINT8 value )

  Description:
    This function writes a byte to the LM49450 headphone amplifier.  Note
    that only the 8-bit development board has a headphone amplifier.

  Precondition:
    None

  Parameters:
    None

  Return Values:
   TRUE     - Byte was written successfully.
   FALSE    - Byte was not written successfully.

  Remarks:
    This should not be called during the main loop.  It should be used during
    initialization only.
  ***************************************************************************/

BOOL LM49450_WriteByte( UINT8 register_address, UINT8 value )
{
    LM49450_operationStartTime = TickGet();

    // We'll use the same frequency as the CP chip, so we don't have to put it to sleep.
    I2CConfigure( LM49450_I2C, I2C_MODE_MASTER | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE );
    I2CSetFrequency( LM49450_I2C, GetInstructionClock(), LM49450_MAX_I2C_FREQUENCY );
    I2CEnable( LM49450_I2C, TRUE );

    I2CStart( LM49450_I2C );
    while (!I2CTransmitterIsReady( LM49450_I2C ) && !I2C_OperationTimeout( LM49450_operationStartTime )) {};

    I2CSendByte( LM49450_I2C, LM49450_ADDRESS_WRITE );
    while (!I2CTransmissionHasCompleted( LM49450_I2C ) && !I2C_OperationTimeout( LM49450_operationStartTime )) {};
    if (!I2CByteWasAcknowledged( LM49450_I2C ))
    {
        return FALSE;
    }

    I2CSendByte( LM49450_I2C, register_address );
    while (!I2CTransmissionHasCompleted( LM49450_I2C ) && !I2C_OperationTimeout( LM49450_operationStartTime )) {};
    if (!I2CByteWasAcknowledged( LM49450_I2C ))
    {
        return FALSE;
    }

    I2CSendByte( LM49450_I2C, value );
    while (!I2CTransmissionHasCompleted( LM49450_I2C ) && !I2C_OperationTimeout( LM49450_operationStartTime )) {};
    if (!I2CByteWasAcknowledged( LM49450_I2C ))
    {
        return FALSE;
    }

    I2CStop( LM49450_I2C );
    while (!I2CBusIsIdle( LM49450_I2C ) && !I2C_OperationTimeout( LM49450_operationStartTime )) {};

    I2CEnable( LM49450_I2C, FALSE );

    if (I2C_OperationTimeout( LM49450_operationStartTime ))
    {
        return FALSE;
    }
    return TRUE;
}



