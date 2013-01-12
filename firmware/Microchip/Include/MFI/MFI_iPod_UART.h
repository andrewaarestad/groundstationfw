/******************************************************************************
    UART Drivers for the Apple MFI Development Library

This file provides the UART drivers for the Apple MFI Development Library.
All architectures are included in this file.

DO NOT MODIFY THE API IN THIS FILE!  Modifications of the functions in this
file should be performed very carefully, since the MFI library is dependent
on these functions.
******************************************************************************/
/******************************************************************************

File Name:       MFI_iPod_UART.h
Dependencies:    None
Processor:       PIC16F1/PIC18/PIC24-dsPIC/PIC32
Compiler:        HiTech PICC/MPLAB C18/MPLAB C30/MPLAB C32
Company:         Microchip Technology, Inc.

Copyright © 2010-2012 Microchip Technology Inc.  All rights reserved.

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

Author          Date    Comments
--------------------------------------------------------------------------------
KO/SP/AF        03-Aug-2012 v3.05
KO/SP/AF        29-Feb-2012 v3.04
KO/SP/AF        02-Feb-2012 v3.03, Limited distribution
KO/SP/AF        02-Dec-2011 v3.02
KO/SP/AF        14-Sep-2011 v3.01
Kimberly Otten/
  Sergey Pavlov 26-May-2011 v3.00
Kimberly Otten  17-Dec-2010 v2.05
Kimberly Otten  25-Oct-2010 v2.04
Kimberly Otten  23-Jul-2010 v2.03
Kimberly Otten  09-Jul-2010 v2.02
Kimberly Otten  22-Jun-2010 v2.01, Limited distribution
Kimberly Otten  13-May-2010 v2.0
Kimberly Otten  15-Apr-2010 v1.02, Limited distribution
Kimberly Otten  11-Mar-2010 v1.01
Kimberly Otten  22-Jan-2010 v1.0

*******************************************************************************/

#include "HardwareProfile.h"
#include "mfi_config.h"

#ifdef IPOD_USE_UART

#ifdef MFI_IPOD_UART_C

    ////////////////////////////////////////////////////////////////////////////////
    // Private

    // *****************************************************************************
    // Configuration Check
    // *****************************************************************************
    // Ensure that required definitions are in place
    #if defined ( __C30__ ) || defined( __PIC32MX__ )
        #if ! defined ( IPOD_UART ) || ! defined ( IPOD_UART_NUMBER )
            #error Please add IPOD_UART and IPOD_UART_NUMBER to the project HardwareProfile.h file
        #endif
    #endif

    // *****************************************************************************
    // Section: Macros
    // *****************************************************************************

    #define CONCAT3(t1, t2, t3)     _CONCAT3_(t1, t2, t3)
    #define _CONCAT3_(t1, t2, t3)   t1##t2##t3

    #define MU(reg)                 CONCAT3(U, IPOD_UART_NUMBER, reg)
    #define _MU(reg)                CONCAT3(_U, IPOD_UART_NUMBER, reg)
    #define MFI_UART                IPOD_UART

#else
    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif

////////////////////////////////////////////////////////////////////////////////
// Common

