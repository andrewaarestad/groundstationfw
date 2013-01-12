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

// Created by the Microchip MFi Library SW320411 Configuration Utility, Version 3.05.00.00, 7/3/2012, 15:21:46

#define _MFI_HANDLERS_C

#include "mfi_handlers.h"

void MFICB_CommandReceive ( void )
{
    MFIIF_USBH_CommandReceive ();
}

void MFICB_CommandTransmit ( void )
{
    MFIIF_USBH_CommandTransmit ();
}

IPOD_COMMUNICATION_STATUS MFICB_GetStatus ( void )
{
    IPOD_COMMUNICATION_STATUS status;

    status = MFIIF_USBH_GetStatus ();
    if ( MFIID_IsIdentifying() )
    {
        status.identifying = 1;
    }
    if ( MFIAU_IsAuthenticating() )
    {
        status.authenticating = 1;
    }
    return status;
}

UINT8 MFICB_Initialize ( void )
{
    MFIIF_USBH_Initialize ();
    MFIID_Initialize ();
    if ( ! MFIAU_Initialize () )
    {
        return IPOD_CP_ERROR;
    }
    return IPOD_SUCCESS;
}

BOOL MFICB_IsiPodAttached ( void )
{
    return MFIIF_USBH_IsiPodAttached ();
}

BOOL MFICB_IsReadyForiAP ( void )
{
    return MFIIF_USBH_IsReadyForiAP ();
}

BOOL MFICB_ProcessCompletion ( void )
{
    if ( MFIID_ProcessCompletion() ) return TRUE;
    if ( MFIAU_ProcessCompletion() ) return TRUE;
    return FALSE;
}

void MFICB_ProcessiPodAttach ( void )
{
    MFIIF_USBH_ProcessiPodAttach ();
}

void MFICB_ProcessiPodDetach ( void )
{
    MFIID_ProcessiPodDetach ();
    MFIAU_ProcessiPodDetach ();
    MFIIF_USBH_ProcessiPodDetach ();
}

BOOL MFICB_ProcessPacket ( void )
{
    if ( MFIID_ProcessPacket() ) return TRUE;
    if ( MFIAU_ProcessPacket() ) return TRUE;
    return FALSE;
}

void MFICB_ResetInputCommandBuffer ( void )
{
    MFIIF_USBH_ResetInputCommandBuffer ();
}

void MFICB_Shutdown ( void )
{
    MFIIF_USBH_Shutdown ();
}

void MFICB_Tasks ( void )
{
    MFIIF_USBH_Tasks ();
    MFIID_Tasks ();
    MFIAU_Tasks ();
}

void MFICB_TerminateReceive ( void )
{
    MFIIF_USBH_TerminateReceive ();
}

BOOL MFI_USB_ApplicationDataEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size )
{
    if ( MFI_USB_Host_ApplicationDataEventHandler ( address, event, data, size ) ) return TRUE;
    // Send anything we could not handle to the application layer.
    return USB_ApplicationDataEventHandler( address, event, data, size );
}

BOOL MFI_USB_ApplicationEventHandler( UINT8 address, USB_EVENT event, void *data, UINT32 size )
{
    if ( MFI_USB_Host_ApplicationEventHandler( address, event, data, size ) ) return TRUE;
    // Send anything we could not handle to the application layer.
    return USB_ApplicationEventHandler( address, event, data, size );
}

