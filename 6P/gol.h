#define ROW 25
#define COL 25
#define DEATHS 1
#define BIRTHS 2
#define ITERRARIONS 3

typedef struct {
    int births;
    int deaths;
    int iterations;
    int organism; // 1 for existed organism in a cell and 0 for none

}GridCell;

//Function return value: count of organisms alive
int initializeGrid(char [], GridCell [][25], int *); // (input arguments: filename, array of structures, output argument: size of row/column)

void printGrid(GridCell [][25], int, int, int); // (input arguments: array of structures, size of row/column, generation count, total organisms alive)

//Function return value: count of organisms alive
int computeNextGeneration(GridCell [][25] , GridCell [][25], int); // (input arguments: array of structures for current generation, array of structures for next generation, size of row/column)
void getCellStatistics(GridCell [][25], int, int, int *, int *, int *);
void printStatistics(GridCell [][25], int, int);