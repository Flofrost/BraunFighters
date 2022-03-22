#include <avr/io.h>
#include <avr/interrupt.h>
#include "src/CringeGraphics.h"
#include "src/lowMath.h"

volatile uint16_t lineCounter = 0;
volatile uint8_t done = 0, vsync = 0, can_draw = 0, enabled = 1;
volatile uint8_t line = 0, state = FPORCH, stack[256], stack_length = 0;
uint8_t frame[HEIGHT][WIDTH];

const uint8_t BURST  = 0x17;

const uint8_t BLACK  = 0xE7;
const uint8_t WHITE  = 0xE0;
const uint8_t GREY   = 0xE3;

const uint8_t YELLOW = 0x1D;
const uint8_t ORANGE = 0x3D;
const uint8_t RED    = 0x5D;
const uint8_t PINK   = 0x7D;
const uint8_t PURPLE = 0x9D;
const uint8_t BLUE   = 0xBD;
const uint8_t CYAN   = 0xDD;
const uint8_t GREEN  = 0xFD;

const uint8_t EDGE   = 0xE0;

#ifdef DEBUG
void setupDebug(){
    UBRR1L = 10;
    UCSR1C = 0x06;
    UCSR1B = 0x98;
}

void downloadScreen(uint8_t width){
    uint8_t x=0, y=0;
    stack_length = 0;
    debugSendd((uint8_t)0xE6);
    while(1){
        while(!stack_length);
        if(stack[--stack_length] == 0xE7) break;
        frame[y][x++] = stack[stack_length];
        if(x >= width){
            x = 0;
            y++;
        }
    }
}

ISR(USART1_RX_vect){
    stack[stack_length++] = UDR1;
}
#endif

#define setupTimer3()   TCCR3B = 0x0A; /* CTC + prescaler = 8 */ \
                        OCR3AL = 159;   /* f = 15625 Hz */\
                        OCR3BL = TIMING_START_DRAW_LINE;    /* begin drawing 15 uS after int */\
                        TIMSK3 = 0x06 /* compA + compB interrupt */

ISR(TIMER3_COMPA_vect){

    lineCounter++;
    if(lineCounter > 312) lineCounter = 0;
    line += lineCounter&1;
    if(lineCounter == ((HEIGHT<<1) + INCLINE - 1)){
        can_draw = 0;
        done = 0;
    }

    switch(lineCounter){
        case START_FRAME:
            line=0;
            break;

        case INCLINE:
            can_draw = enabled;
            line = 0;
            break;

        case 308:
            vsync = 1;
            break;

        case 312:
            vsync = 0;
            break;
    }

    if(!vsync){
        DDRD |= 0x01;
    }else{
        DDRD &= 0xFE;
    }

    OCR3BL = TIMING_STOP_HSYNC;
    state = FPORCH;
}

ISR(TIMER3_COMPB_vect){
    switch(state){
        case FPORCH:
            if(!vsync){
                DDRD &= 0xFE;
            }else{
                DDRD |= 0x01;
            }
            #ifndef GREYSCALE
            if(can_draw) DDRA = BURST;
            #endif
            OCR3BL = TIMING_START_DRAW_LINE;
            state = DRAW_LINE;
            break;

        case DRAW_LINE:
            if(can_draw){
                uint8_t *thisLine = frame[line];
                for(uint8_t i = 0 ; i < WIDTH ; i++){
                    DDRA = thisLine[i];
                }
            }else{
                DDRA = WHITE;
            }
            DDRA = BLACK;
            break;
    }
}

