/*
 * Author: Eric Chen, Jaskirat Singh, Paul Davies
 * 
 * stuff that handle high-level gameplay mechanics
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

// TODO: should change them to 0
#define PLAYER_HAND_INIT 10
#define DEALER_HAND_INIT 5

/* data structures */
extern int player_hand;
extern int dealer_hand;

/* deal one card to the player. Modify
 * player_hand upon return
 */
void DealCardToPlayer(void);

/* deal one card to the dealer. Modify
 * dealer_hand upon return
 */
void DealCardToDealer(void);

#endif /* GAMELOGIC_H_ */