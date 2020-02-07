/*
 * Author: Jaskirat Singh, Eric Chen, Paul Davies
 * 
 * GUI functions to be called from the game logic
 */

#include "Graphics.h"
#include "touchscreen.h"

/* screens */
#define HOME_SCREEN 0
#define RESULT_SCREEN 1
#define SEND_RESULT_SCREEN 2

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
#define WIN 0   // player win
#define LOSE 1  // player lose
#define TIE 2
#define RESULT_SCREEN_BUTTON_WIDTH   200
#define RESULT_SCREEN_BUTTON_HEIGHT  100
#define RESULT_SCREEN_BUTTON_BORDER_WIDTH 2
#define RESULT_SCREEN_BUTTON_INIT_Y 360
#define START_AGAIN_INIT_X 100
#define SEND_RESULT_INIT_X 500
#define START_AGAIN_PRESSED 0
#define SEND_RESULT_TO_PHONE_PRESSED 1

/* display the welcome screen
 */
void homeScreen();

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

/* send record to phone */
void SendResponseToPhone(int* phone_num);

/* state machine to process game logic from result
 * screen to phone number screen. Returns the next
 * screen
 */
int ResultScreenAndSendResultScreen(int result);

/* helpers */
extern int player_hand;
extern int dealer_hand;

void screenBorder();
void homeButton(int flag);
void manualScreen();
void manualScreenParagraphFiller(char *a, int lineNumber);
void forwardButton();
void backwardButton();
void manual_1_helper();
void manual_2_helper();
void manual_3_helper();
void manual_4_helper();
void setup_play();
void hand_display();
void hit_stand_display();
void hitme();
void dealerPlay();
void results(int result);
void processResultScreen(int result);
void processPhoneScreen(void);
void dealingCardDisplay();