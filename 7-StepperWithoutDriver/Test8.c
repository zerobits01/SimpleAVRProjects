#include <mega16.h>
#include <delay.h>

void main(void)
{
int i;
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=0x0F;
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTB=0x00;
        
while (1)
      { 
        PORTB = 0x01;
        for(i = 0;i < 4 ; i++){
            delay_ms(200);
            PORTB = PORTB << 1;
        }
      }
}
/*
stepper should have enough time for rotation
or it will step back
if we test 100ms delay and 150 we can see difference
*/