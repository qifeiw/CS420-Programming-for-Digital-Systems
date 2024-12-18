/*------------------------------------------*---------------------------------
   CS420 Earthquake analysis
-----------------------------------------------------------------------------*/
/*=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equake.h"
/*=======================================================*/

//#define DEBUG 1

region_header_t * readData(char *filename, int *regions) {
	region_header_t *global_header = NULL;
	region_header_t *r_header;
	FILE *fp;
	*regions = 0;
	int names_total = 0;
	fp = fopen(filename, "r");
	if (fp != NULL) {
		char fname[30];
		int status;
		while((status = fscanf(fp, "%s", fname)) != EOF) {
			r_header = (region_header_t *) malloc(sizeof(region_header_t));
			r_header->region_name = (char *)malloc(sizeof(char) * (strlen(fname)+1));
			names_total += strlen(fname) + 1; //just keep track of total characters for filenames for later
			strcpy(r_header->region_name, fname);
			r_header->data = NULL;
			r_header->next = NULL;
			if(global_header == NULL) {
				global_header = r_header;
#ifdef DEBUG
				printf("inserted %s as header\n", r_header->region_name);
#endif
			}
			else {
				region_header_t *temp = global_header;
				int done = 0;
				while(!done) {
					if(temp->next == NULL) {
						temp->next = r_header;
#ifdef DEBUG
						printf("inserted %s after %s\n", r_header->region_name, temp->region_name);
#endif
						done = 1;
					}
					else
						temp = temp->next;
				}
			}
			/* Now open the actual data file containing quake data */
			/* and set up the data link list */
			FILE *data_fp;
			data_fp = fopen(fname, "r");
			if (data_fp != NULL) {
				int count = 0;
				int day, month, year;
				char timestamp[12];
				char location[120];
				float magnitude, depth, latitude, longitude;
				equake_data_t *data_node;
				while((fscanf(data_fp, "%d%d%d%s%f%f%f%f%s", &year, &month, \
						&day, timestamp, &latitude, &longitude, &magnitude, \
						&depth, location) != EOF) ) {
					data_node = (equake_data_t *) malloc(sizeof(equake_data_t));
					data_node->year = year;
					data_node->month = month;
					data_node->day = day;
					data_node->timeOfQuake = (char *)malloc(sizeof(char)*(strlen(timestamp)+1));
					strcpy(data_node->timeOfQuake, timestamp);
					data_node->magnitude = magnitude;
					data_node->depth = depth;
					data_node->latitude = latitude;
					data_node->longitude = longitude;
					data_node->location = (char *)malloc(sizeof(char)*(strlen(location)+1));				
					strcpy(data_node->location, location);
					data_node->next = NULL;
					if(r_header->data == NULL)
						r_header->data = data_node;
					else {
						equake_data_t *temp_data = r_header->data;
						int found = 0;
						while(!found) {
							if(temp_data->next == NULL) {
								temp_data->next = data_node;
								found = 1;
							}
							else
								temp_data = temp_data->next;
						}
					}
					count++;
				}
#ifdef DEBUG
				//printf("%s %d\n", r_header->region_name, count);
#endif			
				fclose(data_fp);
			}
			*regions += 1;
		}
	}
	else
		return(NULL);
	fclose(fp);
		
	return(global_header);
}

