#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sources/GPU.h"

volatile int GPUpid = 0;
volatile unsigned char stack_length = 0, stack[255];

void getGPUpid(int v){
    FILE* pidFile = fopen("bin/GPUpid","r");
    fscanf(pidFile,"%d",&GPUpid);
    fclose(pidFile);
}

void writeStack(int v){
    FILE* stackFile = fopen("bin/stack.cringedata","wb");
    fwrite((void*)&stack_length,1,1,stackFile);
    if(stack_length) fwrite((void*)stack,1,stack_length,stackFile);
    fclose(stackFile);
    stack_length = 0;
    kill(GPUpid,35);
}

int main(){
    signal(SIGRTMIN, getGPUpid);
    signal(35, writeStack);

    while(!GPUpid);
    fillScreen(0x07);
    drawString(0x10,0x10,"Hello",0xBE);
    while(1){
        if(!stack_length){
            stack[stack_length++] = 0x01;
            stack[stack_length++] = 0x03;
        }
    }

    return 0;
}