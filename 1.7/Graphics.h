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
#define DrawLine			3
#define	PutAPixel		0xA
#define	GetAPixel		0xB
#define	ProgramPaletteColour    0x10

/* Upper boundaries for x and y
 */
#define DIM_X 800
#define DIM_Y 480

/* Macro to check if a given colour is valid
 */
#define COLOR_IS_VALID(x)   (x>=0 && x<=255)

/* draw horizontal line with accelerator
 * return true if line can be drawn; false otherwise
 */
int HLineAcc(int x1, int y1, int length, int Colour);

/* draw vertical line with accelerator
 * return true if line can be drawn; false otherwise
 */
void VLineAcc(int x1, int y1, int length, int Colour);

/* draw line from & to specified points with accelerator
 * return true if line can be drawn; false otherwise
 */
void Line(int x1, int y1, int x2, int y2, int Colour);

#endif /* GRAPHICS_H_ */