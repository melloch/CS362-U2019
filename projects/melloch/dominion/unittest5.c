#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Create constant variables for number of cards held in hand and player playing game
const int PLAYERCOUNT = 2;
const int RANDOMSEED = 5;
const int CARDSHELD = 5;

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
//  Test card effect                                        //
//                                                          //
int choice(int des, int passOrFail){
    struct gameState gState;
    //Iniitalize gameState object with set infomation 
    initializeGame(PLAYERCOUNT, kingCards, RANDOMSEED, &gState);
    gState.handCount[0] = CARDSHELD;

    if(des == 0){
    int i;
    for (i = 0; i < gState.handCount[0]; i++){
        if(i == 0)
            gState.hand[0][i] = mine;
        else
            gState.hand[0][i] = silver;
        } 

        playCard(0, gState.handCount[0] - 1, gold, 0, &gState);

        //Testing that the current hand is 4
        printf("Testing that the current hand is 4\n");
        passOrFail += conditionTester(gState.handCount[0] == 4);

        //Testing that the discard pile is 1
        printf("Testing that the discard count is 4\n");
        passOrFail += conditionTester(gState.discardCount[0] == 1);

        //Testing that there are only 3 coppers in the hand
        printf("Testing that there is only 3 coppers left in the hand\n");
        int copperCount = 0;
        for(i = 0; i < gState.handCount[0]; i++)
            if (gState.hand[0][i] == copper)
                copperCount++;
        passOrFail += conditionTester(copperCount == 3);

        //Test that the last card in the hand is gold
        printf("Testing the last card in the hand is gold\n");
        passOrFail += conditionTester(gState.hand[0][gState.handCount[0]] == gold);

        //Testing that the discard pile is 1
        printf("Testing that the discard pile is 2\n");
        passOrFail += conditionTester(gState.discardCount[0] == 2);

        //Testing that there is 1 copper in the discard pile
        printf("Testing that there is 1 copper in the discard pile\n");
        copperCount = 0;
        int mineCount = 0;
        for (i = 0; i < gState.discardCount[0]; i++)
            if (gState.discard[0][i] == copper)
                copperCount++;
            else if (gState.discard[0][i] == mine)
                mineCount++;
        passOrFail += conditionTester(copperCount == 1);
        printf("Testing there is 1 mine card in the discard pile\n");
        passOrFail += conditionTester(mineCount == 1);
    }
    //Trying to trade a card with an incompatable card
    else if(des == 1){
    int i;
    for (i = 0; i < gState.handCount[0]; i++){
        if(i == 0)
            gState.hand[0][i] = mine;
        else
            gState.hand[0][i] = copper;
        } 
        playCard(0, gState.handCount[0] - 1, gold, 0, &gState);

        //Testing that the current hand is 4
        printf("Testing that the current hand is 4\n");
        passOrFail += conditionTester(gState.handCount[0] == 4);

        //Testing that the discard pile is 1
        printf("Testing that the discard count is 1\n");
        passOrFail += conditionTester(gState.discardCount[0] == 1);

        //Testing that there are only 4 coppers in the hand
        printf("Testing that there is only 4 coppers left in the hand\n");
        int copperCount = 0;
        for(i = 0; i < gState.handCount[0]; i++)
            if (gState.hand[0][i] == copper)
                copperCount++;
        passOrFail += conditionTester(copperCount == 4);

        //Test that the last card in the hand is gold
        printf("Testing the last card not in the hand is gold\n");
        passOrFail += conditionTester(gState.hand[0][gState.handCount[0]] != gold);

        //Testing that the discard pile is 1
        printf("Testing that the discard pile is 1\n");
        passOrFail += conditionTester(gState.discardCount[0] == 1);

        //Testing that there is 1 copper in the discard pile
        printf("Testing that there is 1 copper in the discard pile\n");
        copperCount = 0;
        int mineCount = 0;
        for (i = 0; i < gState.discardCount[0]; i++)
            if (gState.discard[0][i] == copper)
                copperCount++;
            if (gState.discard[0][i] == mine)
                mineCount++;
        passOrFail += conditionTester(copperCount != 1);
        printf("Testing there is 1 mine card in the discard pile\n");
        passOrFail += conditionTester(mineCount == 1);

    }
    return passOrFail;
}
int main (){
    int passOrFail = 0;
    int i;
    //i stands for how many curse cards we want and how many we want to discard
    for (i = 0; i < 2; i++)
        passOrFail += choice(i, 0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}