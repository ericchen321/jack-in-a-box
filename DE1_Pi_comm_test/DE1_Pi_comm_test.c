#include "../mainframe/pi.h"

void square_wave(void) {
    int i;
    while(1) {
        PI_SINGLEOUT = 0x01;
        for (i=0;i<2;i++) {
            printf("high...\n");
        }
        PI_SINGLEOUT = 0x00;
        for (i=0;i<2;i++) {
            printf("low...\n");
        }
    }
}

void main() {
    int card_val;
    
    /* test successive card dealing */
    int i;
    for (i=0; i<5; i++) {
        if (i%2==0) {
            card_val = DealCard(PI_DEAL_TO_DEALER);
        }
        else {
            card_val = DealCard(PI_DEAL_TO_PLAYER);
        }
        printf("iteration: %d, card: %d\n", i, card_val);
    }
}