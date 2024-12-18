#include <stdio.h>
#include <math.h>
/**
 * @Author Qifei Wang
 * CS420 Worksheet W5  -Spring 2024
*/
// definiton of function isPrime
int isPrime(int Num, int *divisor) {
for (*divisor = 2; *divisor <= sqrt(Num); *divisor++) {
    if (Num % *divisor == 0) {
        return 0;  //not prime number
    } 
    return 1;  // prime number
}
}

int main() {
    int div, result, number;
    printf("Please enter the number to check for prime.\n");
    scanf("\n%d", &number);
    result =isPrime(number, &div);
    printf("%d\n",result);
}
