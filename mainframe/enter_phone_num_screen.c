/*
 * Author: Eric Chen, Paul Davies
 * 
 */

#include "graphics.h"
#include <stdio.h>
#include "Fonts.c"
#include "ColourPallette.c"

#define TRUE 1
#define FALSE 0

/* for various screens */
#define PHONEPAD_INIT_X 300
#define PHONEPAD_INIT_Y 120
#define PHONEPAD_BUTTON_WIDTH 35
#define PHONEPAD_BUTTON_HEIGHT 45
#define PHONEPAD_BUTTON_BORDER_WIDTH 2
#define PHONEPAD_BUTTON_SEPARATION_X 35
#define PHONEPAD_BUTTON_SEPARATION_Y 25
#define CONFIRM_AND_CLEAR_WIDTH   200
#define CONFIRM_AND_CLEAR_HEIGHT  50
#define CONFIRM_AND_CLEAR_BORDER_WIDTH 2
#define CONFIRM_AND_CLEAR_INIT_Y 400
#define CLEAR_INIT_X 100
#define CONFIRM_INIT_X 500

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

void Circle(int x_ctr, int y_ctr, int radius, int BorderColour, int FillColour, int BorderWidth)
{
    WAIT_FOR_GRAPHICS;
    GraphicsX1Reg = x_ctr;				// write coords to x1, y1
	GraphicsY1Reg = y_ctr;
    GraphicsX2Reg = radius;
    GraphicsY2Reg = BorderWidth;
    GraphicsColourReg = BorderColour;
    GraphicsBackGroundColourReg = FillColour;
    GraphicsCommandReg = DrawCircle;
    return;
}

