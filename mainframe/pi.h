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

/* issue a deal-card command to the Pi.
 * read and return the card's face value;
 * A - 1, J, Q, K are 11-13
 */
int DealCard(void);

#endif /* PI_H_ */