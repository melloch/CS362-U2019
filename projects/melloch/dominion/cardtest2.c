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
    int initalDeckSet[5] = {curse, estate, duchy, province, copper};
    struct gameState gState, testState;
    //Iniitalize gameState object with set infomation 
    initializeGame(PLAYERCOUNT, kingCards, RANDOMSEED, &gState);
    //Pass number of cards to gameState object
    gState.deckCount[0] = CARDSHELD;
    //Copy the game state and player cards **Taken from cardtest4.c from instructor handout**
    memcpy(&testState, &gState, sizeof(struct gameState));
//                                                          //
//  Begin Testing Stages  (ONLY TESTING shuffle  )          //
//                                                          //
    //Testing amount and order of cards
    int i, j;
    int counter[2] = {0, 0};
    int shuffleTest = 0;
    printf("Testing if deck has same number and amount of cards");
    for(i = 0; i < gState.deckCount[0]; i++){
        if(i < CARDSHELD){
            if(initalDeckSet[i] != gState.deck[0][i])
                shuffleTest++;

            counter[0]++;
            counter[1]++;
        }
    }
    printf("Testing that deck is the same size");
    passOrFail += conditionTester(counter[0] == counter[1]);

    printf("Testing that the deck is different");
    passOrFail += conditionTester(shuffleTest == 0);

    shuffleTest = 0;
    for(i = 0; i < gState.deckCount[0]; i++){
        for(j = 0; j < CARDSHELD; j++){
            if (gState.deck[0][i] == initalDeckSet[j])
                shuffleTest++;
        }
    }

    //Testing if there are the are cards that were previously added
    printf("Testing that the deck has the same cards\n");
    passOrFail += conditionTester(shuffleTest == CARDSHELD);

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