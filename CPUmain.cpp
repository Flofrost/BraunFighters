#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int GPUpid = 0;
volatile unsigned char stackLength = 6, stack[255] = {0x00,0x07,0x05,0x07,0x07,0xFB};

void getGPUpid(int v){
    FILE* pidFile = fopen("bin/GPUpid","r");
    fscanf(pidFile,"%d",&GPUpid);
    fclose(pidFile);
}

void writeStack(int v){
    FILE* stackFile = fopen("bin/stack.cringedata","wb");
    fwrite((void*)&stackLength,1,1,stackFile);
    if(stackLength) fwrite((void*)stack,1,stackLength,stackFile);
    fclose(stackFile);
    stackLength = 0;
    kill(GPUpid,35);
}

int main(){
    signal(SIGRTMIN, getGPUpid);
    signal(35, writeStack);

    while(!GPUpid);
    while(1){
        if(!stackLength){
            stack[stackLength++] = 0x01;
            stack[stackLength++] = 0x03;
        }
    }

    return 0;
}