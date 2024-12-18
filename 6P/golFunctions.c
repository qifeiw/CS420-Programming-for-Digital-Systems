#include <stdio.h>
#include "gol.h"
//Author: Qifei Wang
//Version 1

//returns count of organisms alive 
int initializeGrid(char fileName[], GridCell Cell[][25], int *size) {
    int gridSize;
    int count = 0;
    FILE *filep = fopen(fileName, "r");
    if (filep != NULL) {
        fscanf(filep, "%d", &gridSize);
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                fscanf(filep, "%d", &Cell[i][j].organism);
                if (Cell[i][j].organism) {
                    Cell[i][j].iterations = 1;
                    count++;
                } else {
                    Cell[i][j].iterations = 0;
                }
                Cell[i][j].deaths = 0;
                Cell[i][j].births = 0;
            }
        }
        fclose(filep);
    }
    *size = gridSize;
    return (count);
}

void printGrid(GridCell Cell[][25], int size, int count_Generation, int total_Organism) {
    printf("\n\n    #### Generation %d #### Total Organisms: %d ####", count_Generation, total_Organism);
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int l = 0; l <= (size*4)+size; l++) {
            printf("-");
        }
        printf("\n");
        printf("|");
        for (int j = 0; j < size; j++) {
            if (Cell[i][j].organism == 1) {
                printf("  X |");
            } else {
                printf("    |");
            }
        }
        printf("\n");
    }
    for (int l = 0; l <= (size*4)+size; l++) {
        printf("-");
    }
    printf("\n");

}

int computeNextGeneration(GridCell Cell1[][25] , GridCell Cell2[][25], int size) {
    int count = 0; // initialize count of live organisms
    int neighborNum;
    char N, E, W, S, SW, SE, NE, NW;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Cell2[i][j] = Cell1[i][j]; // copy Cell1 to Cell2
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            N = E = W = S = SW = SE = NE = NW =0;
            neighborNum = 0;
            if (i == 0 || j == 0 || i == size -1 || j == size -1) {
                ;// don't compute
            } else {
                N = Cell1[i-1][j].organism;
                E = Cell1[i][j+1].organism;
                S = Cell1[i+1][j].organism;
                W = Cell1[i][j-1].organism;
                SW = Cell1[i+1][j-1].organism;
                SE = Cell1[i+1][j+1].organism;
                NE = Cell1[i-1][j+1].organism;
                NW = Cell1[i-1][j-1].organism;
                neighborNum = N + E + S + W + SW + SE + NE + NW;
            }
            if (neighborNum > 3) {
                Cell2[i][j].organism = 0; //death occured
                if (Cell1[i][j].organism == 1) {
                    Cell2[i][j].deaths++;
                }
            }
            if (neighborNum == 3) {
                Cell2[i][j].organism = 1;
                if (Cell1[i][j].organism == 0) {
                    Cell2[i][j].births++;
                }
                Cell2[i][j].iterations++;
            }
            if (neighborNum == 2) {
                Cell2[i][j].organism = Cell1[i][j].organism;
                if (Cell1[i][j].organism == 1) {
                    Cell2[i][j].iterations++;
                }
            }
            if (neighborNum < 2) {
                Cell2[i][j].organism = 0;
                if (Cell1[i][j].organism == 1) {
                    Cell2[i][j].deaths++;
                }
            }
        }
    }
    // count live organisms
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (Cell2[i][j].organism == 1) {
                count++;
            }
        }
    }
    // copy new grid to old grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Cell1[i][j] = Cell2[i][j];
        }
    }
    return (count);
}


/*int computeNextGeneration(GridCell Cell1[][25], GridCell Cell2[][25], int size) {
    int count = 0; // initialize count of live organisms
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int neighborNum = 0;
            // Check all eight possible neighbors
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue; // skip the cell itself
                    int ni = i + di, nj = j + dj;
                    // Check boundaries
                    if (ni >= 0 && ni < size && nj >= 0 && nj < size) {
                        neighborNum += Cell1[ni][nj].organism;
                    }
                }
            }

            // Apply rules of the game
            if (Cell1[i][j].organism == 1 && (neighborNum < 2 || neighborNum > 3)) {
                Cell2[i][j].organism = 0; // Cell dies
                Cell2[i][j].deaths++;
            } else if (Cell1[i][j].organism == 0 && neighborNum == 3) {
                Cell2[i][j].organism = 1; // Cell becomes alive
                Cell2[i][j].births++;
            } else {
                Cell2[i][j].organism = Cell1[i][j].organism; // Stays the same
            }

            if (Cell2[i][j].organism == 1) {
                count++; // Count live cells
                Cell2[i][j].iterations++;
            }
        }
    }

    // Copy new grid to old grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Cell1[i][j] = Cell2[i][j];
        }
    }

    return count;
}
*/
void getCellStatistics(GridCell Cell[][25], int row, int col, int *deaths, int *births, int *iterations) {
    *deaths = Cell[row][col].deaths;
    *births = Cell[row][col].births;
    *iterations = Cell[row][col].iterations;
}
void printStatistics(GridCell Cell[][COL], int size, int stat) {
	if(stat == DEATHS)
		printf("\n\n    #### Final Death Statistics ####");
	else if (stat == BIRTHS)
		printf("\n\n    #### Final Birth Statistics ####");
	else
		printf("\n\n    #### Final Iteration Statistics ####");		

    printf("\n");

    for (int i=0; i < size; i++) {
		for (int l=0; l<=(size*4)+size; l++)
			printf("-");
		printf("\n");

        printf("|");

        for (int j=0; j<size; j++) {
			switch(stat) {
				case DEATHS:
					printf(" %2d |", Cell[i][j].deaths);
					break;
				case BIRTHS:
					printf(" %2d |", Cell[i][j].births);
					break;
				case ITERRARIONS:
					printf(" %2d |", Cell[i][j].iterations);
					break;
			}
        }

        printf("\n");

    }
   	for (int l=0; l<=(size*4)+size; l++)
		printf("-");
	printf("\n");
    
}