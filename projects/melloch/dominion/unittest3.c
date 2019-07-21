#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Create constant variables for number of cards held in hand and player playing game
const int PLAYERCOUNT = 2;
const int RANDOMSEED = 5;
const int AMBASSADORINDEX = 0;
const int AMBASSADORNUM = 17;

    //initalize game functions requires 10 kingdom cards
int kingCards[10] = {ambassador, treasure_map, sea_hag, salvager, outpost, 
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
//  Test card effect Abassador                              //
//                                                          //
int choice(int des, int cardCount, int passOrFail){
    struct gameState gState, testState;
    int curseCard;
    //Iniitalize gameState object with set infomation 
    initializeGame(PLAYERCOUNT, kingCards, RANDOMSEED, &gState);

    gState.handCount[0] = cardCount;
    curseCard = gState.handCount[0] - des;
    int i;
    for(i = 0; i < gState.handCount[0]; i++){
        if (i < gState.handCount[0] - des)
            gState.hand[0][i] = ambassador;
        else
            gState.hand[0][i] = curse;
    }
    //Copy the game state and player cards **Taken from cardtest4.c from instructor handout**
    memcpy(&testState, &gState, sizeof(struct gameState));
//                                                          //
//  Begin Testing Stages  (ONLY TESTING caseMinion)          //
//                                                          //
    playCard(0, curseCard, des, 0, &gState);
    
    //Testing current hand is the previous hand - 3 or 2 depending on curse count 
    printf("Testing current hand is %d\n", (cardCount-(des+1)));
    passOrFail += conditionTester(gState.handCount[0] == (cardCount-(des+1)));

    int correctCards = 0;
    for(i = 0; i < gState.handCount[0]; i++){
        if (gState.hand[0][i] != ambassador)
            correctCards++;
    }
    printf("Testing hand after playing cards\n");
    passOrFail += conditionTester(correctCards == 0);

    //Testing increase in the supply of curse cards
    printf("Testing the supply of curse cards is %d\n", (testState.supplyCount[curse] + des));
    passOrFail += conditionTester(gState.supplyCount[curse] == (testState.supplyCount[curse] + des));

    //Testing discard count
    printf("Testing discard count for player 1 is %d\n", des+1);
    passOrFail += conditionTester(gState.discardCount[0]);

    //Testing if curse card was added to player 2's discard pile
    printf("Testing discard count for player 2 is %d\n", des);
    passOrFail += conditionTester(gState.discardCount[1]);

    //Testing if curse card was added to player 2's discard pile was curse
    if(des > 0){
    printf("Testing discard cards\n");
    for (i = 0; i < des; i++)
        passOrFail += conditionTester(gState.discard[1][i] == curse);
    }

    return passOrFail;
}
int main (){
    int passOrFail = 0;
    int cardCount = 5;
    int i;
    //i stands for how many curse cards we want and how many we want to discard
    for (i = 0; i < 3; i++)
        passOrFail += choice(i, cardCount, 0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}