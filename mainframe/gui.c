//----------------------------------------------------------------------------------------------
//Funcitons by Jaskirat and Eric
//----------------------------------------------------------------------------------------------

#include "Graphics.h"
#include "touchscreen.h"
#include "gui.h"
#include "gameLogic.h"
#include <string.h>

char line_a[] = "->THE OBJECTIVE OF BLACKJACK";
char line_b[] = "Beat the Dealer.";
char line_c[] = "->HOW DO YOU BEAT THE DEALER?";
char line_d[] = "(i) By drawing a hand value that";
char line_e[] = "is higher than the dealer's hand";
char line_f[] = "(ii) By the dealer drawing hand ";
char line_g[] = "value that goes over 21.";
char line_h[] = "(iii) By drawing a hand value of";
char line_i[] = "21 on your first two cards.";
char line_j[] = "->HOW DO YOU LOSE TO THE DEALER?";
char line_k[] = "(i) Your hand value exceeds 21.";
char line_l[] = "(ii) The dealer's hand has a";
char line_m[] = "greater value thatn yours at";
char line_n[] = "the end of the round.";
char line_o[] = "->HOW DO YOU FIND HAND VALUE?";
char line_p[] = "(i) 2 through 10 count as";
char line_q[] = "face value. (3 is 3...).";
char line_r[] = "(ii) Face cards count as 10.";
char line_s[] = "(iii) Ace can be 1 or 11.";    

void screenBorder() {
    //Border for the screen    
    //Outer Red Border
    FillScreen(BLACK);
    RectangleFilledWBorder(31, 0, 750, 479, RED, BLACK, 9);
    //Inner Red Border
    RectangleFilledWBorder(51, 20, 710, 439, RED, BLACK, 9);
}

void homeButton(int flag) {
    char home[] = "HOME";
    int x;
    if(flag==1){
        RectangleFilledWBorder (590,40, 150, 50, RED, BLACK, 9);
        x = 610;
    }
    else
    {
        RectangleFilledWBorder (491,40, 249, 50, RED, BLACK, 9);
        x = 555;
    }
    int i;
    for(i=0;i<4;i++){
        OutGraphicsCharFont22x40(x, 45, WHITE, BLACK, home[i], 0);
        x=x+30;
    }
}

