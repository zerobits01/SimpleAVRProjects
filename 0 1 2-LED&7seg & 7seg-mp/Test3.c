/*
 * Test3.c
 *
 * Created: 10/1/2019 4:55:14 PM
 * Author: zerobits01
 */

#include <io.h>
#include <delay.h>
#include <mega16.h>

flash char sevseg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void main(void)
{
    int i;
    char cd; 

    
    // 7seg config :
    DDRA = 0xF0; // for using led on PORTA
    DDRB = 0xFF; // we are using ports B0 to B7
    DDRC = 0xFF; // for showing numbers on 7seg*8
    DDRD = 0xFF; // for shifting 7seg*8
    
    /*
    G F E D C B A
    powerring on with 1 and 0 off
    e.g : 1-> BC, 8-> ABCDEFG , ....    
        A
      F   B
        G
      E   C
        D
    */
    // if we use int it will cast it to integer number
    /*
        00 turns on all of them
        0F turns all last 4bits
        i tested 0x01 and all of the 7 last bits turned on
        then i found that if i use ~(0x01) it will be just the
        first precios bit
    */ 
    PORTA.0 = 0;
    while (1)
    {         
        cd = 0x01;
        for (i = 0; i < 8; i++)
        {
            PORTA.0 = ~PORTA.0; // led toggle 
            PORTB = sevseg[i];  // this is for 7segment
            PORTD = ~cd;        // for turning on just one cell
            PORTC = sevseg[i];  // setting the value of 7seg-mp value
            cd = cd << 1;       // accessing the next cell of 7seg-mp
            delay_ms(500);      // delay for checking the output
        }        
    }
}
