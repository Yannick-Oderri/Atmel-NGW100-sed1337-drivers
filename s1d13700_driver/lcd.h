/* 
 * File:   S1D13700.h
 * Author: ynki9
 *
 * Created on April 12, 2011, 8:50 PM
 */

#ifndef S1D13700_H
#define	S1D13700_H

#define         S1D13700_BPP                 1
#define         S1D13700_BPP_PARAM          0//((S1D13700_BPP)/(2))

#define S1D13700_PORT PORT_B
#define S1D13700_D0 get_gpio_pin(J6_10_PIO)     //Protim S1D13700 data pin 0
#define S1D13700_D1 get_gpio_pin(J6_11_PIO     //Protip S1D13700 data pin 1
#define S1D13700_D2 get_gpio_pin(J6_12_PIO)     //Protim S1D13700 data pin 2
#define S1D13700_D3 get_gpio_pin(J6_13_PIO)     //Protip S1D13700 data pin 3
#define S1D13700_D4 get_gpio_pin(J6_14_PIO)     //Protim S1D13700 data pin 4
#define S1D13700_D5 get_gpio_pin(J6_15_PIO)     //Protip S1D13700 data pin 5
#define S1D13700_D6 get_gpio_pin(J6_16_PIO)     //Protim S1D13700 data pin 6
#define S1D13700_D7 get_gpio_pin(J6_17_PIO)     //Protip S1D13700 data pin 7
#define S1D13700_A0 get_gpio_pin(J6_23_PIO)    //Protip S1D13700 address 0 pin
#define S1D13700_WR get_gpio_pin(J6_24_PIO)    //Protip S1D13700 write pin
#define S1D13700_RD get_gpio_pin(J6_25_PIO)    //Protip S1D13700 read pin
#define S1D13700_CS get_gpio_pin(J6_22_PIO)    //Protip chip select pin
#define S1D13700_RST get_gpio_pin(J6_21_PIO)   //Protip S1D13700 reset pin
//#define S1D13700_ADJ get_gpio_pin(J6_26_PIO)   //Protip S1D13700 adjust pin
#define S1D13700_DOFF get_gpio_pin(J6_7_PIO)   //Protip S1D13700 adjust pin

#define S1D13700_BASE_PIN S1D13700_D0
#define S1D13700_REG(x) (S1D13700_PORT+(x))

#define S1D13700_CS_VAL (0x00000001<<S1D13700_CS)
#define S1D13700_RST_VAL (0x00000001<<S1D13700_RST)
#define S1D13700_DOFF_VAL (0x00000001<<S1D13700_DOFF)
#define S1D13700_A0_VAL (0x00000001<<S1D13700_A0)
#define S1D13700_WR_VAL (0x00000001<<S1D13700_WR)
#define S1D13700_RD_VAL (0x00000001<<S1D13700_RD)
#define S1D13700_DATA_MASK (0x000000ff<<S1D13700_BASE_PIN)
#define S1D13700_PORT_MASK (S1D13700_DATA_MASK|S1D13700_CS_VAL|S1D13700_RST_VAL|S1D13700_A0_VAL|S1D13700_WR_VAL|S1D13700_RD_VAL|S1D13700_DOFF_VAL)


#define clrbit(x) __raw_writel((x) ,S1D13700_PORT + PIO_CODR )
#define setbit(x) __raw_writel((x)  ,S1D13700_PORT + PIO_SODR )

//#define S1D13700_CLEAR UNDEFINED
#define S1D13700_DATA_DIR_OUT() __raw_writel((S1D13700_DATA_MASK) , S1D13700_PORT + PIO_OER)
#define S1D13700_DATA_DIR_IN() __raw_writel((S1D13700_DATA_MASK), S1D13700_PORT + PIO_ODR)
#define S1D13700_CLEAR_DATA() __raw_writel((S1D13700_DATA_MASK), S1D13700_PORT + PIO_CODR)

#define S1D13700_SET_DATA(x) S1D13700_CLEAR_DATA(); __raw_writel(((unsigned int)(x))<<S1D13700_BASE_PIN, S1D13700_PORT + PIO_SODR)


#define WAIT(x) ndelay((x));
#define SLEEP(x) msleep((x));

