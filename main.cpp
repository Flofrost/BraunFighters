#include <avr/io.h>
#include <avr/interrupt.h>
#include "sources/SynthX.h"

#define clkF() DDRD |= 0x80
#define clkR() DDRD &= 0x7F
#define CLK  (PIND & 0x80)
#define BUSW  DDRC
#define BUSR  PINC

volatile uint8_t stack[256] = {0x50,0x51,0x52,0x53}, stackLength = 4;

ISR(PCINT3_vect){
    cli();

    sei();
}

int main(){

    PCICR = 0x08;
    PCMSK3 = 0x80; //set CLK as PCINT

    sei();

    while(1){

    }

    return 0;
}