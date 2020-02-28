/*
 * Author: Eric Chen
 * 
 * unit tests for critical functions under mainframe/
 */

#include "../mainframe/gameLogic.h"
#include "../mainframe/pi.h"
#include "../mainframe/wifi.h"
#include <stdio.h>

/* player: A5A - 17
 * dealer: Q7 - 17
 */
void test_ScoreCalculation_tie_0(void) {
    player_card_num = 3;
    dealer_card_num = 2;
    player_cards[0] = 'A';
    player_cards[1] = '5';
    player_cards[2] = 'A';
    dealer_cards[0] = 'Q';
    dealer_cards[1] = '7';
    ScoreCalculation(PLAYER_SCORE);
    ScoreCalculation(DEALER_SCORE);
    if(player_hand==17 && dealer_hand==17){
        printf("test_ScoreCalculation_tie_0 is working.\n");
    }
    else{
        printf("test_ScoreCalculation_tie_0 is not working.\n");
        printf("Player hand should be: 17, but is: %d\n", player_hand);
        printf("Dealer hand should be: 17, but is: %d\n", dealer_hand);
    }
}

/* player: AA6J3 - 21
 * dealer: 5AA4 - 21
 */
void test_ScoreCalculation_tie_1(void) {
    player_card_num = 5;
    dealer_card_num = 4;
    player_cards[0] = 'A';
    player_cards[1] = 'A';
    player_cards[2] = '6';
    player_cards[3] = 'J';
    player_cards[4] = '3';
    dealer_cards[0] = '5';
    dealer_cards[1] = 'A';
    dealer_cards[2] = 'A';
    dealer_cards[3] = '4';
    ScoreCalculation(PLAYER_SCORE);
    ScoreCalculation(DEALER_SCORE);
    if(player_hand==21 && dealer_hand==21){
        printf("test_ScoreCalculation_tie_1 is working.\n");
    }
    else{
        printf("test_ScoreCalculation_tie_1 is not working.\n");
        printf("Player hand should be: 21, but is: %d\n", player_hand);
        printf("Dealer hand should be: 21, but is: %d\n", dealer_hand);
    }
}

/* player: 567 - 18
 * dealer: 746 - 17
 */
void test_ScoreCalculation_player_win_0(void) {
    player_card_num = 3;
    dealer_card_num = 3;
    player_cards[0] = '5';
    player_cards[1] = '6';
    player_cards[2] = '7';
    dealer_cards[0] = '7';
    dealer_cards[1] = '4';
    dealer_cards[2] = '6';
    ScoreCalculation(PLAYER_SCORE);
    ScoreCalculation(DEALER_SCORE);
    if(player_hand==18 && dealer_hand==17){
        printf("test_ScoreCalculation_player_win_0 is working.\n");
    }
    else{
        printf("test_ScoreCalculation__player_win_0 is not working.\n");
        printf("Player hand should be: 18, but is: %d\n", player_hand);
        printf("Dealer hand should be: 17, but is: %d\n", dealer_hand);
    }
}

/* player: 524 - 11
 * dealer: 6JJ - 26
 */
void test_ScoreCalculation_player_win_1(void) {
    player_card_num = 3;
    dealer_card_num = 3;
    player_cards[0] = '5';
    player_cards[1] = '2';
    player_cards[2] = '4';
    dealer_cards[0] = '6';
    dealer_cards[1] = 'J';
    dealer_cards[2] = 'J';
    ScoreCalculation(PLAYER_SCORE);
    ScoreCalculation(DEALER_SCORE);
    if(player_hand==11 && dealer_hand==26){
        printf("test_ScoreCalculation_player_win_1 is working.\n");
    }
    else{
        printf("test_ScoreCalculation__player_win_1 is not working.\n");
        printf("Player hand should be: 11, but is: %d\n", player_hand);
        printf("Dealer hand should be: 17, but is: %d\n", dealer_hand);
    }
}

/* player: QQ2 - 22
 * dealer: 3 - 3
 */
void test_ScoreCalculation_player_lose_0(void) {
    player_card_num = 3;
    dealer_card_num = 1;
    player_cards[0] = 'Q';
    player_cards[1] = 'Q';
    player_cards[2] = '2';
    dealer_cards[0] = '3';
    ScoreCalculation(PLAYER_SCORE);
    ScoreCalculation(DEALER_SCORE);
    if(player_hand==22 && dealer_hand==3){
        printf("test_ScoreCalculation_player_lose_0 is working.\n");
    }
    else{
        printf("test_ScoreCalculation__player__lose_0 is not working.\n");
        printf("Player hand should be: 22, but is: %d\n", player_hand);
        printf("Dealer hand should be: 3, but is: %d\n", dealer_hand);
    }
}

/* player: K5 - 15
 * dealer: K36 - 19
 */
void test_ScoreCalculation_player_lose_1(void) {
    player_card_num = 2;
    dealer_card_num = 3;
    player_cards[0] = 'K';
    player_cards[1] = '5';
    dealer_cards[0] = 'K';
    dealer_cards[1] = '3';
    dealer_cards[2] = '6';
    ScoreCalculation(PLAYER_SCORE);
    ScoreCalculation(DEALER_SCORE);
    if(player_hand==15 && dealer_hand==19){
        printf("test_ScoreCalculation_player_lose_1 is working.\n");
    }
    else{
        printf("test_ScoreCalculation__player__lose_1 is not working.\n");
        printf("Player hand should be: 15, but is: %d\n", player_hand);
        printf("Dealer hand should be: 19, but is: %d\n", dealer_hand);
    }
}

void test_ScoreCalculation(void) {
    // TODO:
    test_ScoreCalculation_tie_0();
    test_ScoreCalculation_tie_1();
    test_ScoreCalculation_player_win_0();
    test_ScoreCalculation_player_win_1();
    test_ScoreCalculation_player_lose_0();
    test_ScoreCalculation_player_lose_1();
    return;
}

void main() {
    test_ScoreCalculation();
}