static void printOneRegionSummary(char *region_name, equake_data_t *data, FILE *outp) {
	/* File already open, just start writing */
	
	float min_lat, max_lat, min_long, max_long, min_depth, max_depth;
	float min_mag, max_mag;
	int max_mag_year, max_mag_month, max_mag_day;
	char max_mag_time[12], max_mag_location[120];
	int quake_total = 1;
	
	min_lat = data->latitude;
	min_long = data->longitude;
	max_lat = data->latitude;
	max_long = data->longitude;
	min_depth = data->depth;
	max_depth = data->depth;
	min_mag = data->magnitude;
	max_mag = data->magnitude;

	max_mag_year = data->year;
	max_mag_month = data->month;
	max_mag_day = data->day;
	strcpy(max_mag_time, data->timeOfQuake);
	strcpy(max_mag_location, data->location);
	
#ifdef DEBUG
	fprintf(stdout, "*************************************************************************************\n");
	fprintf(stdout, "EARTHQUAKE SUMMARY FROM DATA FILE: %s\n", e_regions);
#endif
	/* Write the summary heading to the output file */
	fprintf(outp, "*************************************************************************************\n");
	fprintf(outp, "EARTHQUAKE SUMMARY FROM DATA FILE: %s\n", region_name);
	equake_data_t *temp = data->next;
	while(temp != NULL) {
		quake_total++;
		if (temp->latitude < min_lat)
			min_lat = temp->latitude;
		if (temp->latitude > max_lat)
			max_lat = temp->latitude;
		if (temp->longitude < min_long)
			min_long = temp->longitude;
		if (temp->longitude > max_long)
			max_long = temp->longitude;
		if (temp->magnitude < min_mag)
			min_mag = temp->magnitude;
		if (temp->magnitude > max_mag) {
			max_mag = temp->magnitude;
			max_mag_year = temp->year;
			max_mag_month = temp->month;
			max_mag_day = temp->day;
			strcpy(max_mag_time, temp->timeOfQuake);
			strcpy(max_mag_location, temp->location);
		}
		if (temp->depth < min_depth)
			min_depth = temp->depth;
		if (temp->depth > max_depth)
			max_depth = temp->depth;
		temp = temp->next;

	}
#ifdef DEBUG
	fprintf(stdout, "Geographical Range: Latitudes %f to %f, Longitudes %f to %f\n", min_lat, max_lat, min_long, max_long);
	fprintf(stdout, "Total Number of Earthquakes recorded: %d\n", quake_total);
	fprintf(stdout, "Depth Range (Kilometers): %f to %f\n", min_depth, max_depth);
	fprintf(stdout, "Magnitude Range: %3.1f to %3.1f\n", min_mag, max_mag);
	fprintf(stdout, "Largest magnitude of %3.1f occured on %d/%d/%d %s at: %s\n\n", max_mag, \
		max_mag_month, max_mag_day, max_mag_year, \
		max_mag_time, max_mag_location);
#endif

	fprintf(outp, "Geographical Range: Latitudes %f to %f, Longitudes %f to %f\n", min_lat, max_lat, min_long, max_long);
	fprintf(outp, "Total Number of Earthquakes recorded: %d\n", quake_total);
	fprintf(outp, "Depth Range (Kilometers): %f to %f\n", min_depth, max_depth);
	fprintf(outp, "Magnitude Range: %3.1f to %3.1f\n", min_mag, max_mag);
	fprintf(outp, "Largest magnitude of %3.1f occured on %d/%d/%d %s at: %s\n\n", max_mag, \
		max_mag_month, max_mag_day, max_mag_year, \
		max_mag_time, max_mag_location);
}

int printSummary(region_header_t *header, char *output_filename) {
	FILE *fp;
	fp = fopen(output_filename, "w");
	if (fp != NULL) {
		region_header_t *region = header;
		while(region != NULL) {
			printOneRegionSummary(region->region_name, region->data, fp);
#ifdef DEBUG
			printf("%s\n", region->region_name);
#endif
			region = region->next;
		}
		fclose(fp);
		return(1);
	}
	return(0);
}

void buildDailyTotalsArray(region_header_t *header, int monthStats[][MAX_DAYS]){
	region_header_t *region = header;
	int i = 0;	//start at row 0 for first region
	while(region != NULL) {
		equake_data_t *data = region->data;
		while(data != NULL) {
			/* Now fill up the monthStats array (quake totals for the month) as we go along */
			monthStats[i][data->day - 1] += 1;			
			data = data->next;
		}
		region = region->next;
		i++; //increment row index
	}
}

void printDailyTotals(int dailyTotals[][MAX_DAYS], region_header_t *header, int regions) {
	int i, j;
	printf("******************************************************EARTHQUAKE TOTALS FOR THE MONTH BY REGION***************************************************\n");
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("%20s|","");
	for(i=0; i<MAX_DAYS; i++)
		printf("%4d", i+1);
	printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------\n");
	region_header_t *temp = header;
	for(j=0; j<regions; j++) {
		printf("%20s|", temp->region_name);
		for(i=0; i<MAX_DAYS; i++)
			printf("%4d", dailyTotals[j][i]);
		printf("\n");
		printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
		temp = temp->next;
	}
	printf("***************************************************************************************************************************************************\n");

}

