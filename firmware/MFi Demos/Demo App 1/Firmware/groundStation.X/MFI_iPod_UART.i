#line 1 "../../../../Microchip/MFI/MFI_iPod_UART.c"
#line 1 "../../../../Microchip/MFI/MFI_iPod_UART.c"

#line 12 "../../../../Microchip/MFI/MFI_iPod_UART.c"
 

#line 61 "../../../../Microchip/MFI/MFI_iPod_UART.c"
 

#line 64 "../../../../Microchip/MFI/MFI_iPod_UART.c"

#line 1 "../../../../Microchip/Include/GenericTypeDefs.h"

#line 46 "../../../../Microchip/Include/GenericTypeDefs.h"
 


#line 50 "../../../../Microchip/Include/GenericTypeDefs.h"

 
#line 53 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 55 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 56 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 57 "../../../../Microchip/Include/GenericTypeDefs.h"

#line 59 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 60 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 61 "../../../../Microchip/Include/GenericTypeDefs.h"

 
#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
 

#line 4 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"

typedef unsigned char wchar_t;


#line 10 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
 
typedef signed short int ptrdiff_t;
typedef signed short int ptrdiffram_t;
typedef signed short long int ptrdiffrom_t;


#line 20 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
 
typedef unsigned short int size_t;
typedef unsigned short int sizeram_t;
typedef unsigned short long int sizerom_t;


#line 34 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
 
#line 36 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"


#line 41 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
 
#line 43 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"

#line 45 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
#line 63 "../../../../Microchip/Include/GenericTypeDefs.h"
 

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;     
typedef enum _BIT { CLEAR = 0, SET } BIT;

#line 69 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 70 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 71 "../../../../Microchip/Include/GenericTypeDefs.h"

 
typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;

 
#line 80 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 82 "../../../../Microchip/Include/GenericTypeDefs.h"

 
typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
 
#line 89 "../../../../Microchip/Include/GenericTypeDefs.h"
typedef unsigned short long UINT24;
#line 91 "../../../../Microchip/Include/GenericTypeDefs.h"
typedef unsigned long int   UINT32;      
 
#line 94 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 96 "../../../../Microchip/Include/GenericTypeDefs.h"

typedef union
{
    UINT8 Val;
    struct
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union 
{
    UINT16 Val;
    UINT8 v[2] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;

 
#line 145 "../../../../Microchip/Include/GenericTypeDefs.h"
typedef union
{
    UINT24 Val;
    UINT8 v[3] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
    } bits;
} UINT24_VAL, UINT24_BITS;
#line 184 "../../../../Microchip/Include/GenericTypeDefs.h"

typedef union
{
    UINT32 Val;
    UINT16 w[2] ;
    UINT8  v[4] ;
    struct 
    {
        UINT16 LW;
        UINT16 HW;
    } word;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
        UINT8 MB;
    } byte;
    struct 
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
         UINT8 b24:1;
         UINT8 b25:1;
         UINT8 b26:1;
         UINT8 b27:1;
         UINT8 b28:1;
         UINT8 b29:1;
         UINT8 b30:1;
         UINT8 b31:1;
    } bits;
} UINT32_VAL;

 
#line 246 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 333 "../../../../Microchip/Include/GenericTypeDefs.h"

 

 
typedef void                    VOID;

typedef char                    CHAR8;
typedef unsigned char           UCHAR8;

typedef unsigned char           BYTE;                            
typedef unsigned short int      WORD;                            
typedef unsigned long           DWORD;                           
 

typedef unsigned long long      QWORD;                           
typedef signed char             CHAR;                            
typedef signed short int        SHORT;                           
typedef signed long             LONG;                            
 

typedef signed long long        LONGLONG;                        
typedef union
{
    BYTE Val;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    WORD Val;
    BYTE v[2] ;
    struct 
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union
{
    DWORD Val;
    WORD w[2] ;
    BYTE v[4] ;
    struct 
    {
        WORD LW;
        WORD HW;
    } word;
    struct 
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct 
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
    } bits;
} DWORD_VAL;

 
typedef union
{
    QWORD Val;
    DWORD d[2] ;
    WORD w[4] ;
    BYTE v[8] ;
    struct 
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct 
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
         BYTE b32:1;
         BYTE b33:1;
         BYTE b34:1;
         BYTE b35:1;
         BYTE b36:1;
         BYTE b37:1;
         BYTE b38:1;
         BYTE b39:1;
         BYTE b40:1;
         BYTE b41:1;
         BYTE b42:1;
         BYTE b43:1;
         BYTE b44:1;
         BYTE b45:1;
         BYTE b46:1;
         BYTE b47:1;
         BYTE b48:1;
         BYTE b49:1;
         BYTE b50:1;
         BYTE b51:1;
         BYTE b52:1;
         BYTE b53:1;
         BYTE b54:1;
         BYTE b55:1;
         BYTE b56:1;
         BYTE b57:1;
         BYTE b58:1;
         BYTE b59:1;
         BYTE b60:1;
         BYTE b61:1;
         BYTE b62:1;
         BYTE b63:1;
    } bits;
} QWORD_VAL;

#line 548 "../../../../Microchip/Include/GenericTypeDefs.h"

#line 550 "../../../../Microchip/Include/GenericTypeDefs.h"
#line 65 "../../../../Microchip/MFI/MFI_iPod_UART.c"

#line 1 "../../../../Microchip/Include/Compiler.h"

#line 56 "../../../../Microchip/Include/Compiler.h"
 

#line 59 "../../../../Microchip/Include/Compiler.h"


#line 62 "../../../../Microchip/Include/Compiler.h"
	
#line 64 "../../../../Microchip/Include/Compiler.h"
#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"

#line 3 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"

#line 5 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 7 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 9 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 11 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 13 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 15 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 17 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 19 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 21 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 23 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 25 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 27 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 29 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 31 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 33 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 35 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 37 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 39 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 41 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 43 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 45 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 47 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 49 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 51 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 53 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 55 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 57 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 59 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 61 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 63 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 65 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 67 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 69 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 71 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 73 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 75 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 77 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 79 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 81 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 83 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 85 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 87 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 89 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 91 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 93 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 95 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 97 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 99 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 101 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 103 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 105 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 107 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 109 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 111 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 113 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 115 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 117 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 119 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 121 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 123 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 125 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 127 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 129 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 131 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 133 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 135 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 137 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 139 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 141 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 143 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 145 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 147 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 149 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 151 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 153 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 155 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 157 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 159 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 161 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 163 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 165 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 167 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 169 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 171 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 173 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 175 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 177 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 179 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 181 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 183 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 185 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 187 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 189 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 191 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 193 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 195 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 197 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 199 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 201 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 203 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 205 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 207 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 209 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 211 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 213 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 215 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 217 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 219 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 221 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 223 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 225 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 227 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 229 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 231 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 233 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 235 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 237 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 239 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 241 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 243 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 245 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 247 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 249 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 251 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 253 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 255 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 257 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 259 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 261 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 263 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 265 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 267 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 269 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 271 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 273 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 275 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 277 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 279 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 281 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 283 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 285 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 287 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 289 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 291 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 293 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 295 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 297 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 299 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 301 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 303 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 305 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 307 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 309 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 311 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 313 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 315 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 317 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 319 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 321 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 323 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 325 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 327 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 329 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 331 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 333 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 335 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 337 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 339 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 341 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 343 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 345 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 347 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 349 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 351 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 353 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 355 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 357 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 359 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 361 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 363 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 365 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 367 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 369 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 371 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 373 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 375 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 377 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 379 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 381 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 383 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 385 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 387 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 389 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 391 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 393 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 395 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 397 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 399 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 401 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 403 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 405 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 407 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 409 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 411 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 413 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 415 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 417 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 419 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 421 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 423 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 425 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 427 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 429 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 431 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 433 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 435 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 437 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 439 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 441 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 443 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 445 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 447 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 449 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 451 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"

#line 5 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
 


#line 9 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"

