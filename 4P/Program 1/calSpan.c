#include "calSpan.h"
#include <stdio.h>


int calSpan(int maxSize, char *filename, double data[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return (-1); // invalid filename
    }
    int index = 0;
    char line[50];
    while (fscanf(file, "%s", line) != EOF && index < maxSize) {
        if ((data[index] = atof(line)) == 0) {
            data[index] = -101;
        }
        if (data[index] > 100 || data[index] < -100) {
            data[index] = -101;
        }
        index++;
    }
    fclose(file);
    char min_to_query[50] = "";
    while(strcmp(min_to_query, "exist") != 0) {
        int minToQuery = 0;
        printf("\nWhich minute to quety?\n");
        scanf("%s", min_to_query);
        if (strcmp(min_to_query, "exit") == 0) {
            return index;
        }
        minToQuery = atof(min_to_query);
        if (minToQuery <= 0) {
            printf("Wrong input\n");
        } else if (minToQuery >= index) {
            printf("Query out of range\n");
        } else {
            int length = 0;
            double maximum = data[(int)minToQuery];
            if (maximum == -101) {
                printf("Temperature at %d is corrupted", (int)minToQuery);
            } else {
                int isDone = 0;
                int min = (int)minToQuery;
                while (min >= 0 && isDone == 0) {
                    if (data[min] <= maximum) {
                        length++;
                    } else {
                        isDone = 1;
                    }
                    min--;
                }
                printf("Data at minute %d is a %d-minute(s) high\n", (int)minToQuery, length);
            }
        }
    }
    return index;
}