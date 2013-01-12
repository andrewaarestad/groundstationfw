/******************************************************************************

File Name:       PED_Universal.c
Dependencies:    None
Processor:       PIC18, PIC24/dsPIC, PIC32
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

Author          Date        Comments
--------------------------------------------------------------------------------
KO/SP/AF        03-Aug-2012 v3.05
KO/SP/AF        29-Feb-2012 v3.04
KO/SP/AF        02-Feb-2012 v3.03, Limited distribution
KO/SP/AF        02-Dec-2011 v3.02

*******************************************************************************/

#define PED_UNIVERSAL_C
#include "MFI/PED_Universal.h"

//******************************************************************************
// Section: Global Variables
//******************************************************************************

#if defined ( IPOD_USE_USB_HOST )

    static char androidManufacturer[]   = ANDROID_ACCESSORY_MANUFACTURER;
    static char androidModel[]          = ANDROID_ACCESSORY_MODEL;
    static char androidDescription[]    = ANDROID_ACCESSORY_DESCRIPTION;
    static char androidVersion[]        = ANDROID_ACCESSORY_VERSION;
    static char androidURI[]            = ANDROID_ACCESSORY_URI;
    static char androidSerial[]         = ANDROID_ACCESSORY_SERIAL;

    ANDROID_ACCESSORY_INFORMATION       androidDeviceInfo =
    {
        androidManufacturer,
        sizeof ( androidManufacturer ),
        androidModel,
        sizeof ( androidModel ),
        androidDescription,
        sizeof ( androidDescription ),
        androidVersion,
        sizeof ( androidVersion ),
        androidURI,
        sizeof ( androidURI ),
        androidSerial,
        sizeof ( androidSerial )
    };

#endif

void                *androidDeviceHandle;

UINT8               *iOSCommandDataPtr;
IOS_COMMAND_STATUS  iOSCommandStatus;
IPOD_INFORMATION    *iOSInformation;
UINT8               iOSProtocolIndex;
UINT16              iOSSessionID;
IOS_STATUS          iOSStatus;

PED_INFORMATION     pedInformation;
RECEIVED_APP_DATA   pedRxData;


/****************************************************************************
  ***************************************************************************/

