/*------------------------------------------*---------------------------------
   CS420 Earthquake analysis
-----------------------------------------------------------------------------*/
/*=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "equake.h"
/*=======================================================*/

/*int main(int argc, char *argv[])
{
	region_header_t *header;
	int numberOfRegions;
	int *dailyTotals, *magnitudeTotals, *depthTotals;
	if (argc == 3) {
		header = readData(argv[1], &numberOfRegions); //first argument is input file name
        printf("Read %d regions successfully.\n", numOfRegions);
		printSummary(header, argv[2]); //second argument is output/summary file name

		//we know the number of regions, create enough space for the arrays we want
		dailyTotals = (int *)(calloc(numberOfRegions*MAX_DAYS,sizeof(int)));
		buildDailyTotalsArray(header, (int (*)[])dailyTotals); 
		printDailyTotals((int (*)[])dailyTotals, header, numberOfRegions);
	
		magnitudeTotals = (int *)(calloc(numberOfRegions*MAX_COLS,sizeof(int)));
		buildMagnitudeTotalsArray(header, (int (*)[])magnitudeTotals); 
		printMagnitudeTotals((int (*)[])magnitudeTotals, header, numberOfRegions);
		
		depthTotals = (int *)(calloc(numberOfRegions*(MAX_COLS+1),sizeof(int)));
		buildDepthTotalsArray(header, (int (*)[])depthTotals); 		
		printDepthTotals((int (*)[])depthTotals, header, numberOfRegions);
		
		cleanUp(header, dailyTotals, magnitudeTotals, depthTotals);
	}
	else {
		fprintf(stderr, "Incorrect number of arguments\n");
		exit(-1);
	}
	return(0);
} */

int main(int argc, char *argv[]) {
    int numOfRegions;
    region_header_t *head = readData(argv[1], &numOfRegions);
    if (head != NULL) {
        printf("Read %d regions successfully.\n", numOfRegions);
        printf("Printing data:\n");
    } else {
        printf("Failed to read data from file.\n");
    }
    return 0;
}


