#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Create constant variables for number of cards held in hand and player playing game
const int CARDSHELD = 5;
const int PLAYERCOUNT = 2;
const int RANDOMSEED = 5;
const int MINIONINDEX = 0;
const int MINIONNUM = 17;

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

//                                                          //
//  Test card effect                                        //
//                                                          //
int choice(int des, int passOrFail){
    struct gameState gState, testState;
    //Iniitalize gameState object with set infomation 
    initializeGame(PLAYERCOUNT, kingCards, RANDOMSEED, &gState);
    gState.handCount[0] = CARDSHELD;

    //Indexes 0 - 4 are minions.
    int i;
    for(i = 0; i < gState.handCount[0]; i++)
        gState.hand[0][i] = minion;
    //Copy the game state and player cards **Taken from cardtest4.c from instructor handout**
    memcpy(&testState, &gState, sizeof(struct gameState));
//                                                          //
//  Begin Testing Stages  (ONLY TESTING caseMinion)          //
//                                                          //
    //if des is 1 then +2 coin option. If des is 2 then discard option
    
    if(des == 1)
        playCard(MINIONINDEX, des, 0, 0, &gState);
    else
        playCard(MINIONINDEX, 0, des, 0, &gState);
    
    //Test that the number of Actions decreased by 1
    printf("Testing a decreases in number of actions by 1\n");
    passOrFail = conditionTester(gState.numActions == (testState.numActions - 1));

    //Testing that the players hand count is 4
    printf("Testing players hand count is 4\n");
    passOrFail += conditionTester(gState.handCount[0] == 4);

    //Tests for choice 1
    if (des == 1){
    //Tests if 2 coins were obtained 
    printf("Testing that 2 coins were obtained\n");
    passOrFail += conditionTester((gState.coins == (testState.coins + 2)) && (gState.coins == 2));

    //Testing discount count to be equal to 1
    printf("Testing the discount count is 1\n");
    passOrFail += conditionTester(gState.discardCount[0] == (testState.discardCount[0] + 1) && gState.discardCount[0] == 1);
    //Test that checks the card was placed in the pile
    int minionNum = 0;
    printf("Testing the discard pile contains 1 minion\n");
    for (i = 0; i < gState.discardCount[0]; i++){
        if (gState.discard[0][i] == MINIONNUM){
            minionNum++;
            }
        }
    passOrFail += conditionTester(minionNum == 1);

    //Tests 
    }
    //Player chose the second option
    else{
    //Tests that 2 coins were not obtained
    printf("Testing that 2 coins were not obtained\n");
    passOrFail += conditionTester(gState.coins == 0);

    //Testing that discount count is 5
    printf("Testing the discard count is 5\n");
    passOrFail += conditionTester(gState.discardCount[0] == 5);
    }

    return passOrFail;
}
//
//  Des is 1 when gaining 2 coins. Des is 2 when discarding hand. 
//
int main (){
    int passOrFail = 0;
    int i;
    for (i = 1; i < 3; i++)
        passOrFail += choice(i, 0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}


