/**
 * @Author: Qifei Wang
 * @Description: CS420 1P. Roll a 6-sided die many times and track the largest number of consecutive
   sequences of each number 1 through 6.
*/

#include <stdio.h>
#include <stdlib.h>

int main (void) {

    int rollTimes;
    int currentNumber;
    int consecutiveCount = 1;
    int maxConsecutiveCount[6] = {0};
    int i;

    do {
        printf("How many times do you want to roll the dice?");
        scanf("\n%d", &rollTimes);
        if (rollTimes < 2) {
            printf("\nInvalid input. Please enter an integer greater than 2.\n");
        }
    } while(rollTimes < 2);

    //get the first random number
    int lastNum = 1 + rand()%6;
        printf("%d ", lastNum);

    // get the rest random numer
    for (int i = 2; i <= rollTimes; i++) {
        currentNumber = 1 + rand()%6 ; 
        printf("%d ", currentNumber);

        // using sliding window to check consecutive numbers
        if (currentNumber == lastNum) {
            consecutiveCount++;
        } else {
            if (consecutiveCount > maxConsecutiveCount[lastNum-1]) {
                maxConsecutiveCount[lastNum-1] = consecutiveCount;
            }
            consecutiveCount = 1;
        }
        lastNum = currentNumber;
        
        if (i%30 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    //update the max counts for the last number rolled
    if (consecutiveCount > maxConsecutiveCount[lastNum-1]) {
        maxConsecutiveCount[lastNum-1] = consecutiveCount;
    }
    
   //print the max consecutives for each number
     printf("Consecutive Count\n");
    for(i = 0; i < 6; i++) {
        printf("%ds: %d\n", i+1, maxConsecutiveCount[i]);
    }

    return 0;
}