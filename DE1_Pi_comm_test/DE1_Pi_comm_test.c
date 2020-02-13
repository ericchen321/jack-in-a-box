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
    for (i=0; i<10; i++) {
        card_val = DealCard();
        printf("iteration: %d, card: %d\n", i, card_val);
    }
}