extern volatile far  unsigned            PMSTAT;
extern volatile far  unsigned char       PMSTATL;
extern volatile far  struct {
  unsigned OB0E:1;
  unsigned OB1E:1;
  unsigned OB2E:1;
  unsigned OB3E:1;
  unsigned :2;
  unsigned OBUF:1;
  unsigned OBE:1;
} PMSTATLbits;
extern volatile far  unsigned char       PMSTATH;
extern volatile far  struct {
  unsigned IB0F:1;
  unsigned IB1F:1;
  unsigned IB2F:1;
  unsigned IB3F:1;
  unsigned :2;
  unsigned IBOV:1;
  unsigned IBF:1;
} PMSTATHbits;
extern volatile far  unsigned char       PMEL;
extern volatile far  union {
  struct {
    unsigned PTENL:8;
  };
  struct {
    unsigned PTEN0:1;
    unsigned PTEN1:1;
    unsigned PTEN2:1;
    unsigned PTEN3:1;
    unsigned PTEN4:1;
    unsigned PTEN5:1;
    unsigned PTEN6:1;
    unsigned PTEN7:1;
  };
} PMELbits;
extern volatile far  unsigned            PMEN;
extern volatile far  unsigned char       PMEH;
extern volatile far  union {
  struct {
    unsigned PTENH:8;
  };
  struct {
    unsigned PTEN8:1;
    unsigned PTEN9:1;
    unsigned PTEN10:1;
    unsigned PTEN11:1;
    unsigned PTEN12:1;
    unsigned PTEN13:1;
    unsigned PTEN14:1;
    unsigned PTEN15:1;
  };
} PMEHbits;
extern volatile far  unsigned            PMDIN2;
extern volatile far  unsigned char       PMDIN2L;
extern volatile far  unsigned char       PMDIN2H;
extern volatile near unsigned            PMDOUT2;
extern volatile near unsigned char       PMDOUT2L;
extern volatile near unsigned char       PMDOUT2H;
extern volatile near unsigned            PMMODE;
extern volatile near unsigned char       PMMODEL;
extern volatile near union {
  struct {
    unsigned WAITE:2;
    unsigned WAITM:4;
    unsigned WAITB:2;
  };
  struct {
    unsigned WAITE0:1;
    unsigned WAITE1:1;
    unsigned WAITM0:1;
    unsigned WAITM1:1;
    unsigned WAITM2:1;
    unsigned WAITM3:1;
    unsigned WAITB0:1;
    unsigned WAITB1:1;
  };
} PMMODELbits;
extern volatile near unsigned char       PMMODEH;
extern volatile near union {
  struct {
    unsigned MODE:2;
    unsigned MODE16:1;
    unsigned INCM:2;
    unsigned IRQM:2;
    unsigned BUSY:1;
  };
  struct {
    unsigned MODE0:1;
    unsigned MODE1:1;
    unsigned :1;
    unsigned INCM0:1;
    unsigned INCM1:1;
    unsigned IRQM0:1;
    unsigned IRQM1:1;
  };
} PMMODEHbits;
extern volatile near unsigned            PMCON;
extern volatile near unsigned char       PMCONL;
extern volatile near struct {
  unsigned RDSP:1;
  unsigned WRSP:1;
  unsigned BEP:1;
  unsigned CS1P:1;
  unsigned CS2P:1;
  unsigned ALP:1;
  unsigned CSF0:1;
  unsigned CSF1:1;
} PMCONLbits;
extern volatile near unsigned char       PMCONH;
extern volatile near struct {
  unsigned PTRDEN:1;
  unsigned PTWREN:1;
  unsigned PTBEEN:1;
  unsigned ADRMUX0:1;
  unsigned ADRMUX1:1;
  unsigned PSIDL:1;
  unsigned :1;
  unsigned PMPEN:1;
} PMCONHbits;
extern volatile near unsigned            PMDIN1;
extern volatile near unsigned char       PMDIN1L;
extern volatile near unsigned char       PMDIN1H;
extern volatile near unsigned            PMADDR;
extern volatile near unsigned char       PMADDRL;
extern volatile near unsigned            PMDOUT1;
extern volatile near unsigned char       PMDOUT1L;
extern volatile near unsigned char       PMADDRH;
extern volatile near struct {
  unsigned ADDRH:6;
  unsigned CS1:1;
  unsigned CS2:1;
} PMADDRHbits;
extern volatile near unsigned char       PMDOUT1H;
extern volatile near unsigned char       CMSTAT;
extern volatile near struct {
  unsigned COUT1:1;
  unsigned COUT2:1;
} CMSTATbits;
extern volatile near unsigned char       CMSTATUS;
extern volatile near struct {
  unsigned COUT1:1;
  unsigned COUT2:1;
} CMSTATUSbits;
extern volatile near unsigned char       SSP2CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSP2CON2bits;
extern volatile near unsigned char       SSP2CON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSP2CON1bits;
extern volatile near unsigned char       SSP2STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSP2STATbits;
extern volatile near unsigned char       SSP2ADD;
extern volatile near unsigned char       SSP2MSK;
extern volatile near struct {
  unsigned MSK0:1;
  unsigned MSK1:1;
  unsigned MSK2:1;
  unsigned MSK3:1;
  unsigned MSK4:1;
  unsigned MSK5:1;
  unsigned MSK6:1;
  unsigned MSK7:1;
} SSP2MSKbits;
extern volatile near unsigned char       SSP2BUF;
extern volatile near unsigned char       CCP5CON;
extern volatile near union {
  struct {
    unsigned CCP5M:4;
    unsigned DC5B:2;
  };
  struct {
    unsigned CCP5M0:1;
    unsigned CCP5M1:1;
    unsigned CCP5M2:1;
    unsigned CCP5M3:1;
    unsigned DC5B0:1;
    unsigned DC5B1:1;
  };
  struct {
    unsigned :4;
    unsigned DCCP5Y:1;
    unsigned DCCP5X:1;
  };
} CCP5CONbits;
extern volatile near unsigned            CCPR5;
extern volatile near unsigned char       CCPR5L;
extern volatile near unsigned char       CCPR5H;
extern volatile near unsigned char       CCP4CON;
extern volatile near union {
  struct {
    unsigned CCP4M:4;
    unsigned DC4B:2;
  };
  struct {
    unsigned CCP4M0:1;
    unsigned CCP4M1:1;
    unsigned CCP4M2:1;
    unsigned CCP4M3:1;
    unsigned DC4B0:1;
    unsigned DC4B1:1;
  };
  struct {
    unsigned :4;
    unsigned DCCP4Y:1;
    unsigned DCCP4X:1;
  };
} CCP4CONbits;
extern volatile near unsigned            CCPR4;
extern volatile near unsigned char       CCPR4L;
extern volatile near unsigned char       CCPR4H;
extern volatile near unsigned char       T4CON;
extern volatile near union {
  struct {
    unsigned T4CKPS:2;
    unsigned TMR4ON:1;
    unsigned T4OUTPS:4;
  };
  struct {
    unsigned T4CKPS0:1;
    unsigned T4CKPS1:1;
    unsigned :1;
    unsigned T4OUTPS0:1;
    unsigned T4OUTPS1:1;
    unsigned T4OUTPS2:1;
    unsigned T4OUTPS3:1;
  };
} T4CONbits;
extern volatile near unsigned char       CVRCON;
extern volatile near union {
  struct {
    unsigned CVR:4;
    unsigned CVRSS:1;
    unsigned CVRR:1;
    unsigned CVROE:1;
    unsigned CVREN:1;
  };
  struct {
    unsigned CVR0:1;
    unsigned CVR1:1;
    unsigned CVR2:1;
    unsigned CVR3:1;
  };
} CVRCONbits;
extern volatile near unsigned char       PR4;
extern volatile near unsigned char       TMR4;
extern volatile near unsigned char       T3CON;
extern volatile near union {
  struct {
    unsigned TMR3ON:1;
    unsigned TMR3CS:1;
    unsigned NOT_T3SYNC:1;
    unsigned T3CCP1:1;
    unsigned T3CKPS:2;
    unsigned T3CCP2:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T3SYNC:1;
    unsigned :1;
    unsigned T3CKPS0:1;
    unsigned T3CKPS1:1;
  };
  struct {
    unsigned :2;
    unsigned T3INSYNC:1;
  };
} T3CONbits;
extern volatile near unsigned char       TMR3L;
extern volatile near unsigned char       TMR3H;
extern volatile near unsigned char       BAUDCON2;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
    unsigned DTRXP:1;
    unsigned RCMT:1;
  };
} BAUDCON2bits;
extern volatile near unsigned char       SPBRGH2;
extern volatile near unsigned char       BAUDCON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
    unsigned DTRXP:1;
    unsigned RCMT:1;
  };
} BAUDCONbits;
extern volatile near unsigned char       BAUDCON1;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned SCKP:1;
    unsigned DTRXP:1;
    unsigned RCMT:1;
  };
} BAUDCON1bits;
extern volatile near unsigned char       SPBRGH1;
extern volatile near unsigned char       PORTA;
extern volatile near union {
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
    unsigned RA7:1;
  };
  struct {
    unsigned AN0:1;
    unsigned AN1:1;
    unsigned AN2:1;
    unsigned AN3:1;
    unsigned T0CKI:1;
    unsigned AN4:1;
    unsigned OSC2:1;
  };
  struct {
    unsigned :2;
    unsigned VREFM:1;
    unsigned VREFP:1;
    unsigned PMD5:1;
    unsigned PMD4:1;
    unsigned CLKO:1;
  };
} PORTAbits;
extern volatile near unsigned char       PORTB;
extern volatile near union {
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
  struct {
    unsigned INT0:1;
    unsigned INT1:1;
    unsigned INT2:1;
    unsigned INT3:1;
    unsigned KBI0:1;
    unsigned KBI1:1;
    unsigned KBI2:1;
    unsigned KBI3:1;
  };
  struct {
    unsigned :1;
    unsigned PMA4:1;
    unsigned PMA3:1;
    unsigned PMA2:1;
    unsigned PMA1:1;
    unsigned PMA0:1;
  };
  struct {
    unsigned FLT0:1;
    unsigned :2;
    unsigned CCP2:1;
    unsigned :2;
    unsigned PGC:1;
    unsigned PGD:1;
  };
} PORTBbits;
extern volatile near unsigned char       PORTC;
extern volatile near union {
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
  struct {
    unsigned T1OSO:1;
    unsigned T1OSI:1;
    unsigned CCP1:1;
    unsigned SCK:1;
    unsigned SDI:1;
    unsigned SDO:1;
    unsigned TX:1;
    unsigned RX:1;
  };
  struct {
    unsigned T13CKI:1;
    unsigned CCP2:1;
    unsigned :1;
    unsigned SCL:1;
    unsigned SDA:1;
    unsigned :1;
    unsigned CK:1;
    unsigned DT:1;
  };
} PORTCbits;
extern volatile near unsigned char       PORTD;
extern volatile near union {
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
  struct {
    unsigned PMD0:1;
    unsigned PMD1:1;
    unsigned PMD2:1;
    unsigned PMD3:1;
    unsigned PMD4:1;
    unsigned PMD5:1;
    unsigned PMD6:1;
    unsigned PMD7:1;
  };
  struct {
    unsigned AD0:1;
    unsigned AD1:1;
    unsigned AD2:1;
    unsigned AD3:1;
    unsigned AD4:1;
    unsigned AD5:1;
    unsigned AD6:1;
    unsigned AD7:1;
  };
  struct {
    unsigned :5;
    unsigned SDA2:1;
    unsigned SCL2:1;
    unsigned SS2:1;
  };
  struct {
    unsigned :4;
    unsigned SDO2:1;
    unsigned SDI2:1;
    unsigned SCK2:1;
  };
} PORTDbits;
extern volatile near unsigned char       PORTE;
extern volatile near union {
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
    unsigned RE3:1;
    unsigned RE4:1;
    unsigned RE5:1;
    unsigned RE6:1;
    unsigned RE7:1;
  };
  struct {
    unsigned AD8:1;
    unsigned AD9:1;
    unsigned AD10:1;
    unsigned AD11:1;
    unsigned AD12:1;
    unsigned AD13:1;
    unsigned AD14:1;
    unsigned AD15:1;
  };
  struct {
    unsigned PMRD:1;
    unsigned PMWR:1;
    unsigned PMBE:1;
    unsigned PMA13:1;
    unsigned PMA12:1;
    unsigned PMA11:1;
    unsigned PMA10:1;
    unsigned PMA9:1;
  };
  struct {
    unsigned :3;
    unsigned REFO:1;
    unsigned :3;
    unsigned CCP2:1;
  };
} PORTEbits;
extern volatile near unsigned char       PORTF;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned RF1:1;
    unsigned RF2:1;
    unsigned RF3:1;
    unsigned RF4:1;
    unsigned RF5:1;
    unsigned RF6:1;
    unsigned RF7:1;
  };
  struct {
    unsigned :1;
    unsigned AN6:1;
    unsigned AN7:1;
    unsigned AN8:1;
    unsigned AN9:1;
    unsigned AN10:1;
    unsigned AN11:1;
    unsigned SS:1;
  };
  struct {
    unsigned :5;
    unsigned CVREF:1;
  };
  struct {
    unsigned :1;
    unsigned C2OUT:1;
    unsigned C1OUT:1;
    unsigned C2INB:1;
    unsigned C2INA:1;
    unsigned C1INB:1;
    unsigned C1INA:1;
  };
  struct {
    unsigned :2;
    unsigned PMA5:1;
    unsigned :2;
    unsigned PMD2:1;
    unsigned PMD1:1;
    unsigned PMD0:1;
  };
} PORTFbits;
extern volatile near unsigned char       PORTG;
extern volatile near union {
  struct {
    unsigned RG0:1;
    unsigned RG1:1;
    unsigned RG2:1;
    unsigned RG3:1;
    unsigned RG4:1;
    unsigned RJPU:1;
    unsigned REPU:1;
    unsigned RDPU:1;
  };
  struct {
    unsigned CCP3:1;
    unsigned TX2:1;
    unsigned RX2:1;
    unsigned CCP4:1;
    unsigned CCP5:1;
  };
  struct {
    unsigned :1;
    unsigned CK2:1;
    unsigned DT2:1;
  };
  struct {
    unsigned PMA8:1;
    unsigned PMA7:1;
    unsigned PMA6:1;
    unsigned PMCS1:1;
    unsigned PMCS2:1;
  };
} PORTGbits;
extern volatile near unsigned char       PORTH;
extern volatile near union {
  struct {
    unsigned RH0:1;
    unsigned RH1:1;
    unsigned RH2:1;
    unsigned RH3:1;
    unsigned RH4:1;
    unsigned RH5:1;
    unsigned RH6:1;
    unsigned RH7:1;
  };
  struct {
    unsigned A16:1;
    unsigned A17:1;
    unsigned A18:1;
    unsigned A19:1;
    unsigned AN12:1;
    unsigned AN13:1;
    unsigned AN14:1;
    unsigned AN15:1;
  };
  struct {
    unsigned :2;
    unsigned PMD7:1;
    unsigned PMD6:1;
    unsigned PMD3:1;
    unsigned PMBE:1;
    unsigned PMRD:1;
    unsigned PMWR:1;
  };
  struct {
    unsigned :4;
    unsigned C2INC:1;
    unsigned C2IND:1;
    unsigned C1INC:1;
  };
} PORTHbits;
extern volatile near unsigned char       PORTJ;
extern volatile near union {
  struct {
    unsigned RJ0:1;
    unsigned RJ1:1;
    unsigned RJ2:1;
    unsigned RJ3:1;
    unsigned RJ4:1;
    unsigned RJ5:1;
    unsigned RJ6:1;
    unsigned RJ7:1;
  };
  struct {
    unsigned ALE:1;
    unsigned OE:1;
    unsigned WRL:1;
    unsigned WRH:1;
    unsigned BA0:1;
    unsigned CE:1;
    unsigned LB:1;
    unsigned UB:1;
  };
} PORTJbits;
extern volatile near unsigned char       LATA;
extern volatile near struct {
  unsigned LATA0:1;
  unsigned LATA1:1;
  unsigned LATA2:1;
  unsigned LATA3:1;
  unsigned LATA4:1;
  unsigned LATA5:1;
  unsigned LATA6:1;
  unsigned LATA7:1;
} LATAbits;
extern volatile near unsigned char       LATB;
extern volatile near struct {
  unsigned LATB0:1;
  unsigned LATB1:1;
  unsigned LATB2:1;
  unsigned LATB3:1;
  unsigned LATB4:1;
  unsigned LATB5:1;
  unsigned LATB6:1;
  unsigned LATB7:1;
} LATBbits;
extern volatile near unsigned char       LATC;
extern volatile near struct {
  unsigned LATC0:1;
  unsigned LATC1:1;
  unsigned LATC2:1;
  unsigned LATC3:1;
  unsigned LATC4:1;
  unsigned LATC5:1;
  unsigned LATC6:1;
  unsigned LATC7:1;
} LATCbits;
extern volatile near unsigned char       LATD;
extern volatile near struct {
  unsigned LATD0:1;
  unsigned LATD1:1;
  unsigned LATD2:1;
  unsigned LATD3:1;
  unsigned LATD4:1;
  unsigned LATD5:1;
  unsigned LATD6:1;
  unsigned LATD7:1;
} LATDbits;
extern volatile near unsigned char       LATE;
extern volatile near struct {
  unsigned LATE0:1;
  unsigned LATE1:1;
  unsigned LATE2:1;
  unsigned LATE3:1;
  unsigned LATE4:1;
  unsigned LATE5:1;
  unsigned LATE6:1;
  unsigned LATE7:1;
} LATEbits;
extern volatile near unsigned char       LATF;
extern volatile near struct {
  unsigned :1;
  unsigned LATF1:1;
  unsigned LATF2:1;
  unsigned LATF3:1;
  unsigned LATF4:1;
  unsigned LATF5:1;
  unsigned LATF6:1;
  unsigned LATF7:1;
} LATFbits;
extern volatile near unsigned char       LATG;
extern volatile near struct {
  unsigned LATG0:1;
  unsigned LATG1:1;
  unsigned LATG2:1;
  unsigned LATG3:1;
  unsigned LATG4:1;
} LATGbits;
extern volatile near unsigned char       LATH;
extern volatile near struct {
  unsigned LATH0:1;
  unsigned LATH1:1;
  unsigned LATH2:1;
  unsigned LATH3:1;
  unsigned LATH4:1;
  unsigned LATH5:1;
  unsigned LATH6:1;
  unsigned LATH7:1;
} LATHbits;
extern volatile near unsigned char       LATJ;
extern volatile near struct {
  unsigned LATJ0:1;
  unsigned LATJ1:1;
  unsigned LATJ2:1;
  unsigned LATJ3:1;
  unsigned LATJ4:1;
  unsigned LATJ5:1;
  unsigned LATJ6:1;
  unsigned LATJ7:1;
} LATJbits;
extern volatile near unsigned char       DDRA;
extern volatile near union {
  struct {
    unsigned TRISA0:1;
    unsigned TRISA1:1;
    unsigned TRISA2:1;
    unsigned TRISA3:1;
    unsigned TRISA4:1;
    unsigned TRISA5:1;
    unsigned TRISA6:1;
    unsigned TRISA7:1;
  };
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
    unsigned RA7:1;
  };
} DDRAbits;
extern volatile near unsigned char       TRISA;
extern volatile near union {
  struct {
    unsigned TRISA0:1;
    unsigned TRISA1:1;
    unsigned TRISA2:1;
    unsigned TRISA3:1;
    unsigned TRISA4:1;
    unsigned TRISA5:1;
    unsigned TRISA6:1;
    unsigned TRISA7:1;
  };
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
    unsigned RA7:1;
  };
} TRISAbits;
extern volatile near unsigned char       DDRB;
extern volatile near union {
  struct {
    unsigned TRISB0:1;
    unsigned TRISB1:1;
    unsigned TRISB2:1;
    unsigned TRISB3:1;
    unsigned TRISB4:1;
    unsigned TRISB5:1;
    unsigned TRISB6:1;
    unsigned TRISB7:1;
  };
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
} DDRBbits;
extern volatile near unsigned char       TRISB;
extern volatile near union {
  struct {
    unsigned TRISB0:1;
    unsigned TRISB1:1;
    unsigned TRISB2:1;
    unsigned TRISB3:1;
    unsigned TRISB4:1;
    unsigned TRISB5:1;
    unsigned TRISB6:1;
    unsigned TRISB7:1;
  };
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
} TRISBbits;
extern volatile near unsigned char       DDRC;
extern volatile near union {
  struct {
    unsigned TRISC0:1;
    unsigned TRISC1:1;
    unsigned TRISC2:1;
    unsigned TRISC3:1;
    unsigned TRISC4:1;
    unsigned TRISC5:1;
    unsigned TRISC6:1;
    unsigned TRISC7:1;
  };
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
} DDRCbits;
extern volatile near unsigned char       TRISC;
extern volatile near union {
  struct {
    unsigned TRISC0:1;
    unsigned TRISC1:1;
    unsigned TRISC2:1;
    unsigned TRISC3:1;
    unsigned TRISC4:1;
    unsigned TRISC5:1;
    unsigned TRISC6:1;
    unsigned TRISC7:1;
  };
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
} TRISCbits;
extern volatile near unsigned char       DDRD;
extern volatile near union {
  struct {
    unsigned TRISD0:1;
    unsigned TRISD1:1;
    unsigned TRISD2:1;
    unsigned TRISD3:1;
    unsigned TRISD4:1;
    unsigned TRISD5:1;
    unsigned TRISD6:1;
    unsigned TRISD7:1;
  };
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
} DDRDbits;
extern volatile near unsigned char       TRISD;
extern volatile near union {
  struct {
    unsigned TRISD0:1;
    unsigned TRISD1:1;
    unsigned TRISD2:1;
    unsigned TRISD3:1;
    unsigned TRISD4:1;
    unsigned TRISD5:1;
    unsigned TRISD6:1;
    unsigned TRISD7:1;
  };
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
} TRISDbits;
extern volatile near unsigned char       DDRE;
extern volatile near union {
  struct {
    unsigned TRISE0:1;
    unsigned TRISE1:1;
    unsigned TRISE2:1;
    unsigned TRISE3:1;
    unsigned TRISE4:1;
    unsigned TRISE5:1;
    unsigned TRISE6:1;
    unsigned TRISE7:1;
  };
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
    unsigned RE3:1;
    unsigned RE4:1;
    unsigned RE5:1;
    unsigned RE6:1;
    unsigned RE7:1;
  };
} DDREbits;
extern volatile near unsigned char       TRISE;
extern volatile near union {
  struct {
    unsigned TRISE0:1;
    unsigned TRISE1:1;
    unsigned TRISE2:1;
    unsigned TRISE3:1;
    unsigned TRISE4:1;
    unsigned TRISE5:1;
    unsigned TRISE6:1;
    unsigned TRISE7:1;
  };
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
    unsigned RE3:1;
    unsigned RE4:1;
    unsigned RE5:1;
    unsigned RE6:1;
    unsigned RE7:1;
  };
} TRISEbits;
extern volatile near unsigned char       DDRF;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned TRISF1:1;
    unsigned TRISF2:1;
    unsigned TRISF3:1;
    unsigned TRISF4:1;
    unsigned TRISF5:1;
    unsigned TRISF6:1;
    unsigned TRISF7:1;
  };
  struct {
    unsigned :1;
    unsigned RF1:1;
    unsigned RF2:1;
    unsigned RF3:1;
    unsigned RF4:1;
    unsigned RF5:1;
    unsigned RF6:1;
    unsigned RF7:1;
  };
} DDRFbits;
extern volatile near unsigned char       TRISF;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned TRISF1:1;
    unsigned TRISF2:1;
    unsigned TRISF3:1;
    unsigned TRISF4:1;
    unsigned TRISF5:1;
    unsigned TRISF6:1;
    unsigned TRISF7:1;
  };
  struct {
    unsigned :1;
    unsigned RF1:1;
    unsigned RF2:1;
    unsigned RF3:1;
    unsigned RF4:1;
    unsigned RF5:1;
    unsigned RF6:1;
    unsigned RF7:1;
  };
} TRISFbits;
extern volatile near unsigned char       DDRG;
extern volatile near union {
  struct {
    unsigned TRISG0:1;
    unsigned TRISG1:1;
    unsigned TRISG2:1;
    unsigned TRISG3:1;
    unsigned TRISG4:1;
  };
  struct {
    unsigned RG0:1;
    unsigned RG1:1;
    unsigned RG2:1;
    unsigned RG3:1;
    unsigned RG4:1;
  };
} DDRGbits;
extern volatile near unsigned char       TRISG;
extern volatile near union {
  struct {
    unsigned TRISG0:1;
    unsigned TRISG1:1;
    unsigned TRISG2:1;
    unsigned TRISG3:1;
    unsigned TRISG4:1;
  };
  struct {
    unsigned RG0:1;
    unsigned RG1:1;
    unsigned RG2:1;
    unsigned RG3:1;
    unsigned RG4:1;
  };
} TRISGbits;
extern volatile near unsigned char       DDRH;
extern volatile near union {
  struct {
    unsigned TRISH0:1;
    unsigned TRISH1:1;
    unsigned TRISH2:1;
    unsigned TRISH3:1;
    unsigned TRISH4:1;
    unsigned TRISH5:1;
    unsigned TRISH6:1;
    unsigned TRISH7:1;
  };
  struct {
    unsigned RH0:1;
    unsigned RH1:1;
    unsigned RH2:1;
    unsigned RH3:1;
    unsigned RH4:1;
    unsigned RH5:1;
    unsigned RH6:1;
    unsigned RH7:1;
  };
} DDRHbits;
extern volatile near unsigned char       TRISH;
extern volatile near union {
  struct {
    unsigned TRISH0:1;
    unsigned TRISH1:1;
    unsigned TRISH2:1;
    unsigned TRISH3:1;
    unsigned TRISH4:1;
    unsigned TRISH5:1;
    unsigned TRISH6:1;
    unsigned TRISH7:1;
  };
  struct {
    unsigned RH0:1;
    unsigned RH1:1;
    unsigned RH2:1;
    unsigned RH3:1;
    unsigned RH4:1;
    unsigned RH5:1;
    unsigned RH6:1;
    unsigned RH7:1;
  };
} TRISHbits;
extern volatile near unsigned char       DDRJ;
extern volatile near union {
  struct {
    unsigned TRISJ0:1;
    unsigned TRISJ1:1;
    unsigned TRISJ2:1;
    unsigned TRISJ3:1;
    unsigned TRISJ4:1;
    unsigned TRISJ5:1;
    unsigned TRISJ6:1;
    unsigned TRISJ7:1;
  };
  struct {
    unsigned RJ0:1;
    unsigned RJ1:1;
    unsigned RJ2:1;
    unsigned RJ3:1;
    unsigned RJ4:1;
    unsigned RJ5:1;
    unsigned RJ6:1;
    unsigned RJ7:1;
  };
} DDRJbits;
extern volatile near unsigned char       TRISJ;
extern volatile near union {
  struct {
    unsigned TRISJ0:1;
    unsigned TRISJ1:1;
    unsigned TRISJ2:1;
    unsigned TRISJ3:1;
    unsigned TRISJ4:1;
    unsigned TRISJ5:1;
    unsigned TRISJ6:1;
    unsigned TRISJ7:1;
  };
  struct {
    unsigned RJ0:1;
    unsigned RJ1:1;
    unsigned RJ2:1;
    unsigned RJ3:1;
    unsigned RJ4:1;
    unsigned RJ5:1;
    unsigned RJ6:1;
    unsigned RJ7:1;
  };
} TRISJbits;
extern volatile near unsigned char       OSCTUNE;
extern volatile near struct {
  unsigned TUN0:1;
  unsigned TUN1:1;
  unsigned TUN2:1;
  unsigned TUN3:1;
  unsigned TUN4:1;
  unsigned TUN5:1;
  unsigned PLLEN:1;
  unsigned INTSRC:1;
} OSCTUNEbits;
extern volatile near unsigned char       RCSTA2;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
  struct {
    unsigned RX9D2:1;
    unsigned OERR2:1;
    unsigned FERR2:1;
    unsigned ADDEN2:1;
    unsigned CREN2:1;
    unsigned SREN2:1;
    unsigned RX92:1;
    unsigned SPEN2:1;
  };
} RCSTA2bits;
extern volatile near unsigned char       PIE1;
extern volatile near union {
  struct {
    unsigned TMR1IE:1;
    unsigned TMR2IE:1;
    unsigned CCP1IE:1;
    unsigned SSP1IE:1;
    unsigned TX1IE:1;
    unsigned RC1IE:1;
    unsigned ADIE:1;
    unsigned PMPIE:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIE:1;
    unsigned TXIE:1;
    unsigned RCIE:1;
  };
} PIE1bits;
extern volatile near unsigned char       PIR1;
extern volatile near union {
  struct {
    unsigned TMR1IF:1;
    unsigned TMR2IF:1;
    unsigned CCP1IF:1;
    unsigned SSP1IF:1;
    unsigned TX1IF:1;
    unsigned RC1IF:1;
    unsigned ADIF:1;
    unsigned PMPIF:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIF:1;
    unsigned TXIF:1;
    unsigned RCIF:1;
  };
} PIR1bits;
extern volatile near unsigned char       IPR1;
extern volatile near union {
  struct {
    unsigned TMR1IP:1;
    unsigned TMR2IP:1;
    unsigned CCP1IP:1;
    unsigned SSP1IP:1;
    unsigned TX1IP:1;
    unsigned RC1IP:1;
    unsigned ADIP:1;
    unsigned PMPIP:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIP:1;
    unsigned TXIP:1;
    unsigned RCIP:1;
  };
} IPR1bits;
extern volatile near unsigned char       PIE2;
extern volatile near union {
  struct {
    unsigned CCP2IE:1;
    unsigned TMR3IE:1;
    unsigned LVDIE:1;
    unsigned BCL1IE:1;
    unsigned :1;
    unsigned CM1IE:1;
    unsigned CM2IE:1;
    unsigned OSCFIE:1;
  };
  struct {
    unsigned :3;
    unsigned BCLIE:1;
  };
} PIE2bits;
extern volatile near unsigned char       PIR2;
extern volatile near union {
  struct {
    unsigned CCP2IF:1;
    unsigned TMR3IF:1;
    unsigned LVDIF:1;
    unsigned BCL1IF:1;
    unsigned :1;
    unsigned CM1IF:1;
    unsigned CM2IF:1;
    unsigned OSCFIF:1;
  };
  struct {
    unsigned :3;
    unsigned BCLIF:1;
  };
} PIR2bits;
extern volatile near unsigned char       IPR2;
extern volatile near union {
  struct {
    unsigned CCP2IP:1;
    unsigned TMR3IP:1;
    unsigned LVDIP:1;
    unsigned BCL1IP:1;
    unsigned :1;
    unsigned CM1IP:1;
    unsigned CM2IP:1;
    unsigned OSCFIP:1;
  };
  struct {
    unsigned :3;
    unsigned BCLIP:1;
  };
} IPR2bits;
extern volatile near unsigned char       PIE3;
extern volatile near struct {
  unsigned CCP3IE:1;
  unsigned CCP4IE:1;
  unsigned CCP5IE:1;
  unsigned TMR4IE:1;
  unsigned TX2IE:1;
  unsigned RC2IE:1;
  unsigned BCL2IE:1;
  unsigned SSP2IE:1;
} PIE3bits;
extern volatile near unsigned char       PIR3;
extern volatile near struct {
  unsigned CCP3IF:1;
  unsigned CCP4IF:1;
  unsigned CCP5IF:1;
  unsigned TMR4IF:1;
  unsigned TX2IF:1;
  unsigned RC2IF:1;
  unsigned BCL2IF:1;
  unsigned SSP2IF:1;
} PIR3bits;
extern volatile near unsigned char       IPR3;
extern volatile near struct {
  unsigned CCP3IP:1;
  unsigned CCP4IP:1;
  unsigned CCP5IP:1;
  unsigned TMR4IP:1;
  unsigned TX2IP:1;
  unsigned RC2IP:1;
  unsigned BCL2IP:1;
  unsigned SSP2IP:1;
} IPR3bits;
extern volatile near unsigned char       EECON1;
extern volatile near struct {
  unsigned :1;
  unsigned WR:1;
  unsigned WREN:1;
  unsigned WRERR:1;
  unsigned FREE:1;
  unsigned WPROG:1;
} EECON1bits;
extern volatile near unsigned char       EECON2;
extern volatile near unsigned char       TXSTA2;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
  struct {
    unsigned TX9D2:1;
    unsigned TRMT2:1;
    unsigned BRGH2:1;
    unsigned SENDB2:1;
    unsigned SYNC2:1;
    unsigned TXEN2:1;
    unsigned TX92:1;
    unsigned CSRC2:1;
  };
} TXSTA2bits;
extern volatile near unsigned char       TXREG2;
extern volatile near unsigned char       RCREG2;
extern volatile near unsigned char       SPBRG2;
extern volatile near unsigned char       RCSTA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
  struct {
    unsigned RX9D1:1;
    unsigned OERR1:1;
    unsigned FERR1:1;
    unsigned ADDEN1:1;
    unsigned CREN1:1;
    unsigned SREN1:1;
    unsigned RX91:1;
    unsigned SPEN1:1;
  };
} RCSTAbits;
extern volatile near unsigned char       RCSTA1;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
  struct {
    unsigned RX9D1:1;
    unsigned OERR1:1;
    unsigned FERR1:1;
    unsigned ADDEN1:1;
    unsigned CREN1:1;
    unsigned SREN1:1;
    unsigned RX91:1;
    unsigned SPEN1:1;
  };
} RCSTA1bits;
extern volatile near unsigned char       TXSTA;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
  struct {
    unsigned TX9D1:1;
    unsigned TRMT1:1;
    unsigned BRGH1:1;
    unsigned SENDB1:1;
    unsigned SYNC1:1;
    unsigned TXEN1:1;
    unsigned TX91:1;
    unsigned CSRC1:1;
  };
} TXSTAbits;
extern volatile near unsigned char       TXSTA1;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
  struct {
    unsigned TX9D1:1;
    unsigned TRMT1:1;
    unsigned BRGH1:1;
    unsigned SENDB1:1;
    unsigned SYNC1:1;
    unsigned TXEN1:1;
    unsigned TX91:1;
    unsigned CSRC1:1;
  };
} TXSTA1bits;
extern volatile near unsigned char       TXREG;
extern volatile near unsigned char       TXREG1;
extern volatile near unsigned char       RCREG;
extern volatile near unsigned char       RCREG1;
extern volatile near unsigned char       SPBRG;
extern volatile near unsigned char       SPBRG1;
extern volatile near unsigned char       CCP3CON;
extern volatile near union {
  struct {
    unsigned CCP3M:4;
    unsigned DC3B:2;
    unsigned P3M:2;
  };
  struct {
    unsigned CCP3M0:1;
    unsigned CCP3M1:1;
    unsigned CCP3M2:1;
    unsigned CCP3M3:1;
    unsigned DC3B0:1;
    unsigned DC3B1:1;
    unsigned P3M0:1;
    unsigned P3M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP3Y:1;
    unsigned CCP3X:1;
  };
} CCP3CONbits;
extern volatile near unsigned char       ECCP3CON;
extern volatile near union {
  struct {
    unsigned CCP3M:4;
    unsigned DC3B:2;
    unsigned P3M:2;
  };
  struct {
    unsigned CCP3M0:1;
    unsigned CCP3M1:1;
    unsigned CCP3M2:1;
    unsigned CCP3M3:1;
    unsigned DC3B0:1;
    unsigned DC3B1:1;
    unsigned P3M0:1;
    unsigned P3M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP3Y:1;
    unsigned CCP3X:1;
  };
} ECCP3CONbits;
extern volatile near unsigned            CCPR3;
extern volatile near unsigned char       CCPR3L;
extern volatile near unsigned char       CCPR3H;
extern volatile near unsigned char       ECCP3DEL;
extern volatile near union {
  struct {
    unsigned PDC:7;
    unsigned PRSEN:1;
  };
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
  };
  struct {
    unsigned P3DC0:1;
    unsigned P3DC1:1;
    unsigned P3DC2:1;
    unsigned P3DC3:1;
    unsigned P3DC4:1;
    unsigned P3DC5:1;
    unsigned P3DC6:1;
    unsigned P3RSEN:1;
  };
} ECCP3DELbits;
extern volatile near unsigned char       ECCP3AS;
extern volatile near union {
  struct {
    unsigned PSSBD:2;
    unsigned PSSAC:2;
    unsigned ECCPAS:3;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
  };
  struct {
    unsigned PSS3BD0:1;
    unsigned PSS3BD1:1;
    unsigned PSS3AC0:1;
    unsigned PSS3AC1:1;
    unsigned ECCP3AS0:1;
    unsigned ECCP3AS1:1;
    unsigned ECCP3AS2:1;
    unsigned ECCP3ASE:1;
  };
} ECCP3ASbits;
extern volatile near unsigned char       CCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M:4;
    unsigned DC2B:2;
    unsigned P2M:2;
  };
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} CCP2CONbits;
extern volatile near unsigned char       ECCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M:4;
    unsigned DC2B:2;
    unsigned P2M:2;
  };
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} ECCP2CONbits;
extern volatile near unsigned            CCPR2;
extern volatile near unsigned char       CCPR2L;
extern volatile near unsigned char       CCPR2H;
extern volatile near unsigned char       ECCP2DEL;
extern volatile near union {
  struct {
    unsigned PDC:7;
    unsigned PRSEN:1;
  };
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
  };
  struct {
    unsigned P2DC0:1;
    unsigned P2DC1:1;
    unsigned P2DC2:1;
    unsigned P2DC3:1;
    unsigned P2DC4:1;
    unsigned P2DC5:1;
    unsigned P2DC6:1;
    unsigned P2RSEN:1;
  };
} ECCP2DELbits;
extern volatile near unsigned char       ECCP2AS;
extern volatile near union {
  struct {
    unsigned PSSBD:2;
    unsigned PSSAC:2;
    unsigned ECCPAS:3;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
  };
  struct {
    unsigned PSS2BD0:1;
    unsigned PSS2BD1:1;
    unsigned PSS2AC0:1;
    unsigned PSS2AC1:1;
    unsigned ECCP2AS0:1;
    unsigned ECCP2AS1:1;
    unsigned ECCP2AS2:1;
    unsigned ECCP2ASE:1;
  };
} ECCP2ASbits;
extern volatile near unsigned char       CCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M:4;
    unsigned DC1B:2;
    unsigned P1M:2;
  };
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} CCP1CONbits;
extern volatile near unsigned char       ECCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M:4;
    unsigned DC1B:2;
    unsigned P1M:2;
  };
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} ECCP1CONbits;
extern volatile near unsigned            CCPR1;
extern volatile near unsigned char       CCPR1L;
extern volatile near unsigned char       CCPR1H;
extern volatile near unsigned char       ECCP1DEL;
extern volatile near union {
  struct {
    unsigned PDC:7;
    unsigned PRSEN:1;
  };
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
  };
  struct {
    unsigned P1DC0:1;
    unsigned P1DC1:1;
    unsigned P1DC2:1;
    unsigned P1DC3:1;
    unsigned P1DC4:1;
    unsigned P1DC5:1;
    unsigned P1DC6:1;
    unsigned P1RSEN:1;
  };
} ECCP1DELbits;
extern volatile near unsigned char       ECCP1AS;
extern volatile near union {
  struct {
    unsigned PSSBD:2;
    unsigned PSSAC:2;
    unsigned ECCPAS:3;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
  };
  struct {
    unsigned PSS1BD0:1;
    unsigned PSS1BD1:1;
    unsigned PSS1AC0:1;
    unsigned PSS1AC1:1;
    unsigned ECCP1AS0:1;
    unsigned ECCP1AS1:1;
    unsigned ECCP1AS2:1;
    unsigned ECCP1ASE:1;
  };
} ECCP1ASbits;
extern volatile near unsigned char       WDTCON;
extern volatile near union {
  struct {
    unsigned SWDTEN:1;
    unsigned :3;
    unsigned ADSHR:1;
    unsigned :1;
    unsigned LVDSTAT:1;
    unsigned REGSLP:1;
  };
  struct {
    unsigned SWDTE:1;
    unsigned :3;
    unsigned DEVCFG:1;
  };
} WDTCONbits;
extern volatile near unsigned char       ADCON1;
extern volatile near union {
  struct {
    unsigned ADCS:3;
    unsigned ACQT:3;
    unsigned ADCAL:1;
    unsigned ADFM:1;
  };
  struct {
    unsigned ADCS0:1;
    unsigned ADCS1:1;
    unsigned ADCS2:1;
    unsigned ACQT0:1;
    unsigned ACQT1:1;
    unsigned ACQT2:1;
  };
} ADCON1bits;
extern volatile near unsigned char       ANCON0;
extern volatile near union {
  struct {
    unsigned PCFGL:8;
  };
  struct {
    unsigned PCFG0:1;
    unsigned PCFG1:1;
    unsigned PCFG2:1;
    unsigned PCFG3:1;
    unsigned PCFG4:1;
    unsigned :1;
    unsigned PCFG6:1;
    unsigned PCFG7:1;
  };
} ANCON0bits;
extern volatile near unsigned char       ADCON0;
extern volatile near union {
  struct {
    unsigned ADON:1;
    unsigned GO_NOT_DONE:1;
    unsigned CHS:4;
    unsigned VCFG:2;
  };
  struct {
    unsigned :1;
    unsigned DONE:1;
    unsigned CHS0:1;
    unsigned CHS1:1;
    unsigned CHS2:1;
    unsigned CHS3:1;
    unsigned VCFG0:1;
    unsigned VCFG1:1;
  };
  struct {
    unsigned :1;
    unsigned GO_DONE:1;
  };
  struct {
    unsigned :1;
    unsigned GO:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_DONE:1;
  };
} ADCON0bits;
extern volatile near unsigned char       ANCON1;
extern volatile near union {
  struct {
    unsigned PCFGH:8;
  };
  struct {
    unsigned PCFG8:1;
    unsigned PCFG9:1;
    unsigned PCFG10:1;
    unsigned PCFG11:1;
    unsigned PCFG12:1;
    unsigned PCFG13:1;
    unsigned PCFG14:1;
    unsigned PCFG15:1;
  };
} ANCON1bits;
extern volatile near unsigned            ADRES;
extern volatile near unsigned char       ADRESL;
extern volatile near unsigned char       ADRESH;
extern volatile near unsigned char       SSP1CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSP1CON2bits;
extern volatile near unsigned char       SSPCON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSPCON2bits;
extern volatile near unsigned char       SSP1CON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSP1CON1bits;
extern volatile near unsigned char       SSPCON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSPCON1bits;
extern volatile near unsigned char       SSP1STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSP1STATbits;
extern volatile near unsigned char       SSPSTAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSPSTATbits;
extern volatile near unsigned char       SSP1ADD;
extern volatile near unsigned char       SSP1MSK;
extern volatile near struct {
  unsigned MSK0:1;
  unsigned MSK1:1;
  unsigned MSK2:1;
  unsigned MSK3:1;
  unsigned MSK4:1;
  unsigned MSK5:1;
  unsigned MSK6:1;
  unsigned MSK7:1;
} SSP1MSKbits;
extern volatile near unsigned char       SSPADD;
extern volatile near unsigned char       SSP1BUF;
extern volatile near unsigned char       SSPBUF;
extern volatile near unsigned char       T2CON;
extern volatile near union {
  struct {
    unsigned T2CKPS:2;
    unsigned TMR2ON:1;
    unsigned TOUTPS:4;
  };
  struct {
    unsigned T2CKPS0:1;
    unsigned T2CKPS1:1;
    unsigned :1;
    unsigned T2OUTPS0:1;
    unsigned T2OUTPS1:1;
    unsigned T2OUTPS2:1;
    unsigned T2OUTPS3:1;
  };
} T2CONbits;
extern volatile near unsigned char       MEMCON;
extern volatile near union {
  struct {
    unsigned WM:2;
    unsigned :2;
    unsigned WAIT:2;
    unsigned :1;
    unsigned EBDIS:1;
  };
  struct {
    unsigned WM0:1;
    unsigned WM1:1;
    unsigned :2;
    unsigned WAIT0:1;
    unsigned WAIT1:1;
    unsigned :1;
    unsigned EDBIS:1;
  };
} MEMCONbits;
extern volatile near unsigned char       PR2;
extern volatile near unsigned char       PADCFG1;
extern volatile near union {
  struct {
    unsigned PMPTL:1;
  };
  struct {
    unsigned PMPTTL:1;
  };
} PADCFG1bits;
extern volatile near unsigned char       TMR2;
extern volatile near unsigned char       ODCON3;
extern volatile near struct {
  unsigned SPI1OD:1;
  unsigned SPI2OD:1;
} ODCON3bits;
extern volatile near unsigned char       T1CON;
extern volatile near union {
  struct {
    unsigned TMR1ON:1;
    unsigned TMR1CS:1;
    unsigned NOT_T1SYNC:1;
    unsigned T1OSCEN:1;
    unsigned T1CKPS:2;
    unsigned T1RUN:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T1SYNC:1;
    unsigned :1;
    unsigned T1CKPS0:1;
    unsigned T1CKPS1:1;
  };
  struct {
    unsigned :2;
    unsigned T1INSYNC:1;
  };
} T1CONbits;
extern volatile near unsigned char       ODCON2;
extern volatile near union {
  struct {
    unsigned USART1OD:1;
    unsigned USART2OD:1;
  };
  struct {
    unsigned U1OD:1;
    unsigned U2OD:1;
  };
} ODCON2bits;
extern volatile near unsigned char       TMR1L;
extern volatile near unsigned char       ODCON1;
extern volatile near struct {
  unsigned ECCP1OD:1;
  unsigned ECCP2OD:1;
  unsigned ECCP3OD:1;
  unsigned CCP4OD:1;
  unsigned CCP5OD:1;
} ODCON1bits;
extern volatile near unsigned char       TMR1H;
extern volatile near unsigned char       RCON;
extern volatile near union {
  struct {
    unsigned NOT_BOR:1;
    unsigned NOT_POR:1;
    unsigned NOT_PD:1;
    unsigned NOT_TO:1;
    unsigned NOT_RI:1;
    unsigned NOT_CM:1;
    unsigned :1;
    unsigned IPEN:1;
  };
  struct {
    unsigned BOR:1;
    unsigned POR:1;
    unsigned PD:1;
    unsigned TO:1;
    unsigned RI:1;
    unsigned CM:1;
  };
} RCONbits;
extern volatile near unsigned char       CM2CON;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned C1CH0:1;
    unsigned C1CH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
  };
} CM2CONbits;
extern volatile near unsigned char       CM2CON1;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned C1CH0:1;
    unsigned C1CH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
  };
} CM2CON1bits;
extern volatile near unsigned char       CM1CON;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned C1CH0:1;
    unsigned C1CH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
  };
} CM1CONbits;
extern volatile near unsigned char       CM1CON1;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned C1CH0:1;
    unsigned C1CH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
  };
} CM1CON1bits;
extern volatile near unsigned char       OSCCON;
extern volatile near union {
  struct {
    unsigned SCS:2;
    unsigned :1;
    unsigned OSTS:1;
    unsigned IRCF:3;
    unsigned IDLEN:1;
  };
  struct {
    unsigned SCS0:1;
    unsigned SCS1:1;
    unsigned :2;
    unsigned IRCF0:1;
    unsigned IRCF1:1;
    unsigned IRCF2:1;
  };
} OSCCONbits;
extern volatile near unsigned char       REFOCON;
extern volatile near union {
  struct {
    unsigned RODIV:4;
    unsigned ROSEL:1;
    unsigned ROSSLP:1;
    unsigned :1;
    unsigned ROON:1;
  };
  struct {
    unsigned RODIV0:1;
    unsigned RODIV1:1;
    unsigned RODIV2:1;
    unsigned RODIV3:1;
  };
} REFOCONbits;
extern volatile near unsigned char       T0CON;
extern volatile near union {
  struct {
    unsigned T0PS:3;
    unsigned PSA:1;
    unsigned T0SE:1;
    unsigned T0CS:1;
    unsigned T08BIT:1;
    unsigned TMR0ON:1;
  };
  struct {
    unsigned T0PS0:1;
    unsigned T0PS1:1;
    unsigned T0PS2:1;
    unsigned T0PS3:1;
  };
} T0CONbits;
extern volatile near unsigned char       TMR0L;
extern volatile near unsigned char       TMR0H;
extern          near unsigned char       STATUS;
extern          near struct {
  unsigned C:1;
  unsigned DC:1;
  unsigned Z:1;
  unsigned OV:1;
  unsigned N:1;
} STATUSbits;
extern          near unsigned            FSR2;
extern          near unsigned char       FSR2L;
extern          near unsigned char       FSR2H;
extern volatile near unsigned char       PLUSW2;
extern volatile near unsigned char       PREINC2;
extern volatile near unsigned char       POSTDEC2;
extern volatile near unsigned char       POSTINC2;
extern          near unsigned char       INDF2;
extern          near unsigned char       BSR;
extern          near unsigned            FSR1;
extern          near unsigned char       FSR1L;
extern          near unsigned char       FSR1H;
extern volatile near unsigned char       PLUSW1;
extern volatile near unsigned char       PREINC1;
extern volatile near unsigned char       POSTDEC1;
extern volatile near unsigned char       POSTINC1;
extern          near unsigned char       INDF1;
extern          near unsigned char       WREG;
extern          near unsigned            FSR0;
extern          near unsigned char       FSR0L;
extern          near unsigned char       FSR0H;
extern volatile near unsigned char       PLUSW0;
extern volatile near unsigned char       PREINC0;
extern volatile near unsigned char       POSTDEC0;
extern volatile near unsigned char       POSTINC0;
extern          near unsigned char       INDF0;
extern volatile near unsigned char       INTCON3;
extern volatile near union {
  struct {
    unsigned INT1IF:1;
    unsigned INT2IF:1;
    unsigned INT3IF:1;
    unsigned INT1IE:1;
    unsigned INT2IE:1;
    unsigned INT3IE:1;
    unsigned INT1IP:1;
    unsigned INT2IP:1;
  };
  struct {
    unsigned INT1F:1;
    unsigned INT2F:1;
    unsigned INT3F:1;
    unsigned INT1E:1;
    unsigned INT2E:1;
    unsigned INT3E:1;
    unsigned INT1P:1;
    unsigned INT2P:1;
  };
} INTCON3bits;
extern volatile near unsigned char       INTCON2;
extern volatile near union {
  struct {
    unsigned RBIP:1;
    unsigned INT3IP:1;
    unsigned TMR0IP:1;
    unsigned INTEDG3:1;
    unsigned INTEDG2:1;
    unsigned INTEDG1:1;
    unsigned INTEDG0:1;
    unsigned NOT_RBPU:1;
  };
  struct {
    unsigned :1;
    unsigned INT3P:1;
    unsigned T0IP:1;
    unsigned :4;
    unsigned RBPU:1;
  };
} INTCON2bits;
extern volatile near unsigned char       INTCON;
extern volatile near union {
  struct {
    unsigned RBIF:1;
    unsigned INT0IF:1;
    unsigned TMR0IF:1;
    unsigned RBIE:1;
    unsigned INT0IE:1;
    unsigned TMR0IE:1;
    unsigned PEIE_GIEL:1;
    unsigned GIE_GIEH:1;
  };
  struct {
    unsigned :1;
    unsigned INT0F:1;
    unsigned T0IF:1;
    unsigned :1;
    unsigned INT0E:1;
    unsigned T0IE:1;
    unsigned PEIE:1;
    unsigned GIE:1;
  };
  struct {
    unsigned :6;
    unsigned GIEL:1;
    unsigned GIEH:1;
  };
} INTCONbits;
extern          near unsigned            PROD;
extern          near unsigned char       PRODL;
extern          near unsigned char       PRODH;
extern volatile near unsigned char       TABLAT;
extern volatile near unsigned short long TBLPTR;
extern volatile near unsigned char       TBLPTRL;
extern volatile near unsigned char       TBLPTRH;
extern volatile near unsigned char       TBLPTRU;
extern volatile near unsigned short long PC;
extern volatile near unsigned char       PCL;
extern volatile near unsigned char       PCLATH;
extern volatile near unsigned char       PCLATU;
extern volatile near unsigned char       STKPTR;
extern volatile near union {
  struct {
    unsigned STKPTR:5;
    unsigned :1;
    unsigned STKUNF:1;
    unsigned STKFUL:1;
  };
  struct {
    unsigned STKPTR0:1;
    unsigned STKPTR1:1;
    unsigned STKPTR2:1;
    unsigned STKPTR3:1;
    unsigned STKPTR4:1;
    unsigned :2;
    unsigned STKOVF:1;
  };
  struct {
    unsigned SP0:1;
    unsigned SP1:1;
    unsigned SP2:1;
    unsigned SP3:1;
    unsigned SP4:1;
  };
} STKPTRbits;
extern          near unsigned short long TOS;
extern          near unsigned char       TOSL;
extern          near unsigned char       TOSH;
extern          near unsigned char       TOSU;

