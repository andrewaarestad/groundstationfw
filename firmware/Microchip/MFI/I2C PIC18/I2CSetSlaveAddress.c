/*******************************************************************************
FileName:       I2CSetSlaveAddress.c
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


// Private mask definition
#define I2C_ADDRESS_MODE_FLAGS_MASK (I2C_ENABLE_GENERAL_CALL_ADDRESS)


/*******************************************************************************
  Function:
    void I2CSetSlaveAddress ( I2C_MODULE id, UINT16 address, UINT16 mask,
                              I2C_ADDRESS_MODE flags )

  Summary:
    Routine to set the value and mode of the slave address(es) in slave mode

  Description:
    This routine sets the slave address and size (7-or-10 bits) to which the
    module will respond.  It also sets an optional "ignore" mask, allowing the
    module to ignore bits within the address and thus respond to multiple slave
    addresses as well as how reserved addresses are handled.

  Precondition:
    The module should be configured for slave mode operation.

  Parameters:
    id      - Identifies the desired I2C module

    address - The 7- or 10-bit slave address to which the module will respond.
              (The address should be right-aligned in the 16-bit parameter,
              without any read/write bit in the 0 position.)

    mask    - This parameter identifies bits in the address that are "don't-
              care" bits.  These bits will be ignored when attempting to match
              the address, effectively allowing the module to recognize
              multiple slave addresses.  (To match an address exactly, this
              parameter must be zero (0).)

    flags   - This parameter is a bit-wise OR of the values in the
              I2C_ADDRESS_MODE enumeration.  These enumeration flags can be
              used to select the addressing mode (7- or 10-bit) and define how
              reserved addresses are handled.
  Returns:
    Some modules may not support all addressing modes or the mask feature.  It
    is safe to pass a zero (0) value for these features if they are not needed.
    If they are not available, the value passed for these features will be
    ignored.

  Example:
    <code>
    I2CConfigure(I2C1, I2C_MODE_SLAVE_10);
    I2CSetSlaveAddress(I2C1, MY_SLAVE_ADDRESS, 0, I2C_ENABLE_GENERAL_CALL_ADDRESS);
    </code>

  Remarks:
  *****************************************************************************/

void I2CSetSlaveAddress ( I2C_MODULE id, UINT16 address, UINT16 mask, I2C_ADDRESS_MODE flags )
{
    I2C_REGISTERS * const i2cRegisters = i2cBase[id];
    UINT8   oldSSPCON1;

    // Load the address.
    i2cRegisters->SSPxADD.value     = address;

    // Switch the ADD register to be the MASK register.
    oldSSPCON1                      = i2cRegisters->SSPxCON1.value;
    i2cRegisters->SSPxCON1.value    = (oldSSPCON1 & ~_SSPCON1_SSPM_MASK) | I2C_MODE_LOAD_SSPMSK;

    // Load the mask.
    i2cRegisters->SSPxMSK.value     = mask;

    // Restore the mode.
    i2cRegisters->SSPxCON1.value    = oldSSPCON1;

    // Set the address mode flags.
    i2cRegisters->I2CxCON.value     &= ~I2C_ADDRESS_MODE_FLAGS_MASK;
    i2cRegisters->I2CxCON.value     |= (I2C_ADDRESS_MODE_FLAGS_MASK & flags);
}
