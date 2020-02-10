//----------------------------------------------------------------------------------------------
//Funcitons by Jaskirat and Eric
//----------------------------------------------------------------------------------------------

#include "pi.h"

char DealCard(void) {
    char card_val;

    // wait for Pi to get ready
    while (PI_SINGLEIN == 0x01);    

    // issue read
    PI_SINGLEOUT = 0x01;

    // wait for Pi to acknowledge
    while (PI_SINGLEIN == 0x00) {
        printf("waiting for Pi to ack\n");  // delay
    }

    // read in the card value
    card_val = PI_SIXIN & 0x3F;

    // acknowledge back
    PI_SINGLEOUT = 0x00;

    return card_val;
}