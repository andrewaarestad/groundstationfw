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

#define _MFI_HANDLERS_C

#include "mfi_handlers.h"

void MFICB_CommandReceive ( void )
{
    MFIIF_USBD_CommandReceive ();
}

void MFICB_CommandTransmit ( void )
{
    MFIIF_USBD_CommandTransmit ();
}

IPOD_COMMUNICATION_STATUS MFICB_GetStatus ( void )
{
    IPOD_COMMUNICATION_STATUS status;

    status = MFIIF_USBD_GetStatus ();
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
    MFIIF_USBD_Initialize ();
    MFIID_Initialize ();
    if ( ! MFIAU_Initialize () )
    {
        return IPOD_CP_ERROR;
    }
    return IPOD_SUCCESS;
}

BOOL MFICB_IsiPodAttached ( void )
{
    return MFIIF_USBD_IsiPodAttached ();
}

BOOL MFICB_IsReadyForiAP ( void )
{
    return MFIIF_USBD_IsReadyForiAP ();
}

BOOL MFICB_ProcessCompletion ( void )
{
    if ( MFIID_ProcessCompletion() ) return TRUE;
    if ( MFIAU_ProcessCompletion() ) return TRUE;
    return FALSE;
}

void MFICB_ProcessiPodAttach ( void )
{
    MFIIF_USBD_ProcessiPodAttach ();
}

void MFICB_ProcessiPodDetach ( void )
{
    MFIID_ProcessiPodDetach ();
    MFIAU_ProcessiPodDetach ();
    MFIIF_USBD_ProcessiPodDetach ();
}

BOOL MFICB_ProcessPacket ( void )
{
    if ( MFIID_ProcessPacket() ) return TRUE;
    if ( MFIAU_ProcessPacket() ) return TRUE;
    return FALSE;
}

void MFICB_ResetInputCommandBuffer ( void )
{
    MFIIF_USBD_ResetInputCommandBuffer ();
}

void MFICB_Shutdown ( void )
{
    MFIIF_USBD_Shutdown ();
}

void MFICB_Tasks ( void )
{
    MFIIF_USBD_Tasks ();
    MFIID_Tasks ();
    MFIAU_Tasks ();
}

void MFICB_TerminateReceive ( void )
{
    MFIIF_USBD_TerminateReceive ();
}

void MFIIF_USBD_USBDisableInterrupts( void )
{
    USBDisableInterrupts();
}

void MFIIF_USBD_USBEnableInterrupts( void )
{
    USBEnableInterrupts();
}

////////////////////////////////////////////////////////////////////////////////
// USB Device Event Handler and Transfer Callback
//
// Add any application specific functionality between the appropriate tags. 
// All lines between the tags will be copied into regenerated configuration 
// configuration files.  DO NOT MODIFY the tags themselves. 
////////////////////////////////////////////////////////////////////////////////

BOOL USER_USB_CALLBACK_EVENT_HANDLER ( USB_EVENT event, void *pdata, WORD size )
{
    switch(event)
    {
        case EVENT_CONFIGURED:
            MFIIF_USBD_EventCONFIGURED ();
            // <MFIConfig.EVENT_CONFIGURED>
            // </MFIConfig.EVENT_CONFIGURED>
            break;

        case EVENT_SET_DESCRIPTOR:
            // <MFIConfig.EVENT_SET_DESCRIPTOR>
            // </MFIConfig.EVENT_SET_DESCRIPTOR>
            break;

        case EVENT_SOF:
            // <MFIConfig.EVENT_SOF>
            // </MFIConfig.EVENT_SOF>
            break;

        case EVENT_EP0_REQUEST:
            // <MFIConfig.EVENT_EP0_REQUEST>
            // </MFIConfig.EVENT_EP0_REQUEST>
            break;

        case EVENT_ALT_INTERFACE:
            // <MFIConfig.EVENT_ALT_INTERFACE>
            // </MFIConfig.EVENT_ALT_INTERFACE>
            break;

        case EVENT_TRANSFER:
            // TRAP - We need the USB Device Stack version that uses USBCBTransfer.
            while (1) {};
            break;

        case EVENT_SUSPEND:
            // <MFIConfig.EVENT_SUSPEND>
            USBCBSuspend ();
            // </MFIConfig.EVENT_SUSPEND>
            break;

        case EVENT_RESET:
            // <MFIConfig.EVENT_RESET>
            USBCBReset ();
            // </MFIConfig.EVENT_RESET>
            break;

        case EVENT_RESUME:
            // <MFIConfig.EVENT_RESUME>
            USBCBWakeFromSuspend ();
            // </MFIConfig.EVENT_RESUME>
            break;

        case EVENT_BUS_ERROR:
            // <MFIConfig.EVENT_BUS_ERROR>
            USBCBErrorHandler ();
            // </MFIConfig.EVENT_BUS_ERROR>
            break;

        case EVENT_TRANSFER_TERMINATED:
            MFIIF_USBD_EventTRANSFER_TERMINATED ( pdata );
            // <MFIConfig.EVENT_TRANSFER_TERMINATED>
            // </MFIConfig.EVENT_TRANSFER_TERMINATED>
            break;

       default:
           break;
    }

    return TRUE;
}

void USBCBTransfer ( BYTE endpointNumber )
{
    if ( MFIIF_USBD_USBCBTransfer ( endpointNumber ) == TRUE ) return;
    // <MFIConfig.USBCBTransfer>
    // </MFIConfig.USBCBTransfer>

    // Unhandled USB transfer - not necessarily a problem
}