#pragma varlocate 15 PMSTAT
#pragma varlocate 15 PMSTATL
#pragma varlocate 15 PMSTATLbits
#pragma varlocate 15 PMSTATH
#pragma varlocate 15 PMSTATHbits
#pragma varlocate 15 PMEL
#pragma varlocate 15 PMELbits
#pragma varlocate 15 PMEN
#pragma varlocate 15 PMEH
#pragma varlocate 15 PMEHbits
#pragma varlocate 15 PMDIN2
#pragma varlocate 15 PMDIN2L
#pragma varlocate 15 PMDIN2H


#line 2634 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
 
#line 2636 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2637 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"


#line 2640 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
 
#line 2642 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2643 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2644 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2645 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"

#line 2647 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2648 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2649 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2650 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 2651 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"


#line 2655 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
 
#line 2657 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"


#line 2660 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18f87j11.h"
#line 451 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"

#line 453 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 455 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 457 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 459 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 461 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 463 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 465 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 467 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 469 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 471 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 473 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 475 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 477 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 479 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 481 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 483 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 485 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 487 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 489 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 491 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 493 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 495 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 497 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 499 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 501 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 503 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 505 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 507 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 509 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 511 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 513 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 515 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 517 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 519 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 521 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 523 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 525 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 527 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 529 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 531 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 533 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 535 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 537 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 539 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 541 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 543 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 545 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 547 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 549 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 551 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 553 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 555 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 557 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 559 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 561 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"

