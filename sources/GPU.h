#ifndef CRINGEGPUH
#define CRINGEGPUH

#include "lowMath.h"
#include "Colors.h"

const unsigned char colors[256][3] = {
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {235,230,219},{224,219,204},{212,205,183},{191,183,151},{167,158,113},{126,116, 56},{ 54, 47, 22},{  8, 10,  4},
    {235,225,177},{230,220,159},{214,206,113},{199,195, 75},{181,184, 56},{142,155, 49},{ 65, 98, 38},{ 32, 52, 36},
    {235,236,148},{225,233,126},{216,229, 93},{194,220, 73},{161,206, 56},{105,178, 45},{ 37,114, 29},{ 43, 94,  0},
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {236,215,215},{223,199,199},{212,189,187},{197,174,165},{174,150,130},{131,103, 67},{ 44, 32, 14},{ 10, 11,  6},
    {243,212,195},{243,207,184},{233,188,151},{222,168,112},{210,147, 76},{190,109, 41},{139, 52, 38},{ 97, 12,  0},
    {250,220,166},{250,209,149},{251,200,120},{249,183, 68},{245,159, 34},{222,126, 43},{186, 80,  0},{160, 45,  0},
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {238,211,226},{227,195,216},{214,180,201},{198,156,178},{176,123,149},{130, 67, 91},{ 35, 17, 19},{  6,  9,  8},
    {244,204,223},{245,197,217},{241,181,200},{231,158,176},{222,131,154},{204, 88,110},{158, 47, 47},{112, 10, 20},
    {255,199,235},{255,187,225},{255,176,209},{255,154,180},{255,116,142},{255, 52, 77},{213, 12,  0},{121,  0,  0},
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {233,211,243},{218,195,237},{207,180,230},{188,156,215},{163,124,194},{115, 69,154},{ 31, 18, 57},{ 12, 10, 17},
    {245,200,243},{245,194,245},{237,175,238},{226,151,228},{215,124,216},{192, 80,195},{137, 45,153},{ 98, 60,128},
    {255,199,252},{255,184,252},{255,173,251},{255,146,246},{255,106,240},{255, 40,232},{213,  0,190},{136,  0,118},
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {232,223,246},{218,205,243},{201,187,237},{181,166,227},{153,134,207},{104, 75,169},{ 49, 23, 83},{  9,  8, 19},
    {231,197,245},{223,189,245},{208,170,245},{192,149,239},{176,127,235},{137, 85,219},{ 66, 45,185},{ 47, 44,143},
    {248,198,255},{239,187,255},{229,178,255},{218,156,255},{203,122,255},{172, 65,255},{ 87,  0,242},{ 29,  0,188},
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {203,214,240},{181,199,234},{153,184,224},{122,167,214},{ 85,137,194},{ 43, 82,156},{ 23, 23, 75},{ 11, 12, 30},
    {203,201,244},{192,197,245},{164,182,244},{129,163,238},{ 90,146,233},{ 40,105,218},{ 31, 43,182},{ 36, 37,133},
    {200,210,255},{183,202,255},{163,190,255},{139,176,255},{ 95,150,255},{ 32,104,255},{  0, 27,233},{  3,  0,190},
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {192,220,222},{168,206,207},{135,193,191},{103,177,169},{ 59,149,137},{ 24, 95, 81},{ 10, 20, 29},{  4,  9, 13},
    {148,216,219},{128,215,214},{ 79,203,195},{ 41,193,176},{ 24,178,155},{ 18,143,105},{ 14, 71, 38},{ 17, 36, 35},
    {102,235,234},{ 67,233,227},{ 34,228,218},{ 19,218,205},{ 15,198,184},{  0,183,152},{  0,139,109},{  0,103, 64},
    {255,255,255},{217,217,217},{178,178,178},{143,143,143},{107,107,107},{ 71, 71, 71},{ 36, 36, 36},{  0,  0,  0},
    {212,215,202},{192,199,182},{172,184,159},{151,166,128},{117,136, 89},{ 56, 81, 40},{  4, 40, 26},{  0, 10,  6},
    {192,210,174},{185,206,161},{160,193,128},{129,178, 94},{ 95,162, 65},{ 39,132, 46},{ 12, 58, 24},{  9, 21, 15},
    {187,224,163},{168,218,142},{143,210,107},{104,201, 84},{ 69,184, 72},{ 31,153, 57},{ 13, 83, 29},{  6, 23,  9}};

