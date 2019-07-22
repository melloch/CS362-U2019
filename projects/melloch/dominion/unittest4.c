#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Create constant variables for number of cards held in hand and player playing game
const int CARDSHELD = 2;
const int PLAYERCOUNT = 2;
const int RANDOMSEED = 5;

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
//  Test card effect for tribute                            //
//                                                          //

int choice (int des, int passOrFail){
    struct gameState gState;
    //Iniitalize gameState object with set infomation 
    initializeGame(PLAYERCOUNT, kingCards, RANDOMSEED, &gState);
    gState.handCount[0] = CARDSHELD;
    int j;
    for (j = 0; j < gState.handCount[0]; j++)
        gState.hand[0][j] = tribute;

    //Test with actions cards
    if(des == 0){
    gState.deckCount[1] = CARDSHELD;
    int i;
    for(i = 0; i < gState.deckCount[1]; i++){
            gState.deck[1][i] = tribute;
        }
    playCard(0, 0, 0, 0, &gState);

    //Player 1 should have +4 actions
    printf("Player 1 should have +4 actions\n");
    passOrFail += conditionTester(gState.numActions = 4);

    printf("Player 1 should have 1 card left\n");
    passOrFail += conditionTester(gState.handCount[0] == 1);

    //Check discard pile for player 2
    int deckCheck = 0;
    for(i = 0; i < gState.discardCount[1]; i++){
            if (gState.discard[1][i] != tribute)
                deckCheck++;
        }
    printf("Testing that the cards previously in player 2's hand are in the discard pile\n");
    passOrFail += conditionTester(deckCheck == 0);

    }

    else if(des == 1){
    gState.deckCount[1] = CARDSHELD;
    int i;
    for(i = 0; i < gState.deckCount[1]; i++){
            gState.deck[1][i] = silver;
        }
        playCard(0, 0, 0, 0, &gState);

    //Player 1 should have +4 actions
    printf("Player 1 should have +4 coins\n");
    passOrFail += conditionTester(gState.coins = 4);

    printf("Player 1 should have 1 card left\n");
    passOrFail += conditionTester(gState.handCount[0] == 1);

    //Check discard pile for player 2
    int deckCheck = 0;
    for(i = 0; i < gState.discardCount[1]; i++){
            if (gState.discard[1][i] != silver)
                deckCheck++;
        }
    printf("Testing that the cards previously in player 2's hand are in the discard pile\n");
    passOrFail += conditionTester(deckCheck == 0);

    }

    else if(des == 2){
    gState.deckCount[1] = CARDSHELD;
    int i;
    for(i = 0; i < gState.deckCount[1]; i++){
            gState.deck[1][i] = estate;
        }
        playCard(0, 0, 0, 0, &gState);

    //Player 1 should have +4 cards
    printf("Player 1 should have +4 cards\n");
    passOrFail += conditionTester(gState.handCount[0] = 5);

    //Check discard pile for player 2
    int deckCheck = 0;
    for(i = 0; i < gState.discardCount[1]; i++){
            if (gState.discard[1][i] != estate)
                deckCheck++;
        }
    printf("Testing that the cards previously in player 2's hand are in the discard pile\n");
    passOrFail += conditionTester(deckCheck == 0);
    }
    else if (des == 3){
    gState.deckCount[1] = CARDSHELD;
    int i;
    for(i = 0; i < gState.deckCount[1]; i++){
        if (i < gState.deckCount[1] - 1)
            gState.deck[1][i] = silver;
        else 
            gState.deck[1][i] = estate;
        }
        playCard(0, 0, 0, 0, &gState);

    //Player 1 should have +4 actions
    printf("Player 1 should have +2 coins\n");
    passOrFail += conditionTester(gState.coins = 2);

    printf("Player 1 should have 3 card left\n");
    passOrFail += conditionTester(gState.handCount[0] == 3);

    //Check discard pile for player 2
    int deckCheck = 0;
    for(i = 0; i < gState.discardCount[1]; i++){
            if (gState.discard[1][i] != silver)
                deckCheck++;
            if (gState.discard[1][i] != estate)
                deckCheck++;
        }
    printf("Testing that the cards previously in player 2's hand are in the discard pile\n");
    passOrFail += conditionTester(deckCheck == 0);
    }
    else if (des == 4){
    gState.deckCount[1] = CARDSHELD;
    int i;
    for(i = 0; i < gState.deckCount[1]; i++){
        if (i < gState.deckCount[1] - 1)
            gState.deck[1][i] = estate;
        else 
            gState.deck[1][i] = tribute;
        }

    playCard(0, 0, 0, 0, &gState);
    //Player 1 should have +4 actions
    printf("Player 1 should have +2 actions\n");
    passOrFail += conditionTester(gState.numActions = 2);

    printf("Player 1 should have 3 card left\n");
    passOrFail += conditionTester(gState.handCount[0] == 3);

    //Check discard pile for player 2
    int deckCheck = 0;
    for(i = 0; i < gState.discardCount[1]; i++){
            if (gState.discard[1][i] != tribute)
                deckCheck++;
            if (gState.discard[1][i] != estate)
                deckCheck++;
        }
    printf("Testing that the cards previously in player 2's hand are in the discard pile");
    passOrFail += conditionTester(deckCheck == 0);

    }

    //Player 2 should have 0 cards in deck and 2 in discard pile 
    printf("Player 2 should have 0 cards in deck\n");
    passOrFail += conditionTester(gState.deckCount[1] == 0);

    printf("Player 2 should have 2 cards in discard pile\n");
    passOrFail += conditionTester(gState.discardCount[1] == 2);

    return passOrFail;
}


int main (){
    int passOrFail = 0;
    int i;
    for (i = 0; i < 5; i++)
        passOrFail += choice(i, 0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}