/******************************************************************************

* Apple Device Driver File *

This file contains the functions necessary for an application to interface to
an Apple Device.  It handles all of the hardware interface (USB or UART), and
will automatically handle identification and authentication, informing the
application layer when the Apple Device has been successfully authenticated.  If
Digital Audio is being used, it will also handle that automatically, informing
the application when it needs to take actions such as change the sample rate
or start or stop audio playback.  This file handles OS3 and pre-OS3
identification and authentication.  The library is intended to serve as a
minimal hardware wrapper, allowing the application to utilize the full
capabilities of the iPod Accessory Protocol (iAP).

The MFi Library driver is event driven, meaning that when certain situations
occur, the driver will call an event handler in the application.  The event
handler receives an indication of what event occurred, and any data associated
with that event.  It is then up to the application to take the appropriate action
in response to that event.  Some events are callbacks to the application.
The application must then perform the required action and return the appropriate
response.

To use the driver, the application must provide the following:
    * Delay functions with the prototypes void Delay10us( UINT32 count ); and
        void DelayMs( UINT16 count );  These functions are provided with the
        Microchip Application Library TimeDelay.c/.h files.
    * TICK timing functions, identical to those used by the TCP/IP stack.  A
        sample of these functions is provided with the demo applications.
    * The standard I2C interface module. This module is provided with the
        library installation.

The application must initialize the global mfi_iPodApplicationInformation variable of type
IPOD_APPLICATION_INFORMATION.  This variable must be maintained
by the application, as the driver can require the information at any time.

The timing functions are required so the library can be used in applications
running at various clock frequencies.

To initialize the driver and all lower driver layers, the application must do
the following:
    * Initialize the TICK timing functions
    * Initialize the IPOD_APPLICATION_INFORMATION mfi_iPodApplicationInformation variable
    * Call the function MFI_Initialize

* Application Code *

Basic initialization is shown below:
<code>
TickInit();                     // Initialize the timing function.
InitializeiPodInformation();    // Application function to initialize mfi_iPodApplicationInformation
if (MFI_Initialize( &mfi_iPodApplicationInformation ))
{
    // We have a major problem.
    while (1);
}
</code>
Some hardware configurations require specific hardware initialization before
MFI_Initialize is called.  For more information, see MFI_Initialize.

During normal processing, the application must call the function MFI_Tasks at
least every few milliseconds.  Hardware operation is interrupt driven, so an
exact polling rate is not required.  However, faster polling will decrease
response time to events such as an Apple device docking.

The basic application framework is as shown below:
<code>
while (1)
{
    MFI_Tasks();

    // Other application code here...
}
</code>

If the library encounters something that the application needs to be aware of,
it will call the function MFI_HandleiPodEvents.  This function must be
provided by the application to respond to MFi Library events.  See the
enumeration MFI_EVENT for a complete list of all events that the MFi Library
can issue and detailed descriptions of the events.  Key events are:
    * MFI_EVENT_IS_IPOD_ATTACHED - Asks the application for the status of
                the Accessory Power pin.
    * MFI_EVENT_IPOD_READY - The Apple Device has been authenticated and is ready for
                any command from any lingo.  NOTE: Digital Audio Lingo accessories
                should use the MFI_EVENT_IPOD_READY_AUDIO_HOST event instead.
    * MFI_EVENT_COMMAND_AVAILABLE - The Apple Device has sent the application a
                command.

The event handler should have the following basic structure.  For best results,
copy the event handler from a demo application as a starting point.
<code>
BOOL MFI_HandleiPodEvents( MFI_EVENT event, void *data, UINT32 size )
{
    switch( event )
    {
        case MFI_EVENT_IS_IPOD_ATTACHED:
            // See if the Apple Device is docked by checking pins 13 and 30 on the
            // connector.
            return (IPOD_ACCESSORY_POWER == 1) && (IPOD_DETECT == 0);
            break;

        case MFI_EVENT_CP_SET_NRESET:
            // Set the CP nRESET line to the requested state.
            MFI_AUTH_NRESET = size;
            break;

        case MFI_EVENT_CP_OPEN_I2C:
            // Enable I2C1 at the proper frequency.
            #if defined( __18CXX )
                I2CConfigure( mfi_iPodApplicationInformation.cpCommunicationModule,
                    I2C_MODE_MASTER | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE );
            #endif
            I2CSetFrequency( mfi_iPodApplicationInformation.cpCommunicationModule,
                I2C_Clock(), IPOD_CP_FREQUENCY );
            I2CEnable( I2C1, TRUE );
            Delay10us( 10 );
            break;

        case MFI_EVENT_CP_I2C_CLOSED:
            // The library is done using the I2C module.
            break;

        case MFI_EVENT_CANNOT_SET_EXTRA_CURRENT:
            // Cannot send the extra current configuration message to  the Apple Device
            // (USB only).
            break;

        case MFI_EVENT_GENERAL_ERROR:
            // General USB error.
            break;

        case MFI_EVENT_FATAL_ERROR:
            // Fatal USB error.
            break;

        case MFI_EVENT_IPOD_ATTACHED:
            // The library recognizes that an Apple Device has attached.  Identification is
            // complete, but authentication still needs to take place.
            break;

        case MFI_EVENT_IPOD_DETACHED:
            // The Apple device has detached.
            #if defined( __18CXX )
                // An Apple device just detached.  Tristate the RX and TX lines.
                USART1_RX_TRIS  = 1;
                USART1_TX_TRIS  = 1;
            #endif
            // If the application reconfigured itself for the specific attached device,
            // set the IPOD_APPLICATION_INFORMATION back to its default values.
            break;

        case MFI_EVENT_IDPS_NOT_SUPPORTED:
            // The Apple Device doesn't suppport IDPS.  If the accessory requires an app,
            // then it also requires an Apple Device that supports IDPS, so return FALSE
            // to abandon the identification and authentication.  If the accessory
            // does not require an app, return TRUE to allow the library to identify
            // using IDL.

            // If we are a USB Host accessory that supports the 2G iPod nano, update
            // the command delay for the delay needed for IDL.  Otherwise, commandDelay
            // can be left at 0.
            mfi_iPodApplicationInformation.operationalParameters.commandDelay = IPOD_COMMAND_DELAY_IDL;
            break;

        case MFI_EVENT_LINGO_NOT_SUPPORTED:
            // The requested lingo is not supported.  If the accessory requires
            // the lingo, return FALSE.  Otherwise, reconfigure the accessory and
            // return TRUE.
            break;

        case MFI_EVENT_LINGO_VERSION:
            // This event is only thrown for IDL devices.  Retain whatever versions will
            // be necessary for the accessory.
            return TRUE;

        case MFI_EVENT_CHECK_LINGO_OPTIONS:
            // Check the lingo options that are supported by this Apple Device.  Check the
            // specified options and configure the accessory appropriately for the
            // supported options.  If the accessory requires support that the Apple device
            // does not provide, return FALSE.  The following is an example of an
            // accessory that requires OS3 apps (OS3 was the first Apple Device
            // operating system version that supported communication with accessories).
            if (*(UINT8 *)data == IPOD_LINGO_GENERAL)
            {
                if (!((IPOD_OPTIONS_FOR_LINGO_GENERAL *)(data+1))->iPhoneOS3Applications)
                {
                    return FALSE;
                }
            }
            break;

        case MFI_EVENT_TOKEN_PROBLEM:
            // The Apple Device returned a non-zero status for an IDPS token.  The following
            // example shows how to ignore the problem and continue with identification.
            ((IPOD_TOKEN_PROBLEM_INFO *)data)->action = IPOD_TOKEN_PROBLEM_IGNORE;
            break;

        case MFI_EVENT_IPOD_CANNOT_CONNECT:
            // The Apple Device will not let us connect.
            break;

        case MFI_EVENT_IDPS_FAILURE:
            // IDPS failed.  We cannot communicate with the Apple Device.
            break;

        case MFI_EVENT_IPOD_AUTHENTICATION_FAILED:
            // Authentication failed.  We cannot communicate with the Apple Device.
            break;

        case MFI_EVENT_IPOD_READY:
            // An Apple Device is docked and ready to go, unless the Digital Audio Lingo
            // is in use.  In this case, we must wait for the
            // MFI_EVENT_IPOD_READY_AUDIO_HOST event for all Apple Device information
            // to be valid.
            break;

        case MFI_EVENT_IPOD_READY_AUDIO_HOST:
            // This event only occurs if the Digital Audio Lingo is being used.
            // At this point, all Apple Device information is valid, and the application
            // can start to manipulate the Apple Device based on that information.

            // If we are a USB Host accessory that supports the 2G iPod nano, update
            // the command delay to the application specific value (usually 0).
            mfi_iPodApplicationInformation.operationalParameters.commandDelay = IPOD_COMMAND_DELAY;
            break;

        case MFI_EVENT_IPOD_READY:
            // An Apple Device is docked and ready to go...
            break;

        case MFI_EVENT_COMMAND_AVAILABLE:
            switch( ((IPOD_COMMAND *)data)->lingo )
            {
                case IPOD_LINGO_GENERAL:
                    switch( ((IPOD_COMMAND *)data)->command )
                    {
                        // Handle the various commands that we might receive.
                        // Important data here is:
                        //   Transaction ID: ((IPOD_COMMAND *)data)->transactionID
                        //   Command data:   ((IPOD_COMMAND *)data)->pData
                        //   Data length:    ((IPOD_COMMAND *)data)->dataLength

                        case IPOD_iPodDataTransfer:
                            // Copy the data into a buffer for processing in
                            // the background.  We may not receive all required
                            // data in a single transfer.
                            break;
                    }
                    break;

                // Handle other lingoes.
            }
            break;

        case MFI_EVENT_COMMAND_SENT:
            // The last command has been sent.  This event can be used if the
            // accessory needs to send back-to-back commands, such as a DevACK
            // followed by a DevDataTransfer.
            break;

        // Digital Audio Events
        case MFI_EVENT_AUDIO_SUPPORT_ERROR:
        case MFI_EVENT_AUDIO_RATE_ERROR:
            // Digital audio error.
            break;

        case MFI_EVENT_AUDIO_RECEIVING_DATA:
            // We will now begin receiving digital audio data.
            break;

        case MFI_EVENT_AUDIO_STOPPING_DATA:
            // Digital audio data is no longer being received.
            break;

        case MFI_EVENT_AUDIO_SET_SAMPLE_RATE:
            // The digital audio sample rate is changing.  Adjust the decoder.
            break;

        case MFI_EVENT_AUDIO_STREAM_RECEIVED:
            // This event should only be received by the Data Event Handler.
            break;

        // UART Only Events
        case MFI_EVENT_RECEIVE_BUFFER_OVERRUN:
            // UART receive buffer overrun.
            break;

        case MFI_EVENT_RECEIVE_BUFFER_OVERRUN_COMMAND:
            // UART received Apple device command overrun.
            break;

        default:
            break;
    }

    return TRUE;
}
</code>

If the USB interface is being used with the accessory acting as a USB Embedded
Host, a data event handler is also required.  The data
event handler should have the following basic structure.  For best results,
copy the data event handler from a demo application as a starting point.
<code>
BOOL MFI_HandleiPodDataEvents( MFI_EVENT event, void *data, UINT32 size )
{
    if ((event == MFI_EVENT_AUDIO_STREAM_RECEIVED) && (size > 0))
    {
        // Process digital audio data.
    }

    return TRUE;
}
</code>

The application can use the function MFI_SendCommand to send an iAP command to the
Apple device.  If the Apple device responds, the driver will issue an MFI_EVENT_COMMAND_AVAILABLE
event when the iAP response is received.

In the code example above, the accessory can receive data from the Apple Device via the
iPodDataTransfer iAP command.  In return, the accessory may then send a response.  The
follow code will send an AccessoryDataTransfer iAP command response to an Apple Device app.
<code>
UINT16 transactionID;

pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 3 );
if (pCommandData != NULL)
{
    *pCommandData++ = HIGH_BYTE( iPodSessionID );
    *pCommandData++ = LOW_BYTE(  iPodSessionID );
    *pCommandData++ = MY_ACCESSORY_COMMAND_RESPONSE;

    MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_AccessoryDataTransfer, 3, &transactionID );
}
</code>

Some iAP commands are not available to the application layer.  These are primarily
commands that are used for authentication, which is handled automatically by
the driver, so they should not be needed by the application.  The following is
the list of General Lingo commands that the application should not issue and
does not need to respond to:
        * RequestIdentify (0x00) (receive)
        * RequestLingoProtocolVersion (0x0F) (send, USB interface and General, Extended Interface, and Digital Audio lingoes only)
        * ReturnLingoProtocolVersion (0x10) (receive, USB interface and General, Extended Interface, and Digital Audio lingoes only)
        * RequestTransportMaxPayloadSize (0x11) (send)
        * ReturnTransportMaxPayloadSize (0x12) (receive)
        * IdentifyDeviceLingoes (0x13) (send)
        * GetDevAuthenticationInfo (0x14) (receive)
        * RetDevAuthenticationInfo (0x15) (send)
        * AckDevAuthenticationInfo (0x16) (receive)
        * GetDevAuthenticationSignature (0x17) (receive)
        * RetDevAuthenticationSignature (0x18) (send)
        * AckDevAuthenticationStatus (0x19) (receive)
        * GetiPodOptions (0x24) (send)
        * RetiPodOptions (0x25) (receive)
        * GetAccessoryInfo (0x27) (receive)
        * RetAccessoryInfo (0x28) (send)
        * StartIDPS (0x38) (send)
        * SetFIDTokenValues (0x39) (send)
        * RetFIDTokenValueACKs (0x3A) (receive)
        * EndIDPS (0x3B) (send)
        * IDPSStatus (0x3C) (receive)
        * GetiPodOptionsForLingo (0x4B) (send)
        * RetiPodOptionsForLingo (0x4C) (receive)


* USB INTERFACE REQUIREMENTS - USB HOST ACCESSORY *

The USB interface requires that two additional event handlers be defined, to handle
events from the USB stack that are not handled by the MFI Library and to allow the
application to support devices other than just Apple Devices.  The functions must be named
as follows, to work correctly with the library.  See the demos for complete examples
of these event handlers.

<code>
#ifdef IPOD_USE_USB_HOST
BOOL USB_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size )
{
    // We are not supporting any other devices that generate data events.
    return FALSE;
}
#endif
</code>

<code>
#ifdef IPOD_USE_USB_HOST
BOOL USB_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size )
{
    switch( event )
    {
        // Add other device support event handling here.

        // --------------------------------------------------------------------------
        // Host events

        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            return TRUE;
            break;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
        case EVENT_UNSUPPORTED_DEVICE:
            // A USB device other than one listed in the TPL has attached.
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
        case EVENT_CLIENT_INIT_ERROR:
        case EVENT_OUT_OF_MEMORY:
        case EVENT_UNSPECIFIED_ERROR:
            return TRUE;
            break;

        default;
            break;
    }

    return FALSE;
}
#endif
</code>


* USING DIGITAL AUDIO - USB HOST ACCESSORY *

If the application's IPOD_APPLICATION_INFORMATION structure indicates Digital
Audio lingo support, the Apple Device will automatically send a GetAccessorySampleRateCaps
command.  The driver will automatically respond to this command, indicating
support for 32 KHz, 44.1 KHz, and 48 KHz sample rates (the minimum support
required).  The driver will issue events to the main event handler when the
application needs to set the sample rate for the incoming data
(MFI_EVENT_AUDIO_SET_SAMPLE_RATE), when the audio data is starting
(MFI_EVENT_AUDIO_RECEIVING_DATA), and when the audio data is stopping
(MFI_EVENT_AUDIO_STOPPING_DATA).  After the MFI_EVENT_AUDIO_RECEIVING_DATA event,
the application will begin receiving MFI_EVENT_AUDIO_STREAM_RECEIVED events via
the MFI_HandleiPodDataEvents handler, indicating reception of audio data.
The application must process the received data within approximately 500 us, as
new data will be received every one millisecond.

If Digital Audio is used, then the following Digital Audio lingo commands are
handled by the driver:
        * GetAccessorySampleRateCaps (receive)
        * RetAccessorySampleRateCaps (send)
        * TrackNewAudioAttributes (previously called NewiPodTrackInfo) (receive)

In OS v2.21, Digital Audio may not stream if identification and
authentication require more than a couple seconds.  An OS upgrade is recommended.


* USB INTERFACE REQUIREMENTS - USB PERIPHERAL DEVICE ACCESSORY *

Applications that utilize the USB Peripheral Device interface must provide
callbacks that are required by the USB Stack:
        * void USBCBErrorHandler ( void );
        * void USBCBReset ( void );
        * void USBCBSendResume ( void );
        * void USBCBSuspend ( void );
        * void USBCBWakeFromSuspend ( void );

*******************************************************************************/
//DOM-IGNORE-BEGIN
/******************************************************************************

File Name:       MFI_iPod.h
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

#ifndef _IPOD_H_
#define _IPOD_H_


    // This constant indicates the version of the library, in BCD format.
    // For example, 0x3014 indicates MFi Library v3.01.04.
#define MFI_VERSION                 0x3050


#include "mfi_config.h"

#if defined ( IPOD_USE_USB_DEVICE )
    #include "./USB/usb.h"
#endif


//******************************************************************************
//******************************************************************************
// Section: Apple Device Configuration
//******************************************************************************
//******************************************************************************

#define MFI_CONVERT_TO_BCD(x)   (((x/10) << 4) + (x%10))

#define MFI_CONFIG_VERSION  ( (MFI_CONVERT_TO_BCD( _MFI_CONFIG_VERSION_MAJOR ) << 12) + (MFI_CONVERT_TO_BCD( _MFI_CONFIG_VERSION_MINOR ) << 4) + MFI_CONVERT_TO_BCD( _MFI_CONFIG_VERSION_DOT ) )

#if ( MFI_CONFIG_VERSION != MFI_VERSION )
    #error Please regenerate your configuration files with MFIConfig.exe and verify your library version (mfi_Version)
#endif

//DOM-IGNORE-END

// *****************************************************************************
/* Section: Apple device Hardware Interface

Make sure a valid interface has been defined.  If the wrong interface is defined
in the configuration file, other options may not be set up correctly, so
generate an error.
*/
#if defined( IPOD_USE_USB )
    // MFi Library v2.02 and greater differentiate between USB Host and USB Device operation.
    #error Please regenerate the configuration file with the latest MFIConfig.exe.
    #error ***** Be sure to replace references to IPOD_USE_USB with IPOD_USE_USB_HOST for
    #error ***** accessory USB Embedded Host operation, or IPOD_USE_USB_DEVICE for accessory
    #error ***** USB Device operation.
