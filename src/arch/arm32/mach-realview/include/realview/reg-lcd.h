#ifndef __REALVIEW_REG_LCD_H__
#define __REALVIEW_REG_LCD_H__

#define REALVIEW_CLCD_BASE	(0x10020000)

#define CLCD_TIM0			(0x000)
#define CLCD_TIM1			(0x004)
#define CLCD_TIM2			(0x008)
#define CLCD_TIM3			(0x00c)
#define CLCD_UBAS			(0x010)
#define CLCD_LBAS			(0x014)
#define CLCD_CNTL			(0x018)
#define CLCD_IMSC			(0x01c)
#define CLCD_RIS			(0x020)
#define CLCD_MIS			(0x024)
#define CLCD_ICR			(0x028)
#define CLCD_UCUR			(0x02c)
#define CLCD_LCUR			(0x030)
#define CLCD_PALETTE		(0x200)

#define CNTL_LCDEN			(1 << 0)
#define CNTL_LCDBPP1		(0 << 1)
#define CNTL_LCDBPP2		(1 << 1)
#define CNTL_LCDBPP4		(2 << 1)
#define CNTL_LCDBPP8		(3 << 1)
#define CNTL_LCDBPP16		(4 << 1)
#define CNTL_LCDBPP24		(5 << 1)
#define CNTL_LCDBW			(1 << 4)
#define CNTL_LCDTFT			(1 << 5)
#define CNTL_LCDMONO8		(1 << 6)
#define CNTL_LCDDUAL		(1 << 7)
#define CNTL_BGR			(1 << 8)
#define CNTL_BEBO			(1 << 9)
#define CNTL_BEPO			(1 << 10)
#define CNTL_LCDPWR			(1 << 11)
#define CNTL_LCDVCOMP(x)	((x) << 12)
#define CNTL_LDMAFIFOTIME	(1 << 15)
#define CNTL_WATERMARK		(1 << 16)

#endif /* __REALVIEW_REG_LCD_H__ */
