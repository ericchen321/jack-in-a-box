/*
 * Author: Eric Chen
 * 
 * stuff that handle communication with Raspberry Pi
 */

#ifndef PI_H_
#define PI_H_

/* ports */
#define PI_SINGLEIN (*(volatile unsigned char *)(0xFF200070))
#define PI_SINGLEOUT (*(volatile unsigned char *)(0xFF200060))
#define PI_SIXIN (*(volatile unsigned char *)(0xFF200080))
#define PI_DEALER_OR_PLAYER_OUT (*(volatile unsigned char *)(0xFF200090))

/* flags to DealCard */
#define PI_DEAL_TO_PLAYER 0x00
#define PI_DEAL_TO_DEALER 0x01

/* issue a deal-card command to the Pi;
 * given flag represents to whom the card
 * is dealt;
 * read and return the card's face value;
 * A - 1, J, Q, K are 11-13
 */
int DealCard(char flag);

#endif /* PI_H_ */