/******************************************************************************

Demo App 1

This demo runs on the following platforms:

    * iPod Accessory PICtail Plus with Explorer 16 and a PIC24FJ256GB110
    * iPod Accessory PICtail Plus with Explorer 16 and a PIC32MX460F512L
    * iPod Accessory Development Board for 8-bit PIC MCUs with a PIC18F87J11
    * Explorer 16 and a PIC24FJ256GB110 with a PICtail Plus card that includes
        a Flexipanel LM20 Bluetooth module and an Apple Coprocessor chip.

    * Explorer 16 and a Bluetooth PICtail Plus.  NOTE: This requires hardware
        modification.  If using a PIC32MX, the iPod PICtail Plus must be modified
        to move the Authentication Coprocessor nRESET to pin 1 of J2.  If using
        a PIC24F, usually either the iPod PICtail Plus or the Bluetooth PICtail
        Plus can be modified.  See the comments in HardareProfile PIC24 DotStack.h
        for more information.

This demo communicates with an app running on either on iPod touch or an iPhone
running OS3.

This demo will produce the following status indications on the LEDs:
    * LEDs flash one at a time, from one side to the other, then back, twice.  This
        indicates that communication with the iPod Authentication Coprocessor
        was successful, and the application is waiting for an iPod to dock.
    * All of the LEDs blink repetitively on and off at a rate of once per second.
        This indicates that there is a problem communicating with the iPod
        Authentication Coprocessor.  The blinking will continue until power is
        removed.
    * All of the LEDs blink repetitively on and off at a rate of twice per second.
        This indicates that there is a problem with the LM49450 Headphone Amplifier
        (iPod Accessory Development Board for 8-bit PIC MCUs only).  The blinking
        will continue until power is removed.
    * All of the LEDs blink repetitively on and off 5 times rapidly.  There is a
        problem with identifying or authenticating the iPod, or the iPod cannot
        be used with the accessory (for example, an iPod nano or classic).
    * The LEDs flash in an alternating pattern from one side to the other, twice.
        This indicates that an iPod has successfully identified, but has not yet
        been authenticated.
    * The LEDs flash in pairs from outside to inside to outside, 5 times.  The iPod
        has successfully authenticated the accessory, and the accessory is ready
        for use.

****************************** NOTE ******************************
Be sure the configuration file mfi_config.h reflect the correct iPod interface
(UART or USB) and the correct library for the desired device, interface, and
object file format (if applicable) is included in the project.  The project
may still build without errors if these are not set up correctly.

Hardware Limitations:

iPod Accessory PICtail Plus with Explorer 16 and a PIC24FJ256GB110
    * Switch S5 and LED D10 are both connected to RA7.  Therefore, switch S5
      will not toggle the display indication on the iPod.
    * Audio and video output are not available by default.
    * Headphone amplifier not available.

iPod Accessory PICtail Plus with Explorer 16 and a PIC32MX460F512L
    * Switches on the Explorer 16 are not supported.
    * Audio and video output are not available by default.
    * Headphone amplifier not available.

iPod Accessory Development Board for 8-bit PIC MCUs with a PIC18F87J11
    * No LCD display
    * Not all PIMs are supported.  For example, the PIC18FJ46J11 PIM is not
        recommended due to an errata concerning the I2C and RB4/RB5 on certain
        revisions of the device.
    * Only component video is supported.

******************************************************************************/
/******************************************************************************

File Name:       main.c
Dependencies:    USB Embedded Host library, MFI library
Processor:       PIC16F1/PIC18/PIC24-dsPIC/PIC32
Compiler:        HiTech PICC/MPLAB C18/MPLAB C30/MPLAB C32
Company:         Microchip Technology, Inc.

Copyright 2009-2012 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
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
  Sergey Pavlov 31-May-2011 v3.00
Kimberly Otten  24-Nov-2010 v2.05
Kimberly Otten  25-Oct-2010 v2.04

*******************************************************************************/

#define MAIN_C
#include "main.h"
#include "./groundStation.X/debugQueue.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

