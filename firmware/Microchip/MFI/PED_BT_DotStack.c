/******************************************************************************
    CandleDragon dotstack(tm) Drivers for the Apple MFI Development Library

This file provides the CandleDragon dotstack(tm) drivers for the Apple MFI
Development Library.  All supported architectures are included in this file.

DO NOT MODIFY THE API IN THIS FILE!  Modifications of the functions in this
file should be performed very carefully, since the MFI library is dependent
on these functions.  Also, note that this file will be overwritten whenever the
library is updated.  So be sure to archive any required changes.

******************************************************************************/
/******************************************************************************

File Name:       PED_BT_DotStack.c
Dependencies:    None
Processor:       PIC24-dsPIC/PIC32
Compiler:        MPLAB C30, MPLAB C32
Company:         Microchip Technology, Inc.

Copyright 2011-2012 Microchip Technology Inc.  All rights reserved.

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

*******************************************************************************/

#define PED_BT_DOTSTACK_C
#include "MFI/PED_BT_DotStack.h"

//****************************************************************************
// Section: Global Variables
//****************************************************************************

static const bt_uuid                IAP_SERVER_SERVICE_CLASS_ID
                                        = { 0xdecacafe, 0xdecadeaf, 0xdecafade, 0x00000000 };

DWORD                               androidReceiveCount;
BYTE                                androidReceiveError;
DWORD                               androidTransmitCount;
BYTE                                androidTransmitError;

LINK_INFO                           btLastConnectedInfo;

bt_bdaddr                           btDeviceAddress;
bt_spp_port_t                       *btPort;

bt_byte                             *btReceiveBufferPointer;
bt_uint                             btReceiveLength;
bt_uint                             btReceiveBytesRemaining;
bt_oem_recv_callback_fp             btReceiveCallback;

volatile bt_byte                    *btTransmitBufferPointer;
bt_uint                             btTransmitLength;
volatile bt_uint                    btTransmitBytesRemaining;
bt_oem_send_callback_fp             btTransmitCallback;

UINT8 *                             receiveRequestData;
bt_ulong                            receiveRequestLength;
bt_spp_receive_callback_fp          receiveRequestCallback;

static TIMER_DATA                   timers[BT_TIMER_MAX];
static bt_timer_callback_fp         timerCallbacks[BT_TIMER_MAX];

static volatile BLUETOOTH_FLAGS     flags;
static volatile BLUETOOTH_SIGNALS   signals;


/****************************************************************************
  ***************************************************************************/

void AndroidCallbackRead( bt_spp_port_t* port, bt_int bytes_received, void* param )
{
    androidReceiveCount = bytes_received;
    androidReceiveError = IPOD_SUCCESS;

    DotStack_ClearSignal( flags.bits.androidReceiving );
}

/****************************************************************************
  ***************************************************************************/

void AndroidCallbackWrite( bt_spp_port_t* port, bt_ulong bytes_sent, bt_spp_send_status_e status, void* param )
{
    androidTransmitCount    = bytes_sent;
    androidTransmitError    = status;

    DotStack_ClearSignal( flags.bits.androidTransmitting );
}

/****************************************************************************
  ***************************************************************************/

BOOL AndroidAppIsReadComplete ( void *androidDeviceHandle, BYTE *errorCode, DWORD *size )
{
    *size       = androidReceiveCount;
    *errorCode  = androidReceiveError;

    return ( flags.bits.androidReceiving == 0 );
}

/****************************************************************************
  ***************************************************************************/

BOOL AndroidAppIsWriteComplete ( void *androidDeviceHandle, BYTE *errorCode, DWORD *size )
{
    *size       = androidTransmitCount;
    *errorCode  = androidTransmitError;

    return ( flags.bits.androidTransmitting == 0 );
}

/****************************************************************************
  ***************************************************************************/

UINT8 AndroidAppRead ( void *androidDeviceHandle, BYTE *data, DWORD length )
{
    if ( bt_spp_receive ( btPort, (void *) data, length, AndroidCallbackRead ) == TRUE )
    {
        DotStack_SetSignal( flags.bits.androidReceiving );
        return PED_SUCCESS;
    }
    else
    {
        return PED_BUSY;
    }
}

/****************************************************************************
  ***************************************************************************/

