#include "ipAddress.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int readData(char fileName[], ipInfo_t ip[]) {
    FILE *inputFile;
    int i = 0;
    int status = 0;
    inputFile = fopen(fileName, "r");
    while((status = fscanf(inputFile, "%s%s\n", ip[i].ipAddressDot, ip[i].subnetMaskDot)) != EOF) {
        i++;

    }
    fclose(inputFile);
    return (i);
}
//count the number of bit 1 for value n
int num_bitOne(int n) {
    int count = 0;
    while (n != 0) {
        n = n & (n -1);
        count++;
    }
    return (count);
}
unsigned int dotToNum(char* dotNotation) {
    int num = 0;
    int octet;
    char* token = strtok((char*)dotNotation, ".");
    while (token != NULL) {
        octet = atoi(token);
        num = (num << 8) + octet;
        token = strtok(NULL, ".");
    }
    return num;
}

char networkClass(unsigned int ipAddress) {
    unsigned int msb = ipAddress >> 24;
     if (msb >= 0 && msb <= 127) { 
        return 'A';
    } else if (msb >= 128 && msb <= 191) { 
        return 'B';
    } else if (msb >= 192 && msb <= 223) {
        return 'C';
    } else {
        return '0'; 
    }
}
  
void computeValues(ipInfo_t ip[], int size) {
    for (int i = 0; i < size; i++) {
        char ipDotCopy[16];
        char subnetDotCopy[16];
        strcpy(ipDotCopy, ip[i].ipAddressDot);
        strcpy(subnetDotCopy, ip[i].subnetMaskDot);
        ip[i].ipAddress = dotToNum(ipDotCopy);
        ip[i].subnetMask = dotToNum(subnetDotCopy);
        ip[i].networkClass = networkClass(ip[i].ipAddress);

         // Determine bits for subnetting and host portions
        /*
        unsigned int hostBitsMask = ~ip[i].subnetMask; // Flip bits to get host portion
        int subnetBits = num_bitOne(ip[i].subnetMask); // Count '1' bits for subnet
        int hostBits = num_bitOne(hostBitsMask); // Count '1' bits for hosts

        // Calculate total subnets - Adjust subnetBits based on class
        if (ip[i].networkClass == 'A') subnetBits -= 8;
        else if (ip[i].networkClass == 'B') subnetBits -= 16;
        else if (ip[i].networkClass == 'C') subnetBits -= 24;

        ip[i].totalSubnets = subnetBits > 0 ? (1 << subnetBits) : 1;
        ip[i].totalHosts = hostBits > 0 ? (1 << hostBits) - 2 : 0; // Subtract 2 for network and broadcast addresses
        */
        char netClass = ip[i].networkClass;
        // Correctly determine the number of subnet bits (s) and host bits (h)
        
        if (netClass == 'A') {
            int n = ip[i].subnetMask & 0xFFFFFF;
            int numOneBits = num_bitOne(n);
            ip[i].totalSubnets = pow(2, numOneBits);
            ip[i].totalHosts = pow(2, 24 - numOneBits) - 2;
        }
        else if (netClass == 'B') {
            int n = ip[i].subnetMask & 0XFFFF;
            int numOneBits = num_bitOne(n);
            ip[i].totalSubnets = pow(2, numOneBits);
            ip[i].totalHosts = pow(2, 16 - numOneBits) - 2;
        } else if (netClass == 'C') {
            int n = ip[i].subnetMask & 0xFF;
            int numOneBits = num_bitOne(n);
            ip[i].totalSubnets = pow(2, numOneBits);
            ip[i].totalHosts = pow(2, 8 - numOneBits) -2;
        }

    }
}
void printResults(char fileName[], ipInfo_t ip[], int size) {
    FILE *outFile = fopen(fileName, "w");
    int i;
    fprintf(outFile, "%20s%13s%20s%13s%8s%8s%8s\n","Octet IP Address", "IP Address", "Octet Subnet Mask", "Subnet Mask", "Class","Subnets","Hosts");
    for (i = 0; i < size; i++) {
        fprintf(outFile, "%20s%5s%08x%20s%5s%08x%8c%8d%8d\n", ip[i].ipAddressDot, " ", ip[i].ipAddress, \
			ip[i].subnetMaskDot, " ", ip[i].subnetMask,  \
			ip[i].networkClass, ip[i].totalSubnets, ip[i].totalHosts);
    }
    fclose(outFile);
}