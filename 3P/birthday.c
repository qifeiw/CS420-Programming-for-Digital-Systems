#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double birthdayGame(int numberOfTrials, int numberOfPeople, double *monthProbability) {
    if (numberOfTrials <= 0 || numberOfPeople <= 0) {
        *monthProbability = -1;
        return -1;
    }
    srand(time(NULL));
    int dayMatchCount = 0;
    int monthMatchCount = 0;
    for (int i = 0; i < numberOfTrials; i++) {
        int birthDays[365] = {0};
        int birthMonths[12] = {0};
        for (int j = 0; j < numberOfPeople; j++) {
            int birthday = rand() % 365;
            birthDays[birthday]++;
            int birthmonth = birthday / 30;
            birthMonths[birthmonth]++;
            if (birthDays[birthday] == 2) {
            dayMatchCount++;
            break;
        }
        }
        for (int i = 0; i < 12; i++) {
        if(birthMonths[i] >= 2) {
            monthMatchCount++;
            break;
        }
        }

    }
    
    *monthProbability = (double) monthMatchCount / numberOfTrials;
    double dayProbability =(double) dayMatchCount / numberOfTrials;
    return dayProbability;
}
/*
int main() {
    double monthProbability;
    double dayProbability = birthdayGame(100000, 23, &monthProbability);

    printf("Day Probability: %f\\n", dayProbability);
    printf("Month Probability: %f\\n", monthProbability);

    return 0;
}
*/