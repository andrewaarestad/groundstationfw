/******************************************************************************
    UART Drivers for the Apple MFI Development Library

This file provides the UART drivers for the Apple MFI Development Library.
All architectures are included in this file.

DO NOT MODIFY THE API IN THIS FILE!  Modifications of the functions in this
file should be performed very carefully, since the MFI library is dependent
on these functions.  Also, note that this file will be overwritten whenever the
library is updated.  So be sure to archive any required changes.

******************************************************************************/
/******************************************************************************

File Name:       MFI_iPod_UART.c
Dependencies:    None
Processor:       PIC16F1/PIC18/PIC24-dsPIC/PIC32
Compiler:        HiTech PICC/MPLAB C18/MPLAB C30/MPLAB C32
Company:         Microchip Technology, Inc.

Copyright 2010-2012 Microchip Technology Inc.  All rights reserved.

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

#define MFI_IPOD_UART_C

#include "GenericTypeDefs.h"
#include "Compiler.h"

#include "mfi_config.h"

#include "MFI/MFI_iPod.h"
#include "MFI/MFI_iPod_UART.h"


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
#if defined ( _PIC14E )
    void IMFI_UART_Disable( void )
    {
        // Make sure the transmitter is completely finished.
        while (!TX1STAbits.TRMT) {};
        RCSTA = 0x00;
    }
#elif defined( __18CXX )
    void IMFI_UART_Disable( void )
    {
        // Make sure the transmitter is completely finished.
        while (!TXSTA1bits.TRMT) {};
        RCSTA1 = 0x00;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_Disable( void )
    {
        // Make sure the transmitter is completely finished.
        while(MU(STAbits).TRMT == 0);

        MU(STAbits).UTXEN    = 0;
        MU(MODEbits).UARTEN  = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_Disable( void )
    {
        // Make sure the transmitter is completely finished.
        while(MU(STAbits).TRMT == 0);

        MU(STACLR)  = _MU(STA_URXEN_MASK) | _MU(STA_UTXEN_MASK);
        MU(MODECLR) = _MU(MODE_ON_MASK);
    }
#else
    #error Unsupported processor
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
#if defined( _PIC14E )
    void IMFI_UART_Enable( void )
    {
        RCSTA               = 0x90;
    }
#elif defined( __18CXX )
    void IMFI_UART_Enable( void )
    {
        RCSTA1              = 0x90;
        //HACK to turn on UART2 also
        RCSTA2              = 0x90;
        Nop();
        Nop();
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_Enable( void )
    {
        MU(MODEbits).UARTEN   = 1;
        MU(STAbits).UTXEN     = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_Enable( void )
    {
        MU(MODESET) = _MU(MODE_ON_MASK);
        MU(STASET)  = _MU(STA_URXEN_MASK) | _MU(STA_UTXEN_MASK);
    }
#else
    #error Unsupported processor
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

void IMFI_UART_Initialize( void )
{
    #if defined ( _PIC14E )
        // Initialize as much of the UART as we can.
        TXSTA              &= 0x04;    // Clear everything except BRGH.
        TX1STAbits.TXEN     = 1;        // Enable transmitter
    #elif defined( __18CXX )
        // Initialize as much of the UART as we can.
        TXSTA1              &= 0x04;    // Clear everything except BRGH.
        TXSTA1bits.TXEN     = 1;        // Enable transmitter
    #elif defined( __C30__ )
        MU(MODEbits).UARTEN   = 0;      // Turn off the module.  Retain user settings.
        MU(STA)               = 0;

        // Set receive interrupt mode to interrupt when a character is in the receive buffer (so we don't miss any)
        MU(STAbits).URXISEL1 = 0;
        MU(STAbits).URXISEL0 = 0;

        // Set transmit interrupt mode to interrupt when transmit operation over (01)
        // NOTE - This has to be repeated when we turn on the transmitter
        MU(STAbits).UTXISEL1 = 0;
        MU(STAbits).UTXISEL0 = 1;

        // Disable the interrupts and reset the interrupt flags.  We will enable them once we
        // know we have an iPod attached.
        IMFI_UART_RxInterruptDisable();
        IMFI_UART_TxInterruptDisable();
        IMFI_UART_RxInterruptClear();
        IMFI_UART_TxInterruptClear();

        // Establish transmit and receive interrupt priorities.
        _MU(TXIP) = 4;
        _MU(RXIP) = 4;

        // Do not enable the UART until we know that an iPod has attached.  We
        // need to leave the RX and TX lines tristated.
    #elif defined( __PIC32MX__ )
        MU(MODECLR) = _MU(MODE_ON_MASK);    // Turn off the module.  Retain user settings.
        MU(STA)               = 0;

        // Set receive interrupt mode to interrupt when a character is in the receive buffer (so we don't miss any)
        MU(STAbits).URXISEL1 = 0;
        MU(STAbits).URXISEL0 = 0;

        // Set transmit interrupt mode to interrupt when transmit operation over (01)
        // NOTE - This has to be repeated when we turn on the transmitter
        MU(STAbits).UTXISEL1 = 0;
        MU(STAbits).UTXISEL0 = 1;

        // Disable the interrupts and reset the interrupt flags.  We will enable them once we
        // know we have an iPod attached.
        IMFI_UART_RxInterruptDisable();
        IMFI_UART_TxInterruptDisable();
        IMFI_UART_RxInterruptClear();
        IMFI_UART_TxInterruptClear();

        // Establish interrupt priority.
        INTSetVectorPriority ( INT_VECTOR_UART ( MFI_UART ), 4 );
        INTSetVectorSubPriority ( INT_VECTOR_UART ( MFI_UART ), 0 );

        // Do not enable the UART until we know that an iPod has attached.  We
        // need to leave the RX and TX lines tristated.
    #else
        #error UART initialization is undefined.
    #endif
}


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
    This implementation does no special checks for reception errors.  It
    simply clears the error to enable reception of the next byte.  Corrupt
    data packets will be handled by the library.
  ***************************************************************************/