#endif

#if defined( IPOD_USE_USB_HOST ) && !(defined( __C30__ ) || defined( __PIC32MX__ ))
    #error This processor does not support this Apple device interface.
#endif


#if defined( IPOD_USE_USB_DEVICE ) || defined( IPOD_USE_USB_HOST )
    #include "usb_config.h"
    #include "USB/usb.h"
    #ifdef IPOD_USE_USB_HOST
        #include "USB/usb_host_hid.h"
    #endif
    #ifdef IPOD_USE_USB_HOST_AUDIO
        #include "USB/usb_host_audio_v1.h"
    #endif
#endif

#define IPOD_MAX_SMALL_PACKET_PAYLOAD_SIZE  251
#if defined ( __18CXX ) || defined ( _PIC14E )
    #if IPOD_COMMAND_PAYLOAD_SIZE_IN > IPOD_MAX_SMALL_PACKET_PAYLOAD_SIZE
        #warning The maximum received command payload size is 251
        #undef IPOD_COMMAND_PAYLOAD_SIZE_IN
        #define IPOD_COMMAND_PAYLOAD_SIZE_IN IPOD_MAX_SMALL_PACKET_PAYLOAD_SIZE
    #endif
    #if IPOD_COMMAND_PAYLOAD_SIZE_OUT > IPOD_MAX_SMALL_PACKET_PAYLOAD_SIZE
        #warning The maximum transmitted command payload size is 251
        #undef IPOD_COMMAND_PAYLOAD_SIZE_OUT
        #define IPOD_COMMAND_PAYLOAD_SIZE_OUT IPOD_MAX_SMALL_PACKET_PAYLOAD_SIZE
    #endif
#endif


//******************************************************************************
//******************************************************************************
// Section: Apple Device Constants
//******************************************************************************
//******************************************************************************

//******************************************************************************
// Section: Apple Device Error Codes
//******************************************************************************

    // The operation was successful.
#define IPOD_SUCCESS                            0

    // The operation failed.  See MFI_Initialize for more information about
    // this error.
#define IPOD_ERROR                              1

    // The Apple device is not in a state to perform the operation.
#define IPOD_NOT_READY                          2

    // The Apple device is busy performing another task, and cannot send a message.
#define IPOD_BUSY                               3

    // Coprocessor chip error.  See MFI_Initialize for more information about
    // this error.
#define IPOD_CP_ERROR                           4

    // The Apple device has reached the maximum allowed accessory connections.
#define IPOD_ERROR_MAX_CONNECTIONS              5

   // Problem with FID tokens.  Confirm there are no mismatches in supported
   // lingoes, capabilities, and preferences.  For example, if the Digital Audio
   // is used, it must be indicated both in the supported lingoes and in the
   // accessory capabilities.
#define IPOD_ERROR_FID_TOKEN_PROBLEM            6

    // The accessory was not authenticated.
#define IPOD_ERROR_NOT_AUTHENTICATED            9

    // Bad authentication version.
#define IPOD_ERROR_BAD_AUTHENTICATION_VERSION   10

    // Invalid certificate from the CP chip.
#define IPOD_ERROR_CERTIFICATE_INVALID          11

    // Certificate permissions are invalid for the accessory.
#define IPOD_ERROR_PERMISSIONS_INVALID          12

    // The wrong value of accessory resistor is present.
#define IPOD_ERROR_ACCESSORY_RESISTOR_INVALID   13

    // Could not allocate memory for the Apple device command buffers.  Ensure that a
    // heap has been defined for the project, and that the heap size is adequate.
#define IPOD_ERROR_OUT_OF_MEMORY                14

    // The maxCommandPayloadLengthIn or maxCommandPayloadLengthOut value is less
    // than the minimum required by the Apple device (IPOD_MIN_COMMAND_PAYLOAD_LENGTH).
    // Or the commandDataSize parameter of the MFI_SendCommand function is too
    // large.
#define IPOD_ERROR_INVALID_IAP_COMMAND_LENGTH   15

    // There was a problem getting the certificate length from the CP chip.
    // This is usually due to a hardware conflict on the CP communication interface.
#define IPOD_ERROR_BAD_CERTIFICATE_LENGTH       16

    // The Apple device returned an error for the accessory's RetDevAuthenticationInfo
    // command.
#define IPOD_ERROR_CERTIFICATE_PIECE_PROBLEM    17

    // The Apple device returned an error in the AckDevAuthenticationInfo command.  This
    // indicates that there was a problem with the certificate that was sent to
    // the Apple device.  It can indicate a problem with correctly reading the certificate
    // from the CP.
#define IPOD_ERROR_CERTIFICATE_PROBLEM          18

    // On the call to MFI_Intialize, the pointer parameter does not point to the global
    // mfi_iPodApplicationInformation.  Applications should use this global
    // IPOD_APPLICATION_INFORMATION variable to define the application
    // specific information.
#define IPOD_ERROR_INVALID_INFORMATION_STRUCTURE    19

// *****************************************************************************
/* MFI Events

These events are generated by the driver when certain events occur, or when the
driver needs the application to perform a task.  The application provided
functions MFI_HandleiPodEvents and MFI_HandleiPodEvents are called to handle
these events.
*/
typedef enum
{
        // This event is a callback to the application layer to
        // see if an Apple device is attached.  The application is responsible for
        // determining if an Apple device is docked in the accessory.  In general,
        // this consists of checking the Accessory Power pin from the Apple device.
        // The data pointer parameter is null, and the size parameter indicates
        // whether or not the driver thinks the Apple device is attached (0=not attached,
        // 1=attached).  This indication should be utilized when using the UART
        // interface with PIC18, to take the RX and TX lines out of tristate.
        // The 16 and 32-bit MCUs handle this automatically.
    MFI_EVENT_IS_IPOD_ATTACHED,

        // This event is a callback to the application layer to set the
        // authentication coprocessor nRESET line to the indicated value.
        // This allows the application to use any I/O pin for the reset line.
        // The least significant byte contains the value to set the pin (0 or 1).
        // The data pointer is not used.
    MFI_EVENT_CP_SET_NRESET,

        // This event is a callback to the application layer to enable the I2C
        // module and set its speed to up to 50kHz.  Since the speed of the I2C
        // depends on the execution speed of the application, the application
        // must be responsible for this action.  It the application cannot currently
        // enable the I2c module for use by the MFI Library, it should return FALSE
        // for this event.  Otherwise, it should enable and configure the appropriate
        // I2C module and return TRUE.  The event handler should use the provided I2C
        // drivers.  Neither the data nor the size parameter is used by this event.  After
        // this event, the application should not use the I2C module until the event
        // MFI_EVENT_CP_I2C_CLOSED is received.
    MFI_EVENT_CP_OPEN_I2C,

        // This event lets the application know that the I2C module is now
        // available for general use.  Neither the data nor the size parameter is
        // used by this event.
    MFI_EVENT_CP_I2C_CLOSED,

        // This event is thrown if there is a problem issuing the USB device request
        // to set the extra current that the Apple device can draw.
    MFI_EVENT_CANNOT_SET_EXTRA_CURRENT,

        // This event is thrown if there is a problem communicating with the Apple device
        // when it first attaches.  This error may be a simple communication
        // problem, and redocking the Apple device may fix it.
    MFI_EVENT_GENERAL_ERROR,

        // This event is thrown if there is a nonrecoverable system error.  An
        // released end application should never throw this error.  It usually
        // indicates a problem with the build, such as not enough heap space,
        // which cannot be fixed by simply redocking the Apple device.
    MFI_EVENT_FATAL_ERROR,

        // An Apple device has attached and completed the identification process.  At this
        // point, IDPS or IDL is complete, but authentication must still be performed.
        // The data pointer is null, and the size parameter is zero.  To ensure that
        // ATS timing requirements are met, processing here should be brief.
    MFI_EVENT_IPOD_ATTACHED,

        // An Apple device has detached.  When using the UART interface, the RX and TX
        // lines should be tristated at this event.
    MFI_EVENT_IPOD_DETACHED,

        // This event is issued if the Apple device does not support IDPS.  This indicates
        // that the Apple device is an older model that does not support applications.
        // Return TRUE to allow the accessory to use IDL to identify and authenticate,
        // or return FALSE to indicate that the accessory is not supported.  The
        // data and size parameters are both zero.
    MFI_EVENT_IDPS_NOT_SUPPORTED,

        // Either the Apple device does not support one of the lingoes specified by the
        // application, or the version of the lingo is not supported by the
        // driver.  The data pointer parameter is NULL.  If IDPS is being used,
        // the size parameter is the lingo that is not supported.  If IDL is
        // being used, the size parameter is zero.  If the application would like to
        // reconfigure itself by changing the IPOD_APPLICATION_INFORMATION structure
        // whose pointer it passed to the driver on the call to MFI_Initialize
        // and try to authenticate again, it should do so at this
        // event and return TRUE.  If the current lingoes are required for operation
        // and the application cannot reconfigure itself, return FALSE so the driver
        // will halt the attach attempt and display an "Accessory not supported"
        // message on the Apple device.
    MFI_EVENT_LINGO_NOT_SUPPORTED,

        // This event will only be thrown if the attached Apple device does not support
        // IDPS.  The library will automatically query the attached device for the
        // version of each lingo for which the accessory has claimed support.  The data
        // pointer points to a structure of type IPOD_LINGO_VERSION_INFORMATION.  The
        // size parameter indicates the size of this structure.  The application should
        // check the lingo version and configure itself accordingly, if necessary.  The
        // return condition from this event is arbitrary.  If the application layer needs
        // to retain this information for later use, it must copy the values locally.
        // The library does not retain this information.
    MFI_EVENT_LINGO_VERSION,

        // This event is thrown if the attached Apple device supports IDPS.  When the Apple device
        // first attaches, the driver will issue a GetiPodOptionsForLingo command
        // for each supported lingo to determine the options that the Apple device supports.
        // The data pointer points to the returned byte string from the Apple device.  The
        // first byte is the lingo for the options (for example, IPOD_LINGO_GENERAL).
        // The following bytes are the returned option bytes from the Apple device.  The size
        // parameter is the total number of bytes.  The
        // application should examine this information and update the
        // IPOD_APPLICATION_INFORMATION structure whose pointer it passed to the driver
        // on the call to MFI_Initialize.  Upon return from this event, the
        // driver will then send the required FID tokens for the lingo.
    MFI_EVENT_CHECK_LINGO_OPTIONS,

        // This event is thrown if the attached Apple device supports IDPS and the Apple device
        // returns a non-zero status when the accessory sends IDPS tokens.  The data
        // pointer points to a structure of type IPOD_TOKEN_PROBLEM_INFO, and the
        // size parameter is the size of this structure.  The application should
        // evaluate the information in this structure and tell the driver how to
        // proceed by setting the action field appropriately.  Possible courses of
        // action are:
        //  * update the fields in the IPOD_APPLICATION_INFORMATION structure and
        //      retry the token (IPOD_TOKEN_PROBLEM_RETRY).
        //  * update the fields in the IPOD_APPLICATION_INFORMATION structure and
        //      restart IDPS (IPOD_TOKEN_PROBLEM_RESET).  If the Apple Device displays
        //      the message "This accessory is not supported by ..." if a simple
        //      retry is performed, then use this option.  Since this will cause an
        //      increase in the time needed to perform IDPS, which is a time sensitive
        //      operation, only use this option if required.
        //  * ignore the problem and continue sending tokens using the existing
        //      information (IPOD_TOKEN_PROBLEM_IGNORE).
        //  * fail the IDPS process and abort the connection (IPOD_TOKEN_PROBLEM_FAIL).
    MFI_EVENT_TOKEN_PROBLEM,

        // This error event is issued if an Apple device using IDPS cannot connect
        // to the accessory.  The size parameter indicates the error.  Errors
        // can be IPOD_ERROR_MAX_CONNECTIONS or IPOD_ERROR_FID_TOKEN_PROBLEM.
    MFI_EVENT_IPOD_CANNOT_CONNECT,

        // This error event is issued if an Apple device using IDPS returns a failure
        // when the IDPSStatus command is issued.  The data pointer is null,
        // and the size pointer is the status value returned by the Apple device.
    MFI_EVENT_IDPS_FAILURE,

        // The Apple device did not authenticate the accessory.  The size parameter indicates
        // the error code.  Possible errors generated from receiving the AckDevAuthenticationStatus
        // command from the Apple device are IPOD_ERROR_NOT_AUTHENTICATED,
        // IPOD_ERROR_BAD_AUTHENTICATION_VERSION, IPOD_ERROR_CERTIFICATE_INVALID,
        // IPOD_ERROR_PERMISSIONS_INVALID, IPOD_ERROR_ACCESSORY_RESISTOR_INVALID,
        // or IPOD_ERROR. Errors generated at various other points during authentication
        // are IPOD_ERROR_BAD_CERTIFICATE_LENGTH, IPOD_ERROR_CERTIFICATE_PIECE_PROBLEM, or
        // IPOD_ERROR_CERTIFICATE_PROBLEM.
    MFI_EVENT_IPOD_AUTHENTICATION_FAILED,

        // The Apple device has successfully authenticated the accessory, and will now
        // accept all commands from all supported lingoes.  The data pointer
        // parameter points to information about the attached Apple device in an IPOD_INFORMATION
        // information structure.  DO NOT ALTER ANY INFORMATION IN THIS STRUCTURE.
        // The size parameter will be the size of the structure.  If the Digital Audio
        // Lingo is supported, the application must wait for the MFI_EVENT_IPOD_READY_AUDIO_HOST
        // event to determine if Extended Interface mode is required to utilize digital audio.
        // To ensure that ATS timing requirements are met, processing here should be brief.
    MFI_EVENT_IPOD_READY,

        // The Apple device has sent a command to the accessory, and the application layer
        // must process it.  The data pointer points to a structure of type
        // IPOD_COMMAND, which contains information about the received command
        // and a pointer to its data.  Upon return from this event, the command
        // will be destroyed.  If the application layer needs to retain any
        // information from the command, it must copy the data.
    MFI_EVENT_COMMAND_AVAILABLE,

        // The application layer uses the function MFI_SendCommand to send a
        // command to the Apple device.  This event is thrown after the driver has
        // successfully sent the command to the Apple device.  Some Apple device commands do not
        // generate a response, so this event can be used to advance an application
        // layer state machine.  It can be ignored if it is not needed.
    MFI_EVENT_COMMAND_SENT,

    //----------------------------------------------------------------------
    // Section: Digital Audio Events

        // If the Digital Audio lingo is supported, this event will be sent when the
        // library has determined whether or not Extended Interface mode is required to
        // utilize digital audio.  If so, the application is responsible for placing the
        // Apple device into Extended Interface mode.  To ensure that ATS timing requirements are met,
        // processing here should be brief.  NOTE: When in Extended Interface mode, it is recommended not
        // to use Simple Remote commands, as they may not function identically across different iPods.
    MFI_EVENT_IPOD_READY_AUDIO_HOST,

        // This error is issued if either the Digital Audio lingo version
        // is v1.00 (which is not supported), or if the version is v1.01
        // and the application does not support the Extended Interface
        // lingo.  Neither the data nor the size parameter is used by this
        // event.
    MFI_EVENT_AUDIO_SUPPORT_ERROR,

        // This error is issued if the Apple device returns an error when the
        // accessory sends the list of supported sample rates.  Neither the
        // data nor the size parameter is used by this event.
    MFI_EVENT_AUDIO_RATE_ERROR,

        // The driver has requested digital audio data from the Apple device.  The
        // application layer should prepare to receive it.  Neither the
        // data nor the size parameter is used by this event.
    MFI_EVENT_AUDIO_RECEIVING_DATA,

        // The driver has stopped requesting digital audio data from the
        // Apple device.  This can happen either by an application layer request
        // or when the Apple device indicates a sampling frequency change.  Neither
        // the data nor the size parameter is used by this event.
    MFI_EVENT_AUDIO_STOPPING_DATA,

        // The Apple device has requested a sample rate change.  The application
        // must reconfigure its audio output to the new sample rate.  The
        // data parameter points to the 4-byte sample rate value; the size
        // parameter is 4 (the number of bytes in the sample rate value).
    MFI_EVENT_AUDIO_SET_SAMPLE_RATE,

        // The Apple device has received some audio data.  This event will be sent to the
        // MFI_HandleiPodDataEvents event handler.  Processing of this event is
        // extremely time critical, since it will be called from the USB interrupt
        // handler, and new data will be received every 1 ms.
    MFI_EVENT_AUDIO_STREAM_RECEIVED,

    //----------------------------------------------------------------------
    // Section: UART Only Events

        // The Apple device sent more data bytes than the accessory could buffer in the
        // raw UART buffer.  If this event occurs, the MFi Library will no longer
        // be able to receive any commands from the Apple device.  This event indicates
        // a fatal design problem at the application layer.  In general, MFI_Tasks
        // is not being called quickly enough such that commands from the
        // Apple device can be received and processed at the same rate that they
        // are being sent.  If using a custom app, and if the accessory will require
        // a long time to process commands from the app, then the custom
        // protocol should be designed with a flow control or command-response
        // mechanism.  If not using a custom app, then the accessory must simply be
        // designed such that it can keep up with the rate of the commands sent from
        // the Apple device.
    MFI_EVENT_RECEIVE_BUFFER_OVERRUN,

        // The Apple device sent more data bytes than the maximum number of data
        // bytes that can be received for a single command.  If buffer declarations
        // and command payload specifications are set as shown in the demo
        // applications, the Apple device will never send more bytes in a single
        // command than the accessory can receive, and this event will never occur.
    MFI_EVENT_RECEIVE_BUFFER_OVERRUN_COMMAND

} MFI_EVENT;


