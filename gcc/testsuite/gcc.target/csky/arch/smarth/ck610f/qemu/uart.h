
#ifndef __UART_H__
#define __UART_H__

#include "ckconfig.h"

extern int uart_init( U32 ulBaudRate );
extern int printf ( const char *fmt, ... );

#endif   
