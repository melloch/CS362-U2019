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
int choice(int passOrFail){
    struct gameState gState, testState;
    //Iniitalize gameState object with set infomation 
    initializeGame(PLAYERCOUNT, kingCards, RANDOMSEED, &gState);
    //Copy the game state and player cards **Taken from cardtest4.c from instructor handout**
    memcpy(&testState, &gState, sizeof(struct gameState));
//                                                          //
//  Begin Testing Stages  (ONLY TESTING initalize function) //
//                                                          //

    //Test for correct number of players
    printf("Testing for correct number of players\n");
    passOrFail += conditionTester (gState.numPlayers == 2);

    //Check all supply fuctionality in game set up
    printf("Testing for correct supply of curse cards\n");
    passOrFail += conditionTester(gState.supplyCount[curse] == 10);

    printf("Testing for correct supply of estate cards\n");
    passOrFail += conditionTester(gState.supplyCount[estate] == 8);

    printf("Testing for correct supply of duchy cards\n");
    passOrFail += conditionTester(gState.supplyCount[duchy] == 8);

    printf("Testing for correct supply of province cards\n");
    passOrFail += conditionTester(gState.supplyCount[duchy] == 8);

    printf("Testing for correct supply of copper cards\n");
    passOrFail += conditionTester(gState.supplyCount[copper] == 46);

    printf("Testing for correct supply of silver cards\n");
    passOrFail += conditionTester(gState.supplyCount[silver] == 40);

    printf("Testing for correct supply of gold cards\n");
    passOrFail += conditionTester(gState.supplyCount[gold] == 30);

    printf("Testing for correct supply of silver cards\n");
    passOrFail += conditionTester(gState.supplyCount[silver] == 40);

    //                                                      //
    //  Check first players initalization set up            //
    //                                                      //
    printf("Testing count of outpost played\n");
    passOrFail += conditionTester(gState.outpostPlayed == 0);

    printf("Testing count of phase\n");
    passOrFail += conditionTester(gState.phase == 0);

    printf("Testing count of numActions\n");
    passOrFail += conditionTester(gState.numActions == 1);

    printf("Testing count of numBuys\n");
    passOrFail += conditionTester(gState.numBuys == 1);

    printf("Testing count of playerd Card Count\n");
    passOrFail += conditionTester(gState.playedCardCount == 0);

    printf("Testing count of whoseTurn\n");
    passOrFail += conditionTester(gState.whoseTurn == 0);

    printf("Testing count of hand count\n");
    passOrFail += conditionTester(gState.handCount[0] == 0);

return passOrFail;
}
//                                                          //
//  Test card effect                                        //
//                                                          //
int main (){
    int passOrFail = 0;
    passOrFail += choice(0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}