UINT8 * PED_CanWrite (UINT16 length )
{
    DWORD   size;
    BYTE    errorCode;

    if ( ! pedInformation.flags.bits.deviceAttached )
    {
        return NULL;
    }

    if ( pedInformation.flags.bits.deviceAndroid )
    {
        // If we are attached to an Android device, then we can send data
        // if there is currently no OUT transfer in progress.
        if ( ( AndroidAppIsWriteComplete ( androidDeviceHandle, &errorCode, &size ) == TRUE ) &&
             ( length <= sizeof ( mfi_iAPOut ) ) )
        {
            return (UINT8 *) &mfi_iAPOut;
        }
        else
        {
            return NULL;
        }
    }
    else if ( pedInformation.flags.bits.deviceiOS )
    {
        // Be sure skip over the session ID bytes (we'll fill those in later), but
        // include it in the required length.

        // Ask for the larger of (length+2) or the maximum command data size.  This way,
        // if the application layer tries to send too large a packet, the request
        // will fail.

        length += 2;
        if ( MFI_GetMaxCommandDataSize ( IPOD_LINGO_GENERAL ) > length )
        {
            length = MFI_GetMaxCommandDataSize ( IPOD_LINGO_GENERAL );
        }

        if (   iOSStatus.flags.bits.dataSessionOpen &&
             ! iOSStatus.flags.bits.waitingForSessionSpaceAvailable &&
             ( iOSCommandStatus.flags.value == 0 ) )
        {
            iOSCommandDataPtr = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, length );
            if ( iOSCommandDataPtr == NULL )
            {
                return NULL;
            }
            else
            {
                return iOSCommandDataPtr + 2;
            }
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

/****************************************************************************
  ***************************************************************************/

void PED_Flush ( UINT16 count )
{
    if ( count > PED_ReadBytesAvailable () )
    {
        count = PED_ReadBytesAvailable ();
    }

    pedRxData.tail += count;
    if (pedRxData.tail >= PED_RX_DATA_BUFFER_SIZE)
    {
        pedRxData.tail -= PED_RX_DATA_BUFFER_SIZE;
    }
}

/****************************************************************************
  ***************************************************************************/

UINT8 PED_Initialize ( void )
{
    UINT8   initializationReturn;

    PEDI_InitializeVariables ();
    initializationReturn = MFI_Initialize( &mfi_iPodApplicationInformation );

    #if defined ( IPOD_USE_USB_HOST )
        AndroidAppStart ( &androidDeviceInfo );
    #endif

    return initializationReturn;
}

/****************************************************************************
  ***************************************************************************/

UINT8 PED_Peek( UINT16 offset )
{
    UINT16    location;

    location = pedRxData.tail + offset;
    if (location >= PED_RX_DATA_BUFFER_SIZE)
    {
        location -= PED_RX_DATA_BUFFER_SIZE;
    }
    return pedRxData.data[location];
}

/****************************************************************************
  ***************************************************************************/

UINT16 PED_Read( UINT8 *dest, UINT16 count )
{
    UINT16  bytesCopied;
    UINT16  tailBytes;

    if ( count < PED_ReadBytesAvailable () )
    {
        bytesCopied = count;
    }
    else
    {
        bytesCopied = PED_ReadBytesAvailable ();
    }

    if ((PED_RX_DATA_BUFFER_SIZE - pedRxData.tail) >= bytesCopied)
    {
        memcpy ( dest, pedRxData.data + pedRxData.tail, bytesCopied);
    }
    else
    {
        // The requested data is wrapped in the circular buffer.

        tailBytes = PED_RX_DATA_BUFFER_SIZE - pedRxData.tail;

        memcpy ( dest, pedRxData.data + pedRxData.tail, tailBytes);
        memcpy ( dest + tailBytes, pedRxData.data, bytesCopied - tailBytes);
    }

    PED_Flush ( bytesCopied );

    return bytesCopied;
}

/****************************************************************************
  ***************************************************************************/

UINT16 PED_ReadBytesAvailable( void )
{
    if (pedRxData.head >= pedRxData.tail)
    {
        return pedRxData.head - pedRxData.tail;
    }
    else
    {
        return PED_RX_DATA_BUFFER_SIZE + pedRxData.head - pedRxData.tail;
    }
}

/****************************************************************************
  ***************************************************************************/

void PED_Tasks ( void )
{
    // Run all general MFi tasks.
    MFI_Tasks();

    // Run all general Android tasks
    #if defined ( IPOD_USE_USB_HOST )
        // USB Host interface tasks
        USBHostTasks();
        AndroidTasks();
    #elif defined ( IPOD_USE_BLUETOOTH ) && defined ( IPOD_BT_CANDLEDRAGON_CSR )
        // Bluetooth interface tasks
        if ( ! pedInformation.flags.bits.deviceAttached )
        {
            // Check for attachment
            if ( DotStack_IsAndroidAttached() )
            {
                pedInformation.flags.bits.deviceAttached    = 1;
                pedInformation.flags.bits.deviceAndroid     = 1;

                PED_CallbackConnect ( PED_DEVICE_ANDROID );
            }
        }
        else if ( pedInformation.flags.bits.deviceAndroid )
        {
            // Check for detachment of an Android device
            if ( ! DotStack_IsAndroidAttached() )
            {
                pedInformation.flags.bits.deviceAttached    = 0;
                pedInformation.flags.bits.deviceAndroid     = 0;

                AndroidAppReadCancel ( androidDeviceHandle );
                PED_CallbackDisconnect ();
                PEDI_InitializeVariables ();
            }
        }
    #else
        #error Unsupported hardware interface
    #endif

    // Run the tasks that are required for the specific attached device
    if ( pedInformation.flags.bits.deviceAndroid )
    {
        PEDI_TasksAndroid ();
    }
    else if ( pedInformation.flags.bits.deviceiOS )
    {
        PEDI_TasksiOS ();
    }
}

/****************************************************************************
  ***************************************************************************/

UINT8 PED_Write ( UINT16 length )
{
    UINT8   rc;

    if ( pedInformation.flags.bits.deviceAndroid )
    {
        rc = AndroidAppWrite ( androidDeviceHandle, (BYTE*) &mfi_iAPOut, length );

        #if defined ( IPOD_USE_USB_HOST )
            switch ( rc )
            {
                case USB_SUCCESS:                       // Write started successfully.
                    return PED_SUCCESS;
                    break;

                case USB_UNKNOWN_DEVICE:                // Device with the specified address not found.
                case USB_INVALID_STATE:                 // We are not in a normal running state.
                    return PED_NOT_READY;
                    break;

                case USB_ENDPOINT_BUSY:                 // A Write is already in progress.
                    return PED_BUSY;
                    break;

                case USB_ENDPOINT_ILLEGAL_TYPE:         // Must use USBHostControlWrite to write to a control endpoint.
                case USB_ENDPOINT_ILLEGAL_DIRECTION:    // Must write to an OUT endpoint.
                case USB_ENDPOINT_STALLED:              // Endpoint is stalled.  Must be cleared by the application.
                case USB_ENDPOINT_ERROR:                // Endpoint has too many errors.  Must be cleared by the application.
                case USB_ENDPOINT_NOT_FOUND:            // Invalid endpoint.
                    return PED_TRANSPORT_ERROR;
                    break;

                default:
                    return PED_ERROR;
                    break;
            }
        #else
            return rc;
        #endif
    }
    else if ( pedInformation.flags.bits.deviceiOS )
    {
        if ( ( length < (251 - 2) ) &&
             ( MFI_GetMaxCommandDataSize ( IPOD_LINGO_GENERAL ) > (251 - 2) ) )
        {
            // We asked for a large packet, but we only need a small packet.
            // Move the data so it is aligned correctly.

            iOSCommandDataPtr -= 2;
            memmove ( iOSCommandDataPtr, iOSCommandDataPtr + 2, length );
        }

        iOSCommandDataPtr[0] = HIGH_BYTE( iOSSessionID );
        iOSCommandDataPtr[1] = LOW_BYTE(  iOSSessionID );

        rc = MFI_SendCommand ( TRUE, IPOD_LINGO_GENERAL, IPOD_AccessoryDataTransfer, length + 2, &(iOSCommandStatus.transactionIDDevDataTransfer ) );
        if ( rc == IPOD_SUCCESS )
        {
            iOSCommandStatus.flags.bits.sendingCommand               = 1;
            iOSCommandStatus.flags.bits.waitingForDevDataTransferACK = 1;
            iOSCommandStatus.timeoutDevDataTransferACK               = TickGet() + (500 * dwTicksPerMillisecond);
        }

        switch ( rc )
        {
            case IPOD_SUCCESS:                          // Command sent.
                return PED_SUCCESS;
                break;

            case IPOD_NOT_READY:                        // The iPod is not in a state where it will accept commands.
                return PED_NOT_READY;
                break;

            case IPOD_BUSY:                             // A command is currently being sent.
                return PED_BUSY;
                break;

            case IPOD_ERROR_INVALID_IAP_COMMAND_LENGTH: // The commandDataSize is too large.
                return PED_TRANSPORT_ERROR;
                break;

            default:
                return PED_ERROR;
                break;
        }
    }
    else
    {
        return 0xFF;
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Internal Functions
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/****************************************************************************
  ***************************************************************************/

void PEDI_InitializeVariables ( void )
{
    androidDeviceHandle = NULL;

    memset ( (UINT8 *) &iOSCommandStatus, 0x00, sizeof ( IOS_COMMAND_STATUS ) );
    memset ( (UINT8 *) &iOSStatus, 0x00, sizeof ( IOS_STATUS ) );

    memset ( (UINT8 *) &pedInformation, 0x00, sizeof ( PED_INFORMATION ) );

    PEDI_RxDataReset ();
}

/****************************************************************************
  ***************************************************************************/

UINT16 PEDI_RxDataAdd( UINT8 *src, UINT16 count )
{
    UINT16  bytesCopied;
    UINT16  tailBytes;

    if ( count < ( PED_RX_DATA_BUFFER_SIZE - PED_ReadBytesAvailable () - 1 ) )
    {
        bytesCopied = count;
    }
    else
    {
        bytesCopied = PED_RX_DATA_BUFFER_SIZE - PED_ReadBytesAvailable () - 1;
    }

    if ( bytesCopied > 0 )
    {
        if ((PED_RX_DATA_BUFFER_SIZE - pedRxData.head) >= bytesCopied)
        {
            memcpy ( pedRxData.data + pedRxData.head, src, bytesCopied);
            pedRxData.head += bytesCopied;
        }
        else
        {
            // The requested data is wrapped in the circular buffer.

            tailBytes = PED_RX_DATA_BUFFER_SIZE - pedRxData.head;

            memcpy ( pedRxData.data + pedRxData.head, src, tailBytes );
            memcpy ( pedRxData.data, src + tailBytes, bytesCopied - tailBytes );
            pedRxData.head = bytesCopied - tailBytes;
        }
    }

    return bytesCopied;
}

/****************************************************************************
  ***************************************************************************/

void PEDI_TasksAndroid ( void )
{
    DWORD   size;
    BYTE    errorCode;

    if ( AndroidAppIsReadComplete ( androidDeviceHandle, &errorCode, &size ) == TRUE )
    {
        // Copy the data into the command buffer.
        if ( ( errorCode == IPOD_SUCCESS ) && ( size != 0 ) )
        {
            PEDI_RxDataAdd ( (UINT8 *) &mfi_iAPIn, (UINT16) size );
        }

        // Initiate the next read
        errorCode = AndroidAppRead ( androidDeviceHandle, (BYTE*)&mfi_iAPIn, (DWORD)sizeof( mfi_iAPIn ) );
    }
}

/****************************************************************************
  ***************************************************************************/

void PEDI_TasksiOS ( void )
{
    UINT8       *pCommandData;
    signed long temp;

    // If we are currently waiting because of an iPodNotification FlowControl
    // message, see if the timeout has passed.
    if (iOSStatus.flags.bits.communicationWaiting)
    {
        temp = (signed long)TickGet() - (signed long)iOSStatus.communicationWaitTimeoutAt.Val;
        if ( temp > 0 )
        {
            iOSStatus.flags.bits.communicationWaiting = 0;
        }
    }

    // If we are currently waiting for an ACK to a DevDataTransfer command, see if the
    // timeout has passed.
    if (iOSCommandStatus.flags.bits.waitingForDevDataTransferACK)
    {
        temp = (signed long)TickGet() - (signed long)iOSCommandStatus.timeoutDevDataTransferACK;
        if ( temp > 0 )
        {
            iOSCommandStatus.flags.bits.waitingForDevDataTransferACK = 0;
        }
    }

    if (!iOSStatus.flags.bits.communicationWaiting)
    {
        if (iOSCommandStatus.flags.bits.sendGetSupportedEventNotification)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 0 );
            if ( pCommandData != NULL )
            {
                if ( MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_GetSupportedEventNotification, 0, NULL ) == IPOD_SUCCESS )
                {
                    iOSCommandStatus.flags.bits.sendGetSupportedEventNotification   = 0;
                    iOSCommandStatus.flags.bits.sendingCommand                      = 1;
                }
            }
        }
        else if (iOSCommandStatus.flags.bits.sendSetEventNotification)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 8 );
            if ( pCommandData != NULL )
            {
                *pCommandData++ = 0;
                *pCommandData++ = 0;
                *pCommandData++ = 0;
                *pCommandData++ = 0;
                *pCommandData++ = 0;
                *pCommandData++ = 0;
                *pCommandData++ = 0x08; // Request SessionSpaceAvailable notifications
                *pCommandData++ = 0x04; // Request flow control notifications

                if ( MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_SetEventNotification, 8, NULL ) == IPOD_SUCCESS )
                {
                    iOSCommandStatus.flags.bits.sendSetEventNotification    = 0;
                    iOSCommandStatus.flags.bits.sendingCommand              = 1;
                }
            }
        }
        else if (iOSCommandStatus.flags.bits.sendAutolaunchRequest)
        {
            UINT8   stringLength;

            #if defined ( __18CXX ) || defined ( _PIC14E )
                stringLength = (UINT8)strlenpgm( IPOD_ACCESSORY_BUNDLE_ID ) + 1;
            #else
                stringLength = (UINT8)strlen( IPOD_ACCESSORY_BUNDLE_ID ) + 1;
            #endif
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, stringLength + 3 );
            if (pCommandData != NULL)
            {
                *pCommandData++ = 0;    // Reserved
                *pCommandData++ = 2;    // Reserved
                *pCommandData++ = 0;    // Reserved

                // Copy the Application Bundle ID string.  Be sure to copy the null terminator -
                // the length calculation includes it.
                #if defined ( __18CXX ) || defined ( _PIC14E )
                    memcpypgm2ram( pCommandData, IPOD_ACCESSORY_BUNDLE_ID, stringLength );
                #else
                    memcpy( pCommandData, IPOD_ACCESSORY_BUNDLE_ID, stringLength );
                #endif

                if ( MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_RequestApplicationLaunch, stringLength + 3, NULL ) == IPOD_SUCCESS )
                {
                    iOSCommandStatus.flags.bits.sendAutolaunchRequest   = 0;
                    iOSCommandStatus.flags.bits.sendingCommand          = 1;
                }
            }
        }
        else if (iOSCommandStatus.flags.bits.sendOpenDataSessionACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                pCommandData[0] = 0x00;     // Success
                pCommandData[1] = IPOD_OpenDataSessionForProtocol;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iOSCommandStatus.transactionIDOpenDataSession) ) == IPOD_SUCCESS )
                {
                    iOSStatus.flags.bits.dataSessionOpen                = 1;
                    iOSCommandStatus.flags.bits.sendOpenDataSessionACK  = 0;
                    iOSCommandStatus.flags.bits.sendingCommand          = 1;

                    // Now the data stream is open.  Tell the application layer.
                    PED_CallbackConnect ( PED_DEVICE_APPLE );
                }
            }
        }
        else if (iOSCommandStatus.flags.bits.sendCloseDataSessionACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                pCommandData[0] = 0x00;     // Success
                pCommandData[1] = IPOD_CloseDataSession;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iOSCommandStatus.transactionIDCloseDataSession) ) == IPOD_SUCCESS )
                {
                    iOSCommandStatus.flags.bits.sendCloseDataSessionACK = 0;
                    iOSCommandStatus.flags.bits.sendingCommand          = 1;
                }
            }
        }
        else if (iOSCommandStatus.flags.bits.sendiPodDataTransferACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                *pCommandData++ = IPOD_ACK_SUCCESS;
                *pCommandData++ = IPOD_iPodDataTransfer;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iOSCommandStatus.transactionIDiPodDataTransfer) ) == IPOD_SUCCESS )
                {
                    iOSCommandStatus.flags.bits.sendiPodDataTransferACK = 0;
                    iOSCommandStatus.flags.bits.sendingCommand          = 1;
                }
            }
        }
        else if (iOSCommandStatus.flags.bits.sendiPodDataTransferNACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                *pCommandData++ = IPOD_ACK_BAD_PARAMETER;
                *pCommandData++ = IPOD_iPodDataTransfer;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iOSCommandStatus.transactionIDiPodDataTransfer) ) == IPOD_SUCCESS )
                {
                    iOSCommandStatus.flags.bits.sendiPodDataTransferNACK    = 0;
                    iOSCommandStatus.flags.bits.sendingCommand              = 1;
                }
            }
        }
    }
}

