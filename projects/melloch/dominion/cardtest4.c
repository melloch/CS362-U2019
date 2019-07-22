#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Create constant variables for number of cards held in hand and player playing game
const int CARDSHELD = 15;
const int PLAYERCOUNT = 3;
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
int choice(int winner, int passOrFail){
    struct gameState gState;
    //Iniitalize gameState object with set infomation 
    initializeGame(PLAYERCOUNT, kingCards, RANDOMSEED, &gState);
//                                                          //
//  Begin Testing Stages  (ONLY TESTING getWinner function) //
//                                                          //

    int i, j;
    for(i = 0; i < PLAYERCOUNT; i++){
        gState.handCount[i] = CARDSHELD;
        for(j = 0; j < gState.handCount[i]; j++)
                gState.hand[i][j] = ambassador;
    }

    //To pass into getWinner function
    int players[3] = {-1, -1, -1};

    //Set winner with correct card
    if (winner == 0){
        gState.hand[winner][gState.handCount[winner] - 1] = estate;
        gState.hand[winner+1][gState.handCount[winner+1] - 1] = curse;
        gState.hand[winner+2][gState.handCount[winner+2] - 1] = curse;
    }
    else if (winner == 1){
        gState.hand[winner][gState.handCount[winner-1] - 1] = estate;
        gState.hand[winner+1][gState.handCount[winner] - 1] = curse;
        gState.hand[winner+2][gState.handCount[winner+1] - 1] = curse;
    }
    else if (winner == 2){
        gState.hand[winner][gState.handCount[winner-2] - 1] = estate;
        gState.hand[winner+1][gState.handCount[winner-1] - 1] = curse;
        gState.hand[winner+2][gState.handCount[winner] - 1] = curse;
    }
    else{
        gState.hand[0][gState.handCount[0] - 1] = estate;
        gState.hand[1][gState.handCount[1] - 1] = estate;
        gState.hand[2][gState.handCount[1] - 1] = estate;
    }
    
    getWinners(players, &gState);

    if(winner == 0){
        printf("Checking that player 1 is the winner\n");
        passOrFail += conditionTester(players[0] == 1);
        
        printf("Checking that player 2 is not the winner\n");
        passOrFail += conditionTester(players[1] == 0);

        printf("Checking that player 3 is not the winner\n");
        passOrFail += conditionTester(players[2] == 0);
    }
    else if (winner == 1){
        printf("Checking that player 1 is not the winner\n");
        passOrFail += conditionTester(players[0] == 0);
        
        printf("Checking that player 2 is the winner\n");
        passOrFail += conditionTester(players[1] == 1);

        printf("Checking that player 3 is not the winner\n");
        passOrFail += conditionTester(players[2] == 0);
    }
    else if (winner == 2){
        printf("Checking that player 1 is not the winner\n");
        passOrFail += conditionTester(players[0] == 0);
        
        printf("Checking that player 2 is not the winner\n");
        passOrFail += conditionTester(players[1] == 0);

        printf("Checking that player 3 is the winner\n");
        passOrFail += conditionTester(players[2] == 1);
    }
    else{
        printf("Checking that player 1 is not the winner\n");
        passOrFail += conditionTester(players[0] == 1);
        
        printf("Checking that player 2 is not the winner\n");
        passOrFail += conditionTester(players[1] == 1);

        printf("Checking that player 3 is not the winner\n");
        passOrFail += conditionTester(players[2] == 1);
    }
    
return passOrFail;
}
//                                                          //
//  Test card effect                                        //
//                                                          //
int main (){
    int passOrFail = 0;
    int i;
    for(i = 0; i < 4; i++)
        passOrFail += choice(i, 0);

    if (passOrFail == 0)
        printf("**OVERALL CONSENSUS = PASS**\n");
    else 
        printf("**OVERALL CONSENSUS = FAIL**\n");

    return 0;
}
