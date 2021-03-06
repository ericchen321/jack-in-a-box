//----------------------------------------------------------------------------------------------
//Funcitons by Eric and Jaskirat
//----------------------------------------------------------------------------------------------

#include "gameLogic.h"
#include "pi.h"
#include "wifi.h"
#include <string.h>

char player_cards[10] = PLAYER_CARDS_INIT;
char dealer_cards[10] = DEALER_CARDS_INIT;
int player_hand, dealer_hand;
int player_card_num = 0;
int dealer_card_num = 0;

void DealCardToPlayer(void) {
#ifdef MOCK
    int i;
    for (i=0; i<10; i++) {
        printf("mock dealing card to player...\n");
    }
#else
    /* actual card dealing & recognition */
    int card_face_val = DealCard(PI_DEAL_TO_PLAYER);
    switch (card_face_val)
    {
        case (1):
            player_cards[player_card_num] = 'A';
            break;
        case (10):
            player_cards[player_card_num] = 'T';
            break;
        case (11):
            player_cards[player_card_num] = 'J';
            break;
        case (12):
            player_cards[player_card_num] = 'Q';
            break;
        case (13):
            player_cards[player_card_num] = 'K';
            break;
        default:
            player_cards[player_card_num] = (char)card_face_val + 0x30;
            break;
    }
#endif
    player_card_num += 1;
    return;
}

void ScoreCalculation(int flag) {
    int i;
    int temp_player[10];
    int temp_dealer[10];
    int ace_player=0;
    int ace_dealer=0;
    for (i=0; i<player_card_num; i++){
        if(player_cards[i]=='2')
            temp_player[i]=2;
        else if (player_cards[i]=='3')
            temp_player[i]=3;
        else if (player_cards[i]=='4')
            temp_player[i]=4;
        else if (player_cards[i]=='5')
            temp_player[i]=5;
        else if (player_cards[i]=='6')
            temp_player[i]=6;
        else if (player_cards[i]=='7')
            temp_player[i]=7;
        else if (player_cards[i]=='8')
            temp_player[i]=8;
        else if (player_cards[i]=='9')
            temp_player[i]=9;
        else if (player_cards[i]=='J')
            temp_player[i]=10;
        else if (player_cards[i]=='K')
            temp_player[i]=10;
        else if (player_cards[i]=='Q')
            temp_player[i]=10;
        else if (player_cards[i]=='T')
            temp_player[i]=10;
        else{
            temp_player[i]=1;
            ace_player++;
        }
    }
    for (i=0; i<dealer_card_num; i++){
        if(dealer_cards[i]=='2')
            temp_dealer[i]=2;
        else if (dealer_cards[i]=='3')
            temp_dealer[i]=3;
        else if (dealer_cards[i]=='4')
            temp_dealer[i]=4;
        else if (dealer_cards[i]=='5')
            temp_dealer[i]=5;
        else if (dealer_cards[i]=='6')
            temp_dealer[i]=6;
        else if (dealer_cards[i]=='7')
            temp_dealer[i]=7;
        else if (dealer_cards[i]=='8')
            temp_dealer[i]=8;
        else if (dealer_cards[i]=='9')
            temp_dealer[i]=9;
        else if (dealer_cards[i]=='J')
            temp_dealer[i]=10;
        else if (dealer_cards[i]=='K')
            temp_dealer[i]=10;
        else if (dealer_cards[i]=='Q')
            temp_dealer[i]=10;
        else if (player_cards[i]=='T')
            temp_dealer[i]=10;
        else{
            temp_dealer[i]=1;
            ace_dealer++;
        }
    }
    //printf("outisde both the forloops\n");
    int score_a, score_b;
    if(flag == PLAYER_SCORE){
        score_a = 0;
        score_b = 0;
        for(i=0; i<player_card_num; i++){
            score_a +=temp_player[i];
            //printf("temp_player of %d : %d\n", i, temp_player[i]);
        }
        if(ace_player==0){
            player_hand = score_a;
            //printf("Player score_a: %d\n", score_a);
        }
        else {
            score_b = score_a + 10;
            if(score_b<22){
                player_hand = (score_a > score_b) ? score_a : score_b;
            }
            else 
                player_hand = score_a;
        }
        //printf("Players: %d\n", player_hand);
    }
    else {
        score_a = 0;
        score_b = 0;
        for(i=0; i<dealer_card_num; i++){
            score_a +=temp_dealer[i];
            //printf("temp_dealer of %d : %d\n", i, temp_dealer[i]);
        }   
        if(ace_dealer==0){
            dealer_hand = score_a;
        }
        else {
            score_b = score_a + 10;
            if(score_b<22){
                dealer_hand = (score_a > score_b) ? score_a : score_b;
            }
            else 
                dealer_hand = score_a;
        }
        //printf("Dealers: %d\n", dealer_hand);
    }   
}



void DealCardToDealer(void) {
#ifdef MOCK
    int i;
    for (i=0; i<10; i++) {
        printf("mock dealing card to dealer...\n");
    }
#else
    /* actual card dealing & recognition */
    int card_face_val = DealCard(PI_DEAL_TO_DEALER);
    printf("card's face value: %d\n", card_face_val);
    switch (card_face_val)
    {
        case (1):
            dealer_cards[dealer_card_num] = 'A';
            break;
        case (10):
            dealer_cards[dealer_card_num] = 'T';
            break;
        case (11):
            dealer_cards[dealer_card_num] = 'J';
            break;
        case (12):
            dealer_cards[dealer_card_num] = 'Q';
            break;
        case (13):
            dealer_cards[dealer_card_num] = 'K';
            break;
        default:
            dealer_cards[dealer_card_num] = (char)card_face_val + 0x30;
            break;
    }
#endif
    dealer_card_num += 1;
    return;
}

void SendResponseToPhone(int result, int* phone_num) {
    char string_to_wifi_chip[] = "username, phone_number, game_result = \"ben\", \"+17788469337\", \"w\"";
    
    /* encode the phone number string */
    int i;
    for (i=48; i<58; i++) {
        string_to_wifi_chip[i] = (char)(phone_num[i-48]) + 0x30;
    }

    /* encode the result string */
    if (result == WIN) {
        string_to_wifi_chip[62] = 'w';
    }
    else if (result == LOSE) {
        string_to_wifi_chip[62] = 'l';
    }
    else {
        string_to_wifi_chip[62] = 't';
    }
        
    /* send the result to the chip */
    putstringWifi(string_to_wifi_chip);
    putstringWifi( "dofile(\"send_data_new.lua\")");
    return;
}