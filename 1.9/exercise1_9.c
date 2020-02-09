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
/* definitions for Wifi
 */
#define Wifi_Offset                      (volatile unsigned char *)(0x00000040) // from the RS232 port
#define Wifi_ReceiverFifo                (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_ReceiverFifo))
#define Wifi_TransmitterFifo             (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_TransmitterFifo))   
#define Wifi_InterruptEnableReg          (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_InterruptEnableReg))
#define Wifi_InterruptIdentificationReg  (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_InterruptIdentificationReg))
#define Wifi_FifoControlReg              (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_FifoControlReg))
#define Wifi_LineControlReg              (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_LineControlReg))
#define Wifi_ModemControlReg             (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_ModemControlReg))
#define Wifi_LineStatusReg               (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_LineStatusReg))
#define Wifi_ModemStatusReg              (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_ModemStatusReg))
#define Wifi_ScratchReg                  (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_ScratchReg))
#define Wifi_DivisorLatchLSB             (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_DivisorLatchLSB))
#define Wifi_DivisorLatchMSB             (*(volatile unsigned char *)((int)Wifi_Offset + (int)&RS232_DivisorLatchMSB))
#include <stdio.h>
#include <string.h>
#include <time.h>
void Init_Wifi(void) { 
    int divisor = (int)((50E6)/(115200 * 16)  );
    Wifi_LineControlReg = 0b10000000;
    Wifi_DivisorLatchLSB = divisor & 0b11111111;
    Wifi_DivisorLatchMSB = (divisor >> 8) & 0b11111111;
    Wifi_LineControlReg = 0b00110011;
    Wifi_FifoControlReg = 0b110;
    Wifi_FifoControlReg = 0;
} 
int putcharWifi(int c) {   
    while( ((Wifi_LineStatusReg >> 5) & 1) == 0){}
    Wifi_TransmitterFifo = c;
    return c;
} 
void putstringWifi(char* string){
    int i;
    for(i = 0; i < strlen(string); i++){
        putcharWifi(string[i]);
    }
    putcharWifi('\r');
    putcharWifi('\n');
}
void WifiFlush(void) { 
    volatile int dummy = 0;
    while(Wifi_LineStatusReg & 1) {
        dummy += Wifi_ReceiverFifo;
    }
    return;   
}
int getcharWifi( void ) {  
    while ((Wifi_LineStatusReg & 1) == 0){}
    return Wifi_ReceiverFifo;
} 
 
int WifiTestForReceivedData(void) { 
    return (Wifi_LineStatusReg & 1);
} 
void putenters(){
    putcharWifi('\r');
    putcharWifi('\n');
} 
void getstringWifi(volatile char* buff){
    buff[0] = getcharWifi();
    volatile int i = 1;
    while ((Wifi_LineStatusReg & 1)){
        buff[i] = Wifi_ReceiverFifo;
        i++;
        }
    buff[i] = '\0';
}
volatile char buff1[1024];
volatile char buff2[1024];
void main(){
    Init_Wifi();
    putenters();
    
    putstringWifi( "dofile(\"si.lua\")");

    volatile char gotChar = getcharWifi();
    printf("We got char %c\n",gotChar);
    WifiFlush();


    while(1){}
}

