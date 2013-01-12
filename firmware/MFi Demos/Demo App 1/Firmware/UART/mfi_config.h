/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright � 2010-2012 Microchip Technology Inc.  All rights reserved.           
                                                                                
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

// Created by the Microchip MFi Library SW320411 Configuration Utility, Version 3.05.00.00, 7/3/2012, 15:21:23

#ifndef _MFI_CONFIG_H_
#define _MFI_CONFIG_H_

#define _MFI_CONFIG_VERSION_MAJOR 3
#define _MFI_CONFIG_VERSION_MINOR 5
#define _MFI_CONFIG_VERSION_DOT   0
#define _MFI_CONFIG_VERSION_BUILD 0

//------------------------------------------------------------------------------
// iPod Communication Interface

#define IPOD_USE_UART
//Using 10Mhz clock only 19200 works
//#define IPOD_UART_BAUD_RATE (57600ul)
#define IPOD_UART_BAUD_RATE (192000ul)
#define IPOD_COMMAND_PAYLOAD_SIZE_IN            136
#define IPOD_COMMAND_PAYLOAD_SIZE_OUT           136
#define IPOD_OPERATIONAL_PARAMETERS_BYTE0       0x00
#define IPOD_OPERATIONAL_PARAMETERS_BYTE1       0x60
#define IPOD_OPERATIONAL_PARAMETERS_BYTE2       0x04
#define IPOD_CP_INTERFACE                       0x20
//Original value
#define IPOD_CP_FREQUENCY                       (40000ul)
//HACK using external 8MHz clock
//#define IPOD_CP_FREQUENCY                       (80000ul)

#define IPOD_COMMAND_DELAY_IDL                  0
#define IPOD_COMMAND_DELAY                      0

//------------------------------------------------------------------------------
// Accessory Information

#define IPOD_ACCESSORY_NAME                     "MFI Accessory Development Kit"
#define IPOD_ACCESSORY_MANUFACTURER             "Microchip Technology Inc."
#define IPOD_ACCESSORY_MODEL_NUMBER             "DM240411 or DM240412"
#define IPOD_ACCESSORY_SERIAL_NUMBER            ""
#define IPOD_ACCESSORY_HARDWARE_VERSION_MAJOR   1
#define IPOD_ACCESSORY_HARDWARE_VERSION_MINOR   0
#define IPOD_ACCESSORY_HARDWARE_VERSION_REV     0
#define IPOD_ACCESSORY_SOFTWARE_VERSION_MAJOR   3
#define IPOD_ACCESSORY_SOFTWARE_VERSION_MINOR   5
#define IPOD_ACCESSORY_SOFTWARE_VERSION_REV     0

//------------------------------------------------------------------------------
// Lingoes, Capabilities, and Preferences

#define IPOD_ACCESSORY_LINGOES                  (IPOD_LINGO_FLAG_GENERAL)

#define IPOD_ACCESSORY_PREFERENCES_BYTE0        0x71
#define IPOD_ACCESSORY_PREFERENCES_BYTE1        0x00

#define IPOD_ACCESSORY_CAPABILITIES_BYTE0       0x05
#define IPOD_ACCESSORY_CAPABILITIES_BYTE1       0x02
#define IPOD_ACCESSORY_CAPABILITIES_BYTE2       0x00
#define IPOD_ACCESSORY_CAPABILITIES_BYTE3       0x00
#define IPOD_ACCESSORY_CAPABILITIES_BYTE4       0x00
#define IPOD_ACCESSORY_CAPABILITIES_BYTE5       0x00
#define IPOD_ACCESSORY_CAPABILITIES_BYTE6       0x00
#define IPOD_ACCESSORY_CAPABILITIES_BYTE7       0x00


//------------------------------------------------------------------------------
// Accessory RF Certifications

#define IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE0  0x00
#define IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE1  0x00
#define IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE2  0x00
#define IPOD_ACCESSORY_RF_CERTIFICATIONS_BYTE3  0x00

//------------------------------------------------------------------------------
// Device Options

#define IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE0     0x02
#define IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE1     0x00
#define IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE2     0x00
#define IPOD_ACCESSORY_DEVICE_OPTIONS_BYTE3     0x00


//------------------------------------------------------------------------------
// OS Application Information

#define IPOD_ACCESSORY_BUNDLE_SEED_ID           "ZH2665EYXS"
#define IPOD_ACCESSORY_BUNDLE_ID                "com.microchip.mfiDemo"
#define IPOD_ACCESSORY_EA_STRING_COUNT          1
#define IPOD_ACCESSORY_EA_STRINGS              "\x02" "com.microchip.ipodaccessory.demo1"


//------------------------------------------------------------------------------
// Extra USB Charging Current (USB only)

#define IPOD_USB_EXTRA_CURRENT_IN_SUSPEND       0
#define IPOD_USB_EXTRA_CURRENT_NOT_IN_SUSPEND   500


#endif