//******************************************************************************
// Section: Apple Device Lingo Support Flags
//******************************************************************************

#define IPOD_LINGO_FLAG_GENERAL                 0x00000001ul    // General lingo support flag
#define IPOD_LINGO_FLAG_MICROPHONE              0x00000002ul    // Microphone lingo support flag
#define IPOD_LINGO_FLAG_SIMPLE_REMOTE           0x00000004ul    // Simple Remote lingo support flag
#define IPOD_LINGO_FLAG_DISPLAY_REMOTE          0x00000008ul    // Display Remote lingo support flag
#define IPOD_LINGO_FLAG_EXTENDED_INTERFACE      0x00000010ul    // Extended Interface lingo support flag
#define IPOD_LINGO_FLAG_ACCESSORY_POWER         0x00000020ul    // Accessory Power lingo support flag
#define IPOD_LINGO_FLAG_USB_HOST_MODE           0x00000040ul    // USB Host Mode lingo support flag
#define IPOD_LINGO_FLAG_RF_TUNER                0x00000080ul    // RF Tuner lingo support flag
#define IPOD_LINGO_FLAG_ACCESSORY_EQUALIZER     0x00000100ul    // Accessory Equalizer lingo support flag
#define IPOD_LINGO_FLAG_SPORTS                  0x00000200ul    // Sports lingo support flag
#define IPOD_LINGO_FLAG_DIGITAL_AUDIO           0x00000400ul    // Digital Audio lingo support flag
#define IPOD_LINGO_FLAG_STORAGE                 0x00001000ul    // Storage lingo support flag
#define IPOD_LINGO_FLAG_IPOD_OUT                0x00002000ul    // Apple device Out lingo support flag
#define IPOD_LINGO_FLAG_LOCATION                0x00004000ul    // Location lingo support flag


//******************************************************************************
// Section: Apple Device Lingo IDs
//******************************************************************************

#define IPOD_LINGO_GENERAL                      0x00    // General lingo identifier
#define IPOD_LINGO_MICROPHONE                   0x01    // Microphone lingo identifier
#define IPOD_LINGO_SIMPLE_REMOTE                0x02    // Simple Remote lingo identifier
#define IPOD_LINGO_DISPLAY_REMOTE               0x03    // Display Remote lingo identifier
#define IPOD_LINGO_EXTENDED_INTERFACE           0x04    // Extended Interface lingo identifier
#define IPOD_LINGO_ACCESSORY_POWER              0x05    // Accessory Power lingo identifier
#define IPOD_LINGO_USB_HOST_MODE                0x06    // USB Host Mode lingo identifier
#define IPOD_LINGO_RF_TUNER                     0x07    // RF Tuner lingo identifier
#define IPOD_LINGO_ACCESSORY_EQUALIZER          0x08    // Accessory Equalizer lingo identifier
#define IPOD_LINGO_SPORTS                       0x09    // Sports lingo identifier
#define IPOD_LINGO_DIGITAL_AUDIO                0x0A    // Digital Audio lingo identifier
#define IPOD_LINGO_STORAGE                      0x0C    // Storage lingo identifier
#define IPOD_LINGO_IPOD_OUT                     0x0D    // iPod Out lingo identifier
#define IPOD_LINGO_LOCATION                     0x0E    // Location lingo identifier


//******************************************************************************
// Section: General Lingo Commands
//******************************************************************************

#define IPOD_RequestIdentify                        0x00    // iAP command.  See the Apple Specification for complete information.
#define IPOD_iPodAck                                0x02    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestExtendedInterfaceMode           0x03    // iAP command.  See the Apple Specification for complete information.
#define IPOD_ReturnExtendedInterfaceMode            0x04    // iAP command.  See the Apple Specification for complete information.
#define IPOD_EnterRemoteUIMode                      0x05    // iAP command.  See the Apple Specification for complete information.  Deprecated in R44, but needed for older devices.
#define IPOD_ExitExtendedInterfaceMode              0x06    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestiPodName                        0x07    // iAP command.  See the Apple Specification for complete information.
#define IPOD_ReturniPodName                         0x08    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestiPodSoftwareVersion             0x09    // iAP command.  See the Apple Specification for complete information.
#define IPOD_ReturniPodSoftwareVersion              0x0A    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestiPodSerialNum                   0x0B    // iAP command.  See the Apple Specification for complete information.
#define IPOD_ReturniPodSerialNum                    0x0C    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestLingoProtocolVersion            0x0F    // iAP command.  See the Apple Specification for complete information.
#define IPOD_ReturnLingoProtocolVersion             0x10    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestTransportMaxPayloadSize         0x11    // iAP command.  See the Apple Specification for complete information.
#define IPOD_ReturnTransportMaxPayloadSize          0x12    // iAP command.  See the Apple Specification for complete information.
#define IPOD_IdentifyDeviceLingoes                  0x13    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetAccessoryAuthenticationInfo         0x14    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetAccessoryAuthenticationInfo         0x15    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AckAccessoryAuthenticationInfo         0x16    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetAccessoryAuthenticationSignature    0x17    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetAccessoryAuthenticationSignature    0x18    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AckAccessoryAuthenticationStatus       0x19    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetiPodAuthenticationInfo              0x1A    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetiPodAuthenticationInfo              0x1B    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AckiPodAuthenticationInfo              0x1C    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetiPodAuthenticationSignature         0x1D    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetiPodAuthenticationSignature         0x1E    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AckiPodAuthenticationStatus            0x1F    // iAP command.  See the Apple Specification for complete information.
#define IPOD_NotifyiPodStateChange                  0x23    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetiPodOptions                         0x24    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetiPodOptions                         0x25    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetAccessoryInfo                       0x27    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetAccessoryInfo                       0x28    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetiPodPreferences                     0x29    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetiPodPreferences                     0x2A    // iAP command.  See the Apple Specification for complete information.
#define IPOD_SetiPodPreferences                     0x2B    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetUIMode                              0x35    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetUIMode                              0x36    // iAP command.  See the Apple Specification for complete information.
#define IPOD_SetUIMode                              0x37    // iAP command.  See the Apple Specification for complete information.
#define IPOD_StartIDPS                              0x38    // iAP command.  See the Apple Specification for complete information.
#define IPOD_SetFIDTokenValues                      0x39    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AckFIDTokenValues                      0x3A    // iAP command.  See the Apple Specification for complete information.
#define IPOD_EndIDPS                                0x3B    // iAP command.  See the Apple Specification for complete information.
#define IPOD_IDPSStatus                             0x3C    // iAP command.  See the Apple Specification for complete information.
#define IPOD_OpenDataSessionForProtocol             0x3F    // iAP command.  See the Apple Specification for complete information.
#define IPOD_CloseDataSession                       0x40    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AccessoryACK                           0x41    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AccessoryDataTransfer                  0x42    // iAP command.  See the Apple Specification for complete information.
#define IPOD_iPodDataTransfer                       0x43    // iAP command.  See the Apple Specification for complete information.
#define IPOD_SetAccessoryStatusNotification         0x46    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetAccessoryStatusNotification         0x47    // iAP command.  See the Apple Specification for complete information.
#define IPOD_AccessoryStatusNotification            0x48    // iAP command.  See the Apple Specification for complete information.
#define IPOD_SetEventNotification                   0x49    // iAP command.  See the Apple Specification for complete information.
#define IPOD_iPodNotification                       0x4A    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetiPodOptionsForLingo                 0x4B    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetiPodOptionsForLingo                 0x4C    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetEventNotification                   0x4D    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetEventNotification                   0x4E    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetSupportedEventNotification          0x4F    // iAP command.  See the Apple Specification for complete information.
#define IPOD_CancelCommand                          0x50    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetSupportedEventNotification          0x51    // iAP command.  See the Apple Specification for complete information.
#define IPOD_SetAvailableCurrent                    0x54    // iAP command.  See the Apple Specification for complete information.
#define IPOD_SetInternalBatteryChargingState        0x56    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestApplicationLaunch               0x64    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetNowPlayingApplicationBundleName     0x65    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetNowPlayingApplicationBundleName     0x66    // iAP command.  See the Apple Specification for complete information.
#define IPOD_GetLocalizationInfo                    0x67    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RetLocalizationInfo                    0x68    // iAP command.  See the Apple Specification for complete information.
#define IPOD_RequestWiFiConnectionInfo              0x69    // iAP command.  See the Apple Specification for complete information.
#define IPOD_WiFiConnectionInfo                     0x6A    // iAP command.  See the Apple Specification for complete information.

//------------------------------------------------------------------------------
// Deprecated or Renamed Commands - DO NOT UNCOMMENT (for reference only)

// Renamed in R44 #define IPOD_ACK                                    0x02
// Renamed in R44 #define IPOD_RequestRemoteUIMode                    0x03
// Renamed in R44 #define IPOD_ReturnRemoteUIMode                     0x04
// Renamed in R44 #define IPOD_ExitRemoteUIMode                       0x06
// Renamed in R44 #define IPOD_GetDevAuthenticationInfo               0x14
// Renamed in R44 #define IPOD_RetDevAuthenticationInfo               0x15
// Renamed in R44 #define IPOD_AckDevAuthenticationInfo               0x16
// Renamed in R44 #define IPOD_GetDevAuthenticationSignature          0x17
// Renamed in R44 #define IPOD_RetDevAuthenticationSignature          0x18
// Renamed in R44 #define IPOD_AckDevAuthenticationStatus             0x19
// Renamed in R44 #define IPOD_RetFIDTokenValueACKs                   0x3A
// Renamed in R44 #define IPOD_DevACK                                 0x41
// Renamed in R44 #define IPOD_DevDataTransfer                        0x42
// Renamed in R44 #define IPOD_SetAccStatusNotification               0x46
// Renamed in R44 #define IPOD_RetAccStatusNotification               0x47
// Renamed in R44 #define IPOD_GetNowPlayingFocusApp                  0x65
// Renamed in R44 #define IPOD_RetNowPlayingFocusApp                  0x66

// Deprecated in R43 #define IPOD_RequestiPodModelNum                    0x0D
// Deprecated in R43 #define IPOD_ReturniPodModelNum                     0x0E
// Renamed in R43 #define IPOD_RequestTransportMaxPacketSize          0x11
// Renamed in R43 #define IPOD_ReturnTransportMaxPacketSize           0x12

// Removed in R40 #define IPOD_GetPreferredCurrentSource          0x52
// Removed in R40 #define IPOD_RetPreferredCurrentSource          0x53
// Removed in R40 #define IPOD_GetChargingInfo                    0x58
// Removed in R40 #define IPOD_RetChargingInfo                    0x59

// Deprecated in R34 #define IPOD_Identify                               0x01

//------------------------------------------------------------------------------
// ACK Constants

#define IPOD_ACK_SUCCESS                                0x00    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_UNKNOWN_DATABASE_CATEGORY              0x01    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_COMMAND_FAILED                         0x02    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_OUT_OF_RESOURCES                       0x03    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_BAD_PARAMETER                          0x04    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_UNKNOWN_ID                             0x05    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_COMMAND_PENDING                        0x06    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_NOT_AUTHENTICATED                      0x07    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_BAD_AUTHENTICATION_VERSION             0x08    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_ACCESSORY_POWER_MODE_REQUEST_FAILED    0x09    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_CERTIFICATE_INVALID                    0x0A    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_CERTIFICATE_PERMISSIONS_INVALID        0x0B    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_FILE_IS_IN_USE                         0x0C    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_INVALID_FILE_HANDLE                    0x0D    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_DIRECTORY_NOT_EMPTY                    0x0E    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_OPERATION_TIMED_OUT                    0X0F    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_COMMAND_UNAVAILABLE                    0x10    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_INVALID_ACCESSORY_RESISTOR             0x11    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_ACCESSORY_NOT_GROUNDED                 0x12    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_SUCCESS_MULTISECTION_DATA              0x13    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_MAXIMUM_ACCESSORY_CONNECTIONS          0x15    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_SessionWriteFailure                    0x17    // iAP ACK return value.  See the Apple Specification for complete information.
#define IPOD_ACK_IPOD_OUT_MODE_ENTRY_ERROR              0x18    // iAP ACK return value.  See the Apple Specification for complete information.

//------------------------------------------------------------------------------
// SetiPodPreferences Constants

    // For use with the SetiPodPreferences command.  This value tells the Apple device
    // to restore the original settings when the accessory is disconnected.
#define IPOD_PREFERENCES_RESTORE                    0x01
    // For use with the SetiPodPreferences command.  This value tells the Apple device
    // not to restore the original settings when the accessory is disconnected.
#define IPOD_PREFERENCES_RETAIN                     0x00


    // For use with the iPodPreferences.videoOutSetting member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to enable or disable video output, or to as the
    // user.
#define IPOD_VIDEO_CLASS_VIDEO_OUT                  0x00
#define IPOD_VIDEO_SETTING_VIDEO_OFF                0x00    // Disables video output.
#define IPOD_VIDEO_SETTING_VIDEO_ON                 0x01    // Enables video output.
// Deprecated in R41 #define IPOD_VIDEO_SETTING_VIDEO_ASK                0x02    // Asks user for video output status

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to set the screen configuration.  It is not the
    // same as setting the aspect ratio.
#define IPOD_VIDEO_CLASS_SCREEN_CONFIGURATION       0x01
#define IPOD_VIDEO_SETTING_SCREEN_FILL              0x00    // Fill the entire screen.  Image may be cut off.
#define IPOD_VIDEO_SETTING_SCREEN_FIT_TO_EDGE       0x01    // Expand to the screen edge without losing any image information.

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to set the video signal format.
#define IPOD_VIDEO_CLASS_VIDEO_SIGNAL               0x02
#define IPOD_VIDEO_SETTING_SIGNAL_NTSC              0x00    // NTSC video format and timing.
#define IPOD_VIDEO_SETTING_SIGNAL_PAL               0x01    // PAL video format and timing.

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to set the line-out usage.
#define IPOD_VIDEO_CLASS_LINE_OUT                   0x03
#define IPOD_VIDEO_SETTING_LINE_OUT_OFF             0x00    // Line-out disabled.
#define IPOD_VIDEO_SETTING_LINE_OUT_ON              0x01    // Line-out enabled.

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to set the video out connection type.
#define IPOD_VIDEO_CLASS_VIDEO_TYPE                 0x08
#define IPOD_VIDEO_SETTING_VIDEO_TYPE_NONE          0x00    // No video.
#define IPOD_VIDEO_SETTING_VIDEO_TYPE_COMPOSITE     0x01    // Composite video (interlaced video only), default.
#define IPOD_VIDEO_SETTING_VIDEO_TYPE_S_VIDEO       0x02    // S-video (interlaced video only).
#define IPOD_VIDEO_SETTING_VIDEO_TYPE_COMPONENT     0x03    // Component Y/Pr/Pb video (interlaced or progressive, depending on the Apple device).

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to enable or disable closed captioning.
#define IPOD_VIDEO_CLASS_CLOSED_CAPTIONING          0x09
#define IPOD_VIDEO_SETTING_CLOSED_CAPTIONING_OFF    0x00    // No closed captioning.
#define IPOD_VIDEO_SETTING_CLOSED_CAPTIONING_ON     0x01    // Closed captioning enabled. Cannot enable subtitles.

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to set the aspect ratio.
#define IPOD_VIDEO_CLASS_ASPECT_RATIO               0x0A
#define IPOD_VIDEO_SETTING_ASPECT_RATIO_4_3         0x00    // Video aspect ration of 4:3.
#define IPOD_VIDEO_SETTING_ASPECT_RATIO_16_9        0x01    // Video aspect ration of 16:9.

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to enable or disable subtitles.
#define IPOD_VIDEO_CLASS_SUBTITLES                  0x0C
#define IPOD_VIDEO_SETTING_SUBTITLES_OFF            0x00    // No subtitles.
#define IPOD_VIDEO_SETTING_SUBTITLES_ON             0x01    // Enable subtitles.  Cannot enable closed captioning.

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to enable or disable the alternate audio channel.
#define IPOD_VIDEO_CLASS_ALTERNATE_AUDIO            0x0D
#define IPOD_VIDEO_SETTING_ALTERNATE_AUDIO_OFF      0x00    // Turn off alternate audio channel.
#define IPOD_VIDEO_SETTING_ALTERNATE_AUDIO_ON       0x01    // Turn on alternate audio channel.

    // For use with the iPodPreferences.screenConfiguration member of the
    // IPOD_APPLICATION_INFORMATION struture and the SetiPodPreferences command.
    // This class ID is used to enable or disable video pausing on USB power removal.
#define IPOD_VIDEO_CLASS_PAUSE                      0x0F
#define IPOD_VIDEO_SETTING_PAUSE_OFF                0x00    // Turn off pause on power removal.
#define IPOD_VIDEO_SETTING_PAUSE_ON                 0x01    // Turn on pause on power removal.

    // For use with the SetiPodPreferences command.  This class ID is used to enable
    // or disable VoiceOver.  It is represented in the AccessoryCapsToken by the voiceOver bit in
    // the accCapsBitmask member of the IPOD_APPLICATION_INFORMATION structure.
#define IPOD_VIDEO_CLASS_VOICEOVER                  0x14
// Renamed in R44 #define IPOD_VIDEO_CLASS_ACCESSIBILITY              0x14
#define IPOD_VIDEO_SETTING_VOICEOVER_OFF            0x00    // Disable VoiceOver.
#define IPOD_VIDEO_SETTING_VOICEOVER_ON             0x01    // Enable VoiceOver.

    // For use with the SetiPodPreferences command.  This class ID is used to enable
    // or disable AssistiveTouch.  It is represented in the AccessoryCapsToken by the AssistiveTouch bit in
    // the accCapsBitmask member of the IPOD_APPLICATION_INFORMATION structure.
#define IPOD_VIDEO_CLASS_ASSISTIVETOUCH             0x16
#define IPOD_VIDEO_SETTING_ASSISTIVETOUCH_OFF       0x00    // Disable AssistiveTouch.
#define IPOD_VIDEO_SETTING_ASSISTIVETOUCH_ON        0x01    // Enable AssistiveTouch.


//------------------------------------------------------------------------------
// AckFIDTokenValues ACKStatus Values and Actions

