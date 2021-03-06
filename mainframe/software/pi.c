//----------------------------------------------------------------------------------------------
//Funcitons by Jaskirat and Eric
//----------------------------------------------------------------------------------------------

#include "pi.h"

int DealCard(char flag) {
    int card_val;

    // wait for Pi to get ready
    while (PI_SINGLEIN == 0x01) {
        printf("waiting for Pi to get ready\n");
    }
    printf("Pi is ready\n");

    // set deal flag
    PI_DEALER_OR_PLAYER_OUT = flag;
    int i;
    for (i=0; i<2; i++) {
        printf("set dealer/player flag, poll a bit...\n");
    }

    // issue read
    PI_SINGLEOUT = 0x01;
    for (i=0; i<2; i++) {
        printf("issued DEAL command, poll a bit...\n");
    }

    // wait for Pi to acknowledge
    while (PI_SINGLEIN == 0x00) {
        printf("waiting for Pi to ack\n");  // delay
    }
    printf("Pi acked\n");

    // read in the card value
    card_val = PI_SIXIN & 0x3F;

    // acknowledge back
    PI_SINGLEOUT = 0x00;
    for (i=0; i<2; i++) {
        printf("acknowledged back, poll a bit...\n");
    }

    return card_val;
}