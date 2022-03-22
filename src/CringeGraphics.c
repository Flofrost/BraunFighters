#include <avr/io.h>
#include <avr/pgmspace.h>
#include "CringeGraphics.h"
#include "lowMath.h"
#include "assets/text.h"
//#include "assets/sprites.h"

#ifdef DEBUG
#include <avr/interrupt.h>
void debugSendd(const uint8_t x){
    while(!(UCSR1A & 0x20));
    UDR1 = x;
}

void debugSends(const char* s){
    for(uint8_t i = 0 ; s[i] ; i++){
        while(!(UCSR1A & 0x20));
        UDR1 = s[i];
    }
}
#endif

void fetchStack(){
    clkF();
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    clkR();
    while(!CLK);
    stack_length = BUSR;

    for(uint8_t i = 0 ; i < stack_length ; i++){
        clkF();
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        clkR();
        while(!CLK);
        stack[i] = BUSR;
    }
}

void setEnabled(const uint8_t ena){
    enabled = ena;
}

void fillScreen(const uint8_t color){
    for(uint8_t l = 0; l < HEIGHT; l++){
        uint8_t *thisLine = frame[l];
        for(uint8_t i = 0; i < WIDTH ; i++){
            thisLine[i] = color;
        }
    }
}

void addScreen(const char amount){
    for(uint8_t l = 0; l < HEIGHT; l++){
        uint8_t *thisLine = frame[l];
        for(uint8_t i = 0; i < WIDTH ; i++){
            thisLine[i] += amount;
        }
    }
}

void rShiftScreen(){
    for(uint8_t l = 0; l < HEIGHT; l++){
        uint8_t *thisLine = frame[l];
        uint8_t bufferPixel = thisLine[WIDTH-1];
        for(uint8_t i = WIDTH-1 ; i > 0 ; i--){
            thisLine[i] = thisLine[i-1];
        }
        thisLine[0] = bufferPixel;
    }
}

void lShiftScreen(){
    for(uint8_t l = 0; l < HEIGHT; l++){
            uint8_t *thisLine = frame[l];
            uint8_t bufferPixel = thisLine[0];
            for(uint8_t i = 0 ; i < WIDTH-1 ; i++){
                thisLine[i] = thisLine[i+1];
            }
            thisLine[WIDTH-1] = bufferPixel;
    }
}

void uShiftScreen(){
    for(uint8_t i = 0; i < WIDTH; i++){
            uint8_t bufferPixel = frame[0][i];
            for(uint8_t l = 0 ; l < HEIGHT-1 ; l++){
                frame[l][i] = frame[l+1][i];
            }
            frame[HEIGHT-1][i] = bufferPixel;
    }
}

void dShiftScreen(){
    for(uint8_t i = 0; i < WIDTH; i++){
            uint8_t bufferPixel = frame[HEIGHT-1][i];
            for(uint8_t l = HEIGHT-1 ; l > 0 ; l--){
                frame[l][i] = frame[l-1][i];
            }
            frame[0][i] = bufferPixel;
    }
}

void drawGrid(const uint8_t x, const uint8_t y, const uint8_t color){
    for(uint8_t i = 0 ; i < WIDTH ; i += x) drawVLine(i,0,119,color);
    for(uint8_t i = 0 ; i < HEIGHT ; i += y) drawHLine(i,0,119,color);
}

void setPixel(const uint8_t x, const uint8_t y, const uint8_t color){
    frame[y][x] = color;
}

void drawHLine(const uint8_t line, const uint8_t start, const uint8_t end, const uint8_t color){
    uint8_t *thisLine = frame[line];
    for(uint8_t i = start ; i < end ; i++) thisLine[i] = color;
}

void drawVLine(const uint8_t column, const uint8_t start, const uint8_t end, const uint8_t color){
    for(uint8_t i = start ; i < end ; i++) frame[i][column] = color;
}

void drawLine(const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2, const uint8_t color){
    int dx = x2-x1;
    int dy = y2-y1;
    #define abs(x) ((x)<0 ? -(x) : (x))

    if(abs(dx) > abs(dy)){
        if(x2 > x1){
            dy = (unsigned long)((dy << SCALE_FACTOR) / abs(dx));
            unsigned int yPos = y1 << SCALE_FACTOR;
            for(uint8_t i = x1 ; i <= x2 ; i++){
                frame[yPos >> SCALE_FACTOR][i] = color;
                yPos += dy;
            }
        }else{
            dy = (unsigned long)((dy << SCALE_FACTOR) / abs(dx));
            unsigned int yPos = y1 << SCALE_FACTOR;
            for(uint8_t i = x1 ; i >= x2 ; i--){
                frame[yPos >> SCALE_FACTOR][i] = color;
                yPos += dy;
            }
        }
    }else{
        if(y2 > y1){
            dx = (unsigned long)((dx << SCALE_FACTOR) / abs(dy));
            unsigned int xPos = x1 << SCALE_FACTOR;
            for(uint8_t i = y1 ; i <= y2 ; i++){
                frame[i][xPos >> SCALE_FACTOR] = color;
                xPos += dx;
            }
        }else{
            dx = (unsigned long)((dx << SCALE_FACTOR) / abs(dy));
            unsigned int xPos = x1 << SCALE_FACTOR;
            for(uint8_t i = y1 ; i >= y2 ; i--){
                frame[i][xPos >> SCALE_FACTOR] = color;
                xPos += dx;
            }
        }
    }
}

