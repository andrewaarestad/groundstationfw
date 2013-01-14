/******************************************************************************

File Name:       iPxx.c
Dependencies:    None
Processor:       PIC18, PIC24/dsPIC, PIC32
Company:         Microchip Technology, Inc.

Copyright 2009-2012 Microchip Technology Inc.  All rights reserved.

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

*******************************************************************************/

#define IPXX_C
#include "iPxx.h"
#include "groundStation.X/debugQueue.h"

// *****************************************************************************
// *****************************************************************************
// Section: Configuration
// *****************************************************************************
// *****************************************************************************

// Make sure that the Authentication coprocessor I2C frequency we want can be
// achieved at the speed we are running.
#if defined (__PIC32MX__)
    // We must do this check at run time for the PIC32.
#else
    // Since we are not doing any clock switching, and I2C_Clock() is defined as a constant,
    // we can do this here at compile time.  If I2C_Clock() is not a constant, you can still
    // perform this check at compile time by substituting constants for the possible values
    // of the clock speed.  Note that the first parameter of I2CGeneratedFrequency is not
    // needed for this check.

    #define I2C_FREQ_ACTUAL I2CGeneratedFrequency( 0, I2C_Clock(), IPOD_CP_FREQUENCY )
    #if (I2C_FREQ_ACTUAL > IPOD_CP_FREQUENCY)
        #define I2C_FREQ_ERROR                      (I2C_FREQ_ACTUAL-IPOD_CP_FREQUENCY)
    #else
        #define I2C_FREQ_ERROR                      (IPOD_CP_FREQUENCY-I2C_FREQ_ACTUAL)
    #endif
    #define I2C_FREQ_ERROR_PERCENT        ((I2C_FREQ_ERROR*100 + IPOD_CP_FREQUENCY/2) / IPOD_CP_FREQUENCY)

    #if (I2C_FREQ_ERROR_PERCENT > 50)
        #error I2C frequency error is worse than 50%
    #elif (I2C_FREQ_ERROR_PERCENT > 10)
        #warning I2C frequency error is worse than 10%
    #endif
#endif


//******************************************************************************
//******************************************************************************
// Section: Global Variables
//******************************************************************************
//******************************************************************************

#if defined ( __18CXX )
    #pragma udata COMMAND_BUFFER
    IPXX_APP_COMMAND                iPxxCommand;
    #pragma udata
#else
    IPXX_APP_COMMAND                iPxxCommand;
#endif
IPXX_COMMAND_STATUS             iPxxCommandStatus;
IPOD_INFORMATION                *iPxxInformation;
INTERFACE_DATA                  *iPxxInterfaceData;
UINT8                           iPxxProtocolIndex;
UINT16                          iPxxSessionID;
IPXX_STATUS                     iPxxStatus;




//******************************************************************************
//******************************************************************************
// Section: Macros
//******************************************************************************
//******************************************************************************

#define HIGH_BYTE(x)                    (((x) >> 8) & 0xFF)
#define LOW_BYTE(x)                     ((x) & 0xFF)

//******************************************************************************
//******************************************************************************
// Section: Command Buffer Manipulation Routines and Macros
//******************************************************************************
//******************************************************************************

#define CommandBufferAdd(x)     {                                                   \
                                    iPxxCommand.packet[iPxxCommand.head++] = x;     \
                                    if (iPxxCommand.head == COMMAND_BUFFER_SIZE)    \
                                    {                                               \
                                        iPxxCommand.head = 0;                       \
                                    }                                               \
                                }

#if (COMMAND_BUFFER_SIZE + ACC_COMMAND_SIZE) < 256
UINT8 CommandBufferBytesAvailable( void )
#else
UINT16 CommandBufferBytesAvailable( void )
#endif
{
    if (iPxxCommand.head >= iPxxCommand.tail)
    {
        return iPxxCommand.head - iPxxCommand.tail;
    }
    else
    {
        return COMMAND_BUFFER_SIZE + iPxxCommand.head - iPxxCommand.tail;
    }
}

#define CommandBufferEmpty()    (iPxxCommand.head == iPxxCommand.tail)
#define CommandBufferFull()     (((iPxxCommand.head == COMMAND_BUFFER_SIZE-1) && (iPxxCommand.tail == 0)) || \
                                  (iPxxCommand.head == iPxxCommand.tail-1))

#if (COMMAND_BUFFER_SIZE + ACC_COMMAND_SIZE) < 256
    UINT8 CommandBufferPeek( UINT8 offset )
    {
        UINT8    location;

        location = iPxxCommand.tail + offset;
        if (location >= COMMAND_BUFFER_SIZE)
        {
            location -= COMMAND_BUFFER_SIZE;
        }
        return iPxxCommand.packet[location];
    }
#else
    UINT8 CommandBufferPeek( UINT16 offset )
    {
        UINT16    location;

        location = iPxxCommand.tail + offset;
        if (location >= COMMAND_BUFFER_SIZE)
        {
            location -= COMMAND_BUFFER_SIZE;
        }
        return iPxxCommand.packet[location];
    }
#endif

#if (COMMAND_BUFFER_SIZE + ACC_COMMAND_SIZE) < 256
    void CommandBufferRemove( UINT8 count )
    {
        iPxxCommand.tail += count;
        if (iPxxCommand.tail >= COMMAND_BUFFER_SIZE)
        {
            iPxxCommand.tail -= COMMAND_BUFFER_SIZE;
        }
    }
#else
    void CommandBufferRemove( UINT16 count )
    {
        iPxxCommand.tail += count;
        if (iPxxCommand.tail >= COMMAND_BUFFER_SIZE)
        {
            iPxxCommand.tail -= COMMAND_BUFFER_SIZE;
        }
    }
#endif

#define CommandBufferReset()            { iPxxCommand.head = 0; iPxxCommand.tail = 0; }

#define IsCommandStart()                ((CommandBufferPeek(0) == SYNC_BYTE_1) && (CommandBufferPeek(1) == SYNC_BYTE_2))


/****************************************************************************
  Function:
     BOOL iPxx_CanSendDevDataTransfer( void )

  Description:
    This function indicates whether or not a DevDataTransfer command can
    be sent.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    TRUE    - a DevDataTransfer command can be sent
    FALSE   - a DevDataTransfer command cannot be sent at this time

  Remarks:
    This function assumes that the configuration file enables both audio and
    video output.  We will disable them if they are not available.
  ***************************************************************************/

