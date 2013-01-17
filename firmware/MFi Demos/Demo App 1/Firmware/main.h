/******************************************************************************

File Name:       main.h
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

#ifndef MAIN_H
#define MAIN_H

////////////////////////////////////////////////////////////////////////////////
// Common

#include <usart.h>
#include <delays.h>
#include "GenericTypedefs.h"
#include "mfi_config.h"
#include "system.h"

// *****************************************************************************
// Section: Configuration
// *****************************************************************************

    // Ensure that the configuration files were created with the correct library
    // version.  This will also see if this demo is grabbing an mfi_config.h file
    // from a previous installation version.
#if (((_MFI_CONFIG_VERSION_MAJOR * 100) + _MFI_CONFIG_VERSION_MINOR) < 299)
    #error Please ensure that configuration files are up to date, and remove any old versions
#endif

// *****************************************************************************
// Section: Data Structures and Enumerations
// *****************************************************************************

// *****************************************************************************
/* Button Data

This data is used by various modules in the system.
*/
typedef union
{
    UINT8   value;
    struct
    {
        UINT8   b0  : 1;
        UINT8   b1  : 1;
        UINT8   b2  : 1;
        UINT8   b3  : 1;
    } bits;
} BUTTON_STRUCT;


// *****************************************************************************
/* Interface Data

This data is used by various modules in the system.
*/
#define UART_BUFFER_SIZE 100

typedef struct
{
    UINT16_VAL      potentiometer;

    BUTTON_STRUCT   buttonState;
    BUTTON_STRUCT   buttonChange;
    BUTTON_STRUCT   buttonFlag;

    UINT8           temperatureDegrees;
    UINT8           temperatureSign;
    UINT8           temperatureTenths;

    UINT8           volume;

    char uartData1[UART_BUFFER_SIZE];
    char uartData2[UART_BUFFER_SIZE];
    UINT8 uartActiveBuffer;
    UINT8 uartData1Length;
    UINT8 uartData2Length;

    union
    {
        UINT8       value;
        struct
        {
            UINT8   dataSessionOpen         : 1;
            UINT8   sendSwitchState         : 1;
            #ifdef IPOD_USE_BLUETOOTH
                UINT8   pairingMode         : 1;
                UINT8   removeAllPairings   : 1;
                UINT8   initializationDone  : 1;
            #endif
        } bits;
    } flags;

    union
    {
        UINT8       value;
        struct
        {
            UINT8   inUseI2C_LM45490        : 1;
            UINT8   inUseI2C_MCP9800        : 1;
            UINT8   inUseI2C_MFI            : 1;
        } bits;
    } inUseI2C;
} INTERFACE_DATA;


////////////////////////////////////////////////////////////////////////////////

#ifdef MAIN_C

    ////////////////////////////////////////////////////////////////////////////////
    // Private

    #include "DebugUARTBuffered.h"

    #include "MFI/MFI_iPod.h"

    #ifdef IPOD_USE_UART
        #include "MFI/MFI_iPod_UART.h"
    #endif

    #include "iPxx.h"
    #ifdef IPOD_USE_BLUETOOTH
        #include "MFI/MFI_Data.h"
        #if defined ( IPOD_BT_UART_MODULE )
            #include "LM20.h"
        #elif defined ( IPOD_BT_CANDLEDRAGON_CSR )
            #include "MFI/MFI_BT_DotStack.h"
        #endif
    #endif

    #ifdef LCD_AVAILABLE
        #include "LCDBlocking.h"
    #endif
    #ifdef TEMPERATURE_SENSOR_AVAILABLE
        #include "MCP9800.h"
    #endif
    #ifdef HEADPHONE_AMPLIFIER_AVAILABLE
        #include "LM49450.h"
    #endif


    // *****************************************************************************
    // Section: Constants
    // *****************************************************************************

    #define INFORMATION_LENGTH                  (16*2)
    #define IPOD_NAME_LENGTH                    20
    #define MAX_ALLOWED_CURRENT                 500     // The iPod will request 500mA.
    #define TEMPERATURE_READ_INTERVAL           (TICKS_PER_SECOND / 2)

    // *****************************************************************************
    // Section: Data Structures and Enumerations
    // *****************************************************************************

    // *****************************************************************************
    /* Application Status

    This structure contains information about the status of the application.
    */
    typedef struct
    {
        union
        {
            UINT8   value;
            struct
            {
                UINT8   overcurrentStateUSB     : 1;
            } bits;
        } flags;

    } APPLICATION_STATUS;


    // *****************************************************************************
    // Section: Internal Function Prototypes
    // *****************************************************************************

    void        CheckButtons( void );
    void        Initialize( void );
    void        InitializeHardware( void );
    void        MonitorPotentiometer( void );
    void        MonitorVBUS( void );
    void        RxInterrupt (void);


    //******************************************************************************
    // Section: Other Macros
    //******************************************************************************

    #define HIGH_BYTE(x)                    (((x) >> 8) & 0xFF)
    #define LOW_BYTE(x)                     ((x) & 0xFF)

#else

    ////////////////////////////////////////////////////////////////////////////////
    // Public

    extern INTERFACE_DATA          interfaceData;

#endif

////////////////////////////////////////////////////////////////////////////////
// Common

// *****************************************************************************
// Section: Constants and Enumerations
// *****************************************************************************

#define BLINK_RATE_ERROR                    100
#define BLINK_INFINITE                      0       // Blink the indication infinitely.

#if defined ( IPOD_USE_USB_HOST )
    #define WELCOME_STRING                  "iPod Demo1 v3.05 Dock iPod USB H"
#elif defined ( IPOD_USE_USB_DEVICE )
    #define WELCOME_STRING                  "iPod Demo1 v3.05 Dock iPod USB D"
#elif defined ( IPOD_USE_BLUETOOTH )
    #define WELCOME_STRING                  "iPod Demo1 v3.05 Dock iPod BT "
#else
    #define WELCOME_STRING                  "iPod Demo1 v3.05 Dock iPod UART "
#endif


// *****************************************************************************
/* Blink Patterns

These definitions are used by the BlinkIndication() routine to use the LEDs to
indicate status.
*/
typedef enum
{
    BLINK_PATTERN_ON_OFF,
    BLINK_PATTERN_CYLON,
    BLINK_PATTERN_SWEEP_LEFT,
    BLINK_PATTERN_SWEEP_RIGHT,
    BLINK_PATTERN_IN_OUT,
    BLINK_PATTERN_BROKEN_THIRDS
} BLINK_PATTERNS;


// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************

void        BlinkIndication( BLINK_PATTERNS pattern, UINT8 repetitions, UINT16 rate );

#if !defined( LCD_AVAILABLE )
    #define LCDInit()
    #define UpdateInformation(x)
    //void    UpdateInformation( const char * newString );
#else
    void    UpdateInformation( const char * newString );
#endif


#endif