void AndroidAppReadCancel( void *androidDeviceHandle )
{
    if (flags.bits.androidReceiving  )
    {
        DotStack_CancelReceive ();
        DotStack_ClearSignal( flags.bits.androidReceiving );
    }
}

/****************************************************************************
  ***************************************************************************/

UINT8 AndroidAppWrite ( void *androidDeviceHandle, BYTE * data, DWORD length )
{
    if ( bt_spp_send ( btPort, (void *) data, length, AndroidCallbackWrite ) == TRUE )
    {
        DotStack_SetSignal( flags.bits.androidTransmitting );
        return PED_SUCCESS;
    }
    else
    {
        return PED_BUSY;
    }
}


/****************************************************************************
  ***************************************************************************/

void DotStack_CallbackStart ( bt_bool success, void* param )
{
    if ( success )
    {
        //bt_oem_log_write ( "BTCBSS\r\n" );
        btPort = bt_spp_allocate ( bt_sys_get_l2cap_manager(), &DotStack_CallbackState, NULL );
        if ( ! bt_spp_listen ( btPort, RFCOMM_CHANNEL_IOS ) )
        {
            Nop();
            while ( 1 );    // Configuration error
        }
        if ( ! bt_spp_listen ( btPort, RFCOMM_CHANNEL_ANDROID ) )
        {
            Nop();
            while ( 1 );    // Configuration error
        }
    }
    else
    {
        //bt_oem_log_write ( "BTCBSSF " );
    }
}

/****************************************************************************
  ***************************************************************************/

void DotStack_CallbackState ( bt_spp_port_t* port, bt_spp_port_event_e evt, void* param )
{
    switch ( evt )
    {
        case SPP_PORT_EVENT_CONNECTION_FAILED:
            //bt_oem_log_write("Connection failed");
            Nop();
            break;

        case SPP_PORT_EVENT_CONNECTED:
            //bt_oem_log_write("Connected");
            DotStack_SetSignal( flags.bits.isAttached );
            if ( port->server_channel == RFCOMM_CHANNEL_IOS )
            {
                DotStack_SetSignal( flags.bits.isAttachediOS );
            }
            else if ( port->server_channel == RFCOMM_CHANNEL_ANDROID )
            {
                DotStack_SetSignal( flags.bits.isAttachedAndroid );
            }
            else
            {
                while (1);
            }
            break;

        case SPP_PORT_EVENT_DISCONNECTED:
            //bt_oem_log_write("Disconnected");
            DotStack_ClearSignal( flags.bits.isAttached );
            DotStack_ClearSignal( flags.bits.isAttachediOS );
            DotStack_ClearSignal( flags.bits.isAttachedAndroid );
            break;

        case SPP_PORT_EVENT_SEND_PROGRESS:
            //bt_oem_log_write("Sending...");
            break;

        default:
            break;
    }
}

/****************************************************************************
  ***************************************************************************/

void DotStack_CancelReceive ( void )
{
    DotStack_ClearSignal( flags.bits.tryingToReceive );
    bt_spp_cancel_receive ( btPort );
}

/****************************************************************************
  ***************************************************************************/

static void DotStack_CheckTimers ( void )
{
    UINT8   i;
    DWORD   time;

    time = TickGet();
    for ( i = 0; i < BT_TIMER_MAX; i++ )
    {
        if ( ( timers[i].duration != 0 ) &&
             ( ( (signed long)time - (signed long)timers[i].timeoutAt ) >= 0 ) )
        {
            bt_timer_callback_fp callback = timers[i].callback;

            timers[i].duration = 0;
            timers[i].callback = NULL;
            (*callback)();
        }
    }
}

/****************************************************************************
  Function:
    void DotStack_HandleReceive( void )

  Description:
    This routine is the interrupt handler for when a character is received
    by the UART.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/

void DotStack_HandleReceive( void )
{
    UINT8    temp;

    if ( IMFI_UART_RxInterruptFired() )
    {
        #if !defined( __18CXX )  && !defined( _PIC14E )
        while ( IMFI_UART_RxBytesAvailable() )
        #endif
        {
            temp = IMFI_UART_Receive();

            if (MFIIF_UART_RawBufferFull())
            {
                DotStack_SetSignalInISR( flags.bits.receiveBufferOverrun );

                //while (1);
            }
            else
            {
                MFIIF_UART_RawBufferPutByte( temp );
            }
        }

        DotStack_SetSignalInISR( signals.bits.btSignalReceive );

        IMFI_UART_RxInterruptClear();
    }
}

/****************************************************************************
  Function:
    void DotStack_HandleTransmit( void )

  Description:
    This routine is the interrupt handler for when a character can be
    transmitted by the UART.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    This routine is written with the assumption that there is always space
    for one byte in the transmit buffer.  If the interrupt mode is changed, or
    if multiple characters are written to the FIFO within this handler, then
    all UART writes (IMFI_UART_Transmit()) must be qualified with space available
    in the transmit buffer (!IMFI_UART_TxBufferFull()).
  ***************************************************************************/