/****************************************************************************
  Function:
    void IMFI_UART_Disable( void )

  Description:
    This function disables the UART.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_Disable( void );
#else
    __inline__ void IMFI_UART_Disable( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_Enable( void )

  Description:
    This function enables the UART.

  Precondition:
    The UART should have already been configured by calling
    IMFI_UART_Initialize() and any application specific configuration.

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_Enable( void );
#else
    __inline__ void IMFI_UART_Enable( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_Initialize( void )

  Description:
    This function initializes the UART as much as possible, independent of
    application-specific information.  Users should not modify this function.
    Any initialization not handled here should be performed in the
    application itself, so modifications are not overwritten with library
    update installations.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void IMFI_UART_Initialize( void );


/****************************************************************************
  Function:
    UINT8 IMFI_UART_Receive( void )

  Description:
    This function returns the last byte received by the UART.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    The last byte received by the UART.

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    UINT8 IMFI_UART_Receive( void );
#else
    __inline__ UINT8 IMFI_UART_Receive( void );
#endif


/****************************************************************************
  Function:
    BOOL IMFI_UART_RxBytesAvailable( void )

  Description:
    This function indicates whether or not bytes are available to read from
    the UART receive buffer.  The function utilizes the Received Data
    Available bit available on certain architectures, so the library can
    extract all available bytes at one time.  If this capability is not
    available for the architecture, do not implement this function - the
    library is aware of the architectural limitation.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    // Do not define anything for PIC16F1/PIC18 - the library file knows that this
    // feature is not available on a PIC16F1/PIC18.
#else
    __inline__ BOOL IMFI_UART_RxBytesAvailable( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_RxInterruptClear( void )

  Description:
    This function clears the receive interrupt flag.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_RxInterruptClear( void );
#else
    __inline__ void IMFI_UART_RxInterruptClear( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_RxInterruptDisable( void )

  Description:
    This function disables the receive interrupt.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_RxInterruptDisable( void );
#else
    __inline__ void IMFI_UART_RxInterruptDisable( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_RxInterruptEnable( void )

  Description:
    This function enables the receive interrupt.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_RxInterruptEnable( void );
#else
    __inline__ void IMFI_UART_RxInterruptEnable( void );
#endif


/****************************************************************************
  Function:
    BOOL IMFI_UART_RxInterruptFired( void )

  Description:
    This function indicates if the receive interrupt has fired.

  Precondition:
    None

  Parameters:
    None - None

  Return Values:
    TRUE    - The receive interrupt has fired.
    FALSE   - The receive interrupt has not fired.

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    BOOL IMFI_UART_RxInterruptFired( void );
#else
    __inline__ BOOL IMFI_UART_RxInterruptFired( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_Transmit( UINT8 x)

  Description:
    This function transmits a byte out the UART.

  Precondition:
    None

  Parameters:
    UINT8 x - Byte to transmit.

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_Transmit( UINT8 x);
#else
    __inline__ void IMFI_UART_Transmit(UINT8 x);
#endif


/****************************************************************************
  Function:
    BOOL IMFI_UART_TxComplete( void )

  Description:
    This function returns whether or not UART transmission is complete.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

BOOL IMFI_UART_TxComplete( void );


/****************************************************************************
  Function:
    void IMFI_UART_TxEnable( void )

  Description:
    This function enables the transmitter.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    Some architectures require that the interrupt mode be set after the
    transmitter is enabled.
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_TxEnable( void );
#else
    __inline__ void IMFI_UART_TxEnable( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_TxEnableWithInterrupts( void )

  Description:
    This function enables the transmitter and the transmit interrupts.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    This function is provided to assist with the differences in architectures
    of how the first transmit interrupt is generated.
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_TxEnableWithInterrupts( void );
#else
    __inline__ void IMFI_UART_TxEnableWithInterrupts( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_TxInterruptClear( void )

  Description:
    This function clears the transmit interrupt.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_TxInterruptClear( void );
#else
    __inline__ void IMFI_UART_TxInterruptClear( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_TxInterruptDisable( void )

  Description:
    This function disables the transmit interrupt.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_TxInterruptDisable( void );
#else
    __inline__ void IMFI_UART_TxInterruptDisable( void );
#endif


/****************************************************************************
  Function:
    void IMFI_UART_TxInterruptEnable( void )

  Description:
    This function enables the transmit interrupt.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    void IMFI_UART_TxInterruptEnable( void );
#else
    __inline__ void IMFI_UART_TxInterruptEnable( void );
#endif


/****************************************************************************
  Function:
    BOOL IMFI_UART_TxInterruptFired( void )

  Description:
    This function indicates whether or not the transmit interrupt has fired.

  Precondition:
    None

  Parameters:
    None - None

  Return Values:
    TRUE    - The transmit interrupt has fired.
    FALSE   - The transmit interrupt has not fired.

  Remarks:
    None
  ***************************************************************************/

#if defined( _PIC14E ) || defined( __18CXX )
    BOOL IMFI_UART_TxInterruptFired( void );
#else
    __inline__ BOOL IMFI_UART_TxInterruptFired( void );
#endif


#endif
