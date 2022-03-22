#ifndef CRINGEGRAPHICS_H
#define CRINGEGRAPHICS_H   

#include <avr/pgmspace.h>

//#define GREYSCALE

#define WIDTH 120
#define HEIGHT 120
#define TOTALPIXELS 14400
#define START_FRAME 28
#define INCLINE 40

#define FPORCH 0
#define START_BURST 1
#define STOP_BURST 2
#define DRAW_LINE 3

#define TIMING_STOP_HSYNC 15
#define TIMING_START_DRAW_LINE 40

#define clkF() DDRD |= 0x80
#define clkR() DDRD &= 0x7F
#define CLK  (PIND & 0x80)
#define BUSR     PINC
#define BUSW(x)  DDRC = ~(x)


extern volatile uint16_t lineCounter;
extern volatile uint8_t done, vsync, can_draw, enabled;
extern volatile uint8_t line, state, stack[256], stack_length;
extern uint8_t frame[HEIGHT][WIDTH];

extern const uint8_t BURST;

extern const uint8_t BLACK;
extern const uint8_t WHITE;
extern const uint8_t GREY;

extern const uint8_t YELLOW;
extern const uint8_t ORANGE;
extern const uint8_t RED;
extern const uint8_t PINK;
extern const uint8_t PURPLE;
extern const uint8_t BLUE;
extern const uint8_t CYAN;
extern const uint8_t GREEN;

extern const uint8_t EDGE;


#ifdef DEBUG
#include <stdio.h>
void debugSendd(const uint8_t x);
void debugSends(const char* s);
#endif

#define CAN_CALCULATE (!can_draw)

//Asks CPU for stack
void fetchStack();

//enables display, disabling display yields display time to calculations
void setEnabled(const uint8_t ena);
//Fills the whole screen with a color.
void fillScreen(const uint8_t color);
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
void drawGrid(const uint8_t x, const uint8_t y, const uint8_t color);
//Changes a single pixel
void setPixel(const uint8_t x, const uint8_t y, const uint8_t color);
//Draws a horizontal line.
void drawHLine(const uint8_t line, const uint8_t start, const uint8_t end, const uint8_t color);
//Draws a vertical line.
void drawVLine(const uint8_t column, const uint8_t start, const uint8_t end, const uint8_t color);
//Draw any line.
void drawLine(const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2, const uint8_t color);
//Draws a hollow rectangle.
void drawRect(const uint8_t xs, const uint8_t ys, const uint8_t xe, const uint8_t ye, const uint8_t color);
//Draws a filled rectangle.
void drawFRect(const uint8_t xs, const uint8_t ys, const uint8_t xe, const uint8_t ye, const uint8_t color);
//Draws a regular polygon
void drawRPoly(const uint8_t xc, const uint8_t yc, const uint8_t radius, const uint8_t edges, const uint8_t angleOffset, const uint8_t color);
//Draws a filled regular polygon
void drawRFPoly(const uint8_t xc, const uint8_t yc, const uint8_t radius, const uint8_t edges, const uint8_t angleOffset, const uint8_t color);
//Draws a polygon following the points given
void drawPoly(const uint8_t edges, const uint8_t color, const uint8_t* points);
//Draws a filled polygon following the points given
void drawFPoly(const uint8_t edges, const uint8_t color, const uint8_t* points);
//Draws a segmented line, points are structured as follow: [x0,y0,x1,y1,x2,y2,x3,y3,x4,y4...]
void drawKinkLine(const uint8_t length, const uint8_t color, const uint8_t* points);
//Draws a character
void drawChar(const uint8_t x, const uint8_t y, const char c, const uint8_t color);
//Draws a string of characters, returns length of printed string
uint8_t drawString(const uint8_t xs, const uint8_t ys, const char* s, const uint8_t color);
//Draws a sprite
void drawSprite(const uint8_t x, const uint8_t y, const uint8_t spritID, const uint8_t options);

//Colors inside a shape using the edge fake color
void colorIn(const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2, const uint8_t color);


#define guess_prescaler0(note) (((note) < 15) ? 5 :(\
                               ((note) < 39) ? 4 : 3))

#define guess_prescaler2(note) (((note) < 15) ? 7 :(\
                               ((note) < 27) ? 6 :(\
                               ((note) < 39) ? 5 : 4)))

#define setupVoice0()   TCCR0A = 0x42;\
                        DDRB |= 1<<PB3

void changeVoice0(const uint8_t tone);

#define setupVoice1()   TCCR1A = 0x40;\
                        TCCR1B = 0x08;\
                        DDRD |= 1<<PD5

void changeVoice1(const uint8_t tone);

#define setupVoice2()   TCCR2A = 0x12;\
                        DDRD |= (1<<PD6)

void changeVoice2(const uint8_t tone);


#endif