void DotStack_HandleTransmit( void )
{
    if ( IMFI_UART_TxInterruptFired() )
    {
        if ( flags.bits.transmitting )
        {
            //while ( ( btTransmitBytesRemaining > 0 ) && ! IMFI_UART_TxBufferFull() )
            if ( btTransmitBytesRemaining > 0 )
            {
                IMFI_UART_Transmit( *btTransmitBufferPointer ); //send next byte from buffer if not finished
                btTransmitBufferPointer ++;
                btTransmitBytesRemaining --;
            }

            if (btTransmitBytesRemaining == 0)
            {
                DotStack_SetSignalInISR( signals.bits.btSignalTransmit );
                DotStack_ClearSignalInISR( flags.bits.transmitting );
            }
        }
        else
        {
            IMFI_UART_TxInterruptDisable();
        }

        IMFI_UART_TxInterruptClear();
    }
}

/****************************************************************************
  ***************************************************************************/

UINT8 DotStack_Initialize ( void )
{
    flags.value = 0;
    signals.value = 0;
    memset ( timerCallbacks, 0, sizeof ( timerCallbacks ) );

    #if defined ( BLUETOOTH_MODULE_SPI_nCSB )
        BLUETOOTH_MODULE_SPI_nCSB       = 1;
        BLUETOOTH_MODULE_SPI_nCSB_TRIS  = 1;
    #endif

    BLUETOOTH_MODULE_RESET          = 0;
    BLUETOOTH_MODULE_RESET_TRIS     = 0;
    DelayMs ( 10 );
    BLUETOOTH_MODULE_RESET          = 1;
    DelayMs ( 60 );

    // *****
    // Here is where the user should read the link key from non-volatile
    // memory, if supported.
    // *****
    memset ( &btLastConnectedInfo, 0x00, sizeof ( btLastConnectedInfo ) );

    MFIIF_UART_RawBufferReset();
    IMFI_UART_Initialize();

    return 0;
}

/****************************************************************************
  ***************************************************************************/

BOOL DotStack_IsAndroidAttached( void )
{
    return ( flags.bits.isAttachedAndroid == 1 );
}

/****************************************************************************
  ***************************************************************************/

BOOL DotStack_IsiPodAttached( void )
{
    return ( flags.bits.isAttachediOS == 1 );
}

/****************************************************************************
  ***************************************************************************/

BOOL DotStack_Receive (  UINT8 * data, bt_ulong dataLength, bt_spp_receive_callback_fp callback )
{
    if ( flags.bits.tryingToReceive )
    {
        // This should never occur - the upper layer must guard against this.
        while ( 1 );
        return FALSE;
    }

    DotStack_SetSignal( flags.bits.tryingToReceive );

    receiveRequestData          = data;
    receiveRequestLength        = dataLength;
    receiveRequestCallback      = callback;

    DotStack_ReceiveQueuedRequest ();

    return TRUE;
}

/****************************************************************************
  ***************************************************************************/

