/*
 * Description: ck5a6.h - Define the system configuration, memory & IO base
 * address, flash size & address, interrupt resource for ck5a6 soc.
 *
 * Copyright (C) : 2008 Hangzhou C-SKY Microsystems Co.,LTD.
 * Author(s): Liu Bing (bing_liu@c-sky.com)
 * Contributors: Liu Bing
 * Date:  2010-06-26
 */

#ifndef __INCLUDE_CK5A6_H
#define __INCLUDE_CK5A6_H

/**************************************
 * MCU & Borads.
 *************************************/

/* PLL input ckock(crystal frequency) */
#define CONFIG_PLL_INPUT_CLK   48000000   /* HZ */
/* CPU frequence definition */
#define CPU_DEFAULT_FREQ       48000000  /* Hz */
/* AHB frequence definition */
#define AHB_DEFAULT_FREQ       48000000   /* Hz */
/* APB frequence definition */
#define APB_DEFAULT_FREQ       48000000   /* Hz */

/**********************************************
 * Config CPU cache
 *********************************************/
/* 0 - rw; 1 - rwc; 2 - rwc; 3 - rw */
/*
#define CONFIG_CKCPU_MGU_BLOCKS         0xff02
*/
#define CONFIG_CKCPU_MGU_BLOCKS         0xff06

/* 0 - baseaddr: 0x0; size: 4G */
#define CONFIG_CKCPU_MGU_REGION1        0x3f
/* 1- baseaddr: 0x8000000; size: 8M */
#define CONFIG_CKCPU_MGU_REGION2        0x00000025
/* 2- baseaddr: 0x8600000; size: 256K for MAC */
#define CONFIG_CKCPU_MGU_REGION3        0x20000025
/* 3- Disable */
#undef CONFIG_CKCPU_MGU_REGION4

/*******************************
 * Config CPU cache
 ******************************/
/*
#define CONFIG_CKCPU_ICACHE             1
#define CONFIG_CKCPU_DCACHE             1
*/
#define CONFIG_CKCPU_ICACHE             0
#define CONFIG_CKCPU_DCACHE             0

/************************************************
 * perpheral module baseaddress and irq number
 ***********************************************/
/**** AHB BUS ****/
#define CK_AHBBUS_BASE			((volatile CK_UINT32*)(0x40001000))

/*
 * SDRAM Config Register set,because ck5a6 need to reset memory when init.
 * TODO: no used configuration
 */
#define MMC_SCONR				(0x10001000)

/***** Intc ******/
/*
#ifdef VIC
*/
#define CK_INTC_BASEADDRESS		(0xe000e100)
/*
#else
#define CK_INTC_BASEADDRESS		(0x40016100)
#endif

#ifdef CTIM
*/
#define CORETIM_BASE          0xe000e010
/*
#else
#define CORETIM_BASE          0x40017010
#endif
*/

/*
 * define irq number of perpheral modules
 */
/*
#define  CK_INTC_GPIO0     0
#define  CK_INTC_GPIO1     1
#define  CK_INTC_GPIO2     2
#define  CK_INTC_GPIO3     3
#define  CK_INTC_GPIO4     4
#define  CK_INTC_GPIO5     5
#define  CK_INTC_GPIO6     6
#define  CK_INTC_GPIO7     7
#define  CK_INTC_GPIO8     8
#define  CK_INTC_GPIO9     9
#define  CK_INTC_GPIO10    10
#define  CK_INTC_USBH      11
#define  CK_INTC_TIM0      12
#define  CK_INTC_TIM1      13
#define  CK_INTC_TIM2      14
#define  CK_INTC_TIM3      15
#define  CK_INTC_UART0     16
#define  CK_INTC_UART1     17
#define  CK_INTC_UART2     18
#define  CK_INTC_SDHC      19
#define  CK_INTC_AC97      20
#define  CK_INTC_SSI       21
#define  CK_INTC_IIC       22
#define  CK_INTC_PWM       23
#define  CK_INTC_Watchdog  24
#define  CK_INTC_RTC	   25
#define  CK_INTC_MAC       26
#define  CK_INTC_USBD      27 
#define  CK_INTC_LCDC      28
#define  CK_INTC_DMAC      29
#define  CK_INTC_LCDC      28
#define  CK_INTC_POWM      30
#define  CK_INTC_NFC       31 
*/
#define  CK_INTC_CTIM      0
#define  CK_INTC_UART0     1

