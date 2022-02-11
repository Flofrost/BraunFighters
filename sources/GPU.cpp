#include "GPU.h"

void fillScreen(const unsigned char color){
    for(unsigned char l = 0; l < 120; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = 0; i < 120 ; i++){
            thisLine[i] = color;
        }
    }
}

void addScreen(const char amount){
    for(unsigned char l = 0; l < 120; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = 0; i < 120 ; i++){
            thisLine[i] += amount;
        }
    }
}

void rShiftScreen(){
    for(unsigned char l = 0; l < 120; l++){
        unsigned char *thisLine = frame[l];
        unsigned char bufferPixel = thisLine[120-1];
        for(unsigned char i = 120-1 ; i > 0 ; i--){
            thisLine[i] = thisLine[i-1];
        }
        thisLine[0] = bufferPixel;
    }
}

void lShiftScreen(){
    for(unsigned char l = 0; l < 120; l++){
            unsigned char *thisLine = frame[l];
            unsigned char bufferPixel = thisLine[0];
            for(unsigned char i = 0 ; i < 120-1 ; i++){
                thisLine[i] = thisLine[i+1];
            }
            thisLine[120-1] = bufferPixel;
    }
}

void uShiftScreen(){
    for(unsigned char i = 0; i < 120; i++){
            unsigned char bufferPixel = frame[0][i];
            for(unsigned char l = 0 ; l < 120-1 ; l++){
                frame[l][i] = frame[l+1][i];
            }
            frame[120-1][i] = bufferPixel;
    }
}

void dShiftScreen(){
    for(unsigned char i = 0; i < 120; i++){
            unsigned char bufferPixel = frame[120-1][i];
            for(unsigned char l = 120-1 ; l > 0 ; l--){
                frame[l][i] = frame[l-1][i];
            }
            frame[0][i] = bufferPixel;
    }
}

void drawGrid(const unsigned char x, const unsigned char y, const unsigned char color){
    for(unsigned char i = 0 ; i < 120 ; i += x) drawVLine(i,0,119,color);
    for(unsigned char i = 0 ; i < 120 ; i += y) drawHLine(i,0,119,color);
}

void setPixel(const unsigned char x, const unsigned char y, const unsigned char color){
    frame[y][x] = color;
}

void drawHLine(const unsigned char line, const unsigned char start, const unsigned char end, const unsigned char color){
    unsigned char *thisLine = frame[line];
    for(unsigned char i = start ; i < end ; i++) thisLine[i] = color;
}

void drawVLine(const unsigned char column, const unsigned char start, const unsigned char end, const unsigned char color){
    for(unsigned char i = start ; i < end ; i++) frame[i][column] = color;
}

void drawLine(const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2, const unsigned char color){
    int dx = x2-x1;
    int dy = y2-y1;
    #define abs(x) ((x)<0 ? -(x) : (x))

    if(abs(dx) > abs(dy)){
        if(x2 > x1){
            dy = (unsigned long)((dy << SCALE_FACTOR) / abs(dx));
            unsigned int yPos = y1 << SCALE_FACTOR;
            for(unsigned char i = x1 ; i <= x2 ; i++){
                frame[yPos >> SCALE_FACTOR][i] = color;
                yPos += dy;
            }
        }else{
            dy = (unsigned long)((dy << SCALE_FACTOR) / abs(dx));
            unsigned int yPos = y1 << SCALE_FACTOR;
            for(unsigned char i = x1 ; i >= x2 ; i--){
                frame[yPos >> SCALE_FACTOR][i] = color;
                yPos += dy;
            }
        }
    }else{
        if(y2 > y1){
            dx = (unsigned long)((dx << SCALE_FACTOR) / abs(dy));
            unsigned int xPos = x1 << SCALE_FACTOR;
            for(unsigned char i = y1 ; i <= y2 ; i++){
                frame[i][xPos >> SCALE_FACTOR] = color;
                xPos += dx;
            }
        }else{
            dx = (unsigned long)((dx << SCALE_FACTOR) / abs(dy));
            unsigned int xPos = x1 << SCALE_FACTOR;
            for(unsigned char i = y1 ; i >= y2 ; i--){
                frame[i][xPos >> SCALE_FACTOR] = color;
                xPos += dx;
            }
        }
    }
}

void drawRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color){
    unsigned char *firstLine = frame[ys];
    unsigned char *secondline = frame[ye];
    for(unsigned char i = xs ; i < xe ; i++){
        firstLine[i] = color;
        secondline[i] = color;
    }
    for(unsigned char i = ys+1 ; i < ye ; i++){
        frame[i][xs] = color;
        frame[i][xe] = color;
    }
}

void drawFRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color){
    for(unsigned char l = ys ; l < ye ; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = xs ; i < xe ; i++){
            thisLine[i] = color;
        }
    }
}

void drawRPoly(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char edges, const unsigned char angleOffset, const unsigned char color){
    unsigned char points[20][2] = {0};    
    for(unsigned char i = 0 ; i < edges ; i++){
        points[i][0] = xc + (((long)(radius << SCALE_FACTOR) * (long)low_cos((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
        points[i][1] = yc + (((long)(radius << SCALE_FACTOR) * (long)low_sin((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
    }
    for(unsigned char i = 1 ; i < edges ; i++){
        if(points[i][0] >= 120 || points[i][1] >= 120) return;
        drawLine(points[i-1][0],points[i-1][1],points[i][0],points[i][1],color);
    }
    drawLine(points[edges-1][0],points[edges-1][1],points[0][0],points[0][1],color);
}

void drawRFPoly(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char edges, const unsigned char angleOffset, const unsigned char color){
    unsigned char points[20][2] = {0}; 
    unsigned char maxX = 0, maxY = 0, minX = 255, minY = 255;
    for(unsigned char i = 0 ; i < edges ; i++){
        points[i][0] = xc + (((long)(radius << SCALE_FACTOR) * (long)low_cos((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
        points[i][1] = yc + (((long)(radius << SCALE_FACTOR) * (long)low_sin((PIx2/edges) * i + angleOffset * 6))>>(SCALE_FACTOR<<1));
    }
    for(unsigned char i = 1 ; i < edges ; i++){
        if(points[i][0] >= 120 || points[i][1] >= 120) return;
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

void drawPoly(const unsigned char edges, const unsigned char color, const unsigned char* points){
    for(unsigned char i = 0 ; i < (edges-1)<<1 ; i += 2){
        drawLine(points[i],points[i+1],points[i+2],points[i+3],color);
    }
    drawLine(points[0],points[1],points[(edges<<1)-2],points[(edges<<1)-1],color);
}

void drawFPoly(const unsigned char edges, const unsigned char color, const unsigned char* points){
    unsigned char maxX = 0, maxY = 0, minX = 255, minY = 255;
    for(unsigned char i = 0 ; i < (edges-1)<<1 ; i += 2){
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

void drawKinkLine(const unsigned char length, const unsigned char color, const unsigned char* points){
    for(unsigned char i = 0 ; i < (length-1)<<1 ; i += 2){
        drawLine(points[i],points[i+1],points[i+2],points[i+3],color);
    }
}

void drawChar(const unsigned char x, const unsigned char y, const char c, const unsigned char color){
    for(unsigned char i = 0 ; i < 5 ; i++){
        if(((unsigned char)(c - 0x21)) < 0x5D){
            const unsigned char charSeg = charset[(c - 0x21)*5 + i + 1];
            for(unsigned char ii = 0 ; ii < 8 ; ii++){
                if(charSeg & (1<<ii)) frame[y + ii][x + i] = color;
            }
        }
    }
}

unsigned char drawString(const unsigned char xs, const unsigned char ys, const char* s, const unsigned char color){
    unsigned char x = xs;
    unsigned char i = 0;
    for(i = 0 ; s[i] ; i++){
        if(x >= 120) return ++i;
        drawChar(x,ys,s[i],color);
        x += 6;
    }
    return ++i;
}

void drawSprite(const unsigned char x, const unsigned char y, const unsigned char spritID, const unsigned char options){
    
}

void colorIn(const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2, const unsigned char color){
    for(unsigned char l = y1 ; l < y2 ; l++){
        unsigned char *thisLine = frame[l];
        unsigned char pos1 = 255, pos2 = 255;
        bool prevPix = 0;
        for(unsigned char i = x1 ; i < x2 ; i++){
            bool thisPix = thisLine[i] == EDGE;
            if((thisPix != prevPix) && thisPix){
                if(pos1 == 255) pos1 = i;
                else pos2 = i;
            }
            if(thisPix) thisLine[i] = color;
            prevPix = thisPix;
            if((pos1 != 255) && (pos2 != 255)){
                for(unsigned char ii = pos1 ; ii < pos2 ; ii++) thisLine[ii] = color;
                pos1 = 255; pos2 = 255;
            }
        }
    }
}