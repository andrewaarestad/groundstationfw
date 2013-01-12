/******************************************************************************
    MFI Library Data Definition File

This file defines the input and output buffers for iPod communication data.

DO NOT MODIFY THIS FILE!

*******************************************************************************/
//DOM-IGNORE-BEGIN
/******************************************************************************

File Name:       MFI_Data.c
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
Kimberly Otten/
 Sergey Pavlov  17-Dec-2010 v2.05
Kimberly Otten  25-Oct-2010 v2.04
Kimberly Otten  23-Jul-2010 v2.03

*******************************************************************************/

#define MFI_DATA_C

#include "MFI/MFI_Data.h"

//****************************************************************************
// Section: Configuration
//****************************************************************************

#if defined( IPOD_USE_UART ) || defined ( IPOD_BT_STACK_INTERNAL )
    #if defined( __C30__ ) || defined( __PIC32MX__ ) || (IPOD_BUFFER_LENGTH_INPUT != 256)
        #define BUFFER_WRAP_CHECK_NEEDED    1
    #endif
#endif

//****************************************************************************
// Section: Global Variables
//****************************************************************************

IPOD_APPLICATION_INFORMATION        mfi_iPodApplicationInformation;

#if defined ( _PIC14E )

    volatile UINT8                  mfi_rawDataHead;
    UINT8                           mfi_rawDataTail;

    volatile UINT8                  mfi_RXBufferRaw[IPOD_BUFFER_LENGTH_INPUT];
    IPOD_DATA_FORMAT_IN             mfi_iAPIn;                          // Current iPod iAP input command
    IPOD_DATA_FORMAT_OUT            mfi_iAPOut;                         // Current iPod iAP output command

#elif defined( __18CXX )

    // NOTE: structures cannot span bank boundaries

    #if defined ( IPOD_USE_UART )
        volatile UINT8              mfi_rawDataHead;
        UINT8                       mfi_rawDataTail;

        #pragma udata MFI_BUFFER_RX_RAW
        volatile UINT8              mfi_RXBufferRaw[IPOD_BUFFER_LENGTH_INPUT];
        #pragma udata
    #endif

    #pragma udata MFI_BUFFER_RX
    volatile IPOD_DATA_FORMAT_IN    mfi_iAPIn;                          // Current iPod iAP input command
    #pragma udata

    #pragma udata MFI_BUFFER_TX
    IPOD_DATA_FORMAT_OUT            mfi_iAPOut;                         // Current iPod iAP output command
    #pragma udata

#elif defined( __C30__ ) || defined( __PIC32MX__ )

    #if defined ( IPOD_USE_UART ) || defined ( IPOD_BT_STACK_INTERNAL )
        volatile UINT16             mfi_rawDataHead;
        volatile UINT16             mfi_rawDataTail;

        volatile UINT8              mfi_RXBufferRaw[IPOD_BUFFER_LENGTH_INPUT];   // Raw bytes from UART
    #endif

    volatile IPOD_DATA_FORMAT_IN    mfi_iAPIn;                          // Current iPod iAP input command
    IPOD_DATA_FORMAT_OUT            mfi_iAPOut;                         // Current iPod iAP output command

#else
    #error This library does not support the selected processor.
#endif


#if defined( IPOD_USE_USB_HOST ) && ( ( IPOD_ACCESSORY_LINGOES & IPOD_LINGO_FLAG_DIGITAL_AUDIO ) != 0 )
    ISOCHRONOUS_DATA                    mfi_iPodStreamingAudio;     // Digital audio data
#endif


//****************************************************************************
// Section: Functions
//****************************************************************************

/****************************************************************************
  Function:
    BOOL MFIIF_UART_RawBufferEmpty( void )

  Description:
    This function determines if the raw input data buffer is empty.  It is
    needed only for the UART interface.

  Precondition:
    None

  Parameters:
    None

  Returns:
    TRUE    - Raw buffer is empty
    FALSE   - Raw buffer is not empty

  Remarks:
    None
  ***************************************************************************/
#if defined( IPOD_USE_UART ) || defined ( IPOD_BT_STACK_INTERNAL )
    BOOL MFIIF_UART_RawBufferEmpty( void )
    {
        return (mfi_rawDataHead == mfi_rawDataTail);
    }
#endif

/****************************************************************************
  Function:
    BOOL MFIIF_UART_RawBufferFull( void )

  Description:
    This function determines if the raw input data buffer is full.  It is
    needed only for the UART interface.

  Precondition:
    None

  Parameters:
    None

  Returns:
    TRUE    - Raw buffer is full
    FALSE   - Raw buffer is not full

  Remarks:
    None
  ***************************************************************************/
#if defined( IPOD_USE_UART ) || defined ( IPOD_BT_STACK_INTERNAL )
    BOOL MFIIF_UART_RawBufferFull( void )
    {
        return (((mfi_rawDataHead == IPOD_BUFFER_LENGTH_INPUT-1) && (mfi_rawDataTail == 0)) ||
                 (mfi_rawDataHead == mfi_rawDataTail-1));
    }
#endif



/****************************************************************************
  Function:
    UINT8 MFIIF_UART_RawBufferGetByte( void )

  Description:
    This routine gets a byte from the raw UART data buffer.

  Precondition:
    This routine cannot be run on an empty buffer.

  Parameters:
    None

  Returns:
    Raw data byte

  Remarks:
    None
  ***************************************************************************/
#if defined( IPOD_USE_UART ) || defined ( IPOD_BT_STACK_INTERNAL )
    UINT8 MFIIF_UART_RawBufferGetByte( void )
    {
        UINT8   oneByte;

        oneByte = mfi_RXBufferRaw[mfi_rawDataTail++];
        #if BUFFER_WRAP_CHECK_NEEDED
            if (mfi_rawDataTail >= IPOD_BUFFER_LENGTH_INPUT)
            {
                mfi_rawDataTail = 0;
            }
        #endif

        return oneByte;
    }
#endif


/****************************************************************************
  Function:
    void MFIIF_UART_RawBufferPutByte( UINT8 oneByte )

  Description:
    This routine puts a byte into the raw UART data buffer.

  Precondition:
    This routine cannot be run on a full buffer.

  Parameters:
    UINT8 oneByte   - New data byte

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
#if defined( IPOD_USE_UART ) || defined ( IPOD_BT_STACK_INTERNAL )
    void MFIIF_UART_RawBufferPutByte( UINT8 oneByte )
    {
        mfi_RXBufferRaw[mfi_rawDataHead++] = oneByte;
        #if BUFFER_WRAP_CHECK_NEEDED
            if (mfi_rawDataHead >= IPOD_BUFFER_LENGTH_INPUT)
            {
                mfi_rawDataHead = 0;
            }
        #endif
    }
#endif


/****************************************************************************
  Function:
    void MFIIF_UART_RawBufferReset( void )

  Description:
    This routine resets the raw UART data buffer.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
#if defined( IPOD_USE_UART ) || defined ( IPOD_BT_STACK_INTERNAL )
    void MFIIF_UART_RawBufferReset( void )
    {
        mfi_rawDataHead = 0;
        mfi_rawDataTail = 0;
    }
#endif