BOOL iPxx_CanSendDevDataTransfer( void )
{
    return  (   iPxxInterfaceData->flags.bits.dataSessionOpen &&
              ! iPxxStatus.flags.bits.waitingForSessionSpaceAvailable &&
              ! iPxxCommandStatus.flags.sendingCommand &&
              ! iPxxCommandStatus.flags.waitingForDevDataTransferACK );
}


/****************************************************************************
  Function:
     BOOL iPxx_Initialize( INTERFACE_DATA *interfaceData )

  Description:
    This function initializes the iPod driver.

  Precondition:
    None

  Parameters:
    INTERFACE_DATA *interfaceData

  Return Values:
    IPXX_SUCCESS    - Initialization was successful

  Remarks:
    This function assumes that the configuration file enables both audio and
    video output.  We will disable them if they are not available.
  ***************************************************************************/

BOOL iPxx_Initialize( INTERFACE_DATA *interfaceData )
{
    UINT8       initializationReturn;

    // Our event handler needs to know where this structure is.
    iPxxInterfaceData = interfaceData;

    memset( (UINT8 *)&iPxxCommandStatus, 0, sizeof( IPXX_COMMAND_STATUS ) );
    iPxxStatus.flags.value = 0;
    CommandBufferReset();

    // Initialize the iPod driver.
    initializationReturn = MFI_Initialize( &mfi_iPodApplicationInformation );
    if (initializationReturn != IPOD_SUCCESS)
    {
        // We have a major problem
        if (initializationReturn == IPOD_CP_ERROR)
        {
            UpdateInformation( "CP access problem" );
        }
        else
        {
            UpdateInformation( "Cannot initialize" );
        }

        // Hold here.  Flash the LED's so we know there is a problem.
        BlinkIndication( BLINK_PATTERN_ON_OFF, BLINK_INFINITE, 500 );
    }

    return IPXX_SUCCESS;
}


/****************************************************************************
  Function:
     void iPxx_InitializeInformation( void )

  Description:
    This function initializes the interface variable used by the MFI Library
    to perform IDPS/IDL.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    This function assumes that the configuration file enables both audio and
    video output.  We will disable them if they are not available.
  ***************************************************************************/

void iPxx_InitializeInformation( void )
{
    mfi_iPodApplicationInformation.deviceLingoesSpoken.lingoes.Val          = IPOD_ACCESSORY_LINGOES;

    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[0]            = IPOD_ACCESSORY_CAPABILITIES_BYTE0;
    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[1]            = IPOD_ACCESSORY_CAPABILITIES_BYTE1;
    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[2]            = IPOD_ACCESSORY_CAPABILITIES_BYTE2;
    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[3]            = IPOD_ACCESSORY_CAPABILITIES_BYTE3;
    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[4]            = IPOD_ACCESSORY_CAPABILITIES_BYTE4;
    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[5]            = IPOD_ACCESSORY_CAPABILITIES_BYTE5;
    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[6]            = IPOD_ACCESSORY_CAPABILITIES_BYTE6;
    mfi_iPodApplicationInformation.accessoryCapsBitmask.bytes[7]            = IPOD_ACCESSORY_CAPABILITIES_BYTE7;

    mfi_iPodApplicationInformation.accessoryRFCertifications.bytes[0]       = IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE0;
    mfi_iPodApplicationInformation.accessoryRFCertifications.bytes[1]       = IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE1;
    mfi_iPodApplicationInformation.accessoryRFCertifications.bytes[2]       = IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE2;
    mfi_iPodApplicationInformation.accessoryRFCertifications.bytes[3]       = IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE3;

    #if defined ( _PIC14E )
        mfi_iPodApplicationInformation.accessoryManufacturer                    = (char *) IPOD_ACCESSORY_MANUFACTURER;
        mfi_iPodApplicationInformation.accessoryName                            = (char *) IPOD_ACCESSORY_NAME;
        mfi_iPodApplicationInformation.accessoryModelNumber                     = (char *) IPOD_ACCESSORY_MODEL_NUMBER;
        mfi_iPodApplicationInformation.accessorySerialNumber                    = (char *) IPOD_ACCESSORY_SERIAL_NUMBER;
    #else
        mfi_iPodApplicationInformation.accessoryManufacturer                    = IPOD_ACCESSORY_MANUFACTURER;
        mfi_iPodApplicationInformation.accessoryName                            = IPOD_ACCESSORY_NAME;
        mfi_iPodApplicationInformation.accessoryModelNumber                     = IPOD_ACCESSORY_MODEL_NUMBER;
        mfi_iPodApplicationInformation.accessorySerialNumber                    = IPOD_ACCESSORY_SERIAL_NUMBER;
    #endif

    #if defined ( _PIC14E )
        mfi_iPodApplicationInformation.BundleSeedIDString                       = (char *) IPOD_ACCESSORY_BUNDLE_SEED_ID;
    #else
        mfi_iPodApplicationInformation.BundleSeedIDString                       = IPOD_ACCESSORY_BUNDLE_SEED_ID;
    #endif

    mfi_iPodApplicationInformation.numEAProtocolStrings                     = IPOD_ACCESSORY_EA_STRING_COUNT;

    #if defined ( _PIC14E )
        mfi_iPodApplicationInformation.protocolStrings                          = (char *)IPOD_ACCESSORY_EA_STRINGS;
    #else
        mfi_iPodApplicationInformation.protocolStrings                          = IPOD_ACCESSORY_EA_STRINGS;
    #endif

    mfi_iPodApplicationInformation.accessorySoftwareVersionMajor            = IPOD_ACCESSORY_SOFTWARE_VERSION_MAJOR;
    mfi_iPodApplicationInformation.accessorySoftwareVersionMinor            = IPOD_ACCESSORY_SOFTWARE_VERSION_MINOR;
    mfi_iPodApplicationInformation.accessorySoftwareVersionRevision         = IPOD_ACCESSORY_SOFTWARE_VERSION_REV;

    mfi_iPodApplicationInformation.accessoryHardwareVersionMajor            = IPOD_ACCESSORY_HARDWARE_VERSION_MAJOR;
    mfi_iPodApplicationInformation.accessoryHardwareVersionMinor            = IPOD_ACCESSORY_HARDWARE_VERSION_MINOR;
    mfi_iPodApplicationInformation.accessoryHardwareVersionRevision         = IPOD_ACCESSORY_HARDWARE_VERSION_REV;

    mfi_iPodApplicationInformation.iPodPreferences.bytes[0]                 = IPOD_ACCESSORY_PREFERENCES_BYTE0;
    mfi_iPodApplicationInformation.iPodPreferences.bytes[1]                 = IPOD_ACCESSORY_PREFERENCES_BYTE1;

    mfi_iPodApplicationInformation.DeviceOptions.bytes[0]                   = IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE0;
    mfi_iPodApplicationInformation.DeviceOptions.bytes[1]                   = IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE1;
    mfi_iPodApplicationInformation.DeviceOptions.bytes[2]                   = IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE2;
    mfi_iPodApplicationInformation.DeviceOptions.bytes[3]                   = IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE3;

    mfi_iPodApplicationInformation.usbExtraCurrentInSuspend                 = IPOD_USB_EXTRA_CURRENT_IN_SUSPEND;
    mfi_iPodApplicationInformation.usbExtraCurrentNotInSuspend              = IPOD_USB_EXTRA_CURRENT_NOT_IN_SUSPEND;

    mfi_iPodApplicationInformation.cpCommunicationInterface                 = IPOD_CP_INTERFACE;
    mfi_iPodApplicationInformation.cpCommunicationModule                    = I2C1;

    mfi_iPodApplicationInformation.maxCommandPayloadLengthIn                = IPOD_COMMAND_PAYLOAD_SIZE_IN;
    mfi_iPodApplicationInformation.maxCommandPayloadLengthOut               = IPOD_COMMAND_PAYLOAD_SIZE_OUT;

    mfi_iPodApplicationInformation.operationalParameters.bytes[0]           = IPOD_OPERATIONAL_PARAMETERS_BYTE0;
    mfi_iPodApplicationInformation.operationalParameters.bytes[1]           = IPOD_OPERATIONAL_PARAMETERS_BYTE1;
    mfi_iPodApplicationInformation.operationalParameters.bytes[2]           = IPOD_OPERATIONAL_PARAMETERS_BYTE2;
    mfi_iPodApplicationInformation.operationalParameters.commandDelay       = 0;

    #ifndef VIDEO_OUTPUT_AVAILABLE
        // Note that we have to disable all of the options, or the iPod will not be happy.
        mfi_iPodApplicationInformation.accessoryCapsBitmask.analogVideoOut  = 0;
        mfi_iPodApplicationInformation.iPodPreferences.videoOutSetting      = IPOD_VIDEO_SETTING_VIDEO_OFF;
        mfi_iPodApplicationInformation.iPodPreferences.videoOutConnection   = IPOD_VIDEO_SETTING_VIDEO_TYPE_NONE;
    #endif
    #ifndef AUDIO_OUTPUT_AVAILABLE
        // Note that we have to disable all of the options, or the iPod will not be happy.
        mfi_iPodApplicationInformation.accessoryCapsBitmask.analogLineOut   = 0;
        mfi_iPodApplicationInformation.iPodPreferences.lineOutUsage         = 0;
    #endif
}


