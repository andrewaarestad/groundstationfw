//DOM-IGNORE-BEGIN
/******************************************************************************

File Name:       PED_Universal.h
Dependencies:    None
Processor:       PIC24-dsPIC/PIC32
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

#ifndef PED_UNIVERSAL_H
#define PED_UNIVERSAL_H

////////////////////////////////////////////////////////////////////////////////
// Common

#include "GenericTypeDefs.h"
#include "Compiler.h"

#include "MFI/MFI_iPod.h"

//DOM-IGNORE-END

//******************************************************************************
// Section: Constants
//******************************************************************************

#define PED_SUCCESS                 IPOD_SUCCESS    // <b>PED Universal Framework</b> - The command completed successfully
#define PED_ERROR                   0x01            // <b>PED Universal Framework</b> - General error
#define PED_NOT_READY               0x02            // <b>PED Universal Framework</b> - The device is not ready for the requested operation
#define PED_BUSY                    0x03            // <b>PED Universal Framework</b> - The device is busy, and cannot perform the requested operation
#define PED_TRANSPORT_ERROR         0x04            // <b>PED Universal Framework</b> - Error in the transport layer


//******************************************************************************
// Section: Typedefs
//******************************************************************************

// *****************************************************************************
/* <b>PED Universal Framework</b> - PED Device Types

These are the supported device types.
*/
typedef enum
{
    PED_DEVICE_APPLE,       // An Apple iOS device
    PED_DEVICE_ANDROID      // An Android device
} PED_DEVICE_TYPE;

////////////////////////////////////////////////////////////////////////////////

#ifdef PED_UNIVERSAL_C

    //DOM-IGNORE-BEGIN

    ////////////////////////////////////////////////////////////////////////////////
    // Private

    #include "MFI/MFI_Data.h"

    #include "HardwareProfile.h"
    #include "Tick.h"
    #include "TimeDelay.h"

    #include "ped_config.h"
    #include "mfi_config.h"

    #if defined ( IPOD_USE_USB_HOST )
        #include "usb_config.h"
        #include "USB/usb.h"
        #include "USB/usb_host_android.h"
    #elif defined ( IPOD_USE_BLUETOOTH ) && defined ( IPOD_BT_CANDLEDRAGON_CSR )
        #include "MFI/PED_BT_DotStack.h"
    #endif

    //******************************************************************************
    // Section: Typedefs
    //******************************************************************************

    // *****************************************************************************
    /* iOS Status

    This structure contains information about the status of the iOS device.
    */
    typedef struct
    {
        UINT32_VAL      communicationWaitTimeoutAt;

        union
        {
            UINT8       value;
            struct
            {
                UINT8   autolaunchSupported             : 1;
                UINT8   communicationWaiting            : 1;
                UINT8   dataSessionOpen                 : 1;
                UINT8   waitingForSessionSpaceAvailable : 1;
                UINT8   sendSmallDataTransfer           : 1;
            } bits;
        } flags;

    } IOS_STATUS;


    // *****************************************************************************
    /* iOS Command Status

    This structure holds information about the various commands that have been sent
    from or need to be sent to the iOS device.
    */
    typedef struct
    {
        UINT32      timeoutDevDataTransferACK;

        UINT16      transactionIDOpenDataSession;
        UINT16      transactionIDCloseDataSession;
        UINT16      transactionIDiPodDataTransfer;
        UINT16      transactionIDDevDataTransfer;

        union
        {
            UINT16      value;
            struct
            {
                UINT8   sendingCommand                      : 1;
                UINT8   sendAutolaunchRequest               : 1;
                UINT8   sendGetSupportedEventNotification   : 1;
                UINT8   sendSetEventNotification            : 1;
                UINT8   sendOpenDataSessionACK              : 1;
                UINT8   sendCloseDataSessionACK             : 1;
                UINT8   sendiPodDataTransferACK             : 1;
                UINT8   sendiPodDataTransferNACK            : 1;
                UINT8   waitingForDevDataTransferACK        : 1;
            } bits;
        } flags;
    } IOS_COMMAND_STATUS;

    // *****************************************************************************
    /* PED Information

    This structure holds general information about the attached device, whatever it is.
    */
    typedef struct
    {
        union
        {
            UINT8           value;

            struct
            {
                UINT8   deviceAttached          : 1;
                UINT8   deviceAndroid           : 1;
                UINT8   deviceiOS               : 1;
            } bits;
        } flags;
    } PED_INFORMATION;

    // *****************************************************************************
    /* Received Application Data

    This structure is used to hold data that has been received from the device.
    */
    typedef struct
    {
        UINT8   data[PED_RX_DATA_BUFFER_SIZE];
        UINT16  head;
        UINT16  tail;
    } RECEIVED_APP_DATA;


    //******************************************************************************
    // Section: Macros
    //******************************************************************************

    #define HIGH_BYTE(x)        (((x) >> 8) & 0xFF)
    #define LOW_BYTE(x)         ((x) & 0xFF)


    #define PEDI_RxDataReset()  { pedRxData.head = 0; pedRxData.tail = 0; }


    //******************************************************************************
    // Section: Function Prototypes - Internal
    //******************************************************************************

    void    PEDI_InitializeVariables ( void );
    UINT16  PEDI_RxDataAdd( UINT8 *src, UINT16 count );
    void    PEDI_TasksAndroid ( void );
    void    PEDI_TasksiOS ( void );

    //DOM-IGNORE-END

