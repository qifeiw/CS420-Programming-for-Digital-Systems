#include "stats.h"

int read_data(char *filename, char player[], int field_goals[], int three_pts[], int free_throws[])
{
int n = 0;
int status = 0;
FILE *fptr;
fptr = fopen(filename,"r");
if (fptr != NULL) {
    fscanf(fptr, "%s", player);
    while (n < MAXIMUM && (status = fscanf(fptr, "%d%d%d", &field_goals[n], &three_pts[n], &free_throws[n])) != EOF) {
        n++;
    }
    fclose(fptr);
}
return n;
}

float compute_stats(int field_goals[], int three_pts[], int free_throws[], int size, float *avg_fg, float *avg_tpt, float *avg_ft)
{
    int total_fg = 0;
    int total_tpt = 0;
    int total_ft = 0;
    float average_pts;
    for (int i =0; i < size; i++) {
        total_fg += field_goals[i];
        total_tpt += three_pts[i];
        total_ft += free_throws[i];
    }
    *avg_fg = 1.0 * total_fg / size;
    *avg_tpt = 1.0 * total_tpt / size;
    *avg_ft = 1.0 * total_ft / size;
    average_pts = (*avg_fg *2.0 + *avg_tpt *3.0 + *avg_ft *1.0) /size;
    return (average_pts);
}