/****************************************************************************
  Function:
    BOOL MFI_HandleiPodDataEvents( MFI_EVENT event, void *data, UINT32 size )

  Description:
    This function is called by the iPod driver when the application layer
    needs to handle data events.

    The iPod sends one isochronous data packet of up to 194 bytes of audio
    data every millisecond.  This routine must be able to process the data
    and return before the next SOF, or the USB Host stack will not be able to
    query the iPod in time to maintain the required transfer rate.

  Precondition:
    None

  Parameters:
    MFI_EVENT event - Event that has occurred
    void *data      - Pointer to the data for the event
    UINT32 size     - Size of the data

  Return Values:
    TRUE    - Event was processed
    FALSE   - Event was not processed

  Remarks:
    This event handler will be called from the USB interrupt handler, so
    processing time should be carefully considered.

    Please refer to the online Help file for more information about these
    events.
  ***************************************************************************/

BOOL MFI_HandleiPodDataEvents( MFI_EVENT event, void *data, UINT32 size )
{
    // Not needed for this application.
    return TRUE;
}

/****************************************************************************
  Function:
    BOOL MFI_HandleiPodEvents( MFI_EVENT event, void *data, UINT32 size )

  Description:
    This function is called by the iPod driver when the application layer
    needs to handle events.

  Precondition:
    None

  Parameters:
    MFI_EVENT event - Event that has occurred
    void *data      - Pointer to the data for the event
    UINT32 size     - Size of the data

  Return Values:
    TRUE    - Event was processed
    FALSE   - Event was not processed

  Remarks:
    IMPORTANT - It is recommended not to send iPod commands from the event
    handler.  If the iPod driver is busy and cannot accept a new command, the
    attempt will fail, and the event handler will not be called again.

    Please refer to the online Help file for more information about these
    events.
  ***************************************************************************/