INTERFACE_DATA          interfaceData;
APPLICATION_STATUS      status;
DWORD                   timeLast10ms;
DWORD                   timeLast100ms;
DWORD                   timeLast1s;


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
BOOL USB_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size )
{
    // We are not supporting any other devices that generate data events.
    return FALSE;
}
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
BOOL USB_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size )
{
    switch( event )
    {
        // --------------------------------------------------------------------------
        // HID error events

        case EVENT_HID_BAD_REPORT_DESCRIPTOR:
            // This will occur before we know exactly what HID device has attached,
            // so we have to handle it here.
            UpdateInformation( "Cannot parse    report descript." );
            BlinkIndication( BLINK_PATTERN_ON_OFF, 5, BLINK_RATE_ERROR );
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
            else
            {
                // iPod requires too much current.
                return FALSE;
            }
            break;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            // The PIC24F with the Explorer 16 cannot turn off Vbus through software.
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
        case EVENT_UNSUPPORTED_DEVICE:
            // A USB device other than an iPod has attached.
            UpdateInformation( "Device is not an iPod" );
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
            UpdateInformation( "Cannot enumerate" );
            return TRUE;
            break;

        case EVENT_CLIENT_INIT_ERROR:
        case EVENT_OUT_OF_MEMORY:
        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            UpdateInformation( "Memory or init error" );
            return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}
#endif


//******************************************************************************
//******************************************************************************
// Internal Functions
//******************************************************************************
//******************************************************************************


/****************************************************************************
  Function:
    void BlinkIndication( BLINK_PATTERNS pattern, UINT8 repetitions, UINT16 rate )

  Description:
    This function blinks the LED's in a specific pattern, at the specified rate.
    It will blink them for either a specific number of repetitions, or infinitely.
    The LEDs are all turned off upon exit.

  Precondition:
    The LED TRIS bits must already be configured.

  Parameters:
    BLINK_PATTERNS pattern  - The blink pattern.
    UINT8 repetitions       - How many times to blink the pattern.  BLINK_INFINITE (0) =infinite
    UINT16 rate             - Number of milliseconds between pattern changes.

  Returns:
    None

  Remarks:
    This is a blocking function.
  ***************************************************************************/

void BlinkIndication( BLINK_PATTERNS pattern, UINT8 repetitions, UINT16 rate )
{
    UINT8   originalRepetitions;

    originalRepetitions = repetitions;

    // Initialize the LEDs based on the pattern selected.
    switch( pattern )
    {
        case BLINK_PATTERN_ON_OFF:
            LEDSet( 0x00 );
            repetitions *= 2;
            break;

        case BLINK_PATTERN_CYLON:
        case BLINK_PATTERN_SWEEP_LEFT:
        case BLINK_PATTERN_SWEEP_RIGHT:
        case BLINK_PATTERN_IN_OUT:
        case BLINK_PATTERN_BROKEN_THIRDS:
            break;
    }

    // Start the pattern.
    while ((originalRepetitions == BLINK_INFINITE) || (repetitions > 0))
    {
        switch( pattern )
        {
            case BLINK_PATTERN_ON_OFF:
                LEDSet ( LEDGet () ^ 0xFF );
                break;

            case BLINK_PATTERN_CYLON:
                LEDSet ( 0x01 );
                while ( LEDGet () != 0)
                {
                    DelayMs( rate );
                    LEDSet ( LEDGet () << 1 );
                }
                LEDSet ( 0x80 );
                while ( LEDGet () != 0)
                {
                    DelayMs( rate );
                    LEDSet ( LEDGet () >> 1 );
                }
                break;

            case BLINK_PATTERN_SWEEP_LEFT:
                LEDSet ( 0x01 );
                while ( LEDGet () != 0)
                {
                    DelayMs( rate );
                    LEDSet ( LEDGet () << 1 );
                }
                break;

            case BLINK_PATTERN_SWEEP_RIGHT:
                LEDSet ( 0x80 );
                while ( LEDGet () != 0)
                {
                    DelayMs( rate );
                    LEDSet ( LEDGet () >> 1 );
                }
                break;

            case BLINK_PATTERN_IN_OUT:
                LEDSet ( 0x81 );
                DelayMs( rate );
                LEDSet ( 0x42 );
                DelayMs( rate );
                LEDSet ( 0x24 );
                DelayMs( rate );
                LEDSet ( 0x18 );
                DelayMs( rate );
                LEDSet ( 0x24 );
                DelayMs( rate );
                LEDSet ( 0x42 );
                DelayMs( rate );
                LEDSet ( 0x81 );
                break;

            case BLINK_PATTERN_BROKEN_THIRDS:
                LEDSet ( 0x80 );
                DelayMs( rate );
                LEDSet ( 0x20 );
                DelayMs( rate );
                LEDSet ( 0x40 );
                DelayMs( rate );
                LEDSet ( 0x10 );
                DelayMs( rate );
                LEDSet ( 0x20 );
                DelayMs( rate );
                LEDSet ( 0x08 );
                DelayMs( rate );
                LEDSet ( 0x10 );
                DelayMs( rate );
                LEDSet ( 0x04 );
                DelayMs( rate );
                LEDSet ( 0x08 );
                DelayMs( rate );
                LEDSet ( 0x02 );
                DelayMs( rate );
                LEDSet ( 0x04 );
                DelayMs( rate );
                LEDSet ( 0x01 );
                break;
        }

        DelayMs( rate );
        repetitions--;
    }

    LEDSet ( 0x00 );
}

/****************************************************************************
****************************************************************************/

/****************************************************************************
  Function:
    void CheckButtons( void )

  Description:
    This function monitors the buttons.  Upon button press, the state of the
    buttons is sent to the iPod/iPhone.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    The buttons are not supported for PIC32 due to PIM remapping.
  ***************************************************************************/

void CheckButtons( void )
{
    static UINT8 buttonLatch = 0;

    // The buttons read 0 when they are pressed, which is backwards from what
    // we need.  Flip the bits, then mask off the ones we don't need.
    interfaceData.buttonState.value = (~ReadButtons()) & 0x0F;

    interfaceData.buttonChange.value |= interfaceData.buttonState.value ^ buttonLatch;
    interfaceData.buttonFlag.value |= interfaceData.buttonChange.value & interfaceData.buttonState.value;

    buttonLatch = interfaceData.buttonState.value;

    if (interfaceData.buttonChange.value != 0)
    {
        interfaceData.flags.bits.sendSwitchState = 1;
    }
}


/****************************************************************************
  Function:
     void Initialize( void )

  Description:
    This function initializes the entire system.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void Initialize( void )
{
    // Initialize the demo board.
    InitializeHardware();

    DebugUART_PrintString( "iPod Demo App 1\r\n\r\n" );
    UpdateInformation( "Initializing..." );

    memset( (UINT8 *)&interfaceData, 0, sizeof( INTERFACE_DATA ) );
    memset( (UINT8 *)&status, 0, sizeof( APPLICATION_STATUS ) );
    timeLast10ms    = 0;
    timeLast100ms   = 0;
    timeLast1s      = 0;

    // Initialize the various modules.
    iPxx_InitializeInformation();
    #if defined ( IPOD_BT_UART_MODULE )
        LM20_Initialize( (UINT8 *)mfi_RXBufferRaw, IPOD_BUFFER_LENGTH_INPUT );
    #elif defined ( IPOD_BT_CANDLEDRAGON_CSR )
        DotStack_Initialize();
    #endif
    #ifdef TEMPERATURE_SENSOR_AVAILABLE
        MCP9800_Initialize( I2C1 );
    #endif
    #ifdef HEADPHONE_AMPLIFIER_AVAILABLE
        if (LM49450_Initialize( I2C1 ) != LM49450_SUCCESS)
        {
            // Hold here.  Flash the LED's so we know there is a problem.
            BlinkIndication( BLINK_PATTERN_ON_OFF, BLINK_INFINITE, 250 );
        }
    #endif

    iPxx_Initialize( &interfaceData );

    // Do something silly with the LED's, so we know everything is functioning properly.
    BlinkIndication( BLINK_PATTERN_CYLON, 2, 20 );

    #if defined ( IPOD_BT_UART_MODULE )
        if (BUTTON_S3_IO == 0)
        {
            // If S3 is pressed, enter pairing mode without removing existing pairings.  LM20 only.
            interfaceData.flags.bits.pairingMode        = 1;
            interfaceData.flags.bits.removeAllPairings  = 1;
        }
        else if (BUTTON_S6_IO == 0)
        {
            // If S6 is pressed, remove existing pairings and enter pairing mode.  LM20 only.
            interfaceData.flags.bits.pairingMode        = 1;
        }
    #endif
}


/****************************************************************************
  Function:
     void InitializeHardware( void )

  Description:
    This function initializes board hardware, including the monitoring of the
    VBUS analog input.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    Since we really don't care how old the data is when we check the analog
    monitoring, we'll just wait here until the first sample is complete, then
    the rest of the monitoring can just use the buffered ADC values.
  ***************************************************************************/

void InitializeHardware( void )
{
    SysInit();

    // Configure the ADC.
    ConfigureAnalog();

    // Configure the iPod Detect input
    iPodDetectConfigure();

    // Configure the iPod communication interface.
    ConfigureiPodCommunicationInterface();

    // Configure the Accessory ID resistor, so the iPod will know what
    // communication interface we are using.
    AccessoryIDConfigure();
    AccessoryIDEnable();

    // Configure Accessory Detect, so the iPod will know that an
    // accessory has attached.
    AccessoryDetectConfigure();

    // Configure and set the authentication coprocessor nRESET line.
    ConfigureCPPins();

    // Configure the button switch inputs.
    ConfigureButtons();

    // Configure the outputs for the LEDs
    LEDInit();

    // Initialize the LCD display.
    #ifdef LCD_AVAILABLE
        LCDInit();
    #endif

    // Debug aids, not required for normal use.  May not be available for
    // all hardware platforms.
    DebugPinInitialize();
    ConfigureDebugUART();
    DebugUART_InitializeLogging();
    DebugUART_StartLogging();

    // Wait until the first conversion has time to occur.  After that, we
    // won't bother checking for completion - we'll just use the last value,
    // since we're just doing simple monitoring.  This time is more than
    // enough for the samples to complete.
    DelayMs( 1 );

    #if defined ( __18CXX ) || defined ( _PIC14E )
        // Enable interrupts.
        INTCONbits.PEIE     = 1; //enable peripheral interrupts
        INTCONbits.GIE      = 1; //enable interrupts globally
    #endif

    return;
}


/****************************************************************************
  Function:
    void MonitorPotentiometer( void )

  Description:
    This function monitors the potentiometer, and stores its current reading
    in a global variable.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    Since reading the ADC can take some time, we read it in the background
    and store it for later use elsewhere.
  ***************************************************************************/

void MonitorPotentiometer( void )
{
    #if defined ( _PIC14E )
        if (!ADCON0bits.GO_nDONE)
        {
            interfaceData.potentiometer.byte.HB = ADRESH;
            interfaceData.potentiometer.byte.LB = ADRESL;
            ADCON0bits.GO_nDONE = 1;
        }
    #elif defined ( __18CXX )
        if (!ADCON0bits.GO)
        {
            interfaceData.potentiometer.byte.HB = ADRESH;
            interfaceData.potentiometer.byte.LB = ADRESL;
            ADCON0bits.GO = 1;
        }
    #else
        if (AD1CON1bits.DONE)
        {
            interfaceData.potentiometer.byte.HB = HIGH_BYTE( ADC_READING_POTENTIOMETER );
            interfaceData.potentiometer.byte.LB = LOW_BYTE(  ADC_READING_POTENTIOMETER );
        }
    #endif
}


/****************************************************************************
  Function:
    void MonitorVBUS( void )

  Description:
    This routine monitors VBUS to check for overcurrent conditions.  The
    board has an analog input dedicated to monitoring Vbus.  The voltage on
    Vbus is divided by two and fed into an A/D channel.  The valid range for
    host Vbus is 4.75V - 5.25V.  If we are in an overcurrent condition, Vbus
    will be lower than 4.75V.  Full range on the A/D is 0x3FF for 3.3V.  So
    any value lower than the value calculated below on the Vbus monitor is
    overcurrent.  Otherwise, the current level is fine.

    The overcurrent condition is statically maintained.  It is reset if
    the voltage comes back up to 4.8V.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    TRUE    - An overcurrent situation exists. USB shut down.
    FALSE   - Normal USB operation.

  Remarks:
    Since Vbus monitoring is application-specific, it is the application's
    responsibility.  It is only required if the application will be certified.
    Otherwise, it's still a good idea, but not required.

    If we get an overcurrent, we must shut down immediately to avoid brownout
    or blackout.  We are not concerned about the age of the data, so we'll
    just check whatever value happens to be in the A/D buffer.

    If the DC/DC converter is being used, it can introduce enough noise on
    the 3.3v power that it trips the overcurrent.  Therefore, this routine
    will be used only if the DC/DC converter is not being used.
  ***************************************************************************/

void MonitorVBUS( void )
{
    #if defined( IPOD_USE_USB_HOST )
        while (!AD1CON1bits.DONE);  // Make sure the ADC reading is not in progress.
        if (ADC_READING_VBUS < OVERCURRENT_TRIP_READING)
        {
            if (!status.flags.bits.overcurrentStateUSB)
            {
                USBHostVbusEvent( EVENT_VBUS_OVERCURRENT, USB_ROOT_HUB, 0 );
                UpdateInformation( "*USB overcurrent detected*" );
                status.flags.bits.overcurrentStateUSB = TRUE;
            }
        }
        else if (ADC_READING_VBUS > OVERCURRENT_RESET_READING)
        {
            if (status.flags.bits.overcurrentStateUSB)
            {
                USBHostVbusEvent( EVENT_VBUS_POWER_AVAILABLE, USB_ROOT_HUB, 0 );
                UpdateInformation( "   Please dock       an iPod" );
            }
            status.flags.bits.overcurrentStateUSB = FALSE;
        }
   #endif
}



/****************************************************************************
  Function:
    void UpdateInformation( const char * newString )

  Description:
    This function updates the status line on the OLED.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
#if defined( LCD_AVAILABLE )
void UpdateInformation( const char * newString )
{
    UINT8   i;

    i = 0;
    while ((i < INFORMATION_LENGTH) && (*newString != 0))
    {
        LCDText[i] = *newString++;
        i++;
    }
    while (i < INFORMATION_LENGTH)
    {
        LCDText[i] = ' ';
        i++;
    }
    LCDText[i] = 0;

    // Update LCD display
    LCDUpdate();
}
#endif




//******************************************************************************
//******************************************************************************
//******************************************************************************
// Main
//******************************************************************************
//******************************************************************************
//******************************************************************************
//char i = 0;
//char uart2ReadBuffer[100];

char stringOneHzTick[] = "1Hz Tick";
char stringTest[] = "TestString";
char stringOneHzTickUart[] = "1Hz Tick\r\n";
char stringInitialized[] = "Initialized";
char stringUartRx[] = "UartRx";

//Lets the compiler know that this function is the ISR
void RxInterrupt (void)
{
    if(DataRdy2USART())
    {
        //addToQueue(stringUartRx);
        //putrs2USART("DataReady\r\n");
        while(DataRdy2USART())
        {
            interfaceData.uartData[interfaceData.uartLength] = Read2USART();
            ++interfaceData.uartLength;
        }
        //uart2ReadBuffer[i] = 0;
        //gets2USART(uart2ReadBuffer,100);
        PIR3bits.RC2IF = 0;
    }
    //Check for errors
    /*
    if(RCSTA2bits.OERR)
    {
        //Overrun error, clear it
        RCSTA2bits.CREN = 0;            // Clear any overflow error that occurred.
        RCSTA2bits.CREN = 1;
    }
    */
}

