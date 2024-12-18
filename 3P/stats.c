#include "stats.h"
// Author: Qifei Wang
// Version 1

int main(int argc, char *argv[]) {
    int totalGames;
    int fieldGoals[MAXIMUM], threePoints[MAXIMUM], freeThrows[MAXIMUM];
    char player[82];
    float average_fieldGoals, average_threePoints, averrage_freeThrows;
    float average_totalPoints;
    if (argc < 2) {
        printf("This program needs at lease 2 arguments.\n");
    } else {
        for (int i = 1; i < argc; i++) {
            totalGames = read_data(argv[i], player, fieldGoals, threePoints, freeThrows);
            if (totalGames != 0) {
                printf("Statistics for: %s\n", player);
                printf("Total games played: %d\n", totalGames);
                average_totalPoints = compute_stats(fieldGoals, threePoints, freeThrows, totalGames, &average_fieldGoals, &average_threePoints, &averrage_freeThrows);
                printf("Season Averages:\nField Goals: %4.2f\t3 Pointers: %4.2f\tFree Throws: %4.2f\n", average_fieldGoals, average_threePoints, averrage_freeThrows);
				printf("Points per game: %4.2f\n\n", average_totalPoints);
            } else {
                printf("Data file %s is empty.\n", argv[i]);
            }
        }
    }
    return 0;
}
