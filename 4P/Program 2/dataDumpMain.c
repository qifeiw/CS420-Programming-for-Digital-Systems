include "dataDump.h"

int main(int argc, *char argv[]) {
    int size;
    size = dataDump(argv[1]);
    if (size == -1) 
		printf("Invalid file %s\n", argv[1]);
	else
		fprintf(stderr, "Number of bytes: %d\n", size);
	return(0);
}