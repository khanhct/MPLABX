#ifndef __LCD_H
#define __LCD_H

#include"p18f26k20.h"
#include"delays.h"

#define LCD_RS LATAbits.LATA0
#define LCD_RW LATAbits.LATA1
#define LCD_E  LATAbits.LATA2

#define	LCD_D4 LATBbits.LATB4	
#define	LCD_D5 LATBbits.LATB5
#define	LCD_D6 LATBbits.LATB6
#define	LCD_D7 LATBbits.LATB7
//#define lcd_busy LATBbits.LATB7

#define	LCD_clear	0x01	 //Xoa man hinh LCD
#define	LCD_home	0x02	 //Tro ve dau dong
#define	LCD_normal	0x06	 //Che do nhap du lieu binh thuong
#define	LCD_normal_s	0x07	//Che do nhap du lieu binh thuong, dich man hinh
#define	LCD_off 0x08	 //Tat man hinh
#define	LCD_on	 0x0C	 //Bat man hinh
#define	LCD_on_crsr 0x0E	 //Bat man hinh va con tro
#define	LCD_on_blink 0x0F	 //Bat man hinh va con tro (nhap nhay)
#define	LCD_4b2l	0x28	 //Che do 2 dong, giao tiep 4 bit du lieu
#define	LCD_homeL1	0x80	 //Ve dau dong 1
#define	LCD_homeL2	0xC0	 //Ve dau dong 2
#define lcd_line_two 0x40
#define lcd_line_one 0x00
//---------------------------------------------------------------------------------------------------------
//Cac prototype cho cac chuong trinh con
void Init_PORTS(void);
void Init_LCD(void);
void LCD_OK(void);
void LCD_CMD(unsigned char cmd);
void LCD_DATA(unsigned char dat);
void lcd_putstr(char *buffer);
void lcd_gotoxy(int x, int y);
void khoi_tao(void);
void LCD_IN_INTER(unsigned int d);
void LCD_IN_FLOAT( float d);
void lcd_clear(void);
void lcd_int(char a);
void lcd_putch(char data);


void Init_PORTS(void)
{
TRISAbits.TRISA0 = 0;
TRISAbits.TRISA1 = 0; 
TRISAbits.TRISA2 = 0;	 	
TRISBbits.TRISB4 = 0;	 
TRISBbits.TRISB5 = 0;	
TRISBbits.TRISB6 = 0;
TRISBbits.TRISB7 = 0;	
}
void Init_LCD(void)
{
LCD_CMD(0x02);	 //Dat che do giao tiep 4-bit, man hinh 2 dong
Delay1KTCYx(1);
LCD_CMD(0x28);	 //Tat man hinh
Delay1KTCYx(1);
LCD_CMD(0x0C);	 //Che do nhap du lieu binh thuong
Delay1KTCYx(1);
LCD_CMD(0x06 );	 //Bat man hinh, hien con tro nhap nhay
Delay1KTCYx(1);
//LCD_CMD(0x01);	 //Xoa man hinh
Delay1KTCYx(1);
}
void LCD_OK(void)
{
unsigned u;
LCD_E = 1; //Tao xung Enable
for (u = 0; u < 2; u++); //keo dai toi thieu 1 us
LCD_E = 0;
}
void LCD_CMD(unsigned char cmd) 
{
unsigned temp1;
LCD_RW = 0;
LCD_RS = 0; //Dat che do xuat lenh
temp1 = cmd >> 4; //Lay 4 bit cao
LCD_D4 = temp1 & 1; //Xuat 4 bit cao
LCD_D5 = (temp1 & 2) >>1;
LCD_D6 = (temp1 & 4) >>2;
LCD_D7 = (temp1 & 8) >>3;
LCD_OK();
temp1 = cmd & 0x0F; //Lay 4 bit thap
LCD_D4 = temp1 & 1; //Xuat 4 bit thap
LCD_D5 = (temp1 & 2) >>1;
LCD_D6 = (temp1 & 4) >>2;
LCD_D7 = (temp1 & 8) >>3;
LCD_OK();
Delay1KTCYx(5);
}
void LCD_DATA (unsigned char dat) 
{
unsigned temp2;
LCD_RW = 0;
LCD_RS = 1; //Dat che do xuat du lieu
temp2 = dat >> 4; //Lay 4 bit cao
LCD_D4 = temp2 & 1; //Xuat 4 bit cao
LCD_D5 = (temp2 & 2) >>1;
LCD_D6 = (temp2 & 4) >>2;
LCD_D7 = (temp2 & 8) >>3;
LCD_OK();
temp2 = dat & 0x0F; //Lay 4 bit thap
LCD_D4 = temp2 & 1; //Xuat 4 bit thap
LCD_D5 = (temp2 & 2) >>1;
LCD_D6 = (temp2 & 4) >>2;
LCD_D7 = (temp2 & 8) >>3;
LCD_OK();
Delay1KTCYx(5);
}	
void lcd_clear(void)
{
	LCD_CMD(0x01);
}
void lcd_putch(char data)
{
		LCD_DATA(data);
}
void lcd_putstr(char *buffer)
{
	while(*buffer != '\0')
	{
		LCD_DATA(*buffer); /* calling another function */
		/* to write each char to the lcd module */
		buffer++;
		Delay1KTCYx(2);	
	};
}

//-----------Chuong trinh con nhay den cot x, dong y-------------------------------------------------------------------
void lcd_gotoxy(int x, int y)
{
	int address;
	if(y != 1) address = lcd_line_two;
	else address=0;
	address += x-1;
	LCD_CMD(0x80|address);
	Delay1KTCYx(2);
}
void LCD_IN_INTER(unsigned int d)
{
unsigned i,j,k,l;
l=d/1000;//nghin
k=(d%1000)/100;//tram
j=((d%1000)%100)/10;//chuc
i=((d%1000)%100)%10;//donvi
LCD_DATA(0x30+l);
LCD_DATA(0x30+k);
LCD_DATA(0x30+j);
LCD_DATA(0x30+i);
}
void lcd_int(char a)
{
	char x,y;
	x=a/10;
	y=a%10;
	if(x>=1)
	{
		LCD_DATA(0x30 +x);
		LCD_DATA(0x30+y);
	}
	else 
	LCD_DATA(0x30+y);
	
}

//=======giu so thuc len lcd=============================
void LCD_IN_FLOAT( float d)
{
char ch[]=".";
unsigned int e, i,j,k,l;
// d=round(d,1);
e=(int)(d*10);
l=e/1000;//nghin
k=(e%1000)/100;//tram
j=((e%1000)%100)/10;//chuc
i=((e%1000)%100)%10;//donvi
LCD_DATA(0x30+l);
LCD_DATA(0x30+k);
LCD_DATA(0x30+j);
lcd_putstr(ch);
LCD_DATA(0x30+i);
}


#endif