#define IPOD_RetFIDTokenValueAcks_SUCCESS           0x00    // Token-value field accepted.
#define IPOD_RetFIDTokenValueAcks_REQUIRED_FAILED   0x01    // Required token-value field failed.
#define IPOD_RetFIDTokenValueAcks_OPTIONAL_FAILED   0x02    // Optional token-value field recognized but failed.
#define IPOD_RetFIDTokenValueAcks_NOT_SUPPORTED     0x03    // Token not supported.
#define IPOD_RetFIDTokenValueAcks_LINGOES_BUSY      0x04    // Lingoes busy.
#define IPOD_RetFIDTokenValueAcks_MAX_CONNECTIONS   0x05    // Maximum connections reached.

#define IPOD_TOKEN_PROBLEM_RETRY                    0x00    // Send tokens again with new information.
#define IPOD_TOKEN_PROBLEM_IGNORE                   0x01    // Ignore the problem and continue the IDPS process.
#define IPOD_TOKEN_PROBLEM_FAIL                     0x02    // Fail IDPS and do not try to communicate with the Apple device.
// NOT YET SUPPORTED #define IPOD_TOKEN_PROBLEM_ABANDON                  0x03    // Abandon IDPS and try IDL.
#define IPOD_TOKEN_PROBLEM_RESET                    0x04    // Change in token (e.g. IdentifyToken) requiring IDPS restart.


//------------------------------------------------------------------------------
// FID Token Value Constants for MFI_EVENT_TOKEN_PROBLEM event

#define IPOD_FID_IdentifyToken                          0x0000  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_AccessoryCapsToken                     0x0001  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_AccessoryInfoToken                     0x0002  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_iPodPreferenceToken                    0x0003  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_EAProtocolToken                        0x0004  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_BundleSeedIDPrefToken                  0x0005  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_EAProtocolMetadataToken                0x0008  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_AccessoryDigitalAudioSampleRatesToken  0x000E // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
#define IPOD_FID_AccessoryDigitalAudioVideoDelayToken   0x000F // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.

// Renamed in R44 #define IPOD_FID_AccCapsToken                           0x0001  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
// Renamed in R44 #define IPOD_FID_AccInfoToken                           0x0002  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
// Deprecated in R44 #define IPOD_FID_ScreenInfoToken                        0x0007  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.
// Deprecated in R42 #define IPOD_FID_MicrophoneCapsToken                    0x0100  // Token constant for the MFI_EVENT_TOKEN_PROBLEM event.


//------------------------------------------------------------------------------
// EndIDPS accEndIDPSStatus Values

#define IPOD_EndIDPS_SUCCESS                        0x00    // EndIDPS accEndIDPSStatus constant
#define IPOD_EndIDPS_RESET                          0x01    // EndIDPS accEndIDPSStatus constant
#define IPOD_EndIDPS_ABANDON                        0x02    // EndIDPS accEndIDPSStatus constant
#define IPOD_EndIDPS_CHANGE_TRANSPORT               0x03    // EndIDPS accEndIDPSStatus constant


//------------------------------------------------------------------------------
// User Interface Mode Values

#define IPOD_UI_MODE_STANDARD                       0x00    // UIMode constant for SetUIMode and RetUIMode
#define IPOD_UI_MODE_EXTENDED_INTERFACE             0x01    // UIMode constant for SetUIMode and RetUIMode
#define IPOD_UI_MODE_IPOD_OUT_FULLSCREEN            0x02    // UIMode constant for SetUIMode and RetUIMode
#define IPOD_UI_MODE_IPOD_OUT_ACTION_SAFE           0x03    // UIMode constant for SetUIMode and RetUIMode


//------------------------------------------------------------------------------
// iPodNotification Values

#define IPOD_iPodNotification_FlowControl                       0x02    // iPodNotification constant
#define IPOD_iPodNotification_RadioTagging                      0x03    // iPodNotification constant
#define IPOD_iPodNotification_CameraNotifications               0x04    // iPodNotification constant
#define IPOD_iPodNotification_ChargingInfo                      0x05    // iPodNotification constant
#define IPOD_iPodNotification_DatabaseChanged                   0x09    // iPodNotification constant
#define IPOD_iPodNotification_NowPlayingApplicationBundleName   0x0A    // iPodNotification constant
// Renamed in R44 #define IPOD_iPodNotification_NowPlayingAppFocusChange  0x0A    // iPodNotification constant
#define IPOD_iPodNotification_SessionSpaceAvailable             0x0B    // iPodNotification constant
// Deprecated in R44 #define IPOD_iPodNotification_DatabaseAvailable                 0x0C    // iPodNotification constant
#define IPOD_iPodNotification_CommandComplete                   0x0D    // iPodNotification constant
#define IPOD_iPodNotification_iPodOutMode                       0x0F    // iPodNotification constant
#define IPOD_iPodNotification_BluetoothConnection               0x11    // iPodNotification constant
#define IPOD_iPodNotification_NowPlayingApplicationDisplayName  0x13    // iPodNotification constant
#define IPOD_iPodNotification_AssistiveTouch                    0x14    // iPodNotification constant

//------------------------------------------------------------------------------
// WiFiConnectionInfo Values

#define IPOD_WiFiConnectionInfo_SUCCESS                         0x00
#define IPOD_WiFiConnectionInfo_UNAVAILABLE                     0x01
#define IPOD_WiFiConnectionInfo_DECLINED                        0x02
#define IPOD_WiFiConnectionInfo_FAILED                          0x03

#define IPOD_WiFiConnectionInfo_UNSECURED                       0x00
#define IPOD_WiFiConnectionInfo_WEP                             0x01
#define IPOD_WiFiConnectionInfo_WPA                             0x02
#define IPOD_WiFiConnectionInfo_WPA2                            0x03
#define IPOD_WiFiConnectionInfo_WPA_AND_WPA2                    0x04

//******************************************************************************
// Section: Extended Interface Lingo Commands
//******************************************************************************

#define IPOD_EIL_iPodAck                                    0x0001  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetCurrentPlayingTrackChapterInfo          0x0002  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnCurrentPlayingTrackChapterInfo       0x0003  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SetCurrentPlayingTrackChapter              0x0004  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetCurrentPlayingTrackChapterPlayStatus    0x0005  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnCurrentPlayingTrackChapterPlayStatus 0x0006  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetCurrentPlayingTrackChapterName          0x0007  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnCurrentPlayingTrackChapterName       0x0008  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetAudiobookSpeed                          0x0009  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnAudiobookSpeed                       0x000A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SetAudiobookSpeed                          0x000B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetIndexedPlayingTrackInfo                 0x000C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnIndexedPlayingTrackInfo              0x000D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetArtworkFormats                          0x000E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetArtworkFormats                          0x000F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetTrackArtworkData                        0x0010  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetTrackArtworkData                        0x0011  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ResetDBSelection                           0x0016  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SelectDBRecord                             0x0017  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetNumberCategorizedDBRecords              0x0018  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnNumberCategorizedDBRecords           0x0019  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetrieveCategorizedDatabaseRecords         0x001A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnCategorizedDatabaseRecord            0x001B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetPlayStatus                              0x001C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnPlayStatus                           0x001D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetCurrentPlayingTrackIndex                0x001E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnCurrentPlayingTrackIndex             0x001F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetIndexedPlayingTrackTitle                0x0020  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnIndexedPlayingTrackTitle             0x0021  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetIndexedPlayingTrackArtistName           0x0022  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnIndexedPlayingTrackArtistName        0x0023  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetIndexedPlayingTrackAlbumName            0x0024  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnIndexedPlayingTrackAlbumName         0x0025  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SetPlayStatusChangeNotification            0x0026  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_PlayStatusChangeNotification               0x0027  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_PlayControl                                0x0029  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetTrackArtworkTimes                       0x002A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetTrackArtworkTimes                       0x002B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetShuffle                                 0x002C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnShuffle                              0x002D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SetShuffle                                 0x002E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetRepeat                                  0x002F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnRepeat                               0x0030  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SetRepeat                                  0x0031  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SetDisplayImage                            0x0032  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetMonoDisplayImageLimits                  0x0033  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnMonoDisplayImageLimits               0x0034  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetNumPlayingTracks                        0x0035  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnNumPlayingTracks                     0x0036  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_SetCurrentPlayingTrack                     0x0037  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetColorDisplayImageLimits                 0x0039  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ReturnColorDisplayImageLimits              0x003A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_ResetDBSelectionHierarchy                  0x003B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetDBiTunesInfo                            0x003C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetDBiTunesInfo                            0x003D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetUIDTrackInfo                            0x003E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetUIDTrackInfo                            0x003F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetDBTrackInfo                             0x0040  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetDBTrackInfo                             0x0041  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_GetPBTrackInfo                             0x0042  // Extended Interface Lingo command.  See the Apple Specification for complete information.
#define IPOD_EIL_RetPBTrackInfo                             0x0043  // Extended Interface Lingo command.  See the Apple Specification for complete information.

// Renamed in R44 #define IPOD_iPodAck                                    0x0001  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetCurrentPlayingTrackChapterInfo          0x0002  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnCurrentPlayingTrackChapterInfo       0x0003  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetCurrentPlayingTrackChapter              0x0004  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetCurrentPlayingTrackChapterPlayStatus    0x0005  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnCurrentPlayingTrackChapterPlayStatus 0x0006  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetCurrentPlayingTrackChapterName          0x0007  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnCurrentPlayingTrackChapterName       0x0008  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetAudiobookSpeed                          0x0009  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnAudiobookSpeed                       0x000A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetAudiobookSpeed                          0x000B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetIndexedPlayingTrackInfo                 0x000C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnIndexedPlayingTrackInfo              0x000D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetArtworkFormats                          0x000E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetArtworkFormats                          0x000F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetTrackArtworkData                        0x0010  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetTrackArtworkData                        0x0011  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Deprecated in R44 #define IPOD_RequestProtocolVersion                     0x0012  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Deprecated in R44 #define IPOD_ReturnProtocolVersion                      0x0013  // Deprecated Extended Interface Lingo command.  See the Apple Specification for complete information.
// Deprecated #define IPOD_RequestiPodName_EI                         0x0014  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Deprecated #define IPOD_ReturniPodName_EI                          0x0015  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ResetDBSelection                           0x0016  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SelectDBRecord                             0x0017  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetNumberCategorizedDBRecords              0x0018  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnNumberCategorizedDBRecords           0x0019  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetrieveCategorizedDatabaseRecords         0x001A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnCategorizedDatabaseRecord            0x001B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetPlayStatus                              0x001C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnPlayStatus                           0x001D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetCurrentPlayingTrackIndex                0x001E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnCurrentPlayingTrackIndex             0x001F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetIndexedPlayingTrackTitle                0x0020  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnIndexedPlayingTrackTitle             0x0021  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetIndexedPlayingTrackArtistName           0x0022  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnIndexedPlayingTrackArtistName        0x0023  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetIndexedPlayingTrackAlbumName            0x0024  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnIndexedPlayingTrackAlbumName         0x0025  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetPlayStatusChangeNotification            0x0026  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_PlayStatusChangeNotification               0x0027  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Deprecated in R44 #define IPOD_PlayCurrentSelection                       0x0028  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_PlayControl                                0x0029  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetTrackArtworkTimes                       0x002A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetTrackArtworkTimes                       0x002B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetShuffle                                 0x002C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnShuffle                              0x002D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetShuffle                                 0x002E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetRepeat                                  0x002F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnRepeat                               0x0030  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetRepeat                                  0x0031  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetDisplayImage                            0x0032  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetMonoDisplayImageLimits                  0x0033  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnMonoDisplayImageLimits               0x0034  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetNumPlayingTracks                        0x0035  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnNumPlayingTracks                     0x0036  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetCurrentPlayingTrack                     0x0037  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Deprecated in R44 #define IPOD_SelectSortDBRecord                         0x0038  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetColorDisplayImageLimits                 0x0039  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ReturnColorDisplayImageLimits              0x003A  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ResetDBSelectionHierarchy                  0x003B  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetDBiTunesInfo                            0x003C  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetDBiTunesInfo                            0x003D  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetUIDTrackInfo                            0x003E  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetUIDTrackInfo                            0x003F  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetDBTrackInfo                             0x0040  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetDBTrackInfo                             0x0041  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetPBTrackInfo                             0x0042  // Extended Interface Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetPBTrackInfo                             0x0043  // Extended Interface Lingo command.  See the Apple Specification for complete information.


//------------------------------------------------------------------------------
// Database Category Type Constants

#define IPOD_DATABASE_CATEGORY_Playlist                 0x01    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Artist                   0x02    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Album                    0x03    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Genre                    0x04    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Track                    0x05    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Composer                 0x06    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Audiobook                0x07    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Podcast                  0x08    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DATABASE_CATEGORY_Nested_Playlist          0x09    // Extended Interface Lingo constant.  See the Apple Specification for complete information.


//------------------------------------------------------------------------------
// Display Pixel Format Constants

#define IPOD_DISPLAY_PIXEL_FORMAT_MONOCHROME            0x01    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DISPLAY_PIXEL_FORMAT_RGB565_LITTLE_ENDIAN  0x02    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_DISPLAY_PIXEL_FORMAT_RGB565_BIG_ENDIAN     0x03    // Extended Interface Lingo constant.  See the Apple Specification for complete information.


//------------------------------------------------------------------------------
// PlayControl Constants

#define IPOD_PlayControl_COMMAND_PLAY_PAUSE         0x01    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_NEXT_TRACK         0x03    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_PREVIOUS_TRACK     0x04    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_START_FFORWARD     0x05    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_START_REWIND       0x06    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_END_FF_REW         0x07    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_NEXT               0x08    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_PREVIOUS           0x09    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_PLAY               0x0A    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_PAUSE              0x0B    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_NEXT_CHAPTER       0x0C    // Extended Interface Lingo constant.  See the Apple Specification for complete information.
#define IPOD_PlayControl_COMMAND_PREVIOUS_CHAPTER   0x0D    // Extended Interface Lingo constant.  See the Apple Specification for complete information.


//******************************************************************************
// Section: Simple Remote Lingo Commands
//******************************************************************************

#define IPOD_SRL_ContextButtonStatus                0x00    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_iPodAck                            0x01    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_VideoButtonStatus                  0x03    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_AudioButtonStatus                  0x04    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_iPodOutButtonStatus                0x0B    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_RotationInputStatus                0x0C    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_RadioButtonStatus                  0x0D    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_CameraButtonStatus                 0x0E    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_RegisterDescriptor                 0x0F    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_iPodHIDReport                      0x10    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_AccessoryHIDReport                 0x11    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_UnregisterDescriptor               0x12    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_VoiceOverEvent                     0x13    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_GetVoiceOverParameter              0x14    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_RetVoiceOverParameter              0x15    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_SetVoiceOverParameter              0x16    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_GetCurrentItemVoiceOverProperty    0x17    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_RetCurrentItemVoiceOverProperty    0x18    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_SetVoiceOverContext                0x19    // Simple Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_SRL_AccessoryACK                       0x81    // Simple Remote Lingo command.  See the Apple Specification for complete information.

// Renamed in R44 #define IPOD_ContextButtonStatus                    0x00    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_ACK_SIMPLE_REMOTE                      0x01    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Deprecated in R44 #define IPOD_ImageButtonStatus                      0x02    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_VideoButtonStatus                      0x03    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_AudioButtonStatus                      0x04    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_iPodOutButtonStatus                    0x0B    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RotationInputStatus                    0x0C    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RadioButtonStatus                      0x0D    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_CameraButtonStatus                     0x0E    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RegisterDescriptor                     0x0F    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_iPodHIDReport                          0x10    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SendHIDReportToiPod                    0x10    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_AccessoryHIDReport                     0x11    // Simple Remote Lingo command.  See the Apple Specification for complete information.
//#define IPOD_SendHIDReportToAcc                     0x11    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_UnregisterDescriptor                   0x12    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_AccessibilityEvent                     0x13    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetAccessibilityParameter              0x14    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetAccessibilityParameter              0x15    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetAccessibilityParameter              0x16    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetCurrentItemProperty                 0x17    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetCurrentItemProperty                 0x18    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetContext                             0x19    // Simple Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_DevACK_SIMPLE_REMOTE                   0x81    // Simple Remote Lingo command.  See the Apple Specification for complete information.


//******************************************************************************
// Section: Display Remote Lingo Commands
//******************************************************************************

#define IPOD_DRL_iPodAck                            0x00    // Display Remote Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_DRL_ACK                                0x00    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetCurrentEQProfileIndex           0x01    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetCurrentEQProfileIndex           0x02    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_SetCurrentEQProfileIndex           0x03    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetNumEQProfiles                   0x04    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetNumEQProfiles                   0x05    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetIndexedEQProfileName            0x06    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetIndexedEQProfileName            0x07    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_SetRemoteEventNotification         0x08    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RemoteEventNotification            0x09    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetRemoteEventStatus               0x0A    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetRemoteEventStatus               0x0B    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetiPodStateInfo                   0x0C    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetiPodStateInfo                   0x0D    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_SetiPodStateInfo                   0x0E    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetPlayStatus                      0x0F    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetPlayStatus                      0x10    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_SetCurrentPlayingTrack             0x11    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetIndexedPlayingTrackInfo         0x12    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetIndexedPlayingTrackInfo         0x13    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetNumPlayingTracks                0x14    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetNumPlayingTracks                0x15    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetArtworkFormats                  0x16    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetArtworkFormats                  0x17    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetTrackArtworkData                0x18    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetTrackArtworkData                0x19    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetPowerBatteryState               0x1A    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetPowerBatteryState               0x1B    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetSoundCheckState                 0x1C    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetSoundCheckState                 0x1D    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_SetSoundCheckState                 0x1E    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_GetTrackArtworkTimes               0x1F    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_RetTrackArtworkTimes               0x20    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_CreateGeniusPlaylist               0x21    // Display Remote Lingo command.  See the Apple Specification for complete information.
#define IPOD_DRL_IsGeniusAvailableForTrack          0x22    // Display Remote Lingo command.  See the Apple Specification for complete information.


//******************************************************************************
// Section: USB Host Mode Lingo Commands
//******************************************************************************

