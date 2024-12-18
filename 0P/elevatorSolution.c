#include <stdio.h>
#define MAX 1000

int main(void) {
 
  int total_weight = 0, weight, proposed_weight = 0;
  while (proposed_weight < MAX) {
    printf("Please give the proposed weight: ");
    scanf("\n%d", &weight);
    proposed_weight = total_weight + weight;
    if (proposed_weight < MAX) {
        total_weight = proposed_weight;
        printf("new = %4d total = %4d\n", weight, total_weight);
    }
    else {
        printf("Not allowed. This will give a total weight of %d.\n", total_weight + weight);
    }
  }
}
