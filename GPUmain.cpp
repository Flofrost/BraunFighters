#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <CImg.h>
#include "sources/GPU.h"

using namespace cimg_library;

unsigned char frame[120][120];
unsigned char stack[256] = {0x00,0xBE}, stack_length;
unsigned long frame_count = 0;
int CPUpid = 0;

void executeStack(){
    for(unsigned char i = 0 ; i < stack_length ; i++){
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
                unsigned char x = stack[++i];
                unsigned char y = stack[++i];
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
                const unsigned char x = stack[++i];
                const unsigned char y = stack[++i];
                setPixel(x,y,stack[++i]);
                break;
            }
            case 0x11:{ //drawHLine
                const unsigned char h = stack[++i];
                const unsigned char s = stack[++i];
                const unsigned char e = stack[++i];
                drawHLine(h,s,e,stack[++i]);
                break;
            }
            case 0x12:{ //drawVLine
                const unsigned char l = stack[++i];
                const unsigned char s = stack[++i];
                const unsigned char e = stack[++i];
                drawVLine(l,s,e,stack[++i]);
                break;                
            }
            case 0x13:{ //drawLine
                const unsigned char x1 = stack[++i];
                const unsigned char y1 = stack[++i];
                const unsigned char x2 = stack[++i];
                const unsigned char y2 = stack[++i];
                drawLine(x1,y1,x2,y2,stack[++i]);
                break;                
            }
            case 0x14:{ //drawRect
                const unsigned char x1 = stack[++i];
                const unsigned char y1 = stack[++i];
                const unsigned char x2 = stack[++i];
                const unsigned char y2 = stack[++i];
                drawRect(x1,y1,x2,y2,stack[++i]);
                break;
            }
            case 0x15:{ //drawFRect
                const unsigned char x1 = stack[++i];
                const unsigned char y1 = stack[++i];
                const unsigned char x2 = stack[++i];
                const unsigned char y2 = stack[++i];
                drawFRect(x1,y1,x2,y2,stack[++i]);
                break;
            }
            case 0x16:{ //drawRPoly
                const unsigned char xc = stack[++i];
                const unsigned char yc = stack[++i];
                const unsigned char r = stack[++i];
                const unsigned char e = stack[++i];
                const unsigned char ao = stack[++i];
                drawRPoly(xc,yc,r,e,ao,stack[++i]);
                break;
            }
            case 0x17:{ //drawRFPoly
                const unsigned char xc = stack[++i];
                const unsigned char yc = stack[++i];
                const unsigned char r = stack[++i];
                const unsigned char e = stack[++i];
                const unsigned char ao = stack[++i];
                drawRFPoly(xc,yc,r,e,ao,stack[++i]);
                break;
            }
            case 0x18:{ //drawPoly
                const unsigned char l = stack[++i];
                const unsigned char c = stack[++i];
                drawPoly(l,c,(const unsigned char*)&stack[++i]);
                i += l<<1;
                break;
            }
            case 0x19:{ //drawFPoly
                const unsigned char l = stack[++i];
                const unsigned char c = stack[++i];
                drawFPoly(l,c,(const unsigned char*)&stack[++i]);
                i += l<<1;
                break;
            }
            case 0x1A:{ //drawKinkLine
                const unsigned char l = stack[++i];
                const unsigned char c = stack[++i];
                drawKinkLine(l,c,(const unsigned char*)&stack[++i]);
                i += l<<1;
                break;
            }
            case 0x1C:{ //drawChar
                const unsigned char x = stack[++i];
                const unsigned char y = stack[++i];
                const unsigned char c = stack[++i];
                drawChar(x,y,c,stack[++i]);
                break;
            }
            case 0x1D:{ //drawString
                const unsigned char x = stack[++i];
                const unsigned char y = stack[++i];
                const unsigned char c = stack[++i];
                i += drawString(x,y,(char *)&stack[++i],c);
                break;
            }
        }
    }
    stack_length = 0;
}

void stackProcess(int v){
    FILE* stackFile = fopen("bin/stack.cringedata","rb");
    fread(&stack_length,1,1,stackFile);
    fread(stack,1,stack_length,stackFile);
    fclose(stackFile);
    executeStack();
}

void getCPUpid(int v){
    // FILE* stackFile = fopen("bin/stack.cringedata","rb");
    // fread(&stack_length,1,1,stackFile);
    // fread(stack,1,stack_length,stackFile);
    // fclose(stackFile);
}

int main(){

    CImgDisplay main_window(120,120,"Braun Fighters",0);
    CImg<unsigned char> img(120,120,1,3);

    unsigned long prevTime = clock();

    signal(SIGRTMIN, stackProcess);
    signal(SIGRTMIN+1, getCPUpid);

    while(!main_window.is_closed()){

        frame_count++;

        int t50 = 20000 - (clock() - prevTime);
        usleep(t50 > 0 ? t50 : 0);
        prevTime = clock();

        if(main_window.is_resized()) main_window.resize(main_window.window_width(),main_window.window_height());
        for(int i = 0 ; i < 120 ; i++)
            for(int j = 0 ; j < 120 ; j++){
                img.draw_point(j,i,colors[frame[i][j]]);
            }
        main_window.display(img);
    }

    return 0;
}