/******************************************************************************

File Name:       system.h
Dependencies:    USB Embedded Host library, MFI library
Processor:       PIC24F
Company:         Microchip Technology, Inc.

Copyright 2009-2010 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
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

#ifndef SYSTEM_H
#define SYSTEM_H

////////////////////////////////////////////////////////////////////////////////
// Common

// *****************************************************************************
// Section: Configuration
// *****************************************************************************

#if !defined ( __18CXX )
    #error This system file is for PIC18 only
#endif


// *****************************************************************************
// Section: Includes
// *****************************************************************************

#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"

#include "Tick.h"
#include "TimeDelay.h"

#include "MFI/I2C PIC18/i2c.h"


////////////////////////////////////////////////////////////////////////////////

#ifdef  SYSTEM_C

    ////////////////////////////////////////////////////////////////////////////////
    // Private

    #include "main.h"
    #include "MFI/MFI_iPod.h"
    
    
    #if ((IPOD_OPERATIONAL_PARAMETERS_BYTE0 & 0x01) == 0x01)
        #define USING_LM20_BLUETOOTH
        #include "LM20.h"
    #endif

#else

    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif

////////////////////////////////////////////////////////////////////////////////
// Common

/****************************************************************************
  Function:
    VOID SysInit ( VOID )

  Description:
    This function initializes the system.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
VOID SysInit ( VOID );

////////////////////////////////////////////////////////////////////////////////
#endif