void RenderHomeScreen(void) {
    screenBorder();
    int i;
    //WELCOME 
    OutGraphicsCharFont22x40(275, 100, WHITE, WHITE, 'W', 0);
    OutGraphicsCharFont22x40(305, 100, WHITE, WHITE, 'E', 0);
    OutGraphicsCharFont22x40(335, 100, WHITE, WHITE, 'L', 0);
    OutGraphicsCharFont22x40(365, 100, WHITE, WHITE, 'C', 0);
    OutGraphicsCharFont22x40(395, 100, WHITE, WHITE, 'O', 0);
    OutGraphicsCharFont22x40(425, 100, WHITE, WHITE, 'M', 0);
    OutGraphicsCharFont22x40(455, 100, WHITE, WHITE, 'E', 0);
    //TO
    OutGraphicsCharFont22x40(515, 100, WHITE, WHITE, 'T', 0);
    OutGraphicsCharFont22x40(545, 100, WHITE, WHITE, 'O', 0);
    //BLACKJACK
    OutGraphicsCharFont22x40(290, 150, WHITE, WHITE, 'B', 0);
    OutGraphicsCharFont22x40(320, 150, WHITE, WHITE, 'L', 0);
    OutGraphicsCharFont22x40(350, 150, WHITE, WHITE, 'A', 0);
    OutGraphicsCharFont22x40(380, 150, WHITE, WHITE, 'C', 0);
    OutGraphicsCharFont22x40(410, 150, WHITE, WHITE, 'K', 0);
    OutGraphicsCharFont22x40(440, 150, WHITE, WHITE, 'J', 0);
    OutGraphicsCharFont22x40(470, 150, WHITE, WHITE, 'A', 0);
    OutGraphicsCharFont22x40(500, 150, WHITE, WHITE, 'C', 0);
    OutGraphicsCharFont22x40(530, 150, WHITE, WHITE, 'K', 0);

    //PLAY and MANUAL Boxes
    RectangleFilledWBorder(200, 250, 200, 150, RED, BLACK, 9);
    RectangleFilledWBorder(450, 250, 200, 150, RED, BLACK, 9);
    
    //Animation for PLAY  and MANUAL
    for (i=0; i<=700; i++){
        if(i<100){
            if((i%10)==0)
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, RED, 'P', 1);
                OutGraphicsCharFont22x40(270, 300, WHITE, RED, 'L', 1);
                OutGraphicsCharFont22x40(300, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(330, 300, WHITE, RED, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, RED, 'M', 1);
                OutGraphicsCharFont22x40(495, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, RED, 'N', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, RED, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, RED, 'L', 1);
            }
            else
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 1);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 1);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(330, 300, WHITE, BLACK, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 1);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 1);
            }
            
        }
        else if (i<200) {//p
            if((i%10)==0)
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 1);
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, RED, 'L', 1);
                OutGraphicsCharFont22x40(300, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(330, 300, WHITE, RED, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, RED, 'N', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, RED, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, RED, 'L', 1);
            }
            else
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 1);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(330, 300, WHITE, BLACK, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 1);
            }
        }
        else if (i<300) {//l
            if((i%10)==0)
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 1);
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 1);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 0);
                OutGraphicsCharFont22x40(300, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(330, 300, WHITE, RED, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, RED, 'N', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, RED, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, RED, 'L', 1);
            }
            else
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 0);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(330, 300, WHITE, BLACK, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 1);
            }
        }
        else if (i<400) {//a
            if((i%10)==0)
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 1);
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 1);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 0);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(330, 300, WHITE, RED, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, RED, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, RED, 'L', 1);
            }
            else
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 0);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(330, 300, WHITE, BLACK, 'Y', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 1);
            }
        }
        else if (i<500) {
            if((i%10)==0)//Y
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 1);
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 1);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 0);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(330, 300, WHITE, BLACK, 'Y', 1);
                OutGraphicsCharFont22x40(330, 300, WHITE, BLACK, 'Y', 0);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 0);
                OutGraphicsCharFont22x40(585, 300, WHITE, RED, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, RED, 'L', 1);
            }
            else
            {
                OutGraphicsCharFont22x40(240, 300, WHITE, BLACK, 'P', 0);
                OutGraphicsCharFont22x40(270, 300, WHITE, BLACK, 'L', 0);
                OutGraphicsCharFont22x40(300, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(330, 300, WHITE, BLACK, 'Y', 0);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 0);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 1);
            }
        }
        else if (i<600) {
            if((i%10)==0)//A
            {
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 0);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(615, 300, WHITE, RED, 'L', 1);
            }
            else
            {
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 0);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 1);
            }
        }
        else if (i<700) {
            if((i%10)==0)//L
            {
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 1);
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 1);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 1);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 0);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 1);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 1);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 0);
            }
            else
            {
                OutGraphicsCharFont22x40(465, 300, WHITE, BLACK, 'M', 0);
                OutGraphicsCharFont22x40(495, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(525, 300, WHITE, BLACK, 'N', 0);
                OutGraphicsCharFont22x40(555, 300, WHITE, BLACK, 'U', 0);
                OutGraphicsCharFont22x40(585, 300, WHITE, BLACK, 'A', 0);
                OutGraphicsCharFont22x40(615, 300, WHITE, BLACK, 'L', 0);
            }
        } 
    }
}