#line 563 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 64 "../../../../Microchip/Include/Compiler.h"

#line 66 "../../../../Microchip/Include/Compiler.h"
#line 68 "../../../../Microchip/Include/Compiler.h"
#line 70 "../../../../Microchip/Include/Compiler.h"
#line 73 "../../../../Microchip/Include/Compiler.h"
#line 77 "../../../../Microchip/Include/Compiler.h"
#line 81 "../../../../Microchip/Include/Compiler.h"
#line 85 "../../../../Microchip/Include/Compiler.h"
#line 89 "../../../../Microchip/Include/Compiler.h"
#line 93 "../../../../Microchip/Include/Compiler.h"
#line 97 "../../../../Microchip/Include/Compiler.h"
#line 101 "../../../../Microchip/Include/Compiler.h"
#line 106 "../../../../Microchip/Include/Compiler.h"
#line 111 "../../../../Microchip/Include/Compiler.h"
#line 112 "../../../../Microchip/Include/Compiler.h"
#line 113 "../../../../Microchip/Include/Compiler.h"
#line 115 "../../../../Microchip/Include/Compiler.h"
#line 119 "../../../../Microchip/Include/Compiler.h"
#line 121 "../../../../Microchip/Include/Compiler.h"

#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"

#line 3 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"

#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdarg.h"
 


