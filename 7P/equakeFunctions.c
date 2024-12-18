#include "equake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Qifei Wang
 * @version 1
*/
//Notes from class for readData function
/*open filename
    if (success) {
        read region_file_name
        open region_file name
            if (success) {
                //loop until end of the file
                create region_header_node
                fill it up
            }
    } */
region_header_t *readData(char *fileName, int *numOfRegions) {
    FILE *filep;
    *numOfRegions = 0;
    region_header_t *region_header;
    region_header_t *head = NULL;
    int totalRegionNum = 0;
    filep = fopen(fileName, "r");
    if (filep != NULL) {
        int status;
        char regionName[10];
        while ((status = fscanf(filep, "%s", regionName)) != EOF) {
            region_header = (region_header_t *)malloc(sizeof(region_header_t));
            region_header->region_name = (char *)malloc(sizeof(char) *(strlen(regionName) + 1));
            totalRegionNum += strlen(regionName) + 1;
            strcpy(region_header->region_name, regionName);
            region_header->data = NULL;
            region_header->next = NULL;
            if (head == NULL) {
                head = region_header;
                printf("Inserted %s as head.", region_header->region_name);
            } else {
                region_header_t *curr = head;
                int done = 0;
                while (!done) {
                    if (curr->next == NULL) {
                        curr->next = region_header;
                        done = 0;
                    } else {
                        curr = curr->next;
                    }
                }
            }

            // fill the data
            FILE *data_filep;
            data_filep = fopen(regionName, "r");
            if (data_filep != NULL) {
                int count = 0;
                int Day, Year, Month;
                char Times[12];
                float Magnitude, Latitude, Longtitude, Depth;
                char Location[100];
                equake_data_t *node;
                while ((fscanf(data_filep, "%d%d%d%s%f%f%f%f%s", &Year, &Month, &Day, Times, &Latitude, &Longtitude, &Magnitude, &Depth, Location) !=EOF)) {
                    node = (equake_data_t *)malloc(sizeof(equake_data_t));
                    node->year = Year;
                    node->month = Month;
                    node->day = Day;
                    node->timeOfQuake = (char *)malloc(sizeof(char) * (strlen(Times) + 1));
                    strcpy(node->timeOfQuake, Times);
                    node->latitude = Latitude;
                    node->longitude = Longtitude;
                    node->magnitude = Magnitude;
                    node->depth = Depth;
                    node->location = (char *)malloc(sizeof(char) * (strlen(Location) + 1));
                    strcpy(node->location, Location);
                    node->next = NULL;
                    if (region_header->data == NULL) {
                        region_header->data = node;
                    } else {
                        equake_data_t *temp_node = node;
                        int found = 0;
                        while (!found) {
                            if (temp_node->next == NULL) {
                                temp_node->next = node;
                                found = 1;
                            } else {
                                temp_node = temp_node->next;
                            }
                        }
                    }
                    count++;
                    
                }
                fclose(data_filep);
            }
            *numOfRegions +=1;
        } 
    } else {
        return NULL;
    }
    fclose(filep);
    return head;
} 

int printSummary(region_header_t *header, char *output_filename) {
    
}

void buildDailyTotalsArray(region_header_t *header, int monthStats[][MAX_DAYS]) {

}
void printDailyTotals(int dailyTotals[][MAX_DAYS], region_header_t *header, int regions) {

}
void buildMagnitudeTotalsArray(region_header_t *header, int magStats[][MAX_COLS]) {

}
void printMagnitudeTotals(int magTotals[][MAX_COLS], region_header_t *header, int regions) {

}
void buildDepthTotalsArray(region_header_t *header, int depthStats[][MAX_COLS+1]) {

}
void printDepthTotals(int depthTotals[][MAX_COLS+1], region_header_t *header, int regions) {

}
void cleanUp(region_header_t *header, int *dailyTotals, int *magTotals, int *depthTotals) {

}




