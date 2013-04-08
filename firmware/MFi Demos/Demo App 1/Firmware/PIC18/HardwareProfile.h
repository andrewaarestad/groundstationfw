
/******************************************************************************

    Hardware Profile Configuration File

This file contains definitions of hardware-specific options.


Software License Agreement

The software supplied herewith by Microchip Technology Incorporated
(the “Company”) for its PICmicro® Microcontroller is intended and
supplied to you, the Company’s customer, for use solely and
exclusively on Microchip PICmicro Microcontroller products. The
software is owned by the Company and/or its supplier, and is
protected under applicable copyright laws. All rights are reserved.
Any use in violation of the foregoing restrictions may subject the
user to criminal sanctions under applicable laws, as well as to
civil liability for the breach of the terms and conditions of this
license.

THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

Author          Date    Comments
--------------------------------------------------------------------------------

*******************************************************************************/

#ifndef _HARDWARE_PROFILE_PIC18_H_
#define _HARDWARE_PROFILE_PIC18_H_


#include <p18cxxx.h>

//******************************************************************************
// Clock Information
//******************************************************************************

//Turn on PLL and increase the baudrate
//#define GetSystemClock()                    8000000UL
//#define GetSystemClock()                    12000000UL  // microchip mfi eval board
#define GetSystemClock()                    14745400UL  // andrew's board rev1

#define GetPeripheralClock()                (GetSystemClock() / 4)
#define GetInstructionClock()               (GetSystemClock() / 4)

#define I2C_Clock()                         GetInstructionClock()
//#define I2C_Clock()                         (3000000ul)


//******************************************************************************
// Configuration Bits
//******************************************************************************

#if defined( MAIN_C )
    #ifdef __DEBUG
        #pragma config FOSC     = HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config WDTEN    = OFF
        #pragma config WDTPS    = 32768
        #pragma config XINST    = OFF
        #pragma config CP0      = OFF
    #else
        #pragma config FOSC     = HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config WDTEN    = OFF
        #pragma config WDTPS    = 32768
        #pragma config XINST    = OFF
        #pragma config CP0      = ON
    #endif
#endif

//******************************************************************************
// Hardware Connections and Information
//******************************************************************************

//------------------------------------------------------------------------------
// General Hardware Setup

#define ConfigureClocks()
#define ConfigureDebugUART()

#define DebugPinInitialize()                { TRISJbits.TRISJ0 = 0; LATJbits.LATJ0 = 0; }
#define DebugPinClear()                     { LATJbits.LATJ0 = 0; }
#define DebugPinSet()                       { LATJbits.LATJ0 = 1; }
#define DebugPinToggle()                    { LATJbits.LATJ0 ^= 1; }


//------------------------------------------------------------------------------
// iPod General Information

#define IPOD_ACCESSORY_SELECT               LATBbits.LATB4      // Accessory Select, for enabling Accessory Detect and Accessory ID
#define IPOD_ACCESSORY_SELECT_TRIS          TRISBbits.TRISB4    // Accessory Select, for enabling Accessory Detect and Accessory ID
#define IPOD_ACCESSORY_POWER                PORTEbits.RE0       // Accessory Power indication from the iPod
#define IPOD_ACCESSORY_POWER_TRIS           TRISEbits.TRISE0    // Accessory Power indication from the iPod
#define IPOD_DETECT                         PORTBbits.RB5       // iPod Detect for the accessory
#define IPOD_DETECT_TRIS                    TRISBbits.TRISB5    // iPod Detect for the accessory

#define AccessoryDetectConfigure()          {                                       \
                                                IPOD_ACCESSORY_SELECT       = 0;    \
                                                IPOD_ACCESSORY_SELECT_TRIS  = 0;    \
                                            }
#define AccessoryDetectDisable()            { IPOD_ACCESSORY_SELECT = 0; }
#define AccessoryDetectEnable()             { IPOD_ACCESSORY_SELECT = 1; }

#define iPodDetectConfigure()               { IPOD_DETECT_TRIS = 1; }

// These are done automatically with the Accessory Detect macros.
#define AccessoryIDConfigure()
#define AccessoryIDDisable()
#define AccessoryIDEnable()

//------------------------------------------------------------------------------
// iPod Communication Interface Information

