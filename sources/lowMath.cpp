#include "lowMath.h"

int low_sin(const unsigned int x){

    int res = (((unsigned long)x<<SCALE_FACTOR) / PI) & 0x01FF;
    if(res > (1<<SCALE_FACTOR)-1){
        res &= ~(1<<SCALE_FACTOR);
        int res2 = ((unsigned long)res*(unsigned long)res)>>SCALE_FACTOR;
        res = (res - res2) << 2;
        res = ~res + 1;
    }else{
        int res2 = ((unsigned long)res*(unsigned long)res)>>SCALE_FACTOR;
        res = (res - res2) << 2;
    }

    return res;
}