#if defined ( _PIC14E )
    UINT8 IMFI_UART_Receive( void )
    {
        return RCREG;
    }
#elif defined( __18CXX )
    UINT8 IMFI_UART_Receive( void )
    {
        if (RCSTA1bits.OERR)
        {
            RCSTA1bits.CREN = 0;            // Clear any overflow error that occurred.
            RCSTA1bits.CREN = 1;
        }
        return RCREG1;
    }
#elif defined( __C30__ )
    __inline__ UINT8 IMFI_UART_Receive( void )
    {
        MU(STAbits).OERR = 0;             // Clear any overflow error that occurred.
        return MU(RXREG);
    }
#elif defined( __PIC32MX__ )
    __inline__ UINT8 IMFI_UART_Receive( void )
    {
        UINT8 temp;

        temp = MU(RXREG);
        MU(STACLR) = _MU(STA_OERR_MASK);    // Clear any overflow error that occurred.
        return temp;
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    // Do not define anything for PIC16 - the library file knows that this
    // feature is not available on a PIC16.
#elif defined( __18CXX )
    // Do not define anything for PIC18 - the library file knows that this
    // feature is not available on a PIC18.
#elif defined( __C30__ )
    __inline__ BOOL IMFI_UART_RxBytesAvailable( void )
    {
        return MU(STAbits).URXDA;
    }
#elif defined( __PIC32MX__ )
    __inline__ BOOL IMFI_UART_RxBytesAvailable( void )
    {
        return MU(STAbits).URXDA;
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_RxInterruptClear( void )
    {
        PIR1bits.RCIF = 0;
    }
#elif defined( __18CXX )
    void IMFI_UART_RxInterruptClear( void )
    {
        PIR1bits.RC1IF = 0;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_RxInterruptClear( void )
    {
        _MU(RXIF) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_RxInterruptClear( void )
    {
       INTClearFlag ( INT_SOURCE_UART_RX ( MFI_UART ) );
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_RxInterruptDisable( void )
    {
        PIE1bits.RCIE = 0;
    }
#elif defined( __18CXX )
    void IMFI_UART_RxInterruptDisable( void )
    {
        PIE1bits.RC1IE = 0;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_RxInterruptDisable( void )
    {
        _MU(RXIE) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_RxInterruptDisable( void )
    {
        INTEnable ( INT_SOURCE_UART_RX ( MFI_UART ), INT_DISABLED );
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_RxInterruptEnable( void )
    {
        PIE1bits.RCIE = 1;
    }
#elif defined( __18CXX )
    void IMFI_UART_RxInterruptEnable( void )
    {
        PIE1bits.RC1IE = 1;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_RxInterruptEnable( void )
    {
        _MU(RXIE) = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_RxInterruptEnable( void )
    {
        INTEnable ( INT_SOURCE_UART_RX ( MFI_UART ), INT_ENABLED );
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    BOOL IMFI_UART_RxInterruptFired( void )
    {
        return (PIE1bits.RCIE && PIR1bits.RCIF);
    }
#elif defined( __18CXX )
    BOOL IMFI_UART_RxInterruptFired( void )
    {
        return (PIE1bits.RC1IE && PIR1bits.RC1IF);
    }
#elif defined( __C30__ )
    __inline__ BOOL IMFI_UART_RxInterruptFired( void )
    {
        return ( _MU(RXIF) == 1 );
    }
#elif defined( __PIC32MX__ )
    __inline__ BOOL IMFI_UART_RxInterruptFired( void )
    {
        return ( INTGetFlag ( INT_SOURCE_UART_RX ( MFI_UART ) ) != 0 );
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_Transmit( UINT8 x)
    {
        TXREG = x;
    }
#elif defined( __18CXX )
    void IMFI_UART_Transmit( UINT8 x)
    {
        TXREG1 = x;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_Transmit(UINT8 x)
    {
        MU(TXREG) = x;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_Transmit( UINT8 x )
    {
        MU(TXREG) = x;
    }
#else
    #error Unsupported processor
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

BOOL IMFI_UART_TxComplete( void )
{
    #if defined ( _PIC14E )
        return( TX1STAbits.TRMT = 1 );
    #elif defined( __18CXX )
        return( TXSTA1bits.TRMT = 1 );
    #elif defined( __C30__ )
        return( MU(STAbits).TRMT == 1 );
    #elif defined( __PIC32MX__ )
        return( MU(STAbits).TRMT == 1 );
    #else
        #error Unsupported processor
    #endif
}


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

#if defined( _PIC14E )
    void IMFI_UART_TxEnable( void )
    {
        TX1STAbits.TXEN = 1;
    }
#elif defined( __18CXX )
    void IMFI_UART_TxEnable( void )
    {
        TXSTA1bits.TXEN = 1;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_TxEnable( void )
    {
        // Make sure the transmitter is completely finished.
        while ( MU(STAbits).TRMT == 0 );

        MU(STAbits).UTXEN    = 0;
        MU(STAbits).UTXEN    = 1;
        MU(STAbits).UTXISEL1 = 0;
        MU(STAbits).UTXISEL0 = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxEnable( void )
    {
        // Make sure the transmitter is completely finished.
        while ( MU(STAbits).TRMT == 0 );

        MU(STACLR) = _MU(STA_UTXEN_MASK);
        MU(STASET) = _MU(STA_UTXEN_MASK);
        MU(STACLR) = _MU(STA_UTXISEL1_MASK);
        MU(STASET) = _MU(STA_UTXISEL0_MASK);
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_TxEnableWithInterrupts( void )
    {
        // Make sure the transmitter is completely finished.
        while ( !TX1STAbits.TRMT ) {};

        TX1STAbits.TXEN = 0;
        IMFI_UART_TxInterruptEnable();
        TX1STAbits.TXEN = 1;
    }
#elif defined( __18CXX )
    void IMFI_UART_TxEnableWithInterrupts( void )
    {
        // Make sure the transmitter is completely finished.
        while ( !TXSTA1bits.TRMT ) {};

        TXSTA1bits.TXEN = 0;
        IMFI_UART_TxInterruptEnable();
        TXSTA1bits.TXEN = 1;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_TxEnableWithInterrupts( void )
    {
        // Make sure the transmitter is completely finished.
        while ( MU(STAbits).TRMT == 0 );

        MU(STAbits).UTXEN    = 0;
        MU(STAbits).UTXEN    = 1;
        MU(STAbits).UTXISEL1 = 0;
        MU(STAbits).UTXISEL0 = 1;
        IMFI_UART_TxInterruptEnable();
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxEnableWithInterrupts( void )
    {
        // Make sure the transmitter is completely finished.
        while ( MU(STAbits).TRMT == 0 );

        MU(STACLR) = _MU(STA_UTXEN_MASK);
        MU(STASET) = _MU(STA_UTXEN_MASK);
        MU(STACLR) = _MU(STA_UTXISEL1_MASK);
        MU(STASET) = _MU(STA_UTXISEL0_MASK);
        IMFI_UART_TxInterruptEnable();
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_TxInterruptClear( void )
    {
        PIR1bits.TXIF = 0;
    }
#elif defined( __18CXX )
    void IMFI_UART_TxInterruptClear( void )
    {
        PIR1bits.TX1IF = 0;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_TxInterruptClear( void )
    {
        _MU(TXIF) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxInterruptClear( void )
    {
       INTClearFlag ( INT_SOURCE_UART_TX ( MFI_UART ) );
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_TxInterruptDisable( void )
    {
        PIE1bits.TXIE = 0;
    }
#elif defined( __18CXX )
    void IMFI_UART_TxInterruptDisable( void )
    {
        PIE1bits.TX1IE = 0;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_TxInterruptDisable( void )
    {
        _MU(TXIE) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxInterruptDisable( void )
    {
        INTEnable ( INT_SOURCE_UART_TX ( MFI_UART ), INT_DISABLED );
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    void IMFI_UART_TxInterruptEnable( void )
    {
        PIE1bits.TXIE = 1;
    }
#elif defined( __18CXX )
    void IMFI_UART_TxInterruptEnable( void )
    {
        PIE1bits.TX1IE = 1;
    }
#elif defined( __C30__ )
    __inline__ void IMFI_UART_TxInterruptEnable( void )
    {
        _MU(TXIE) = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxInterruptEnable( void )
    {
        INTEnable ( INT_SOURCE_UART_TX ( MFI_UART ), INT_ENABLED );
    }
#else
    #error Unsupported processor
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

#if defined( _PIC14E )
    BOOL IMFI_UART_TxInterruptFired( void )
    {
        return (PIE1bits.TXIE && PIR1bits.TXIF);
    }
#elif defined( __18CXX )
    BOOL IMFI_UART_TxInterruptFired( void )
    {
        return (PIE1bits.TX1IE && PIR1bits.TX1IF);
    }
#elif defined( __C30__ )
    __inline__ BOOL IMFI_UART_TxInterruptFired( void )
    {
        return _MU(TXIF);
    }
#elif defined( __PIC32MX__ )
    __inline__ BOOL IMFI_UART_TxInterruptFired( void )
    {
        return ( INTGetFlag ( INT_SOURCE_UART_TX ( MFI_UART ) ) != 0 );
    }
#else
    #error Unsupported processor
#endif




