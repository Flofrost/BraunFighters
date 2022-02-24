#include "GPUCPU.h"

void fillScreen(const unsigned char color){
    stack[stack_length++] = 0x00;
    stack[stack_length++] = color;
}

void rShiftScreen(){
    stack[stack_length++] = 0x01;
}

void lShiftScreen(){
    stack[stack_length++] = 0x02;
}

void uShiftScreen(){
    stack[stack_length++] = 0x03;
}

void dShiftScreen(){
    stack[stack_length++] = 0x04;
}

void drawGrid(const unsigned char x, const unsigned char y, const unsigned char color){
    stack[stack_length++] = 0x05;
    stack[stack_length++] = x;
    stack[stack_length++] = y;
    stack[stack_length++] = color;
}

void setPixel(const unsigned char x, const unsigned char y, const unsigned char color){
    stack[stack_length++] = 0x10;
    stack[stack_length++] = x;
    stack[stack_length++] = y;
    stack[stack_length++] = color;
}

void drawHLine(const unsigned char line, const unsigned char start, const unsigned char end, const unsigned char color){
    stack[stack_length++] = 0x11;
    stack[stack_length++] = line;
    stack[stack_length++] = start;
    stack[stack_length++] = end;
    stack[stack_length++] = color;
}

void drawVLine(const unsigned char column, const unsigned char start, const unsigned char end, const unsigned char color){
    stack[stack_length++] = 0x12;
    stack[stack_length++] = column;
    stack[stack_length++] = start;
    stack[stack_length++] = end;
    stack[stack_length++] = color;
}

void drawLine(const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2, const unsigned char color){
    stack[stack_length++] = 0x13;
    stack[stack_length++] = x1;
    stack[stack_length++] = y1;
    stack[stack_length++] = x2;
    stack[stack_length++] = y2;
    stack[stack_length++] = color;
}

void drawRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color){
    stack[stack_length++] = 0x14;
    stack[stack_length++] = xs;
    stack[stack_length++] = ys;
    stack[stack_length++] = xe;
    stack[stack_length++] = ye;
    stack[stack_length++] = color;
}

void drawFRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color){
    stack[stack_length++] = 0x15;
    stack[stack_length++] = xs;
    stack[stack_length++] = ys;
    stack[stack_length++] = xe;
    stack[stack_length++] = ye;
    stack[stack_length++] = color;
}

void drawRPoly(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char edges, const unsigned char angleOffset, const unsigned char color){
    stack[stack_length++] = 0x16;
    stack[stack_length++] = xc;
    stack[stack_length++] = yc;
    stack[stack_length++] = radius;
    stack[stack_length++] = edges;
    stack[stack_length++] = angleOffset;
    stack[stack_length++] = color;
}

void drawRFPoly(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char edges, const unsigned char angleOffset, const unsigned char color){
    stack[stack_length++] = 0x17;
    stack[stack_length++] = xc;
    stack[stack_length++] = yc;
    stack[stack_length++] = radius;
    stack[stack_length++] = edges;
    stack[stack_length++] = angleOffset;
    stack[stack_length++] = color;
}

void drawPoly(const unsigned char edges, const unsigned char color, const unsigned char* points){
    stack[stack_length++] = 0x18;
    stack[stack_length++] = edges;
    stack[stack_length++] = color;
    for(int i = 0 ; i < edges ; i++){
        stack[stack_length++] = points[i<<1];
        stack[stack_length++] = points[(i<<1)+1];
    }
}

void drawFPoly(const unsigned char edges, const unsigned char color, const unsigned char* points){
    stack[stack_length++] = 0x19;
    stack[stack_length++] = edges;
    stack[stack_length++] = color;
    for(int i = 0 ; i < edges ; i++){
        stack[stack_length++] = points[i<<1];
        stack[stack_length++] = points[(i<<1)+1];
    }
}

void drawKinkLine(const unsigned char length, const unsigned char color, const unsigned char* points){
    stack[stack_length++] = 0x1A;
    stack[stack_length++] = length;
    stack[stack_length++] = color;
    for(int i = 0 ; i < length ; i++){
        stack[stack_length++] = points[i<<1];
        stack[stack_length++] = points[(i<<1)+1];
    }
}

void drawChar(const unsigned char x, const unsigned char y, const char c, const unsigned char color){
    stack[stack_length++] = 0x1C;
    stack[stack_length++] = x;
    stack[stack_length++] = y;
    stack[stack_length++] = c;
    stack[stack_length++] = color;
}

unsigned char drawString(const unsigned char xs, const unsigned char ys, const char* s, const unsigned char color){
    stack[stack_length++] = 0x1D;
    stack[stack_length++] = xs;
    stack[stack_length++] = ys;
    stack[stack_length++] = color;
    int i;
    for( i = 0 ; s[i] ; i++)
        stack[stack_length++] = s[i];
    stack[stack_length++] = 0x00;
    return i+1;
}

void drawSprite(const unsigned char x, const unsigned char y, const unsigned char spritID, const unsigned char options);