void drawRect(const uint8_t xs, const uint8_t ys, const uint8_t xe, const uint8_t ye, const uint8_t color){
    uint8_t *firstLine = frame[ys];
    uint8_t *secondline = frame[ye];
    for(uint8_t i = xs ; i < xe ; i++){
        firstLine[i] = color;
        secondline[i] = color;
    }
    for(uint8_t i = ys+1 ; i < ye ; i++){
        frame[i][xs] = color;
        frame[i][xe] = color;
    }
}

void drawFRect(const uint8_t xs, const uint8_t ys, const uint8_t xe, const uint8_t ye, const uint8_t color){
    for(uint8_t l = ys ; l < ye ; l++){
        uint8_t *thisLine = frame[l];
        for(uint8_t i = xs ; i < xe ; i++){
            thisLine[i] = color;
        }
    }
}

void drawRPoly(const uint8_t xc, const uint8_t yc, const uint8_t radius, const uint8_t edges, const uint8_t angleOffset, const uint8_t color){
    uint8_t points[20][2] = {0};    
    for(uint8_t i = 0 ; i < edges ; i++){
        points[i][0] = xc + (((long)(radius << SCALE_FACTOR) * (long)low_cos((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
        points[i][1] = yc + (((long)(radius << SCALE_FACTOR) * (long)low_sin((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
    }
    for(uint8_t i = 1 ; i < edges ; i++){
        if(points[i][0] >= WIDTH || points[i][1] >= HEIGHT) return;
        drawLine(points[i-1][0],points[i-1][1],points[i][0],points[i][1],color);
    }
    drawLine(points[edges-1][0],points[edges-1][1],points[0][0],points[0][1],color);
}

void drawRFPoly(const uint8_t xc, const uint8_t yc, const uint8_t radius, const uint8_t edges, const uint8_t angleOffset, const uint8_t color){
    uint8_t points[20][2] = {0}; 
    uint8_t maxX = 0, maxY = 0, minX = 255, minY = 255;
    for(uint8_t i = 0 ; i < edges ; i++){
        points[i][0] = xc + (((long)(radius << SCALE_FACTOR) * (long)low_cos((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
        points[i][1] = yc + (((long)(radius << SCALE_FACTOR) * (long)low_sin((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
    }
    for(uint8_t i = 1 ; i < edges ; i++){
        if(points[i][0] >= WIDTH || points[i][1] >= HEIGHT) return;
        drawLine(points[i-1][0],points[i-1][1],points[i][0],points[i][1],EDGE);
        if(points[i][0]<minX) minX = points[i][0];
        if(points[i][1]<minY) minY = points[i][1];
        if(points[i][0]>maxX) maxX = points[i][0];
        if(points[i][1]>maxY) maxY = points[i][1];
    }
    drawLine(points[edges-1][0],points[edges-1][1],points[0][0],points[0][1],EDGE);
    if(points[0][0]<minX) minX = points[0][0];
    if(points[0][1]<minY) minY = points[0][1];
    if(points[0][0]>maxX) maxX = points[0][0];
    if(points[0][1]>maxY) maxY = points[0][1];
    colorIn(minX,minY,maxX+1,maxY+1,color);
}

void drawPoly(const uint8_t edges, const uint8_t color, const uint8_t* points){
    for(uint8_t i = 0 ; i < (edges-1)<<1 ; i += 2){
        drawLine(points[i],points[i+1],points[i+2],points[i+3],color);
    }
    drawLine(points[0],points[1],points[(edges<<1)-2],points[(edges<<1)-1],color);
}

void drawFPoly(const uint8_t edges, const uint8_t color, const uint8_t* points){
    uint8_t maxX = 0, maxY = 0, minX = 255, minY = 255;
    for(uint8_t i = 0 ; i < (edges-1)<<1 ; i += 2){
        drawLine(points[i],points[i+1],points[i+2],points[i+3],EDGE);
        if(points[i]<minX) minX = points[i];
        if(points[i+1]<minY) minY = points[i+1];
        if(points[i]>maxX) maxX = points[i];
        if(points[i+1]>maxY) maxY = points[i+1];
    }
    drawLine(points[0],points[1],points[(edges<<1)-2],points[(edges<<1)-1],EDGE);
    if(points[(edges<<1)-2]<minX) minX = points[(edges<<1)-2];
    if(points[(edges<<1)-1]<minY) minY = points[(edges<<1)-1];
    if(points[(edges<<1)-2]>maxX) maxX = points[(edges<<1)-2];
    if(points[(edges<<1)-1]>maxY) maxY = points[(edges<<1)-1];
    colorIn(minX,minY,maxX+1,maxY+1,color);
}

void drawKinkLine(const uint8_t length, const uint8_t color, const uint8_t* points){
    for(uint8_t i = 0 ; i < (length-1)<<1 ; i += 2){
        drawLine(points[i],points[i+1],points[i+2],points[i+3],color);
    }
}

void drawChar(const uint8_t x, const uint8_t y, const char c, const uint8_t color){
    for(uint8_t i = 0 ; i < 5 ; i++){
        if(((uint8_t)(c - 0x21)) < 0x5D){
            const uint8_t charSeg = pgm_read_byte(&charset[(c - 0x21)*5 + i + 1]);
            for(uint8_t ii = 0 ; ii < 8 ; ii++){
                if(charSeg & (1<<ii)) frame[y + ii][x + i] = color;
            }
        }
    }
}

uint8_t drawString(const uint8_t xs, const uint8_t ys, const char* s, const uint8_t color){
    uint8_t x = xs;
    uint8_t i = 0;
    for(i = 0 ; s[i] ; i++){
        if(x >= 120) return ++i;
        drawChar(x,ys,s[i],color);
        x += 6;
    }
    return ++i;
}

void drawSprite(const uint8_t x, const uint8_t y, const uint8_t spritID, const uint8_t options){
    
}

void colorIn(const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2, const uint8_t color){
    for(uint8_t l = y1 ; l < y2 ; l++){
        uint8_t *thisLine = frame[l];
        uint8_t pos1 = 255, pos2 = 255;
        uint8_t prevPix = 0;
        for(uint8_t i = x1 ; i < x2 ; i++){
            uint8_t thisPix = thisLine[i] == EDGE;
            if((thisPix != prevPix) && thisPix){
                if(pos1 == 255) pos1 = i;
                else pos2 = i;
            }
            if(thisPix) thisLine[i] = color;
            prevPix = thisPix;
            if((pos1 != 255) && (pos2 != 255)){
                for(uint8_t ii = pos1 ; ii < pos2 ; ii++) thisLine[ii] = color;
                pos1 = 255; pos2 = 255;
            }
        }
    }
}

//                                         C   C#  D   D#  E   F   F#  G   G#  A   A#  B
const uint8_t notes0[60] PROGMEM = {148,140,132,125,118,111,105, 99, 93, 88, 83, 78,// O2
//                                         5   5   5   5   5   5   5   5   5   5   5   5
                                           74, 69, 66,250,236,223,210,198,187,177,167,157,// O3
//                                         5   5   5   4   4   4   4   4   4   4   4   4
                                          148,140,132,125,118,111,105, 99, 93, 88, 83, 78,// O4
//                                         4   4   4   4   4   4   4   4   4   4   4   4                                 
                                           73, 69, 66,250,236,223,210,198,187,177,167,157,// O5
//                                         4   4   4   3   3   3   3   3   3   3   3   3
                                          148,140,132,125,118,111,105, 99, 93, 88, 83, 78};//O6
//                                         3   3   3   3   3   3   3   3   3   3   3   3

//                                         C   C#  D   D#  E   F   F#  G   G#  A   A#  B
const uint8_t notes2[60] PROGMEM = {148,140,132,125,118,111,105, 99, 93, 88, 83, 78,// O2
//                                         7   7   7   7   7   7   7   7   7   7   7   7
                                           74, 69, 66,250,236,223,210,198,187,177,167,157,// O3
//                                         7   7   7   6   6   6   6   6   6   6   6   6
                                          148,140,132,250,236,222,210,198,187,177,167,157,// O4
//                                         6   6   6   5   5   5   5   5   5   5   5   5                                    
                                          147,140,132,250,236,223,210,198,187,177,167,157,// O5
//                                         5   5   5   4   4   4   4   4   4   4   4   4                           
                                          148,140,132,125,118,111,105, 99, 93, 88, 83, 78};//O6
//                                         4   4   4   4   4   4   4   4   4   4   4   4


void changeVoice0(const uint8_t tone){
    const uint8_t note = tone & 0x3F;
    if(note < 60){
        TCCR0B = guess_prescaler0(note);
        OCR0A = pgm_read_byte(&notes0[note]);
        DDRB = (DDRB & 0xEB) | ((tone&0x80)>>3) | ((tone&0x40)>>4);
    }else{
        TCCR0B = 0;
    }
}

void changeVoice1(const uint8_t tone){
    const uint8_t note = tone & 0x3F;
    if(note < 60){
        TCCR1B = 0x08 | guess_prescaler0(note);
        TCNT1 = 0;
        OCR1AL = pgm_read_byte(&notes0[note]);
        DDRB = (DDRB & 0xFC) | ((tone&0x80)>>6) | ((tone&0x40)>>6);
    }else{
        TCCR1B = 0x08;
    }
}

void changeVoice2(const uint8_t tone){
    const uint8_t note = tone & 0x3F;
    if(note < 60){
        TCCR2B = guess_prescaler2(note);
        OCR2A = pgm_read_byte(&notes2[note]);
        DDRD = (DDRD & 0xED) | ((tone >> 5) & 0x02) | ((tone >> 3) & 0x10);
    }else{
        TCCR2B = 0;
    }
}