/*Display Commands*/
#define 	S1D13700_SYS_SET             0x40
#define 	S1D13700_SLEEP_IN   		0x53
#define 	S1D13700_DISP_OFF   		0x58
#define 	S1D13700_DISP_ON   		0x59
#define 	S1D13700_SCROLL   		0x44
#define 	S1D13700_CSRFORM   		0x5d
#define 	S1D13700_CGRAM_ADR   	0x5c
#define 	S1D13700_CSRDIR_U   		0x4e
#define 	S1D13700_CSRDIR_D   		0x4f
#define 	S1D13700_CSRDIR_L   		0x4d
#define 	S1D13700_CSRDIR_R   		0x4c
#define 	S1D13700_HDOT_SCR   		0x5a
#define 	S1D13700_OVLAY   		0x5b
#define 	S1D13700_CSRW   		0x46
#define 	S1D13700_CSRR   		0x47
#define 	S1D13700_MWRITE   		0x42
#define 	S1D13700_MREAD   		0x43


#define 	S1D13700_SCR_WIDTH   	320
#define 	S1D13700_M0   			0
#define 	S1D13700_M1   			0
#define 	S1D13700_M2   			0
#define 	S1D13700_WS   			0
#define 	S1D13700_IV   			1
#define 	S1D13700_FX   			7
#define 	S1D13700_FY   			7
#define 	S1D13700_WF   			1
#define 	S1D13700_CR   			(S1D13700_SCR_WIDTH/8)*S1D13700_BPP
#define 	S1D13700_TCR   			90
#define 	S1D13700_LF   			239
#define 	S1D13700_APL   			40
#define 	S1D13700_APH   			0
#define 	S1D13700_LINES   		30
#define 	S1D13700_SAD1L   		0
#define 	S1D13700_SAD1H   		0
#define 	S1D13700_SL1   		0xEF
#define 	S1D13700_SAD2L   		0xB0
#define 	S1D13700_SAD2H   		0x04
#define 	S1D13700_SL2   		0xEF
#define 	S1D13700_SAD3L   		0
#define 	S1D13700_SAD3H  		0
#define 	S1D13700_SAD4L   		0
#define 	S1D13700_SAD4H   		0
#define 	S1D13700_CRX   		0x04
#define 	S1D13700_CRY   		0x07
#define 	S1D13700_CM   			0
#define 	S1D13700_MX0   			1
#define 	S1D13700_MX1   			0
#define 	S1D13700_DM1   			0
#define 	S1D13700_DM2   			0
#define 	S1D13700_OV   			0
#define 	S1D13700_SAGL   			0
#define 	S1D13700_SAGH   			0x70
#define 	S1D13700_SCRD   			0
#define 	S1D13700_FLASH   		0x16
#define 	S1D13700_TEXTSIZE   		((S1D13700_SAD2H << 8) + S1D13700_SAD2L)
#define         S1D13700_GRAYSCALE           0x60

#define		S1D13700_GRAPHICSTART	((S1D13700_SAD2H << 8) + S1D13700_SAD2L)

#define 	S1D13700_GRAPHICSIZE   	(((S1D13700_SL2+1) * (S1D13700_SCR_WIDTH+1))>>3)*S1D13700_BPP
#define 	S1D13700_MEM_END   		10800
#define 	S1D13700_SYS_P1   		0x10 | (S1D13700_IV << 5) | (S1D13700_WS << 3) | (S1D13700_M2 << 2) | (S1D13700_M1 << 1) | S1D13700_M0
#define 	S1D13700_SYS_P2   		0x00 | (S1D13700_WF << 7) | S1D13700_FX
#define 	S1D13700_CSRF_P2   		0x00 | (S1D13700_CM << 7) | S1D13700_CRY
#define 	S1D13700_OVLAY_P1   		0x00 | (S1D13700_OV << 4) | (S1D13700_DM2 << 3) | (S1D13700_DM1 << 2) | (S1D13700_MX1 << 1) | S1D13700_MX0
#define         S1D13700_TEXT_OVLAY_WIDTH    ((S1D13700_APH << 8) | (S1D13700_APL))

/** Writes command to S1D13700, or DATA **/
void  s1d13700_write_command(unsigned char data);
void  s1d13700_write_data(unsigned char data);
void s1d13700_set_cursor_addr(unsigned int address);
unsigned char  s1d13700_read_data(void);
void s1d13700_write_text(unsigned char * text);
void s1d13700_write_buffer(const unsigned char* buffer, int count);
void s1d13700_text_goto(unsigned char x, unsigned char y);
void s1d13700_clear_text(void);
void s1d13700_clear_graphic(void);
void s1d13700_graphic_goto(unsigned int x, unsigned int y);
/**Initialize S1D13700**/
//void S1D13700_initPort(void);
void  s1d13700_init(void);
void s1d13700_hard_reset(void);
void s1d13700_off(void);
void s1d13700_clear(void);

#endif	/* S1D13700_H */