/*
void    UpdateInformation( const char * newString )
{
    putrs2USART(newString);
}
*/

#if defined ( __18CXX ) || defined ( _PIC14E )
void main( void )
#else
int main( void )
#endif
{
    int idx = 0;
    // Initialize the system.
    Initialize();

    addToQueue(stringInitialized);

    Open2USART(USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH, USART1_SPBRG);
    //RCONbits.IPEN = 1;      //Enable interrupt priority
    //INTCONbits.GIEH = 1;    //Enable all high priority interrupts


    // We are now ready to go.
    UpdateInformation( WELCOME_STRING );

    // Tell the iPod that an accessory is attached.
    AccessoryDetectEnable();

    // The iPod requires accessory identification within 3 seconds of attaching.
    // Therefore, be sure that this section of code is reached within approximately
    // 2 seconds from power up.
    IPR3bits.RC2IP = 1;      //Make receive interrupt high priority
    //HACK to turn on UART2 also
    //RCSTA2              = 0x90;
    //Nop();
    //Nop();

    //uart2ReadBuffer = 'Test First Message';
    while ( TRUE )
    {
        // This scheduler has not been optimized for maximum throughput, but
        // rather balanced operation.  If your accessory requires more data throughput
        // between the acccessory and the Apple Device, you may want to move
        // MFI_Tasks and iPxx_Tasks to the default case, so it is executed whenever
        // possible.
        
        if (( TickGet() - timeLast10ms ) > ( 10 * dwTicksPerMillisecond ))
        {
            timeLast10ms = TickGet();

            MFI_Tasks();
            iPxx_Tasks( &interfaceData );
            MonitorVBUS();
            
        }
        //100ms tick
        else if (( TickGet() - timeLast100ms ) > ( 100 * dwTicksPerMillisecond ))
        {
            timeLast100ms = TickGet();
            //putrs1USART("c");
            CheckButtons();
            if ( interfaceData.flags.bits.dataSessionOpen )
            {
                MonitorPotentiometer();
            }

            #if defined ( IPOD_USE_BLUETOOTH ) && defined ( IPOD_BT_UART_MODULE )
                if ( interfaceData.flags.bits.initializationDone )
                {
                    interfaceData.flags.bits.initializationDone = 0;
                    UpdateInformation( WELCOME_STRING );
                }
            #endif
        }
            
        else if (( TickGet() - timeLast1s ) > ( dwTicksPerSecond ))
        {
            timeLast1s = TickGet();

            if ( interfaceData.flags.bits.dataSessionOpen )
            {
                #ifdef TEMPERATURE_SENSOR_AVAILABLE
                    MCP9800_StartRead();
                #endif
            }
            //putrs2USART( "Hello World!\r\n" );

            addToQueue(stringOneHzTick);
            //addToQueue(stringTest);
            if(interfaceData.uartLength>0)
            {
                interfaceData.uartData[interfaceData.uartLength] = 0;
                addToQueue(interfaceData.uartData);
                //puts2USART(interfaceData.uartData);
                interfaceData.uartLength = 0;
            }
            //puts2USART(stringOneHzTickUart);
            //addToQueue("MoreQueueTest");
        }
        else
        {
            #ifdef TEMPERATURE_SENSOR_AVAILABLE
                MCP9800_Tasks( &interfaceData );
            #endif

            #ifdef HEADPHONE_AMPLIFIER_AVAILABLE
                LM49450_Tasks( &interfaceData );
            #endif
        }

        #ifdef IPOD_USE_BLUETOOTH
            #if defined ( IPOD_BT_UART_MODULE )
                LM20_Tasks( &interfaceData );
            #elif defined ( IPOD_BT_CANDLEDRAGON_CSR )
                DotStack_Tasks ();
            #endif
        #endif


    }
}