void executeStack(){
    for(uint8_t i = 0 ; i < stack_length ; i++){
        switch(stack[i]){
            case 0x00:{ //fillScreen
                fillScreen(stack[++i]);
                break;
            }
            case 0x01:{ //rShiftScreen
                rShiftScreen();
                break;
            }
            case 0x02:{ //lShiftScreen
                lShiftScreen();
                break;
            }
            case 0x03:{ //uShiftScreen
                uShiftScreen();
                break;
            }
            case 0x04:{ //dShiftScreen
                dShiftScreen();
                break;
            }
            case 0x05:{ //drawGrid
                uint8_t x = stack[++i];
                uint8_t y = stack[++i];
                drawGrid(x,y,stack[++i]);
                break;
            }
            #ifdef DEBUG
            case 0x06:{ //downloadScreen
                downloadScreen(stack[++i]);
                stack_length = 0;
                break;
            }
            #endif
            case 0x10:{ //setPixel
                const uint8_t x = stack[++i];
                const uint8_t y = stack[++i];
                setPixel(x,y,stack[++i]);
                break;
            }
            case 0x11:{ //drawHLine
                const uint8_t h = stack[++i];
                const uint8_t s = stack[++i];
                const uint8_t e = stack[++i];
                drawHLine(h,s,e,stack[++i]);
                break;
            }
            case 0x12:{ //drawVLine
                const uint8_t l = stack[++i];
                const uint8_t s = stack[++i];
                const uint8_t e = stack[++i];
                drawVLine(l,s,e,stack[++i]);
                break;                
            }
            case 0x13:{ //drawLine
                const uint8_t x1 = stack[++i];
                const uint8_t y1 = stack[++i];
                const uint8_t x2 = stack[++i];
                const uint8_t y2 = stack[++i];
                drawLine(x1,y1,x2,y2,stack[++i]);
                break;                
            }
            case 0x14:{ //drawRect
                const uint8_t x1 = stack[++i];
                const uint8_t y1 = stack[++i];
                const uint8_t x2 = stack[++i];
                const uint8_t y2 = stack[++i];
                drawRect(x1,y1,x2,y2,stack[++i]);
                break;
            }
            case 0x15:{ //drawFRect
                const uint8_t x1 = stack[++i];
                const uint8_t y1 = stack[++i];
                const uint8_t x2 = stack[++i];
                const uint8_t y2 = stack[++i];
                drawFRect(x1,y1,x2,y2,stack[++i]);
                break;
            }
            case 0x16:{ //drawRPoly
                const uint8_t xc = stack[++i];
                const uint8_t yc = stack[++i];
                const uint8_t r = stack[++i];
                const uint8_t e = stack[++i];
                const uint8_t ao = stack[++i];
                drawRPoly(xc,yc,r,e,ao,stack[++i]);
                break;
            }
            case 0x17:{ //drawRFPoly
                const uint8_t xc = stack[++i];
                const uint8_t yc = stack[++i];
                const uint8_t r = stack[++i];
                const uint8_t e = stack[++i];
                const uint8_t ao = stack[++i];
                drawRFPoly(xc,yc,r,e,ao,stack[++i]);
                break;
            }
            case 0x18:{ //drawPoly
                const uint8_t l = stack[++i];
                const uint8_t c = stack[++i];
                drawPoly(l,c,(const uint8_t*)&stack[++i]);
                i += l<<1;
                break;
            }
            case 0x19:{ //drawFPoly
                const uint8_t l = stack[++i];
                const uint8_t c = stack[++i];
                drawFPoly(l,c,(const uint8_t*)&stack[++i]);
                i += l<<1;
                break;
            }
            case 0x1A:{ //drawKinkLine
                const uint8_t l = stack[++i];
                const uint8_t c = stack[++i];
                drawKinkLine(l,c,(const uint8_t*)&stack[++i]);
                i += l<<1;
                break;
            }
            case 0x1C:{ //drawChar
                const uint8_t x = stack[++i];
                const uint8_t y = stack[++i];
                const uint8_t c = stack[++i];
                drawChar(x,y,c,stack[++i]);
                break;
            }
            case 0x1D:{ //drawString
                const uint8_t x = stack[++i];
                const uint8_t y = stack[++i];
                const uint8_t c = stack[++i];
                i += drawString(x,y,(char *)&stack[++i],c);
                break;
            }
            case 0x30:{ //changeVoice0
                changeVoice0(stack[++i]);
                break;
            }
            case 0x31:{ //changeVoice1
                changeVoice1(stack[++i]);
                break;
            }
            case 0x32:{ //changeVoice2
                changeVoice2(stack[++i]);
                break;
            }
            #ifdef DEBUG
            default:{ //Error MSG
                debugSendd((const uint8_t)0xEE);
                stack_length = 0;
            }
            #endif
        }
    }
    stack_length = 0;
}

int main(){
    for(uint8_t l = 0; l < HEIGHT ; l++)
        for(uint8_t i = 0 ; i < WIDTH ; i++)
            frame[l][i] = l+i;

    MCUCR |= (1<<PUD); //Disable pullup resistors

    setupTimer3();
    setupVoice2();  //setup timer and voices
    setupVoice1();
    setupVoice0();

    PORTA = 0xFF;

    sei();

    #ifdef DEBUG
    setupDebug();
    debugSends((char*)"RRR");
    #endif


    // fetchStack();
    // debugSendd(stack_length);
    // for(uint8_t i = 0 ; i < stack_length ; i++) debugSendd(stack[i]);
    //executeStack();

    processShit:
    if(CAN_CALCULATE){
    }

    done = 1;
    while(done);
    goto processShit;

    return 0;
}