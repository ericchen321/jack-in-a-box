#include <stdio.h>
#include <string.h>
#include <time.h>
#include "wifi.h"

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
// void main(){
//     Init_Wifi();
//     putenters();
    
//     putstringWifi( "dofile(\"si.lua\")");
//     putstringWifi( "dofile(\"si.lua\")");

//     volatile char gotChar = getcharWifi();
//     printf("We got char %c\n",gotChar);
//     WifiFlush();


//     while(1){}
// }