#if defined ( IPOD_USE_UART )
    // NOTE: For the PIC18 demo board with an 8MHz crystal, only 19200 baud is
    // suppported.  57600 will generate an error.
    #if (GetSystemClock() == 8000000) && (IPOD_UART_BAUD_RATE != 19200)
        #warning UART baud rate unsupported - using 19200
        #undef IPOD_UART_BAUD_RATE
        #define IPOD_UART_BAUD_RATE 19200
    #endif
    
    // General speed requirement checks
    #if (IPOD_UART_BAUD_RATE == 57600) && (GetSystemClock() < 12000000)
        #warning Demo App 1 will not function with these system clock and baud rate settings.
    #endif
    #if (IPOD_UART_BAUD_RATE == 57600) && (GetSystemClock() < 11059200)
        #warning The iPod will not authenticate with these system clock and baud rate settings.
    #endif
    #if (IPOD_UART_BAUD_RATE == 19200) && (GetSystemClock() < 7372800)
        #warning Demo App 1 will not function with these system clock and baud rate settings.
    #endif
    #if (IPOD_UART_BAUD_RATE == 19200) && (GetSystemClock() < 3686400)
        #warning The iPod will not authenticate with these system clock and baud rate settings.
    #endif
    
    #define USART1_RX_TRIS                      (TRISCbits.TRISC7)
    #define USART1_TX                           (LATCbits.LATC6)
    #define USART1_TX_TRIS                      (TRISCbits.TRISC6)
    #define USART1_BRGH                         1
    #define USART1_BAUDRATE                     IPOD_UART_BAUD_RATE
    
    #if (USART1_BRGH == 0)
        #define USART1_BRG_DIV                  64
    #elif (USART1_BRGH == 1)
        #define USART1_BRG_DIV                  16
    #else
        #error Invalid USART1_BRGH value.
    #endif
    #define USART1_SPBRG                        ((GetSystemClock() + (USART1_BRG_DIV/2*USART1_BAUDRATE)) / USART1_BRG_DIV / USART1_BAUDRATE - 1)
    
    #define BAUD_ACTUAL                         (GetSystemClock() / USART1_BRG_DIV / (USART1_SPBRG+1))
    #if (BAUD_ACTUAL > USART1_BAUDRATE)
        #define BAUD_ERROR                      (BAUD_ACTUAL-USART1_BAUDRATE)
    #else
        #define BAUD_ERROR                      (USART1_BAUDRATE-BAUD_ACTUAL)
    #endif
    #define BAUD1_ERROR_PERCENT_HUNDREDS        ((BAUD_ERROR*10000 + USART1_BAUDRATE/2) / USART1_BAUDRATE)
    
    #if (BAUD1_ERROR_PERCENT_HUNDREDS > 200)
        #error UART frequency error is worse than 2%
    #endif
    
    #define ConfigureiPodCommunicationInterface()   {                                   \
                                                        TXSTA1bits.BRGH = USART1_BRGH;  \
                                                        SPBRG1          = USART1_SPBRG; \
                                                    }
    
    #define ConfigureUARTPins()                     {                                   \
                                                        USART1_RX_TRIS  = 1;            \
                                                        USART1_TX       = 1;            \
                                                        USART1_TX_TRIS  = 0;            \
                                                    }
    #define TristateUARTPins()                      {                                   \
                                                        USART1_RX_TRIS  = 1;            \
                                                        USART1_TX_TRIS  = 1;            \
                                                    }
#else
    #define ConfigureiPodCommunicationInterface()
#endif


//------------------------------------------------------------------------------
// Analog Information

    // AN0 is analog, right justify, 8 Tad, Fosc/8.  Then turn it on.
#define ConfigureAnalog()                   {                                   \
                                                ANCON0              = 0xFE;     \
                                                ADCON0              = 0x00;     \
                                                ADCON1              = 0xA1;     \
                                                ADCON0bits.ADON     = 1;        \
                                            }


//------------------------------------------------------------------------------
// Buttons

#define BUTTON1_TRIS                        TRISBbits.TRISB0
#define BUTTON1_IO                          PORTBbits.RB0

#define BUTTON2_TRIS                        TRISBbits.TRISB1
#define BUTTON2_IO                          PORTBbits.RB1

#define BUTTON3_TRIS                        TRISBbits.TRISB2
#define BUTTON3_IO                          PORTBbits.RB2

#define BUTTON4_TRIS                        TRISBbits.TRISB3
#define BUTTON4_IO                          PORTBbits.RB3

#define ConfigureButtons()                  {                                   \
                                                BUTTON1_TRIS            = 1;    \
                                                BUTTON2_TRIS            = 1;    \
                                                BUTTON3_TRIS            = 1;    \
                                                BUTTON4_TRIS            = 1;    \
                                            }

#define ReadButtons()                       ((((((BUTTON1_IO << 1) | BUTTON2_IO) << 1) | BUTTON3_IO) << 1) | BUTTON4_IO)


//------------------------------------------------------------------------------
// LEDs

#define LEDS_TRIS                           TRISD
#define LEDS_IO                             LATD

#define LEDInit()                           {                       \
                                                LEDS_IO     = 0;    \
                                                LEDS_TRIS   = 0;    \
                                            }

#define LEDGet()                            LEDS_IO
#define LEDSet(x)                           {                       \
                                                LEDS_IO     = x;    \
                                            }

//------------------------------------------------------------------------------
// Authentication coprocessor signal pins

#define MFI_AUTH_NRESET_TRIS                (TRISCbits.TRISC0)
#define MFI_AUTH_NRESET                     (LATCbits.LATC0)

#define ConfigureCPPins()                   {                                       \
                                                MFI_AUTH_NRESET             = 0;    \
                                                MFI_AUTH_NRESET_TRIS        = 0;    \
                                            }

//------------------------------------------------------------------------------
// USB Device Definitions

#define self_power          0   //Host (bus) powered only design
#define USB_BUS_SENSE       1


//------------------------------------------------------------------------------
// Special Board Capabilities

//#define VIDEO_OUTPUT_AVAILABLE
//#define AUDIO_OUTPUT_AVAILABLE
//#define HEADPHONE_AMPLIFIER_AVAILABLE
//#define TEMPERATURE_SENSOR_AVAILABLE

#endif

