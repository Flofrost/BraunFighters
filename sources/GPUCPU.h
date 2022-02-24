#ifndef CRINGEGPUCPUH
#define CRINGEGPUCPUH

extern volatile unsigned char stack[255], stack_length;

//Fills the whole screen with a color.
void fillScreen(const unsigned char color);
//Shifts the whole screen to the right by an amount.
void rShiftScreen();
//Shifts the whole screen to the left by an amount.
void lShiftScreen();
//Shifts the whole screen upwards by an amount.
void uShiftScreen();
//Shifts the whole screen downwards by an amount.
void dShiftScreen();
//Draws an orthonormal grid across the screen
void drawGrid(const unsigned char x, const unsigned char y, const unsigned char color);
//Changes a single pixel
void setPixel(const unsigned char x, const unsigned char y, const unsigned char color);
//Draws a horizontal line.
void drawHLine(const unsigned char line, const unsigned char start, const unsigned char end, const unsigned char color);
//Draws a vertical line.
void drawVLine(const unsigned char column, const unsigned char start, const unsigned char end, const unsigned char color);
//Draw any line.
void drawLine(const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2, const unsigned char color);
//Draws a hollow rectangle.
void drawRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color);
//Draws a filled rectangle.
void drawFRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color);
//Draws a regular polygon
void drawRPoly(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char edges, const unsigned char angleOffset, const unsigned char color);
//Draws a filled regular polygon
void drawRFPoly(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char edges, const unsigned char angleOffset, const unsigned char color);
//Draws a polygon following the points given
void drawPoly(const unsigned char edges, const unsigned char color, const unsigned char* points);
//Draws a filled polygon following the points given
void drawFPoly(const unsigned char edges, const unsigned char color, const unsigned char* points);
//Draws a segmented line, points are structured as follow: [x0,y0,x1,y1,x2,y2,x3,y3,x4,y4...]
void drawKinkLine(const unsigned char length, const unsigned char color, const unsigned char* points);
//Draws a character
void drawChar(const unsigned char x, const unsigned char y, const char c, const unsigned char color);
//Draws a string of characters, returns length of printed string
unsigned char drawString(const unsigned char xs, const unsigned char ys, const char* s, const unsigned char color);
//Draws a sprite
void drawSprite(const unsigned char x, const unsigned char y, const unsigned char spritID, const unsigned char options);

//Colors inside a shape using the edge fake color
void colorIn(const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2, const unsigned char color);

#endif