#define IPOD_USB_HOST_AccessoryAck                  0x00    // USB Host Mode Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_USB_HOST_DevACK                        0x00    // USB Host Mode Lingo command.  See the Apple Specification for complete information.
#define IPOD_USB_HOST_NotifyUSBMode                 0x04    // USB Host Mode Lingo command.  See the Apple Specification for complete information.
#define IPOD_USB_HOST_iPodACK                       0x80    // USB Host Mode Lingo command.  See the Apple Specification for complete information.
#define IPOD_USB_HOST_GetiPodUSBMode                0x81    // USB Host Mode Lingo command.  See the Apple Specification for complete information.
#define IPOD_USB_HOST_RetiPodUSBMode                0x82    // USB Host Mode Lingo command.  See the Apple Specification for complete information.
#define IPOD_USB_HOST_SetiPodUSBMode                0x83    // USB Host Mode Lingo command.  See the Apple Specification for complete information.


//******************************************************************************
// Section: Digital Audio Lingo Commands
//******************************************************************************

#define IPOD_DAL_AccessoryAck                       0x00    // Digital Audio Lingo command.  See the Apple Specification for complete information.
#define IPOD_DAL_iPodAck                            0x01    // Digital Audio Lingo command.  See the Apple Specification for complete information.
#define IPOD_DAL_GetAccessorySampleRateCaps         0x02    // Digital Audio Lingo command.  See the Apple Specification for complete information.
#define IPOD_DAL_RetAccessorySampleRateCaps         0x03    // Digital Audio Lingo command.  See the Apple Specification for complete information.
#define IPOD_DAL_TrackNewAudioAttributes            0x04    // Digital Audio Lingo command.  See the Apple Specification for complete information.
#define IPOD_DAL_SetVideoDelay                      0x05    // Digital Audio Lingo command.  See the Apple Specification for complete information.

// Renamed in R44 #define IPOD_AccAck                                 0x00    // Digital Audio Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetAccSampleRateCaps                   0x02    // Digital Audio Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetAccSampleRateCaps                   0x03    // Digital Audio Lingo command.  See the Apple Specification for complete information.


#ifdef IPOD_USE_USB_HOST
        // This value is the number of streaming digital audio buffers.  Note
        // that this value us built into the library, and must not be changed
        // unless the library is rebuilt.
    #define IPOD_STREAMING_AUDIO_BUFFERS            USB_MAX_ISOCHRONOUS_DATA_BUFFERS
#endif


//******************************************************************************
// Section: iPod Out Lingo Commands
//******************************************************************************

#define IPOD_OUT_iPodACK                            0x00    // iPod Out Lingo command.  See the Apple Specification for complete information.
#define IPOD_OUT_GetiPodOutOptions                  0x01    // iPod Out Lingo command.  See the Apple Specification for complete information.
#define IPOD_OUT_RetiPodOutOptions                  0x02    // iPod Out Lingo command.  See the Apple Specification for complete information.
#define IPOD_OUT_SetiPodOutOptions                  0x03    // iPod Out Lingo command.  See the Apple Specification for complete information.
#define IPOD_OUT_AccessoryStateChangeEvent          0x04    // iPod Out Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_OUT_DevStateChangeEvent                0x04    // iPod Out Lingo command.  See the Apple Specification for complete information.
// Deprecated in R44 #define IPOD_OUT_DevVideoScreenInfo                 0x06    // iPod Out Lingo command.  See the Apple Specification for complete information.


//******************************************************************************
// Section: iPod Out Lingo Constants
//******************************************************************************

#define IPOD_OUT_DISPLAY_DISABLED                   0x00    // iPod Out Lingo constant.  See the Apple Specification for complete information.
#define IPOD_OUT_DISPLAY_ENABLED                    0x01    // iPod Out Lingo constant.  See the Apple Specification for complete information.
#define IPOD_OUT_AUDIO_DISABLED                     0x02    // iPod Out Lingo constant.  See the Apple Specification for complete information.
#define IPOD_OUT_AUDIO_ENABLED                      0x03    // iPod Out Lingo constant.  See the Apple Specification for complete information.
#define IPOD_OUT_DAYTIME_MODE                       0x04    // iPod Out Lingo constant.  See the Apple Specification for complete information.
#define IPOD_OUT_NIGHTTIME_MODE                     0x05    // iPod Out Lingo constant.  See the Apple Specification for complete information.


//******************************************************************************
// Section: Location Lingo Commands
//******************************************************************************

#define IPOD_LOCATION_AccessoryAck                           0x00    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_GetAccessoryCaps                       0x01    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_RetAccessoryCaps                       0x02    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_GetAccessoryControl                    0x03    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_RetAccessoryControl                    0x04    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_SetAccessoryControl                    0x05    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_GetAccessoryData                       0x06    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_RetAccessoryData                       0x07    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_SetAccessoryData                       0x08    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_AsyncAccessoryData                     0x09    // Location Lingo command.  See the Apple Specification for complete information.
#define IPOD_LOCATION_iPodACK_LOCATION                       0x80    // Location Lingo command.  See the Apple Specification for complete information.

// Renamed in R44 #define IPOD_DevACK_LOCATION                        0x00    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetDevCaps                             0x01    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetDevCaps                             0x02    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetDevControl                          0x03    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetDevControl                          0x04    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetDevControl                          0x05    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_GetDevData                             0x06    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_RetDevData                             0x07    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_SetDevData                             0x08    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_AsyncDevData                           0x09    // Location Lingo command.  See the Apple Specification for complete information.
// Renamed in R44 #define IPOD_iPodACK_LOCATION                       0x80    // Location Lingo command.  See the Apple Specification for complete information.

//******************************************************************************
// Section: Apple Device Device Options Values
//******************************************************************************

#define IPOD_AUTHENTICATE_IMMEDIATELY               0x02        // Authenticate immediately after identification, required for Authentication 2.0.
#define IPOD_POWER_HIGH                             0x03        // Accessory requires 5-100 mA from the Apple device at all times.
#define IPOD_POWER_HIGH_INTERMITTENT                0x01        // Accessory requires 5-100 mA from the Apple device during playback.
#define IPOD_POWER_LOW                              0x00        // Accessory requires less than 5 mA from the Apple device at all times.


//******************************************************************************
// Section: Accessory Status Values
//******************************************************************************

#define IPOD_ACCESSORY_FAULT_NONE                   0x00    // For use with the IPOD_ACCESSORY_STATUS structure.
#define IPOD_ACCESSORY_FAULT_VOLTAGE                0x01    // For use with the IPOD_ACCESSORY_STATUS structure.
#define IPOD_ACCESSORY_FAULT_CURRENT                0x02    // For use with the IPOD_ACCESSORY_STATUS structure.
#define IPOD_ACCESSORY_FAULT_RECOVERABLE            0x01    // For use with the IPOD_ACCESSORY_STATUS structure.
#define IPOD_ACCESSORY_FAULT_NOT_RECOVERABLE        0x02    // For use with the IPOD_ACCESSORY_STATUS structure.


//******************************************************************************
// Section: Miscellaneous Constants
//******************************************************************************

    // Maximum stored length of the Apple device model string.  These strings are
    // usually of the format MnnnnXX, PnnnnXX, MAnnnXX, PAnnnXX, MBnnnXX, or
    // PBnnnXX.
#define IPOD_MAX_MODEL_STRING_LENGTH            10

    // This is the maximum size of command data that the accessory can send
    // to the Apple device.  DO NOT ALTER THIS VALUE.
#define IPOD_MAX_COMMAND_PAYLOAD_LENGTH         (65535 - 5)

    // This is the minimum size of command data that the accessory can send
    // to or receive from the Apple device.  DO NOT ALTER THIS VALUE.
#define IPOD_MIN_COMMAND_PAYLOAD_LENGTH         (128 + 4 + 4)

    // This is the size of the data buffers for receiving data from the Apple device.
    // This is the command payload size plus bytes for the sync byte (1),
    // length (up to 3), and checksum (1).
    // DO NOT ALTER THIS VALUE.
#define IPOD_BUFFER_LENGTH_INPUT                (1 + 3 + IPOD_COMMAND_PAYLOAD_SIZE_IN + 1)

    // This is the size of the data buffers for sending data to the Apple device.
    // This is the command payload size plus bytes for the sync byte (1),
    // length (up to 3), and checksum (1).
    // DO NOT ALTER THIS VALUE.
#define IPOD_BUFFER_LENGTH_OUTPUT               (1 + 3 + IPOD_COMMAND_PAYLOAD_SIZE_OUT + 1)


// Check the user definitions for valid values.
#if IPOD_COMMAND_PAYLOAD_SIZE_IN < IPOD_MIN_COMMAND_PAYLOAD_LENGTH
    #error The minimum input command payload size from the Apple device is 136 bytes.
#endif
#if IPOD_COMMAND_PAYLOAD_SIZE_IN > IPOD_MAX_COMMAND_PAYLOAD_LENGTH
    #error The maximum input command payload size from the Apple device is 65530 bytes.
#endif
#if IPOD_COMMAND_PAYLOAD_SIZE_OUT < IPOD_MIN_COMMAND_PAYLOAD_LENGTH
    #error The minimum output command payload size to the Apple device is 136 bytes.
#endif
#if IPOD_COMMAND_PAYLOAD_SIZE_OUT > IPOD_MAX_COMMAND_PAYLOAD_LENGTH
    #error The maximum output command payload size to the Apple device is 65530 bytes.
#endif

    // For the IPOD_APPLICATION_INFORMATION structure, protocolTransport member.
    // Indicates that the UART hardware interface is being used.
#define IPOD_INTERFACE_UART                     0
    // For the IPOD_APPLICATION_INFORMATION structure, protocolTransport member.
    // Indicates that the USB hardware interface is being used, and the accessory
    // is a USB Host.
#define IPOD_INTERFACE_USB_HOST                 1
    // For the IPOD_APPLICATION_INFORMATION structure, protocolTransport member.
    // Indicates that the USB hardware interface is being used, and the accessory
    // is a USB Device.
#define IPOD_INTERFACE_USB_DEVICE               2
    // For the IPOD_APPLICATION_INFORMATION structure, protocolTransport member.
    // Indicates that the Bluetooth interface is being used.
#define IPOD_INTERFACE_BLUETOOTH                3


//******************************************************************************
//******************************************************************************
// Section: Data Structures
//******************************************************************************
//******************************************************************************

// *****************************************************************************
/* Apple device Accessory Status

This structure is used to return the accessory status to the Apple device.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[4];
    struct __attribute__((packed))
    {
        UINT8   reserved[3];

        UINT8                   : 2;
                    // Possible values are IPOD_ACCESSORY_FAULT_NONE,
                    // IPOD_ACCESSORY_FAULT_RECOVERABLE, and IPOD_ACCESSORY_FAULT_NOT_RECOVERABLE.
        UINT8   faultCondition  : 2;
    };
} IPOD_ACCESSORY_STATUS;


// *****************************************************************************
/* Apple device Application Information

This structure contains information about the Apple device application.

NOTE: Strings have a length restriction of 64 bytes.
*/
typedef struct
{
    union
    {
        UINT32_VAL  lingoes;
        struct __attribute__((packed))
        {
            UINT8   lingoGeneral                : 1;    // If the General lingo is supported.
            UINT8                               : 1;    // lingoMicrophone; Deprecated in R42; If the Microphone lingo is supported.
            UINT8   lingoSimpleRemote           : 1;    // If the Simple Remote lingo is supported.
            UINT8   lingoDisplayRemote          : 1;    // If the Display Remote lingo is supported.

            UINT8   lingoExtendedInterface      : 1;    // If the Extended Interface lingo is supported.
            UINT8                               : 1;    // lingoAccessoryPower; Deprecated in R44; If the Accessory Power lingo is supported.
            UINT8   lingoUSBHostMode            : 1;    // If the USB Host Mode lingo is supported.
            UINT8   lingoRFTuner                : 1;    // If the RF Tuner lingo is supported.

            UINT8   lingoAccessoryEqualizer     : 1;    // If the Accessory Equalizer lingo is supported.
            UINT8   lingoSports                 : 1;    // If the Sports lingo is supported.
            UINT8   lingoDigitalAudio           : 1;    // If the Digital Audio lingo is supported.
            UINT8                               : 1;

            UINT8   lingoStorage                : 1;    // If the Storage lingo is supported.
            UINT8   lingoiPodOut                : 1;    // If the iPod Out lingo is supported.
            UINT8   lingoLocation               : 1;    // If the Location lingo is supported.
            UINT8                               : 1;
            UINT16  reserved;
        };
    } deviceLingoesSpoken;                              // Device Lingoes used by the accessory.

    union
    {
        UINT8   bytes[8];
        struct __attribute__((packed))
        {
            UINT8       analogLineOut           : 1;    // The accessory will use the analog audio line out.
            UINT8       analogLineIn            : 1;    // The accessory will use the analog audio line in.
            UINT8       analogVideoOut          : 1;    // The accessory will use the analog video line out.
            UINT8                               : 1;
            UINT8       digitalAudio            : 1;    // The accessory will use digital audio.
            UINT8                               : 3;

            UINT8                               : 1;
            UINT8       iPhoneApplication       : 1;    // The accessory will communicate with an application.
            UINT8                               : 1;
            UINT8       checksVolume            : 1;    // The accessory will check Apple device volume.
            UINT8                               : 4;

            UINT8                               : 1;
            UINT8       voiceOver               : 1;    // The accessory uses Apple device user interface VoiceOver features.
            UINT8       playbackStateChanges    : 1;    // The accessory can handle asynchronous playback state changes.
            UINT8       multipacketResponse     : 1;    // The accessory can handle a multi-packet response from the Apple device.
            UINT8                               : 1;
            UINT8       audioRouteSwitching     : 1;    // The accessory can switch between digital and analog audio output.
            UINT8                               : 1;
            UINT8       assistiveTouch          : 1;    // The accessory can support AssistiveTouch cursor feature.

            UINT8       reservedSpace[5];
        };
    } accessoryCapsBitmask;                             // Accessory capabilities (Renamed from accCapsBitmask in R44)

    union
    {
        UINT8   bytes[4];
        struct __attribute__((packed))
        {
            UINT8   class1  : 1;    // iPhone, iPhone 3G, iPhone 3GS
            UINT8   class2  : 1;    // iPhone 4 (GSM)
            UINT8   class3  : 1;    // Removed in R43, was iPad
            UINT8   class4  : 1;    // iPhone 4 (CDMA)
            UINT8   class5  : 1;    // iPhone 4S
        };
    } accessoryRFCertifications;

// Deprecated in R42    union
// Deprecated in R42    {
// Deprecated in R42        UINT8   bytes[4];
// Deprecated in R42        struct __attribute__((packed))
// Deprecated in R42        {
// Deprecated in R42            UINT8       stereoLineInput             : 1;    // Stereo line input.
// Deprecated in R42            UINT8       stereoOrMonoLineInput       : 1;    // Stereo or mono line input.
// Deprecated in R42            UINT8       recordingLevelPresent       : 1;    // Recording level is preset and variable.
// Deprecated in R42            UINT8       recordingLevelLimitPreset   : 1;    // Recording level limit is preset.
// Deprecated in R42            UINT8       audioDuplex                 : 1;    // Audio duplex supported.
// Deprecated in R42            UINT8                                   : 3;
// Deprecated in R42            UINT8       reservedSpace[3];
// Deprecated in R42        };
// Deprecated in R42    } micCapsBitmask;

// Deprecated in R44    union
// Deprecated in R44    {
// Deprecated in R44        UINT8   bytes[14];
// Deprecated in R44        struct __attribute__((packed))
// Deprecated in R44        {
// Deprecated in R44            UINT16_VAL  totalScreenWidthInches;             // Accessory's approximate screen width in inches.
// Deprecated in R44            UINT16_VAL  totalScreenHeightInches;            // Accessory's approximate screen height in inches.
// Deprecated in R44            UINT16_VAL  totalScreenWidthPixels;             // Number of pixels along the accessory's screen width.
// Deprecated in R44            UINT16_VAL  totalScreenHeightPixels;            // Number of pixels along the accessory's screen height.
// Deprecated in R44            UINT16_VAL  iPodOutScreenWidthPixels;           // Number of pixels along the Apple device Out screen width allotment.
// Deprecated in R44            UINT16_VAL  iPodOutScreenHeightPixels;          // Number of pixels along the Apple device Out screen height allotment.
// Deprecated in R44            union
// Deprecated in R44            {
// Deprecated in R44                UINT8   byte;
// Deprecated in R44                struct __attribute__((packed))
// Deprecated in R44                {
// Deprecated in R44                    UINT8   colorDisplay    : 1;
// Deprecated in R44                } bits;
// Deprecated in R44            }           screenFeaturesMask;
// Deprecated in R44            UINT8       screenGammaValue;                   // Gamma value minus 1 times 100.
// Deprecated in R44        };
// Deprecated in R44    } screenInfo;

    #if defined( __18CXX )
        const rom char  *accessoryManufacturer;             // Accessory manufacturer, 64 byte maximum length including NULL terminator.
        const rom char  *accessoryName;                     // Accessory name, 64 byte maximum length including NULL terminator.
        const rom char  *accessoryModelNumber;              // Accessor model number, 64 byte maximum length including NULL terminator.
        const rom char  *accessorySerialNumber;             // Accessory serial number, 64 byte maximum length including NULL terminator.
        const rom char  *BundleSeedIDString;                // A 10-byte Vendor App ID assigned by Apple (plus a null terminator).
        const rom char  *protocolStrings;                   // List of null terminated protocol strings.
    #else
        char            *accessoryManufacturer;             // Accessory manufacturer, 64 byte maximum length including NULL terminator.
        char            *accessoryName;                     // Accessory name, 64 byte maximum length including NULL terminator.
        char            *accessoryModelNumber;              // Accessor model number, 64 byte maximum length including NULL terminator.
        char            *accessorySerialNumber;             // Accessory serial number, 64 byte maximum length including NULL terminator.
        char            *BundleSeedIDString;                // A 10-byte Vendor App ID assigned by Apple (plus a null terminator).
        char            *protocolStrings;                   // List of null terminated protocol strings.
    #endif

    UINT8           numEAProtocolStrings;                   // Number of EA Protocol strings pointed to by protocolStrings (Renamed in R44 from numSDKProtocolStrings).

    UINT8           accessorySoftwareVersionMajor;          // Accessory software version, major value.
    UINT8           accessorySoftwareVersionMinor;          // Accessory software version, minor value.
    UINT8           accessorySoftwareVersionRevision;       // Accessory software version, revision value.

    UINT8           accessoryHardwareVersionMajor;          // Accessory hardware version, major value.
    UINT8           accessoryHardwareVersionMinor;          // Accessory hardware version, minor value.
    UINT8           accessoryHardwareVersionRevision;       // Accessory hardware version, revision value.

    union
    {
        UINT8       bytes[2];
        struct __attribute__((packed))
        {
            UINT8       videoOutSetting         : 2;        // IPOD_VIDEO_SETTING_VIDEO_OFF, IPOD_VIDEO_SETTING_VIDEO_ON, or IPOD_VIDEO_SETTING_VIDEO_ASK
            UINT8       screenConfiguration     : 1;        // IPOD_VIDEO_SETTING_SCREEN_FILL or IPOD_VIDEO_SETTING_SCREEN_FIT_TO_EDGE
            UINT8       videoSignalFormat       : 1;        // IPOD_VIDEO_SETTING_SIGNAL_NTSC or IPOD_VIDEO_SETTING_SIGNAL_PAL

            UINT8       lineOutUsage            : 1;        // IPOD_VIDEO_SETTING_LINE_OUT_OFF or IPOD_VIDEO_SETTING_LINE_OUT_ON
            UINT8       videoOutConnection      : 2;        // IPOD_VIDEO_SETTING_VIDEO_TYPE_NONE, IPOD_VIDEO_SETTING_VIDEO_TYPE_COMPOSITE, IPOD_VIDEO_SETTING_VIDEO_TYPE_S_VIDEO, or IPOD_VIDEO_SETTING_VIDEO_TYPE_COMPONENT
            UINT8       closedCaptioning        : 1;        // IPOD_VIDEO_SETTING_CLOSED_CAPTIONING_OFF or IPOD_VIDEO_SETTING_CLOSED_CAPTIONING_ON

            UINT8       videoAspectRatio        : 1;        // IPOD_VIDEO_SETTING_ASPECT_RATIO_4_3 or IPOD_VIDEO_SETTING_ASPECT_RATIO_16_9
            UINT8       subtitles               : 1;        // IPOD_VIDEO_SETTING_SUBTITLES_OFF or IPOD_VIDEO_SETTING_SUBTITLES_ON
            UINT8       alternateAudioChannel   : 1;        // IPOD_VIDEO_SETTING_ALTERNATE_AUDIO_OFF or IPOD_VIDEO_SETTING_ALTERNATE_AUDIO_ON
            UINT8       pauseOnPowerRemoval     : 1;        // IPOD_VIDEO_SETTING_PAUSE_ON or IPOD_VIDEO_SETTING_PAUSE_OFF
        };
    } iPodPreferences;                                      // iPod preferences

    union
    {
        UINT8       bytes[4];
        struct __attribute__((packed))
        {
            UINT8       authenticationControl   : 2;        // Whether or not authentication is required.  Always set to IPOD_AUTHENTICATE_IMMEDIATELY.
// Deprecated in R44            UINT8       powerControl            : 2;        // IPOD_POWER_LOW, IPOD_POWER_HIGH_INTERMITTENT, or IPOD_POWER_HIGH
        };
    } DeviceOptions;

    UINT16  usbExtraCurrentInSuspend;                       // Extra current the device is allowed to draw when in suspend mode.
    UINT16  usbExtraCurrentNotInSuspend;                    // Extra current the device is allowed to draw when not in suspend mode.

    UINT8   cpCommunicationInterface;                       // The interface uses to communicate with the CP chip.
    UINT8   cpCommunicationModule;                          // The specific module used to communicate with the CP chip.

    UINT16  maxCommandPayloadLengthIn;                      // Maximum number of command data bytes the accessory can receive from the Apple device.
    UINT16  maxCommandPayloadLengthOut;                     // Maximum number of command data bytes the accessory can send to the Apple device.

    union
    {
        UINT8       bytes[4];
        struct __attribute__((packed))
        {
            UINT8       disableSyncByteUsage                : 1;    // For UART only; do not use the sync byte.  For Bluetooth modules.
            UINT8       sendExtraCurrentDeviceRequest       : 1;    // USB Host only; send the extra current device request
            UINT8       digitalAudioIn                      : 1;    // USB Device only; digital audio in supported
            UINT8       digitalAudioOut                     : 1;    // USB Device only; digital audio out supported
            UINT8       protocolTransport                   : 3;    // Current hardware interface: IPOD_INTERFACE_UART, IPOD_INTERFACE_USB_HOST, IPOD_INTERFACE_USB_DEVICE
            UINT8       suppressVideoConnectionToken        : 1;    // For the 5G nano - do not send the iPodPreferenceToken to set the video-out connection

            UINT8       suppressVideoOutSettingToken        : 1;    // Do not send the iPodPreferenceToken for video out setting
            UINT8       suppressScreenConfigurationToken    : 1;    // Do not send the iPodPreferenceToken for screen configuration
            UINT8       suppressVideoSignalFormatToken      : 1;    // Do not send the iPodPreferenceToken for video signal format
            UINT8       suppressClosedCaptioningToken       : 1;    // Do not send the iPodPreferenceToken for closed captioning
            UINT8       suppressAspectRatioToken            : 1;    // Do not send the iPodPreferenceToken for aspect ratio
            UINT8       suppressSubtitlesToken              : 1;    // Do not send the iPodPreferenceToken for subtitles
            UINT8       suppressAlternateChannelToken       : 1;    // Do not send the iPodPreferenceToken for video alternate audio channel
            UINT8       suppressPauseOnRemovalToken         : 1;    // Do not send the iPodPreferenceToken for pause on power removal

            UINT8       suppressLineOutUsageToken           : 1;    // Do not send the iPodPreferenceToken for line out usage
            UINT8       suppressGetiPodOptions              : 1;    // Do not send GetiPodOptions (IDL devices only)
            UINT8       suppressSerialNumber                : 1;    // Do not send the optional serial number
            UINT8       suppressMetadata                    : 1;    // Do not send the EAProtocolMetadata token
            UINT8                                           : 4;

            UINT8       commandDelay;                               // Time to delay between application commands (initialize to 0).
        };
    } operationalParameters;

} IPOD_APPLICATION_INFORMATION;


    // Mask for checking for USB Device digital audio in support in the
    // operationalParameters member of the IPOD_APPLICATION_INFORMATION structure.