#else

    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif

////////////////////////////////////////////////////////////////////////////////
// Common

//******************************************************************************
// Section: Function Prototypes - Application Callbacks
//******************************************************************************

/****************************************************************************
  Function:
    void PED_CallbackConnect ( PED_DEVICE_TYPE device );

  Description:
    <b>PED Universal Framework</b>

    This callback must be provided by the application code.  The universal
    wrapper will call this function when a device has attached, connected with
    an app on the personal electronic device, and is ready to exchange data.

  Precondition:
    None

  Parameters:
    PED_DEVICE_TYPE device  - The type of device that has attached.

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
void    PED_CallbackConnect ( PED_DEVICE_TYPE device );

/****************************************************************************
  Function:
    void    PED_CallbackDisconnect ( void );

  Description:
    <b>PED Universal Framework</b>

    This callback must be provided by the application code.  The universal
    wrapper will call this function when the connection with the app on the
    personal electronic device is severed, and data can no longer be exchanged.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    Android devices generate this callback only on a physical disconnection
    of the hardware interface.  If the app is sent to the background or
    closed, Android does not close the connection.  Therefore, the application
    layer must handle this in its protocol implementation.  See the Android
    Library Help and Android Accessories demos in the Microchip Application
    Libraries installation for more information.
  ***************************************************************************/
void    PED_CallbackDisconnect ( void );


//******************************************************************************
// Section: Function Prototypes - API
//******************************************************************************

/****************************************************************************
  Function:
     UINT8 * PED_CanWrite ( UINT16 length )

  Description:
    <b>PED Universal Framework</b>

    This function indicates whether or not the requested amount of data can
    be sent.

  Precondition:
    None

  Parameters:
    UINT16 length

  Returns:
    If data can be sent to the attached device, then a pointer to where to
    place the data is returned.  If data cannot be sent at this time, NULL
    is returned.

  Example:
    This example shows a typical write sequence:
    <code>
    UINT8   *pCommandData;

    pCommandData = PED_CanWrite ( 6 );
    if (pCommandData != NULL)
    {
        *pCommandData++ = SYNC_BYTE_1;
        *pCommandData++ = SYNC_BYTE_2;
        *pCommandData++ = myCommand;
        *pCommandData++ = commandLength;
        *pCommandData++ = commandData0;
        *pCommandData++ = commandData1;
        if ( PED_Write ( 6 ) == PED_SUCCESS )
        {
            // data was sent successfully
        }
    }
    </code>

  Remarks:
    None
  ***************************************************************************/
UINT8 * PED_CanWrite ( UINT16 length );

/****************************************************************************
  Function:
    void    PED_Flush ( UINT16 count );

  Description:
    <b>PED Universal Framework</b>

    This function is designed to be used in conjunction with the PED_Peek
    function.  It will flush the specified number of bytes from the received
    data buffer.

  Precondition:
    None

  Parameters:
    UINT16 count    - Number of bytes to be flushed from the buffer

  Return Values:
    None

  Example:
    This example checks for and processes simple received commands.
    <code>
    if ( PED_ReadBytesAvailable() >= 4 )
    {
        if ( (PED_Peek(0) == SYNC_BYTE_1) && (PED_Peek(1) == SYNC_BYTE_2) )
        {
            switch ( PED_Peek(2) )
            {
                case COMMAND_LEDS:
                    LEDS = PED_Peek(3);
                    break;
            }
        }
        PED_Flush(4);
    }
    </code>

  Remarks:
    If the specified count is greater than the number of bytes in the received
    data buffer, then the buffer will simply be emptied.
  ***************************************************************************/
void    PED_Flush ( UINT16 count );

/****************************************************************************
  Function:
    UINT8 PED_Initialize ( void )

  Description:
    <b>PED Universal Framework</b>

    This routine initializes support for both Android and iOS devices.  See
    the documentation for MFI_Initialize for a full description of MFi
    initialization.

  Precondition:
    The application must initialize the mfi_iPodApplicationInformation variable
    before calling this function.

    The application should also initialize the TICK timing function before
    calling this function.

    See also the preconditions for MFI_Initialize.

  Parameters:
    IPOD_APPLICATION_INFORMATION *iPodApplicationInformation   - Must point to
        the global mfi_iPodApplicationInformation.

  Returns:
    See the documentation for the function MFI_Initialize.

  Remarks:
    None
  ***************************************************************************/
