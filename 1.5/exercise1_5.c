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

#define HEX0_1 (volatile unsigned char *)(0xff200030)
#define HEX2_3 (volatile unsigned char *)(0xff200040)
#define HEX4_5 (volatile unsigned char *)(0xff200050)

#include <stdio.h>

typedef struct
{
    int hour, minute, second;
} Time;

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

/* 
 * helper for waiting for a message 
 */
void WaitForMessage()
{
    GPSFlush();
    while (!GPSTestForReceivedData())
    {
        printf("\nWaiting for GPS data...\n");
    }
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
void GPSReadMessage(char *message)
{

    // GGA string will be roughly 70 characters so overcompensating a bit
    int length = 100;
    int i;
    for (i = 0; i < length; i++)
    {
        unsigned char byte = getcharGPS();
        message[i] = byte;
    }
    message[length] = '\0';
}

/* 
 * Helper to parse out the GGA string
 */
void ParseGGA(char *message)
{
    int j = 0;
    while (message[j] != '\n')
    {
        j++;
    }
    message[j] = '\0';
}

/* 
 * Helper function get the GGA string
 */
void getGGA(char *message)
{
    // Fetch Message
    GPSReadMessage(message);

    // Parse the string to only grab GGA because that's all we want
    ParseGGA(message);
}

/*
 * Helper function to extra time from GGA string
 */
Time GGAtoTime(char *message) {
    int i = 0;
    while (message[i] != ',') {
        i++;
    }
    i += 1;

    Time t;
    t.hour = ((message[i] - '0') * 10) + (message[i + 1] - '0');
    i += 2;
    
    t.minute = ((message[i] - '0') * 10) + (message[i + 1] - '0');
    i += 2;

    t.second  = ((message[i] - '0') * 10) + (message[i + 1] - '0');
    
    return t;
}

void main()
{

    printf("Initializing GPS...\n");
    Init_GPS();
    printf("Done\n");

    GPSFlush();

    printf("Attempting to read from GPS...\n");

    // Message buffer
    char message[500];

    int i;
    for (i = 0; i < 100; i++)
    {
        Time t;
        getGGA(message);
        printf("%s", message);
        t = GGAtoTime(message);
        printf("\n%d:%d:%d\n", t.hour, t.minute, t.second);
        *HEX0_1 = t.second;
        *HEX2_3 = t.minute;
        *HEX4_5 = t.hour;
        GPSFlush();
    }
}