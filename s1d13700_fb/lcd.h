/* 
 * File:   lcd.h
 * Author: ynki9
 *
 * Created on April 12, 2011, 8:50 PM
 */

#ifndef LCD_H
#define	LCD_H
#include "port_def.h"

#define LCD_PORT PORT_B
#define LCD_D0 get_gpio_pin(J6_10_PIO)     //Protim lcd data pin 0
#define LCD_D1 get_gpio_pin(J6_11_PIO     //Protip lcd data pin 1
#define LCD_D2 get_gpio_pin(J6_12_PIO)     //Protim lcd data pin 2
#define LCD_D3 get_gpio_pin(J6_13_PIO)     //Protip lcd data pin 3
#define LCD_D4 get_gpio_pin(J6_14_PIO)     //Protim lcd data pin 4
#define LCD_D5 get_gpio_pin(J6_15_PIO)     //Protip lcd data pin 5
#define LCD_D6 get_gpio_pin(J6_16_PIO)     //Protim lcd data pin 6
#define LCD_D7 get_gpio_pin(J6_17_PIO)     //Protip lcd data pin 7
#define LCD_A0 get_gpio_pin(J6_23_PIO)    //Protip lcd address 0 pin
#define LCD_WR get_gpio_pin(J6_24_PIO)    //Protip lcd write pin
#define LCD_RD get_gpio_pin(J6_25_PIO)    //Protip lcd read pin
#define LCD_CS get_gpio_pin(J6_22_PIO)    //Protip chip select pin
#define LCD_RST get_gpio_pin(J6_21_PIO)   //Protip lcd reset pin
//#define LCD_ADJ get_gpio_pin(J6_26_PIO)   //Protip lcd adjust pin
#define LCD_DOFF get_gpio_pin(J6_7_PIO)   //Protip lcd adjust pin

#define LCD_BASE_PIN LCD_D0
#define LCD_REG(x) (LCD_PORT+(x))

#define LCD_CS_VAL (0x00000001<<LCD_CS)
#define LCD_RST_VAL (0x00000001<<LCD_RST)
#define LCD_DOFF_VAL (0x00000001<<LCD_DOFF)
#define LCD_A0_VAL (0x00000001<<LCD_A0)
#define LCD_WR_VAL (0x00000001<<LCD_WR)
#define LCD_RD_VAL (0x00000001<<LCD_RD)
#define LCD_DATA_MASK (0x000000ff<<LCD_BASE_PIN)
#define LCD_PORT_MASK (LCD_DATA_MASK|LCD_CS_VAL|LCD_RST_VAL|LCD_A0_VAL|LCD_WR_VAL|LCD_RD_VAL|LCD_DOFF_VAL)


#define clrbit(x) __raw_writel((x) ,LCD_PORT + PIO_CODR )
#define setbit(x) __raw_writel((x)  ,LCD_PORT + PIO_SODR )

//#define LCD_CLEAR UNDEFINED
#define LCD_DATA_DIR_OUT() __raw_writel((LCD_DATA_MASK) , LCD_PORT + PIO_OER)
#define LCD_DATA_DIR_IN() __raw_writel((LCD_DATA_MASK), LCD_PORT + PIO_ODR)
#define LCD_CLEAR_DATA() __raw_writel((LCD_DATA_MASK), LCD_PORT + PIO_CODR)

#define LCD_SET_DATA(x) LCD_CLEAR_DATA(); __raw_writel(((unsigned int)(x))<<LCD_BASE_PIN, LCD_PORT + PIO_SODR)


#define WAIT(x) ndelay((x));
#define SLEEP(x) msleep((x));

/*Display Commands*/
#define 	LCD_SYS_SET             0x40
#define 	LCD_SLEEP_IN   		0x53
#define 	LCD_DISP_OFF   		0x58
#define 	LCD_DISP_ON   		0x59
#define 	LCD_SCROLL   		0x44
#define 	LCD_CSRFORM   		0x5d
#define 	LCD_CGRAM_ADR   	0x5c
#define 	LCD_CSRDIR_U   		0x4e
#define 	LCD_CSRDIR_D   		0x4f
#define 	LCD_CSRDIR_L   		0x4d
#define 	LCD_CSRDIR_R   		0x4c
#define 	LCD_HDOT_SCR   		0x5a
#define 	LCD_OVLAY   		0x5b
#define 	LCD_CSRW   		0x46
#define 	LCD_CSRR   		0x47
#define 	LCD_MWRITE   		0x42
#define 	LCD_MREAD   		0x43


#define 	LCD_SCR_WIDTH   	319
#define 	LCD_M0   			0
#define 	LCD_M1   			0
#define 	LCD_M2   			0
#define 	LCD_WS   			0
#define 	LCD_IV   			1
#define 	LCD_FX   			7
#define 	LCD_FY   			7
#define 	LCD_WF   			1
#define 	LCD_CR   			39
#define 	LCD_TCR   			90
#define 	LCD_LF   			239
#define 	LCD_APL   			40
#define 	LCD_APH   			0
#define 	LCD_LINES   		30
#define 	LCD_SAD1L   		0
#define 	LCD_SAD1H   		0
#define 	LCD_SL1   		0xEF
#define 	LCD_SAD2L   		0xB0
#define 	LCD_SAD2H   		0x04
#define 	LCD_SL2   		0xEF
#define 	LCD_SAD3L   		0
#define 	LCD_SAD3H  		0
#define 	LCD_SAD4L   		0
#define 	LCD_SAD4H   		0
#define 	LCD_CRX   		0x04
#define 	LCD_CRY   		0x07
#define 	LCD_CM   			0
#define 	LCD_MX0   			1
#define 	LCD_MX1   			0
#define 	LCD_DM1   			0
#define 	LCD_DM2   			0
#define 	LCD_OV   			0
#define 	LCD_SAGL   			0
#define 	LCD_SAGH   			0x70
#define 	LCD_SCRD   			0
#define 	LCD_FLASH   		0x06
#define 	LCD_TEXTSIZE   		((LCD_SAD2H << 8) + LCD_SAD2L)

#define		LCD_GRAPHICSTART	((LCD_SAD2H << 8) + LCD_SAD2L)

#define 	LCD_GRAPHICSIZE   	((LCD_SL2+1) * (LCD_SCR_WIDTH+1))>>3
#define 	LCD_MEM_END   		10800
#define 	LCD_SYS_P1   		0x10 | (LCD_IV << 5) | (LCD_WS << 3) | (LCD_M2 << 2) | (LCD_M1 << 1) | LCD_M0
#define 	LCD_SYS_P2   		0x00 | (LCD_WF << 7) | LCD_FX
#define 	LCD_CSRF_P2   		0x00 | (LCD_CM << 7) | LCD_CRY
#define 	LCD_OVLAY_P1   		0x00 | (LCD_OV << 4) | (LCD_DM2 << 3) | (LCD_DM1 << 2) | (LCD_MX1 << 1) | LCD_MX0

/** Writes command to LCD, or DATA **/
void  LCD_writeCMD(unsigned char data);
void  LCD_writeData(unsigned char data);
unsigned char  LCD_readData(void);
void LCD_writeText(unsigned char * text);
void LCD_writeBuffer(const unsigned char* buffer, int count);
void LCD_hardReset(void);
void LCD_off(void);
/**Initialize LCD**/
//void LCD_initPort(void);
void  LCD_init(void);
//
void LCD_ClearText(void);
void LCD_clear(void);
void LCD_TextGoTo(unsigned char x, unsigned char y);
void LCD_SetCursorAddress(unsigned int address);

#endif	/* LCD_H */

