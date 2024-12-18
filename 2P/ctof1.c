#include <stdio.h>
#include <math.h>

// Simplified heat index formula for demonstration.
double calculateHeatIndex(double temperature, double humidity) {
    return -42.379 + 2.04901523 * temperature + 10.14333127 * humidity - 0.22475541 * temperature * humidity - 6.83783e-3 * pow(temperature, 2) - 5.481717e-2 * pow(humidity, 2) + 1.22874e-3 * pow(temperature, 2) * humidity + 8.5282e-4 * temperature * pow(humidity, 2) - 1.99e-6 * pow(temperature, 2) * pow(humidity, 2);
}

// Wind chill formula as per the assignment's description.
double calculateWindChill(double temperature, double windSpeed) {
    return 35.74 + 0.6215 * temperature - 35.75 * pow(windSpeed, 0.16) + 0.4275 * temperature * pow(windSpeed, 0.16);
}

// Function to convert Celsius to Fahrenheit.
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32;
}

int main() {
    int lower, upper;

    // Input validation for temperature range.
    do {
        printf("Enter the temperature range in Celsius (-20 to 50) as two integers: ");
        scanf("%d %d", &lower, &upper);
    } while (lower < -20 || upper > 50 || lower >= upper);

    printf("\nTemperature Conversion Table from Celsius to Fahrenheit with Wind Chill Factors\n");
    printf("Celsius\tFahrenheit\tWind Speed (mph)\n");
    // Loop for Wind Chill table.
    for (int tempC = lower; tempC <= upper; tempC++) {
        double tempF = celsiusToFahrenheit(tempC);
        printf("%7d\t%11.1f", tempC, tempF);
        for (int speed = 5; speed <= 40; speed += 5) {
            if (tempF <= 50) {
                double chill = calculateWindChill(tempF, speed);
                printf("\t%10.1f", chill);
            } else {
                printf("\t         X");
            }
        }
        printf("\n");
    }

    printf("\nTemperature Conversion Table from Celsius to Fahrenheit with Heat Index Factors\n");
    printf("Celsius\tFahrenheit\tHumidity\n");
    // Loop for Heat Index table.
    for (int tempC = lower; tempC <= upper; tempC++) {
        double tempF = celsiusToFahrenheit(tempC);
        printf("%7d\t%11.1f", tempC, tempF);
        for (int humidity = 40; humidity <= 100; humidity += 10) {
            if (tempF >= 80) {
                double index = calculateHeatIndex(tempF, humidity);
                printf("\t%9.1f", index);
            } else {
                printf("\t         X");
            }
        }
        printf("\n");
    }

    return 0;
}