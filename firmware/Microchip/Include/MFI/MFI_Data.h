/******************************************************************************

File Name:       MFI_Data.h
Dependencies:    None
Processor:       PIC16F1/PIC18/PIC24-dsPIC/PIC32
Compiler:        HiTech PICC/MPLAB C18/MPLAB C30/MPLAB C32
Company:         Microchip Technology, Inc.

Copyright © 2009-2012 Microchip Technology Inc.  All rights reserved.

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

Author          Date        Comments
--------------------------------------------------------------------------------
KO/SP/AF        03-Aug-2012 v3.05
KO/SP/AF        29-Feb-2012 v3.04
KO/SP/AF        02-Feb-2012 v3.03, Limited distribution
KO/SP/AF        02-Dec-2011 v3.02
KO/SP/AF        14-Sep-2011 v3.01
Kimberly Otten/
  Sergey Pavlov 26-May-2011 v3.00

*******************************************************************************/

#ifndef MFI_DATA_H
#define MFI_DATA_H

////////////////////////////////////////////////////////////////////////////////
// Common

#include "GenericTypeDefs.h"
#include "Compiler.h"

#include "mfi_config.h"

#include "MFI/MFI_iPod.h"


////////////////////////////////////////////////////////////////////////////////

#ifdef MFI_DATA_C

    ////////////////////////////////////////////////////////////////////////////////
    // Private

#else

    ////////////////////////////////////////////////////////////////////////////////
    // Public

    //******************************************************************************
    // Section: Global Variables
    //******************************************************************************

    #if defined( IPOD_USE_USB_DEVICE ) || defined( IPOD_USE_USB_HOST )
        // Section: Variables for USB applications
        extern IPOD_DATA_FORMAT_IN                  mfi_iAPIn;                   // Current iPod iAP input command
        extern IPOD_DATA_FORMAT_OUT                 mfi_iAPOut;                  // Current iPod iAP output command
    #elif defined ( IPOD_USE_BLUETOOTH )
        // Section: Variables for BT applications
        extern volatile UINT8                       mfi_RXBufferRaw[IPOD_BUFFER_LENGTH_INPUT];
        extern IPOD_DATA_FORMAT_IN                  mfi_iAPIn;                   // Current iPod iAP input command
        extern IPOD_DATA_FORMAT_OUT                 mfi_iAPOut;                  // Current iPod iAP output command
    #else
        // Section: Variables for UART applications
        #ifdef _PIC14E
            extern IPOD_DATA_FORMAT_IN              mfi_iAPIn;                   // Current iPod iAP input command
            extern IPOD_DATA_FORMAT_OUT             mfi_iAPOut;                  // Current iPod iAP output command
        #else
            extern volatile IPOD_DATA_FORMAT_IN     mfi_iAPIn;                   // Current iPod iAP input command
            extern IPOD_DATA_FORMAT_OUT             mfi_iAPOut;                  // Current iPod iAP output command
        #endif
    #endif

    #if defined( IPOD_USE_USB_HOST ) && ( ( IPOD_ACCESSORY_LINGOES & IPOD_LINGO_FLAG_DIGITAL_AUDIO ) != 0 )
            // This structure is used for the streaming Digital Audio data.  After
            // receiving the MFI_EVENT_AUDIO_RECEIVING_DATA, the application layer
            // must monitor these buffers, play the content, and mark them used.
            // The application layer must be able to process one buffer every
            // millisecond, since the iPod will send one buffer every millisecond.
        extern ISOCHRONOUS_DATA                     mfi_iPodStreamingAudio;
    #endif

#endif

////////////////////////////////////////////////////////////////////////////////
// Common


BOOL        MFIIF_UART_RawBufferEmpty ( void );
BOOL        MFIIF_UART_RawBufferFull ( void );
UINT8       MFIIF_UART_RawBufferGetByte ( void );
void        MFIIF_UART_RawBufferPutByte ( UINT8 oneByte );
void        MFIIF_UART_RawBufferReset ( void );

#endif