BOOL MFI_HandleiPodEvents( MFI_EVENT event, void *data, UINT32 size )
{

    switch( event )
    {
        case MFI_EVENT_IS_IPOD_ATTACHED:
            // We need to tell the library whether or not an iPod is present.
            // If we are using the USB Host interface, we do not need
            // to monitor these pins, and we can simply return TRUE.
            #if defined ( IPOD_USE_USB_HOST )
                return TRUE;
            #elif defined ( IPOD_USE_BLUETOOTH )
                return DotStack_IsiPodAttached();
            #endif
            break;

        case MFI_EVENT_CP_SET_NRESET:
            // Set the CP nRESET line to the requested state.  ACP 2.0B only
            #if defined ( MFI_AUTH_NRESET )
                MFI_AUTH_NRESET = size;
            #endif
            break;

        case MFI_EVENT_CP_OPEN_I2C:
            // Enable the I2C at the proper frequency.
            // NOTE: Currently, a dedicated I2C port is required.
            #if defined ( __18CXX ) || defined ( _PIC14E )
                I2CConfigure( mfi_iPodApplicationInformation.cpCommunicationModule, I2C_MODE_MASTER | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE );
            #endif
            I2CSetFrequency( mfi_iPodApplicationInformation.cpCommunicationModule, I2C_Clock(), IPOD_CP_FREQUENCY );
            I2CEnable( mfi_iPodApplicationInformation.cpCommunicationModule, TRUE );
            Delay10us( 10 );
            break;

        case MFI_EVENT_CP_I2C_CLOSED:
            // The library is done using the I2C module.
            break;

        case MFI_EVENT_CANNOT_SET_EXTRA_CURRENT:
            // Cannot send the extra current configuration message to  the iPod (USB only).
            break;

        case MFI_EVENT_GENERAL_ERROR:
            // General USB error.
            break;

        case MFI_EVENT_FATAL_ERROR:
            // Fatal USB error.
            break;

        case MFI_EVENT_IPOD_ATTACHED:
            // The library recognizes that an iPod has attached.  Identification is
            // complete, but authentication still needs to take place.  Do not spend
            // too much time here.
            break;

        case MFI_EVENT_IPOD_DETACHED:
            // The iPod has detached.
            // If the data session was open, tell the application layer.
            if ( iOSStatus.flags.bits.dataSessionOpen )
            {
                PED_CallbackDisconnect();
            }

            // Reset all flags and buffers.
            PEDI_InitializeVariables ();
            PEDI_RxDataReset();
            break;

        case MFI_EVENT_IDPS_NOT_SUPPORTED:
            // If the iPod doesn't suppport IDPS, then it doesn't support
            // apps either, so abandon the identification and authentication.
            return FALSE;
            break;

        case MFI_EVENT_LINGO_NOT_SUPPORTED:
            // The only lingo we are asking for is General, so if there is a
            // problem, we need to terminate.  See the online Help file
            // for more information about this event.
            return FALSE;
            break;

        case MFI_EVENT_CHECK_LINGO_OPTIONS:
            // Make sure the iPod can handle OS3 apps.  We have to check this here.
            // Some iPods won't return an error later.  See the online Help file
            // for more information about this event.
            if (*(UINT8 *)data == IPOD_LINGO_GENERAL)
            {
                #ifdef _PIC14E
                if( ((IPOD_OPTIONS_FOR_LINGO_GENERAL *)((UINT8*)(((UINT16)data)+1)))->iPhoneOS3Applications == 0  )
                #else
                if (((IPOD_OPTIONS_FOR_LINGO_GENERAL *)(data+1))->iPhoneOS3Applications == 0)
                #endif
                {
                    // This demo requires iOS app support
                    return FALSE;
                }
                #ifdef _PIC14E
                    iOSStatus.flags.bits.autolaunchSupported = ((IPOD_OPTIONS_FOR_LINGO_GENERAL *)((UINT8*)(((UINT16)data)+1)))->requestApplicationLaunch;
                #else
                    iOSStatus.flags.bits.autolaunchSupported = ((IPOD_OPTIONS_FOR_LINGO_GENERAL *)(data+1))->requestApplicationLaunch;
                #endif
            }
            break;

        case MFI_EVENT_TOKEN_PROBLEM:
            // This is NOT necessarily an error!  Older iPods may not support all the functionality that
            // is required by the latest Apple specifications.
            // See the Apple specifications and the online Help file for more information about this event.

            // There are no errors that will be reported here that we can recover from.
            // Items that are warnings will be ignored, and any true fails will cause
            // IDPS to fail.
            #if defined ( _PIC14E )
                ((IPOD_TOKEN_PROBLEM_INFO *)((UINT8*)((UINT16)data)))->action = IPOD_TOKEN_PROBLEM_IGNORE;
            #else
                ((IPOD_TOKEN_PROBLEM_INFO *)data)->action = IPOD_TOKEN_PROBLEM_IGNORE;
            #endif

            break;

        case MFI_EVENT_IPOD_CANNOT_CONNECT:
            // The iPod will not let us connect.
            break;

        case MFI_EVENT_IDPS_FAILURE:
            // IDPS failed.  We cannot communicate with the iPod.
            break;

        case MFI_EVENT_IPOD_AUTHENTICATION_FAILED:
            // Authentication failed.  We cannot communicate with the iPod.
            break;

        case MFI_EVENT_IPOD_READY:
            // Identification and authentication have completed, and we can now
            // communicate with the iPod.  For this demo to work, we need an Apple Device
            // that supports IDPS.

            pedInformation.flags.bits.deviceAttached = 1;
            pedInformation.flags.bits.deviceiOS  = 1;

            iOSInformation = (IPOD_INFORMATION *)data;         // Save a pointer to the iPod information structure.

            // Set the flag to sent the GetSupportedEventNotification command.
            iOSCommandStatus.flags.bits.sendGetSupportedEventNotification = 1;

            // The Apple device is attached, but the data session isn't open yet, so we
            // cannot exchange data.
            // PED_CallbackConnect ( PED_DEVICE_APPLE );
            break;

        case MFI_EVENT_COMMAND_AVAILABLE:
            // The iPod has sent us a command.
            #if defined ( _PIC14E )
            switch( ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->lingo )
            #else
            switch( ((IPOD_COMMAND *)data)->lingo )
            #endif
            {
                case IPOD_LINGO_GENERAL:
                    #if defined ( _PIC14E )
                    switch( ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->command )
                    #else
                    switch( ((IPOD_COMMAND *)data)->command )
                    #endif
                    {
                        case IPOD_iPodAck:

                            #ifdef _PIC14E
                            switch (*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+1))
                            #else
                            switch (*(((IPOD_COMMAND *)data)->pData+1))
                            #endif
                            {
                                case IPOD_AccessoryDataTransfer:
                                    iOSCommandStatus.flags.bits.waitingForDevDataTransferACK = 0;
                                    #ifdef _PIC14E
                                    if ( (*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData) == IPOD_ACK_SessionWriteFailure) )
                                    #else
                                    if ( (*(((IPOD_COMMAND *)data)->pData) == IPOD_ACK_SessionWriteFailure) )
                                    #endif
                                    {
                                        UINT16_VAL  sessionID;

                                        #ifdef _PIC14E
                                            sessionID.v[1] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+2);
                                            sessionID.v[0] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+3);
                                        #else
                                            sessionID.v[1] = *(((IPOD_COMMAND *)data)->pData+2);
                                            sessionID.v[0] = *(((IPOD_COMMAND *)data)->pData+3);
                                        #endif

                                        if ( sessionID.Val == iOSSessionID )
                                        {
                                            iOSStatus.flags.bits.waitingForSessionSpaceAvailable = 1;

                                            // The Apple Device didn't actually receive all of the bytes
                                            // that we sent it with the last DevDataTransfer command.  Since
                                            // the bytes are considered a stream, we must either resend the
                                            // portion of the command that was dropped, or depend on the
                                            // synchronization scheme to recover from the lost data.
                                            // This demo does NOT resend the last command.
                                        }
                                    }
                                    break;

                                case IPOD_SetEventNotification:
                                case IPOD_GetSupportedEventNotification:    // This command isn't supported if an ACK is received.
                                    // If autolaunch is supported, try to launch the app.
                                    iOSCommandStatus.flags.bits.sendAutolaunchRequest = iOSStatus.flags.bits.autolaunchSupported;
                                    break;
                            }
                            break;

                        case IPOD_OpenDataSessionForProtocol:
                            #if defined( _PIC14E )
                                iOSSessionID       = ((UINT16)(*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData)) << 8) | (UINT16)(*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+1));
                                iOSProtocolIndex   = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+2);

                            #else
                                iOSSessionID       = ((UINT16)(*(((IPOD_COMMAND *)data)->pData)) << 8) | (UINT16)(*(((IPOD_COMMAND *)data)->pData+1));
                                iOSProtocolIndex   = *(((IPOD_COMMAND *)data)->pData+2);
                            #endif

                            iOSCommandStatus.flags.bits.sendOpenDataSessionACK = 1;
                            #if defined ( _PIC14E )
                                iOSCommandStatus.transactionIDOpenDataSession = ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->transactionID;
                            #else
                                iOSCommandStatus.transactionIDOpenDataSession = ((IPOD_COMMAND *)data)->transactionID;
                            #endif
                            break;

                        case IPOD_CloseDataSession:
                            // Shut down everything, and make sure we don't send any more responses.
                            PEDI_RxDataReset();

                            // Tell the application that the data session is closed.
                            iOSStatus.flags.bits.dataSessionOpen = 0;
                            PED_CallbackDisconnect();

                            iOSCommandStatus.flags.bits.sendCloseDataSessionACK = 1;
                            #if defined ( _PIC14E )
                                iOSCommandStatus.transactionIDCloseDataSession = ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->transactionID;
                            #else
                                iOSCommandStatus.transactionIDCloseDataSession = ((IPOD_COMMAND *)data)->transactionID;
                            #endif
                            break;

                        case IPOD_iPodDataTransfer:
                            #if defined ( _PIC14E )
                                iOSCommandStatus.transactionIDiPodDataTransfer = ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->transactionID;
                            #else
                                iOSCommandStatus.transactionIDiPodDataTransfer = ((IPOD_COMMAND *)data)->transactionID;
                            #endif

                            if (!iOSStatus.flags.bits.dataSessionOpen)
                            {
                                // There is no session open.  Respond with an ACK and Bad Parameter.
                                iOSCommandStatus.flags.bits.sendiPodDataTransferNACK = 1;
                            }
                            else
                            {
                                // Copy the data into a buffer.  We may not have enough data
                                // for a command, or we may have several commands.  So we
                                // cannot process it here.

                                #if defined ( _PIC14E )
                                    PEDI_RxDataAdd ( ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData + 2, ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->dataLength - 2 );
                                #else
                                    PEDI_RxDataAdd ( ((IPOD_COMMAND *)data)->pData + 2, ((IPOD_COMMAND *)data)->dataLength - 2 );
                                #endif

                                iOSCommandStatus.flags.bits.sendiPodDataTransferACK = 1;
                            }
                            break;

                        case IPOD_iPodNotification:
                            #ifdef _PIC14E
                            if (*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData) == IPOD_iPodNotification_FlowControl)
                            #else
                            if (*(((IPOD_COMMAND *)data)->pData) == IPOD_iPodNotification_FlowControl)
                            #endif
                            {
                                iOSStatus.flags.bits.communicationWaiting = 1;
                                #ifdef _PIC14E
                                    iOSStatus.communicationWaitTimeoutAt.v[3] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+1);
                                    iOSStatus.communicationWaitTimeoutAt.v[2] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+2);
                                    iOSStatus.communicationWaitTimeoutAt.v[1] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+3);
                                    iOSStatus.communicationWaitTimeoutAt.v[0] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+4);
                                #else
                                    iOSStatus.communicationWaitTimeoutAt.v[3] = *(((IPOD_COMMAND *)data)->pData+1);
                                    iOSStatus.communicationWaitTimeoutAt.v[2] = *(((IPOD_COMMAND *)data)->pData+2);
                                    iOSStatus.communicationWaitTimeoutAt.v[1] = *(((IPOD_COMMAND *)data)->pData+3);
                                    iOSStatus.communicationWaitTimeoutAt.v[0] = *(((IPOD_COMMAND *)data)->pData+4);
                                #endif
                                iOSStatus.communicationWaitTimeoutAt.Val *= dwTicksPerMillisecond;  // Convert to ticks
                                iOSStatus.communicationWaitTimeoutAt.Val += TickGet();              // Add to current time
                            }
                            #ifdef _PIC14E
                            else if (*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData) == IPOD_iPodNotification_SessionSpaceAvailable)
                            #else
                            else if (*(((IPOD_COMMAND *)data)->pData) == IPOD_iPodNotification_SessionSpaceAvailable)
                            #endif
                            {
                                UINT16_VAL  sessionID;
                                #ifdef _PIC14E
                                    sessionID.v[1] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+1);
                                    sessionID.v[0] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+2);
                                #else
                                    sessionID.v[1] = *(((IPOD_COMMAND *)data)->pData+1);
                                    sessionID.v[0] = *(((IPOD_COMMAND *)data)->pData+2);
                                #endif

                                if ( sessionID.Val == iOSSessionID )
                                {
                                    iOSStatus.flags.bits.waitingForSessionSpaceAvailable = 0;
                                    iOSStatus.flags.bits.sendSmallDataTransfer = 1;
                                }
                            }
                            break;

                        case IPOD_RetSupportedEventNotification:
                            #ifdef _PIC14E
                            if ( ((IPOD_NOTIFICATIONS_BITMASK *)(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData))->SessionSpaceAvailable == 1 )
                            #else
                            if ( ((IPOD_NOTIFICATIONS_BITMASK *)(((IPOD_COMMAND *)data)->pData))->SessionSpaceAvailable == 1 )
                            #endif
                            {
                                // Set the flag to sent the SetEventNotification command.
                                iOSCommandStatus.flags.bits.sendSetEventNotification = 1;
                            }
                            else
                            {
                                // If autolaunch is supported, try to launch the app.
                                iOSCommandStatus.flags.bits.sendAutolaunchRequest = iOSStatus.flags.bits.autolaunchSupported;
                            }
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            break;

        case MFI_EVENT_COMMAND_SENT:
            iOSCommandStatus.flags.bits.sendingCommand = 0;
            break;

        // Digital Audio Events
        #ifdef IPOD_USE_USB_HOST
        case MFI_EVENT_AUDIO_SUPPORT_ERROR:
        case MFI_EVENT_AUDIO_RATE_ERROR:
        case MFI_EVENT_AUDIO_RECEIVING_DATA:
        case MFI_EVENT_AUDIO_STOPPING_DATA:
        case MFI_EVENT_AUDIO_SET_SAMPLE_RATE:
        case MFI_EVENT_AUDIO_STREAM_RECEIVED:
            // We are not using Digital Audio, so ignore these events.
            break;
        #endif

        // UART Only Events
        case MFI_EVENT_RECEIVE_BUFFER_OVERRUN:
            // UART receive buffer overrun.
            #ifdef __DEBUG
                while (1);
            #endif
            break;

        case MFI_EVENT_RECEIVE_BUFFER_OVERRUN_COMMAND:
            // UART receive buffer overrun.
            #ifdef __DEBUG
                while (1);
            #endif
            break;

        default:
            break;
    }

    return TRUE;
}