#line 5 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdarg.h"

typedef void* va_list;
#line 8 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdarg.h"
#line 9 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdarg.h"
#line 10 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdarg.h"
#line 11 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdarg.h"
#line 12 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdarg.h"
#line 4 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"

#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
 

#line 10 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"

#line 20 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"

#line 34 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"

#line 41 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
#line 45 "/Applications/microchip/mplabc18/v3.40/bin/../h/stddef.h"
#line 5 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"



#line 9 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"
 
#line 11 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"

#line 13 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"


typedef unsigned char FILE;

 
#line 19 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"
#line 20 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"

extern FILE *stderr;
extern FILE *stdout;


int putc (auto char c, auto FILE *f);
int vsprintf (auto char *buf, auto const far  rom char *fmt, auto va_list ap);
int vprintf (auto const far  rom char *fmt, auto va_list ap);
int sprintf (auto char *buf, auto const far  rom char *fmt, ...);
int printf (auto const far  rom char *fmt, ...);
int fprintf (auto FILE *f, auto const far  rom char *fmt, ...);
int vfprintf (auto FILE *f, auto const far  rom char *fmt, auto va_list ap);
int puts (auto const far  rom char *s);
int fputs (auto const far  rom char *s, auto FILE *f);

#line 36 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdio.h"
#line 122 "../../../../Microchip/Include/Compiler.h"

#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 

#line 4 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"

#line 6 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"

#line 9 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
 

#line 16 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
double atof (const auto char *s);

#line 28 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
signed char atob (const auto char *s);


#line 39 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
int atoi (const auto char *s);

#line 47 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
long atol (const auto char *s);

#line 58 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
unsigned long atoul (const auto char *s);


#line 71 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
char *btoa (auto signed char value, auto char *s);

#line 83 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
char *itoa (auto int value, auto char *s);

#line 95 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
char *ltoa (auto long value, auto char *s);

#line 107 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
char *ultoa (auto unsigned long value, auto char *s);
 


#line 112 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
 

#line 116 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
#line 118 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"


#line 124 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
int rand (void);

#line 136 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
 
void srand (auto unsigned int seed);
 
#line 140 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
#line 149 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"

#line 151 "/Applications/microchip/mplabc18/v3.40/bin/../h/stdlib.h"
#line 123 "../../../../Microchip/Include/Compiler.h"

#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"

#line 3 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"

#line 7 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"


#line 20 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
#line 22 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"


#line 25 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
#line 27 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"

 

#line 39 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
void *memcpy (auto void *s1, auto const void *s2, auto size_t n);


#line 55 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
void *memmove (auto void *s1, auto const void *s2, auto size_t n);


#line 67 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strcpy (auto char *s1, auto const char *s2);


#line 83 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strncpy (auto char *s1, auto const char *s2, auto size_t n);


#line 97 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strcat (auto char *s1, auto const char *s2);


#line 113 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strncat (auto char *s1, auto const char *s2, auto size_t n);


#line 128 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char memcmp (auto const void *s1, auto const void *s2, auto size_t n);


#line 141 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strcmp (auto const char *s1, auto const char *s2);


#line 147 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 


#line 161 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strncmp (auto const char *s1, auto const char *s2, auto size_t n);


#line 167 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 


#line 183 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
void *memchr (auto const void *s, auto unsigned char c, auto size_t n);


#line 199 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strchr (auto const char *s, auto unsigned char c);


#line 210 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
size_t strcspn (auto const char *s1, auto const char *s2);


#line 222 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strpbrk (auto const char *s1, auto const char *s2);


#line 238 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strrchr (auto const char *s, auto unsigned char c);


#line 249 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
size_t strspn (auto const char *s1, auto const char *s2);


#line 262 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strstr (auto const char *s1, auto const char *s2);


#line 305 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strtok (auto char *s1, auto const char *s2);


#line 321 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
void *memset (auto void *s, auto unsigned char c, auto size_t n);


#line 339 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
#line 341 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"


#line 349 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
size_t strlen (auto const char *s);


#line 358 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strupr (auto char *s);


#line 367 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strlwr (auto char *s);



 

#line 379 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom void *memcpypgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 389 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
void *memcpypgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 398 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom void *memcpyram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 407 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom void *memmovepgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 417 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
void *memmovepgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 426 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom void *memmoveram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 434 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strcpypgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 443 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strcpypgm2ram (auto char *s1, auto const far  rom char *s2);


