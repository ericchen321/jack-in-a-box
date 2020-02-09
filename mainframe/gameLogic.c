//----------------------------------------------------------------------------------------------
//Funcitons by Eric and Jaskirat
//----------------------------------------------------------------------------------------------

#include "gameLogic.h"

player_hand = PLAYER_HAND_INIT;
dealer_hand = DEALER_HAND_INIT;

void DealCardToPlayer(void) {
    /* NOTE: set to some dummy values for testing */
    player_hand += 2;

    /* NOTE: for now just poll a bit to mock the dealing & recognizing process */
    int i;
    for (i=0; i<50; i++) {
        printf("dealing a card to player... player score is %d\n", player_hand);
    }

    /* TODO: actual card dealing & recognition */
    return;
}

void DealCardToDealer(void) {
    /* NOTE: set to some dummy values for testing */
    dealer_hand += 4;

    /* NOTE: for now just poll a bit to mock the dealing & recognizing process */
    int i;
    for (i=0; i<50; i++) {
        printf("dealing a card to dealer... dealer score is %d\n", dealer_hand);
    }

    /* TODO: actual card dealing & recognition */
    return;
}