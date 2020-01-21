/*
 * Author: Eric Chen, Paul Davies
 * 
 */

#include "Graphics.h"
#include <stdio.h>

void WriteAPixel(int x, int y, int Colour)
{
	WAIT_FOR_GRAPHICS;				// is graphics ready for new command

	GraphicsX1Reg = x;				// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;			// set pixel colour
	GraphicsCommandReg = PutAPixel;			// give graphics "write pixel" command
}

int ReadAPixel(int x, int y)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS;			// is graphics done reading pixel
	return (int)(GraphicsColourReg) ;	// return the palette number (colour)
}

void ProgramPalette(int PaletteNumber, int RGB)
{
    WAIT_FOR_GRAPHICS;
    GraphicsColourReg = PaletteNumber;
    GraphicsX1Reg = RGB >> 16   ;        // program red value in ls.8 bit of X1 reg
    GraphicsY1Reg = RGB ;                // program green and blue into ls 16 bit of Y1 reg
    GraphicsCommandReg = ProgramPaletteColour; // issue command
}

void HLine(int x1, int y1, int length, int Colour)
{
	int i;

	for(i = x1; i < x1+length; i++ )
		WriteAPixel(i, y1, Colour);
}

void VLine(int x1, int y1, int length, int Colour)
{
	int i;

	for(i = y1; i < y1+length; i++ )
		WriteAPixel(x1, i, Colour);
}

/*******************************************************************************
** Implementation of Bresenhams line drawing algorithm
*******************************************************************************/
int abs(int a)
{
    if(a < 0)
        return -a ;
    else
        return a ;
}

int sign(int a)
{
    if(a < 0)
        return -1 ;
    else if (a == 0)
        return 0 ;
    else
        return 1 ;
}

void Line(int x1, int y1, int x2, int y2, int Colour)
{
    // DrawLine: init x, y; get dx and dy
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);
    int i, temp, interchange = 0, error ;

// if x1=x2 and y1=y2 then it is a line of zero length so we are done

    if(dx == 0 && dy == 0)
        return ;

 // must be a complex line so use Bresenhams algorithm
    else    {

// swap delta x and delta y depending upon slop of line
// DrawLine1: swap and set interchange
        if(dy > dx) {
            temp = dx ;
            dx = dy ;
            dy = temp ;
            interchange = 1 ;
        }

// initialise the error term to compensate for non-zero intercept
// DrawLine2: set error
        error = (dy << 1) - dx ;    // error = (2 * dy) - dx

// main loop
        for(i = 1; i <= dx; i++)    {
            // DrawLine3: write pixel
            WriteAPixel(x, y, Colour);

            while(error >= 0)   {
                // DrawLine4: set error, x, y in the loop
                if(interchange == 1)
                    x += s1 ;
                else
                    y += s2 ;

                error -= (dx << 1) ;    // error = error - (dx * 2)
                // DrawLine5: decides if should go to DrawLine 4 or 6
            }
            // DrawLine6: set x, y, error
            if(interchange == 1)
                y += s2 ;
            else
                x += s1 ;

            error += (dy << 1) ;    // error = error + (dy * 2)

        }
    }
}

int HLineAcc(int x1, int y1, int length, int Colour) {
    /* check if inputs are valid */
    if (!POINT_POS_IS_VALID(x1, y1)){
        return 0;
    }
    else if (!POINT_POS_IS_VALID(x1+length, y1)) {
        return 0;
    }
    else if (!COLOR_IS_VALID(Colour)) {
        return 0;
    }
    /* now we can safely let the hardware does its job */
    else {
        WAIT_FOR_GRAPHICS;				// is graphics ready for new command
	    GraphicsX1Reg = x1;				// write coords to x1, y1
	    GraphicsY1Reg = y1;
        GraphicsX2Reg = x1+length;
        GraphicsY2Reg = y1;
        GraphicsColourReg = Colour;			// set pixel colour
        GraphicsCommandReg = DrawHLine;
        return 1;
    }
}

int VLineAcc(int x1, int y1, int length, int Colour) {
    /* check if inputs are valid */
    if (!POINT_POS_IS_VALID(x1, y1)){
        return 0;
    }
    else if (!POINT_POS_IS_VALID(x1, y1+length)) {
        return 0;
    }
    else if (!COLOR_IS_VALID(Colour)) {
        return 0;
    }
    /* now we can safely let the hardware does its job */
    else {
        WAIT_FOR_GRAPHICS;				// is graphics ready for new command
	    GraphicsX1Reg = x1;				// write coords to x1, y1
	    GraphicsY1Reg = y1;
        GraphicsX2Reg = x1;
        GraphicsY2Reg = y1+length;
        GraphicsColourReg = Colour;			// set pixel colour
        GraphicsCommandReg = DrawVLine;
        return 1;
    }
}

int LineAcc(int x1, int y1, int x2, int y2, int Colour){
    /* check if inputs are valid */
    if (x2-x1<=0 && y2-y1<=0) {
        return 0;
    }
    else if (!COLOR_IS_VALID(Colour)) {
        return 0;
    }
    /* now we can safely let the hardware does its job */
    else {
        WAIT_FOR_GRAPHICS;				// is graphics ready for new command
	    GraphicsX1Reg = x1;				// write coords to x1, y1
	    GraphicsY1Reg = y1;
        GraphicsX2Reg = x2;
        GraphicsY2Reg = y2;
        GraphicsColourReg = Colour;			// set pixel colour
        GraphicsCommandReg = DrawLine;
        return 1;
    }
}

int Rectangle(int x_ul, int y_ul, int dx, int dy, int Colour) {
    int x_ur = x_ul + dx;
    int y_ur = y_ul;
    int x_ll = x_ul;
    int y_ll = y_ul + dy;
    int x_lr = x_ul + dx;
    int y_lr = y_ul + dy;
    if (!POINT_POS_IS_VALID(x_ul, y_ul)
        || !POINT_POS_IS_VALID(x_ur, y_ur)
        || !POINT_POS_IS_VALID(x_ll, y_ll)
        || !POINT_POS_IS_VALID(x_lr, y_lr)) {
            return 0;
    }
    else if (!COLOR_IS_VALID(Colour)) {
        return 0;
    }
    else {
        HLineAcc(x_ul, y_ul, dx, Colour);
        HLineAcc(x_ll, y_ll, dx, Colour);
        VLineAcc(x_ul, y_ul, dy, Colour);
        VLineAcc(x_ur, y_ur, dy, Colour);
        return 0;
    }
}

void main() {
    int hline_ret = HLineAcc(100, 100, 100, YELLOW);
    printf("drawing horizontal line returns %d\n", hline_ret);
    int vline_ret = VLineAcc(150, 150, 150, TEAL);
    printf("drawing vertical line returns %d\n", vline_ret);
    int line_ret = LineAcc(100, 100, 150, 150, RED);
    printf("drawing line returns %d\n", line_ret);
    int rectangle_ret = Rectangle(250, 250, 100, 100, GREEN);
    printf("drawing rectangle returns %d\n", rectangle_ret);
}


