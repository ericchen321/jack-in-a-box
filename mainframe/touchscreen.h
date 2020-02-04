/*
 * Author: Eric Chen, Paul Davies
 * 
 * useful definitions and declartions for the touchscreen library
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#include "Graphics.h"

/* definitions for RS232 ports
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
/* definitions for touchscreen ports
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
#define IMG_DIM_X DIM_X
#define IMG_DIM_Y DIM_Y

/* a data type to hold a point/coord */ 
typedef struct { 
    int x, y; 
} Point; 

/* initialize touchscreen
 */
void Init_Touch(void);

/* test if screen touched;
 * return TRUE if the function can read a pen down
 * report from the head of the read buffer, or FALSE 
 * otherwise
 */
int ScreenTouched(void);

/* wait for screen to be touched
 */
void WaitForTouch(void);

/* test if screen released;
 * return TRUE if the function can read a pen up
 * report from the head of the read buffer, or FALSE 
 * otherwise
 */
int ScreenReleased(void);

/* wait for screen to be released
 */
void WaitForRelease(void);

/* This function waits for a touch screen press event and returns X,Y coord 
 */
Point GetPress(void);

/* This function waits for a touch screen release event and returns X,Y coord;
 */
Point GetRelease(void);

#endif /* TOUCHSCREEN_H_ */




