/*******************************************************************************
FileName:       I2CReceiverEnable.c
Processor:      PIC18
Compiler:       Microchip MPLAB C18 v3.34 or higher

Copyright © 2010 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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

#include "I2CPrivate.h"

/*******************************************************************************
  Function:
    I2C_RESULT I2CReceiverEnable ( I2C_MODULE id, BOOL enable )

  Summary:
    Routine to enable the module to receive data from the I2C bus

  Description:
    This routine enables the module to receive data from the I2C bus.

  Precondition:
    The module must have been configured appropriately and enabled, a transfer
    must have been previously started, and module must be the intended receiver
    of the next byte of data.

  Parameters:
    id      - Identifies the desired I2C module

    enable  - Determines if the receiver is to be enabled or disabled
              * If TRUE, enables the module to receive data on the I2C
              * If FALSE, disables the module from receiving data on the I2C

  Returns:
    None

  Example:
    <code>
    I2CReceiverEnable( I2C1, TRUE );
    while (!I2CReceivedDataIsAvailable(I2C1) && !OperationTimeout())
    {
        // Wait for the data byte
        Nop();
    }
    oneByte = I2CGetByte( I2C1 );
    </code>

  Remarks:
    This routine should be used by both master and slave receivers.
  *****************************************************************************/

I2C_RESULT I2CReceiverEnable ( I2C_MODULE id, BOOL enable )
{
    I2C_REGISTERS * const i2cRegisters = i2cBase[id];

    // Enable the receiver
    i2cRegisters->SSPxCON2.bits.RCEN = enable;

    // Check for an overflow condition
    if(i2cRegisters->SSPxCON1.bits.SSPOV)
    {
        return(I2C_RECEIVE_OVERFLOW);
    }
    else
    {
        return(I2C_SUCCESS);
    }
}