void buildMagnitudeTotalsArray(region_header_t *header, int magStats[][MAX_COLS]){
	region_header_t *region = header;
	int i = 0;	//start at row 0 for first region
	while(region != NULL) {
		equake_data_t *data = region->data;
		while(data != NULL) {
			/* Now fill up the magStats array (magnitude totals for the month as we go along */
			/* Truncate magnitude value to integer, for ex: values > 2 and < 3 will go into col 2 */
			int magColumn = data->magnitude;
			magStats[i][magColumn] += 1;			
			data = data->next;
		}
		region = region->next;
		i++; //increment row index
	}
}

void printMagnitudeTotals(int magTotals[][MAX_COLS], region_header_t *header, int regions) {
	int i, j;
	printf("\n************EARTHQUAKE TOTALS BY MAGNITUDE BY REGION***********\n");
	printf("%20s|Magnitude Range: 0 to 10 (increments of 1)\n","");
	printf("---------------------------------------------------------------\n");
	printf("%20s|","");
	for(i=0; i<MAX_COLS; i++)
		printf("%4d", i);
	printf("\n---------------------------------------------------------------\n");
	region_header_t *temp = header;
	for(j=0; j<regions; j++) {
		printf("%20s|", temp->region_name);
		for(i=0; i<MAX_COLS; i++) {
			printf("%4d", magTotals[j][i]);
		}
		printf("\n");
		printf("---------------------------------------------------------------\n");
		temp = temp->next;
	}
	printf("***************************************************************\n");
}

void buildDepthTotalsArray(region_header_t *header, int depthStats[][MAX_COLS+1]){
	region_header_t *region = header;
	int i = 0;	//start at row 0 for first region
	while(region != NULL) {
		equake_data_t *data = region->data;
		while(data != NULL) {
			/* Now fill up the depthStats array (depth totals for the month as we go along */
			/* Truncate depth value to integer, for ex: values > 2 and < 3 will go into col 2 */
			int depthColumn = data->depth/10;
			if (depthColumn > 10)
				depthColumn = 10; //anything greater than 10 goes into the last column
			depthStats[i][depthColumn] += 1;			
			data = data->next;
		}
		region = region->next;
		i++; //increment row index
	}
}

void printDepthTotals(int depthTotals[][MAX_COLS+1], region_header_t *header, int regions) {
	int i, j;
	printf("\n***************EARTHQUAKE TOTALS BY DEPTH BY REGION****************\n");
	printf("%20s|Depth Range in KM (increments of 10)\n","");
	printf("-------------------------------------------------------------------\n");
	printf("%20s|","");
	for(i=0; i<MAX_COLS+1; i++)
		if (i==MAX_COLS)
			printf("%4d+", i*10);
		else
			printf("%4d", i*10);
	printf("\n-------------------------------------------------------------------\n");
	region_header_t *temp = header;
	for(j=0; j<regions; j++) {
		printf("%20s|", temp->region_name);
		for(i=0; i<MAX_COLS+1; i++) {
			printf("%4d", depthTotals[j][i]);
		}
		printf("\n");
		printf("-------------------------------------------------------------------\n");
		temp = temp->next;
	}
	printf("*******************************************************************\n");
}

void cleanUp(region_header_t *header, int *dailyTotals, int *magTotals, int *depthTotals) {
	region_header_t *region = header;
	region_header_t *temp_region = region;
	equake_data_t *data, *temp_data; 
	while(temp_region != NULL) {
		data = temp_region->data;
		temp_data = data;
		int count = 0;
		while(temp_data != NULL) {
			count++;
			equake_data_t *delete_data;
			delete_data = temp_data;
			temp_data = temp_data->next;
			free(delete_data->timeOfQuake);
			free(delete_data->location);
			free(delete_data);
		}
		region_header_t *delete_region = temp_region;
		temp_region = temp_region->next;
		free(delete_region->region_name);
		free(delete_region);
	}
	free(dailyTotals);
	free(magTotals);
	free(depthTotals);
		
}

