/******************************************************************************
    dotstack Bluetooth Stack Drivers for the
    PED Universal Framework

******************************************************************************/
/******************************************************************************

File Name:       PED_BT_DotStack.h
Dependencies:    None
Processor:       PIC16F1/PIC18/PIC24-dsPIC/PIC32
Company:         Microchip Technology, Inc.

Copyright © 2011-2012 Microchip Technology Inc.  All rights reserved.

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

*******************************************************************************/

#ifndef PED_BT_DOTSTACK_H
#define PED_BT_DOTSTACK_H

////////////////////////////////////////////////////////////////////////////////
// Common

//******************************************************************************
// Section: Includes
//******************************************************************************

#include "Compiler.h"
#include "GenericTypedefs.h"

#include "btconfig.h"
#include "sdpdb.h"
#include "stdapp.h"
#include "cdbt/bt/bt_std.h"
#include "cdbt/bt/bt_hcitr.h"
#include "cdbt/bt/bt_oem.h"
#include "cdbt/bt/bt_system.h"
#include "cdbt/bt/bt_timer.h"
#include "cdbt/hci/hci.h"
#include "cdbt/hci/hcitr_uart.h"
#include "cdbt/spp/spp.h"
#include "cdbt/spp/spp_config.h"


#ifdef PED_BT_DOTSTACK_C


    ////////////////////////////////////////////////////////////////////////////////
    // Private

    #include "HardwareProfile.h"

    //******************************************************************************
    // Section: Configuration
    //******************************************************************************

    #define BLUETOOTH_DEBUG

    //******************************************************************************
    // Section: Includes
    //******************************************************************************

    #include "mfi_config.h"
    #include "MFI/MFI_iPod.h"
    #include "MFI/MFI_Data.h"

    #include "MFI/PED_Universal.h"

    #include "Tick.h"
    #include "TimeDelay.h"


    //******************************************************************************
    // Section: Constants
    //******************************************************************************

    #define RFCOMM_CHANNEL_ANDROID          RFCOMM_SERIAL_PORT_CH_2 // Must match the SDP database entry
    #define RFCOMM_CHANNEL_IOS              RFCOMM_SERIAL_PORT_CH_1 // Must match the SDP database entry

    //******************************************************************************
    // Section: Data Structures
    //******************************************************************************


    // *****************************************************************************
    /* Internal Flags
    */
    typedef union
    {
        struct
        {
            UINT8                       isAttached              : 1;
            UINT8                       isAttachedAndroid       : 1;
            UINT8                       isAttachediOS           : 1;
            UINT8                       tryingToReceive         : 1;

            UINT8                       receiveError            : 1;
            UINT8                       receiveBufferOverrun    : 1;
            UINT8                       transmitting            : 1;
            UINT8                       receiving               : 1;

            UINT8                       androidTransmitting     : 1;
            UINT8                       androidReceiving        : 1;

        }                               bits;
        UINT16                          value;
    } BLUETOOTH_FLAGS;

    // *****************************************************************************
    /* Internal Signals
    */
    typedef union
    {
        struct
        {
            UINT8                       btSignalReceive         : 1;
            UINT8                       btSignalTransmit        : 1;
            UINT8                       btSignalStack           : 1;
        }                               bits;
        UINT8                           value;
    } BLUETOOTH_SIGNALS;

    // *****************************************************************************
    /* Link Information
    */

    typedef struct
    {
        bt_bdaddr   addr;
        bt_byte     linkKey[ LKS_LINK_KEY_LEN ];
    } LINK_INFO;

    // *****************************************************************************
    /* Timer Information
    */

    typedef struct
    {
        DWORD                   duration;
        DWORD                   timeoutAt;
        bt_timer_callback_fp    callback;
    } TIMER_DATA;


    //******************************************************************************
    // Section: Internal Macros
    //******************************************************************************

    #define DotStack_ClearSignal(x)         {                                       \
                                                DotStack_InterruptsDisable();       \
                                                x = 0;                              \
                                                DotStack_InterruptsEnable();        \
                                            }
    #define DotStack_ClearSignalInISR(x)    {                                       \
                                                x = 0;                              \
                                            }
    #define DotStack_InterruptsDisable()    DISABLE_INTERRUPTS()
    #define DotStack_InterruptsEnable()     ENABLE_INTERRUPTS()
    #define DotStack_SetSignal(x)           {                                       \
                                                DotStack_InterruptsDisable();       \
                                                x = 1;                              \
                                                DotStack_InterruptsEnable();        \
                                            }
    #define DotStack_SetSignalInISR(x)      {                                       \
                                                x = 1;                              \
                                            }

    // Macros for accessing Bluetooth module UART registers
    #define BTU(reg)               CONCAT3(U, BT_UART_NUMBER, reg)
    #define _BTU(reg)              CONCAT3(_U, BT_UART_NUMBER, reg)

    // Macros for accessing LOG UART registers
    #define LOGU(reg)               CONCAT3(U, LOG_UART_NUMBER, reg)
    #define _LOGU(reg)              CONCAT3(_U, LOG_UART_NUMBER, reg)

    // Helper macros
    #define CONCAT2(t1, t2)         _CONCAT2_(t1, t2)
    #define _CONCAT2_(t1, t2)       t1##t2
    #define CONCAT3(t1, t2, t3)     _CONCAT3_(t1, t2, t3)
    #define _CONCAT3_(t1, t2, t3)   t1##t2##t3

    //******************************************************************************
    // Section: Internal Function Prototypes
    //******************************************************************************

    void DotStack_CallbackFindServer ( bt_byte serverChannel, bt_bool found, void* param );
    void DotStack_CallbackReceive ( bt_spp_port_t *port, bt_int bytes_received, void *param );
    void DotStack_CallbackSend (bt_spp_port_t *port, bt_ulong bytes_sent,
                                    bt_spp_send_status_e status, void *param );
    void DotStack_CallbackStart ( bt_bool success, void* param );
    void DotStack_CallbackState ( bt_spp_port_t* port, bt_spp_port_event_e evt, void* param );

    static void DotStack_CheckTimers ( void );
    static void DotStack_InitializeLogging ( void );
    static BOOL DotStack_ReceiveQueuedRequest ( void );
    static void DotStack_StartLogging ( void );

    void bt_oem_log_write(const char* msg);
