
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "ipAddress.h"
int main(int argc, char *argv[]) {
    ipInfo_t ip[MAX_RECORDS];
    if (argc < 4) {
        printf("More arguments needed.\n");
        return (-1);
    }
    int size = readData(argv[1], ip);
    int numToPrint = atoi(argv[3]);
	int i = 0;
	if (numToPrint == 1) {
		for(i=0; i<size; i++) {
			printf("%s\t%s\n", ip[i].ipAddressDot, ip[i].subnetMaskDot);
		}	
	}
	
	computeValues(ip, size);
	
	if (numToPrint == 2) {
		for(i=0; i<size; i++) {
			printf("%s\t%08x\t%s\t%08x\t%c\t%d\t%d\n", ip[i].ipAddressDot, ip[i].ipAddress, ip[i].subnetMaskDot, ip[i].subnetMask, \
			ip[i].networkClass, ip[i].totalSubnets, ip[i].totalHosts);
		}
	}
	
	if (numToPrint == 3) {
		printResults(argv[2], ip, size);
	}
	
	return(0);
    
}