static BOOL DotStack_ReceiveQueuedRequest ( void )
{
    if ( bt_spp_receive ( btPort, (void *) receiveRequestData, receiveRequestLength, receiveRequestCallback ) == TRUE )
    {
        DotStack_ClearSignal( flags.bits.tryingToReceive );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/****************************************************************************
  ***************************************************************************/

BOOL DotStack_Send ( UINT8 * data, bt_ulong dataLength, bt_spp_send_callback_fp callback )
{
    return ( bt_spp_send ( btPort, (void *) data, dataLength, callback ) );
}

/****************************************************************************
  ***************************************************************************/

UINT8 DotStack_Shutdown ( void )
{
    bt_spp_disconnect ( btPort );

    flags.value = 0;

    BLUETOOTH_MODULE_RESET = 0;

    return 0;
}

/****************************************************************************
  ***************************************************************************/

UINT8 DotStack_Start ( void )
{
    DotStack_StartLogging();

    MFIIF_UART_RawBufferReset();

    IMFI_UART_RxInterruptEnable();
    IMFI_UART_Enable();

    hcitr_uart_init();

    bt_sys_init ( sdp_db, sdp_db_len );
    bt_spp_init ();

    bt_sys_start ( &DotStack_CallbackStart, NULL, HCI_SCAN_INQUIRY | HCI_SCAN_PAGE );

    return 0;
}

/****************************************************************************
  ***************************************************************************/

void DotStack_Tasks ( void )
{
    BLUETOOTH_SIGNALS   signalsCopy;

    DotStack_CheckTimers();

    if ( flags.bits.tryingToReceive )
    {
        DotStack_ReceiveQueuedRequest ();
    }

    DotStack_InterruptsDisable();
    signalsCopy = signals;
    signals.value = 0;
    DotStack_InterruptsEnable();

    if ( signalsCopy.bits.btSignalStack )
    {
        // The Bluetooth stack needs servicing.
        bt_signal_process_pending();
    }

    if ( signalsCopy.bits.btSignalReceive )
    {
        // If we have received all the bytes that were requested, call the
        // specified receive callback.  This will be somewhere in the BT stack.

        if ( btReceiveBytesRemaining != 0 )
        {
            while ( ( btReceiveBytesRemaining > 0 ) && ! MFIIF_UART_RawBufferEmpty() )
            {
                *btReceiveBufferPointer = MFIIF_UART_RawBufferGetByte();
                btReceiveBufferPointer ++;
                btReceiveBytesRemaining --;
            }

            if ( btReceiveBytesRemaining == 0 )
            {
                DotStack_ClearSignal( flags.bits.receiving );
                btReceiveCallback ( btReceiveLength );
            }
        }
    }

    if ( signalsCopy.bits.btSignalTransmit )
    {
        // If we have transmitted all the bytes we requested, call the
        // specified transmit callback.  This will be somewhere in the BT stack.
        btTransmitCallback ();
    }
}




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

#if defined( __C30__ )
    __inline__ void IMFI_UART_Enable( void )
    {
        BTU(MODEbits).UARTEN   = 1;
        BTU(STAbits).UTXEN     = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_Enable( void )
    {
        BTU(MODESET) = _BTU(MODE_ON_MASK);
        BTU(STASET)  = _BTU(STA_URXEN_MASK) | _BTU(STA_UTXEN_MASK);
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
    #if defined( __C30__ )
        BTU(MODE)               &= 0x2098;  // Retain USIDL, WAKE, RXINV, and BRGH from the application.
        BTU(STA)                = 0;

        // Set hardware flow control.
        BTU(MODEbits).RTSMD     = 0;
        BTU(MODEbits).UEN       = 2;

        // Set receive interrupt mode to interrupt when a character is in the receive buffer (so we don't miss any)
        BTU(STAbits).URXISEL1   = 0;
        BTU(STAbits).URXISEL0   = 0;

        // Set transmit interrupt mode to interrupt when transmit operation over (01)
        // NOTE - This has to be repeated when we turn on the transmitter
        BTU(STAbits).UTXISEL1   = 0;
        BTU(STAbits).UTXISEL0   = 1;

        // Disable the interrupts and reset the interrupt flags.bits.  We will enable them once we
        // know we have an iPod attached.
        IMFI_UART_RxInterruptDisable();
        IMFI_UART_TxInterruptDisable();
        IMFI_UART_RxInterruptClear();
        IMFI_UART_TxInterruptClear();

        // Establish transmit and receive interrupt priorities.  They must be identical.
        _BTU(TXIP)             = BT_UART_INTERRUPT_PRIORITY;
        _BTU(RXIP)             = BT_UART_INTERRUPT_PRIORITY;

        // Do not enable the UART until we know that an iPod has attached.  We
        // need to leave the RX and TX lines tristated.
    #elif defined( __PIC32MX__ )
        BTU(MODE)              &= 0x2098;  // Retain USIDL, WAKE, RXINV, and BRGH from the application.
        BTU(STA)               = 0;

        // Set hardware flow control.
        BTU(MODEbits).RTSMD    = 0;
        BTU(MODEbits).UEN      = 2;

        // Set receive interrupt mode to interrupt when a character is in the receive buffer (so we don't miss any)
        BTU(STAbits).URXISEL1 = 0;
        BTU(STAbits).URXISEL0 = 0;

        // Set transmit interrupt mode to interrupt when transmit operation over (01)
        // NOTE - This has to be repeated when we turn on the transmitter
        BTU(STAbits).UTXISEL1 = 0;
        BTU(STAbits).UTXISEL0 = 1;

        // Disable the interrupts and reset the interrupt flags.bits.  We will enable them once we
        // know we have an iPod attached.
        IMFI_UART_RxInterruptDisable();
        IMFI_UART_TxInterruptDisable();
        IMFI_UART_RxInterruptClear();
        IMFI_UART_TxInterruptClear();

        // Establish interrupt priority.
        INTSetVectorPriority ( INT_VECTOR_UART ( BT_UART ), BT_UART_INT_PRIORITY );
        INTSetVectorSubPriority ( INT_VECTOR_UART ( BT_UART ), BT_UART_INT_SUBPRIORITY );

        // Do not enable the UART until we know that an iPod has attached.  We
        // need to leave the RX and TX lines tristated.
    #else
        #error UART initialization is undefined.
    #endif

    DotStack_InitializeLogging();
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

#if defined( __C30__ )
    __inline__ UINT8 IMFI_UART_Receive( void )
    {
        if ( BTU(STAbits).OERR || BTU(STAbits).FERR )
        {
            DotStack_SetSignalInISR( flags.bits.receiveError );
        }
        BTU(STAbits).OERR = 0;             // Clear any overflow error that occurred.
        return BTU(RXREG);
    }
#elif defined( __PIC32MX__ )
    __inline__ UINT8 IMFI_UART_Receive( void )
    {
        UINT8 temp;

        if ( BTU(STAbits).OERR || BTU(STAbits).FERR )
        {
            DotStack_SetSignalInISR( flags.bits.receiveError );
        }
        temp = BTU(RXREG);
        BTU(STACLR) = _BTU(STA_OERR_MASK);    // Clear any overflow error that occurred.
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

#if defined( __C30__ )
    __inline__ BOOL IMFI_UART_RxBytesAvailable( void )
    {
        return BTU(STAbits).URXDA;
    }
#elif defined( __PIC32MX__ )
    __inline__ BOOL IMFI_UART_RxBytesAvailable( void )
    {
        return BTU(STAbits).URXDA;
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_RxInterruptClear( void )
    {
        _BTU(RXIF) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_RxInterruptClear( void )
    {
       INTClearFlag ( INT_SOURCE_UART_RX ( BT_UART ) );
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_RxInterruptDisable( void )
    {
        _BTU(RXIE) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_RxInterruptDisable( void )
    {
        INTEnable ( INT_SOURCE_UART_RX ( BT_UART ), INT_DISABLED );
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_RxInterruptEnable( void )
    {
        _BTU(RXIE) = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_RxInterruptEnable( void )
    {
        INTEnable ( INT_SOURCE_UART_RX ( BT_UART ), INT_ENABLED );
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
    The PIC32 Plib returns 0 or not 0.
  ***************************************************************************/

#if defined( __C30__ )
    __inline__ BOOL IMFI_UART_RxInterruptFired( void )
    {
        return ( _BTU(RXIF) == 1 );
    }
#elif defined( __PIC32MX__ )
    __inline__ BOOL IMFI_UART_RxInterruptFired( void )
    {
        return ( INTGetFlag ( INT_SOURCE_UART_RX ( BT_UART ) ) != 0 );
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_Transmit(UINT8 x)
    {
        BTU(TXREG) = x;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_Transmit( UINT8 x )
    {
        BTU(TXREG) = x;
    }
#else
    #error Unsupported processor
#endif


/****************************************************************************
  Function:
    BOOL IMFI_UART_TxBufferFull( void )

  Description:
    This function indicates whether or not space is available in the UART
    transmit buffer.  The function utilizes the Transmit Buffer Full bit
    available on certain architectures, so the library can load as many bytes
    as possible at one time.  If this capability is not available for the
    architecture, do not implement this function, and rework any code that
    requires it such that only one byte is transmitted.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( __C30__ )
    __inline__ BOOL IMFI_UART_TxBufferFull( void )
    {
        return BTU(STAbits).UTXBF;
    }
#elif defined( __PIC32MX__ )
    __inline__ BOOL IMFI_UART_TxBufferFull( void )
    {
        return BTU(STAbits).UTXBF;
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
    #if defined( __C30__ )
        return( BTU(STAbits).TRMT == 1 );
    #elif defined( __PIC32MX__ )
        return( BTU(STAbits).TRMT == 1 );
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_TxEnable( void )
    {
        // Make sure the transmitter is completely finished.
        while ( BTU(STAbits).TRMT == 0 );

        BTU(STAbits).UTXEN    = 0;
        BTU(STAbits).UTXEN    = 1;
        BTU(STAbits).UTXISEL1 = 0;
        BTU(STAbits).UTXISEL0 = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxEnable( void )
    {
        // Make sure the transmitter is completely finished.
        while ( BTU(STAbits).TRMT == 0 );

        BTU(STACLR) = _BTU(STA_UTXEN_MASK);
        BTU(STASET) = _BTU(STA_UTXEN_MASK);
        BTU(STACLR) = _BTU(STA_UTXISEL1_MASK);
        BTU(STASET) = _BTU(STA_UTXISEL0_MASK);
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_TxEnableWithInterrupts( void )
    {
        // Make sure the transmitter is completely finished.
        while ( BTU(STAbits).TRMT == 0 );

        BTU(STAbits).UTXEN    = 0;
        BTU(STAbits).UTXEN    = 1;
        BTU(STAbits).UTXISEL1 = 0;
        BTU(STAbits).UTXISEL0 = 1;
        IMFI_UART_TxInterruptEnable();
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxEnableWithInterrupts( void )
    {
        // Make sure the transmitter is completely finished.
        while ( BTU(STAbits).TRMT == 0 );

        BTU(STACLR) = _BTU(STA_UTXEN_MASK);
        BTU(STASET) = _BTU(STA_UTXEN_MASK);
        BTU(STACLR) = _BTU(STA_UTXISEL1_MASK);
        BTU(STASET) = _BTU(STA_UTXISEL0_MASK);
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_TxInterruptClear( void )
    {
        _BTU(TXIF) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxInterruptClear( void )
    {
       INTClearFlag ( INT_SOURCE_UART_TX ( BT_UART ) );
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_TxInterruptDisable( void )
    {
        _BTU(TXIE) = 0;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxInterruptDisable( void )
    {
        INTEnable ( INT_SOURCE_UART_TX ( BT_UART ), INT_DISABLED );
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

#if defined( __C30__ )
    __inline__ void IMFI_UART_TxInterruptEnable( void )
    {
        _BTU(TXIE) = 1;
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxInterruptEnable( void )
    {
        INTEnable ( INT_SOURCE_UART_TX ( BT_UART ), INT_ENABLED );
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
    The PIC32 Plib returns 0 or not 0.
  ***************************************************************************/

#if defined( __C30__ )
    __inline__ BOOL IMFI_UART_TxInterruptFired( void )
    {
        return _BTU(TXIF);
    }
#elif defined( __PIC32MX__ )
    __inline__ BOOL IMFI_UART_TxInterruptFired( void )
    {
        return ( INTGetFlag ( INT_SOURCE_UART_TX ( BT_UART ) ) != 0 );
    }
#else
    #error Unsupported processor
#endif

/****************************************************************************
  Function:
    void IMFI_UART_TxInterruptSet( void )

  Description:
    This function sets the transmit interrupt.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

#if defined( __C30__ )
    __inline__ void IMFI_UART_TxInterruptSet( void )
    {
        DotStack_InterruptsDisable();
        _BTU(TXIF) = 1;
        DotStack_InterruptsEnable();
    }
#elif defined( __PIC32MX__ )
    __inline__ void IMFI_UART_TxInterruptSet( void )
    {
        INTSetFlag ( INT_SOURCE_UART_TX ( BT_UART ) );
    }
#else
    #error Unsupported processor
#endif


//****************************************************************************
//****************************************************************************
//****************************************************************************

/****************************************************************************
  ***************************************************************************/

void bt_oem_linkkey_notification ( bt_evt_linkkey_notification_t* lkn )
{
    btLastConnectedInfo.addr = lkn->bdaddr_remote;
    memcpy ( btLastConnectedInfo.linkKey, lkn->key, LKS_LINK_KEY_LEN);

    // *****
    // Here is where the user should store the link key into non-volatile
    // memory, if supported.
    // *****
}

/****************************************************************************
  ***************************************************************************/

void bt_oem_linkkey_request ( bt_evt_linkkey_request_t* lkr )
{
    if ( btLastConnectedInfo.addr.bd_addr_l == lkr->bdaddr_remote.bd_addr_l &&
         btLastConnectedInfo.addr.bd_addr_m == lkr->bdaddr_remote.bd_addr_m )
    {
        bt_hci_send_linkkey ( &lkr->bdaddr_remote, btLastConnectedInfo.linkKey, NULL );
    }
    else
    {
        bt_hci_send_linkkey ( &lkr->bdaddr_remote, NULL, NULL );
    }
}

/****************************************************************************
  ***************************************************************************/

void bt_oem_recv ( bt_byte * buffer, bt_uint len, bt_oem_recv_callback_fp callback )
{
    btReceiveBufferPointer      = buffer;
    btReceiveLength             = len;
    btReceiveBytesRemaining     = len;
    btReceiveCallback           = callback;

    DotStack_SetSignal( flags.bits.receiving );
    DotStack_SetSignal( signals.bits.btSignalReceive );
}

/****************************************************************************
  ***************************************************************************/

void bt_oem_schedule_signals(void)
{
    DotStack_SetSignal( signals.bits.btSignalStack );
}

/****************************************************************************
  ***************************************************************************/

void bt_oem_send ( const bt_byte * buffer, bt_uint len, bt_oem_send_callback_fp callback )
{
    if ( btTransmitCallback == NULL )
    {
        Nop();
    }

    btTransmitBufferPointer     = (bt_byte *) buffer;
    btTransmitLength            = len;
    btTransmitBytesRemaining    = len;
    btTransmitCallback          = callback;

    DotStack_SetSignal( flags.bits.transmitting );

    while ( BTU(STAbits).TRMT == 0 );
    IMFI_UART_TxInterruptSet();
    IMFI_UART_TxInterruptEnable();
}

/****************************************************************************
  ***************************************************************************/

void bt_oem_timer_clear ( bt_uint timerId )
{
    timers[timerId].duration = 0;
    timers[timerId].callback = NULL;
}

/****************************************************************************
  ***************************************************************************/

void bt_oem_timer_set(bt_uint timerId, bt_ulong milliseconds, bt_timer_callback_fp callback)
{
    timers[timerId].duration = (DWORD) milliseconds;
    timers[timerId].timeoutAt = TickGet() + ( ( (DWORD) milliseconds + 1 ) * dwTicksPerMillisecond );
    timers[timerId].callback = callback;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

#if defined ( ENABLE_DOTSTACK_LOGGING )

    #define LOG_BUFFER_SIZE        (2048)   // must be a power of 2
    #define LOG_BUFFER_SIZE_MASK   (LOG_BUFFER_SIZE - 1)

    static char           mLogBuffer[LOG_BUFFER_SIZE];
    static volatile int   mLogHead;
    static int            mLogTail;
    static volatile char  mLogUartBusy;
    static char           mLogOverflow;

    static void DotStack_InitializeLogging(void)
    {
        mLogHead = mLogTail = 0;
        mLogUartBusy = 0;
        mLogOverflow = 0;

        LOGU(MODEbits).BRGH     = 1; // Use high speed baud generator
        LOGU(MODEbits).STSEL    = 0; // One stop bit
        LOGU(MODEbits).PDSEL    = 0; // 8 data bits, no parity
        LOGU(MODEbits).ABAUD    = 0; // Disable auto baud rate
        LOGU(MODEbits).LPBACK   = 0; // Disable loopback
        LOGU(MODEbits).WAKE     = 0; // Disable wake up on receive during Sleep mode
        LOGU(MODEbits).UEN      = 0; // Disable RTS/CTS flow control
        LOGU(MODEbits).IREN     = 0; // Disable IrDA
        LOGU(MODEbits).USIDL    = 0; // Continue operation in Idle mode
        LOGU(MODEbits).UARTEN   = 1; // Enable UART

        LOGU(BRG)               = LOG_BRG;

        LOGU(STAbits).UTXEN     = 1; // Enable transmitter.
        LOGU(STAbits).URXISEL   = 0; // Interrupt on receiving single byte.
        LOGU(STAbits).UTXISEL0  = 0; // Interrupt when any character is transferred to the Transmit Shift Register
        LOGU(STAbits).UTXISEL1  = 0; //   (this implies at least one location is empty in the transmit buffer).

        #if defined ( __C30__ )
            _LOGU(RXIF)             = 0; // clear Rx interrupt flag
            _LOGU(TXIF)             = 0; // clear Tx interrupt flag
            _LOGU(RXIP)             = LOG_INTERRUPT_PRIORITY;
            _LOGU(TXIP)             = LOG_INTERRUPT_PRIORITY;
        #elif defined ( __PIC32MX__ )
            INTSetVectorPriority ( INT_VECTOR_UART ( LOG_UART ), LOG_INTERRUPT_PRIORITY );
            INTSetVectorSubPriority ( INT_VECTOR_UART ( LOG_UART ), LOG_INTERRUPT_SUBPRIORITY );
            INTClearFlag ( INT_SOURCE_UART_RX ( LOG_UART ) );
            INTClearFlag ( INT_SOURCE_UART_TX ( LOG_UART ) );
        #endif

        LOGU(MODEbits).UARTEN = 0; // Disable UART
    }


    static void DotStack_StartLogging(void)
    {
        LOGU(MODEbits).UARTEN  = 1;  // Enable UART
        LOGU(STAbits).UTXEN    = 1;  // Enable transmitter

    }


    void bt_oem_log_write(const char* msg)
    {
        int avail;
        int len = strlen(msg);

        DISABLE_INTERRUPTS();
        // Free space available in the buffer
        avail = LOG_BUFFER_SIZE - 1 - ((mLogTail - mLogHead) & LOG_BUFFER_SIZE_MASK);
        ENABLE_INTERRUPTS();
        avail -= 3; // reserve space for the overflow indicator

        if (len > avail)
        {
            if (mLogOverflow)
                return;
            mLogOverflow = 1;
            msg = "*\r\n";  // overflow indicator
            len = 3;
        }
        else
        {
            mLogOverflow = 0;
        }

        if (len > 0)
        {
            if ((LOG_BUFFER_SIZE - mLogTail) >= len)
            {
                // Whole message can be written at once.
                memcpy(mLogBuffer + mLogTail, msg, len);
            }
            else
            {
                // Part of the message is written to the end of the buffer
                // and next part to the begining.

                // Free bytes available from the tail pointer to the end of the buffer
                int avail2 = LOG_BUFFER_SIZE - mLogTail;
                memcpy(mLogBuffer + mLogTail, msg, avail2);
                memcpy(mLogBuffer, msg + avail2, len - avail2);
            }

            DISABLE_INTERRUPTS();
            mLogTail = (mLogTail + len) & LOG_BUFFER_SIZE_MASK;
            if (!mLogUartBusy)
            {
                mLogUartBusy = 1;
                LOGU(TXREG) = mLogBuffer[mLogHead];
                mLogHead = (mLogHead + 1) & LOG_BUFFER_SIZE_MASK;

                #if defined ( __C30__ )
                    _LOGU(TXIE) = 1;
                #elif defined ( __PIC32MX__ )
                    INTEnable ( INT_SOURCE_UART_TX ( LOG_UART ), INT_ENABLED );
                #endif
            }
            ENABLE_INTERRUPTS();
        }
    }


    void __attribute__((interrupt, no_auto_psv)) _LOGU(TXInterrupt)(void)
    {
        if (mLogHead != mLogTail)
        {
            LOGU(TXREG) = mLogBuffer[mLogHead];
            mLogHead = (mLogHead + 1) & LOG_BUFFER_SIZE_MASK;
        }
        else
        {
            mLogUartBusy = 0;

            #if defined( __C30__ )
                _LOGU(TXIE) = 0;
            #elif defined( __PIC32MX__ )
                INTEnable ( INT_SOURCE_UART_TX ( LOG_UART ), INT_DISABLED );
            #endif
        }

        #if defined ( __C30__ )
            _LOGU(TXIF) = 0; // clear Tx interrupt flag
        #elif defined ( __PIC32MX__ )
            INTClearFlag ( INT_SOURCE_UART_TX ( LOG_UART ) );
        #endif
    }

#else

    static void DotStack_InitializeLogging ( void ) {}
    static void DotStack_StartLogging ( void ) {}
    void bt_oem_log_write ( const char* msg ) {}

#endif

