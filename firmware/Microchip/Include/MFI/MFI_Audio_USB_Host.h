/******************************************************************************

File Name:       MFI_Audio_USB_Host.h
Dependencies:    None
Processor:       PIC18/PIC24-dsPIC/PIC32
Company:         Microchip Technology, Inc.

Copyright � 2009-2012 Microchip Technology Inc.  All rights reserved.

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

#ifndef MFI_AUDIO_USB_HOST_H
#define MFI_AUDIO_USB_HOST_H


// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************

void MFIDAH_Initialize ( void );
BOOL MFIDAH_IsPlaying ( void );
void MFIDAH_ProcessiPodDetach ( void );
BOOL MFIDAH_ProcessPacket( void );
BOOL MFIDAH_ProcessCompletion( void );
void MFIDAH_Tasks ( void );


#endif