const unsigned char charset[470] = {
    0b00000000,
    0b00000000,
    0b01011110,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00001110,
    0b00000000,
    0b00001110,
    0b00000000,
    0b00100100,
    0b01111110,
    0b00100100,
    0b01111110,
    0b00100100,
    0b01001000,
    0b01010100,
    0b11111110,
    0b01010100,
    0b00100100,
    0b11000000,
    0b00100010,
    0b00011000,
    0b01000100,
    0b00000011,
    0b01110110,
    0b10001001,
    0b10001001,
    0b10010101,
    0b01000010,
    0b00000000,
    0b00000000,
    0b00001110,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111110,
    0b10000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000001,
    0b01111110,
    0b00000000,
    0b00000000,
    0b00100100,
    0b00011000,
    0b01111110,
    0b00011000,
    0b00100100,
    0b00010000,
    0b00010000,
    0b01111100,
    0b00010000,
    0b00010000,
    0b00000000,
    0b00000000,
    0b11000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00000000,
    0b00000000,
    0b10000000,
    0b00000000,
    0b00000000,
    0b11000000,
    0b00100000,
    0b00011000,
    0b00000100,
    0b00000011,
    0b01111110,
    0b10100001,
    0b10010001,
    0b10001001,
    0b01111110,
    0b10000100,
    0b10000010,
    0b11111111,
    0b10000000,
    0b10000000,
    0b11000010,
    0b10100001,
    0b10010001,
    0b10001001,
    0b10000110,
    0b01000011,
    0b10001001,
    0b10001001,
    0b10001101,
    0b01111011,
    0b00011000,
    0b00010100,
    0b00010010,
    0b11111111,
    0b00010000,
    0b01001111,
    0b10001001,
    0b10001001,
    0b10001001,
    0b01110001,
    0b01111110,
    0b10001001,
    0b10001001,
    0b10001001,
    0b01110010,
    0b00000011,
    0b00000001,
    0b11100001,
    0b00011001,
    0b00000111,
    0b01110110,
    0b10001001,
    0b10001001,
    0b10001001,
    0b01110110,
    0b01001110,
    0b10010001,
    0b10010001,
    0b10010001,
    0b01111110,
    0b00000000,
    0b00000000,
    0b01101100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000000,
    0b01101100,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00101000,
    0b00101000,
    0b01000100,
    0b01000100,
    0b00101000,
    0b00101000,
    0b00101000,
    0b00101000,
    0b00101000,
    0b01000100,
    0b01000100,
    0b00101000,
    0b00101000,
    0b00010000,
    0b00000010,
    0b00000001,
    0b10110001,
    0b00001001,
    0b00000110,
    0b01111100,
    0b10010010,
    0b10101010,
    0b10010010,
    0b00011100,
    0b11111110,
    0b00010001,
    0b00010001,
    0b00010001,
    0b11111110,
    0b11111111,
    0b10010001,
    0b10010001,
    0b10010001,
    0b01101110,
    0b01111110,
    0b10000001,
    0b10000001,
    0b10000001,
    0b01000010,
    0b11111111,
    0b10000001,
    0b10000001,
    0b01000010,
    0b00111100,
    0b11111111,
    0b10001001,
    0b10001001,
    0b10001001,
    0b10000001,
    0b11111111,
    0b00001001,
    0b00001001,
    0b00001001,
    0b00000001,
    0b01111110,
    0b10000001,
    0b10000001,
    0b10010001,
    0b01110010,
    0b11111111,
    0b00010000,
    0b00010000,
    0b00010000,
    0b11111111,
    0b00000000,
    0b10000001,
    0b11111111,
    0b10000001,
    0b00000000,
    0b01100001,
    0b10000001,
    0b10000001,
    0b01111111,
    0b00000001,
    0b11111111,
    0b00011000,
    0b00100100,
    0b01000010,
    0b10000001,
    0b11111111,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b11111111,
    0b00000010,
    0b00001100,
    0b00000010,
    0b11111111,
    0b11111111,
    0b00000110,
    0b00011000,
    0b01100000,
    0b11111111,
    0b01111110,
    0b10000001,
    0b10000001,
    0b10000001,
    0b01111110,
    0b11111111,
    0b00010001,
    0b00010001,
    0b00010001,
    0b00001110,
    0b01111110,
    0b10000001,
    0b10100001,
    0b01000001,
    0b10111110,
    0b11111111,
    0b00010001,
    0b00110001,
    0b01010001,
    0b10001110,
    0b01001110,
    0b10010001,
    0b10010001,
    0b10010001,
    0b01100010,
    0b00000001,
    0b00000001,
    0b11111111,
    0b00000001,
    0b00000001,
    0b01111111,
    0b10000000,
    0b10000000,
    0b10000000,
    0b01111111,
    0b00011111,
    0b01100000,
    0b10000000,
    0b01100000,
    0b00011111,
    0b11111111,
    0b10000000,
    0b01110000,
    0b10000000,
    0b11111111,
    0b11000011,
    0b00100100,
    0b00011000,
    0b00100100,
    0b11000011,
    0b00000011,
    0b00001100,
    0b11110000,
    0b00001100,
    0b00000011,
    0b11000001,
    0b10100001,
    0b10011001,
    0b10000101,
    0b10000011,
    0b11111111,
    0b10000001,
    0b10000001,
    0b00000000,
    0b00000000,
    0b00000011,
    0b00000100,
    0b00011000,
    0b00100000,
    0b11000000,
    0b00000000,
    0b00000000,
    0b10000001,
    0b10000001,
    0b11111111,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00001000,
    0b00010000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00000000,
    0b01110000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b11111000,
    0b11111100,
    0b10010000,
    0b10010000,
    0b10010000,
    0b01100000,
    0b01110000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b00000000,
    0b01100000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b11111100,
    0b01110000,
    0b10101000,
    0b10101000,
    0b10101000,
    0b00010000,
    0b00000000,
    0b11111000,
    0b00100100,
    0b00000100,
    0b00000000,
    0b00011000,
    0b10100100,
    0b10100100,
    0b10100100,
    0b01111000,
    0b11111100,
    0b00010000,
    0b00010000,
    0b11100000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11110100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000000,
    0b01110100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11111000,
    0b00100000,
    0b11011000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11111100,
    0b00000000,
    0b00000000,
    0b11111000,
    0b00001000,
    0b00010000,
    0b00001000,
    0b11110000,
    0b11111000,
    0b00001000,
    0b00001000,
    0b11110000,
    0b00000000,
    0b01110000,
    0b10001000,
    0b10001000,
    0b01110000,
    0b00000000,
    0b11111000,
    0b00101000,
    0b00101000,
    0b00010000,
    0b00000000,
    0b00010000,
    0b00101000,
    0b00101000,
    0b11111000,
    0b00000000,
    0b00000000,
    0b11111000,
    0b00010000,
    0b00010000,
    0b00000000,
    0b00010000,
    0b10101000,
    0b10101000,
    0b10101000,
    0b01000000,
    0b00000000,
    0b01111000,
    0b10010000,
    0b10000000,
    0b00000000,
    0b01111000,
    0b10000000,
    0b10000000,
    0b01111000,
    0b00000000,
    0b00011000,
    0b01100000,
    0b10000000,
    0b01100000,
    0b00011000,
    0b01111000,
    0b10000000,
    0b01000000,
    0b10000000,
    0b01111000,
    0b10001000,
    0b01010000,
    0b00100000,
    0b01010000,
    0b10001000,
    0b00001000,
    0b00010000,
    0b11100000,
    0b00010000,
    0b00001000,
    0b00000000,
    0b11001000,
    0b10101000,
    0b10011000,
    0b00000000,
    0b00010000,
    0b01101100,
    0b10000010,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111110,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000010,
    0b01101100,
    0b00010000,
    0b00011000,
    0b00001000,
    0b00010000,
    0b00100000,
    0b00110000};

extern unsigned char frame[120][120];
extern volatile unsigned char stack[255], stack_length;

//Fills the whole screen with a color.
void fillScreen(const unsigned char color);
//Adds a value to each pixel.
void addScreen(const char amount);
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