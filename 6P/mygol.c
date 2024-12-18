#include <stdio.h>
#include "gol.h"

int main() {
    GridCell Cell1[25][25], Cell2[25][25]; // Two grids to hold the state of the game
    int size;
    int total_Organism;
    const char* fileName = "in1.txt"; // The name of your input file

    // Initialize the grid with values from the file
    total_Organism = initializeGrid(fileName, Cell1, &size);
    if (size == 0) {
        printf("Failed to initialize the grid.\n");
        return 1;
    }

    // Print initial state
    printf("Initial Game State:\n");
    printGrid(Cell1, size, 0, total_Organism);

    // Run a few generations
    for (int i = 1; i <= 5; i++) {
        total_Organism = computeNextGeneration(Cell1, Cell2, size); // Compute next generation
        printf("Generation %d:\n", i);
        printGrid(Cell2, size, i, total_Organism);
        // Copy Cell2 back to Cell1 for next generation
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                Cell1[j][k] = Cell2[j][k];
            }
        }
    }

    // Print statistics for a specific cell
    int deaths, births, iterations;
    int row = 5, col = 5; // Change these values based on specific cells you want to check
    getCellStatistics(Cell1, row, col, &deaths, &births, &iterations);
    printf("Statistics for cell (%d, %d): Deaths = %d, Births = %d, Iterations = %d\n", row, col, deaths, births, iterations);

    return 0;
}