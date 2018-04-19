/*
 * uart.c -- The UART interface functions for CKM5108
 *
 * Copyright (C) 2008  Hangzhou C-SKY Microsystems Co., Ltd
 */

#include "ckconfig.h"
#include "ckuart.h"
#include <stdarg.h>
#include <stdio.h>

#ifndef CONFIG_SYS_SPARK
#include "uart.h"
#endif

//extern void main();
//
//int firstc ()
//{
//#if !(CONFIG_SYS_SPARK)
//    uart_init (BAUDRATE);
//#endif
//
//        main();
//
//    return 0;
//}


static int __need_init_uart = 1;

_UART  whichuart = UART0;

U32    MCLK = UART_FREQ;
//int printf ( const char *fmt, ... );
static void delay ( int sec )
{
    int i;
    volatile int j;
   
    for (i = 0x00; i < sec * 100; i ++)
        j = i;
}

static _UART GetUart ( void )
{
    return whichuart;
}

void SetUart ( _UART pUart )
{
    whichuart = pUart;
}

/*
 * Initial uart selected. 
 */
int uart_init( U32 ulBaudRate )
{
    _UART  pUart = whichuart;
    U32 uDivisor;


    while (pUart[UART_USR] & 0x01);

    uDivisor = ((MCLK / ulBaudRate) >> 4);
    pUart[UART_LCR] = LCR_SEL_DLR | LCR_WORD_SIZE_8;

    pUart[UART_DLL] =  uDivisor & 0xff;

    pUart[UART_DLH] = (uDivisor >> 8) & 0xff;

    /* clear DLAB and set operation mode with no parity, 8 bits and 1 stop bit */
    pUart[UART_LCR]  = 0x03;  
    /* rcvc watermark 1/4 full, tx fifo 1/2 full,FCR_BYTE_1; */
    pUart[UART_FCR]  = 0x00;  
    pUart[UART_MCR]  = 0x00;   	
    return 0x00;
}

/*
 * Change uart baud rate.
 */
int change_uart_baudrate(unsigned int baudrate)
{
    if ((baudrate == 4800) || (baudrate == 9600) ||
        (baudrate == 14400) || (baudrate == 19200) ||
        (baudrate == 38400) || (baudrate == 56000) ||
        (baudrate == 57600) || (baudrate == 115200))
    {
        printf("\r\nPlease change Baudrate of Terminal!");
        uart_init(baudrate);
    }
    else
    {
        printf("\r\nBaudrate inputted is not support!");
    } 
}


void EnableUart ( void ) 
{
    _UART  pUart = whichuart;

    pUart[UART_IER] |= IER_RDAR_INT_ENABLE;
}

void DisableUart ( void ) 
{
    _UART  pUart = whichuart;

    pUart[UART_IER] &= ~IER_RDAR_INT_ENABLE;
}

/*
 * Receive data from UART to pucData.
 */
int UartRead ( U8 * pucData, U32 ulNumBytes, U32 * pulBytesRead )
{
    _UART  pUart = whichuart;

    *pulBytesRead = 0;
    if (1)
    {
        while (*pulBytesRead < ulNumBytes)
        {
            while ((pUart[UART_LSR] & LSR_DATA_READY) == 0);
            *pucData = pUart[UART_RBR];
            (*pulBytesRead)++;
            if ((*pulBytesRead == ulNumBytes) || (*pucData == 0))
                break;
            pucData++;
        }
    }
   
    return (*pulBytesRead);
}

/*
 *  Output data in pucData to UART in byte.
 */
int UartWrite ( U8 *pucData, U32 ulNumBytes, U32 *pulBytesWritten )
{
    _UART  pUart = whichuart;

    *pulBytesWritten = 0;
    while (*pulBytesWritten < ulNumBytes)
    {
        while ((pUart[UART_LSR] & LSR_TRANS_EMPTY) == 0);
        pUart[UART_THR] = *pucData;
        (*pulBytesWritten)++;
        if ((ulNumBytes == *pulBytesWritten) || (*pucData == 0))
            break;
        pucData++;
    }

    return (*pulBytesWritten);
}

/*
 * Is receive a char from UART
 */
int  kbhit ( void )
{
    if(__need_init_uart == 1){
        uart_init(19200);
        __need_init_uart = 0;
    }
    _UART  pUart = whichuart;

    return (pUart[UART_LSR] & LSR_DATA_READY);    
}

/*
 * Get a char from UART selected.
 */