UINT8   PED_Initialize ( void );

/****************************************************************************
  Function:
    UINT8   PED_Peek ( UINT16 offset );

  Description:
    <b>PED Universal Framework</b>

    This function is designed to be used in conjunction with the PED_Flush
    function.  This function looks into the buffer of received data, and
    returns the value of the byte at the specified offset.  This function
    is useful if the received data does not need to be retained.

  Precondition:
    The function PED_ReadBytesAvailable should be called first, to ensure
    that a valid byte exists at the desired offset.

  Parameters:
    UINT16 offset   - Offset of the desired byte from the current head of the
                        received data buffer

  Returns:
    The value of the byte at the specified offset.

  Example:
    This example checks for and processes simple received commands.
    <code>
    if ( PED_ReadBytesAvailable() >= 4 )
    {
        if ( (PED_Peek(0) == SYNC_BYTE_1) && (PED_Peek(1) == SYNC_BYTE_2) )
        {
            switch ( PED_Peek(2) )
            {
                case COMMAND_LEDS:
                    LEDS = PED_Peek(3);
                    break;
            }
        }
        PED_Flush(4);
    }
    </code>

  Remarks:
    None
  ***************************************************************************/
UINT8   PED_Peek ( UINT16 offset );

/****************************************************************************
  Function:
    UINT16  PED_Read ( UINT8 *dest, UINT16 count );

  Description:
    <b>PED Universal Framework</b>

    This function will transfer the specified number of received bytes to the
    indicated destination.  If the specified count is greater than the number
    of bytes that are actually available, then only the number of available
    bytes are copied.

  Precondition:
    None

  Parameters:
    UINT8 *dest     - Pointer to the copy destination
    UINT16 count    - Number of bytes to copy

  Returns:
    The number of bytes copied.

  Example:
    This example copies a fixed number of data bytes from the internal
    receive buffer.
    <code>
    if (PED_ReadBytesAvailable() >= COMMAND_SIZE)
    {
        // We have a command.  Copy it into a local buffer.
        PED_Read( buffer, COMMAND_SIZE );

        // Process the received command/data
    }
    </code>

  Remarks:
    None
  ***************************************************************************/
UINT16  PED_Read ( UINT8 *dest, UINT16 count );

/****************************************************************************
  Function:
    UINT16  PED_ReadBytesAvailable ( void );

  Description:
    <b>PED Universal Framework</b>

    This function indicates the number of bytes that have been received from
    the attached device and are ready for the application layer.

  Precondition:
    None

  Parameters:
    None

  Returns:
    The number of data bytes available.

    This example copies a fixed number of data bytes from the internal
    receive buffer.
    <code>
    if (PED_ReadBytesAvailable() >= COMMAND_SIZE)
    {
        // We have a command.  Copy it into a local buffer.
        PED_Read( buffer, COMMAND_SIZE );

        // Process the received command/data
    }
    </code>

  Remarks:
    None
  ***************************************************************************/
UINT16  PED_ReadBytesAvailable ( void );

/****************************************************************************
  Function:
    void    PED_Tasks ( void );

  Description:
    <b>PED Universal Framework</b>

    This function executes all of the maintenance tasks needed for
    communication with an attached personal electronic device.  It must be
    called on a regular basis to maintain communication.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
void    PED_Tasks ( void );

/****************************************************************************
  Function:
    UINT8   PED_Write ( UINT16 length );

  Description:
    <b>PED Universal Framework</b>

    This function sends the specified number of bytes, located at the position
    indicated with the return value of PED_CanWrite, to the attached device.

  Precondition:
    PED_CanWrite must be called first, to see if data can be sent to the
    attached device, and to obtain a pointer for where to place the data.

  Parameters:
    UINT16 length   - Number of bytes to send to the device

  Return Values:
    PED_SUCCESS         - The process of sending the data to the device has started successfully
    PED_ERROR           - General error
    PED_NOT_READY       - The device is not ready to receive data
    PED_BUSY            - A previous write is already in progress
    PED_TRANSPORT_ERROR - Error in the transport layer
    None

  Example:
    This example shows a typical write sequence:
    <code>
    UINT8   *pCommandData;

    pCommandData = PED_CanWrite ( 6 );
    if (pCommandData != NULL)
    {
        *pCommandData++ = SYNC_BYTE_1;
        *pCommandData++ = SYNC_BYTE_2;
        *pCommandData++ = myCommand;
        *pCommandData++ = commandLength;
        *pCommandData++ = commandData0;
        *pCommandData++ = commandData1;
        if ( PED_Write ( 6 ) == PED_SUCCESS )
        {
            // data was sent successfully
        }
    }
    </code>

  Remarks:
    None
  ***************************************************************************/
UINT8   PED_Write ( UINT16 length );


#endif

