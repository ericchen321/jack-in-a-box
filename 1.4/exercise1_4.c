/*
 * Author: Eric Chen
 * Developed based on code from Exercise 1.3 by Larry Liu
 */ 

/* definitions for RS232 port
 */
#define RS232_ReceiverFifo                      (*(volatile unsigned char *)(0xFF210200)) 
#define RS232_TransmitterFifo                   (*(volatile unsigned char *)(0xFF210200)) 
#define RS232_InterruptEnableReg                (*(volatile unsigned char *)(0xFF210202))
#define RS232_InterruptIdentificationReg        (*(volatile unsigned char *)(0xFF210204)) 
#define RS232_FifoControlReg                    (*(volatile unsigned char *)(0xFF210204)) 
#define RS232_LineControlReg                    (*(volatile unsigned char *)(0xFF210206)) 
#define RS232_ModemControlReg                   (*(volatile unsigned char *)(0xFF210208)) 
#define RS232_LineStatusReg                     (*(volatile unsigned char *)(0xFF21020A)) 
#define RS232_ModemStatusReg                    (*(volatile unsigned char *)(0xFF21020C)) 
#define RS232_ScratchReg                        (*(volatile unsigned char *)(0xFF21020E)) 
#define RS232_DivisorLatchLSB                   (*(volatile unsigned char *)(0xFF210200)) 
#define RS232_DivisorLatchMSB                   (*(volatile unsigned char *)(0xFF210202)) 
/* definitions for touchscreen
 */
#define TouchScreen_Offset                      (volatile unsigned char *)(0x00000030) // from the RS232 port
#define TouchScreen_ReceiverFifo                (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_ReceiverFifo))
#define TouchScreen_TransmitterFifo             (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_TransmitterFifo))   
#define TouchScreen_InterruptEnableReg          (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_InterruptEnableReg))
#define TouchScreen_InterruptIdentificationReg  (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_InterruptIdentificationReg))
#define TouchScreen_FifoControlReg              (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_FifoControlReg))
#define TouchScreen_LineControlReg              (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_LineControlReg))
#define TouchScreen_ModemControlReg             (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_ModemControlReg))
#define TouchScreen_LineStatusReg               (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_LineStatusReg))
#define TouchScreen_ModemStatusReg              (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_ModemStatusReg))
#define TouchScreen_ScratchReg                  (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_ScratchReg))
#define TouchScreen_DivisorLatchLSB             (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_DivisorLatchLSB))
#define TouchScreen_DivisorLatchMSB             (*(volatile unsigned char *)((int)TouchScreen_Offset + (int)&RS232_DivisorLatchMSB))

/* helpful macros
 */
#define TS_DEBUG 1
#define TS_PEN_UP 1
#define TS_PEN_DOWN 0
#define TS_DIM_X 1024
#define TS_DIM_Y 1024
#define IMG_DIM_X 1024
#define IMG_DIM_Y 1024

#include <stdio.h>

void Init_RS232(void) {   
    RS232_LineControlReg = 0b10000000;
    RS232_DivisorLatchLSB = 0x45;
    RS232_DivisorLatchMSB = 0x01;
    RS232_LineControlReg = 0b00110011;
    RS232_FifoControlReg = 0b110;
    RS232_FifoControlReg = 0;
} 
 
int putcharRS232(int c) {   
    while( ((RS232_LineStatusReg >> 5) & 1) == 0){}
    RS232_TransmitterFifo = c;
    return c;
} 
 
int getcharRS232( void ) {  
    while ((RS232_LineStatusReg & 1) == 0){}
    return RS232_ReceiverFifo;
} 
 
int RS232TestForReceivedData(void) { 
    return (RS232_LineStatusReg & 1);
} 
 
void RS232Flush(void) { 
    volatile int dummy = 0;
    while(RS232_LineStatusReg & 1) {
        dummy += RS232_ReceiverFifo;
    }
    return;   
}

/* helper to send a char to touchscreen
 */
int putcharTouchScreen(unsigned char c) {
    while( ((TouchScreen_LineStatusReg >> 5) & 1) == 0){}
    TouchScreen_TransmitterFifo = c;
    return c;
}

/* helper to get a char from touchscreen
 */
unsigned char getcharTouchScreen(void) {  
    while ((TouchScreen_LineStatusReg & 1) == 0){}
    return TouchScreen_ReceiverFifo;
} 

/* helper to clear off UART read buffer for touchscreen
 */
void TouchScreenFlush(void) { 
    volatile int dummy = 0;
    while(TouchScreen_LineStatusReg & 1) {
        dummy += TouchScreen_ReceiverFifo;
    }
    return;   
}

/* initialize touchscreen
 */
void Init_Touch(void) {
    // Program serial port to communicate with touchscreen 
    TouchScreen_LineControlReg = 0b10000000;
    TouchScreen_DivisorLatchLSB = 0x45;
    TouchScreen_DivisorLatchMSB = 0x01;
    TouchScreen_LineControlReg = 0b00110011;
    TouchScreen_FifoControlReg = 0b110;
    TouchScreen_FifoControlReg = 0;
    // do "disable touch" first to avoid interference from touch reports
    putcharTouchScreen(0x55);
    putcharTouchScreen(0x01);
    putcharTouchScreen(0x13);
#ifdef TS_DEBUG
    getcharTouchScreen();
    getcharTouchScreen();
    if (getcharTouchScreen() == 0) {
        printf("touchscreen disabled\n");
    }
    else {
        printf("touchsreen failed to disable!\n");
    }
#endif
    TouchScreenFlush();
    // send touchscreen controller an "enable touch" command 
    putcharTouchScreen(0x55);
    putcharTouchScreen(0x01);
    putcharTouchScreen(0x12);
#ifdef TS_DEBUG
    getcharTouchScreen();
    getcharTouchScreen();
    if (getcharTouchScreen() == 0) {
        printf("touchscreen enabled\n");
    }
    else {
        printf("touchsreen failed to enable!\n");
    }
#endif
    TouchScreenFlush();
}

