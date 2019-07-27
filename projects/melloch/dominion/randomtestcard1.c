#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

    //Create constant variables for number of cards held in hand and player playing game
const int ESTATENUMBER = 1; //Estate cards is 1 in program
const int BARONINDEX = 0; //BARON CARDS ARE HELD AT BEGINNING OF HAND
const int BARONNUMBER = 15;

    //initalize game functions requires 10 kingdom cards
int kingCards[10] = {baron, treasure_map, sea_hag, salvager, outpost, 
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
//  Test player state with "Greater than 0" estate cards    //
//                                                          //
int oneEstateBaron (int cardsHeld, int seed, int playerCount, int des, int passOrFail){
    struct gameState gState, testState;
    //Iniitalize gameState object with set infomation 
    initializeGame(playerCount, kingCards, seed, &gState);
    gState.handCount[0] = cardsHeld;
    //Indexes 0 - 3 are barons. 1 estate card is available
    int i;
    for(i = 0; i < gState.handCount[0]; i++){
        if (i < (gState.handCount[0] - 1))
            gState.hand[0][i] = baron;
        else
            gState.hand[0][i] = estate;   
    }
    
    //Copy the game state and player cards **Taken from cardtest4.c from instructor handout**
    memcpy(&testState, &gState, sizeof(struct gameState));
//                                                          //
//  Begin Testing Stages  (ONLY TESTING caseBaron)          //
//                                                          //
    //Pass in the index of the baron card, the deision, and the gamestate NEED EXTRA 0'S
    //AT THE 3RD AND 4TH POSITION FOR FUNCTION TO WORK. THEY ARE NOT USED IN 
    //BARON FUNCTION
    playCard(BARONINDEX, des, 0, 0, &gState);
    
    //Testing that numBuys was incremented by 1 from previous state
    printf("Testing if number of buys was incremented by 1 \n");
    passOrFail += conditionTester(((testState.numBuys + 1) == gState.numBuys) && (gState.numBuys == 2));
    
    int estateCount = 0;
//                                                              //
//  Player wants to discard the estate card                     //
//  Player is unable to discard estate when no estates on hand  //
    if (des == 1){
    printf("Testing the estate card was discarded\n");
    //Make sure estate is no longer in hand
    for (i = 0; i < gState.handCount[0]; i++){
        if (gState.hand[0][i] == ESTATENUMBER){
            estateCount++;
            }
        }
    passOrFail += conditionTester(estateCount == 0);

    //Testing that players hand size is 3
    printf("Testing if hand size is cardsHeld - 2\n");
    passOrFail += conditionTester(((testState.handCount[0] - 1) == gState.handCount[0]) && (gState.handCount[0] == (cardsHeld - 2)));

    //Test that the player receives 4 gold
    printf("Testing that the player receives 4 coins\n");
    passOrFail += conditionTester(((testState.coins + 4) == gState.coins) &&(gState.coins == 4));

    //Testing that the discount pile should be 2
    printf("Testing that the discount pile is equal to 1\n");
    passOrFail += conditionTester(((testState.discardCount[0] + 2) == gState.discardCount[0]) && (gState.discardCount[0] == 2));
    }
//                                                           //
//  Player wants another estate card.                        //
//  Player should have 1 estate card in hand.                //
//                                                           //
    else {
    //Reset estateCount
    estateCount = 0;
    printf("Testing another estate card was obtained/current still on hand\n");
    //Make sure there is 1 estate cards
    for (i = 0; i < gState.handCount[0]; i++){
       if (gState.hand[0][i] == ESTATENUMBER){
            estateCount++;
            }
        }
    passOrFail += conditionTester(estateCount == 1);

    //Testing that players hand size is 4
    printf("Testing if hand size is cardsHeld - 1\n");
    passOrFail += conditionTester((testState.handCount[0] == gState.handCount[0]) && (gState.handCount[0] == (cardsHeld - 1)));

    ////Test that the player received 0 gold
    printf("Testing that the player has 0 coins\n");
    passOrFail += conditionTester((testState.coins == gState.coins) && (gState.coins == 0));

    //Testing that the discount pile should be 1
    printf("Testing that the discount pile is equal to 1\n");
    passOrFail += conditionTester(((testState.discardCount[0] + 1) == gState.discardCount[0]) && (gState.discardCount[0] == 1));
    }

    //Make sure there is 1 estate card in the discard pile
    estateCount = 0;
    printf("Testing the discard pile contains 1 estate\n");
    for (i = 0; i < gState.discardCount[0]; i++){
        if (gState.discard[0][i] == BARONNUMBER){
            estateCount++;
            }
        }
    passOrFail += conditionTester(estateCount == 1);

    return passOrFail;
}

//                                                          //
//  Test player state with "Greater than 0" estate cards    //
//                                                          //
int zeroEstateBaron(int cardsHeld, int seed, int playerCount, int des, int passOrFail){
    struct gameState gState, testState;
    //Iniitalize gameState object with set infomation 
    initializeGame(playerCount, kingCards, seed, &gState);
    gState.handCount[0] = cardsHeld;
    //Indexes 0 - 4 are barons. No estate cards are available
    int i;
    for(i = 0; i < gState.handCount[0]; i++)
        gState.hand[0][i] = baron;
    
    //Copy the game state and player cards **Taken from cardtest4.c from instructor handout**
    memcpy(&testState, &gState, sizeof(struct gameState));
//                                                          //
//  Begin Testing Stages  (ONLY TESTING caseBaron)          //
//                                                          //
    //Pass in the index of the baron card, the deision, and the gamestate NEED EXTRA 0'S
    //AT THE 3RD AND 4TH POSITION FOR FUNCTION TO WORK. THEY ARE NOT USED IN 
    //BARON FUNCTION
    playCard(BARONINDEX, des, 0, 0, &gState);  

        //Testing that numBuys was incremented by 1 from previous state
    printf("Testing if number of buys was incremented by 1 \n");
    passOrFail += conditionTester(((testState.numBuys + 1) == gState.numBuys) && (gState.numBuys == 2));
    
    int estateCount = 0;
//                                                              //
//  Player wants to discard the estate card                     //
//  Player is unable to discard estate when no estates on hand  //
    if (des == 1){
    printf("Testing the estate card was discarded\n");
    //Make sure estate is still not in hand
    for (i = 0; i < gState.handCount[0]; i++){
        if (gState.hand[0][i] == ESTATENUMBER){
            estateCount++;
            }
        }
    passOrFail += conditionTester(estateCount == 0);

    //Testing that players hand size is cardsHeld
    printf("Testing if hand size is cardsHeld\n");
    passOrFail += conditionTester((testState.handCount[0] == gState.handCount[0]) && (gState.handCount[0] == cardsHeld));

    ////Test that the player received 0 gold
    printf("Testing that the player has 0 coins\n");
    passOrFail += conditionTester((testState.coins == gState.coins) && (gState.coins == 0));
    }
//                                                           //
//  Player wants another estate card.                        //
//  Player should have 1 estate card in hand.                //
//                                                           //
    else {
    //Reset estateCount
    printf("Testing the estate card was discarded\n");
    //Make sure estate is still not in hand
    for (i = 0; i < gState.handCount[0]; i++){
        if (gState.hand[0][i] == ESTATENUMBER){
            estateCount++;
            }
        }
    passOrFail += conditionTester(estateCount == 0);

    //Testing that players hand size is 5
    printf("Testing if hand size is cardsHeld\n");
    passOrFail += conditionTester((testState.handCount[0] == gState.handCount[0]) && (gState.handCount[0] == cardsHeld));

    ////Test that the player received 0 gold
    printf("Testing that the player has 0 coins\n");
    passOrFail += conditionTester((testState.coins == gState.coins) && (gState.coins == 0));
    }

    //Testing that the discount pile should be 1
    printf("Testing that the discount pile is equal to 1\n");
    passOrFail += conditionTester(((testState.discardCount[0] + 1) == gState.discardCount[0]) && (gState.discardCount[0] == 1));

    //Make sure there is 1 estate card in the discard pile
    estateCount = 0;
    printf("Testing the discard pile contains 1 estate\n");
    for (i = 0; i < gState.discardCount[0]; i++){
        if (gState.discard[0][i] == ESTATENUMBER){
            estateCount++;
            }
        }
    passOrFail += conditionTester(estateCount == 1);

    return passOrFail;

}
int main (){ 
    int des, passOrFail, cardsHeld, seed, playerCount;
    //Number of randomly selected rotations
    int rotations = 1500;
    passOrFail = 0;

    int i;
    for(i = 0; i < rotations; i++){
    printf("***TESTING ROTATION # %d***\n", i + 1);
    seed = rand() % 1000 + 1;
    des = rand () % 2;
    cardsHeld = rand() % 5 + 2;
    playerCount = rand() % 3 + 1;
    //Try function with estate card (both choices) and baron card (both choices)
        passOrFail += oneEstateBaron(cardsHeld, seed, playerCount, des, 0);
        passOrFail += zeroEstateBaron(cardsHeld, seed, playerCount, des, 0);
    }
    //Conclusion of baron function
        if (passOrFail == 0)
            printf("**OVERALL CONSENSUS = PASS**\n");
        else 
            printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}
