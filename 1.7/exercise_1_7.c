/*
 * Author: Eric Chen, Paul Davies
 * 
 */

#include "graphics.h"
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
    if (length<1) {
        return 0;   // does not allow 0-length segments
    }
    else if (!POINT_POS_IS_VALID(x1, y1)){
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
    if (length<1) {
        return 0;   // does not allow 0-length segments
    }
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

void FillScreen(int Colour) {
    int i;
    for (i=0; i<DIM_Y; i++) {
        HLineAcc(0, i, DIM_X-1, Colour);
    }
    return;
}

int LineAcc(int x1, int y1, int x2, int y2, int Colour){
    /* check if inputs are valid */
    if (!POINT_POS_IS_VALID(x1, y1)
        || !POINT_POS_IS_VALID(x2, y2)) {
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
    /* check if inputs are valid */
    if (dx<1 || dy<1) {
        return 0;   // enforce positive dx and dy
    }
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
        return 1;
    }
}

int RectangleFilled(int x_ul, int y_ul, int dx, int dy, int FillColour) {
    /* check if inputs are valid */
    if (dx<1 || dy<1) {
        return 0;   // enforce positive dx and dy
    }
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
    else if (!COLOR_IS_VALID(FillColour)) {
        return 0;
    }
    else {
        int i;
        for (i=0; i<dy; i++) {
            HLineAcc(x_ul, y_ul+i, dx, FillColour);
        }
        return 1;
    }
}

int RectangleFilledWBorder(int x_ul, int y_ul, int dx, int dy, int BorderColour, int FillColour, int BorderWidth) {
    /* check if inputs are valid */
    if (dx<1 || dy<1) {
        return 0;   // enforce positive dx and dy
    }
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
    else if (dx<=2*BorderWidth) {
        return 0;
    }
    else if (!COLOR_IS_VALID(FillColour) || !COLOR_IS_VALID(BorderColour)) {
        return 0;
    }
    else {
        int i;
        for (i=0; i<BorderWidth; i++) {
            HLineAcc(x_ul, y_ul+i, dx, BorderColour);
            HLineAcc(x_ll, y_ll-i, dx, BorderColour);
            VLineAcc(x_ul+i, y_ul, dy, BorderColour);
            VLineAcc(x_ur-i, y_ur, dy, BorderColour);
        }
        for (i=0; i<=dy-2*BorderWidth; i++) {
            HLineAcc(x_ul+BorderWidth, y_ul+BorderWidth+i, dx-2*BorderWidth, FillColour);
        }      
        return 1;
    }
}

int Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int Colour) {
    if (!POINT_POS_IS_VALID(x1, y1)
        || !POINT_POS_IS_VALID(x2, y2)
        || !POINT_POS_IS_VALID(x3, y3)) {
        return 0;
    }
    else if (!COLOR_IS_VALID(Colour)) {
        return 0;
    }
    else {
        LineAcc(x1, y1, x2, y2, Colour);
        LineAcc(x2, y2, x3, y3, Colour);
        LineAcc(x3, y3, x1, y1, Colour);
        return 1;
    }
}

void Arc(int x_ctr, int y_ctr, int deg1, int deg2, int Colour) {
    // TODO: may require changes later on
    WAIT_FOR_GRAPHICS;				// is graphics ready for new command
	GraphicsX1Reg = x_ctr;				// write coords to x1, y1
	GraphicsY1Reg = y_ctr;
    GraphicsX2Reg = deg1;
    GraphicsY2Reg = deg2;
    GraphicsColourReg = Colour;			// set pixel colour
    GraphicsCommandReg = DrawArc;
    return;
}

void main() {
    FillScreen(DARK_OLIVE_GREEN);
    int hline_ret = HLineAcc(100, 477, 690, YELLOW);
    printf("drawing horizontal line returns %d\n", hline_ret);
    int vline_ret = VLineAcc(790, 101, 150, TEAL);
    printf("drawing vertical line returns %d\n", vline_ret);
    int line_ret = LineAcc(100, 100, 150, 150, RED);
    printf("drawing line returns %d\n", line_ret);
    line_ret = LineAcc(150, 300, 750, 450, PINK);
    printf("drawing line returns %d\n", line_ret);
    int rectangle_ret = Rectangle(250, 250, 100, 100, BLUE);
    printf("drawing rectangle returns %d\n", rectangle_ret);
    int triangle_ret = Triangle(251, 251, 311, 192, 304, 471, ORANGE);
    printf("drawing triangle returns %d\n", triangle_ret);
    int rectangle_filled_ret = RectangleFilled(361, 361, 92, 92, PURPLE);
    printf("drawing filled rectangle returns %d\n", rectangle_filled_ret);
    int rectangle_filled_w_border_ret = RectangleFilledWBorder(505, 200, 121, 121, BLACK, RED, 9);
    printf("drawing filled rectangle with border returns %d\n", rectangle_filled_w_border_ret);
}


