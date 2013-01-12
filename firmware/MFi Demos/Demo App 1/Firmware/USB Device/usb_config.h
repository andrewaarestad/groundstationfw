/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright © 2010-2012 Microchip Technology Inc.  All rights reserved.           
                                                                                
Microchip licenses to you the right to use, modify, copy and distribute Software
only when embedded on a Microchip microcontroller or digital signal controller  
that is integrated into your product or third party product (pursuant to the    
sublicense terms in the accompanying license agreement).                        
                                                                                
You should refer to the license agreement accompanying this Software for        
additional information regarding your rights and obligations.                   
                                                                                
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,   
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF        
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.  
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER       
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR    
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES         
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR     
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF        
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES          
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.     
                                                                                
********************************************************************************
*/

// Created by the Microchip MFi Library SW320411 Configuration Utility, Version 3.05.00.00, 7/3/2012, 15:21:33

#ifndef _usb_config_h_
#define _usb_config_h_

#if defined(__PIC24F__)
    #include <p24fxxxx.h>
#elif defined(__18CXX)
    #include <p18cxxx.h>
#elif defined(__PIC32MX__)
    #include <p32xxxx.h>
    #include "plib.h"
#endif

#define _USB_CONFIG_VERSION_MAJOR 3
#define _USB_CONFIG_VERSION_MINOR 5
#define _USB_CONFIG_VERSION_DOT   0
#define _USB_CONFIG_VERSION_BUILD 0

// ********** USB Device Information **********

// Required USB Configuration Options
#define USB_EP0_BUFF_SIZE          8
#define USB_SPEED_OPTION           USB_FULL_SPEED
#define USB_SUPPORT_DEVICE
#define USB_ENABLE_ALL_HANDLERS
#define USB_ENABLE_SUSPEND_HANDLER
#define USB_ENABLE_DEDICATED_TRANSFER_HANDLER

// <MFIConfig.USB_Device_Configuration>
// Application Specific USB Device Configuration Options - be sure to account for iAP requirements when adding functions.
#define USB_APPLICATION_VID        0x0000
#define USB_APPLICATION_PID        0x0000
#define USB_APPLICATION_CURRENT    100  // Current consumption in mA
#define USB_MAX_NUM_INT            1    // iAP requires 1
#define USB_MAX_EP_NUMBER          2    // iAP requires 2
#define USB_NUM_STRING_DESCRIPTORS 6    // iAP requires 6
#define USB_PING_PONG_MODE         USB_PING_PONG__FULL_PING_PONG
#define USB_INTERRUPT
#define USB_PULLUP_OPTION          USB_PULLUP_ENABLE
#define USB_TRANSCEIVER_OPTION     USB_INTERNAL_TRANSCEIVER
// </MFIConfig.USB_Device_Configuration>

#define USB_USER_DEVICE_DESCRIPTOR &device_dsc
#define USB_USER_DEVICE_DESCRIPTOR_INCLUDE extern ROM USB_DEVICE_DESCRIPTOR device_dsc

#define USB_USER_CONFIG_DESCRIPTOR USB_CD_Ptr
#define USB_USER_CONFIG_DESCRIPTOR_INCLUDE extern ROM BYTE *ROM USB_CD_Ptr[]

// Definitions for iAP interface and endpoint descriptors
#define USB_IAP_INTERRUPT_EP         1
#define USB_IAP_INTERRUPT_SIZE       8
#define USB_IAP_BULK_EP              2
#define USB_IAP_BULK_SIZE            64
#define USB_IAP_INTERFACE_ID         0x00

// <MFIConfig.USB_Device_Descriptor_Constants>
// Definitions for any additional interface and endpoint descriptors
// </MFIConfig.USB_Device_Descriptor_Constants>

#endif