/****************************************************************************
  Function:
    BOOL iPxx_IsCommandAvailable( void )

  Description:
    This routine determines if a command is available in the iPodCommand
    buffer.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    TRUE    - A command is present in iPodCommandBuffer
    FALSE   - No command is available

  Remarks:
    None
  ***************************************************************************/

BOOL iPxx_IsCommandAvailable( void )
{
    if (CommandBufferBytesAvailable() >= ACC_COMMAND_SIZE)
    {
        if (IsCommandStart())
        {
            // We have a command.
            return TRUE;
        }
        else
        {
            // We are out of sync.  Search until we find a pair of sync bytes.
            // or we empty out the command buffer.  If there is a command
            // eventually, we will find it on the next pass through.
            while (!CommandBufferEmpty() && !IsCommandStart())
            {
                CommandBufferRemove( 1 );
            }
        }
    }
    return FALSE;
}


/****************************************************************************
  Function:
     void iPxx_Tasks( INTERFACE_DATA *interfaceData )

  Description:
    This function is called during the main processing loop, to send any
    messages that need to be sent to the iPod.

    This function will try to send the maximum amount of responses to the
    Apple Device, based on the maximum packet size of the protocol.  In this
    application defined protocol, the response to each command was defined to
    be the same size - 10 bytes.  However, for demonstration purposes, the
    algorithm below is implemented assuming that each command may have a
    varying response length.  Received commands are only removed from the
    receive buffer after the response has been sent, so it is important to
    ensure that the response will always be less than the maximum packet
    size.

  Precondition:
    None

  Parameters:
    INTERFACE_DATA *interfaceData

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void iPxx_Tasks( INTERFACE_DATA *interfaceData )
{
    UINT8   command;
    UINT8   *pCommandData;

    int bytesNeeded;
    int idx;
    
    const char *debugString;

    char myChar;

    // Our event handler needs to know where this structure is.
    iPxxInterfaceData = interfaceData;

    // If we are currently waiting because of an iPodNotification FlowControl
    // message, see if the timeout has passed.
    if (iPxxStatus.flags.bits.communicationWaiting)
    {
        if (TickGet() >= (iPxxStatus.communicationWaitStart.Val + iPxxStatus.communicationWaitTime.Val))
        {
            iPxxStatus.flags.bits.communicationWaiting = 0;
        }
    }

    // If we are currently waiting for an ACK to a DevDataTransfer command, see if the
    // timeout has passed.
    if (iPxxCommandStatus.flags.waitingForDevDataTransferACK)
    {
        if (TickGet() >= iPxxCommandStatus.timeoutDevDataTransferACK)
        {
            iPxxCommandStatus.flags.waitingForDevDataTransferACK = 0;
        }
    }

    if (!iPxxStatus.flags.bits.communicationWaiting)
    {
        if (iPxxCommandStatus.flags.sendGetSupportedEventNotification)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 0 );
            if ( pCommandData != NULL )
            {
                if ( MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_GetSupportedEventNotification, 0, NULL ) == IPOD_SUCCESS )
                {
                    iPxxCommandStatus.flags.sendGetSupportedEventNotification = 0;
                }
            }
        }
        else if (iPxxCommandStatus.flags.sendSetEventNotification)
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
                    iPxxCommandStatus.flags.sendSetEventNotification = 0;
                }
            }
        }
        else if (iPxxCommandStatus.flags.sendAutolaunchRequest)
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
                if ( iPxxStatus.flags.bits.tryOldAutolaunchRequest )
                {
                    *pCommandData++ = 1;    // Reserved, R43 and earlier spec value
                }
                else
                {
                    *pCommandData++ = 2;    // Reserved, R44 and later spec value; R45 - must try both
                }
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
                    iPxxCommandStatus.flags.sendAutolaunchRequest = 0;
                    iPxxCommandStatus.flags.sendingCommand = 1;
                }
            }
        }
        else if (iPxxCommandStatus.flags.sendOpenDataSessionACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                interfaceData->flags.bits.dataSessionOpen = 1;
                pCommandData[0] = 0x00;     // Success
                pCommandData[1] = IPOD_OpenDataSessionForProtocol;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iPxxCommandStatus.transactionIDOpenDataSession) ) == IPOD_SUCCESS )
                {
                    iPxxCommandStatus.flags.sendOpenDataSessionACK = 0;
                    iPxxCommandStatus.flags.sendingCommand = 1;
                }
            }
        }
        else if (iPxxCommandStatus.flags.sendCloseDataSessionACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                pCommandData[0] = 0x00;     // Success
                pCommandData[1] = IPOD_CloseDataSession;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iPxxCommandStatus.transactionIDCloseDataSession) ) == IPOD_SUCCESS )
                {
                    iPxxCommandStatus.flags.sendCloseDataSessionACK = 0;
                    iPxxCommandStatus.flags.sendingCommand = 1;
                }
            }
        }
        else if (iPxxCommandStatus.flags.sendiPodDataTransferACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                *pCommandData++ = IPOD_ACK_SUCCESS;
                *pCommandData++ = IPOD_iPodDataTransfer;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iPxxCommandStatus.transactionIDiPodDataTransfer) ) == IPOD_SUCCESS )
                {
                    iPxxCommandStatus.flags.sendiPodDataTransferACK = 0;
                    iPxxCommandStatus.flags.sendingCommand = 1;
                }
            }
        }
        else if (iPxxCommandStatus.flags.sendiPodDataTransferNACK)
        {
            pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 2 );
            if (pCommandData != NULL)
            {
                *pCommandData++ = IPOD_ACK_BAD_PARAMETER;
                *pCommandData++ = IPOD_iPodDataTransfer;
                if ( MFI_SendCommand( FALSE, IPOD_LINGO_GENERAL, IPOD_AccessoryACK, 2, &(iPxxCommandStatus.transactionIDiPodDataTransfer) ) == IPOD_SUCCESS )
                {
                    iPxxCommandStatus.flags.sendiPodDataTransferNACK = 0;
                    iPxxCommandStatus.flags.sendingCommand = 1;
                }
            }
        }
        else if (interfaceData->flags.bits.sendSwitchState)
        {
            if ( iPxx_CanSendDevDataTransfer() )
            {
                pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, 10 );
                if (pCommandData != NULL)
                {
                    interfaceData->flags.bits.sendSwitchState   = 0;
                    interfaceData->buttonChange.value           = 0;
                    interfaceData->buttonFlag.value             = 0;

                    memset( pCommandData, 0x00, 10 );
                    *pCommandData++ = HIGH_BYTE( iPxxSessionID );
                    *pCommandData++ = LOW_BYTE(  iPxxSessionID );
                    *pCommandData++ = SYNC_BYTE_1;
                    *pCommandData++ = SYNC_BYTE_2;

                    *pCommandData++ = ACC_ReturnAccessorySwitches;
                    *pCommandData++ = interfaceData->buttonState.value;

                    if ( MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_AccessoryDataTransfer, 10, &(iPxxCommandStatus.transactionIDDevDataTransfer) ) == IPOD_SUCCESS )
                    {
                        iPxxCommandStatus.flags.sendingCommand = 1;
                        iPxxCommandStatus.flags.waitingForDevDataTransferACK = 1;
                        iPxxCommandStatus.timeoutDevDataTransferACK = TickGet() + (500 * dwTicksPerMillisecond);
                    }
                }
            }
        }
        else if ( iPxx_CanSendDevDataTransfer() )
        {
            // In case this command processing takes a long time, only do it if we are not currently
            // in the process of sending a command.  Otherwise, we may not send a DevACK in a timely
            // fashion, and the iPod may repeat the command.

            if ( iPxx_IsCommandAvailable() )
            {
                // Ask for the maximum amount of space.  We may not use it all.  Subtract the length
                // of the lingo, command, and transaction ID bytes.
                // NOTE: We have to be careful of the different packet types here.  The returned data pointer for
                // a large packet is different than the returned data pointer for a small packet.  If the
                // commandDataSize is greater than 252, then a large packet pointer will be returned.

                pCommandData = MFI_GetCommandBufferPointer( IPOD_LINGO_GENERAL, MFI_GetMaxCommandDataSize( IPOD_LINGO_GENERAL ) - 4 );
                if (pCommandData != NULL)
                {
                    BOOL    spaceAvailable  = TRUE;
                    UINT16  bytesUsed       = 0;

                    memset( pCommandData, 0x00, mfi_iPodApplicationInformation.maxCommandPayloadLengthOut - 4 );

                    while (iPxx_IsCommandAvailable() && spaceAvailable)
                    {
                        command = CommandBufferPeek( 2 );
                        switch (command)
                        {
                            case ACC_InitializeAccessory:
                                // This response requires 10 bytes
                                if ( (bytesUsed + 10) > ( mfi_iPodApplicationInformation.maxCommandPayloadLengthOut - 4 ) )
                                {
                                    spaceAvailable = FALSE;
                                }
                                else
                                {
                                    *pCommandData++ = HIGH_BYTE( iPxxSessionID );
                                    *pCommandData++ = LOW_BYTE(  iPxxSessionID );
                                    *pCommandData++ = SYNC_BYTE_1;
                                    *pCommandData++ = SYNC_BYTE_2;

                                    *pCommandData++ = ACC_AccessoryReady;
                                    *pCommandData++ = 0x00;     // Success
                                    *pCommandData++ = IPOD_ACCESSORY_SOFTWARE_VERSION_MAJOR;
                                    *pCommandData++ = IPOD_ACCESSORY_SOFTWARE_VERSION_MINOR;
                                    *pCommandData++ = IPOD_ACCESSORY_SOFTWARE_VERSION_REV;

                                    #if defined ( __18CXX ) || defined ( _PIC14E )
                                        *pCommandData++ = ACC_Board_PIC18;
                                    #else
                                        *pCommandData++ = ACC_Board_EXPLORER16;
                                    #endif
                                    bytesUsed += 10;
                                }
                                break;

                            case ACC_AccessoryReady:
                                // Will not be received by the accessory.
                                break;

                            case ACC_SetAccessoryLEDs:
                                LEDSet ( CommandBufferPeek ( 3 ));
                                break;

                            case ACC_GetAccessorySwitches:
                                // This response requires 10 bytes
                                if (( bytesUsed + 10 ) > ( mfi_iPodApplicationInformation.maxCommandPayloadLengthOut - 4 ) )
                                {
                                    spaceAvailable = FALSE;
                                }
                                else
                                {
                                    *pCommandData++ = HIGH_BYTE( iPxxSessionID );
                                    *pCommandData++ = LOW_BYTE(  iPxxSessionID );
                                    *pCommandData++ = SYNC_BYTE_1;
                                    *pCommandData++ = SYNC_BYTE_2;

                                    *pCommandData++ = ACC_ReturnAccessorySwitches;
                                    *pCommandData++ = interfaceData->buttonState.value;

                                    pCommandData += 4;
                                    bytesUsed += 10;
                                }
                                break;

                            case ACC_ReturnAccessorySwitches:
                                // Will not be received by the accessory.
                                break;

                            case ACC_GetTemperature:
                                // This response requires 10 bytes
                                if ( (bytesUsed + 10) > ( mfi_iPodApplicationInformation.maxCommandPayloadLengthOut - 4 ) )
                                {
                                    spaceAvailable = FALSE;
                                }
                                else
                                {
                                    *pCommandData++ = HIGH_BYTE( iPxxSessionID );
                                    *pCommandData++ = LOW_BYTE(  iPxxSessionID );
                                    *pCommandData++ = SYNC_BYTE_1;
                                    *pCommandData++ = SYNC_BYTE_2;

                                    *pCommandData++ = ACC_ReturnTemperature;

                                    *pCommandData++ = interfaceData->temperatureSign;
                                    *pCommandData++ = interfaceData->temperatureDegrees;
                                    *pCommandData++ = interfaceData->temperatureTenths;

                                    pCommandData += 2;
                                    bytesUsed += 10;
                                }
                                break;

                            case ACC_GetDebugInstrum:

                                debugString = getQueueItem();

                                if (debugString)
                                {
                                    /*bytesNeeded = 0;
                                    do
                                    {
                                        myChar = *debugString;
                                        bytesNeeded++;
                                    }
                                    while (*debugString++);

                                     */
                                    
                                    // Make sure enough bytes are available
                                    bytesNeeded = strlen(debugString) + 5;
                                    if ( (bytesUsed + bytesNeeded) > ( mfi_iPodApplicationInformation.maxCommandPayloadLengthOut - 4 ) )
                                    {
                                        spaceAvailable = FALSE;
                                    }
                                    else
                                    {
                                        *pCommandData++ = HIGH_BYTE( iPxxSessionID );
                                        *pCommandData++ = LOW_BYTE(  iPxxSessionID );
                                        *pCommandData++ = SYNC_BYTE_1;
                                        *pCommandData++ = SYNC_BYTE_2;

                                        *pCommandData++ = ACC_ReturnDebugInstrum;

                                        for (idx=0;idx<bytesNeeded;idx++)
                                        {
                                            *pCommandData++ = debugString[idx];
                                        }

                                        bytesUsed += bytesNeeded;
                                    }
                                }
                                
                                break;

                            case ACC_ReturnTemperature:
                                // Will not be received by the accessory.
                                break;

                            case ACC_GetPotentiometer:
                                // This response requires 10 bytes
                                if ( (bytesUsed + 10) > ( mfi_iPodApplicationInformation.maxCommandPayloadLengthOut - 4 ) )
                                {
                                    spaceAvailable = FALSE;
                                }
                                else
                                {
                                    *pCommandData++ = HIGH_BYTE( iPxxSessionID );
                                    *pCommandData++ = LOW_BYTE(  iPxxSessionID );
                                    *pCommandData++ = SYNC_BYTE_1;
                                    *pCommandData++ = SYNC_BYTE_2;

                                    *pCommandData++ = ACC_ReturnPotentiometer;
                                    *pCommandData++ = interfaceData->potentiometer.byte.HB;
                                    *pCommandData++ = interfaceData->potentiometer.byte.LB;

                                    pCommandData += 3;
                                    bytesUsed += 10;
                                }
                                break;

                            case ACC_ReturnPotentiometer:
                                // Will not be received by the accessory.
                                break;

                            case ACC_SetVolume:
                                interfaceData->volume = CommandBufferPeek( 3 );
                                break;
                        }

                        // If we had enough space to respond to the command, remove the command from the
                        // receive buffer.  Otherwise, leave it in the buffer, so we can process it
                        // next time.
                        if ( spaceAvailable )
                        {
                            CommandBufferRemove( ACC_COMMAND_SIZE );
                        }
                    }

                    // If we generated any response commands, send them.
                    if (bytesUsed != 0)
                    {
                        if ( MFI_SendCommand( TRUE, IPOD_LINGO_GENERAL, IPOD_AccessoryDataTransfer, bytesUsed, &(iPxxCommandStatus.transactionIDDevDataTransfer) ) == IPOD_SUCCESS )
                        {
                            iPxxCommandStatus.flags.sendingCommand = 1;
                            iPxxCommandStatus.flags.waitingForDevDataTransferACK = 1;
                            iPxxCommandStatus.timeoutDevDataTransferACK = TickGet() + (500 * dwTicksPerMillisecond);
                        }
                    }
                }
            }
        }
    }
}


