#include <stdio.h>
#include <math.h>
#include <conio.h>
int main (void){
    float a, b, c, d, result1, result2;
    
    printf("Enter a: ");
    scanf("%f", &a);
    printf("Enter b: ");
    scanf("%f", &b);
    printf("Enter c: ");
    scanf("%f", &c);
    printf("Enter d: ");
    scanf("%f", &d);
    
    result1 = log(fabs((a + b) / (sin(c) + cos(d)))) / log(10);
    result2 = pow(a , pow(b + floor(c) , a + ceil(d)));
    
    printf("\nFormula 1 result = %f", result1);
    printf("\nFormula 2 result = %f", result2);
    
    getch();
    return 0;
}
