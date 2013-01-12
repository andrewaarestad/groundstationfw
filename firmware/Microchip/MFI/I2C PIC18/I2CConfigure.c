/*******************************************************************************
FileName:       I2CConfigure.c
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


#define I2C_CONFIGURE_MASK_CONTROL      (0x0F | I2C_SLAVE_CLOCK_RELEASE)
#define I2C_CONFIGURE_MASK_STATUS       (I2C_SMBUS_INPUTS_ENABLE | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE )


/*******************************************************************************
  Function:
    void I2CConfigure ( I2C_MODULE id, I2C_CONFIGURATION flags )

  Summary:
    I2C module configuration routine

  Description:
    This routine allows the caller to configure various features of the I2C
    module for desired operation.

  Precondition:
    None

  Parameters:
    id      - Identifies the desired I2C module

    flags   - The desired module configuration settings

  Returns:

  Example:
    <code>
    I2CConfigure(I2C1, I2C_MODE_MASTER | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE);
    </code>

  Remarks:
    Refer to the I2C_CONFIGURATION enumerated data type for details on each
    configuration flag.  Note that the bitmask resulting from the bit-wise OR
    of these values will result in a value that is not defined in the enum.

    When configuring slave mode, be sure to specify either
    I2C_SLAVE_CLOCK_RELEASE or I2C_SLAVE_CLOCK_HOLD.
  *****************************************************************************/

void I2CConfigure ( I2C_MODULE id, I2C_CONFIGURATION flags )
{
    I2C_REGISTERS * const i2cRegisters = i2cBase[id];

    i2cRegisters->SSPxCON1.value = flags & I2C_CONFIGURE_MASK_CONTROL;
    i2cRegisters->SSPxSTAT.value = flags & I2C_CONFIGURE_MASK_STATUS;
}