//******************************************************************************
//******************************************************************************
// iPod Event Handlers
//******************************************************************************
//******************************************************************************


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
            // We need to tell the library whether or not an iPod is present.  If
            // we are using the UART or USB Device interface, we need to look at pins 13 and 30
            // on the connector.  If we are using the USB Host interface, we do not need
            // to monitor these pins, and we can simply return TRUE.
            #if defined( IPOD_USE_UART ) && ! defined( IPOD_USE_BLUETOOTH )
                if ((IPOD_ACCESSORY_POWER == 1) && (IPOD_DETECT == 0) && (size == 0))
                {
                    // An iPod just attached.  Set the RX and TX TRIS appropriately.
                    ConfigureUARTPins();
                }
                return (IPOD_ACCESSORY_POWER == 1) && (IPOD_DETECT == 0);
            #elif defined( IPOD_USE_USB_DEVICE )
                return (IPOD_ACCESSORY_POWER == 1) && (IPOD_DETECT == 0);
            #elif defined ( IPOD_BT_UART_MODULE )
                // We are using the LM20 for our Bluetooth module
                return LM20_IsConnected ();
            #else
                return TRUE;
            #endif
            break;

        case MFI_EVENT_CP_SET_NRESET:
            // Set the CP nRESET line to the requested state.  ACP 2.0B
            DebugUART_PrintString( "MFI_EVENT_CP_SET_NRESET\r\n" );
            #if defined ( MFI_AUTH_NRESET )
                MFI_AUTH_NRESET = size;
            #endif
            break;

        case MFI_EVENT_CP_OPEN_I2C:
            if (iPxxInterfaceData->inUseI2C.value != 0)
            {
                return FALSE;
            }
            else
            {
                // Enable the I2C at the proper frequency.
                DebugUART_PrintString( "MFI_EVENT_CP_OPEN_I2C\r\n" );
                #if defined ( __18CXX ) || defined ( _PIC14E )
                    I2CConfigure( mfi_iPodApplicationInformation.cpCommunicationModule, I2C_MODE_MASTER | I2C_STANDARD_SPEED_SLEW_CONTROL_DISABLE );
                #endif
                I2CSetFrequency( mfi_iPodApplicationInformation.cpCommunicationModule, I2C_Clock(), IPOD_CP_FREQUENCY );
                I2CEnable( mfi_iPodApplicationInformation.cpCommunicationModule, TRUE );
                Delay10us( 10 );
                iPxxInterfaceData->inUseI2C.bits.inUseI2C_MFI = 1;
            }
            break;

        case MFI_EVENT_CP_I2C_CLOSED:
            // The library is done using the I2C module.
            DebugUART_PrintString( "MFI_EVENT_CP_I2C_CLOSED\r\n" );
            iPxxInterfaceData->inUseI2C.bits.inUseI2C_MFI = 0;
            break;

        case MFI_EVENT_CANNOT_SET_EXTRA_CURRENT:
            // Cannot send the extra current configuration message to  the iPod (USB only).
            DebugUART_PrintString( "MFI_EVENT_CANNOT_SET_EXTRA_CURRENT\r\n" );
            UpdateInformation( "Cannot configure current" );
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            break;

        case MFI_EVENT_GENERAL_ERROR:
            // General USB error.
            DebugUART_PrintString( "MFI_EVENT_GENERAL_ERROR\r\n" );
            UpdateInformation( "Error -  redock iPod" );
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            break;

        case MFI_EVENT_FATAL_ERROR:
            // Fatal USB error.
            DebugUART_PrintString( "MFI_EVENT_FATAL_ERROR\r\n" );
            UpdateInformation( "Fatal system    error" );
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            break;

        case MFI_EVENT_IPOD_ATTACHED:
            // The library recognizes that an iPod has attached.  Identification is
            // complete, but authentication still needs to take place.  Do not spend
            // too much time here.
            DebugUART_PrintString( "MFI_EVENT_IPOD_ATTACHED\r\n" );
            UpdateInformation( " iPod attached" );
            BlinkIndication( BLINK_PATTERN_BROKEN_THIRDS, 2, 30 );
            break;

        case MFI_EVENT_IPOD_DETACHED:
            // The iPod has detached.
            DebugUART_PrintString( "MFI_EVENT_IPOD_DETACHED\r\n" );
            #if defined( IPOD_USE_UART ) && ! defined( IPOD_USE_BLUETOOTH )
                TristateUARTPins();
            #endif
            UpdateInformation( WELCOME_STRING );
            LEDSet ( 0 );

            // Reset all flags and buffers.
            CommandBufferReset();
            iPxxStatus.flags.value = 0;
            iPxxInterfaceData->flags.value = 0;

            // We might have had to reconfigure ourselves for the specific attached device.
            // Set the application information back to its default values.
            iPxx_InitializeInformation();
            break;

        case MFI_EVENT_IDPS_NOT_SUPPORTED:
            // If the iPod doesn't suppport IDPS, then it doesn't support
            // apps either, so abandon the identification and authentication.
            DebugUART_PrintString( "MFI_EVENT_IDPS_NOT_SUPPORTED\r\n" );
            UpdateInformation( "IDPS not supported" );
            iPxxStatus.flags.bits.errorMessageDisplayed = 1;
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            return FALSE;
            break;

        case MFI_EVENT_LINGO_NOT_SUPPORTED:
            // The only lingo we are asking for is General, so if there is a
            // problem, we need to terminate.  See the online Help file
            // for more information about this event.
            DebugUART_PrintString( "MFI_EVENT_LINGO_NOT_SUPPORTED\r\n" );
            UpdateInformation( "No lingo support" );
            iPxxStatus.flags.bits.errorMessageDisplayed = 1;
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            return FALSE;
            break;

        case MFI_EVENT_CHECK_LINGO_OPTIONS:
            // Make sure the iPod can handle OS3 apps.  We have to check this here.
            // Some iPods won't return an error later.  See the online Help file
            // for more information about this event.
            DebugUART_PrintString( "MFI_EVENT_CHECK_LINGO_OPTIONS\r\n" );
            if (*(UINT8 *)data == IPOD_LINGO_GENERAL)
            {
                #ifdef _PIC14E
                if( ((IPOD_OPTIONS_FOR_LINGO_GENERAL *)((UINT8*)(((UINT16)data)+1)))->iPhoneOS3Applications == 0  )
                #else
                if (((IPOD_OPTIONS_FOR_LINGO_GENERAL *)(data+1))->iPhoneOS3Applications == 0)
                #endif
                {
                    UpdateInformation( "Apps not supported" );
                    iPxxStatus.flags.bits.errorMessageDisplayed = 1;
                    BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
                    return FALSE;
                }
                iPxxStatus.flags.bits.tryOldAutolaunchRequest = 0;
                #ifdef _PIC14E
                    iPxxStatus.flags.bits.autolaunchSupported = ((IPOD_OPTIONS_FOR_LINGO_GENERAL *)((UINT8*)(((UINT16)data)+1)))->requestApplicationLaunch;
                #else
                    iPxxStatus.flags.bits.autolaunchSupported = ((IPOD_OPTIONS_FOR_LINGO_GENERAL *)(data+1))->requestApplicationLaunch;
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

// For example only:  If the application can be configured based on available lingoes, this is how to handle
// an unsupported lingo.  Note that if lingo support needs to be removed, IDPS must be reset.  The library
// will do this if IPOD_TOKEN_PROBLEM_RESET is returned in the action member.
//
//            DebugUART_PrintString( "MFI_EVENT_TOKEN_PROBLEM, token " );
//            DebugUART_PutHex( ((IPOD_TOKEN_PROBLEM_INFO *)data)->token );
//            DebugUART_PrintString( ", item " );
//            DebugUART_PutHex( ((IPOD_TOKEN_PROBLEM_INFO *)data)->item );
//            DebugUART_PrintString( ", status " );
//            DebugUART_PutHex( ((IPOD_TOKEN_PROBLEM_INFO *)data)->status );
//            DebugUART_PrintString( "\r\n" );
//
//            if (((IPOD_TOKEN_PROBLEM_INFO *)data)->token == IPOD_FID_IdentifyToken)
//            {
//                // This is probably an unsupported lingo problem on a device that was
//                // created before the lingo existed.  This is not a nice failure.
//                if (mfi_iPodApplicationInformation.deviceLingoesSpoken.lingoiPodOut)
//                {
//                    mfi_iPodApplicationInformation.deviceLingoesSpoken.lingoiPodOut = 0;
//                    ((IPOD_TOKEN_PROBLEM_INFO *)data)->action = IPOD_TOKEN_PROBLEM_RESET;
//                }
//                else
//                {
//                    // We can't do anything else.  Kill it.
//                    ((IPOD_TOKEN_PROBLEM_INFO *)data)->action = IPOD_TOKEN_PROBLEM_FAIL;
//                }
//            }
//            else
//            {
//                ((IPOD_TOKEN_PROBLEM_INFO *)data)->action = IPOD_TOKEN_PROBLEM_IGNORE;
//            }
            break;

        case MFI_EVENT_IPOD_CANNOT_CONNECT:
            // The iPod will not let us connect.
            DebugUART_PrintString( "MFI_EVENT_IPOD_CANNOT_CONNECT\r\n" );
            if ( size == IPOD_ERROR_MAX_CONNECTIONS )
            {
                UpdateInformation( "OS connect error max connections" );
            }
            else if ( size == IPOD_ERROR_FID_TOKEN_PROBLEM )
            {
                UpdateInformation( "OS connect error token problem" );
            }
            else
            {
                UpdateInformation( "OS connect error" );
            }
            iPxxStatus.flags.bits.errorMessageDisplayed = 1;
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            break;

        case MFI_EVENT_IDPS_FAILURE:
            // IDPS failed.  We cannot communicate with the iPod.
            DebugUART_PrintString( "MFI_EVENT_IDPS_FAILURE\r\n" );
            if (!iPxxStatus.flags.bits.errorMessageDisplayed)
            {
                // This event gets thrown when IDPS is abandoned, even if we told
                // the driver to abandon it.  So only update the message if it
                // is new information.
                UpdateInformation( "IDPS failed" );
                BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            }
            iPxxStatus.flags.bits.errorMessageDisplayed = 0;
            break;

        case MFI_EVENT_IPOD_AUTHENTICATION_FAILED:
            // Authentication failed.  We cannot communicate with the iPod.
            DebugUART_PrintString( "MFI_EVENT_IPOD_AUTHENTICATION_FAILED - error 0x" );
            DebugUART_PutHex( size );
            DebugUART_PrintString( "\r\n" );
            switch ( size )
            {
                case IPOD_ERROR_BAD_CERTIFICATE_LENGTH:
                    UpdateInformation( "Bad cert. length" );
                    break;
                case IPOD_ERROR_CERTIFICATE_PIECE_PROBLEM:
                    UpdateInformation( "Cert piece problem" );
                    break;
                case IPOD_ERROR_CERTIFICATE_PROBLEM:
                    UpdateInformation( "Cert problem" );
                    break;
                case IPOD_ERROR_NOT_AUTHENTICATED:
                    UpdateInformation( "Not auth'd" );
                    break;
                case IPOD_ERROR_BAD_AUTHENTICATION_VERSION:
                    UpdateInformation( "Bad auth version" );
                    break;
                case IPOD_ERROR_CERTIFICATE_INVALID:
                    UpdateInformation( "Cert invalid" );
                    break;
                case IPOD_ERROR_PERMISSIONS_INVALID:
                    UpdateInformation( "Permiss invalid" );
                    break;
                case IPOD_ERROR_ACCESSORY_RESISTOR_INVALID:
                    UpdateInformation( "Resistor invalid" );
                    break;
                default:
                    UpdateInformation( "Auth failed" );
                    break;
            }
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            break;

        case MFI_EVENT_IPOD_READY:
            // Identification and authentication have completed, and we can now
            // communicate with the iPod.  For this demo to work, we need an Apple Device
            // that supports IDPS.
            DebugUART_PrintString( "MFI_EVENT_IPOD_READY\r\n" );
            iPxxInformation = (IPOD_INFORMATION *)data;         // Save a pointer to the iPod information structure.
            if (iPxxInformation->flags.successfulIDPS)
            {
                UpdateInformation( "   iPod Ready" );
                BlinkIndication( BLINK_PATTERN_IN_OUT, 2, 30 );

                // Set the flag to sent the GetSupportedEventNotification command.
                iPxxCommandStatus.flags.sendGetSupportedEventNotification = 1;
            }
            else
            {
                UpdateInformation( "Unsupported iPod" );
                BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
            }
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
                                    iPxxCommandStatus.flags.waitingForDevDataTransferACK = 0;
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

                                        if ( sessionID.Val == iPxxSessionID )
                                        {
                                            iPxxStatus.flags.bits.waitingForSessionSpaceAvailable = 1;

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
                                    iPxxCommandStatus.flags.sendAutolaunchRequest = iPxxStatus.flags.bits.autolaunchSupported;
                                    break;

                                case IPOD_RequestApplicationLaunch:
                                    if ( ! iPxxStatus.flags.bits.tryOldAutolaunchRequest )
                                    {
                                        #ifdef _PIC14E
                                        if ( (*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData) == IPOD_ACK_BAD_PARAMETER) )
                                        #else
                                        if ( (*(((IPOD_COMMAND *)data)->pData) == IPOD_ACK_BAD_PARAMETER) )
                                        #endif
                                        {
                                            iPxxStatus.flags.bits.tryOldAutolaunchRequest = 1;
                                            iPxxCommandStatus.flags.sendAutolaunchRequest = 1;
                                        }
                                    }
                                break;
                            }
                            break;

                        case IPOD_OpenDataSessionForProtocol:
                            #if defined( _PIC14E )
                                iPxxSessionID       = ((UINT16)(*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData)) << 8) | (UINT16)(*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+1));
                                iPxxProtocolIndex   = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+2);

                            #else
                                iPxxSessionID       = ((UINT16)(*(((IPOD_COMMAND *)data)->pData)) << 8) | (UINT16)(*(((IPOD_COMMAND *)data)->pData+1));
                                iPxxProtocolIndex   = *(((IPOD_COMMAND *)data)->pData+2);
                            #endif

                            iPxxCommandStatus.flags.sendOpenDataSessionACK = 1;
                            #if defined ( _PIC14E )
                                iPxxCommandStatus.transactionIDOpenDataSession = ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->transactionID;
                            #else
                                iPxxCommandStatus.transactionIDOpenDataSession = ((IPOD_COMMAND *)data)->transactionID;
                            #endif
                            break;

                        case IPOD_CloseDataSession:
                            // Shut down everything, and make sure we don't send any more responses.
                            LEDSet ( 0 );
                            CommandBufferReset();

                            iPxxInterfaceData->flags.bits.dataSessionOpen = 0;  // Close the data session immediately.
                            iPxxCommandStatus.flags.sendCloseDataSessionACK = 1;
                            #if defined ( _PIC14E )
                                iPxxCommandStatus.transactionIDCloseDataSession = ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->transactionID;
                            #else
                                iPxxCommandStatus.transactionIDCloseDataSession = ((IPOD_COMMAND *)data)->transactionID;
                            #endif
                            break;

                        case IPOD_iPodDataTransfer:
                            #if defined ( _PIC14E )
                                iPxxCommandStatus.transactionIDiPodDataTransfer = ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->transactionID;
                            #else
                                iPxxCommandStatus.transactionIDiPodDataTransfer = ((IPOD_COMMAND *)data)->transactionID;
                            #endif

                            if (!iPxxInterfaceData->flags.bits.dataSessionOpen)
                            {
                                // There is no session open.  Respond with an ACK and Bad Parameter.
                                iPxxCommandStatus.flags.sendiPodDataTransferNACK = 1;
                            }
                            else
                            {
                                // Copy the data into a buffer.  We may not have enough data
                                // for a command, or we may have several commands.  So we
                                // cannot process it here.
                                #if IPOD_COMMAND_PAYLOAD_SIZE_IN > 250
                                    UINT16  i;
                                #else
                                    UINT8   i;
                                #endif
                                UINT8    *ptr;

                                #if defined ( _PIC14E )
                                    ptr = ((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData;
                                #else
                                    ptr = ((IPOD_COMMAND *)data)->pData;
                                #endif
                                //sessionID = ((UINT16)*ptr << 8) | (UINT16)*(ptr+1);
                                ptr += 2;
                                #if defined ( _PIC14E )
                                for (i=2; i<((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->dataLength; i++)
                                #else
                                for (i=2; i<((IPOD_COMMAND *)data)->dataLength; i++)
                                #endif

                                {
                                    if (!CommandBufferFull())
                                    {
                                        CommandBufferAdd( *ptr );
                                        ptr++;
                                    }
                                    else
                                    {
                                        // Our receive buffer is full.
                                        Nop();
                                    }
                                }

                                iPxxCommandStatus.flags.sendiPodDataTransferACK = 1;
                            }
                            break;

                        case IPOD_iPodNotification:
                            #ifdef _PIC14E
                            if (*(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData) == IPOD_iPodNotification_FlowControl)
                            #else
                            if (*(((IPOD_COMMAND *)data)->pData) == IPOD_iPodNotification_FlowControl)
                            #endif
                            {
                                iPxxStatus.flags.bits.communicationWaiting = 1;
                                #ifdef _PIC14E
                                    iPxxStatus.communicationWaitTime.v[3] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+1);
                                    iPxxStatus.communicationWaitTime.v[2] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+2);
                                    iPxxStatus.communicationWaitTime.v[1] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+3);
                                    iPxxStatus.communicationWaitTime.v[0] = *(((IPOD_COMMAND *)((UINT8*)((UINT16)data)))->pData+4);
                                #else
                                    iPxxStatus.communicationWaitTime.v[3] = *(((IPOD_COMMAND *)data)->pData+1);
                                    iPxxStatus.communicationWaitTime.v[2] = *(((IPOD_COMMAND *)data)->pData+2);
                                    iPxxStatus.communicationWaitTime.v[1] = *(((IPOD_COMMAND *)data)->pData+3);
                                    iPxxStatus.communicationWaitTime.v[0] = *(((IPOD_COMMAND *)data)->pData+4);
                                #endif
                                iPxxStatus.communicationWaitTime.Val *= dwTicksPerMillisecond;  // Convert to ticks
                                iPxxStatus.communicationWaitStart.Val = TickGet();
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

                                if ( sessionID.Val == iPxxSessionID )
                                {
                                    iPxxStatus.flags.bits.waitingForSessionSpaceAvailable = 0;
                                    iPxxStatus.flags.bits.sendSmallDataTransfer = 1;
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
                                iPxxCommandStatus.flags.sendSetEventNotification = 1;
                            }
                            else
                            {
                                // If autolaunch is supported, try to launch the app.
                                iPxxCommandStatus.flags.sendAutolaunchRequest = iPxxStatus.flags.bits.autolaunchSupported;
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
            iPxxCommandStatus.flags.sendingCommand = 0;
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
            UpdateInformation( "Buffer overrun" );
            DebugUART_PrintString( "MFI_EVENT_RECEIVE_BUFFER_OVERRUN\r\n" );
            Nop();
            #ifdef __DEBUG
                while (1);
            #endif
            break;

        case MFI_EVENT_RECEIVE_BUFFER_OVERRUN_COMMAND:
            // UART receive buffer overrun.
            UpdateInformation( "Command overrun" );
            DebugUART_PrintString( "MFI_EVENT_RECEIVE_BUFFER_OVERRUN_COMMAND\r\n" );
            Nop();
            #ifdef __DEBUG
                while (1);
            #endif
            break;

        default:
            break;
    }

    return TRUE;
}

