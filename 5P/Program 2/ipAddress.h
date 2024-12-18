#define MAX_RECORDS 100
typedef struct {
    char ipAddressDot[16];
    char subnetMaskDot[16];
    unsigned int ipAddress;
    unsigned int subnetMask;
    char networkClass;
    int totalSubnets;
    int totalHosts;
} ipInfo_t;

//functions prototype
int readData(char [], ipInfo_t []);
void computeValues(ipInfo_t [], int);
void printResults(char [], ipInfo_t [], int);