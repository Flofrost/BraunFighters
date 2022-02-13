#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int GPUpid = 0;
unsigned char stackLength = 2, stack[255] = {0x00,0xBE};

void getGPUpid(int v){
    FILE* pidFile = fopen("bin/GPUpid","r");
    fscanf(pidFile,"%d",&GPUpid);
    fclose(pidFile);
}

void writeStack(int v){
    FILE* stackFile = fopen("bin/stack.cringedata","wb");
    fwrite(&stackLength,1,1,stackFile);
    if(stackLength) fwrite(stack,1,stackLength,stackFile);
    fclose(stackFile);
    kill(GPUpid,SIGRTMIN+1);
}

int main(){

    signal(SIGRTMIN, getGPUpid);
    signal(SIGRTMIN+1, writeStack);
    usleep(1000);

    while(!GPUpid);
    while(1){
        if(kill(GPUpid,0)) exit(0);
        stack[1]++;
    }

    return 0;
}