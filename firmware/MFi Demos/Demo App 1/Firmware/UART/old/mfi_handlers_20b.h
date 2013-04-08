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

// Created by the Microchip MFi Library SW320411 Configuration Utility, Version 3.05.00.00, 7/3/2012, 15:21:23

#ifndef _MFI_HANDLERS_H
#define _MFI_HANDLERS_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

#include "mfi_config.h"

#include "MFI/MFI_iPod.h"

#ifdef  _MFI_HANDLERS_C

    #include "MFI/MFI_Interface.h"
    #include "MFI/MFI_Identification.h"
    #include "MFI/MFI_Authentication.h"

#endif

void MFICB_CommandReceive( void );
void MFICB_CommandTransmit( void );
IPOD_COMMUNICATION_STATUS MFICB_GetStatus ( void );
UINT8 MFICB_Initialize ( void );
BOOL MFICB_IsiPodAttached( void );
BOOL MFICB_IsReadyForiAP( void );
BOOL MFICB_ProcessCompletion ( void );
void MFICB_ProcessiPodAttach( void );
void MFICB_ProcessiPodDetach ( void );
BOOL MFICB_ProcessPacket ( void );
void MFICB_ResetInputCommandBuffer( void );
void MFICB_Shutdown( void );
void MFICB_Tasks ( void );
void MFICB_TerminateReceive( void );

#endif