#define IPOD_DIGITAL_AUDIO_IN       0x20
    // Mask for checking for USB Device digital audio out support in the
    // operationalParameters member of the IPOD_APPLICATION_INFORMATION structure.
#define IPOD_DIGITAL_AUDIO_OUT      0x40

    // Mask for checking operationalParameters byte 0 for any video token suppression.
#define IPOD_PREFERENCES_TOKEN_SUPPRESS0                    0x80
    // Mask for checking operationalParameters byte 1 for any video token suppression.
#define IPOD_PREFERENCES_TOKEN_SUPPRESS1                    0xFF
    // Mask for checking operationalParameters byte 2 for any video token suppression.
#define IPOD_PREFERENCES_TOKEN_SUPPRESS2                    0x00

// *****************************************************************************
/* Apple device Command Information

This structure contains information about the command just received from the
Apple device.
*/
typedef struct
{
    UINT8   lingo;          // Lingo ID of the received command.
    UINT16  command;        // Command ID of the received command.
    UINT16  transactionID;  // Transaction ID, if present.
    UINT8   *pData;         // Pointer to the command data.
    UINT16  dataLength;     // Length of the command data.
} IPOD_COMMAND;


//*****************************************************************************
/* Lingo Protocol Version Information

A pointer to a structure of this format is returned with the the MFI_EVENT
MFI_EVENT_LINGO_VERSION.  The application should check the returned value
so it is aware of the capabilities of an older attached Apple device.
*/
typedef struct
{
    UINT8       lingo;          // Lingo ID.
    UINT16_VAL  version;        // Lingo version, major and minor, in little endian format.
} IPOD_LINGO_VERSION_INFORMATION;


//*****************************************************************************
/* Notifications Bitmask

This structure defines the bits returned by RetSupportedEventNotification.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[6];

        UINT8                                           : 1;    // Reserved
        UINT8   BluetoothConnectionStatus               : 1;
        UINT8                                           : 1;
        UINT8   NowPlayingApplicationDisplayNameStatus  : 1;
        UINT8   AssistiveTouchStatus                    : 1;
        UINT8                                           : 1;
        UINT8                                           : 1;    // Reserved
        UINT8                                           : 1;

        UINT8                                           : 1;    // Reserved
        UINT8   DatabaseAvailable                       : 1;
        UINT8   NowPlayingFocusApp                      : 1;
        UINT8   SessionSpaceAvailable                   : 1;
        UINT8                                           : 1;
        UINT8   CommandCompleted                        : 1;
        UINT8                                           : 1;    // Reserved
        UINT8   iPodOutModeStatus                       : 1;

        UINT8                                           : 1;    // Reserved
        UINT8                                           : 1;    // Reserved
        UINT8   FlowControl                             : 1;
        UINT8   RadioTaggingStatus                      : 1;
        UINT8   CameraStatus                            : 1;
        UINT8   ChargingInfo                            : 1;
        UINT8                                           : 1;    // Reserved
        UINT8                                           : 1;    // Reserved
    };
} IPOD_NOTIFICATIONS_BITMASK;


//*****************************************************************************
/* Options for Accessory Equalizer Lingo

This structure holds all the options of the connected Apple device for the Accessory Equalizer
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    // Reserved
    };
} IPOD_OPTIONS_FOR_LINGO_ACCESSORY_EQUALIZER;


//*****************************************************************************
/* Options for Accessory Power Lingo

This structure holds all the options of the connected Apple device for the Accessory Power
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    // Reserved
    };
} IPOD_OPTIONS_FOR_LINGO_ACCESSORY_POWER;


//*****************************************************************************
/* Options for Digital Audio Lingo

This structure holds all the options of the connected Apple device for the Digital Audio
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   avSynchronization               : 1;    // The Apple device supports A/V synchronization.
    };
} IPOD_OPTIONS_FOR_LINGO_DIGITAL_AUDIO;


//*****************************************************************************
/* Options for Display Remote Lingo

This structure holds all the options of the connected Apple device for the Display Remote
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   volumeControl                   : 1;    // The lingo supports volume control.
        UINT8   absoluteVolumeControl           : 1;    // The lingo supports absolute volume control.
        UINT8   geniusPlaylistCreation          : 1;    // Genius playlist creation supported.
    };
} IPOD_OPTIONS_FOR_LINGO_DISPLAY_REMOTE;


//*****************************************************************************
/* Options for display Extended Interface Lingo

This structure holds all the options of the connected Apple device for the Extended Interface
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   videoBrowsing                   : 1;    // The device supports video browsing.
        UINT8   extendedInterfaceEnhancements   : 1;    // The device supports Extended Interface enhancements.
        UINT8   nestedPlaylists                 : 1;    // The device supports nested playlists.
        UINT8   geniusPlaylistCreation          : 1;    // Genius playlist creation supported.
        UINT8   supportsSetDisplayImage         : 1;    // The device supports setting the display image.
        UINT8   accessibleCategoryList          : 1;    // The accessory can access the list of categories that the Apple device supports.
    };
} IPOD_OPTIONS_FOR_LINGO_EXTENDED_INTERFACE;


//*****************************************************************************
/* Options for General Lingo

This structure holds all the options of the connected Apple device for the General
lingo.  It is primarily intended for iPods that support IDPS.  If the
lingoOptionsGeneralValid member of the IPOD_INFORMATION is not set, then only
the videoOutput flag will be accurate.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[4];

        UINT8   requestApplicationLaunch        : 1;    // Request application launch supported.
        UINT8                                   : 1;    // Reserved
        UINT8   audioRouteSwitching             : 1;    // The Apple device supports audio route switching between digital and analog audio output.
        UINT8   USBHostModeCapable              : 1;    // The Apple device supports USB Host mode using the 28K ohm resistor.
        UINT8   USBHostModeAudioOutput          : 1;    // The Apple device can stream digital audio to a USB audio device.
        UINT8   USBHostModeAudioInput           : 1;    // The Apple device can receive a digital audio stream from a USB audio device.
        UINT8   maxCurrentNotSupported          : 1;    // In USB Host Mode, the device does not support max current draw in Low Power Mode.
        UINT8                                   : 1;    // Reserved

        UINT8                                   : 3;    // Reserved
        UINT8   pauseOnPowerRemoval             : 1;    // Pause on power removal preference control
        UINT8                                   : 3;    // Reserved
        UINT8   extendedIDPSTokens              : 1;    // 0 = Apple device supports subset of IDPS tokens

        UINT8   videoAspectRatio_4_3            : 1;    // The Apple device supports fullscreen output.
        UINT8   videoAspectRatio_16_9           : 1;    // The Apple device supports widescreen output.
        UINT8   subtitles                       : 1;    // The Apple device supports subtitles.
        UINT8   videoAlternateAudioChannel      : 1;    // The Apple device supports an alternate audio channel.
        UINT8                                   : 1;    // Reserved
        UINT8   iPhoneOS3Applications           : 1;    // The Apple device supports communication with OS3 applications.
        UINT8   iPodNotifications               : 1;    // The Apple device supports notifications via the iPodNotification command.
        UINT8                                   : 1;    // Reserved

        UINT8   lineOutUsage                    : 1;    // The Apple device supports line out.
        UINT8   videoOutput                     : 1;    // The Apple device provides video output.
        UINT8   NTSCVideoSignal                 : 1;    // The Apple device can provide an NTSC video signal.
        UINT8   PALVideoSignal                  : 1;    // The Apple device can provide a PAL video signal.
        UINT8   compositeVideoOutConnection     : 1;    // The Apple device can provide a composite video output.
        UINT8   sVideoOutConnection             : 1;    // The Apple device can provide an S-Video output.
        UINT8   componentVideoOutConnection     : 1;    // The Apple device can provide component video output.
        UINT8   closedCaptioning                : 1;    // The Apple device can provide closed captioning.
    };
} IPOD_OPTIONS_FOR_LINGO_GENERAL;


//*****************************************************************************
/* Options for iPod Out Lingo

This structure holds all the options of the connected Apple device for the iPod Out
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   iPodOutAvailable                : 1;    // The Apple device supports the iPod Out lingo.
        UINT8                                   : 7;    // Reserved
    };
} IPOD_OPTIONS_FOR_LINGO_IPOD_OUT;


//*****************************************************************************
/* Options for Location Lingo

This structure holds all the options of the connected Apple device for the Location
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   acceptsLocationData             : 1;    // The Apple device accepts NMEA GPS location data.
        UINT8   sendsLocationData               : 1;    // The Apple device can send location assistance data.
    };
} IPOD_OPTIONS_FOR_LINGO_LOCATION;


//*****************************************************************************
/* Options for Microphone Lingo

This structure holds all the options of the connected Apple device for the Microphone
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    // Reserved
    };
} IPOD_OPTIONS_FOR_LINGO_MICROPHONE;


//*****************************************************************************
/* Options for RF Tuner Lingo

This structure holds all the options of the connected Apple device for the RF Tuner
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   supportRDSRawMode               : 1;    // The Apple device supports RDS raw mode.
        UINT8   supportHDRadioTuning            : 1;    // The Apple device supports HD radio tuning.
        UINT8   supportAMRadioTuning            : 1;    // The Apple device supports AM radio tuning.
        UINT8                                   : 1;    // Reserved
    };
} IPOD_OPTIONS_FOR_LINGO_RF_TUNER;


//*****************************************************************************
/* Options for Simple Remote Lingo

This structure holds all the options of the connected Apple device for the Simple Remote
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[6];

        UINT8   cameraMediaControls             : 1;    // The Apple device supports camera media controls.
        UINT8   USB_HID_Commands                : 1;    //
        UINT8   VoiceOverControls               : 1;    // The Apple device supports VoiceOver controls.
        UINT8   VoiceOverPreferences            : 1;    // The Apple device supports VoiceOver preferences.
        UINT8   AssistiveTouchCursor            : 1;    // The Apple device supports the AssistiveTouch cursor
        UINT8                                   : 3;    // Reserved

        UINT8   contextSpecificControls         : 1;    // The Apple device supports context specific controls.
        UINT8   audioMediaControls              : 1;    // The Apple device supports audio media controls.
        UINT8   videoMediaControls              : 1;    // The Apple device supports video media controls.
        UINT8   imageMediaControls              : 1;    // The Apple device supports image media controls.
        UINT8   sportsMediaControls             : 1;    // The Apple device supports sports media controls.
        UINT8                                   : 3;    // Reserved
    };
} IPOD_OPTIONS_FOR_LINGO_SIMPLE_REMOTE;


//*****************************************************************************
/* Options for Sports Lingo

This structure holds all the options of the connected Apple device for the Sports
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    // Reserved
        UINT8   nikeiPodCardioEquipment         : 1;    // The lingo supports Nike + Apple device cardio equipment.
    };
} IPOD_OPTIONS_FOR_LINGO_SPORTS;


//*****************************************************************************
/* Options for Storage Lingo

This structure holds all the options of the connected Apple device for the Storage
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   iTunesTagging                   : 1;    // The Apple device supports iTunes tagging.
        UINT8   nikeiPodCardioEquipment         : 1;    // The lingo supports Nike + Apple device cardio equipment.
    };
} IPOD_OPTIONS_FOR_LINGO_STORAGE;


//*****************************************************************************
/* Options for USB Host Mode Lingo

This structure holds all the options of the connected Apple device for the USB Host Mode
lingo.  It is primarily intended for iPods that support IDPS.  Flags may not
be fully supported if the Apple device does not support IDPS.
NOTE: The Apple device sends these bytes MSB first, but the PIC architecture is LSB
first.  Rather than flip all the bytes in the received data, the structure is
defined in reverse byte order.  Bit order within the byte is unchanged.
*/
typedef union
{
    UINT8       bytes[8];
    struct __attribute__((packed))
    {
        UINT8   reserved[7];

        UINT8   invokedByHardware               : 1;    // USB Host mode entered via hardware resistor.
        UINT8   invokedByFirmware               : 1;    // USB Host mode entered via iAP command.
        UINT8                                   : 6;    // Reserved
    };
} IPOD_OPTIONS_FOR_LINGO_USB_HOST_MODE;


