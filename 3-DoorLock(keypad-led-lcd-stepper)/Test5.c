/*
    author : zerobits01
*/
#include <mega16.h>
#include <string.h>
#include <delay.h>
#include <alcd.h>

#define STEPPER PORTB

unsigned char correct[] = "1234";
flash char steps[8] = {0b0011, 0b0010, 0b0110, 0b0100, 0b1100, 0b1000, 0b1001, 0b0001}; // stepper motor half steps

char getKey();


void main(void)
{
// Declare your local variables here
char k; // saving input of keypad
int i = 0; // user input index
unsigned char user[sizeof(correct)] = ""; // for saving user input
bit opened = 0; // for controling stepper and lcd

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);


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
lcd_clear();        
lcd_gotoxy(3,0);
lcd_putsf("enter the pass");
lcd_gotoxy(0,1);
lcd_putsf("pass:");

DDRD = 0xF0;
DDRC.0 = 1;
PORTC.0 = 0;

DDRB = 0x0F;
STEPPER = 0x00;

i = 0;
while (1)
      {     STEPPER = steps[0];
            do{
                k = getKey();   // can be between 0-11
            }while(k==0xFF);
            while(getKey() != 0xFF);
            switch(k){
                case 10 :{
                    // delete
                    strcpy(user,"");
                    i = 0;         
                    lcd_clear();
                    lcd_putsf("cleared");
                    delay_ms(1000);
                    lcd_clear();
                    lcd_gotoxy(3,0);
                    lcd_putsf("enter the pass");
                    lcd_gotoxy(0,1);
                    lcd_putsf("pass:");
    
                }
                 break;
                case 11 :{
                // enter
                    user[i] = '\0';
                    if(strcmp(user, correct) == 0){
                        opened = 1;
                        PORTC.0 = 1;    
                        STEPPER = steps[2];
                        lcd_clear();
                        lcd_gotoxy(0,3);
                        lcd_putsf("opened");
                        while(getKey()!=10);
                        lcd_clear();
                        lcd_gotoxy(3,0);
                        lcd_putsf("enter the pass");
                        lcd_gotoxy(0,1);
                        lcd_putsf("pass:");
                        opened = 0;
                        PORTC.0 = 0;
                        strcpy(user,"");
                        i = 0;
                                 
                    }else{
                            lcd_clear();
                            lcd_gotoxy(0,3);
                            lcd_putsf("wrong pass!"); 
                            delay_ms(1000);
                            strcpy(user,"");
                            i = 0;         
                            lcd_clear();
                            lcd_gotoxy(3,0);
                            lcd_putsf("enter the pass");
                            lcd_gotoxy(0,1);
                            lcd_putsf("pass:");
                    }
                }
                    
                 break;
                default :{  
                    if(i < 4){
                        user[i] = k;
                        lcd_putsf("*");
                    }
                    i++;
                }
            }
             
            
      }
}

char getKey(){ 
char k1 = 0xFF;
char columns;
PORTD.4 = 0;
columns = PIND & 0x07;
if(columns != 0x07){
    switch(columns){
        case 0b110:k1 = '1';break;
        case 0b101:k1 = '2';break;
        case 0b011:k1 = '3';break;
    }
}
PORTD.4 = 1;

PORTD.5 = 0;
columns = PIND & 0x07;
if(columns != 0x07){
    switch(columns){
        case 0b110:k1 = '4';break;
        case 0b101:k1 = '5';break;
        case 0b011:k1 = '6';break;
    }
}    
PORTD.5 = 1;
    
PORTD.6 = 0;
columns = PIND & 0x07;
if(columns != 0x07){
    switch(columns){
        case 0b110:k1 = '7';break;
        case 0b101:k1 = '8';break;
        case 0b011:k1 = '9';break;
    }
}    
PORTD.6 = 1;
    
PORTD.7 = 0;
columns = PIND & 0x07;
if(columns != 0x07){
    switch(columns){
        case 0b110:k1 = 10;break;
        case 0b101:k1 = '0';break;
        case 0b011:k1 = 11;break;
    }
}
PORTD.7 = 1;  

PORTD = 0xFF;  
return k1;
}