void OutGraphicsCharFont5x7(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixels ;
	register char theColour = fontcolour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother

    if(((short)(x) > (short)(DIM_X-1)) || ((short)(y) > (short)(DIM_Y-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		for(row = 0; (char)(row) < (char)(7); row ++)	{

// get the bit pattern for row 0 of the character from the software font
			pixels = Font5x7[theC][row] ;
			BitMask = 16 ;

			for(column = 0; (char)(column) < (char)(5); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == TRUE)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void OutGraphicsCharFont10x14(int x, int y, int colour, int backgroundcolour, int c, int Erase)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					j,
					theRow, theColumn;


    if(((short)(x) > (short)(DIM_X-1)) || ((short)(y) > (short)(DIM_Y-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = 14;
		theColumn = 10;

		for(row = 0; row < theRow ; row ++)	{
			pixels = Font10x14[theCharacter][row] ;		     								// get the pixels for row 0 of the character to be displayed
			BitMask = 512 ;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn;   )  	{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel(theX+column, theY+row, theColour) ;
				else {																		// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == TRUE)
						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
					// else leave it alone
				}
					column ++ ;
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void OutGraphicsCharFont16x27(int x, int y, int colour, int backgroundcolour, int c, int Erase) {
    register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					j,
					theRow, theColumn;


    if(((short)(x) > (short)(DIM_X-1)) || ((short)(y) > (short)(DIM_Y-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																		// subtract hex 20 to get index of first printable character (the space character)
        theRow = 27;
		theColumn = 16;

		for(row = 0; row < theRow ; row ++)	{
			BitMask = 128;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn; column++)  	{
                if (column<8) {
                    pixels= Font16x27[theCharacter*theRow*2 + 2*row];
                }
                else {
                    pixels = Font16x27[theCharacter*theRow*2 + 2*row + 1];
                }
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel(theX+column, theY+row, theColour);
				else {																		// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == TRUE)
						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
					// else leave it alone
				}
				BitMask = BitMask >> 1 ;
                if (BitMask == 0) {
                    BitMask = 128; // reset bitmask
                }
			}
		}
	}
}

void OutGraphicsCharFont22x40(int x, int y, int colour, int backgroundcolour, int c, int Erase) {
    register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					j,
					theRow, theColumn;


    if(((short)(x) > (short)(DIM_X-1)) || ((short)(y) > (short)(DIM_Y-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																		// subtract hex 20 to get index of first printable character (the space character)
        theRow = 40;
		theColumn = 22;

		for(row = 0; row < theRow ; row ++)	{
            BitMask = 128;
			for(column = 0; column < theColumn; column++)  	{
                if (column<8) {
                    pixels= Font22x40[theCharacter*theRow*3 + 3*row];
                }
                else if (column<16) {
                    pixels= Font22x40[theCharacter*theRow*3 + 3*row + 1];
                }
                else {
                    pixels = Font22x40[theCharacter*theRow*3 + 3*row + 2];
                }
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel(theX+column, theY+row, theColour);
				else {																		// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == TRUE)
						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
					// else leave it alone
				}
				BitMask = BitMask >> 1 ;
                if (BitMask == 0) {
                    BitMask = 128; // reset bitmask
                }
			}
		}
	}
}

/*
 * render everything on the phone number screen.
 */
void RenderEnterPhoneNumberScreen() {
    /* render background */
    FillScreen(RED);
    
    /* render the instruction line */
    char instructionLine[] = {'P', 'l', 'e', 'a', 's', 'e', ' ', 'e', 'n', 't', 'e', 'r',
                                ' ', 'y', 'o', 'u', 'r', ' ', 'p', 'h', 'o', 'n', 'e', ' ',
                                'n', 'u', 'm', 'b', 'e', 'r', ':'};
    int i;
    int x=150; int y=50;
    for (i=0; i<31; i++) {
        OutGraphicsCharFont10x14(x, y, WHITE, WHITE, instructionLine[i], 0);
        x+= 15;
    }

    /* render the entry box */
    RectangleFilledWBorder(150, 80, 500, 25, BROWN, ORANGE, 4);
    
    /* render the phone pad */
    int num=1;
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (y=PHONEPAD_INIT_Y; num>0; y+=(PHONEPAD_BUTTON_HEIGHT+PHONEPAD_BUTTON_SEPARATION_Y)) {
        if (num>9) {
            num = 0;
            RectangleFilledWBorder(PHONEPAD_INIT_X+PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X, y, PHONEPAD_BUTTON_WIDTH, PHONEPAD_BUTTON_HEIGHT, BLACK, WHITE, 2);
            OutGraphicsCharFont22x40(PHONEPAD_INIT_X+PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X+PHONEPAD_BUTTON_BORDER_WIDTH+5, y+PHONEPAD_BUTTON_BORDER_WIDTH+2, BLACK, BLACK, numbers[num], 0);
            break;
        }
        for (x=PHONEPAD_INIT_X; x<PHONEPAD_INIT_X+3*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X); x+=(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)) {
            RectangleFilledWBorder(x, y, PHONEPAD_BUTTON_WIDTH, PHONEPAD_BUTTON_HEIGHT, BLACK, WHITE, 2);
            OutGraphicsCharFont22x40(x+PHONEPAD_BUTTON_BORDER_WIDTH+5, y+PHONEPAD_BUTTON_BORDER_WIDTH+2, BLACK, BLACK, numbers[num], 0);
            num += 1;
        }
    }

    /* render the clear and confirm button */
    char clearLine[] = {'C', 'L', 'E', 'A', 'R'};
    char confirmLine[] = {'C', 'O', 'N', 'F', 'I', 'R', 'M'};
    RectangleFilledWBorder(CLEAR_INIT_X, CONFIRM_AND_CLEAR_INIT_Y, CONFIRM_AND_CLEAR_WIDTH, CONFIRM_AND_CLEAR_HEIGHT, BLACK, SILVER, CONFIRM_AND_CLEAR_BORDER_WIDTH);
    for (i=0; i<5; i++) {
        OutGraphicsCharFont22x40(CLEAR_INIT_X+CONFIRM_AND_CLEAR_BORDER_WIDTH+25+i*25, CONFIRM_AND_CLEAR_INIT_Y+CONFIRM_AND_CLEAR_BORDER_WIDTH+4, BLACK, WHITE, clearLine[i], 0);
    }
    RectangleFilledWBorder(CONFIRM_INIT_X, CONFIRM_AND_CLEAR_INIT_Y, CONFIRM_AND_CLEAR_WIDTH, CONFIRM_AND_CLEAR_HEIGHT, BLACK, SILVER, CONFIRM_AND_CLEAR_BORDER_WIDTH);
    for (i=0; i<7; i++) {
        OutGraphicsCharFont22x40(CONFIRM_INIT_X+CONFIRM_AND_CLEAR_BORDER_WIDTH+8+i*25, CONFIRM_AND_CLEAR_INIT_Y+CONFIRM_AND_CLEAR_BORDER_WIDTH+4, BLACK, WHITE, confirmLine[i], 0);
    }    
}

void main() {
    int i;
    for (i=0; i<64; i++) {
        ProgramPalette(i, ColourPalletteData[i]);
    }
    FillScreen(BLACK);

    RenderEnterPhoneNumberScreen();
}


