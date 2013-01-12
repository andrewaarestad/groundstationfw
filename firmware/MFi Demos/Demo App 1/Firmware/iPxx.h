/******************************************************************************

File Name:       iPxx.h
Dependencies:    None
Processor:       PIC18, PIC24/dsPIC, PIC32
Company:         Microchip Technology, Inc.

Copyright 2009-2010 Microchip Technology Inc.  All rights reserved.

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

#ifndef IPXX_H
#define IPXX_H

// *****************************************************************************
// Section: Include Files
// *****************************************************************************

#include "main.h"


////////////////////////////////////////////////////////////////////////////////

#ifdef IPXX_C
    ////////////////////////////////////////////////////////////////////////////////
    // Private

    #include "system.h"

    #include "DebugUARTBuffered.h"

    // Use only the newer I2C API.
    #define _PLIB_DISABLE_LEGACY

    #include "MFI/MFI_iPod.h"

    #if defined ( IPOD_USE_BLUETOOTH )
        #if defined ( IPOD_BT_UART_MODULE )
            #include "LM20.h"
        #endif
    #endif

    // *****************************************************************************
    // Section: Configuration
    // *****************************************************************************
    
    #if IPOD_COMMAND_PAYLOAD_SIZE_OUT > 251
        #error To prevent conflicts in packet types, the command payload cannot be greater than 251
    #endif
        
    // *****************************************************************************
    // Section: Constants
    // *****************************************************************************
    #define COMMAND_BUFFER_SIZE                 (IPOD_COMMAND_PAYLOAD_SIZE_IN - 4 + 1)

    #define SYNC_BYTE_1                         0x5A
    #define SYNC_BYTE_2                         0xA5

    //------------------------------------------------------------------------------
    // iPod App Commands

    #define ACC_InitializeAccessory             0
    #define ACC_AccessoryReady                  1
    #define ACC_SetAccessoryLEDs                2
    #define ACC_GetAccessorySwitches            3
    #define ACC_ReturnAccessorySwitches         4
    #define ACC_GetTemperature                  5
    #define ACC_ReturnTemperature               6
    #define ACC_GetPotentiometer                7
    #define ACC_ReturnPotentiometer             8
    #define ACC_SetVolume                       9

    #define ACC_Board_PIC18                     2
    #define ACC_Board_EXPLORER16                3

    #define ACC_COMMAND_SIZE                    (10 - 2)    // Ten bytes minus the session ID

    // *****************************************************************************
    // Section: Data Structures and Enumerations
    // *****************************************************************************

    // *****************************************************************************
    /* iPxx Status

    This structure contains information about the status of the application.
    */
    typedef struct
    {
        UINT32_VAL      communicationWaitTime;
        UINT32_VAL      communicationWaitStart;

        union
        {
            UINT8       value;
            struct
            {
                UINT8   communicationWaiting            : 1;
                UINT8   errorMessageDisplayed           : 1;
                UINT8   autolaunchSupported             : 1;
                UINT8   tryOldAutolaunchRequest         : 1;
                UINT8   waitingForSessionSpaceAvailable : 1;
                UINT8   sendSmallDataTransfer           : 1;
            } bits;
        } flags;

    } IPXX_STATUS;


    // *****************************************************************************
    /* Command Status

    This structure holds the transaction ID's of the various commands that we must
    acknowledge, to make sure that we send the correct transaction ID for the
    correct ACK.  It is safer to do it this way, in case the accessory receives
    back-to-back commands.
    */
    typedef struct
    {
        UINT32      timeoutDevDataTransferACK;
        
        UINT16      transactionIDOpenDataSession;
        UINT16      transactionIDCloseDataSession;
        UINT16      transactionIDiPodDataTransfer;
        UINT16      transactionIDDevDataTransfer;
    
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
        } flags;
    } IPXX_COMMAND_STATUS;


    // *****************************************************************************
    /* iPod Application Command

    This structure is used to hold commands from the iPod.
    */
    #if COMMAND_BUFFER_SIZE < 256
        typedef struct
        {
            UINT8   packet[COMMAND_BUFFER_SIZE];
            UINT8   head;
            UINT8   tail;
        } IPXX_APP_COMMAND;
    #else
        typedef struct
        {
            UINT8   packet[COMMAND_BUFFER_SIZE];
            UINT16  head;
            UINT16  tail;
        } IPXX_APP_COMMAND;
    #endif


    // *****************************************************************************
    // Section: Local Prototypes
    // *****************************************************************************

    BOOL        iPxx_CanSendDevDataTransfer( void );
    BOOL        iPxx_IsCommandAvailable( void );

#else
    ////////////////////////////////////////////////////////////////////////////////
    // Public

#endif

////////////////////////////////////////////////////////////////////////////////
// Common

// *****************************************************************************
// Section: Constants
// *****************************************************************************

#define IPXX_SUCCESS        0


// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************

BOOL        iPxx_Initialize( INTERFACE_DATA *interfaceData );
void        iPxx_InitializeInformation( void );
void        iPxx_Tasks( INTERFACE_DATA *interfaceData );

#endif

