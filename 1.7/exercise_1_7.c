/*
 * Author: Eric Chen
 * 
 */

#include "Graphics.h"
#include <stdio.h>

int HLineAcc(int x1, int y1, int length, int Colour) {
    /* check if inputs are valid */
    if (x1<0 || x1>=DIM_X) {
        return 0;
    }
    else if (y1<0 || y1>=DIM_Y) {
        return 0;
    }
    else if (x1+length>=DIM_X) {
        return 0;
    }
    else if (COLOR_IS_VALID(Colour)) {
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
    if (x1<0 || x1>=DIM_X) {
        return 0;
    }
    else if (y1<0 || y1>=DIM_Y) {
        return 0;
    }
    else if (y1+length>=DIM_Y) {
        return 0;
    }
    else if (COLOR_IS_VALID(Colour)) {
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

void Line(int x1, int y1, int x2, int y2, int Colour){
    // TODO: stub
}

void main() {
    // TODO: stub
}


