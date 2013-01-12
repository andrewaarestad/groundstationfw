/******************************************************************************

File Name:       MFI_Interface.h
Dependencies:    None
Processor:       PIC16F1/PIC18/PIC24-dsPIC/PIC32
Compiler:        HiTech PICC/MPLAB C18/MPLAB C30/MPLAB C32
Company:         Microchip Technology, Inc.

Copyright © 2009-2012 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

Author          Date        Comments
--------------------------------------------------------------------------------
KO/SP/AF        03-Aug-2012 v3.05
KO/SP/AF        29-Feb-2012 v3.04
KO/SP/AF        02-Feb-2012 v3.03, Limited distribution
KO/SP/AF        02-Dec-2011 v3.02
KO/SP/AF        14-Sep-2011 v3.01
Kimberly Otten/
  Sergey Pavlov 26-May-2011 v3.00

*******************************************************************************/

#ifndef MFI_INTERFACE_H
#define MFI_INTERFACE_H

    // *****************************************************************************
    // Section: Function Prototypes
    // *****************************************************************************

    #if defined ( IPOD_USE_USB_HOST )
        void MFIIF_USBH_CommandReceive( void );
        void MFIIF_USBH_CommandTransmit( void );
        IPOD_COMMUNICATION_STATUS MFIIF_USBH_GetStatus( void );
        UINT8 MFIIF_USBH_Initialize( void );
        BOOL MFIIF_USBH_IsiPodAttached( void );
        BOOL MFIIF_USBH_IsReadyForiAP( void );
        void MFIIF_USBH_ProcessiPodAttach( void );
        void MFIIF_USBH_ProcessiPodDetach( void );
        void MFIIF_USBH_ResetInputCommandBuffer( void );
        void MFIIF_USBH_Shutdown( void );
        void MFIIF_USBH_Tasks( void );
        void MFIIF_USBH_TerminateReceive( void );
    #endif

    #if defined ( IPOD_USE_USB_DEVICE )
        void MFIIF_USBD_CommandReceive( void );
        void MFIIF_USBD_CommandTransmit( void );
        void MFIIF_USBD_EventCONFIGURED ( void );
void MFIIF_USBD_EventTRANSFER_TERMINATED ( BDT_ENTRY *p );
        BOOL MFIIF_USBD_USBCBTransfer ( BYTE endpointNumber );
        IPOD_COMMUNICATION_STATUS MFIIF_USBD_GetStatus( void );
        UINT8 MFIIF_USBD_Initialize( void );
        BOOL MFIIF_USBD_IsiPodAttached( void );
        BOOL MFIIF_USBD_IsReadyForiAP( void );
        void MFIIF_USBD_ProcessiPodAttach( void );
        void MFIIF_USBD_ProcessiPodDetach( void );
        void MFIIF_USBD_ResetInputCommandBuffer( void );
        void MFIIF_USBD_Shutdown( void );
        void MFIIF_USBD_Tasks( void );
        void MFIIF_USBD_TerminateReceive( void );
        void MFIIF_USBD_USBDisableInterrupts( void );
        void MFIIF_USBD_USBEnableInterrupts( void );
    #endif

    #if defined ( IPOD_USE_UART )
        void MFIIF_UART_CommandReceive( void );
        void MFIIF_UART_CommandTransmit( void );
        IPOD_COMMUNICATION_STATUS MFIIF_UART_GetStatus( void );
        UINT8 MFIIF_UART_Initialize( void );
        BOOL MFIIF_UART_IsiPodAttached( void );
        BOOL MFIIF_UART_IsReadyForiAP( void );
        void MFIIF_UART_ProcessiPodAttach( void );
        void MFIIF_UART_ProcessiPodDetach( void );
        void MFIIF_UART_ResetInputCommandBuffer( void );
        void MFIIF_UART_Shutdown( void );
        void MFIIF_UART_Tasks( void );
        void MFIIF_UART_TerminateReceive( void );
    #endif

    #if defined ( IPOD_BT_CANDLEDRAGON_CSR )
        void MFIIF_BTDS_CommandReceive( void );
        void MFIIF_BTDS_CommandTransmit( void );
        IPOD_COMMUNICATION_STATUS MFIIF_BTDS_GetStatus( void );
        UINT8 MFIIF_BTDS_Initialize( void );
        BOOL MFIIF_BTDS_IsiPodAttached( void );
        BOOL MFIIF_BTDS_IsReadyForiAP( void );
        void MFIIF_BTDS_ProcessiPodAttach( void );
        void MFIIF_BTDS_ProcessiPodDetach( void );
        void MFIIF_BTDS_ResetInputCommandBuffer( void );
        void MFIIF_BTDS_Shutdown( void );
        void MFIIF_BTDS_Tasks( void );
        void MFIIF_BTDS_TerminateReceive( void );
    #endif

#endif

