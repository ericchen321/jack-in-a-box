/*
 * Author: Eric Chen, Jaskirat Singh
 * 
 * The main function that runs on DE1's ARM processor
 */

#include <stdio.h>
#include "Graphics.h"
#include "touchscreen.h"
#include "gui.h"
#include "gameLogic.h"

void main() {
    // TODO: initialization: initialize UART, touchscreen, GUI, game state variables, etc.
    Init_Touch();
    int i;
    for (i=0; i<64; i++) {
        ProgramPalette(i, ColourPalletteData[i]);
    }
    FillScreen(BLACK);
    int response;
    int result;
    int nextScreen = HOME_SCREEN;
    int phone_num[10];
    int phone_num_entry_cursor_pos = 0;

    // entry point to the game
    while (1) {
        // state WELCOME - home screen
        if (nextScreen == HOME_SCREEN) {
            player_hand = PLAYER_HAND_INIT;
            dealer_hand = DEALER_HAND_INIT;
            RenderHomeScreen();
            response = GetHomeScreenResponse();
            if (response == READ_MANUAL_PRESSED) {
                nextScreen = MANUAL_SCREEN_0;
            }
            else if(response == PLAY_PRESSED) {
                nextScreen = SETUP_PLAYER_1ST_SCREEN;
            }
            else {}
        }

        // state MANUAL_0 - display manual page 1
        else if (nextScreen == MANUAL_SCREEN_0) {
            RenderManualScreen0();
            response = GetManualScreen0Response();
            if (response == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == FORWARD_PRESSED) {
                nextScreen = MANUAL_SCREEN_1;
            }
            else {}
        }

        // state MANUAL_1 - display manual page 2
        else if (nextScreen == MANUAL_SCREEN_1) {
            RenderManualScreen1();
            response = GetManualScreen1Response();
            if (response == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == FORWARD_PRESSED) {
                nextScreen = MANUAL_SCREEN_2;
            }
            else if (response == BACK_PRESSED) {
                nextScreen = MANUAL_SCREEN_0;
            }
            else {}
        }

        // state MANUAL_2 - display manual page 3
        else if (nextScreen == MANUAL_SCREEN_2) {
            RenderManualScreen2();
            response = GetManualScreen2Response();
            if (response == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == FORWARD_PRESSED) {
                nextScreen = MANUAL_SCREEN_3;
            }
            else if (response == BACK_PRESSED) {
                nextScreen = MANUAL_SCREEN_1;
            }
            else {}
        }

        // state MANUAL_3 - display manual page 4
        else if (nextScreen == MANUAL_SCREEN_3) {
            RenderManualScreen3();
            response = GetManualScreen3Response();
            if (response == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == BACK_PRESSED) {
                nextScreen = MANUAL_SCREEN_2;
            }
            else {}
        }

        // state SETUP_PLAYER_1ST - deal player's 1st card during setup
        else if (nextScreen == SETUP_PLAYER_1ST_SCREEN) {
            RenderSetupScreenDuringDealing(DEALING_PLAYER);
            DealCardToPlayer();
            nextScreen = SETUP_DEALER_SCREEN;
        }

        // state SETUP_DEALER - deal a card to dealer during setup
        else if (nextScreen == SETUP_DEALER_SCREEN) {
            RenderSetupScreenDuringDealing(DEALING_DEALER);
            DealCardToDealer();
            nextScreen = SETUP_PLAYER_2ND_SCREEN;
        }

        // state SETUP_PLAYER_2ND - deal player's 2nd card during setup
        else if (nextScreen == SETUP_PLAYER_2ND_SCREEN) {
            RenderSetupScreenDuringDealing(DEALING_PLAYER);
            DealCardToPlayer();
            nextScreen = SETUP_WAIT_PLAYER_RESPOND;
        }

        else if (nextScreen == SETUP_WAIT_PLAYER_RESPOND) {
            RenderSetupScreenAfterDealing();
            response = GetSetupScreenResponse();
            if (response == MAIN_MENU_PRESSED) {
                player_hand = PLAYER_HAND_INIT;
                dealer_hand = DEALER_HAND_INIT;
                nextScreen = HOME_SCREEN;
            }
            else if (response == CONTINUE_PRESSED) {
                if (player_hand == 21) {
                    nextScreen = DEALER_TURN_SCREEN;
                }
                else {
                    nextScreen = PLAYER_TURN_SCREEN;
                }
            }
            else {}
        }

        // state PLAYER_TURN - interactive screen allowing user to hit/stand
        else if (nextScreen == PLAYER_TURN_SCREEN) {
            RenderPlayerTurnScreenBeforeDealing();
            response = GetPlayerTurnScreenResponse();
            if (response == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == PLAYER_HIT_ME) {
                RenderPlayerTurnScreenDuringDealing();
                DealCardToPlayer();
            }
            else if (response == PLAYER_STAND) {
                nextScreen = DEALER_TURN_SCREEN;
            }
            else {}
        }

        // state DEALER_TURN - deal cards to the dealer and produce result
        else if (nextScreen == DEALER_TURN_SCREEN) {
            if (player_hand > 21) {
                result = LOSE;
                nextScreen = RESULT_SCREEN;
            }
            else if (dealer_hand < 17) {
                RenderDealerTurnScreen();
                DealCardToDealer();
            }
            else if (dealer_hand >=17 && dealer_hand <= 21) {
                if (player_hand > dealer_hand)
                    result = WIN;
                else if (player_hand == dealer_hand)
                    result = TIE;
                else
                    result = LOSE;
                nextScreen = RESULT_SCREEN;
            }
            else {
                result = WIN;
                nextScreen = RESULT_SCREEN;
            }
        }

        // state SHOW_RESULT - allow user to play again, or send result, or go to home screen
        else if (nextScreen == RESULT_SCREEN) {
            if (result == WIN) {
                RenderResultScreen(WIN);
            }
            else if (result == LOSE) {
                RenderResultScreen(LOSE);
            }
            else {
                RenderResultScreen(TIE);
            }
            response = GetResultScreenResponse();
            if (response == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == START_AGAIN_PRESSED) {
                player_hand = PLAYER_HAND_INIT;
                dealer_hand = DEALER_HAND_INIT;
                nextScreen = SETUP_PLAYER_1ST_SCREEN;
            }
            else if (response == SEND_RESULT_TO_PHONE_PRESSED) {
                nextScreen = SEND_RESULT_SCREEN;
            }
            else {} // no button pressed
        }

        // state SEND_RESULT - allows user to clear all digits, or confirm sending, or go to home screen
        else if (nextScreen == SEND_RESULT_SCREEN) {
            RenderEnterPhoneNumberScreen(phone_num, phone_num_entry_cursor_pos);
            response = GetPhoneNumberScreenResponse();
            /* if a number is pressed */
            if (response>=0 && response<=9) {
                /* legal phonepad entry */
                if (phone_num_entry_cursor_pos<10) {
                    phone_num[phone_num_entry_cursor_pos] = response;
                    phone_num_entry_cursor_pos += 1;
                }
                /* illegal entry */
                else {
                    printf("illegal entry detected; phone pad entry not registered!\n");
                }
            }
            /* if "main menu" is pressed */
            else if (response==MAIN_MENU_PRESSED) {
                phone_num_entry_cursor_pos = 0;
                nextScreen = HOME_SCREEN;
            }
            /* if "clear" is pressed */
            else if (response==CLEAR_PRESSED) {
                phone_num_entry_cursor_pos = 0;
            }
            /* if "confirm" is pressed */
            else if (response==CONFIRM_PRESSED) {
                if (phone_num_entry_cursor_pos == 10) {
                    SendResponseToPhone(phone_num);
                    phone_num_entry_cursor_pos = 0;
                    nextScreen = HOME_SCREEN;
                }
                else {
                    phone_num_entry_cursor_pos = 0;
                    nextScreen = ILLEGAL_PHONE_NUM_SCREEN;
                }
            }
            /* no button pressed */
            else {}
        }

        // state ILLEGAL_PHONE_NUM - entered when after "confirm", phone number less than 10 digits
        else if (nextScreen == ILLEGAL_PHONE_NUM_SCREEN) {
            RenderIllegalPhoneNumScreen();
            response = GetIllegalPhoneNumScreenResponse();
            if (response == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == OK_PRESSED) {
                nextScreen = SEND_RESULT_SCREEN;
            }
            else {}
        }
    }

    return;
}