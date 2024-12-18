#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 6

int main() {
    int numRolls;
    int currentNum;
    int consecutiveCount = 1;
    int maxConsecutiveCounts[MAX_NUM] = {0};
    int i;

    // Initialize the random number generator with the current time
    srand((unsigned)time(NULL));

    // Prompt the user for the number of dice rolls
    do {
        printf("How many times do you want to roll the dice? ");
        scanf("%d", &numRolls);
        if(numRolls < 2) {
            printf("Invalid input. Please enter an integer greater than 1.\n");
        }
    } while(numRolls < 2);

    // Roll the dice for the first time to initialize the lastNum
    int lastNum = (rand() % MAX_NUM) + 1; // Generates a number between 1 and 6
    printf("%d ", lastNum);

    // Roll the dice the specified number of times
    for(i = 2; i <= numRolls; i++) {
        currentNum = (rand() % MAX_NUM) + 1; // Generates a number between 1 and 6
        printf("%d ", currentNum);

        // Check for consecutive numbers using sliding window
        if(currentNum == lastNum) {
            consecutiveCount++;
        } else {
            if(consecutiveCount > maxConsecutiveCounts[lastNum - 1]) {
                maxConsecutiveCounts[lastNum - 1] = consecutiveCount;
            }
            consecutiveCount = 1; // Reset the count for the new number
        }

        lastNum = currentNum; // Update the last number rolled

        // Wrap the line after every 30 numbers
        if(i % 30 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    // Update the max counts for the last number rolled
    if(consecutiveCount > maxConsecutiveCounts[lastNum - 1]) {
        maxConsecutiveCounts[lastNum - 1] = consecutiveCount;
    }

    // Print the maximum consecutive sequences for each number
    printf("Consecutive Count\n");
    for(i = 0; i < MAX_NUM; i++) {
        printf("%ds: %d\n", i + 1, maxConsecutiveCounts[i]);
    }

    return 0;
}