/*
 * Author: Eric Chen, Jaskirat Singh
 * 
 * stuff that handle high-level gameplay mechanics
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

/* for mock tests without actual motor & image rec */
//#define MOCK

// TODO: should change them to 0
#ifdef MOCK
    #define PLAYER_CARDS_INIT "AA9"
    #define DEALER_CARDS_INIT "QA"
#else
    #define PLAYER_CARDS_INIT ""
    #define DEALER_CARDS_INIT ""
#endif

#define WIN 0   // player win
#define LOSE 1  // player lose
#define TIE 2
#define PLAYER_SCORE 0
#define DEALER_SCORE 1

/* data structures */
extern int player_hand;//stores the players hand value, set by ScoreCalculation()
extern int dealer_hand;//stores the dealers hand value, set by ScoreCalculation()
extern char player_cards[10];//stores the players cards as ranks/A/J/Q/K
extern char dealer_cards[10];//stores the dealers cards as ranks/A/J/Q/K
extern int player_card_num;//stores the number of card being dealt to player
extern int dealer_card_num;//stores the number of card being dealt to dealer

/* deal one card to the player. Modify
 * player_cards[] and player_card_num
 * upon return
 */
void DealCardToPlayer(void);

/* deal one card to the dealer. Modify
 * dealer_cards[] and dealer_card_num
 * upon return
 */
void DealCardToDealer(void);

/* calculate score from cards. flag can
 * be PLAYER_SCORE or DEALER_SCORE. Modify
 * player_hand or dealer_hand depending on
 * flag
 */
void ScoreCalculation(int flag);

/* send win/lose to the given phone number;
 * requires result being WIN, LOSE, or TIE
 * requires a valid 10-digit phone number
 */
void SendResponseToPhone(int result, int* phone_num);

#endif /* GAMELOGIC_H_ */