int GetHomeScreenResponse(void) {
    //Getting the point cordinates of touch release
    //The points are set after the finger is released from the screen
    Point p = GetRelease();

    //condition to determine which button is pressed
    if ((p.x >= 200) && (p.x <= 400) && (p.y>=250) && (p.y<=400)){
        printf("Play button pressed\n");
        return PLAY_PRESSED;
    }
    else if ((p.x>=450)&&(p.x<=650)&&((p.y>=200)&&(p.y<=400)))
    {
        printf("Manual Button pressed\n");
        return READ_MANUAL_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void manualScreenParagraphFiller( char *a, int lineNumber) {
    int len = (int) strlen(a);
    int i;
    int y = (lineNumber-1)*40 + 110;
    int x = 85;
    for (i=0; i<len; i++) {
            OutGraphicsCharFont16x27(x, y, WHITE, BLACK, a[i], 0);
            x = x+20;
    }
}

void forward_button(){
    RectangleFilledWBorder(690,390,37,35, RED, BLACK, 2);
    OutGraphicsCharFont22x40(697,388,RED, BLACK, '-', 0);
    OutGraphicsCharFont22x40(705,388,RED, BLACK, '>', 0);
}

void backward_button() {
    RectangleFilledWBorder(85,390,37,35, RED, BLACK, 2);
    OutGraphicsCharFont22x40(92,388,RED, BLACK, '<', 0);
    OutGraphicsCharFont22x40(99,388,RED, BLACK, '-', 0);
}

void RenderManualScreen0(void) {
    screenBorder();
    int i;
    char heading[] = "MANUAL";
    int len = (int) strlen(heading);
    int a = (400-(len/2)*20);
    for (i=0; i<len; i++){
        OutGraphicsCharFont22x40(a, 50, WHITE, BLACK, heading[i], 0);
        a = a + 20;
    }
    homeButton(1);
    //Manual Instructions inner border
    RectangleFilledWBorder(71, 100, 670, 339, RED, BLACK, 9);

    //Printing two lines in manual box
    manualScreenParagraphFiller(line_a, 1);
    manualScreenParagraphFiller(line_b, 2);

    forward_button();
}

int GetManualScreen0Response(void) {
    //Getting the point cordinates of touch release
    //The points are set after the finger is released from the screen
    Point p = GetRelease();

    //condition to determine which button is pressed
    if((p.x>=570)&&(p.x<=760)&&(p.y>=20)&&(p.y<=110)){
        printf("home button pressed\n");
        return MAIN_MENU_PRESSED;
    }
    else if ((p.x>=670)&&(p.x<=747)&&((p.y>=370)&&(p.y<=425)))
    {
        printf("forward pressed\n");
        return FORWARD_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void RenderManualScreen1(void) {
    //Manual Instructions inner border
    RectangleFilledWBorder(71, 100, 670, 339, RED, BLACK, 9);

    //Printing 7 lines in manual box
    manualScreenParagraphFiller(line_c, 1);
    manualScreenParagraphFiller(line_d, 2);
    manualScreenParagraphFiller(line_e, 3);
    manualScreenParagraphFiller(line_f, 4);
    manualScreenParagraphFiller(line_g, 5);
    manualScreenParagraphFiller(line_h, 6);
    manualScreenParagraphFiller(line_i, 7);

    backward_button();
    forward_button();
}

int GetManualScreen1Response(void) {
    //Getting the point cordinates of touch release
    //The points are set after the finger is released from the screen
    Point p = GetRelease();

    //condition to determine which button is pressed
    //Homescreen
    if((p.x>=570)&&(p.x<=760)&&(p.y>=20)&&(p.y<=110)){
        printf("home button pressed\n");
        return MAIN_MENU_PRESSED;
    }
    //Next page
    else if ((p.x>=670)&&(p.x<=747)&&((p.y>=370)&&(p.y<=425))){
        printf("forward pressed\n");
        return FORWARD_PRESSED;
    }
    //Previous page
    else if((p.x>=65)&&(p.x<=142)&&((p.y>=370)&&(p.y<=455))){
        printf("back pressed\n");
        return BACK_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void RenderManualScreen2(void) {
    //Manual Instructions inner border
    RectangleFilledWBorder(71, 100, 670, 339, RED, BLACK, 9);

    //Printing 5 lines in manual box
    manualScreenParagraphFiller(line_j, 1);
    manualScreenParagraphFiller(line_k, 2);
    manualScreenParagraphFiller(line_l, 3);
    manualScreenParagraphFiller(line_m, 4);
    manualScreenParagraphFiller(line_n, 5);

    forward_button();
    backward_button();
}

int GetManualScreen2Response(void) {
    //Getting the point cordinates of touch release
    //The points are set after the finger is released from the screen
    Point p = GetRelease();

    //condition to determine which button is pressed
    //Homescreen
    if((p.x>=570)&&(p.x<=760)&&(p.y>=20)&&(p.y<=110)){
        printf("home button pressed\n");
        return MAIN_MENU_PRESSED;
    }
    //Next page
    else if ((p.x>=670)&&(p.x<=747)&&((p.y>=370)&&(p.y<=425))) {
        printf("forward pressed\b");
        return FORWARD_PRESSED;
    }
    //Previous page
    else if((p.x>=65)&&(p.x<=142)&&((p.y>=370)&&(p.y<=455))){
        printf("back pressed\n");
        return BACK_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void RenderManualScreen3(void) {
    //Manual Instructions inner border
    RectangleFilledWBorder(71, 100, 670, 339, RED, BLACK, 9);

    //printing 5 lines in manual box
    manualScreenParagraphFiller(line_o, 1);
    manualScreenParagraphFiller(line_p, 2);
    manualScreenParagraphFiller(line_q, 3);
    manualScreenParagraphFiller(line_r, 4);
    manualScreenParagraphFiller(line_s, 5);

    backward_button();
}

int GetManualScreen3Response(void) {
    //Getting the point cordinates of touch release
    //The points are set after the finger is released from the screen
    Point p = GetRelease();

    //condition to determine which button is pressed
    //Homescreen
    if((p.x>=570)&&(p.x<=760)&&(p.y>=20)&&(p.y<=110)){
        printf("home button pressed\n");
        return MAIN_MENU_PRESSED;
    }
    //Previous page
    else if((p.x>=65)&&(p.x<=142)&&((p.y>=370)&&(p.y<=455))){
        printf("back pressed\n");
        return BACK_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void hit_stand_display() {
    /* rectangles for "hit me" and "stand" */
    if (player_hand < 21) {
        RectangleFilledWBorder(491, 110, 249, 120, RED, RED, 9);
    }
    RectangleFilledWBorder(491, 250, 249, 190, RED, RED, 9);

    char hit[] = "HIT ME";
    char stand[] = "STAND!";
    int len = (int) strlen(hit);
    int a = 550;
    int i;
    for (i=0; i<len; i++){
        if (player_hand < 21) {
            OutGraphicsCharFont22x40(a, 155, WHITE, BLACK, hit[i], 0);
        }
        OutGraphicsCharFont22x40(a, 330, WHITE, BLACK, stand[i], 0);
        a = a + 20;
    }
}

void dealingCardDisplay(int flag) {
    //Boxes to show Dealer and Player Hands
    RectangleFilledWBorder(71, 40, 400, 400, RED, BLACK, 9);
    RectangleFilledWBorder(91, 60, 360, 360, RED, BLACK, 9);
    //RectangleFilledWBorder(71, 250, 400, 190, RED, BLACK, 9);

    char player[] = "DEALING PLAYER";
    char dealer[] = "DEALING DEALER";
    int len = (int) strlen(dealer);
    int a = (255-(len/2)*20);
    int i;
    for (i=0; i<len; i++){
        if (flag == DEALING_DEALER)
            OutGraphicsCharFont22x40(a, 240, WHITE, BLACK, dealer[i], 0);
        else if (flag == DEALING_PLAYER)
            OutGraphicsCharFont22x40(a, 240, WHITE, BLACK, player[i], 0);
        a = a + 20;
    }
}

void continue_display(void) {
    /* rectangle for the continue button */
    RectangleFilledWBorder(491, 110, 249, 120, RED, RED, 9);

    char continueLine[] = "CONTINUE";
    int len = (int) strlen(continueLine);
    int a = 550;
    int i;
    for (i=0; i<len; i++){
        OutGraphicsCharFont22x40(a, 155, WHITE, BLACK, continueLine[i], 0);
        a = a + 20;
    }
}

void hand_display(){
    //Boxes to show Dealer and Player Hands
    RectangleFilledWBorder(71, 40, 400, 190, RED, BLACK, 9);
    RectangleFilledWBorder(71, 250, 400, 190, RED, BLACK, 9);

    char dealer[] = "DEALER'S HAND: ";
    char player[] = "PLAYER'S HAND: ";
    int len = (int) strlen(dealer);
    int a = (235-(len/2)*20);
    int i;
    for (i=0; i<len; i++){
        OutGraphicsCharFont22x40(a, 115, WHITE, BLACK, dealer[i], 0);
        OutGraphicsCharFont22x40(a, 345, WHITE, BLACK, player[i], 0);
        a = a + 20;
    }

    //temp variables to print hand value
    int player_hand_digits = 0;
    int dealer_hand_digits = 0;
    int player_hand_temp = player_hand;
    int dealer_hand_temp = dealer_hand;

    //calculating the number of digits in hand value : 1 or 2
    while (player_hand_temp != 0) {
        player_hand_temp /= 10;   
        ++player_hand_digits;
    }
    while (dealer_hand_temp != 0) {
        dealer_hand_temp /= 10;   
        ++dealer_hand_digits;
    }

    //Printing Dealer's Hand
    if(dealer_hand_digits==1)
        OutGraphicsCharFont22x40(a, 115, YELLOW, BLACK, (dealer_hand + '0'), 0);
    else{
        OutGraphicsCharFont22x40(a, 115, YELLOW, BLACK, ((dealer_hand/10) + '0' ), 0);
        OutGraphicsCharFont22x40(a+20, 115, YELLOW, BLACK, ((dealer_hand - (dealer_hand/10)*10) + '0'), 0);
    }

    //Printing Player's Hand
    if(player_hand_digits==1)
        OutGraphicsCharFont22x40(a, 345, GREEN, BLACK, (player_hand + '0'), 0);
    else{
        OutGraphicsCharFont22x40(a, 345, GREEN, BLACK, ((player_hand/10) + '0'), 0);
        OutGraphicsCharFont22x40(a+20, 345, GREEN, BLACK, ((player_hand - (player_hand/10)*10) + '0'), 0);
    }
}

void RenderSetupScreenDuringDealing(int flag) {
    screenBorder();
    homeButton(2);
    dealingCardDisplay(flag);
}

void RenderSetupScreenAfterDealing(void) {
    screenBorder();
    homeButton(2);
    hand_display();
    continue_display();
}

int GetSetupScreenResponse(void) {
    //Getting the point cordinates of touch release
    //The points are set after the finger is released from the screen
    Point p = GetRelease();

    // Homescreen
    if((p.x>=570)&&(p.x<=760)&&(p.y>=20)&&(p.y<=110)){
        printf("home button pressed\n");
        return MAIN_MENU_PRESSED;
    }
    // continue pressed
    else if ((p.x>=491)&&(p.x<=750)&&((p.y>120)&&(p.y<=235))){
        printf("continue pressed\n");
        return CONTINUE_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void RenderPlayerTurnScreenBeforeDealing(void) {
    screenBorder();
    homeButton(2);
    hand_display();
    hit_stand_display();
}

void RenderPlayerTurnScreenDuringDealing(void) {
    screenBorder();
    homeButton(2);
    dealingCardDisplay(DEALING_PLAYER);
}

int GetPlayerTurnScreenResponse(void) {
    //Getting the point cordinates of touch release
    //The points are set after the finger is released from the screen
    Point p = GetRelease();

    // condition to determine which button is pressed
    // Homescreen
    if((p.x>=491)&&(p.x<=750)&&(p.y>=37)&&(p.y<=100)){
        printf("home button pressed\n");
        return MAIN_MENU_PRESSED;
    }
    // hit me
    else if ((p.x>=491)&&(p.x<=750)&&((p.y>120)&&(p.y<=235))){
        printf("Hit me\n");
        return PLAYER_HIT_ME;
    }
    // stand
    else if((p.x>=491)&&(p.x<=750)&&((p.y>=240)&&(p.y<=440))){
        printf("Stand\n");
        return PLAYER_STAND;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void RenderDealerTurnScreen(void) {
    screenBorder();
    homeButton(2);
    dealingCardDisplay(DEALING_DEALER);
}

void RenderEnterPhoneNumberScreen(int* phone_num, int entry_pos) {
    /* render background */
    FillScreen(RED);

    /* render the main menu button */
    homeButton(1);
    
    /* render the instruction line */
    char instructionLine[] = {'P', 'l', 'e', 'a', 's', 'e', ' ', 'e', 'n', 't', 'e', 'r',
                                ' ', 'y', 'o', 'u', 'r', ' ', 'p', 'h', 'o', 'n', 'e', ' ',
                                'n', 'u', 'm', 'b', 'e', 'r', ':'};
    int i;
    int x=150; int y=50;
    for (i=0; i<31; i++) {
        OutGraphicsCharFont10x14(x, y, WHITE, WHITE, instructionLine[i], 0);
        x+= 15;
    }

    /* render the entry box */
    RectangleFilledWBorder(ENTRY_BOX_UL_X, ENTRY_BOX_UL_Y, ENTRY_BOX_WIDTH, ENTRY_BOX_HEIGHT, BROWN, ORANGE, ENTRY_BOX_BORDER_WIDTH);
    for (i=0; i<entry_pos; i++) {
        OutGraphicsCharFont10x14((ENTRY_BOX_UL_X + ENTRY_BOX_BORDER_WIDTH + 20 + 12*i), (ENTRY_BOX_UL_Y + ENTRY_BOX_BORDER_WIDTH + 4), BLACK, WHITE, (phone_num[i] + 0x30), 0);
    }

    /* render the phone pad */
    int num=1;
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (y=PHONEPAD_INIT_Y; num>0; y+=(PHONEPAD_BUTTON_HEIGHT+PHONEPAD_BUTTON_SEPARATION_Y)) {
        if (num>9) {
            num = 0;
            RectangleFilledWBorder(PHONEPAD_INIT_X+PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X, y, PHONEPAD_BUTTON_WIDTH, PHONEPAD_BUTTON_HEIGHT, BLACK, WHITE, 2);
            OutGraphicsCharFont22x40(PHONEPAD_INIT_X+PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X+PHONEPAD_BUTTON_BORDER_WIDTH+5, y+PHONEPAD_BUTTON_BORDER_WIDTH+2, BLACK, BLACK, numbers[num], 0);
            break;
        }
        for (x=PHONEPAD_INIT_X; x<PHONEPAD_INIT_X+3*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X); x+=(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)) {
            RectangleFilledWBorder(x, y, PHONEPAD_BUTTON_WIDTH, PHONEPAD_BUTTON_HEIGHT, BLACK, WHITE, 2);
            OutGraphicsCharFont22x40(x+PHONEPAD_BUTTON_BORDER_WIDTH+5, y+PHONEPAD_BUTTON_BORDER_WIDTH+2, BLACK, BLACK, numbers[num], 0);
            num += 1;
        }
    }

    /* render the clear and confirm button */
    char clearLine[] = {'C', 'L', 'E', 'A', 'R'};
    char confirmLine[] = {'C', 'O', 'N', 'F', 'I', 'R', 'M'};
    RectangleFilledWBorder(CLEAR_INIT_X, CONFIRM_AND_CLEAR_INIT_Y, CONFIRM_AND_CLEAR_WIDTH, CONFIRM_AND_CLEAR_HEIGHT, BLACK, SILVER, CONFIRM_AND_CLEAR_BORDER_WIDTH);
    for (i=0; i<5; i++) {
        OutGraphicsCharFont22x40(CLEAR_INIT_X+CONFIRM_AND_CLEAR_BORDER_WIDTH+25+i*25, CONFIRM_AND_CLEAR_INIT_Y+CONFIRM_AND_CLEAR_BORDER_WIDTH+4, BLACK, WHITE, clearLine[i], 0);
    }
    RectangleFilledWBorder(CONFIRM_INIT_X, CONFIRM_AND_CLEAR_INIT_Y, CONFIRM_AND_CLEAR_WIDTH, CONFIRM_AND_CLEAR_HEIGHT, BLACK, SILVER, CONFIRM_AND_CLEAR_BORDER_WIDTH);
    for (i=0; i<7; i++) {
        OutGraphicsCharFont22x40(CONFIRM_INIT_X+CONFIRM_AND_CLEAR_BORDER_WIDTH+8+i*25, CONFIRM_AND_CLEAR_INIT_Y+CONFIRM_AND_CLEAR_BORDER_WIDTH+4, BLACK, WHITE, confirmLine[i], 0);
    }
}

int GetPhoneNumberScreenResponse(void) {
    Point POfRelease = GetRelease();
    /* if a press in the phonepad area */
    if (POfRelease.x >= PHONEPAD_INIT_X
        && POfRelease.x < PHONEPAD_INIT_X+3*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)
        && POfRelease.y >= PHONEPAD_INIT_Y
        && POfRelease.y < PHONEPAD_INIT_Y+4*(PHONEPAD_BUTTON_HEIGHT+PHONEPAD_BUTTON_SEPARATION_Y)) {
        /* if 1, 2, 3 pressed */
        if (POfRelease.y < PHONEPAD_INIT_Y+1*(PHONEPAD_BUTTON_HEIGHT+PHONEPAD_BUTTON_SEPARATION_Y)) {
            if (POfRelease.x < (int) PHONEPAD_INIT_X+1*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)-0.5*PHONEPAD_BUTTON_SEPARATION_X) {
                return 1;
            }
            else if (POfRelease.x < (int) PHONEPAD_INIT_X+2*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)-0.5*PHONEPAD_BUTTON_SEPARATION_X) {
                return 2;
            }
            else if (POfRelease.x < (int) PHONEPAD_INIT_X+3*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)) {
                return 3;
            }
        }
        /* if 4, 5, 6 pressed */
        else if (POfRelease.y < PHONEPAD_INIT_Y+2*(PHONEPAD_BUTTON_HEIGHT+PHONEPAD_BUTTON_SEPARATION_Y)) {
            if (POfRelease.x < (int) PHONEPAD_INIT_X+1*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)-0.5*PHONEPAD_BUTTON_SEPARATION_X) {
                return 4;
            }
            else if (POfRelease.x < (int) PHONEPAD_INIT_X+2*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)-0.5*PHONEPAD_BUTTON_SEPARATION_X) {
                return 5;
            }
            else if (POfRelease.x < (int) PHONEPAD_INIT_X+3*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)) {
                return 6;
            }
        }
        /* if 7, 8, 9 pressed */
        else if (POfRelease.y < PHONEPAD_INIT_Y+3*(PHONEPAD_BUTTON_HEIGHT+PHONEPAD_BUTTON_SEPARATION_Y)) {
            if (POfRelease.x < (int) PHONEPAD_INIT_X+1*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)-0.5*PHONEPAD_BUTTON_SEPARATION_X) {
                return 7;
            }
            else if (POfRelease.x < (int) PHONEPAD_INIT_X+2*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)-0.5*PHONEPAD_BUTTON_SEPARATION_X) {
                return 8;
            }
            else if (POfRelease.x < (int) PHONEPAD_INIT_X+3*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)) {
                return 9;
            }
        }
        /* if 0 pressed */
        else if (POfRelease.x >= PHONEPAD_INIT_X+1*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)
                 && POfRelease.x < PHONEPAD_INIT_X+2*(PHONEPAD_BUTTON_WIDTH+PHONEPAD_BUTTON_SEPARATION_X)) {
            return 0;
        }
        /* if "null" press */
        else {
            return 0xFFFFFFFF;
        }
    }
    /* TODO: if main menu is pressed */
    else if((POfRelease.x>=491)
            &&(POfRelease.x<=750)
            &&(POfRelease.y>=37)
            &&(POfRelease.y<=100)){
        return MAIN_MENU_PRESSED;
    }
    /* if clear is pressed */
    else if (POfRelease.x >= CLEAR_INIT_X
             && POfRelease.x < CLEAR_INIT_X+CONFIRM_AND_CLEAR_WIDTH
             && POfRelease.y >= CONFIRM_AND_CLEAR_INIT_Y
             && POfRelease.y < CONFIRM_AND_CLEAR_INIT_Y+CONFIRM_AND_CLEAR_HEIGHT) {
        return CLEAR_PRESSED;
    }
    /* if confirm is pressed */
    else if (POfRelease.x >= CONFIRM_INIT_X
             && POfRelease.x < CONFIRM_INIT_X+CONFIRM_AND_CLEAR_WIDTH
             && POfRelease.y >= CONFIRM_AND_CLEAR_INIT_Y
             && POfRelease.y < CONFIRM_AND_CLEAR_INIT_Y+CONFIRM_AND_CLEAR_HEIGHT) {
        return CONFIRM_PRESSED;
    }
    /* no buttons pressed */
    else {
        return 0xFFFFFFFF;
    }
}

void RenderResultScreen(int result) {
    /* render background */
    FillScreen(RED);

    /* render the main menu button */
    homeButton(1);
    
    /* render the result notification */
    Circle(400, 200, 160, BLACK, ORANGE, 8);
    char winLine[] = {'Y', 'o', 'u', ' ', 'w', 'i', 'n', '!'};
    char loseLine[] = {'G', 'a', 'm', 'e', ' ', 'o', 'v', 'e', 'r', '!'};
    char tieLine[] = {'T', 'i', 'e', '!'};
    int char_count;
    if (result==WIN) {
        char_count = 8;
    }
    else if (result==LOSE) {
        char_count = 10;
    }
    else {
        char_count = 4;
    }
    int i;
    for (i=0; i<char_count; i++) {
        if (result==WIN) {
            OutGraphicsCharFont22x40(300+i*28, 180, BLUE, WHITE, winLine[i], 0);
        }
        else if (result==LOSE) {
            OutGraphicsCharFont22x40(270+i*28, 180, BLUE, WHITE, loseLine[i], 0);
        }
        else {
            OutGraphicsCharFont22x40(360+i*28, 180, BLUE, WHITE, tieLine[i], 0);
        }
    }

    /* render start again and send score to phone */
    /* render the clear and confirm button */
    char startAgainLine1[] = {'S', 'T', 'A', 'R', 'T'};
    char startAgainLine2[] = {'A', 'G', 'A', 'I', 'N'};
    char sendResultToPhoneLine1[] = {'S', 'E', 'N', 'D'};
    char sendResultToPhoneLine2[] = {'R', 'E', 'S', 'U', 'L', 'T', ' ', 'T', 'O'};
    char sendResultToPhoneLine3[] = {'P', 'H', 'O', 'N', 'E'};
    RectangleFilledWBorder(START_AGAIN_INIT_X, RESULT_SCREEN_BUTTON_INIT_Y, RESULT_SCREEN_BUTTON_WIDTH, RESULT_SCREEN_BUTTON_HEIGHT, BLACK, SILVER, RESULT_SCREEN_BUTTON_BORDER_WIDTH);
    for (i=0; i<5; i++) {
        OutGraphicsCharFont16x27(START_AGAIN_INIT_X+RESULT_SCREEN_BUTTON_BORDER_WIDTH+45+i*20, RESULT_SCREEN_BUTTON_INIT_Y+RESULT_SCREEN_BUTTON_BORDER_WIDTH+15, BLACK, WHITE, startAgainLine1[i], 0);
    }
    for (i=0; i<5; i++) {
        OutGraphicsCharFont16x27(START_AGAIN_INIT_X+RESULT_SCREEN_BUTTON_BORDER_WIDTH+45+i*20, RESULT_SCREEN_BUTTON_INIT_Y+RESULT_SCREEN_BUTTON_BORDER_WIDTH+46, BLACK, WHITE, startAgainLine2[i], 0);
    }
    RectangleFilledWBorder(SEND_RESULT_INIT_X, RESULT_SCREEN_BUTTON_INIT_Y, RESULT_SCREEN_BUTTON_WIDTH, RESULT_SCREEN_BUTTON_HEIGHT, BLACK, SILVER, RESULT_SCREEN_BUTTON_BORDER_WIDTH);
    for (i=0; i<4; i++) {
        OutGraphicsCharFont16x27(SEND_RESULT_INIT_X+RESULT_SCREEN_BUTTON_BORDER_WIDTH+54+i*20, RESULT_SCREEN_BUTTON_INIT_Y+RESULT_SCREEN_BUTTON_BORDER_WIDTH+4, BLACK, WHITE, sendResultToPhoneLine1[i], 0);
    }
    for (i=0; i<9; i++) {
        OutGraphicsCharFont16x27(SEND_RESULT_INIT_X+RESULT_SCREEN_BUTTON_BORDER_WIDTH+8+i*20, RESULT_SCREEN_BUTTON_INIT_Y+RESULT_SCREEN_BUTTON_BORDER_WIDTH+35, BLACK, WHITE, sendResultToPhoneLine2[i], 0);
    }
    for (i=0; i<5; i++) {
        OutGraphicsCharFont16x27(SEND_RESULT_INIT_X+RESULT_SCREEN_BUTTON_BORDER_WIDTH+44+i*20, RESULT_SCREEN_BUTTON_INIT_Y+RESULT_SCREEN_BUTTON_BORDER_WIDTH+66, BLACK, WHITE, sendResultToPhoneLine3[i], 0);
    }
}

int GetResultScreenResponse(void) {
    Point POfRelease = GetRelease();
    if (POfRelease.x >= START_AGAIN_INIT_X && POfRelease.x < (START_AGAIN_INIT_X + RESULT_SCREEN_BUTTON_WIDTH)
        && POfRelease.y >= RESULT_SCREEN_BUTTON_INIT_Y && POfRelease.y < (RESULT_SCREEN_BUTTON_INIT_Y+RESULT_SCREEN_BUTTON_HEIGHT)) {
        return START_AGAIN_PRESSED;
    }
    else if (POfRelease.x >= SEND_RESULT_INIT_X && POfRelease.x < (SEND_RESULT_INIT_X + RESULT_SCREEN_BUTTON_WIDTH)
             && POfRelease.y >= RESULT_SCREEN_BUTTON_INIT_Y && POfRelease.y < (RESULT_SCREEN_BUTTON_INIT_Y+RESULT_SCREEN_BUTTON_HEIGHT)) {
        return SEND_RESULT_TO_PHONE_PRESSED;
    }
    else if((POfRelease.x>=491)
            &&(POfRelease.x<=750)
            &&(POfRelease.y>=37)
            &&(POfRelease.y<=100)){
        return MAIN_MENU_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}

void SendResponseToPhone(int* phone_num) {
    // TODO: stub
    return;
}

void RenderIllegalPhoneNumScreen(void) {
    RectangleFilledWBorder(200, 100, 400, 280, BLACK, GRAY, 9);
    /* render the prompt */
    int i;
    char illegalPhoneNumLine1[] = " Not enough digits ";
    char illegalPhoneNumLine2[] = "Please enter again.";
    for (i=0; i< strlen(illegalPhoneNumLine1); i++) {
        OutGraphicsCharFont10x14(275+10+i*15, 190, BLACK, BLACK, illegalPhoneNumLine1[i], 0);
        OutGraphicsCharFont10x14(275+10+i*15, 220, BLACK, BLACK, illegalPhoneNumLine2[i], 0);
    }

    /* render OK */
    char OK[] = "OK";
    RectangleFilledWBorder(300, 280, 200, 80, BLACK, WHITE, 9);
    for (i=0; i<2; i++) {
        OutGraphicsCharFont22x40(390+10+i*27, 295, BLACK, BLACK, OK[i], 0);
    }
}

int GetIllegalPhoneNumScreenResponse(void) {
    Point POfRelease = GetRelease();
    if((POfRelease.x>=491)
        &&(POfRelease.x<=750)
        &&(POfRelease.y>=37)
        &&(POfRelease.y<=100)){
        return MAIN_MENU_PRESSED;
    }
    else if (POfRelease.x>=300 && POfRelease.x<600
        && POfRelease.y>=300 && POfRelease.y<380) {
        return OK_PRESSED;
    }
    else {
        return 0xFFFFFFFF;
    }
}