#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
int main (void){
    float n, m, r1, r2, r3;
    
    printf("Enter n, m:");
    scanf("%f%f", &n, &m);
    
    time_t t = time(NULL);
    srand(t);
    r1 = rand();
    r2 = rand();
    r3 = rand();
    
    r1 = fmin(m , n) + ((r1 + 1) / (RAND_MAX + 1)) * fabs(m - n);
    r2 = fmin(m , n) + ((r2 + 1) / (RAND_MAX + 1)) * fabs(m - n);
    r3 = fmin(m , n) + ((r3 + 1) / (RAND_MAX + 1)) * fabs(m - n);
    
    printf("\n%f\n%f\n%f", r1, r2, r3);
    
    getch();
    return 0;
}
