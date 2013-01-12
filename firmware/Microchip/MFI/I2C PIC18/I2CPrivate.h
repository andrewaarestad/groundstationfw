
/*******************************************************************************
  I2C Library Interface Definition: Private Header

  Summary:
    This file contains private definitions for the the Application Program
    Interface (API) definition  for the I2C peripheral library.

  Description:
    This file defines the register structure for the I2C library.
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
FileName:       I2CPrivate.h
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
//DOM-IGNORE-END

#ifndef _I2C_PRIVATE_H_
#define _I2C_PRIVATE_H_


#include <p18cxxx.h>

#include <GenericTypeDefs.h>
#include "MFI/I2C PIC18/i2c.h"

// *****************************************************************************
// Register Definitions
// *****************************************************************************

typedef union {
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned w:8;
  };
} __SSPxCON1bits_t;

typedef union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned : 1;
    unsigned ADMSK1 : 1;
    unsigned ADMSK  : 4;
    unsigned : 2;
  };
  struct {
    unsigned w:8;
  };
} __SSPxCON2bits_t;

typedef union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned w:8;
  };
} __SSPxSTATbits_t;

typedef struct _i2c_registers
{
    union {
        volatile UINT8 value;
        volatile __SSPxCON2bits_t bits;
    } SSPxCON2;
    union {
        volatile UINT8 value;
        volatile __SSPxCON1bits_t bits;
    } SSPxCON1;
    union {
        volatile UINT8 value;
        volatile __SSPxSTATbits_t bits;
    } SSPxSTAT;
    volatile UINT8 SSPxADD;
    volatile UINT8 SSPxBUF;
} I2C_REGISTERS;


extern I2C_REGISTERS * const i2cBase[I2C_NUMBER_OF_MODULES];


// *****************************************************************************
// Bit Definitions
// *****************************************************************************

#define _SSPCON1_SSPM_POSITION                  0
#define _SSPCON1_SSPM_MASK                      0x0F
#define _SSPCON1_SSPM_LENGTH                    4

#define _SSPCON1_CKP_POSITION                   4
#define _SSPCON1_CKP_MASK                       0x10
#define _SSPCON1_CKP_LENGTH                     1

#define _SSPCON1_SSPEN_POSITION                 5
#define _SSPCON1_SSPEN_MASK                     0x20
#define _SSPCON1_SSPEN_LENGTH                   1

#define _SSPCON1_SSPOV_POSITION                 6
#define _SSPCON1_SSPOV_MASK                     0x40
#define _SSPCON1_SSPOV_LENGTH                   1

#define _SSPCON1_WCOL_POSITION                  7
#define _SSPCON1_WCOL_MASK                      0x80
#define _SSPCON1_WCOL_LENGTH                    1



#define _SSPCON2_SEN_POSITION                   0
#define _SSPCON2_SEN_MASK                       0x01
#define _SSPCON2_SEN_LENGTH                     1

#define _SSPCON2_RSEN_POSITION                  1
#define _SSPCON2_RSEN_MASK                      0x02
#define _SSPCON2_RSEN_LENGTH                    1

#define _SSPCON2_PEN_POSITION                   2
#define _SSPCON2_PEN_MASK                       0x04
#define _SSPCON2_PEN_LENGTH                     1

#define _SSPCON2_RCEN_POSITION                  3
#define _SSPCON2_RCEN_MASK                      0x08
#define _SSPCON2_RCEN_LENGTH                    1

#define _SSPCON2_ACKEN_POSITION                 4
#define _SSPCON2_ACKEN_MASK                     0x10
#define _SSPCON2_ACKEN_LENGTH                   1

#define _SSPCON2_ACKDT_POSITION                 5
#define _SSPCON2_ACKDT_MASK                     0x20
#define _SSPCON2_ACKDT_LENGTH                   1

#define _SSPCON2_ACKSTAT_POSITION               6
#define _SSPCON2_ACKSTAT_MASK                   0x40
#define _SSPCON2_ACKSTAT_LENGTH                 1

#define _SSPCON2_GCEN_POSITION                  7
#define _SSPCON2_GCEN_MASK                      0x80
#define _SSPCON2_GCEN_LENGTH                    1



#define _SSPSTAT_BF_POSITION                    0
#define _SSPSTAT_BF_MASK                        0x01
#define _SSPSTAT_BF_LENGTH                      1

#define _SSPSTAT_UA_POSITION                    1
#define _SSPSTAT_UA_MASK                        0x02
#define _SSPSTAT_UA_LENGTH                      1

#define _SSPSTAT_R_W_POSITION                   2
#define _SSPSTAT_R_W_MASK                       0x04
#define _SSPSTAT_R_W_LENGTH                     1

#define _SSPSTAT_S_POSITION                     3
#define _SSPSTAT_S_MASK                         0x08
#define _SSPSTAT_S_LENGTH                       1

#define _SSPSTAT_P_POSITION                     4
#define _SSPSTAT_P_MASK                         0x10
#define _SSPSTAT_P_LENGTH                       1

#define _SSPSTAT_D_A_POSITION                   5
#define _SSPSTAT_D_A_MASK                       0x20
#define _SSPSTAT_D_A_LENGTH                     1

#define _SSPSTAT_CKE_POSITION                   6
#define _SSPSTAT_CKE_MASK                       0x40
#define _SSPSTAT_CKE_LENGTH                     1

#define _SSPSTAT_SMP_POSITION                   7
#define _SSPSTAT_SMP_MASK                       0x80
#define _SSPSTAT_SMP_LENGTH                     1


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

void I2CSetFrequencyWithConstant ( I2C_MODULE id, UINT16 brg );


#endif // _I2C_PRIVATE_H_

