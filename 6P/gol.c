#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

void printGenerations(GridCell Cell[][COL], int size);
void printAllStatistics(GridCell Cell[][COL], int size);

int main(int argc, char *argv[]) {
    int size = 0;
    int count = 0;
    GridCell Cell[ROW][COL];

    // Check for correct usage
    if (argc != 2) {
        printf("Invalid arguments. Usage: %s <input_filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Initialize the grid with the data from the input file
    count = initializeGrid(argv[1], Cell, &size);
    if (count == -1) { 
        printf("Failed to open or read from file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("\n\nWelcome to the Game of Life\n\n\n");
    printGrid(Cell, size, 0, count); // Print initial state

    if (count > 0) {
        printGenerations(Cell, size); // Simulate and print each generation
        printAllStatistics(Cell, size); // Print statistics after all generations
    } else {
        printf("No living organisms to simulate.\n");
    }

    printf("Goodbye\n");
    return 0;
}

void printGenerations(GridCell Cell[][COL], int size) {
    int genNumber = 0;
    int sizes[5] = {0}; 
    GridCell newCell[ROW][COL];
    int count = 0;

    do {
        genNumber++;
        count = computeNextGeneration(Cell, newCell, size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                Cell[i][j] = newCell[i][j]; // Update the main grid with the new state
            }
        }
        printGrid(Cell, size, genNumber, count); // Print current generation
        sizes[genNumber % 5] = count; // Store count to detect stable state
        // Break if the last 5 counts are the same and non-zero, indicating a stable configuration
        if (sizes[0] == sizes[1] && sizes[0] == sizes[2] && sizes[0] == sizes[3] && sizes[0] == sizes[4] && sizes[0] != 0) {
            printf("Stable configuration detected. Simulation will stop.\n");
            break;
        }
    } while (count > 0);
}

void printAllStatistics(GridCell Cell[][COL], int size) {
    printStatistics(Cell, size, DEATHS);
    printStatistics(Cell, size, BIRTHS);
    printStatistics(Cell, size, ITERRARIONS); 
}