// *****************************************************************************
/* Apple device Information

This structure contains information about the attached Apple device.
*/
typedef struct
{
    UINT16_VAL      transportMaxPayloadSize;                // The maximum number of bytes that the accessory can send to the Apple Device.

    union
    {
        UINT8       value;
        struct
        {
            UINT8   successfulIDPS                          : 1;    // IDPS was successful, so all options are set when MFI_EVENT_IPOD_READY is thrown.
            UINT8   supportsVideoOutput                     : 1;    // The Apple device supports video output.
            UINT8   supportsSetiPodPreferences              : 1;    // The Apple device supports the SetiPodPreferences command to control line out usage.
            UINT8   supportsDigitalAudio                    : 1;    // The Apple device supports Digital Audio.
            UINT8   digitalAudioRequiresExtendedInterface   : 1;    // Extended Interface mode is required to control digital audio (Renamed from digitalAudioRequiresRemoteUI in R44)
        };
    } flags;
} IPOD_INFORMATION;


// *****************************************************************************
/* Apple device Communication Status

This structure indicates the current status of Apple device interaction.  Each bit
indicates some sort of communication is in progress with the Apple device.  If the
entire value is 0, communication with the Apple device is currently not in progress.
*/
typedef union
{
    UINT8   value;
    struct
    {
        UINT8   identifying                 : 1;
        UINT8   authenticating              : 1;
        UINT8   receivingCommand            : 1;
        UINT8   commandInBuffer             : 1;
        UINT8   transmittingCommand         : 1;
        UINT8   commandReadyToTransmit      : 1;
        UINT8   processingDigitalAudio      : 1;
        UINT8   commandDelayInProgress      : 1;
    };
} IPOD_COMMUNICATION_STATUS;


// *****************************************************************************
/* Token Problem Information

This structure is returned with an MFI_EVENT_TOKEN_PROBLEM event if there is a
problem with a token during IDPS.  The token and status fields are passed from
the driver to the application.  The action field is returned from the application
to the driver.  See the event MFI_EVENT_TOKEN_PROBLEM for more information about
using this structure.
*/
typedef struct
{
    UINT16  token;      // The token with which the Apple device has a problem.
    UINT8   item;       // The specific token item, if any (lingoIDs for IdentifyToken,
                        // accInfoType for AccInfoToken, iPodPrefClass for
                        // IpodPreferenceToken, protocolIndex for EAProtocolToken).
    UINT8   status;     // The status that the Apple device returned for the token.
    UINT8   action;     // The action that the driver should take.  Valid values
                        // are IPOD_TOKEN_PROBLEM_RETRY, IPOD_TOKEN_PROBLEM_IGNORE,
                        // IPOD_TOKEN_PROBLEM_ABANDON, and IPOD_TOKEN_PROBLEM_FAIL.
} IPOD_TOKEN_PROBLEM_INFO;


// *****************************************************************************
/* Apple device Data Format - Received Command

This structure is used for Apple device iAP data.  It is used internally by the
library only.  The structure is memory mapped, so it must be packed.

If the Lingo ID is the Extended Interface Lingo (IPOD_LINGO_EXTENDED_INTERFACE),
then either the smallTelegram or largeTelegram structure should be used.
Otherwise, either the smallPacket or largePacket structure should be used.  If
the payload length marker is 0, then the large format is being used, and the
application must use the members of the largeXXX structure to access the data.
Otherwise, the small format is being used, and the application must use the
members of the smallXXX structure to access the data.

DO NOT MODIFY THIS DATA STRUCTURE!
*/
typedef union __attribute__((packed)) _IPOD_DATA_FORMAT_IN
{
    UINT8               byteArray[IPOD_BUFFER_LENGTH_INPUT];    // Start byte, length bytes, payload, checksum

    struct
    {
        UINT8           startByte;      // Start byte (0x55).
        union
        {
            struct
            {
                UINT8   payloadLengthMarker;    // If 0x00, this is a large packet.
                UINT8   payloadLengthMSB;       // MSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   payloadLengthLSB;       // LSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.
                UINT8   commandID;              // Lingo command.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_IN - 2]; // Command data
                UINT8   checksum;               // Checksum
            }           largePacket;
            struct
            {
                UINT8   payloadLengthMarker;    // If 0x00, this is a large packet.
                UINT8   payloadLengthMSB;       // MSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   payloadLengthLSB;       // LSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.  Must be 0x04 to use this structure.
                UINT8   commandMSB;             // Lingo command MSB.
                UINT8   commandLSB;             // Lingo command LSB.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_IN - 3];  // Command data
                UINT8   checksum;               // Checksum
            }           largeTelegram;
            struct
            {
                UINT8   payloadLength;          // Bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.
                UINT8   commandID;              // Lingo command.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_IN - 2]; // Command data
                UINT8   checksum;               // Checksum
            }           smallPacket;
            struct
            {
                UINT8   payloadLength;          // Bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.  Must be 0x04 to use this structure.
                UINT8   commandMSB;             // Lingo command MSB.
                UINT8   commandLSB;             // Lingo command LSB.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_IN - 3]; // Command data
                UINT8   checksum;               // Checksum
            }           smallTelegram;
        }               command;
    };
} IPOD_DATA_FORMAT_IN;

// *****************************************************************************
/* Apple device Data Format - Transmitted Command

This structure is used for Apple device iAP data.  It is used internally by the
library only.  The structure is memory mapped, so it must be packed.

If the Lingo ID is the Extended Interface Lingo (IPOD_LINGO_EXTENDED_INTERFACE),
then either the smallTelegram or largeTelegram structure should be used.
Otherwise, either the smallPacket or largePacket structure should be used.  If
the payload length marker is 0, then the large format is being used, and the
application must use the members of the largeXXX structure to access the data.
Otherwise, the small format is being used, and the application must use the
members of the smallXXX structure to access the data.

DO NOT MODIFY THIS DATA STRUCTURE!
*/
typedef union __attribute__((packed)) _IPOD_DATA_FORMAT_OUT
{
    UINT8               byteArray[IPOD_BUFFER_LENGTH_OUTPUT];    // Start byte, length bytes, payload, checksum

    struct
    {
        UINT8           startByte;      // Start byte (0x55).
        union
        {
            struct
            {
                UINT8   payloadLengthMarker;    // If 0x00, this is a large packet.
                UINT8   payloadLengthMSB;       // MSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   payloadLengthLSB;       // LSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.
                UINT8   commandID;              // Lingo command.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_OUT - 2]; // Command data
                UINT8   checksum;               // Checksum
            }           largePacket;
            struct
            {
                UINT8   payloadLengthMarker;    // If 0x00, this is a large packet.
                UINT8   payloadLengthMSB;       // MSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   payloadLengthLSB;       // LSB of count of bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.  Must be 0x04 to use this structure.
                UINT8   commandMSB;             // Lingo command MSB.
                UINT8   commandLSB;             // Lingo command LSB.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_OUT - 3];  // Command data
                UINT8   checksum;               // Checksum
            }           largeTelegram;
            struct
            {
                UINT8   payloadLength;          // Bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.
                UINT8   commandID;              // Lingo command.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_OUT - 2]; // Command data
                UINT8   checksum;               // Checksum
            }           smallPacket;
            struct
            {
                UINT8   payloadLength;          // Bytes in the Lingo ID, Command ID, and Command Data sections.
                UINT8   lingoID;                // Lingo identification.  Must be 0x04 to use this structure.
                UINT8   commandMSB;             // Lingo command MSB.
                UINT8   commandLSB;             // Lingo command LSB.
                UINT8   commandData[IPOD_COMMAND_PAYLOAD_SIZE_OUT - 3]; // Command data
                UINT8   checksum;               // Checksum
            }           smallTelegram;
        }               command;
    };
} IPOD_DATA_FORMAT_OUT;


//******************************************************************************
//******************************************************************************
// Section: Global Variables
//******************************************************************************
//******************************************************************************

    // This structure is used to hold application-specific information that the
    // library will use during the identification process.  The application must
    // initialize this information, and modify it if necessary to allow the
    // accessory to support the attached Apple device.  For example, an application may
    // support the Extended Interface Lingo to support the 1G iPod nano, but
    // will need to disable use of that lingo to support the iPad.  That is
    // done by altering this structure appropriately.  Be sure to re-initialize
    // this structure when an Apple device detaches, since the next Apple device that attaches
    // may be a different model.
extern IPOD_APPLICATION_INFORMATION            mfi_iPodApplicationInformation;

    // This ROM variable indicates the version of the library, in BCD format.
    // For example, 0x3014 indicates MFi Library v3.01.04.  This version
    // must match the MFI_VERSION constant, or there is a mismatch between the
    // header file(s) and the library itself.
extern const ROM UINT16                        mfi_Version;

//******************************************************************************
//******************************************************************************
// Section: Application Event Handler
//******************************************************************************
//******************************************************************************

/****************************************************************************
  Function:
    BOOL MFI_HandleiPodDataEvents( MFI_EVENT event, void *data, UINT32 size )

  Description:
    This function must be provided by the application layer.  This function will
    be called by the driver to send data events to the application layer.

  Precondition:
    None

  Parameters:
    MFI_EVENT event - Event that has occurred
    void *data      - Pointer to the data for the event
    UINT32 size      - Size of the data

  Return Values:
    TRUE    - Event was processed
    FALSE   - Event was not processed

  Remarks:
    IMPORTANT - It is recommended not to send Apple device commands from the event
    handler.  If the Apple device driver is busy and cannot accept a new command, the
    attempt will fail, and the event handler will not be called again.
  ***************************************************************************/
#ifdef USB_HOST_APP_DATA_EVENT_HANDLER
BOOL MFI_HandleiPodDataEvents( MFI_EVENT event, void *data, UINT32 size );
#endif


/****************************************************************************
  Function:
    BOOL MFI_HandleiPodEvents( MFI_EVENT event, void *data, UINT32 size )

  Description:
    This function must be provided by the application layer.  This function will
    be called by the driver to send events to the application layer.

  Precondition:
    None

  Parameters:
    MFI_EVENT event - Event that has occurred
    void *data      - Pointer to the data for the event
    UINT32 size      - Size of the data

  Return Values:
    TRUE    - Event was processed
    FALSE   - Event was not processed

  Remarks:
    IMPORTANT - It is recommended not to send Apple device commands from the event
    handler.  If the Apple device driver is busy and cannot accept a new command, the
    attempt will fail, and the event handler will not be called again.
  ***************************************************************************/
BOOL MFI_HandleiPodEvents( MFI_EVENT event, void *data, UINT32 size );


//******************************************************************************
//******************************************************************************
// Section: API Functions
//******************************************************************************
//******************************************************************************


/****************************************************************************
  Function:
    UINT32 MFI_GetBigEndianUINT32( UINT8 *data )

  Description:
    This routine grabs a big endian, 4-byte value and puts it into a UINT32
    for internal processing.

  Precondition:
    None

  Parameters:
    UINT8 *data  - Pointer to the big endian data

  Returns:
    A little endian UINT32

  Remarks:
    None
  ***************************************************************************/

UINT32 MFI_GetBigEndianUINT32( UINT8 *data );


/****************************************************************************
  Function:
    UINT8 * MFI_GetCommandBufferPointer( UINT8 lingoID, UINT16 commandDataSize )

  Summary:
    This routine returns a pointer to the buffer where the application
    should load the command data.  A NULL return value indicates that a command
    cannot be sent.  This command must be called before calling MFI_SendCommand().

  Description:
    This routine returns a pointer to the buffer where the application
    should load the command data.  The location of the command data depends
    on the lingo, the command data length, and whether or not transaction ID's
    are being used.  This function must be used in conjunction with the
    MFI_SendCommand function.

    This function will return NULL if:
        * No Apple device is attached
        * The Apple device is not ready for iAP communication
        * A command delay is in progress
        * Another command is currently being sent
        * The requested commandDataSize is too large

    The maximum amount of data that can be sent is determined by the
    transportMaxPayloadSize member of the IPOD_INFORMATION structure, calculated
    from the maxCommandPayloadLengthOut member of the IPOD_APPLICATION_INFORMATION
    passed to MFI_Initialize and information from the Apple Device itself.
    See the Help file Tips and Tricks for more information on setting this member
    and data size calculations.

  Precondition:
    None

  Parameters:
    UINT8 lingoID            - Lingo ID.  Valid values begin with IPOD_LINGO_.
    UINT16 commandDataSize   - The number of bytes in the command data, which
                                will be inserted between the transaction ID
                                and the checksum.

  Return Values:
    NULL        - The Apple device driver currently is sending a command.
    Not NULL    - A pointer to the first byte of where to load the command data.

  Example:
    This code snippet sends a Play button press to the Apple device.
    <code>
    UINT16 transactionID;

    pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_SIMPLE_REMOTE, 4 );
    if (ptr != NULL)
    {
        *pCommandData++ = 0x01;
        *pCommandData++ = 0x00;
        *pCommandData++ = 0x00;
        *pCommandData++ = 0x00;
        MFI_SendCommand( TRUE, IPOD_LINGO_SIMPLE_REMOTE, IPOD_AudioButtonStatus, 4, &transactionID );
    }
    </code>
    This code snippet sends a DevDataTransfer command, used to communicate with an Apple device app.
    <code>
    UINT16 transactionID;

    pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 6 );
    if (pCommandData != NULL)
    {
        *pCommandData++ = HIGH_BYTE( iPodSessionID );   // From OpenDataSessionForProtocol
        *pCommandData++ = LOW_BYTE(  iPodSessionID );   // From OpenDataSessionForProtocol

        *pCommandData++ = SYNC_BYTE_1;      // Application defined
        *pCommandData++ = SYNC_BYTE_2;      // Application defined
        *pCommandData++ = MY_COMMAND_ID;    // Application defined
        *pCommandData++ = MY_COMMAND_DATA;  // Application defined

        MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_DevDataTransfer, 6, &transactionID );
    }
    </code>

  Remarks:
    The commandDataSize value is not the same as the Apple defined "packet
    payload length".  The commandDataSize value is the number of bytes in the
    command data, which are the bytes between the transaction ID and the
    checksum; the "packet payload length" is commandDataSize plus the bytes
    needed for the lingo ID, the command ID, and the transaction ID, if in use.
  ***************************************************************************/

UINT8 * MFI_GetCommandBufferPointer( UINT8 lingoID, UINT16 commandDataSize );


/****************************************************************************
  Function:
    UINT16 MFI_GetMaxCommandDataSize( UINT8 lingoID )

  Summary:
    This routine returns the maximum number of bytes that can be sent to the
    Apple device in the command data section of a command.

  Description:
    This routine returns the maximum number of bytes that can be sent to the
    Apple device in the command data section of a command.  It determines this value
    from the maximum command payload length out set by the application and the
    maximum transport packet size reported by the Apple Device.  It
    takes into account the lingo and whether or not transaction ID's are
    being used.  It is intended for use with the MFI_GetCommandBufferPointer
    and MFI_SendCommand functions.

  Precondition:
    MFI_Initialize must have been called previously.

  Parameters:
    UINT8  lingoID            - Lingo ID.  Valid values begin with IPOD_LINGO_.

  Returns:
    UINT16 with the maximum number of bytes that can be in the commandDataSize
    parameter of the MFI_GetCommandBufferPointer and MFI_SendCommand functions.

  Remarks:
    None
  ***************************************************************************/

UINT16 MFI_GetMaxCommandDataSize( UINT8 lingoID );


/****************************************************************************
  Function:
    IPOD_COMMUNICATION_STATUS MFI_GetStatus( void )

  Description:
    This routine returns indications of the current status of communication
    with the Apple device.  If all indication bits are 0, then active communication
    with the Apple device is currently not in progress.  This routine does not check
    to see if the UART is in the process of receiving a sync byte from the
    Apple device.

  Precondition:
    None

  Parameters:
    None

  Returns:
    IPOD_COMMUNICATION_STATUS, with status bits about the state of Apple device
    communication.

  Remarks:
    None
  ***************************************************************************/

IPOD_COMMUNICATION_STATUS MFI_GetStatus( void );