#line 451 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strcpyram2pgm (auto far  rom char *s1, auto const char *s2);


#line 460 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strncpypgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 470 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strncpypgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 479 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strncpyram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 487 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strcatpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 496 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strcatpgm2ram (auto char *s1, auto const far  rom char *s2);


#line 504 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strcatram2pgm (auto far  rom char *s1, auto const char *s2);


#line 513 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strncatpgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 523 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strncatpgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 532 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strncatram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 541 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char memcmppgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 551 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char memcmppgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 560 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char memcmpram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 568 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strcmppgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 577 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strcmppgm2ram (auto const char *s1, auto const far  rom char *s2);


#line 585 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strcmpram2pgm (auto const far  rom char *s1, auto const char *s2);


#line 594 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strncmppgm (auto const far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 604 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strncmppgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 613 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
signed char strncmpram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 622 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *memchrpgm (auto const far  rom char *s, auto const unsigned char c, auto sizerom_t n);


#line 631 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strchrpgm (auto const far  rom char *s, auto unsigned char c);


#line 639 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
sizerom_t strcspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 647 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
sizerom_t strcspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 655 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
sizeram_t strcspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 663 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strpbrkpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 671 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strpbrkpgmram (auto const far  rom char *s1, auto const char *s2);


#line 679 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strpbrkrampgm (auto const char *s1, auto const far  rom char *s2);


#line 688 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
 


#line 696 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
sizerom_t strspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 704 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
sizerom_t strspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 712 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
sizeram_t strspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 720 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strstrpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 729 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strstrpgmram (auto const far  rom char *s1, auto const char *s2);


#line 737 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strstrrampgm (auto const char *s1, auto const far  rom char *s2);


#line 745 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strtokpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 754 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
char *strtokpgmram (auto char *s1, auto const far  rom char *s2);


#line 762 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strtokrampgm (auto far  rom char *s1, auto const char *s2);


#line 771 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom void *memsetpgm (auto far  rom void *s, auto unsigned char c, auto sizerom_t n);


#line 778 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *struprpgm (auto far  rom char *s);


#line 785 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
far  rom char *strlwrpgm (auto far  rom char *s);


#line 792 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
 
sizerom_t strlenpgm (auto const far  rom char *s);

#line 796 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"

#line 798 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"

#line 805 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
#line 814 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"

#line 816 "/Applications/microchip/mplabc18/v3.40/bin/../h/string.h"
#line 124 "../../../../Microchip/Include/Compiler.h"




#line 129 "../../../../Microchip/Include/Compiler.h"
#line 132 "../../../../Microchip/Include/Compiler.h"
#line 135 "../../../../Microchip/Include/Compiler.h"
#line 136 "../../../../Microchip/Include/Compiler.h"
#line 137 "../../../../Microchip/Include/Compiler.h"
#line 138 "../../../../Microchip/Include/Compiler.h"
#line 141 "../../../../Microchip/Include/Compiler.h"



#line 145 "../../../../Microchip/Include/Compiler.h"
#line 155 "../../../../Microchip/Include/Compiler.h"




#line 160 "../../../../Microchip/Include/Compiler.h"
#line 161 "../../../../Microchip/Include/Compiler.h"

#line 163 "../../../../Microchip/Include/Compiler.h"

	
#line 166 "../../../../Microchip/Include/Compiler.h"
#line 167 "../../../../Microchip/Include/Compiler.h"
#line 168 "../../../../Microchip/Include/Compiler.h"
	
	
#line 171 "../../../../Microchip/Include/Compiler.h"
#line 176 "../../../../Microchip/Include/Compiler.h"
#line 179 "../../../../Microchip/Include/Compiler.h"
#line 182 "../../../../Microchip/Include/Compiler.h"
#line 185 "../../../../Microchip/Include/Compiler.h"
#line 186 "../../../../Microchip/Include/Compiler.h"
    


#line 190 "../../../../Microchip/Include/Compiler.h"
#line 194 "../../../../Microchip/Include/Compiler.h"
#line 197 "../../../../Microchip/Include/Compiler.h"
#line 200 "../../../../Microchip/Include/Compiler.h"
#line 201 "../../../../Microchip/Include/Compiler.h"
#line 203 "../../../../Microchip/Include/Compiler.h"
#line 211 "../../../../Microchip/Include/Compiler.h"
#line 213 "../../../../Microchip/Include/Compiler.h"
#line 214 "../../../../Microchip/Include/Compiler.h"
#line 215 "../../../../Microchip/Include/Compiler.h"



#line 219 "../../../../Microchip/Include/Compiler.h"
#line 66 "../../../../Microchip/MFI/MFI_iPod_UART.c"


#line 1 "../UART/mfi_config.h"

#line 28 "../UART/mfi_config.h"
 




#line 34 "../UART/mfi_config.h"

#line 36 "../UART/mfi_config.h"
#line 37 "../UART/mfi_config.h"
#line 38 "../UART/mfi_config.h"
#line 39 "../UART/mfi_config.h"




#line 44 "../UART/mfi_config.h"


#line 47 "../UART/mfi_config.h"
#line 48 "../UART/mfi_config.h"
#line 49 "../UART/mfi_config.h"
#line 50 "../UART/mfi_config.h"
#line 51 "../UART/mfi_config.h"
#line 52 "../UART/mfi_config.h"
#line 53 "../UART/mfi_config.h"

#line 55 "../UART/mfi_config.h"



#line 59 "../UART/mfi_config.h"
#line 60 "../UART/mfi_config.h"




#line 65 "../UART/mfi_config.h"
#line 66 "../UART/mfi_config.h"
#line 67 "../UART/mfi_config.h"
#line 68 "../UART/mfi_config.h"
#line 69 "../UART/mfi_config.h"
#line 70 "../UART/mfi_config.h"
#line 71 "../UART/mfi_config.h"
#line 72 "../UART/mfi_config.h"
#line 73 "../UART/mfi_config.h"
#line 74 "../UART/mfi_config.h"




#line 79 "../UART/mfi_config.h"

#line 81 "../UART/mfi_config.h"
#line 82 "../UART/mfi_config.h"

#line 84 "../UART/mfi_config.h"
#line 85 "../UART/mfi_config.h"
#line 86 "../UART/mfi_config.h"
#line 87 "../UART/mfi_config.h"
#line 88 "../UART/mfi_config.h"
#line 89 "../UART/mfi_config.h"
#line 90 "../UART/mfi_config.h"
#line 91 "../UART/mfi_config.h"





#line 97 "../UART/mfi_config.h"
#line 98 "../UART/mfi_config.h"
#line 99 "../UART/mfi_config.h"
#line 100 "../UART/mfi_config.h"




#line 105 "../UART/mfi_config.h"
#line 106 "../UART/mfi_config.h"
#line 107 "../UART/mfi_config.h"
#line 108 "../UART/mfi_config.h"





#line 114 "../UART/mfi_config.h"
#line 115 "../UART/mfi_config.h"
#line 116 "../UART/mfi_config.h"
#line 117 "../UART/mfi_config.h"





#line 123 "../UART/mfi_config.h"
#line 124 "../UART/mfi_config.h"


#line 127 "../UART/mfi_config.h"

#line 68 "../../../../Microchip/MFI/MFI_iPod_UART.c"


#line 1 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 467 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 


#line 517 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 


#line 521 "../../../../Microchip/Include/MFI/MFI_iPod.h"


    
    
#line 526 "../../../../Microchip/Include/MFI/MFI_iPod.h"


#line 1 "../UART/mfi_config.h"

#line 28 "../UART/mfi_config.h"
 



#line 127 "../UART/mfi_config.h"

#line 528 "../../../../Microchip/Include/MFI/MFI_iPod.h"


#line 531 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 533 "../../../../Microchip/Include/MFI/MFI_iPod.h"








#line 542 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 544 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 546 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 548 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 557 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
#line 559 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 565 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 567 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 569 "../../../../Microchip/Include/MFI/MFI_iPod.h"


#line 572 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 577 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 580 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 581 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 583 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 584 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 585 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 589 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 590 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 594 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 595 "../../../../Microchip/Include/MFI/MFI_iPod.h"












    
#line 609 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 613 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 616 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 619 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 623 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 626 "../../../../Microchip/Include/MFI/MFI_iPod.h"

   
   
   
   
#line 632 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 635 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 638 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 641 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 644 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 647 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 651 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
    
#line 657 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 661 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 665 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
    
#line 671 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
    
#line 677 "../../../../Microchip/Include/MFI/MFI_iPod.h"



#line 685 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef enum
{
        
        
        
        
        
        
        
        
        
    MFI_EVENT_IS_IPOD_ATTACHED,

        
        
        
        
        
    MFI_EVENT_CP_SET_NRESET,

        
        
        
        
        
        
        
        
        
        
    MFI_EVENT_CP_OPEN_I2C,

        
        
        
    MFI_EVENT_CP_I2C_CLOSED,

        
        
    MFI_EVENT_CANNOT_SET_EXTRA_CURRENT,

        
        
        
    MFI_EVENT_GENERAL_ERROR,

        
        
        
        
    MFI_EVENT_FATAL_ERROR,

        
        
        
        
    MFI_EVENT_IPOD_ATTACHED,

        
        
    MFI_EVENT_IPOD_DETACHED,

        
        
        
        
        
    MFI_EVENT_IDPS_NOT_SUPPORTED,

        
        
        
        
        
        
        
        
        
        
        
        
    MFI_EVENT_LINGO_NOT_SUPPORTED,

        
        
        
        
        
        
        
        
        
    MFI_EVENT_LINGO_VERSION,

        
        
        
        
        
        
        
        
        
        
        
    MFI_EVENT_CHECK_LINGO_OPTIONS,

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    MFI_EVENT_TOKEN_PROBLEM,

        
        
        
    MFI_EVENT_IPOD_CANNOT_CONNECT,

        
        
        
    MFI_EVENT_IDPS_FAILURE,

        
        
        
        
        
        
        
        
    MFI_EVENT_IPOD_AUTHENTICATION_FAILED,

        
        
        
        
        
        
        
        
    MFI_EVENT_IPOD_READY,

        
        
        
        
        
        
    MFI_EVENT_COMMAND_AVAILABLE,

        
        
        
        
        
    MFI_EVENT_COMMAND_SENT,

    
    

        
        
        
        
        
        
    MFI_EVENT_IPOD_READY_AUDIO_HOST,

        
        
        
        
        
    MFI_EVENT_AUDIO_SUPPORT_ERROR,

        
        
        
    MFI_EVENT_AUDIO_RATE_ERROR,

        
        
        
    MFI_EVENT_AUDIO_RECEIVING_DATA,

        
        
        
        
    MFI_EVENT_AUDIO_STOPPING_DATA,

        
        
        
        
    MFI_EVENT_AUDIO_SET_SAMPLE_RATE,

        
        
        
        
    MFI_EVENT_AUDIO_STREAM_RECEIVED,

    
    

        
        
        
        
        
        
        
        
        
        
        
        
    MFI_EVENT_RECEIVE_BUFFER_OVERRUN,

        
        
        
        
        
    MFI_EVENT_RECEIVE_BUFFER_OVERRUN_COMMAND

} MFI_EVENT;






#line 936 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 937 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 938 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 939 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 940 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 941 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 942 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 943 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 944 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 945 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 946 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 947 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 948 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 949 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 956 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 957 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 958 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 959 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 960 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 961 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 962 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 963 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 964 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 965 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 966 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 967 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 968 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 969 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 976 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 977 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 978 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 979 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 980 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 981 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 982 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 983 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 984 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 985 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 986 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 987 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 988 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 989 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 990 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 991 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 992 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 993 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 994 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 995 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 996 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 997 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 998 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 999 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1000 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1001 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1002 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1003 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1004 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1005 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1006 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1007 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1008 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1009 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1010 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1011 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1012 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1013 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1014 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1015 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1016 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1017 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1018 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1019 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1020 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1021 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1022 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1023 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1024 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1025 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1026 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1027 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1028 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1029 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1030 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1031 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1032 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1033 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1034 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1035 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1036 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1037 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1038 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1039 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1040 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1041 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1042 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1043 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1044 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1045 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1046 "../../../../Microchip/Include/MFI/MFI_iPod.h"





































#line 1084 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1085 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1086 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1087 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1088 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1089 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1090 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1091 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1092 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1093 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1094 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1095 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1096 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1097 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1098 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1099 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1100 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1101 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1102 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1103 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1104 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1105 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1106 "../../../../Microchip/Include/MFI/MFI_iPod.h"




    
    
#line 1113 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    
    
#line 1116 "../../../../Microchip/Include/MFI/MFI_iPod.h"


    
    
    
    
#line 1123 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1124 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1125 "../../../../Microchip/Include/MFI/MFI_iPod.h"


    
    
    
    
#line 1132 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1133 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1134 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1139 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1140 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1141 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1146 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1147 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1148 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1153 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1154 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1155 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1156 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1157 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1162 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1163 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1164 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1169 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1170 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1171 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1176 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1177 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1178 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1183 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1184 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1185 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1190 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1191 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1192 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1197 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1199 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1200 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
#line 1205 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1206 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1207 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 1213 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1214 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1215 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1216 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1217 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1218 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1220 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1221 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1222 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1224 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 1230 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1231 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1232 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1233 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1234 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1235 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1236 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1237 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1238 "../../../../Microchip/Include/MFI/MFI_iPod.h"










#line 1249 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1250 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1251 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1252 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 1258 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1259 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1260 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1261 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 1267 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1268 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1269 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1270 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1271 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1272 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1274 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1276 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1277 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1278 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1279 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1280 "../../../../Microchip/Include/MFI/MFI_iPod.h"




