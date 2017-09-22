
#ifndef __CKUART_H__
#define __CKUART_H__

#include "ckconfig.h"

#define _UART           volatile U32 *

#define UART0           (volatile U32 *)(0x10015000)
#define UART1           (volatile U32 *)(0x1001b000)
#define UART2           (volatile U32 *)(0x1001c000)
#define UART3           (volatile U32 *)(0x1001d000)
/*
#define UART0           (volatile U32 *)(0xb0015000)
  #define UART0           (volatile U32 *)(0xb001a000)
#define UART1           (volatile U32 *)(0xb001b000)
#define UART2           (volatile U32 *)(0xb001c000)
#define UART3           (volatile U32 *)(0xb001d000)
*/

/* UART frequence definition */
#define UART_FREQ	APB_FREQ

/* CK520 EVB UART registers addr definition */
#define UART_LCR        0x03
#define UART_THR        0x00
#define UART_RBR        0x00
#define UART_DLL        0x00
#define UART_DLH        0x01
#define UART_IER        0x01
#define UART_FCR        0x02
#define UART_IIR        0x02
#define UART_MCR        0x04
#define UART_LSR        0x05
#define UART_MSR        0x06
#define UART_USR        0x1f

#define UART_DIV                0x4
/* UART register bit definitions */
/* CK520 */
#define LCR_SEL_DLR	        0x80
#define LCR_BC_ENABLE		0x40
#define LCR_STICK_PARITY_ENABLE 0x20
#define LCR_PARITY_ENABLE	0x08
#define LCR_PARITY_EVEN         0x10
#define LCR_PARITY_ODD          0x08
#define LCR_WORD_SIZE_6         0x01
#define LCR_WORD_SIZE_7         0x02
#define LCR_WORD_SIZE_8         0x03
#define LCR_STOP_BIT_2          0x40  /* 1.5 stop bit */                        

#define IER_MDM_INT_ENABLE      0x08
#define IER_RCVR_SAT_INT_ENABLE 0x04
#define IER_THER_INT_ENABLE     0x02
#define IER_RDAR_INT_ENABLE     0x01

#define MCR_LB_ENABLE	        0x10

#define LSR_TRANS_EMPTY	        0x40
#define LSR_THR_EMPTP	        0x20
#define LSR_BREAK_INT	        0x10
#define LSR_FRAME_ERROR	        0x08
#define LSR_PARITY_ERROR        0x04
#define LSR_OVERRUN_ERROR       0x02
#define LSR_DATA_READY	        0x01

#define MSR_DATA_CARRIER        0x80
#define MSR_RING_IN	        0x40
#define MSR_DSR		        0x20
#define MSR_CTS		        0x10
#define MSR_DDCD                0x08
#define MSR_TERI                0x04
#define MSR_DDSR                0x20
#define MSR_DCLS                0x01

#define FCR_BYTE_1	        0x00
#define FCR_BYTE_4              0x40
#define FCR_BYTE_8              0x80
#define FCR_BYTE_14             0xc0

/* Flag definitions */
#define UART_BLOCKING 		0x0001
#define UART_STOP_AT_NUL        0x0002

#define RX_CHAR_READY		0x8000
#define RX_STATUS_MASK		0xFF00
#define RX_ERR     			0x4000
#define RX_OVERRUN_ERR			0x2000
#define RX_FRAMING_ERR     		0x1000
#define RX_BREAK     			0x0800
#define RX_PARITY_ERR			0x0400

#define CR1_TX_FIFO_LEVEL_MASK  0xC000
#define CR1_TX_FIFO_LEVEL_14	0xC000
#define CR1_TX_FIFO_LEVEL_8		0x8000
#define CR1_TX_FIFO_LEVEL_4		0x4000
#define CR1_TX_FIFO_LEVEL_1		0x0000
#define CR1_TX_RDY_INT_ENABLE 	0x2000
#define CR1_TX_ENABLE    		0x1000
#define CR1_RX_FIFO_LEVEL_MASK  0x0C00
#define CR1_RX_FIFO_LEVEL_14	0x0C00
#define CR1_RX_FIFO_LEVEL_8		0x0800
#define CR1_RX_FIFO_LEVEL_4		0x0400
#define CR1_RX_FIFO_LEVEL_1		0x0000
#define CR1_RX_RDY_INT_ENABLE 	0x0200
#define CR1_RX_ENABLE    		0x0100
#define CR1_IR_ENABLE    		0x0080
#define CR1_RTS_INT_ENABLE 		0x0020
#define CR1_SEND_BREAK     		0x0010
#define CR1_DOZE	     		0x0002
#define CR1_UART_ENABLE    		0x0001

#define CR2_IGNORE_RTS     		0x4000
#define CR2_CTS_CONTROL    		0x2000
#define CR2_CTS         		0x1000
#define CR2_PARITY_ENABLE  		0x0100
#define CR2_PARITY_ODD     		0x0080
#define CR2_STOP_BITS_2    		0x0040
#define CR2_WORD_SIZE_8    		0x0020

#define SR_TX_EMPTY        		0x8000
#define SR_RTS_STATUS      		0x4000
#define SR_TX_RDY_INT_FLAG 		0x2000
#define SR_RX_RDY_INT_FLAG 		0x0200
#define SR_RTS_CHANGE      		0x0020

#define TR_FORCE_PARITY_ERR		0x2000
#define TR_LOOPBACK       		0x1000
#define TR_IR_LOOPBACK     		0x0400

/* Miscellaneous communications definitions */
#define XON			        0x11
#define XOFF				0x13

/*Uart wait time out number-----*/
#define UART_WRITE_TIMEOUT 0x100

/* Parity definitions */
#define UART_PARITY_NONE	0x0000
#define UART_PARITY_ODD 	0x0001
#define UART_PARITY_EVEN	0x0002

#define CONSOLE   UART0

#define IDLE_COUNT	0x10000

#endif   /* ending __CKUART_H__ */

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
