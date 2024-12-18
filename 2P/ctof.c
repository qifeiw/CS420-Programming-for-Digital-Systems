/**
 * CS420 Program 2 - 
 * @Author Qifei Wang
 * @Version 1
*/
#include <stdio.h>
#include <math.h>

#define A1 35.74
#define A2 0.6215
#define A3 35.75
#define A4 0.4275
#define C1 -42.379
#define C2 2.04901523
#define C3 10.14333127
#define C4 -0.22475541
#define C5 -6.83783e-3
#define C6 -5.481717e-2
#define C7 1.22874e-3
#define C8 8.5282e-4
#define C9 -1.99e-6

int main() {
    int lower;
    int upper;
    printf("This program converts temperature values from Celsius to Fahrenheit and also factors in Wind Chill and Heat Index at the appropriate temperatures\n");
    printf("\n");

    // input validation for temperature range
    do {
        printf("Pleaser enter the range of temperature values (in Celsius between -20 and 50) to be converted:\n");
        scanf("\n%d %d", &lower, &upper);
    } while (lower < -20 || upper > 50 || lower >= upper);
    printf("Input temperature range: %d to %d\n", lower, upper);
    printf("\nCelsius to Fahrenheit with Wind Chill Factors\n");
    printf("Celsius\tFahrenheit\t5mph\t10mph\t15mph\t20mph\t25mph\t30mph\t35mph\t40mph\n");
    printf("-------------------------------------------------------------------------------------\n");

// loop for wind chill table
for (int tempC = lower; tempC <= upper; tempC++) {
    double tempF = (double) (tempC * 9.00) / 5.00 + 32;
    printf("%7d\t%11.2f", tempC, tempF);
    for (int speed = 5; speed <=40; speed +=5){
        if (tempF <=50) {
            double tempChill = A1 + A2 * tempF - A3 * pow(speed, 0.16) + A4 * tempF * pow(speed, 0.16);
            printf("\t%.2f", tempChill);
        } else {
            printf("\t   X");
        }
    }
    printf("\n"); 
    printf("-------------------------------------------------------------------------------------\n");
}

printf("\n Celsius to Fahreheit with Heat Index Factor\n");
printf("Celsius\tFahrenheit\t40%%\t50%%\t60%%\t70%%\t80%%\t90%%\t100%%\n");
printf("-------------------------------------------------------------------------------------\n");
for (int tempC = lower; tempC <= upper; tempC++) {
    double tempF = (double) (tempC * 9.00) / 5.00 + 32;
    printf("%7d\t%11.2f", tempC, tempF);
    for (int humidility = 40; humidility <= 100; humidility +=10) {
        if (tempF >= 80) {
            double tempHumid = C1 + C2 * tempF + C3 * humidility + C4 * tempF * humidility + C5 * pow(tempF,2) + C6 * pow(humidility,2) + C7 * tempF * tempF * humidility + C8 * tempF * pow(humidility,2) + C9 * pow(tempF,2) * pow(humidility,2);
            printf("\t%.2f", tempHumid);
        } else {
            printf("\t    X");
        }
    }
    printf("\n");
    printf("-------------------------------------------------------------------------------------\n");

}
}