/****************************************************************************
  Function:
    UINT8 MFI_Initialize( IPOD_APPLICATION_INFORMATION *iPodApplicationInformation )

  Summary:
    This routine initializes Apple device support.

  Description:
    This routine initializes Apple device support, including resetting the authentication
    CP.  Some hardware initialization may be required before calling this function.

    This function basically does three things:
    * Initialize variables
    * Initialize the USB stack (if using the USB hardware interface)
    * Reset the Apple CP and run the CP self test

  Precondition:
    The application must initialize the mfi_iPodApplicationInformation variable
    before calling this function.

    The application should also initialize the TICK timing function before
    calling this function.

    When using the PIC18 UART interface, the application must set up the following:
        * UART1 TX TRIS
        * UART1 baud rate (TXSTA1 BRGH bit and baud rate generator register SPBRG1)
        * Peripheral interrupt enable
        * Global interrupt enable

    When using a 16-bit or 32-bit MCU UART interface, the application must
    set up the following:
        * If necessary, use Peripheral Pin Select (PPS) to configure U1TX and U1RX appropriately
        * UART1 baud rate (U1MODE BRGH bit and baud rate generator register U1BRG)

    The driver will control the UART interrupt enable/disable.  For 16 and 32-bit PIC's,
    this function will set up a default interrupt priority, but the application can
    override this by simply changing the interrupt priority registers upon return
    from this function.

  Parameters:
    IPOD_APPLICATION_INFORMATION *iPodApplicationInformation   - Must point to the global
                        mfi_iPodApplicationInformation.

  Return Values:
    IPOD_SUCCESS    - Initialization successful.
    IPOD_ERROR      - USB initialization failed.
    IPOD_CP_ERROR   - Error initializing the CP chip.  Either the I2C operations are timing
                        out (one second), or the CP is returning an invalid self test value.
                        Both of these usually indicate a hardware connection problem with the
                        CP.  Confirm I2C module selection, enabling, speed, and pull-ups on
                        the clock and data lines.  Also confirm that the I2C module is being
                        correctly configured and enabled when the library issues the
                        MFI_EVENT MFI_EVENT_CP_OPEN_I2C, and that the CP's nRESET line is
                        being manipulated appropriately when the library issues the
                        MFI_EVENT MFI_EVENT_CP_SET_NRESET.  In addition, confirm that any
                        overriding functionality of the microcontroller pin connected to the
                        CP's nRESET line has been disabled (for example, if it is also an
                        analog input pin, the analog function must be disabled for the pin to
                        operate as digital I/O.  Confirm the I2C timing by monitoring the SCL
                        line with an oscilloscope and verifying that the timing is within spec.
    IPOD_ERROR_INVALID_INFORMATION_STRUCTURE    - Pointer does not point to the global
                        mfi_iPodApplicationInformation.  Applications should use this global
                        IPOD_APPLICATION_INFORMATION variable to define the application
                        specific information.

  Example:
    For PIC24F/PIC32 USB use:
    <code>
    TickInit();
    InitializeiPodInformation();    // Application function to initialize iPodApplicationInformation
    if (MFI_Initialize( &mfi_iPodApplicationInformation ))
    {
        // We have a major problem.
        while (1);
    }
    </code>

    For PIC24 UART use:
    <code>
    #if defined( __PIC24FJ256GB110__ )
        // PPS - Configure U1RX - put on pin 9 (RC4/RPI41)
        RPINR18bits.U1RXR = 41;

        // PPS - Configure U1TX - put on pin 52 (RF2/RP30)
        RPOR15bits.RP30R = 3;
    #endif

    // Set up the UART for 57600 baud at the application's operating frequency.
    U1MODEbits.BRGH = BRGH_57600;
    U1BRG           = BAUDRATE_57600;

    TickInit();
    InitializeiPodInformation();    // Application function to initialize iPodApplicationInformation
    if (MFI_Initialize( &mfi_iPodApplicationInformation ))
    {
        // We have a major problem.
        while (1);
    }
    </code>

    For PIC18 UART use:
    <code>
    // Set up the UART.
    TRISCbits.TRISC6    = 0;    // Set the appropriate UART TX line TRIS bit as an output.
    TXSTA1bits.BRGH     = 1;    // BRG high speed
    SPBRG1              = 8;    // Set baudrate to 57600 when running Fosc=8Mhz

    TickInit();
    InitializeiPodInformation();    // Application function to initialize iPodApplicationInformation
    if (MFI_Initialize( &mfi_iPodApplicationInformation ))
    {
        // We have a major problem.
        while (1);
    }

    // Enable interrupts.
    INTCONbits.PEIE     = 1;    // Enable peripheral interrupts
    INTCONbits.GIE      = 1;    // Enable interrupts globally
    </code>

  Remarks:
    None
  ***************************************************************************/

UINT8 MFI_Initialize( IPOD_APPLICATION_INFORMATION *iPodApplicationInformation );


/****************************************************************************
  Function:
    void MFI_RestartIDPS ( void )

  Summary:
    This routine restarts the identification process.

  Description:
    This routine restarts the identification process.  If IDPS is in progress,
    then IDPS is terminated, and identification is allowed to restart.  If IDL
    is in progress, then identification is simply restarted.

    This function is intended for automatic error recovery during
    authentication and transport upgrade (currently not supported).

  Precondition:
    MFI_Initialize must have been called previously.

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void MFI_RestartIDPS ( void );


/****************************************************************************
  Function:
    UINT8 MFI_SendCommand( BOOL assignTransactionID, UINT8 lingoID, UINT16 commandID,
            UINT16 commandDataSize, UINT16 *transactionID )

  Summary:
    This routine sends an application command to the Apple device.  This function
    must be used in conjunction with the MFI_GetCommandBufferPointer
    function.

  Description:
    This routine sends an application command to the Apple device.  This function
    must be used in conjunction with the MFI_GetCommandBufferPointer
    function.

    If this command is an initiation of a command sequence with the Apple device, set
    assignTransactionID to TRUE, and after this routine completes successfully,
    transactionID will reflect the assigned transaction ID, so the application
    can verify proper response from the Apple device.  If this command is a response to
    an Apple device command, set assignTransactionID to FALSE, and set transactionID to
    the transaction ID to be used.

    This function takes into account whether or not transaction ID's are
    currently in use.  If they are not, then no transaction ID will be added to the
    packet, and *transactionID will be returned as 0.  If they are, then
    the transaction ID will be automatically added to the data packet.

    For all iAP commands, the library populates the command packet up to and
    including the transaction ID, plus the checksum at the end.  Anything in
    between is the application's responsibility.  For example, when issuing the
    command DevDataTransfer, the application is responsible for placing the
    session ID and the data in the command data buffer.  The commandDataSize
    field should match the length of all the bytes inserted after the Transaction
    ID and before the checksum.

  Precondition:
    MFI_Initialize must be called previously.

    If the application is using lingos that require authentication, then the
    event MFI_EVENT_IPOD_READY must be received before calling this
    function.  If the application is not using lingos that require
    authentication, then the event MFI_EVENT_IPOD_ATTACHED must be received
    before calling this function.

    The command data must already be loaded into the output buffer at the
    proper location, as determined by using the MFI_GetCommandBufferPointer
    function.

  Parameters:
    BOOL assignTransactionID    - If the driver should automatically assign a
                                    transaction ID, or if it is provided by the
                                    application.
    UINT8 lingoID               - Lingo ID.  Valid values begin with IPOD_LINGO_.
    UINT16 commandID            - Command ID.  Valid values depend on the lingo.
    UINT16 commandDataSize      - The number of bytes in the command data, which
                                    will be inserted between the transaction ID
                                    and the checksum.
    UINT16 *transactionID       - Pointer to the transaction ID of the command.

  Return Values:
    IPOD_SUCCESS    - Command sent.
    IPOD_NOT_READY  - The Apple device is not in a state where it will accept commands.
    IPOD_BUSY       - A command is currently being sent.
    IPOD_ERROR_INVALID_IAP_COMMAND_LENGTH   - The commandDataSize is too large.

  Example:
    This code snippet sends a Play button press to the Apple device.
    <code>
    UINT16 transactionID;

    pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_SIMPLE_REMOTE, 4 );
    if (ptr != NULL)
    {
        *pCommandData++ = 0x01;
        *pCommandData++ = 0x00;
        *pCommandData++ = 0x00;
        *pCommandData++ = 0x00;
        MFI_SendCommand( TRUE, IPOD_LINGO_SIMPLE_REMOTE, IPOD_AudioButtonStatus, 4, &transactionID );
    }
    </code>
    This code snippet sends a DevDataTransfer command, used to communicate with an Apple device app.
    <code>
    UINT16 transactionID;

    pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 6 );
    if (pCommandData != NULL)
    {
        *pCommandData++ = HIGH_BYTE( iPodSessionID );   // From OpenDataSessionForProtocol
        *pCommandData++ = LOW_BYTE(  iPodSessionID );   // From OpenDataSessionForProtocol

        *pCommandData++ = SYNC_BYTE_1;      // Application defined
        *pCommandData++ = SYNC_BYTE_2;      // Application defined
        *pCommandData++ = MY_COMMAND_ID;    // Application defined
        *pCommandData++ = MY_COMMAND_DATA;  // Application defined

        MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_DevDataTransfer, 6, &transactionID );
    }
    </code>

  Remarks:
    The commandDataSize value is not the same as the Apple defined "packet
    payload length".  The commandDataSize value is the number of bytes in the
    command data, which are the bytes between the transaction ID and the
    checksum; the "packet payload length" is commandDataSize plus the bytes
    needed for the lingo ID and the command ID.
  ***************************************************************************/

UINT8 MFI_SendCommand( BOOL assignTransactionID, UINT8 lingoID, UINT16 commandID,
    UINT16 commandDataSize, UINT16 *transactionID );


/****************************************************************************
  Function:
    UINT8 MFI_SetVideoPreference( UINT8 classID, UINT8 settingID, BOOL restoreOnExit,
            UINT16 *transactionID )

  Description:
    This routine sends a SetiPodPreferences command.  The application should
    watch for the iPodAck that will be received for the SetiPodPreferences command.

  Precondition:
    None

  Parameters:
    UINT8 classID         - Preference class ID.  See the IPOD_VIDEO_CLASS_*
                            values in MFI_iPod.h.
    UINT8 settingID       - Preference setting ID.  See the IPOD_VIDEO_SETTING_*
                            values for the class ID in MFI_iPod.h.
    UINT8 restoreOnExit   - Valid values are:
                            * IPOD_PREFERENCES_RESTORE - The Apple device will restore
                                the original setting when disconnected
                            * IPOD_PREFERENCES_RETAIN - The Apple device will not restore
                                the original setting when disconnected
    UINT16 *transactionID - Transaction ID, so the caller can check the response.

  Return Values:
    IPOD_SUCCESS    - Command sent.
    IPOD_NOT_READY  - The Apple device is not in a state where it will accept commands.
    IPOD_BUSY       - A command is currently being sent.

  Remarks:
    None
  ***************************************************************************/

UINT8 MFI_SetVideoPreference( UINT8 classID, UINT8 settingID, UINT8 restoreOnExit,
        UINT16 *transactionID );


/****************************************************************************
  Function:
    void MFI_Shutdown( void )

  Description:
    This routine can be called to shut down the connection to an Apple device.  The
    events associated with an Apple device detaching will automatically be generated.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void MFI_Shutdown( void );


/****************************************************************************
  Function:
    void MFI_Tasks( void )

  Description:
    This routine should be called on a regular basis to provide Apple device support.

  Precondition:
    MFI_Initialize should be called before calling this function.

    When using the PIC18 UART interface, peripheral interrupts and global
    interrupts must be enabled before the loop that calls this function.

  Parameters:
    None

  Returns:
    None

  Remarks:
    The actual hardware interface is interrupt driven, and does not require
    this function.  However, this function will trigger event generation.  So
    application interaction and response speed will be driven by how
    frequently this routine is called.
  ***************************************************************************/

void MFI_Tasks( void );


///****************************************************************************
//  Function:
//    void MFI_TerminateAudioStream( void )
//
//  Description:
//    This routine terminates a digital audio stream.  It will also generate
//    an event indicating that the stream has stopped.
//
//  Precondition:
//    None
//
//  Parameters:
//    None - None
//
//  Returns:
//    None
//
//  Remarks:
//    None
//  ***************************************************************************/
//#ifdef IPOD_USE_USB_HOST
//    void MFI_TerminateAudioStream( void );
//#endif


/****************************************************************************
  Function:
    void MFI_UART_ISR( void )

  Description:
    This routine handles the receive and transmit interrupts for
    the UART that communicates with the Apple device.  The application layer must call
    this routine from the appropriate interrupt handler.

  Precondition:
    The application layer must initialize the UART such that it runs at either
    19200 or 57600 baud, and generates interrupts on reception.  The MFI
    driver will manipulate the enabling and disabling of transmit interrupts.
    See MFI_Initialize for an example of setting up the UART.

  Parameters:
    None

  Returns:
    None

  Example:
    PIC18: A typical sequence for setting up the interrupt handler is as follows:
    <code>
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
        TickUpdate();       // Update the tick timer.
        MFI_UART_ISR();     // Handle the UART interrupt.
    }
    </code>
    PIC24/dsPIC: A typical sequence for setting up the interrupt handler is as follows:
    <code>
        void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void)
        {
            MFI_UART_ISR();
        }

        void __attribute__((__interrupt__, auto_psv)) _U1TXInterrupt(void)
        {
            MFI_UART_ISR();
        }
    </code>

    PIC32: A typical sequence for setting up the interrupt handler is as follows:
    <code>
        void __attribute((interrupt(ipl4), vector(_UART_1_VECTOR), nomips16)) UART_ISR( void )
        {
            MFI_UART_ISR();
        }
    </code>

  Remarks:
    None
  ***************************************************************************/
#if defined( IPOD_USE_UART  )
    void MFI_UART_ISR( void );
#endif


/****************************************************************************
  Function:
    void MFI_BTDS_ISR( void )

  Description:
    This routine handles the receive and transmit interrupts for
    the UART that communicates with the Bluetooth module using the dotstack
    Bluetooth stack.  The application layer must call this routine from the
    appropriate interrupt handler.

  Precondition:
    The application layer must initialize the UART such that it generates
    interrupts on reception.  The MFI driver will manipulate the enabling
    and disabling of transmit interrupts.
    See MFI_Initialize for an example of setting up the UART.

  Parameters:
    None

  Returns:
    None

  Example:
    PIC18: Not supported
    PIC24/dsPIC: A typical sequence for setting up the interrupt handler is as follows:
    <code>
        void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void)
        {
            MFI_BTDS_ISR();
        }

        void __attribute__((__interrupt__, auto_psv)) _U1TXInterrupt(void)
        {
            MFI_BTDS_ISR();
        }
    </code>

    PIC32: A typical sequence for setting up the interrupt handler is as follows:
    <code>
        void __attribute((interrupt(ipl4), vector(_UART_1_VECTOR), nomips16)) UART_ISR( void )
        {
            MFI_BTDST_ISR();
        }
    </code>

  Remarks:
    None
  ***************************************************************************/
#if defined( IPOD_USE_BLUETOOTH  )
    void MFI_BTDS_ISR( void );
#endif


/****************************************************************************
  Function:
    BOOL USB_ApplicationDataEventHandler( UINT8 address, USB_EVENT event,
                void *data, UINT32 size )

  Summary:
    This is the application USB data event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client drivers or the MFI Library.

  Description:
    This is the application data event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client drivers or the MFI Library.  If the application is able to
    handle the event, it returns TRUE.  Otherwise, it returns FALSE.

    This routine must be defined by any application that uses the USB interface.

  Precondition:
    None

  Parameters:
    UINT8 address   - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    UINT32 size     - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    None
  ***************************************************************************/
#ifdef IPOD_USE_USB_HOST
BOOL USB_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );
#endif

/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( UINT8 address, USB_EVENT event,
                void *data, UINT32 size )

  Summary:
    This is the application USB event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client drivers or the MFI Library.

  Description:
    This is the application USB event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client drivers or the MFI Library.  If the application is able to
    handle the event, it returns TRUE.  Otherwise, it returns FALSE.

    This routine must be defined by any application that uses the USB interface.

  Precondition:
    None

  Parameters:
    UINT8 address   - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    UINT32 size     - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    None
  ***************************************************************************/
#ifdef IPOD_USE_USB_HOST
BOOL USB_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );
#endif



//******************************************************************************
//******************************************************************************
// Section: USB Device Callbacks
//******************************************************************************
//******************************************************************************

#if defined ( IPOD_USE_USB_DEVICE )

/****************************************************************************
  Function:
    void AudioEventCONFIGURED ( void );

  Description:
    This function must be provided by the application if it utilizes digital
    audio as a USB Peripheral Device.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
    void AudioEventCONFIGURED ( void );


/****************************************************************************
  Function:
    BOOL AudioUSBCBTransfer ( BYTE endpointNumber );

  Description:
    This function must be provided by the application if it utilizes digital
    audio as a USB Peripheral Device.

  Precondition:
    None

  Parameters:
    BYTE endpointNumber

  Return Values:
    BOOL

  Remarks:
    None
  ***************************************************************************/
    BOOL AudioUSBCBTransfer ( BYTE endpointNumber );

    //**************************************************************************
    // USB Stack Callbacks
    //**************************************************************************
    void USBCBCheckOtherReq ( void );
    void USBCBErrorHandler(void);
    void USBCBReset ( void );
    void USBCBSendResume(void);
    void USBCBSuspend(void);
    void USBCBWakeFromSuspend(void);
#endif

//******************************************************************************
//******************************************************************************
// Section: USB Embedded Host Callbacks
//******************************************************************************
//******************************************************************************

#if defined ( IPOD_USE_USB_HOST )

/****************************************************************************
  Function:
    BOOL MFI_USB_Host_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );

  Description:
    This function is internal to the MFi Library, and is called as necessary
    by the functions created in mfi_config.c by the MFIConfig.exe configuration tool.

  Precondition:
    None

  Parameters:
    UINT8 address   - Address of USB device
    USB_EVENT event - Event
    void *data      - Pointer to the event data
    UINT32 size     - Size of the data pointed to by *data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    None
  ***************************************************************************/
    BOOL MFI_USB_Host_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );

/****************************************************************************
  Function:
    BOOL MFI_USB_Host_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );

  Description:
    This function is internal to the MFi Library, and is called as necessary
    by the functions created in mfi_config.c by the MFIConfig.exe configuration tool.

  Precondition:
    None

  Parameters:
    UINT8 address   - Address of USB device
    USB_EVENT event - Event
    void *data      - Pointer to the event data
    UINT32 size     - Size of the data pointed to by *data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    None
  ***************************************************************************/
    BOOL MFI_USB_Host_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );

/****************************************************************************
  Function:
    BOOL MFI_USB_Host_Audio_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );

  Description:
    This function is internal to the MFi Library, and is called as necessary
    by the functions created in mfi_config.c by the MFIConfig.exe configuration tool.

  Precondition:
    None

  Parameters:
    UINT8 address   - Address of USB device
    USB_EVENT event - Event
    void *data      - Pointer to the event data
    UINT32 size     - Size of the data pointed to by *data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    None
  ***************************************************************************/
    BOOL MFI_USB_Host_Audio_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );

/****************************************************************************
  Function:
    BOOL MFI_USB_Host_Audio_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );

  Description:
    This function is internal to the MFi Library, and is called as necessary
    by the functions created in mfi_config.c by the MFIConfig.exe configuration tool.

  Precondition:
    None

  Parameters:
    UINT8 address   - Address of USB device
    USB_EVENT event - Event
    void *data      - Pointer to the event data
    UINT32 size     - Size of the data pointed to by *data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    None
  ***************************************************************************/
    BOOL MFI_USB_Host_Audio_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size );
#endif

#endif