/***** GPIO *****/
#define PCK_GPIOA			((volatile CK_UINT32*)(0x10019000))
#define PCK_GPIOB			((volatile CK_UINT32*)(0x1001900c))
#define PCK_GPIO_Control	((volatile CK_UINT32*)(0x10019030))

/**** MAC *******/
#define CKMAC_BASEADDR		(volatile CK_UINT32*)(0x10006000) /* mac base address */
#define CKMAC_BD_ADDR		(volatile CK_UINT32*)(0x10007400) /* BD base addr*/

/***** Uart *******/
#define CK_UART_ADDRBASE0    (volatile CK_UINT32 *)(0x40015000)

/**** Timer ****/
#define  CK_TIMER0_BASSADDR			(volatile CK_UINT32 *)(0x40011000)
#define  CK_TIMER1_BASSADDR			(volatile CK_UINT32 *)(0x40011014)
#define  CK_TIMER2_BASSADDR			(volatile CK_UINT32 *)(0x40011028)
#define  CK_TIMER3_BASSADDR			(volatile CK_UINT32 *)(0x4001103c)

#define  CK_TIMER_CONTROL_BASSADDR	(volatile CK_UINT32 *)(0x100100a0)

/****** DMA *****/
/*
 * Define DMA channel base address
 */
#define CK_DMAC_CH0_BASEADDR  (volatile CK_UINT32 *)(0x10003000)
#define CK_DMAC_CH1_BASEADDR  (volatile CK_UINT32 *)(0x10003058)
#define CK_DMAC_CH2_BASEADDR  (volatile CK_UINT32 *)(0x100030b0)
#define CK_DMAC_CH3_BASEADDR  (volatile CK_UINT32 *)(0x10003108)

/*
 * Define DMA control base address
 */ 
#define CK_DMAC_CONTROL_BASEADDR  (volatile CK_UINT32 *)(0x100032c0)

/****** IIC *************/
/*
 * Define IIC base address
 */
#define CK_IIC_ADDRBASE0	(volatile CK_UINT32 *)(0x10018000)

/****** SPI *************/
/*
 * Define SPI base address
 */
#define CK_SPI_ADDRBASE0	(volatile CK_UINT32 *)(0x1001a000)

/****** WDT *************/
#define CK_WDT_ADDRBASE		(volatile CK_UINT32 *)(0x10013000)

/****** RTC *************/ 
#define CK_RTC_ADDRBASE		(volatile CK_UINT32 *)(0x10012000)

/****** PWM  *************/
#define CK_PWM_ADDRBASE0	(volatile CK_UINT32 *)(0x10014000)

/****** LCDC  *************/
#define CK_LCD_PALETTE_ADDRBASE (volatile CK_UINT32*)(0x10004800)
#define CK_LCD_ADDRBASE         (volatile CK_UINT32*)(0x10004000)

/****** POWM  *************/
#define CK_POWM_ADDRBASE	(volatile CK_UINT32 *)(0x10002000)

/****** NFC  *************/
#define CK_NFC_ADDRBASE		(volatile CK_UINT32 *)(0x10008000)

/****** AC97  *************/
#define CK_AC97_ADDRBASE	(volatile CK_UINT32 *)(0x1001B000)

/****** SDHC  *************/
#define CK_SDHC_ADDRBASE	(volatile CK_UINT32 *)(0x1001C000)

/****** USBD  *************/
#define CK_USBD_ADDRBASE	(volatile CK_UINT32 *)(0x10005000)

/****** USBH  *************/
#define CK_USBH_ADDRBASE	(volatile CK_UINT32 *)(0x1000B000)

/**** Nor FLASH ****/
#define FLASH_START			0x00000000
#define FLASH_END			0x00800000

#define FLASH_SECTOR_SIZE	0X2000   /* 8kb */
#define FLASH_BLOCK_SIZE	0X20000  /* 128Kb */


#endif /* __INCLUDE_CK5A6_H */