#line 1285 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1286 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1287 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1288 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1290 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1291 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1292 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1293 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1294 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 1300 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1301 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1302 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1303 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1304 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1305 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1306 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1307 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1308 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1309 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1310 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1311 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1312 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1313 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1314 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1315 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1316 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1317 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1318 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1319 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1320 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1321 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1322 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1323 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1324 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1325 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1326 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1327 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1328 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1329 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1330 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1331 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1332 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1333 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1334 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1335 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1336 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1337 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1338 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1339 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1340 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1341 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1342 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1343 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1344 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1345 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1346 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1347 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1348 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1349 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1350 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1351 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1352 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1353 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1354 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1355 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1356 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1357 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1358 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1359 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1360 "../../../../Microchip/Include/MFI/MFI_iPod.h"









































































#line 1434 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1435 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1436 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1437 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1438 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1439 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1440 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1441 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1442 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 1448 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1449 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1450 "../../../../Microchip/Include/MFI/MFI_iPod.h"





#line 1456 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1457 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1458 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1459 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1460 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1461 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1462 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1463 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1464 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1465 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1466 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1467 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 1474 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1475 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1476 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1477 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1478 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1479 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1480 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1481 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1482 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1483 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1484 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1485 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1486 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1487 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1488 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1489 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1490 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1491 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1492 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1493 "../../../../Microchip/Include/MFI/MFI_iPod.h"






























#line 1524 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1526 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1527 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1528 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1529 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1530 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1531 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1532 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1533 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1534 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1535 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1536 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1537 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1538 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1539 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1540 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1541 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1542 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1543 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1544 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1545 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1546 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1547 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1548 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1549 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1550 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1551 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1552 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1553 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1554 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1555 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1556 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1557 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1558 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1559 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 1566 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 1568 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1569 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1570 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1571 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1572 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 1579 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1580 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1581 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1582 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1583 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1584 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 1596 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 1603 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1604 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1605 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1606 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1607 "../../../../Microchip/Include/MFI/MFI_iPod.h"








#line 1616 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1617 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1618 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1619 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1620 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1621 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 1628 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1629 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1630 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1631 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1632 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1633 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1634 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1635 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1636 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1637 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1638 "../../../../Microchip/Include/MFI/MFI_iPod.h"

















#line 1656 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1657 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1658 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1659 "../../../../Microchip/Include/MFI/MFI_iPod.h"






#line 1666 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1667 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1668 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1669 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1670 "../../../../Microchip/Include/MFI/MFI_iPod.h"






    
    
    
#line 1680 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 1684 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 1688 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
    
#line 1694 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
    
    
#line 1700 "../../../../Microchip/Include/MFI/MFI_iPod.h"



#line 1704 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1706 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1707 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1709 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1710 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1712 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1713 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1715 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
    
#line 1719 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    
    
    
#line 1723 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    
    
    
#line 1727 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    
    
#line 1730 "../../../../Microchip/Include/MFI/MFI_iPod.h"










#line 1745 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[4];
    struct  
    {
        UINT8   reserved[3];

        UINT8                   : 2;
                    
                    
        UINT8   faultCondition  : 2;
    };
} IPOD_ACCESSORY_STATUS;




#line 1767 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef struct
{
    union
    {
        UINT32_VAL  lingoes;
        struct  
        {
            UINT8   lingoGeneral                : 1;    
            UINT8                               : 1;    
            UINT8   lingoSimpleRemote           : 1;    
            UINT8   lingoDisplayRemote          : 1;    

            UINT8   lingoExtendedInterface      : 1;    
            UINT8                               : 1;    
            UINT8   lingoUSBHostMode            : 1;    
            UINT8   lingoRFTuner                : 1;    

            UINT8   lingoAccessoryEqualizer     : 1;    
            UINT8   lingoSports                 : 1;    
            UINT8   lingoDigitalAudio           : 1;    
            UINT8                               : 1;

            UINT8   lingoStorage                : 1;    
            UINT8   lingoiPodOut                : 1;    
            UINT8   lingoLocation               : 1;    
            UINT8                               : 1;
            UINT16  reserved;
        };
    } deviceLingoesSpoken;                              

    union
    {
        UINT8   bytes[8];
        struct  
        {
            UINT8       analogLineOut           : 1;    
            UINT8       analogLineIn            : 1;    
            UINT8       analogVideoOut          : 1;    
            UINT8                               : 1;
            UINT8       digitalAudio            : 1;    
            UINT8                               : 3;

            UINT8                               : 1;
            UINT8       iPhoneApplication       : 1;    
            UINT8                               : 1;
            UINT8       checksVolume            : 1;    
            UINT8                               : 4;

            UINT8                               : 1;
            UINT8       voiceOver               : 1;    
            UINT8       playbackStateChanges    : 1;    
            UINT8       multipacketResponse     : 1;    
            UINT8                               : 1;
            UINT8       audioRouteSwitching     : 1;    
            UINT8                               : 1;
            UINT8       assistiveTouch          : 1;    

            UINT8       reservedSpace[5];
        };
    } accessoryCapsBitmask;                             

    union
    {
        UINT8   bytes[4];
        struct  
        {
            UINT8   class1  : 1;    
            UINT8   class2  : 1;    
            UINT8   class3  : 1;    
            UINT8   class4  : 1;    
            UINT8   class5  : 1;    
        };
    } accessoryRFCertifications;







































#line 1881 "../../../../Microchip/Include/MFI/MFI_iPod.h"
        const rom char  *accessoryManufacturer;             
        const rom char  *accessoryName;                     
        const rom char  *accessoryModelNumber;              
        const rom char  *accessorySerialNumber;             
        const rom char  *BundleSeedIDString;                
        const rom char  *protocolStrings;                   
#line 1888 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 1895 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    UINT8           numEAProtocolStrings;                   

    UINT8           accessorySoftwareVersionMajor;          
    UINT8           accessorySoftwareVersionMinor;          
    UINT8           accessorySoftwareVersionRevision;       

    UINT8           accessoryHardwareVersionMajor;          
    UINT8           accessoryHardwareVersionMinor;          
    UINT8           accessoryHardwareVersionRevision;       

    union
    {
        UINT8       bytes[2];
        struct  
        {
            UINT8       videoOutSetting         : 2;        
            UINT8       screenConfiguration     : 1;        
            UINT8       videoSignalFormat       : 1;        

            UINT8       lineOutUsage            : 1;        
            UINT8       videoOutConnection      : 2;        
            UINT8       closedCaptioning        : 1;        

            UINT8       videoAspectRatio        : 1;        
            UINT8       subtitles               : 1;        
            UINT8       alternateAudioChannel   : 1;        
            UINT8       pauseOnPowerRemoval     : 1;        
        };
    } iPodPreferences;                                      

    union
    {
        UINT8       bytes[4];
        struct  
        {
            UINT8       authenticationControl   : 2;        

        };
    } DeviceOptions;

    UINT16  usbExtraCurrentInSuspend;                       
    UINT16  usbExtraCurrentNotInSuspend;                    

    UINT8   cpCommunicationInterface;                       
    UINT8   cpCommunicationModule;                          

    UINT16  maxCommandPayloadLengthIn;                      
    UINT16  maxCommandPayloadLengthOut;                     

    union
    {
        UINT8       bytes[4];
        struct  
        {
            UINT8       disableSyncByteUsage                : 1;    
            UINT8       sendExtraCurrentDeviceRequest       : 1;    
            UINT8       digitalAudioIn                      : 1;    
            UINT8       digitalAudioOut                     : 1;    
            UINT8       protocolTransport                   : 3;    
            UINT8       suppressVideoConnectionToken        : 1;    

            UINT8       suppressVideoOutSettingToken        : 1;    
            UINT8       suppressScreenConfigurationToken    : 1;    
            UINT8       suppressVideoSignalFormatToken      : 1;    
            UINT8       suppressClosedCaptioningToken       : 1;    
            UINT8       suppressAspectRatioToken            : 1;    
            UINT8       suppressSubtitlesToken              : 1;    
            UINT8       suppressAlternateChannelToken       : 1;    
            UINT8       suppressPauseOnRemovalToken         : 1;    

            UINT8       suppressLineOutUsageToken           : 1;    
            UINT8       suppressGetiPodOptions              : 1;    
            UINT8       suppressSerialNumber                : 1;    
            UINT8       suppressMetadata                    : 1;    
            UINT8                                           : 4;

            UINT8       commandDelay;                               
        };
    } operationalParameters;

} IPOD_APPLICATION_INFORMATION;


    
    
#line 1982 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    
    
#line 1985 "../../../../Microchip/Include/MFI/MFI_iPod.h"

    
#line 1988 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    
#line 1990 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    
#line 1992 "../../../../Microchip/Include/MFI/MFI_iPod.h"



#line 1998 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef struct
{
    UINT8   lingo;          
    UINT16  command;        
    UINT16  transactionID;  
    UINT8   *pData;         
    UINT16  dataLength;     
} IPOD_COMMAND;




#line 2015 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef struct
{
    UINT8       lingo;          
    UINT16_VAL  version;        
} IPOD_LINGO_VERSION_INFORMATION;




#line 2030 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[6];

        UINT8                                           : 1;    
        UINT8   BluetoothConnectionStatus               : 1;
        UINT8                                           : 1;
        UINT8   NowPlayingApplicationDisplayNameStatus  : 1;
        UINT8   AssistiveTouchStatus                    : 1;
        UINT8                                           : 1;
        UINT8                                           : 1;    
        UINT8                                           : 1;

        UINT8                                           : 1;    
        UINT8   DatabaseAvailable                       : 1;
        UINT8   NowPlayingFocusApp                      : 1;
        UINT8   SessionSpaceAvailable                   : 1;
        UINT8                                           : 1;
        UINT8   CommandCompleted                        : 1;
        UINT8                                           : 1;    
        UINT8   iPodOutModeStatus                       : 1;

        UINT8                                           : 1;    
        UINT8                                           : 1;    
        UINT8   FlowControl                             : 1;
        UINT8   RadioTaggingStatus                      : 1;
        UINT8   CameraStatus                            : 1;
        UINT8   ChargingInfo                            : 1;
        UINT8                                           : 1;    
        UINT8                                           : 1;    
    };
} IPOD_NOTIFICATIONS_BITMASK;




#line 2077 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_ACCESSORY_EQUALIZER;




#line 2099 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_ACCESSORY_POWER;




#line 2121 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   avSynchronization               : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_DIGITAL_AUDIO;




#line 2143 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   volumeControl                   : 1;    
        UINT8   absoluteVolumeControl           : 1;    
        UINT8   geniusPlaylistCreation          : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_DISPLAY_REMOTE;




#line 2167 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   videoBrowsing                   : 1;    
        UINT8   extendedInterfaceEnhancements   : 1;    
        UINT8   nestedPlaylists                 : 1;    
        UINT8   geniusPlaylistCreation          : 1;    
        UINT8   supportsSetDisplayImage         : 1;    
        UINT8   accessibleCategoryList          : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_EXTENDED_INTERFACE;




#line 2195 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[4];

        UINT8   requestApplicationLaunch        : 1;    
        UINT8                                   : 1;    
        UINT8   audioRouteSwitching             : 1;    
        UINT8   USBHostModeCapable              : 1;    
        UINT8   USBHostModeAudioOutput          : 1;    
        UINT8   USBHostModeAudioInput           : 1;    
        UINT8   maxCurrentNotSupported          : 1;    
        UINT8                                   : 1;    

        UINT8                                   : 3;    
        UINT8   pauseOnPowerRemoval             : 1;    
        UINT8                                   : 3;    
        UINT8   extendedIDPSTokens              : 1;    

        UINT8   videoAspectRatio_4_3            : 1;    
        UINT8   videoAspectRatio_16_9           : 1;    
        UINT8   subtitles                       : 1;    
        UINT8   videoAlternateAudioChannel      : 1;    
        UINT8                                   : 1;    
        UINT8   iPhoneOS3Applications           : 1;    
        UINT8   iPodNotifications               : 1;    
        UINT8                                   : 1;    

        UINT8   lineOutUsage                    : 1;    
        UINT8   videoOutput                     : 1;    
        UINT8   NTSCVideoSignal                 : 1;    
        UINT8   PALVideoSignal                  : 1;    
        UINT8   compositeVideoOutConnection     : 1;    
        UINT8   sVideoOutConnection             : 1;    
        UINT8   componentVideoOutConnection     : 1;    
        UINT8   closedCaptioning                : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_GENERAL;




#line 2247 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   iPodOutAvailable                : 1;    
        UINT8                                   : 7;    
    };
} IPOD_OPTIONS_FOR_LINGO_IPOD_OUT;




#line 2270 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   acceptsLocationData             : 1;    
        UINT8   sendsLocationData               : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_LOCATION;




#line 2293 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_MICROPHONE;




#line 2315 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   supportRDSRawMode               : 1;    
        UINT8   supportHDRadioTuning            : 1;    
        UINT8   supportAMRadioTuning            : 1;    
        UINT8                                   : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_RF_TUNER;




#line 2340 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[6];

        UINT8   cameraMediaControls             : 1;    
        UINT8   USB_HID_Commands                : 1;    
        UINT8   VoiceOverControls               : 1;    
        UINT8   VoiceOverPreferences            : 1;    
        UINT8   AssistiveTouchCursor            : 1;    
        UINT8                                   : 3;    

        UINT8   contextSpecificControls         : 1;    
        UINT8   audioMediaControls              : 1;    
        UINT8   videoMediaControls              : 1;    
        UINT8   imageMediaControls              : 1;    
        UINT8   sportsMediaControls             : 1;    
        UINT8                                   : 3;    
    };
} IPOD_OPTIONS_FOR_LINGO_SIMPLE_REMOTE;




#line 2374 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8                                   : 1;    
        UINT8   nikeiPodCardioEquipment         : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_SPORTS;