/****************************************************************************
  Function:
    BOOL USB_ApplicationDataEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )

  Summary:
    Handles USB data application events

  Description:
    Handles USB data application events

  Precondition:
    None

  Parameters:
    BYTE address - address of the device causing the event
    USB_EVENT event - the event that has occurred
    void* data - data associated with the event
    DWORD size - the size of the data in the data field

  Return Values:
    BOOL - Return TRUE of the event was processed.  Return FALSE if the event
           wasn't handled.

  Remarks:
    None
  ***************************************************************************/

#if defined ( IPOD_USE_USB_HOST )

BOOL USB_ApplicationDataEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    return FALSE;
}

#endif

/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )

  Summary:
    Handles USB application events

  Description:
    Handles USB application events

  Precondition:
    None

  Parameters:
    BYTE address - address of the device causing the event
    USB_EVENT event - the event that has occurred
    void* data - data associated with the event
    DWORD size - the size of the data in the data field

  Return Values:
    BOOL - Return TRUE of the event was processed.  Return FALSE if the event
           wasn't handled.

  Remarks:
    None
  ***************************************************************************/

#if defined ( IPOD_USE_USB_HOST )

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( event )
    {
        // --------------------------------------------------------------------------
        // HID error events

        case EVENT_HID_BAD_REPORT_DESCRIPTOR:
            // This will occur before we know exactly what HID device has attached,
            // so we have to handle it here.
            return TRUE;

        // --------------------------------------------------------------------------
        // Host events

        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            if (((USB_VBUS_POWER_EVENT_DATA*)data)->current <= (MAX_ALLOWED_CURRENT / 2))
            {
                return TRUE;
            }
            break;

        case EVENT_VBUS_RELEASE_POWER:
        case EVENT_HUB_ATTACH:
        case EVENT_UNSUPPORTED_DEVICE:
        case EVENT_CANNOT_ENUMERATE:
        case EVENT_CLIENT_INIT_ERROR:
        case EVENT_OUT_OF_MEMORY:
        case EVENT_UNSPECIFIED_ERROR:
        case EVENT_DETACH:
            PEDI_InitializeVariables ();
            return TRUE;
            break;

        case EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION:
            // The Android has an "enumerate everything" entry in the TPL, which we
            // must override for the Apple devices.  When it finds the HID configuration, we
            // can let it enumerate, because then it will have found the correct driver.
            if ( ((((USB_OVERRIDE_CLIENT_DRIVER_EVENT_DATA *)data)->idVendor)           == 0x05AC) &&
                 ((((USB_OVERRIDE_CLIENT_DRIVER_EVENT_DATA *)data)->idProduct & 0xFF00) == 0x1200) &&
              !( ((((USB_OVERRIDE_CLIENT_DRIVER_EVENT_DATA *)data)->bDeviceClass)       == 0x03)   &&
                 ((((USB_OVERRIDE_CLIENT_DRIVER_EVENT_DATA *)data)->bDeviceSubClass)    == 0x00)   &&
                 ((((USB_OVERRIDE_CLIENT_DRIVER_EVENT_DATA *)data)->bDeviceProtocol)    == 0x00) ))
            {
                return TRUE;    // Override
            }
            break;

        // --------------------------------------------------------------------------
        // Android events

        case EVENT_ANDROID_DETACH:
            PED_CallbackDisconnect();
            PEDI_InitializeVariables ();
            return TRUE;
            break;

        // Android Specific events
        case EVENT_ANDROID_ATTACH:
            pedInformation.flags.bits.deviceAttached    = 1;
            pedInformation.flags.bits.deviceAndroid     = 1;
            androidDeviceHandle                         = data;

            PED_CallbackConnect ( PED_DEVICE_ANDROID );
            return TRUE;

        default :
            break;
    }
    return FALSE;
}

#endif


