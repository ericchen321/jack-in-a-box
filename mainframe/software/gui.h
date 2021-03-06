/*
 * Author: Jaskirat Singh, Eric Chen, Paul Davies
 * 
 * GUI stuff to be called from the game logic
 */

#ifndef GUI_H_
#define GUI_H_

/* screens */
#define HOME_SCREEN 0
#define RESULT_SCREEN 1
#define SEND_RESULT_SCREEN 2
#define MANUAL_SCREEN_0 3
#define MANUAL_SCREEN_1 4
#define MANUAL_SCREEN_2 5
#define MANUAL_SCREEN_3 6
#define SETUP_PLAYER_1ST_SCREEN 7
#define SETUP_DEALER_SCREEN 8
#define SETUP_PLAYER_2ND_SCREEN 9
#define SETUP_WAIT_PLAYER_RESPOND_SCREEN 10
#define PLAYER_TURN_SCREEN 11
#define DEALER_TURN_SCREEN 12
#define DEALER_TURN_WAIT_PLAYER_RESPOND_SCREEN 13
#define ILLEGAL_PHONE_NUM_SCREEN 14

/* for the home screen */
#define READ_MANUAL_PRESSED 0
#define PLAY_PRESSED 1

/* for manual pages */
#define FORWARD_PRESSED 0
#define BACK_PRESSED 1

/* for the setup screens and turn screens */
#define DEALING_PLAYER 0
#define DEALING_DEALER 1

/* for the setup screen(s) and dealer's turn screen(s) */
#define CONTINUE_PRESSED 0

/* for player turn screen */
#define PLAYER_HIT_ME 0
#define PLAYER_STAND 1

/* for the phone number entry screen */
#define ENTRY_BOX_UL_X 150
#define ENTRY_BOX_UL_Y 80
#define ENTRY_BOX_WIDTH 500
#define ENTRY_BOX_HEIGHT 25
#define ENTRY_BOX_BORDER_WIDTH 4
#define PHONEPAD_INIT_X 300
#define PHONEPAD_INIT_Y 120
#define PHONEPAD_BUTTON_WIDTH 35
#define PHONEPAD_BUTTON_HEIGHT 45
#define PHONEPAD_BUTTON_BORDER_WIDTH 2
#define PHONEPAD_BUTTON_SEPARATION_X 35
#define PHONEPAD_BUTTON_SEPARATION_Y 25
#define CONFIRM_AND_CLEAR_WIDTH   200
#define CONFIRM_AND_CLEAR_HEIGHT  50
#define CONFIRM_AND_CLEAR_BORDER_WIDTH 2
#define CONFIRM_AND_CLEAR_INIT_Y 400
#define CLEAR_INIT_X 100
#define CONFIRM_INIT_X 500
#define MAIN_MENU_PRESSED 10
#define CLEAR_PRESSED 11
#define CONFIRM_PRESSED 12

/* for the win/lose/tie screen */
#define RESULT_SCREEN_BUTTON_WIDTH   200
#define RESULT_SCREEN_BUTTON_HEIGHT  100
#define RESULT_SCREEN_BUTTON_BORDER_WIDTH 2
#define RESULT_SCREEN_BUTTON_INIT_Y 360
#define START_AGAIN_INIT_X 100
#define SEND_RESULT_INIT_X 500
#define START_AGAIN_PRESSED 0
#define SEND_RESULT_TO_PHONE_PRESSED 1

/* for the illegal phone number entry screen */
# define OK_PRESSED 0

/* render the welcome screen
 */
void RenderHomeScreen(void);

/* get response from the home
 * screen
 */
int GetHomeScreenResponse(void);

/* render the 1st manual screen 
 */
void RenderManualScreen0(void);

/* get response from the 1st manual
 * page
 */
int GetManualScreen0Response(void);

/* render the 2nd manual screen
 */
void RenderManualScreen1(void);

/* get respones from the 2nd manual
 * page
 */
int GetManualScreen1Response(void);

/* render the 3rd manual screen
 */
void RenderManualScreen2(void);

/* get response from the 3rd manual
 * page
 */
int GetManualScreen2Response(void);

/* render the 4th manual screen
 */
void RenderManualScreen3(void);

/* get response from the 4th manual
 * page
 */
int GetManualScreen3Response(void);

/* render the screen for set-up
 * phase, when dealing is in progress.
 * Takes a flag: DEALING_PLAYER or
 * DEALING_DEALER
 */
void RenderSetupScreenDuringDealing(int flag);

/* render the screen for set-up
 * phase, after dealing is done
 */
void RenderSetupScreenAfterDealing(void);

/* get response from the set-up
 * screen
 */
int GetSetupScreenResponse(void);

/* render the screen during a player's
 * turn, before a card is dealt
 */
void RenderPlayerTurnScreenBeforeDealing(void);

/* render the screen during a player's
 * turn, during the time of dealing a card
 */
void RenderPlayerTurnScreenDuringDealing(void);

/* get response from player's turn
 * screen
 */
int GetPlayerTurnScreenResponse(void);

/* render the screen during a dealer's turn
 */
void RenderDealerTurnScreen(void);

/* render the screen after a dealer's turn
 */
void RenderDealerTurnWaitRespondScreen(void);

/* get response from the screen after a dealer's
 * turn
 */
int GetDealerTurnWaitPlayerRespondScreenResponse(void);

/* render the screen for phone
 * number entry
 */
void RenderEnterPhoneNumberScreen(int* phone_num, int entry_pos);

/* render the screen for result
 */
void RenderResultScreen(int result);

/* get response from the phone number
 * entry screen; return 0 - 9 represents
 * a number entry; 10 - 12 respresents
 * main menu, clear, confirm; 0xFFFFFFFF
 * represents no button pressed
 */
int GetPhoneNumberScreenResponse(void);

/* get response from the result screen;
 * return MAIN_MENU_PRESSED, START_AGAIN_PRESSED,
 * or SEND_RESULT_TO_PHONE_PRESSED, or 0xFFFFFFFF
 * if no button pressed
 */
int GetResultScreenResponse(void);

/* state machine to process game logic from result
 * screen to phone number screen. Returns the next
 * screen
 */
int ResultScreenAndSendResultScreen(int result);

/* render the illegal phone number
 * prompt screen
 */
void RenderIllegalPhoneNumScreen(void);

/* get response from the illegal phone
 * number entry screen
 */
int GetIllegalPhoneNumScreenResponse(void);

#endif /* GUI_H_ */