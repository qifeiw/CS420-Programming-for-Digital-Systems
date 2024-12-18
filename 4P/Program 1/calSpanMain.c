#include "calSpan.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Wrong number of arguments\n");
		return(0);
	}
	double data[atoi(argv[1])];
	int size = calSpan(atoi(argv[1]), argv[2], data);
	if (size == -1)
		printf("Cannot open data file %s\n", argv[2]);
	else {
		printf("\nNumber of data items: %d\n", size);
		
		/
		for(int i=0; i<size; i++) {
			fprintf(stderr, "%lf ", data[i]);
			if(i > 0 && i % 9 == 0) 
				fprintf(stderr, "\n");
		}
		fprintf(stderr,"\n");
	}
	return(0);
}