/* helper to check if any data coming in from touchscreen 
 */
int TouchScreenTestForReceivedData(void) { 
    return (TouchScreen_LineStatusReg & 1);
}

/* helper to parse a touch report's 1st byte.
 * returns TRUE if a report exists; FALSE if not;
 * assigns valid up/down only if the function
 * returns TRUE
 */
int TouchScreenParseDirection(int* up_or_down) {
    if (!TouchScreenTestForReceivedData()) {
        return 0;
    }
    else {
        unsigned char byte = getcharTouchScreen();
        if (byte==0x80) {
            *up_or_down = TS_PEN_DOWN;
            return 1;
        }
        else if (byte==0x81) {
            *up_or_down = TS_PEN_UP;
            return 1;
        }
        else {
            return 0;
        }
    }
}

/* helper to parse a touch report without the 1st byte.
 * requires called after the pen up/down byte alread parsed
 * returns TRUE if a report exists; FALSE if not;
 * assigns valid values to given arguments only if the function
 * returns TRUE
 */
int TouchScreenParseReport(int* x, int* y) {
    int i;
    unsigned int x_temp, y_temp;
    for (i=1; i<=4; i++) {
        if (!TouchScreenTestForReceivedData()) {
            return 0;
        }
        unsigned char byte = getcharTouchScreen();
        /* parse x/y pos */
        if (i==1) {
                x_temp = (unsigned int)byte>>2;
        }
        else if (i==2) {
                x_temp = (unsigned int)byte<<5 | x_temp;
        }
        else if (i==3) {
                y_temp = (unsigned int)byte>>2;
        }
        else {
                y_temp = (unsigned int)byte<<5 | y_temp;
        }
    }
    if (x!=NULL)
        *x = x_temp;
    if (y!=NULL)
        *y = y_temp;
    return 1;
}

/* test if screen touched;
 * return TRUE if the function can read a pen down
 * report from the head of the read buffer, or FALSE 
 * otherwise
 */
int ScreenTouched(void) {
    int up_or_down;
    if (TouchScreenParseDirection(&up_or_down)) {
        if (up_or_down==TS_PEN_DOWN) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

/* wait for screen to be touched
 */
void WaitForTouch() {
    TouchScreenFlush();
    while(!ScreenTouched()) {
        printf("waiting for touch\n"); // neceesary delay
    } 
}

/* helper to test if screen released;
 * return TRUE if the function can read a pen up
 * report from the head of the read buffer, or FALSE 
 * otherwise
 */
int ScreenReleased(void) {
    int up_or_down;
    if (TouchScreenParseDirection(&up_or_down)) {
        if (up_or_down==TS_PEN_UP) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

/* helper to wait for screen to be released
 */
void WaitForRelease() {
    TouchScreenFlush();
    while(!ScreenReleased()) {
        printf("waiting for release\n"); // neceesary delay
    } 
}

/* a data type to hold a point/coord */ 
typedef struct { int x, y; } Point ; 
 
/* This function waits for a touch screen press event and returns X,Y coord 
 */
Point GetPress(void) 
{    
    Point p1; 
    // wait for a pen down command then return the X,Y coord of the point
    WaitForTouch();
    int report_ret = TouchScreenParseReport(&(p1.x), &(p1.y));
#ifdef TS_DEBUG
    if (!report_ret) {
        printf("cannot parse a pen down report!\n");
    }
#endif
    // calibrated correctly so that it maps to a pixel on screen
    p1.x = (int)((float)p1.x * IMG_DIM_X/1024.0);
    p1.y = (int)((float)p1.y * IMG_DIM_Y/1024.0);
 
    return p1; 
}

/* This function waits for a touch screen release event and returns X,Y coord;
 */
Point GetRelease(void) {     
    Point p1;       
    // wait for a pen up command then return the X,Y coord of the point
    WaitForRelease();
    int parse_report_ret = TouchScreenParseReport(&(p1.x), &(p1.y));
#ifdef TS_DEBUG
    if (!parse_report_ret) {
        printf("cannot parse a pen down report!\n");
    }
#endif
    // calibrated correctly so that it maps to a pixel on screen 
    p1.x = (int)((float)p1.x * IMG_DIM_X/TS_DIM_X);
    p1.y = (int)((float)p1.y * IMG_DIM_Y/TS_DIM_Y);
 
    return p1; 
} 

void main(){
    Init_Touch();
    /*
    while (1) {
        WaitForTouch();
        printf("touched\n");
    }
    
    while (1) {
        WaitForRelease();
        printf("released\n");
    }
    
    
    while (1) {
        Point p = GetPress();
        printf("press: p_x: %d, p_y:%d\n", p.x, p.y);
    }
    */
    while (1) {
        Point p = GetRelease();
        printf("release: p_x: %d, p_y:%d\n", p.x, p.y);
    }
    
}