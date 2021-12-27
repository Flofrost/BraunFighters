#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <CImg.h>
#include "sources/GPU.h"

bool go = 0;

void processFrame(int v){
    go = 1;
}

void scuicide(int v){
    exit(0);
}

void CPU(int p){

    while(1) sleep(10);

    exit(0);
}

int main(int argc,char **argv){

    int p[2];
    pipe(p);
    int child = fork();
    signal(SIGRTMIN,processFrame);
    signal(SIGCHLD,scuicide);

    if(child){
        close(p[1]);
        GPU(child,p[0]);
        exit(0);
    }
    else{
        close(p[0]);
        CPU(p[1]);
    }

    return 0;
}
