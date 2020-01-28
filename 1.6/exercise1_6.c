#include <stdio.h>

#define RS232_ReceiverFifo         (*(volatile unsigned char *)(0xFF210200)) 
#define RS232_TransmitterFifo      (*(volatile unsigned char *)(0xFF210200)) 
#define RS232_InterruptEnableReg   (*(volatile unsigned char *)(0xFF210202))
#define RS232_InterruptIdentificationReg         (*(volatile unsigned char *)(0xFF210204)) 
#define RS232_FifoControlReg                     (*(volatile unsigned char *)(0xFF210204)) 
#define RS232_LineControlReg                     (*(volatile unsigned char *)(0xFF210206)) 
#define RS232_ModemControlReg                    (*(volatile unsigned char *)(0xFF210208)) 
#define RS232_LineStatusReg                      (*(volatile unsigned char *)(0xFF21020A)) 
#define RS232_ModemStatusReg                     (*(volatile unsigned char *)(0xFF21020C)) 
#define RS232_ScratchReg                         (*(volatile unsigned char *)(0xFF21020E)) 
#define RS232_DivisorLatchLSB                    (*(volatile unsigned char *)(0xFF210200)) 
#define RS232_DivisorLatchMSB                    (*(volatile unsigned char *)(0xFF210202)) 

#define Bluetooth_Offset                        (volatile unsigned char *)(0x00000020)
#define Bluetooth_ReceiverFifo                  (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_ReceiverFifo))
#define Bluetooth_TransmitterFifo               (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_TransmitterFifo))
#define Bluetooth_InterruptEnableReg            (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_InterruptEnableReg))
#define Bluetooth_InterruptIdentificationReg    (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_InterruptIdentificationReg))
#define Bluetooth_FifoControlReg                (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_FifoControlReg))
#define Bluetooth_LineControlReg                (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_LineControlReg))
#define Bluetooth_ModemControlReg               (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_ModemControlReg))
#define Bluetooth_LineStatusReg                 (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_LineStatusReg))
#define Bluetooth_ModemStatusReg                (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_ModemStatusReg))
#define Bluetooth_ScratchReg                    (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_ScratchReg))
#define Bluetooth_DivisorLatchLSB               (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_DivisorLatchLSB))
#define Bluetooth_DivisorLatchMSB               (*(volatile unsigned char *)((int)Bluetooth_Offset + (int)&RS232_DivisorLatchMSB))


void BTOutMessage (char * Message){
    int i;
    for(i = 0; Message[i] != '\0'; i++) { putcharBT(Message[i]);}
}
void BT_Flush (void)
{
    volatile int temp = 0;
    while(Bluetooth_LineStatusReg & 1) {temp = Bluetooth_ReceiverFifo;}
    return;
}

//#include <io.h>
void BTFactoryReset (void)
{
    // wait for 1 second between command
    // enter these commands in upper case
    // $$$ enter command mode
    // SF,1 factory reset
    // SN,Device1 set device name to “Device1”
    // SP,1234 set 4 digit pin to “1234”
    // R,1<CR> reboot BT controller

    char c, Message[100] ;
    int i;
    char temp[20];
    
    while(1) {
 
        printf("\r\nEnter Message for Bluetooth Controller: ") ;
        gets(Message); // get command string from user keyboard
        gets(temp);
        BTOutMessage(Message) ; // write string to BT device

        // if the command string was NOT "$$$" send \r\n
        if(strcmp(Message, "$$$") != 0) { // $$$ puts BT module into command mode
            putcharBT('\r') ;
            putcharBT('\n') ;
        }
      
        // now read back acknowledge string from device and display on console,
        // will timeout after no communication for about 2 seconds
        for(i = 0; i < 2000000; i ++) {
            if(testBT() == 1) {
                c = getcharBT();
                putchar(c);
            }
        }
    }
}

int testBT (void)
{
    if((Bluetooth_LineStatusReg & 1)){
        return 1;
    }
    return 0;
}

void Init_BT (void)
{
    Bluetooth_LineControlReg = 0b10000000;
    int divisor = (int) ((50E6)/(115200 *16));
    Bluetooth_DivisorLatchLSB = divisor & 0b11111111;
    Bluetooth_DivisorLatchMSB = (divisor >> 8) & 0b11111111;

    Bluetooth_LineControlReg = 0b00110011;
    Bluetooth_FifoControlReg = 0b110;
    Bluetooth_FifoControlReg = 0;
}

int putcharBT (int  c)
{
    while( ((Bluetooth_LineStatusReg >> 5) & 1) == 0){}
    Bluetooth_TransmitterFifo = c;
    return c;
}

int getcharBT (void)
{
    // wait for Data Ready bit (0) of line status register to be '1'
    while ( (Bluetooth_LineStatusReg & 1) == 0){}

    // read new character from ReceiverFiFo register
    return Bluetooth_ReceiverFifo;
}

// the following function polls the UART to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read from the FIFO
int BT_TestForReceivedData (void)
{
    // if Bluetooth LineStatusReg bit 0 is set to 1
    return (Bluetooth_LineStatusReg & 1);
}

void main(){
    Init_BT();
    BTFactoryReset();
}