#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Create constant variables for number of cards held in hand and player playing game
const int CARDSHELD = 1;
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

    //Draw card
    drawCard(0, &gState);
    drawCard(1, &gState);

    int i;
    for(i = 0; i < PLAYERCOUNT; i++){
    //Testing if the deck is 0
    printf("Testing if the players deck count is 0\n");
    passOrFail += conditionTester(gState.deckCount[i] == 0);

    //Testing if the players hand is 2
    printf("Testing if the players hand is 0\n");
    passOrFail += conditionTester(gState.handCount[0] == 0);

    //Testing if the dicard count is 0
    printf("Testing if the players discount count is 0\n");
    passOrFail += conditionTester(gState.discardCount[0] == 0);

    }
    //Set up 1 card for each person in deck
    for (i = 0; i < PLAYERCOUNT; i++){
        gState.deckCount[i] = CARDSHELD;
        gState.deck[i][0] = estate;
    }

    drawCard(0, &gState);
    drawCard(1, &gState);

    for(i = 0; i < PLAYERCOUNT; i++){
    //Testing if the deck is 0
    printf("Testing if the players deck count is 0\n");
    passOrFail += conditionTester(gState.deckCount[i] == 0);

    //Testing if the players hand is 2
    printf("Testing if the players hand is 0\n");
    passOrFail += conditionTester(gState.handCount[i] == 1);

    //Testing if the dicard count is 0
    printf("Testing if the players discount count is 0\n");
    passOrFail += conditionTester(gState.discardCount[i] == 0);

    }
        //Set up 1 card for each person in discard with none in deck
    for (i = 0; i < PLAYERCOUNT; i++){
        gState.discardCount[i] = CARDSHELD;
        gState.discard[i][0] = estate;
    }

    drawCard(0, &gState);
    drawCard(1, &gState); 

    for(i = 0; i < PLAYERCOUNT; i++){  
    //Testing if the deck is 0
    printf("Testing if the players deck count is 0\n");
    passOrFail += conditionTester(gState.deckCount[0] == 0);

    //Testing if the players hand is 2
    printf("Testing if the players hand is 0\n");
    passOrFail += conditionTester(gState.handCount[0] == 2);

    //Testing if the dicard count is 0
    printf("Testing if the players discount count is 0\n");
    passOrFail += conditionTester(gState.discardCount[0] == 0);
    }

return passOrFail;
}

int main (){
    int passOrFail = 0;
    passOrFail += choice(0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}