// Name: Qifei Wang
//Assignment: 0P
//Compare the different computing approximation of ellipse circumference

#include <stdio.h>
#include <math.h>
#define PI 3.14159

int main(void) {
 float a,b;
 float ramanujanFirst,ramanujanSecond,muir,hudson,holder,davidCantrell,h;
 printf("Please enter the major axis:");
 scanf("\n%f",&a);
 printf("Please enter the minor axis:");
 scanf("\n%f",&b);

 //ramanujan first approxmiation
 ramanujanFirst = PI*(3*(a + b) - sqrt((3*a + b)*(a+3*b)));

 // ramanujan second approxmiation
 h = pow((a-b),2)/pow((a+b),2);
 ramanujanSecond = PI*(a+b)*(1+(3*h)/(10+sqrt((4-3*h))));


 //Muir's solution
 muir = 2 * PI *pow(((pow(a,1.5)+pow(b,1.5))/2),1/1.5);

 //Hudson's formula
 hudson = 0.25 * PI *(a+b)*(3*(1+h/4)+1/(1-h/4));

 //Holder mean
 float c = log(2)/(log(PI/2));
 holder = 4*pow((pow(a,c)+pow(b,c)),1/c);

 //David Cantrell's formula
 float d = 0.825056;
 davidCantrell= 4*(a+b)-(2*(4-PI)*a*b)/pow((pow(a,d)/2+pow(b,d)/2),1/d);

    printf("\nEllipse Circumference for Major Axis: %.2f and Minor Axis: %.2f\n", a, b);
	printf("+-----------------------------------------------------+\n");
	printf("| %40s |%10.6f|\n", "Ramanujan's First Approximation",ramanujanFirst);
	printf("+-----------------------------------------------------+\n");
	printf("| %40s |%10.6f|\n", "Ramanujan's Second Approximation", ramanujanSecond);
	printf("+-----------------------------------------------------+\n");
	printf("| %40s |%10.6f|\n", "Muir's Formula", muir);
	printf("+-----------------------------------------------------+\n");
	printf("| %40s |%10.6f|\n", "Hudson Formula", hudson);
	printf("+-----------------------------------------------------+\n");
	printf("| %40s |%10.6f|\n", "Holder mean", holder);
	printf("+-----------------------------------------------------+\n");
	printf("| %40s |%10.6f|\n", "David Cantrell's formula", davidCantrell);
	printf("+-----------------------------------------------------+\n");
    return 0;
}
