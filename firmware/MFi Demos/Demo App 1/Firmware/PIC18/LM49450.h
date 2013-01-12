/******************************************************************************

File Name:       LM49450.h
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

#ifndef LM49450_H
#define LM49450_H

////////////////////////////////////////////////////////////////////////////////
// Common

#include "system.h"
#include "main.h"


// *****************************************************************************
// Section: Constants
// *****************************************************************************

// Error Codes
#define LM49450_SUCCESS                     0
#define LM49450_CANNOT_INITIALIZE           1


////////////////////////////////////////////////////////////////////////////////

#ifdef LM49450_C

    ////////////////////////////////////////////////////////////////////////////////
    // Private

    // *****************************************************************************
    // Section: Constants
    // *****************************************************************************

    #define LM49450_ADDRESS                     0x7D
    #define LM49450_ADDRESS_READ                ((LM49450_ADDRESS << 1) | 0x01)
    #define LM49450_ADDRESS_WRITE               (LM49450_ADDRESS << 1)
    #define LM49450_MAX_I2C_FREQUENCY           400000
    #define LM49450_VOLUME_INITIAL              0x04

    // Register Addresses
    #define LM49450_MODE_CTRL                   0x00
    #define LM49450_CLOCK                       0x01
    #define LM49450_CHARGE_PUMP_CLOCK_FREQ      0x02
    #define LM49450_I2S_MODE                    0x03
    #define LM49450_I2S_CLOCK                   0x04
    #define LM49450_HEADPHONE_3D_CTRL           0x05
    #define LM49450_SPEAKER_3D_CTRL             0x06
    #define LM49450_HEADPHONE_VOLUME_CTRL       0x07
    #define LM49450_SPEAKER_VOLUME_CTRL         0x08
    #define LM49450_CMP_0_LSB                   0x09
    #define LM49450_CMP_0_MSB                   0x0A
    #define LM49450_CMP_1_LSB                   0x0B
    #define LM49450_CMP_1_MSB                   0x0C
    #define LM49450_CMP_2_LSB                   0x0D
    #define LM49450_CMP_2_MSB                   0x0E

    // Mode Bits
    #define LM49450_INTERNAL_REFERENCE          0x00
    #define LM49450_EXTERNAL_REFERENCE          0x80
    #define LM49450_DAC_MODE_125                0x00
    #define LM49450_DAC_MODE_128                0x20
    #define LM49450_DAC_MODE_64                 0x40
    #define LM49450_DAC_MODE_32                 0x60
    #define LM49450_COMPENSATION_DEFAULT        0x00
    #define LM49450_COMPENSATION_PROGRAM        0x10
    #define LM49450_OSCILLATOR_FIXED            0x00
    #define LM49450_OSCILLATOR_SS               0x08
    #define LM49450_UNMUTE                      0x00
    #define LM49450_MUTE                        0x04
    #define LM49450_LINE_IN_DISABLE             0x00
    #define LM49450_LINE_IN_ENABLE              0x02
    #define LM49450_DISABLE                     0x00
    #define LM49450_ENABLE                      0x01

    // *****************************************************************************
    // Section: Data Structures and Enumerations
    // *****************************************************************************

    // *****************************************************************************
    /* LM49450 States

    These states are used in the main LM49450 headphone amplifier state machine.
    */
    typedef enum {
        LM49450_WAITING = 0,
        LM49450_VOLUME_ENABLE,
        LM49450_VOLUME_SEND_VOLUME_HEADPHONES,
        LM49450_VOLUME_SEND_VOLUME_SPEAKER,
        LM49450_VOLUME_COMPLETE
    } LM49450_STATES;

    // *****************************************************************************
    /* LM49450 I2C Write Byte States

    These states are used in the state machine that writes a byte to the LM49450
    headphone amplifier .
    */
    typedef enum {
        LM49450_WRITE_BYTE_WAITING = 0,
        LM49450_WRITE_BYTE_START,
        LM49450_WRITE_BYTE_SEND_CHIP_ADDRESS,
        LM49450_WRITE_BYTE_SEND_REGISTER_ADDRESS,
        LM49450_WRITE_BYTE_SEND_VALUE,
        LM49450_WRITE_BYTE_STOP,
        LM49450_WRITE_COMPLETE
    } LM49450_WRITE_BYTE_STATES;

    // *****************************************************************************
    // Section: Internal Function Prototypes
    // *****************************************************************************

    BOOL    LM49450_WriteByte( UINT8 register_address, UINT8 value );

#else
    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif

// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************

UINT8   LM49450_Initialize( I2C_MODULE selectedI2C );
void    LM49450_Tasks( INTERFACE_DATA *interfaceData );

#endif
