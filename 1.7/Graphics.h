/*
 * Author: Eric Chen, Paul Davies
 * 
 * useful definitions and declartions for the graphics library
 */

#ifndef GRAPHICS_H_
#define GRAPHIC_H_

// defined constants representing colours pre-programmed into colour palette
// there are 256 colours but only 8 are shown below, we write these to the colour registers
//
// the header files "Colours.h" contains constants for all 256 colours
// while the course file "ColourPaletteData.c" contains the 24 bit RGB data
// that is pre-programmed into the palette
#include "Colours.h"

// graphics register addresses
#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0xFF210000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0xFF210000))
#define GraphicsX1Reg   			(*(volatile unsigned short int *)(0xFF210002))
#define GraphicsY1Reg   			(*(volatile unsigned short int *)(0xFF210004))
#define GraphicsX2Reg   			(*(volatile unsigned short int *)(0xFF210006))
#define GraphicsY2Reg   			(*(volatile unsigned short int *)(0xFF210008))
#define GraphicsColourReg   		(*(volatile unsigned short int *)(0xFF21000E))
#define GraphicsBackGroundColourReg   	(*(volatile unsigned short int *)(0xFF210010))

/************************************************************************************************
** This macro pauses until the graphics chip status register indicates that it is idle
***********************************************************************************************/
#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

// defined constants representing values we write to the graphics 'command' register to get
// it to draw something. You will add more values as you add hardware to the graphics chip
// Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these
#define DrawHLine		1
#define DrawVLine		2
#define DrawLine		3
#define DrawArc         4
#define DrawCircle      5
#define	PutAPixel		0xA
#define	GetAPixel		0xB
#define	ProgramPaletteColour    0x10

/* Upper boundaries for x and y
 */
#define DIM_X 800   // 800 by default
#define DIM_Y 480  // 480 by default

/* Macro to check if a given colour is valid
 */
#define COLOR_IS_VALID(x)   (x>=0 && x<63)

/* Macro to check if a given point is out of bound
 */
#define POINT_POS_IS_VALID(x, y) (x>=0 && x<DIM_X && y>=0 && y<DIM_Y)

/*******************************************************************************************
* This function writes a single pixel to the x,y coords specified using the specified colour
* Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
********************************************************************************************/
void WriteAPixel(int x, int y, int Colour);

/*********************************************************************************************
* This function read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/
int ReadAPixel(int x, int y);

/**********************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
**
************************************************************************************/
void ProgramPalette(int PaletteNumber, int RGB);

/* This function draw a horizontal line, 1 pixel at a time starting at the 
 *x,y coords specified
 */
void HLine(int x1, int y1, int length, int Colour);

/* This function draw a vertical line, 1 pixel at a time starting at the 
 * x,y coords specified
 */
void VLine(int x1, int y1, int length, int Colour);

/* Draw a line without accelerator
 */
void Line(int x1, int y1, int x2, int y2, int Colour);

/* draw horizontal line with accelerator;
 * requires non-negative length;
 * return true if line can be drawn; false otherwise
 */
int HLineAcc(int x1, int y1, int length, int Colour);

/* draw vertical line with accelerator
 * requires non-negative length;
 * return true if line can be drawn; false otherwise
 */
int VLineAcc(int x1, int y1, int length, int Colour);

/* fills the entire screen with one colour;
 * requires valid colour input
 */
void FillScreen(int Colour);

/* draw line from & to specified points with accelerator
 * return true if line can be drawn; false otherwise
 */
int LineAcc(int x1, int y1, int x2, int y2, int Colour);

/* draw a rectangle with accelerator, using the specified
 * upper-left coordinate and dx, dy;
 * returns true if the figure can be drawn; false otherwise
 */
int Rectangle(int x_ul, int y_ul, int dx, int dy, int Colour);

/* draw a filled rectangle with no border;
 * returns true if the figure can be drawn; false otherwise
 */
int RectangleFilled(int x_ul, int y_ul, int dx, int dy, int FillColour);

/* draw a filled rectangle with border;
 * returns true if the figure can be drawn; false otherwise
 */
int RectangleFilledWBorder(int x_ul, int y_ul, int dx, int dy, int BorderColour, int FillColour, int BorderWidth);

/* draw a triangle with accelerator, using the three given
 * coordinates;
 * returns true if the figure can be drawn; false otherwise
 */
int Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int Colour);

/* draw a circle with parameters as specified; use hardware
 * acceleration.
 * requires user to make sure the circle can be completely
 * drawn on screen TODO: maybe shoule allow incomplete circle
 * to be drawn?
 */
void Circle(int x_ctr, int y_ctr, int radius, int BorderColour, int FillColour, int BorderWidth);

/* draw an arc with the following parameters:
 * x_ctr and y_ctr - center of the arc
 * deg1, deg2 - degree of the boundary points, measured in
 * degree, CCW
 * Colour - colour of the arc
 * the function allows an incomplete arc to be drawn
 */
void Arc(int x_ctr, int y_ctr, int deg1, int deg2, int Colour);

// TODO: may add functions to draw clubs, diamonds, hearts, spades

/* print a character to screen using 5x7 font
 */
void OutGraphicsCharFont5x7(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);

/* print a character to screen using 10x14 font
 */
void OutGraphicsCharFont10x14(int x, int y, int colour, int backgroundcolour, int c, int Erase);

/* print a character to screen using 16x27 font
 */
void OutGraphicsCharFont16x27(int x, int y, int colour, int backgroundcolour, int c, int Erase);

/* print a character to screen using 22x40 font
 */
void OutGraphicsCharFont22x40(int x, int y, int colour, int backgroundcolour, int c, int Erase);

#endif /* GRAPHICS_H_ */