#line 2397 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   iTunesTagging                   : 1;    
        UINT8   nikeiPodCardioEquipment         : 1;    
    };
} IPOD_OPTIONS_FOR_LINGO_STORAGE;




#line 2420 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8       bytes[8];
    struct  
    {
        UINT8   reserved[7];

        UINT8   invokedByHardware               : 1;    
        UINT8   invokedByFirmware               : 1;    
        UINT8                                   : 6;    
    };
} IPOD_OPTIONS_FOR_LINGO_USB_HOST_MODE;




#line 2439 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef struct
{
    UINT16_VAL      transportMaxPayloadSize;                

    union
    {
        UINT8       value;
        struct
        {
            UINT8   successfulIDPS                          : 1;    
            UINT8   supportsVideoOutput                     : 1;    
            UINT8   supportsSetiPodPreferences              : 1;    
            UINT8   supportsDigitalAudio                    : 1;    
            UINT8   digitalAudioRequiresExtendedInterface   : 1;    
        };
    } flags;
} IPOD_INFORMATION;




#line 2465 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union
{
    UINT8   value;
    struct
    {
        UINT8   identifying                 : 1;
        UINT8   authenticating              : 1;
        UINT8   receivingCommand            : 1;
        UINT8   commandInBuffer             : 1;
        UINT8   transmittingCommand         : 1;
        UINT8   commandReadyToTransmit      : 1;
        UINT8   processingDigitalAudio      : 1;
        UINT8   commandDelayInProgress      : 1;
    };
} IPOD_COMMUNICATION_STATUS;




#line 2491 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef struct
{
    UINT16  token;      
    UINT8   item;       
                        
                        
    UINT8   status;     
    UINT8   action;     
                        
                        
} IPOD_TOKEN_PROBLEM_INFO;




#line 2520 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union   _IPOD_DATA_FORMAT_IN
{
    UINT8               byteArray[(1 + 3 + 136  + 1) ];    

    struct
    {
        UINT8           startByte;      
        union
        {
            struct
            {
                UINT8   payloadLengthMarker;    
                UINT8   payloadLengthMSB;       
                UINT8   payloadLengthLSB;       
                UINT8   lingoID;                
                UINT8   commandID;              
                UINT8   commandData[136  - 2]; 
                UINT8   checksum;               
            }           largePacket;
            struct
            {
                UINT8   payloadLengthMarker;    
                UINT8   payloadLengthMSB;       
                UINT8   payloadLengthLSB;       
                UINT8   lingoID;                
                UINT8   commandMSB;             
                UINT8   commandLSB;             
                UINT8   commandData[136  - 3];  
                UINT8   checksum;               
            }           largeTelegram;
            struct
            {
                UINT8   payloadLength;          
                UINT8   lingoID;                
                UINT8   commandID;              
                UINT8   commandData[136  - 2]; 
                UINT8   checksum;               
            }           smallPacket;
            struct
            {
                UINT8   payloadLength;          
                UINT8   lingoID;                
                UINT8   commandMSB;             
                UINT8   commandLSB;             
                UINT8   commandData[136  - 3]; 
                UINT8   checksum;               
            }           smallTelegram;
        }               command;
    };
} IPOD_DATA_FORMAT_IN;



#line 2587 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
typedef union   _IPOD_DATA_FORMAT_OUT
{
    UINT8               byteArray[(1 + 3 + 136  + 1) ];    

    struct
    {
        UINT8           startByte;      
        union
        {
            struct
            {
                UINT8   payloadLengthMarker;    
                UINT8   payloadLengthMSB;       
                UINT8   payloadLengthLSB;       
                UINT8   lingoID;                
                UINT8   commandID;              
                UINT8   commandData[136  - 2]; 
                UINT8   checksum;               
            }           largePacket;
            struct
            {
                UINT8   payloadLengthMarker;    
                UINT8   payloadLengthMSB;       
                UINT8   payloadLengthLSB;       
                UINT8   lingoID;                
                UINT8   commandMSB;             
                UINT8   commandLSB;             
                UINT8   commandData[136  - 3];  
                UINT8   checksum;               
            }           largeTelegram;
            struct
            {
                UINT8   payloadLength;          
                UINT8   lingoID;                
                UINT8   commandID;              
                UINT8   commandData[136  - 2]; 
                UINT8   checksum;               
            }           smallPacket;
            struct
            {
                UINT8   payloadLength;          
                UINT8   lingoID;                
                UINT8   commandMSB;             
                UINT8   commandLSB;             
                UINT8   commandData[136  - 3]; 
                UINT8   checksum;               
            }           smallTelegram;
        }               command;
    };
} IPOD_DATA_FORMAT_OUT;








    
    
    
    
    
    
    
    
    
extern IPOD_APPLICATION_INFORMATION            mfi_iPodApplicationInformation;

    
    
    
    
extern const rom  UINT16                        mfi_Version;








#line 2693 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
#line 2697 "../../../../Microchip/Include/MFI/MFI_iPod.h"



#line 2723 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
BOOL MFI_HandleiPodEvents( MFI_EVENT event, void *data, UINT32 size );










#line 2753 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

UINT32 MFI_GetBigEndianUINT32( UINT8 *data );



#line 2841 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

UINT8 * MFI_GetCommandBufferPointer( UINT8 lingoID, UINT16 commandDataSize );



#line 2875 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

UINT16 MFI_GetMaxCommandDataSize( UINT8 lingoID );



#line 2903 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

IPOD_COMMUNICATION_STATUS MFI_GetStatus( void );



#line 3030 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

UINT8 MFI_Initialize( IPOD_APPLICATION_INFORMATION *iPodApplicationInformation );



#line 3061 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

void MFI_RestartIDPS ( void );



#line 3171 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

UINT8 MFI_SendCommand( BOOL assignTransactionID, UINT8 lingoID, UINT16 commandID,
    UINT16 commandDataSize, UINT16 *transactionID );



#line 3208 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

UINT8 MFI_SetVideoPreference( UINT8 classID, UINT8 settingID, UINT8 restoreOnExit,
        UINT16 *transactionID );



#line 3233 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

void MFI_Shutdown( void );



#line 3262 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 

void MFI_Tasks( void );




























#line 3354 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
#line 3356 "../../../../Microchip/Include/MFI/MFI_iPod.h"
    void MFI_UART_ISR( void );
#line 3358 "../../../../Microchip/Include/MFI/MFI_iPod.h"



#line 3407 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
#line 3409 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 3411 "../../../../Microchip/Include/MFI/MFI_iPod.h"



#line 3446 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
#line 3450 "../../../../Microchip/Include/MFI/MFI_iPod.h"


#line 3484 "../../../../Microchip/Include/MFI/MFI_iPod.h"
 
#line 3488 "../../../../Microchip/Include/MFI/MFI_iPod.h"









#line 3498 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 3518 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 3541 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 3554 "../../../../Microchip/Include/MFI/MFI_iPod.h"







#line 3562 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 3586 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 3612 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 3638 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 3664 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 3667 "../../../../Microchip/Include/MFI/MFI_iPod.h"

#line 3669 "../../../../Microchip/Include/MFI/MFI_iPod.h"
#line 70 "../../../../Microchip/MFI/MFI_iPod_UART.c"

#line 1 "../../../../Microchip/Include/MFI/MFI_iPod_UART.h"

#line 10 "../../../../Microchip/Include/MFI/MFI_iPod_UART.h"
 

#line 59 "../../../../Microchip/Include/MFI/MFI_iPod_UART.h"
 

#line 1 "../PIC18/HardwareProfile.h"


#line 32 "../PIC18/HardwareProfile.h"
 


#line 36 "../PIC18/HardwareProfile.h"


#line 1 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 5 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 7 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 9 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 11 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 13 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 15 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 17 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 19 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 21 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 23 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 25 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 27 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 29 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 31 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 33 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 35 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 37 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 39 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 41 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 43 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 45 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 47 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 49 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 51 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 53 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 55 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 57 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 59 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 61 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 63 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 65 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 67 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 69 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 71 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 73 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 75 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 77 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 79 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 81 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 83 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 85 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 87 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 89 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 91 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 93 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 95 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 97 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 99 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 101 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 103 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 105 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 107 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 109 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 111 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 113 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 115 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 117 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 119 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 121 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 123 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 125 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 127 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 129 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 131 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 133 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 135 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 137 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 139 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 141 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 143 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 145 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 147 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 149 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 151 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 153 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 155 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 157 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 159 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 161 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 163 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 165 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 167 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 169 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 171 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 173 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 175 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 177 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 179 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 181 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 183 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 185 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 187 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 189 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 191 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 193 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 195 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 197 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 199 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 201 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 203 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 205 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 207 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 209 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 211 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 213 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 215 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 217 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 219 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 221 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 223 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 225 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 227 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 229 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 231 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 233 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 235 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 237 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 239 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 241 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 243 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 245 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 247 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 249 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 251 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 253 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 255 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 257 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 259 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 261 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 263 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 265 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 267 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 269 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 271 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 273 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 275 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 277 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 279 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 281 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 283 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 285 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 287 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 289 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 291 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 293 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 295 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 297 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 299 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 301 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 303 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 305 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 307 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 309 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 311 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 313 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 315 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 317 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 319 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 321 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 323 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 325 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 327 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 329 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 331 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 333 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 335 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 337 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 339 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 341 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 343 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 345 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 347 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 349 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 351 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 353 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 355 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 357 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 359 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 361 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 363 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 365 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 367 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 369 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 371 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 373 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 375 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 377 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 379 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 381 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 383 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 385 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 387 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 389 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 391 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 393 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 395 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 397 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 399 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 401 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 403 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 405 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 407 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 409 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 411 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 413 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 415 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 417 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 419 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 421 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 423 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 425 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 427 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 429 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 431 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 433 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 435 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 437 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 439 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 441 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 443 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 445 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 447 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 449 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 451 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 453 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 455 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 457 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 459 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 461 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 463 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 465 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 467 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 469 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 471 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 473 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 475 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 477 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 479 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 481 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 483 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 485 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 487 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 489 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 491 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 493 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 495 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 497 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 499 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 501 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 503 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 505 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 507 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 509 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 511 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 513 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 515 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 517 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 519 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 521 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 523 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 525 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 527 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 529 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 531 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 533 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 535 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 537 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 539 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 541 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 543 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 545 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 547 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 549 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 551 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 553 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 555 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 557 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 559 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 561 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 563 "/Applications/microchip/mplabc18/v3.40/bin/../h/p18cxxx.h"
#line 38 "../PIC18/HardwareProfile.h"








#line 47 "../PIC18/HardwareProfile.h"

#line 49 "../PIC18/HardwareProfile.h"
#line 50 "../PIC18/HardwareProfile.h"

#line 52 "../PIC18/HardwareProfile.h"






#line 59 "../PIC18/HardwareProfile.h"
#line 68 "../PIC18/HardwareProfile.h"
#line 76 "../PIC18/HardwareProfile.h"
#line 77 "../PIC18/HardwareProfile.h"








#line 86 "../PIC18/HardwareProfile.h"
#line 87 "../PIC18/HardwareProfile.h"

#line 89 "../PIC18/HardwareProfile.h"
#line 90 "../PIC18/HardwareProfile.h"
#line 91 "../PIC18/HardwareProfile.h"
#line 92 "../PIC18/HardwareProfile.h"





#line 98 "../PIC18/HardwareProfile.h"
#line 99 "../PIC18/HardwareProfile.h"
#line 100 "../PIC18/HardwareProfile.h"
#line 101 "../PIC18/HardwareProfile.h"
#line 102 "../PIC18/HardwareProfile.h"
#line 103 "../PIC18/HardwareProfile.h"


#line 107 "../PIC18/HardwareProfile.h"
#line 108 "../PIC18/HardwareProfile.h"
#line 109 "../PIC18/HardwareProfile.h"
#line 110 "../PIC18/HardwareProfile.h"

#line 112 "../PIC18/HardwareProfile.h"


#line 115 "../PIC18/HardwareProfile.h"
#line 116 "../PIC18/HardwareProfile.h"
#line 117 "../PIC18/HardwareProfile.h"




#line 122 "../PIC18/HardwareProfile.h"
    
    
#line 125 "../PIC18/HardwareProfile.h"
#line 129 "../PIC18/HardwareProfile.h"
    
    
#line 132 "../PIC18/HardwareProfile.h"
#line 134 "../PIC18/HardwareProfile.h"
#line 135 "../PIC18/HardwareProfile.h"
#line 137 "../PIC18/HardwareProfile.h"
#line 138 "../PIC18/HardwareProfile.h"
#line 140 "../PIC18/HardwareProfile.h"
#line 141 "../PIC18/HardwareProfile.h"
#line 143 "../PIC18/HardwareProfile.h"
    
#line 145 "../PIC18/HardwareProfile.h"
#line 146 "../PIC18/HardwareProfile.h"
#line 147 "../PIC18/HardwareProfile.h"
#line 148 "../PIC18/HardwareProfile.h"
#line 149 "../PIC18/HardwareProfile.h"
    
#line 151 "../PIC18/HardwareProfile.h"
#line 153 "../PIC18/HardwareProfile.h"
#line 154 "../PIC18/HardwareProfile.h"
#line 155 "../PIC18/HardwareProfile.h"
#line 157 "../PIC18/HardwareProfile.h"
#line 158 "../PIC18/HardwareProfile.h"
    
#line 160 "../PIC18/HardwareProfile.h"
#line 161 "../PIC18/HardwareProfile.h"
#line 163 "../PIC18/HardwareProfile.h"
#line 164 "../PIC18/HardwareProfile.h"
#line 165 "../PIC18/HardwareProfile.h"
#line 166 "../PIC18/HardwareProfile.h"
    
#line 168 "../PIC18/HardwareProfile.h"
