#include <avr/io.h>
#include <avr/interrupt.h>
#include "sources/SynthX.h"

#define clkF() DDRD |= 0x80
#define clkR() DDRD &= 0x7F
#define CLK  (PIND & 0x80)
#define BUSW  DDRC
#define BUSR  PINC

volatile uint8_t stack[256], stackLength = 0;

ISR(PCINT3_vect){
    cli();
    clkF();
    uint8_t timeout = 10;
    if(stackLength){
        BUSW = ~stack[--stackLength];
        //while(BUSR != stack[stackLength]);
    }else{
        BUSW = 0x00;
        //while(BUSR != 0xFF);
    }
    clkR();
    while(!CLK && timeout--);
    while(CLK && timeout--);
    sei();
}

int main(){

    PCICR = 0x08;
    PCMSK3 = 0x80; //set CLK as PCINT

    sei();

    while(1){
        if(!stackLength){
            stack[0] = 0x50;
            stack[1] = 0x51;
            stack[2] = 0x52;
            stack[3] = 0x53;
            stackLength = 4;
        }
    }

    return 0;
}