int  getkey ( void )
{
    if(__need_init_uart == 1){
        uart_init(19200);
        __need_init_uart = 0;
    }
    _UART  pUart = whichuart;

    return  (int)pUart[UART_RBR];
}

/*
 *  Get a char from UART selected.
 */
int  getchar1 ( void )
{
    if(__need_init_uart == 1){
        uart_init(19200);
        __need_init_uart = 0;
    }
    _UART  pUart = whichuart;

    while ((pUart[UART_LSR] & LSR_DATA_READY));

    return  (int)pUart[UART_RBR];
}

/*
 *  output char "ch" to UART selected.
 */
//void  putchar ( char ch )
int fputc(int ch, FILE *stream)
{
    if(__need_init_uart == 1){
        uart_init(19200);
        __need_init_uart = 0;
    }
    _UART  pUart = whichuart;

    while (!(pUart[UART_LSR] & LSR_TRANS_EMPTY));
    if (ch == '\n')
    {
        pUart[UART_THR] = '\r';
        delay(10);
    }
    pUart[UART_THR] = ch;
}
int  fgetc(FILE *stream)
{
     if(__need_init_uart == 1){
        uart_init(19200);
        __need_init_uart = 0;
    }
      int ch = getchar1();
      fputc(ch, stream);
      return ch;
}
/*
 *  Output string "str" to UART selected.
 */
//void  puts ( const char * str )
//{
//    char * temp = (char *)str;
//
//    while (*temp)
//    {
//        putchar(*(temp ++));
//    }
//}
//
///*
// *
// */
//void * memset( void * s, int c, U32 count )
//{
//    char *xs = (char *)s;
//
//    while (count --)
//    	*xs ++ = c;
//
//    return s;
//}
//
///* 
// *  uq -> string.
// */
//static char *numtostring (unsigned int uq, int base, char *buf )
//{				
//    register char *p, *p0;
//    int n = 0, i;
//
//    p = buf;
//    *buf = 0;
//    do 
//    {
//    	*buf ++ = "0123456789abcdef"[uq % base];
//    	n++;
//    } while (uq /= base);
//    p[n] = '\0';
//	
//    p0 = ++buf;
//    if (base == 16 && n < 8)  //If Hex, the length is fixxed with 8 digitals
//    {
//        for (i = 0; i < 8 - n; i++)
//        {
//            p0[i] = '0';
//        }
//        for (; i < 8; i++)
//        {
//    	    p0[i] = p[8 - i - 1];
//        }
//        p0[8] = '\0';
//    }
//    else
//    {
//        for (i = 0; i < n; i++)
//        {
//    	    p0[i] = p[n - i - 1];
//        }
//        p0[n] = '\0';
//    }
//
//    return (p0);
//}
//
//
///*
// *  printf: output the string to uart with format, Same to prinrf in libc.
// */
//int printf ( const char *fmt, ... )
//{
//    const char *s;
//    int        value;
//    U32        ptr;
//    char       ch, buf[64], *pbuf;
//    va_list    ap;
//#if CONFIG_SYS_SPARK
//    return 0;
//#endif
//    va_start(ap, fmt);
//    while (*fmt) 
//    {
//        if (*fmt != '%')
//    	{
//	    putchar(*fmt++);
//            continue;
//        }
//
//    	switch (*++fmt)
//    	{
//      	    case 's':
//            	s = va_arg(ap, const char *);
//                puts(s);
//               	break;
//            case 'd':
//                value = va_arg(ap, int);
//                if (value < 0)
//                {
//                    putchar('-');
//                    value = 0 - value;
//                }
//		pbuf = numtostring((unsigned int)value, 10, buf);
//                puts(pbuf);
//                break;
//            case 'x':
//                value = va_arg(ap,int);
//                pbuf = numtostring((unsigned int)value, 16, buf);
//                puts(pbuf);
//                break;
//            case 'c':
//                ch = (U8)va_arg(ap, int);
//                pbuf = &ch;	
//                putchar(*pbuf);				
//                break;
//#if 0
//            case 'f':
//            {
//                float    f;
//
//                f = va_arg(ap, float);
//                sprintf(buf, "%f\0", f);
//                puts(buf);
//                break;
//            }
//#endif
//            case 'p':
//                ptr = (U32) va_arg(ap, void *);	
//                pbuf = numtostring(ptr, 16, buf);
//                puts(pbuf);
//		break;	
//            default:  
//                putchar(*fmt);
//                break;
//        }
//        fmt ++;
//    }
//    va_end(ap);
//
//    return 0x01;   
//}
//
