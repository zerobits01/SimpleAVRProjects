/*
    autor zerobtis01
*/
#include <mega16.h>

// Alphanumeric LCD functions
#include <alcd.h>
#include <stdio.h>
// Declare your global variables here


int count = 0;
int sec = 0;
char ST[20];
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{

    if(count++ == 10){
        sec++;
        count = 0;
        lcd_gotoxy(0,0);
        sprintf(ST , "%d" , sec);
        lcd_puts(ST);
    }
    
}

void main(void)
{
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);


// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 0.977 kHz
// Mode: CTC top=OCR0
// OC0 output: Disconnected
// Timer Period: 0.15462 s
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x80;

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1)
      {

      }
}