#else

    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif

////////////////////////////////////////////////////////////////////////////////
// Common

#if defined ( IPOD_USE_BLUETOOTH ) && defined ( IPOD_BT_CANDLEDRAGON_CSR )
    BOOL AndroidAppIsReadComplete ( void *androidDeviceHandle, UINT8 *errorCode, DWORD *size );
    BOOL AndroidAppIsWriteComplete ( void *androidDeviceHandle, UINT8 *errorCode, DWORD *size );
    UINT8 AndroidAppRead ( void *androidDeviceHandle, BYTE *data, DWORD length );
    void  AndroidAppReadCancel ( void *androidDeviceHandle );
    UINT8 AndroidAppWrite ( void *androidDeviceHandle, BYTE * data, DWORD length );
#endif

void DotStack_CancelReceive ( void );
void DotStack_HandleReceive( void );
void DotStack_HandleTransmit( void );
UINT8 DotStack_Initialize ( void );
BOOL DotStack_IsAndroidAttached( void );
BOOL DotStack_IsiPodAttached ( void );
BOOL DotStack_Receive ( UINT8 * data, bt_ulong dataLength, bt_spp_receive_callback_fp callback );
BOOL DotStack_Send ( UINT8 * data, bt_ulong dataLength, bt_spp_send_callback_fp callback );
UINT8 DotStack_Start ( void );
UINT8 DotStack_Shutdown ( void );
void DotStack_Tasks ( void );

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

__inline__ void IMFI_UART_Disable( void );


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

__inline__ void IMFI_UART_Enable( void );


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

__inline__ UINT8 IMFI_UART_Receive( void );


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

__inline__ BOOL IMFI_UART_RxBytesAvailable( void );


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

__inline__ void IMFI_UART_RxInterruptClear( void );


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

__inline__ void IMFI_UART_RxInterruptDisable( void );


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

__inline__ void IMFI_UART_RxInterruptEnable( void );


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

__inline__ BOOL IMFI_UART_RxInterruptFired( void );


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

__inline__ void IMFI_UART_Transmit ( UINT8 x );


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

__inline__ void IMFI_UART_TxEnable( void );


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

__inline__ void IMFI_UART_TxEnableWithInterrupts( void );


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

__inline__ void IMFI_UART_TxInterruptClear( void );


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

__inline__ void IMFI_UART_TxInterruptDisable( void );


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

__inline__ void IMFI_UART_TxInterruptEnable( void );


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

__inline__ BOOL IMFI_UART_TxInterruptFired( void );


#endif

