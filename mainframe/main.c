/*
 * Author: Eric Chen, Jaskirat Singh
 * 
 * The main function that runs on DE1's ARM processor
 */

#include <stdio.h>
#include "Graphics.h"
#include "touchscreen.h"
#include "gui.h"

void main() {
    // TODO: initialization: initialize UART, touchscreen, GUI, etc.
    Init_Touch();
    int i;
    for (i=0; i<64; i++) {
        ProgramPalette(i, ColourPalletteData[i]);
    }
    FillScreen(BLACK);

    while (1) {
        // TODO: state HOME - display the welcome screen

        // TODO: state DISPLAY_INSTRUCTION - display the game instruction

        // TODO: state SETUP - set up phase of the game

        // TODO: state PLAY_TURN - player's turn

        // TODO: state DEALER_TURN - dealer's turn

        // TODO: state PLAYER_WIN - player has won; allow user to play again, or send result, or go to home screen

        // TODO: state DEALER_WIN - dealer has won; allow user to play again, or send result, or go to home screen

        // TODO: state TIE - tie; allow user to play again, or send result, or go to home screen

        // TODO: state SEND_RESULT - allows user to clear all digits, or confirm sending, or go to home screen
        int phone_num[10];
        int phone_num_entry_cursor_pos = 0;
        while (1) {
            RenderEnterPhoneNumberScreen(phone_num, phone_num_entry_cursor_pos);
            int response = GetPhoneNumberScreenResponse();
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
                break;
            }
            /* if "clear" is pressed */
            else if (response==CLEAR_PRESSED) {
                phone_num_entry_cursor_pos = 0;
            }
            /* if "confirm" is pressed */
            else if (response==CONFIRM_PRESSED) {
                SendResponseToPhone(phone_num);
                break;  // NOTE: for now, just go straight back to home screen
            }
            /* a "null" press */
            else {}
        }
    }

    return;
}