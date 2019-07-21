#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Create constant variables for number of cards held in hand and player playing game
const int CARDSHELD = 5;
const int RANDOMSEED = 5;

    //initalize game functions requires 10 kingdom cards
int kingCards[10] = {minion, treasure_map, sea_hag, salvager, outpost, 
                    embargo, cutpurse, ambassador, tribute, steward};
//                                                          //
//  Generic pass/fail tester for conditional statements     //
//                                                          //
int conditionTester (int result){
    if (result){
        printf("PASS\n");
        return 0;
    }
    else{
        printf("FAIL\n");
        return 1;
    }
    return 1;
}
int choice(int playerCount, int passOrFail){
    struct gameState gState, testState;
    //Iniitalize gameState object with set infomation 
    initializeGame(playerCount, kingCards, RANDOMSEED, &gState);
    //Copy the game state and player cards **Taken from cardtest4.c from instructor handout**
    memcpy(&testState, &gState, sizeof(struct gameState));
//                                                          //
//  Begin Testing Stages  (ONLY TESTING endTurn function) //
//                                                          //

    int result = endTurn(&gState);

    if(playerCount > 1){
        printf("Testing if it is player 1's or player 2's turn\n");
        passOrFail += conditionTester(gState.whoseTurn == 1);
    }
    else if (playerCount < 1){
        printf("Testing if it is still player 1's turn\n");
        passOrFail += conditionTester(gState.whoseTurn == 1);
    }

    printf("Testing output from endTurn function\n");
    passOrFail += conditionTester(result == 0);

    result = endTurn(&gState);

    if(playerCount > 1){
        printf("Testing if it is player 1's or player 2's turn\n");
        passOrFail += conditionTester(gState.whoseTurn == 0);
    }
    
   else if (playerCount < 1){
        printf("Testing if it is still player 1's turn\n");
        passOrFail += conditionTester(gState.whoseTurn == 0);
    }

    printf("Testing output from endTurn function\n");
    passOrFail += conditionTester(result == 0);

return passOrFail;
}
//                                                          //
//  Test card effect                                        //
//                                                          //
int main (){
    int passOrFail = 0;
    int i;
    for(i = 1; i < 3; i++)
        passOrFail += choice(i, 0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}