#include "dataDump.h"


int dataDump(char *filename){
    FILE *file = fopen(filename, "rb");
    int count = 0;
    if (file == NULL) {
        printf("Error opening file");
        return (-1);
    } else {
        int byte;
		byte = getc(file);
		while (byte != EOF) {
			if (count % 16 == 0)
			{
				if (count != 0)
					printf("\n");
				printf("%08d", count);
			}
			count++;
			printf(" %02x", byte);
			byte = getc(file);
			}
		printf("\n%08d\n", count);
		fclose(file);
    }
    return count;
}