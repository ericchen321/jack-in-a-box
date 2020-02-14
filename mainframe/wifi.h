#ifndef WIFI_H_
#define WIFI_H_
#endif

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