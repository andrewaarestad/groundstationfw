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

#define __USB_DESCRIPTORS_C

#include "./USB/usb.h"

#include "mfi_config.h"

// <MFIConfig.USB_Device_Header_Files>
// Additional USB Function header files required by the application
// </MFIConfig.USB_Device_Header_Files>

#if defined(__18CXX)
#pragma romdata
#endif

/* Device Descriptor */
ROM USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    USB_APPLICATION_VID,    // Vendor ID
    USB_APPLICATION_PID,    // Product ID
    0x0000,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x00,                   // No device serial number string
    0x01                    // Number of possible configurations
};

// <MFIConfig.USB_Configuration_Descriptor_Size>
#define USB_CONFIG_DESCRIPTOR_SIZE      (39 + 0)  // 39 bytes are required for the iAP portion
// </MFIConfig.USB_Configuration_Descriptor_Size>

/* Configuration 1 Descriptor */
ROM BYTE configDescriptor1[ USB_CONFIG_DESCRIPTOR_SIZE ]={
    /* Configuration Descriptor */
    0x09,                                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,           // CONFIGURATION descriptor type
    sizeof ( configDescriptor1 ) & 0xFF,    // Total length of the configuration descriptor
    sizeof ( configDescriptor1 ) >> 8,
    USB_MAX_NUM_INT,                        // Number of interfaces in this configuration
    1,                                      // Index value of this configuration
    3,                                      // Configuration string index
    _DEFAULT | _SELF,                       // Attributes, see usb_device.h
    (USB_APPLICATION_CURRENT/2),            // Max power consumption (2X mA)

    ////////////////////////////////////////////////////////////////////////////
    // iAP Interface

    /* USB Standard Interface Descriptor */
    0x09,                                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    USB_IAP_INTERFACE_ID,                   // Interface Number
    0,                                      // Alternate Setting Number
    3,                                      // Number of endpoints in this intf
    0xFF,                                   // Class code
    0xF0,                                   // Subclass code
    0x00,                                   // Protocol code
    4,                                      // Interface string index

        /* USB Standard Endpoint Descriptor - Interrupt Endpoint IN from the device */
        0x07,                               // Size of this descriptor in bytes (bLength)
        USB_DESCRIPTOR_ENDPOINT,            //Endpoint Descriptor
        USB_IAP_INTERRUPT_EP | USB_IN_EP,   //EndpointAddress
        _INTERRUPT,                         //Attributes
        USB_IAP_INTERRUPT_SIZE,0x00,        //size
        IPOD_POLLING_RATE,                  //Interval - for iPod, must be between 4 and 32 ms

        /* USB Standard Endpoint Descriptor - Bulk Endpoint OUT to the device */
        0x07,                               // Size of this descriptor in bytes (bLength)
        USB_DESCRIPTOR_ENDPOINT,            //Endpoint Descriptor
        USB_IAP_BULK_EP | USB_OUT_EP,       //EndpointAddress
        _BULK,                              //Attributes
        USB_IAP_BULK_SIZE,0x00,             //size
        1,                                  //Interval

        /* USB Standard Endpoint Descriptor - Bulk Endpoint IN from the device */
        0x07,                               // Size of this descriptor in bytes (bLength)
        USB_DESCRIPTOR_ENDPOINT,            //Endpoint Descriptor
        USB_IAP_BULK_EP | USB_IN_EP,        //EndpointAddress
        _BULK,                              //Attributes
        USB_IAP_BULK_SIZE,0x00,             //size
        1,                                  //Interval

    // <MFIConfig.USB_Additional_Interfaces>
    // Add any additional USB interfaces here
    // </MFIConfig.USB_Additional_Interfaces>
};

// <MFIConfig.USB_Additional_Configurations>
// Add any additional USB configurations here.  This is rare.
// </MFIConfig.USB_Additional_Configurations>

//Language code string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409}};

//Manufacturer string descriptor - must match Accessory Manufacturer
ROM struct{BYTE bLength;BYTE bDscType;WORD string[25];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{'M','i','c','r','o','c','h','i','p',' ','T','e','c','h','n','o','l','o','g','y',' ','I','n','c','.'}};

//Product string descriptor - must match Accessory Name
ROM struct{BYTE bLength;BYTE bDscType;WORD string[29];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'M','F','I',' ','A','c','c','e','s','s','o','r','y',' ','D','e','v','e','l','o','p','m','e','n','t',' ','K','i','t'}};

//Configuration string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[18];}sd003={
sizeof(sd003),USB_DESCRIPTOR_STRING,
{'M','a','i','n',' ','C','o','n','f','i','g','u','r','a','t','i','o','n'}};

//Interface string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[13];}sd004={
sizeof(sd004),USB_DESCRIPTOR_STRING,
{'i','A','P',' ','I','n','t','e','r','f','a','c','e'}};

// <MFIConfig.USB_Additional_String_Descriptors>
// Add any additional USB string descriptors here.  This must align with USB_NUM_STRING_DESCRIPTORS and USB_SD_Ptr.
// </MFIConfig.USB_Additional_String_Descriptors>

//Array of configuration descriptors
ROM BYTE *ROM USB_CD_Ptr[]=
{
    (ROM BYTE *ROM)&configDescriptor1
    // <MFIConfig.USB_Configuration_Descriptors_Array>
    // Add any additional USB configuration descriptors here.  This is rare.
    // </MFIConfig.USB_Configuration_Descriptors_Array>
};

//Array of string descriptors
ROM BYTE *ROM USB_SD_Ptr[ USB_NUM_STRING_DESCRIPTORS ]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002,
    (ROM BYTE *ROM)&sd003,
    (ROM BYTE *ROM)&sd004
    // <MFIConfig.USB_String_Descriptors_Array>
    // Add any additional USB string descriptors here.  This must align with USB_NUM_STRING_DESCRIPTORS and the definitions above.
    // </MFIConfig.USB_String_Descriptors_Array>
};

