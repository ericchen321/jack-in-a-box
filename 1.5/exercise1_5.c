/*
 * Author: Ben Harder
 * Developed based on code from Exercise 1.3 by Larry Liu
 */

// RS232 definitions
#define RS232_ReceiverFifo (*(volatile unsigned char *)(0xFF210200))
#define RS232_TransmitterFifo (*(volatile unsigned char *)(0xFF210200))
#define RS232_InterruptEnableReg (*(volatile unsigned char *)(0xFF210202))
#define RS232_InterruptIdentificationReg (*(volatile unsigned char *)(0xFF210204))
#define RS232_FifoControlReg (*(volatile unsigned char *)(0xFF210204))
#define RS232_LineControlReg (*(volatile unsigned char *)(0xFF210206))
#define RS232_ModemControlReg (*(volatile unsigned char *)(0xFF210208))
#define RS232_LineStatusReg (*(volatile unsigned char *)(0xFF21020A))
#define RS232_ModemStatusReg (*(volatile unsigned char *)(0xFF21020C))
#define RS232_ScratchReg (*(volatile unsigned char *)(0xFF21020E))
#define RS232_DivisorLatchLSB (*(volatile unsigned char *)(0xFF210200))
#define RS232_DivisorLatchMSB (*(volatile unsigned char *)(0xFF210202))

// Defititions for GPS
#define GPS_Offset (volatile unsigned char *)(0x00000010) // as specified in SerialIODecoder.v, in relation to RS232
#define GPS_ReceiverFifo (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_ReceiverFifo))
#define GPS_TransmitterFifo (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_TransmitterFifo))
#define GPS_InterruptEnableReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_InterruptEnableReg))
#define GPS_InterruptIdentificationReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_InterruptIdentificationReg))
#define GPS_FifoControlReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_FifoControlReg))
#define GPS_LineControlReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_LineControlReg))
#define GPS_ModemControlReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_ModemControlReg))
#define GPS_LineStatusReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_LineStatusReg))
#define GPS_ModemStatusReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_ModemStatusReg))
#define GPS_ScratchReg (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_ScratchReg))
#define GPS_DivisorLatchLSB (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_DivisorLatchLSB))
#define GPS_DivisorLatchMSB (*(volatile unsigned char *)((int)GPS_Offset + (int)&RS232_DivisorLatchMSB))

#include <stdio.h>

void Init_RS232(void)
{
    RS232_LineControlReg = 0b10000000;
    RS232_DivisorLatchLSB = 0x58;
    RS232_DivisorLatchMSB = 0x14;
    RS232_LineControlReg = 0b00110011;
    RS232_FifoControlReg = 0b110;
    RS232_FifoControlReg = 0;
}

int putcharRS232(int c)
{
    while (((RS232_LineStatusReg >> 5) & 1) == 0)
    {
    }
    RS232_TransmitterFifo = c;
    return c;
}

int getcharRS232(void)
{
    while ((RS232_LineStatusReg & 1) == 0)
    {
    }
    return RS232_ReceiverFifo;
}

int RS232TestForReceivedData(void) { return (RS232_LineStatusReg & 1); }

void RS232Flush(void)
{
    volatile int dummy = 0;
    while (RS232_LineStatusReg & 1)
    {
        dummy += RS232_ReceiverFifo;
    }
    return;
}

// GPS methods

/* helper to send a char to GPS
 */
int putcharGPS(unsigned char c)
{
    while (((GPS_LineStatusReg >> 5) & 1) == 0)
    {
    }
    GPS_TransmitterFifo = c;
    return c;
}

/* helper to get a char from GPS
 */
unsigned char getcharGPS(void)
{
    while ((GPS_LineStatusReg & 1) == 0)
    {
    }
    return GPS_ReceiverFifo;
}

/* helper to clear off UART read buffer for GPS
 */
void GPSFlush(void)
{
    volatile int dummy = 0;
    while (GPS_LineStatusReg & 1)
    {
        dummy += GPS_ReceiverFifo;
    }
    return;
}

/* helper to check if any data coming in from GPS 
 */
int GPSTestForReceivedData(void)
{
    return (GPS_LineStatusReg & 1);
}

/* Init for the serial port to communicate with the GPS
 */
void Init_GPS(void)
{
    GPS_LineControlReg = 0b10000000;
    GPS_DivisorLatchLSB = 0x45;
    GPS_DivisorLatchMSB = 0x01;
    GPS_LineControlReg = 0b00110011;
    GPS_FifoControlReg = 0b110;
    GPS_FifoControlReg = 0;
}

/* Checks for data from the GPS
 */
int GPSReadMessage(char *message)
{

    if (!GPSTestForReceivedData())
    {
        return 0;
    }

    // Assemble the bytes into a string
    int i;
    for (i = 0; i < 280; i++)
    {
        unsigned char byte = getcharGPS();

        message[i] = byte;

        // printf("%c", message[i]);
    }

    GPSFlush();
    return 1;
}

void main()
{

    printf("Initializing GPS...\n");
    Init_GPS();
    printf("Done\n");

    GPSFlush();

    printf("Attempting to read from GPS...\n");

    char message[280];

    int i;
    for (i = 0; i < 100; i++) {
        if (GPSReadMessage(message))
        {
            printf("\n%s\n", message);
        }
        else {
            printf("No message available.\n");
        }
    }
    
}