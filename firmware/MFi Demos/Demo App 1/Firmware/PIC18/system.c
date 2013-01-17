/******************************************************************************

File Name:       system.c
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
#define     SYSTEM_C
#include    "system.h"

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

VOID SysInit ( VOID )
{
    ConfigureClocks();

    //OSCTUNE = 0x5F;


    RCONbits.IPEN = 1;      // Enable prioritized interrupts

    TickInit();
}

// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Vectors
// *****************************************************************************
// *****************************************************************************

#if defined( IPOD_USE_UART )

    void high_isr (void);

    #pragma code high_vector=0x08
    void interrupt_at_high_vector(void)
    {
      _asm GOTO high_isr _endasm
    }
    #pragma code

    #pragma interrupt high_isr
    void high_isr (void)
    {
        MFI_UART_ISR();
        //RxInterrupt();
    }

    void low_isr (void);

    #pragma code low_vector=0x18
    void interrupt_at_low_vector(void)
    {
      _asm GOTO low_isr _endasm
    }
    #pragma code

    #pragma interruptlow low_isr
    void low_isr (void)
    {
        TickUpdate();
    }

#else

    void high_isr (void);

    #pragma code high_vector=0x08
    void interrupt_at_high_vector(void)
    {
      _asm GOTO high_isr _endasm
    }
    #pragma code

    #pragma interrupt high_isr
    void high_isr (void)
    {
        #if defined(USB_INTERRUPT)
            USBDeviceTasks();
        #endif
    }

    void low_isr (void);

    #pragma code low_vector=0x18
    void interrupt_at_low_vector(void)
    {
      _asm GOTO low_isr _endasm
    }
    #pragma code

    #pragma interruptlow low_isr
    void low_isr (void)
    {
        TickUpdate();
    }
#endif

// *****************************************************************************
// *****************************************************************************
// Section: USB Device Callbacks
// *****************************************************************************
// *****************************************************************************

#if defined ( IPOD_USE_USB_DEVICE )

    void USBCBErrorHandler ( void )
    {
    }

    void USBCBReset ( void )
    {
    }

    void USBCBSendResume ( void )
    {
    }

    void USBCBSuspend ( void )
    {
    }

    void USBCBWakeFromSuspend ( void )
    {
    }

#endif
