#include "lcd.h"
#include <linux/kernel.h>
#include "port_def.h"
#include "lcd.h"
#include <asm/io.h>
#include <linux/delay.h>

static void s1d13700_init_port(void);

void  s1d13700_init(void)
{
    s1d13700_init_port();
    s1d13700_hard_reset();

    s1d13700_write_command(S1D13700_SYS_SET);
    udelay(500);

    s1d13700_write_data(S1D13700_SYS_P1);
    udelay(5);
    s1d13700_write_data(S1D13700_SYS_P2);
    udelay(5);
    s1d13700_write_data(S1D13700_FY);
    udelay(5);
    s1d13700_write_data(S1D13700_CR);
    udelay(5);
    s1d13700_write_data(S1D13700_TCR);
    udelay(5);
    s1d13700_write_data(S1D13700_LF);
    udelay(5);
    s1d13700_write_data(S1D13700_APL);
    udelay(5);
    s1d13700_write_data(S1D13700_APH);
    udelay(5);

    s1d13700_write_command(S1D13700_SCROLL);
    s1d13700_write_data(S1D13700_SAD1L);
    s1d13700_write_data(S1D13700_SAD1H);
    s1d13700_write_data(S1D13700_SL1);
    s1d13700_write_data(S1D13700_SAD2L);
    s1d13700_write_data(S1D13700_SAD2H);
    s1d13700_write_data(S1D13700_SL2);
    s1d13700_write_data(S1D13700_SAD3L);
    s1d13700_write_data(S1D13700_SAD3H);
    s1d13700_write_data(S1D13700_SAD4L);
    s1d13700_write_data(S1D13700_SAD4H);

    s1d13700_write_command(S1D13700_CSRFORM);
    s1d13700_write_data(S1D13700_CRX);
    s1d13700_write_data(S1D13700_CSRF_P2);

    s1d13700_write_command(S1D13700_CGRAM_ADR);
    s1d13700_write_data(S1D13700_SAGL);
    s1d13700_write_data(S1D13700_SAGH);

    s1d13700_write_command(S1D13700_CSRDIR_R);

    s1d13700_write_command(S1D13700_HDOT_SCR);
    s1d13700_write_data(S1D13700_SCRD);

    s1d13700_write_command(S1D13700_OVLAY);
    s1d13700_write_data(S1D13700_OVLAY_P1);

    s1d13700_write_command(S1D13700_GRAYSCALE);
    s1d13700_write_data(S1D13700_BPP_PARAM);

    s1d13700_write_command(S1D13700_DISP_ON);
    s1d13700_write_data(S1D13700_FLASH);
/*

    s1d13700_ClearText();
    s1d13700_ClearGraphic();
*/
}

void s1d13700_init_port(void)
{
    __raw_writel(S1D13700_PORT_MASK, S1D13700_REG(PIO_PUDR));//test
    __raw_writel(S1D13700_PORT_MASK, S1D13700_REG(PIO_OWER) );
    __raw_writel(S1D13700_PORT_MASK, S1D13700_REG(PIO_PER));
    S1D13700_DATA_DIR_OUT();
    __raw_writel(S1D13700_PORT_MASK , S1D13700_REG(PIO_OER));
    __raw_writel(S1D13700_PORT_MASK , S1D13700_REG(PIO_SODR));
}

void s1d13700_clear_text(void)
{
    int i;
    int total;
    total = S1D13700_TEXT_OVLAY_WIDTH * S1D13700_LINES;
    s1d13700_text_goto(0,0);
    for(i = 0; i < total; i++)
	s1d13700_write_text(" ");
}
void s1d13700_text_goto(unsigned char x, unsigned char y)
{
    s1d13700_set_cursor_addr((y * S1D13700_TEXT_OVLAY_WIDTH) + x);
}

void s1d13700_set_cursor_addr(unsigned int address)
{
    s1d13700_write_command(S1D13700_CSRW);
    s1d13700_write_data((unsigned char)(address & 0xFF));
    s1d13700_write_data((unsigned char)(address >> 8));
}

void s1d13700_write_text(unsigned char * text)
{
    s1d13700_write_command(S1D13700_MWRITE);
    while(*text)
            s1d13700_write_data(*text++);
}
void s1d13700_write_line(unsigned char *text)
{
    s1d13700_write_command(S1D13700_MWRITE);
    while(*text)
        s1d13700_write_data(*text++);
}
void s1d13700_write_buffer(const unsigned char* buffer, int count)
{
    int i=0;
    S1D13700_DATA_DIR_OUT();
    s1d13700_write_command(S1D13700_MWRITE);
    for(i = 0 ; i < count ; i++){
        S1D13700_SET_DATA(buffer[i]);
        clrbit(S1D13700_CS_VAL|S1D13700_WR_VAL|S1D13700_A0_VAL);
        WAIT(10);
        setbit(S1D13700_CS_VAL|S1D13700_WR_VAL|S1D13700_A0_VAL);
        WAIT(10);
    }
}
void  s1d13700_write_command(unsigned char data)
{
    S1D13700_DATA_DIR_OUT();
    S1D13700_SET_DATA(data);
    clrbit(S1D13700_CS_VAL|S1D13700_WR_VAL);
    WAIT(6);
    setbit(S1D13700_CS_VAL|S1D13700_WR_VAL);
}

void  s1d13700_write_data(unsigned char data)
{
    S1D13700_DATA_DIR_OUT();
    S1D13700_SET_DATA(data);
    clrbit(S1D13700_CS_VAL|S1D13700_WR_VAL|S1D13700_A0_VAL);
    WAIT(6);
    setbit(S1D13700_CS_VAL|S1D13700_WR_VAL|S1D13700_A0_VAL);
}

unsigned char s1d13700_read_data(void)
{
    unsigned int val;
    S1D13700_DATA_DIR_IN();
    clrbit(S1D13700_CS_VAL);
    WAIT(6);
    clrbit(S1D13700_RD_VAL);
    WAIT(10);
    val = __raw_readl(S1D13700_REG(PIO_ODSR));
    setbit(S1D13700_RD_VAL);
    WAIT(6);
    setbit(S1D13700_CS_VAL);
    return (unsigned char)((val & S1D13700_DATA_MASK)>>S1D13700_BASE_PIN);
}

/*Graphic Routines*/

void s1d13700_graphic_goto(unsigned int x, unsigned int y) {
    s1d13700_set_cursor_addr(S1D13700_GRAPHICSTART + (y * 40 * S1D13700_BPP) + x / 8);
}

void s1d13700_clear_graphic(void)
{
unsigned int i;
s1d13700_set_cursor_addr(S1D13700_GRAPHICSTART);
s1d13700_write_command(S1D13700_MWRITE);
for(i = 0; i < (40 * 240 * (S1D13700_BPP)); i++)
	s1d13700_write_data(0xff);
}

void s1d13700_hard_reset(void)
{
    clrbit(S1D13700_RST_VAL|S1D13700_DOFF_VAL);
    SLEEP(50);
    setbit(S1D13700_RST_VAL|S1D13700_DOFF_VAL);
    SLEEP(50);
}
void s1d13700_off(void)
{
    s1d13700_hard_reset();
    __raw_writel(S1D13700_PORT_MASK, S1D13700_REG(PIO_ODR));
}
void s1d13700_clear(void)
{
    s1d13700_clear_text();
    s1d13700_clear_graphic();
}
