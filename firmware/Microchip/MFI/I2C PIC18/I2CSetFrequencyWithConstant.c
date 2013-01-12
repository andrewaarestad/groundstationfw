/*******************************************************************************
FileName:       I2CSetFrequencyWithConstant.c
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
    void I2CSetFrequencyWithConstant ( I2C_MODULE id, UINT16 brg )

  Summary:
    Routine to set the I2C module's desired SCL clock frequency.  Not published.

  Description:
    This routine allows the caller to set the desired clock frequency for the
    I2C module's SCL line.  This function is used internally by the library.
    Applications should use the function I2CSetFrequency.

  Precondition:
    The module must have been previously configured to master mode.

  Parameters:
    id          - Identifies the desired I2C module

    brg         - Value to load into the BRG register to obtain the desired
                    clock frequency.

  Returns:
    None

  Example:
    <code>
    actualClock = I2CSetFrequency(I2C1, GetInstructionClock(), I2C_CLOCK_FREQ);
    if ( abs(actualClock-I2C_CLOCK_FREQ) > I2C_CLOCK_FREQ/10 )
    {
        DBPRINT("I2C1 clock frequency (%d) error exceeds 10%\n", actualClock);
    }
    </code>

  Remarks:
    Actual frequency selected may be slightly different than frequency
    requested due to truncation error.  Actual frequency observed on the SCL
    line may be lower due to clock stretching.
  *****************************************************************************/

void I2CSetFrequencyWithConstant ( I2C_MODULE id, UINT16 brg )
{
    I2C_REGISTERS * const i2cRegisters = i2cBase[id];

    i2cRegisters->SSPxADD = brg;
}
