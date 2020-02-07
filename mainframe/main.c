/*
 * Author: Eric Chen, Jaskirat Singh
 * 
 * The main function that runs on DE1's ARM processor
 */

#include <stdio.h>
#include "Graphics.h"
#include "touchscreen.h"
#include "gui.h"

/* the old main function
void main() {
    // TODO: initialization: initialize UART, touchscreen, GUI, etc.
    Init_Touch();
    int i;
    for (i=0; i<64; i++) {
        ProgramPalette(i, ColourPalletteData[i]);
    }
    FillScreen(BLACK);

    int response;
    int result = WIN;
    int nextScreen = RESULT_SCREEN;
    int phone_num[10];
    int phone_num_entry_cursor_pos = 0;
    while (1) {
        // TODO: state PLAYER_WIN - player has won; allow user to play again, or send result, or go to home screen
        if (nextScreen == RESULT_SCREEN) {
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
            if (result == MAIN_MENU_PRESSED) {
                nextScreen = HOME_SCREEN;
            }
            else if (response == START_AGAIN_PRESSED) {
                // TODO:
            }
            else if (response == SEND_RESULT_TO_PHONE_PRESSED) {
                // TODO:
                nextScreen = SEND_RESULT_SCREEN;
            }
            else {} // still display the result screen
        }

        // TODO: state SEND_RESULT - allows user to clear all digits, or confirm sending, or go to home screen
        if (nextScreen == SEND_RESULT_SCREEN) {
            RenderEnterPhoneNumberScreen(phone_num, phone_num_entry_cursor_pos);
            response = GetPhoneNumberScreenResponse();
            /* if a number is pressed 
            if (response>=0 && response<=9) {
                /* legal phonepad entry 
                if (phone_num_entry_cursor_pos<10) {
                    phone_num[phone_num_entry_cursor_pos] = response;
                    phone_num_entry_cursor_pos += 1;
                }
                /* illegal entry 
                else {
                    printf("illegal entry detected; phone pad entry not registered!\n");
                }
            }
            /* if "main menu" is pressed 
            else if (response==MAIN_MENU_PRESSED) {
                phone_num_entry_cursor_pos = 0;
                nextScreen = HOME_SCREEN;
            }
            /* if "clear" is pressed 
            else if (response==CLEAR_PRESSED) {
                phone_num_entry_cursor_pos = 0;
            }
            /* if "confirm" is pressed 
            else if (response==CONFIRM_PRESSED) {
                SendResponseToPhone(phone_num);
                phone_num_entry_cursor_pos = 0;
                nextScreen = HOME_SCREEN;
            }
            /* a "null" press 
            else {}
        }
    }

    return;
}
*/

void main() {
    // TODO: initialization: initialize UART, touchscreen, GUI, etc.
    Init_Touch();
    int i;
    for (i=0; i<64; i++) {
        ProgramPalette(i, ColourPalletteData[i]);
    }
    FillScreen(BLACK);

    homeScreen();
    return;
}