#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <math.h>
int main(void){
    float a1, b1, a2, b2;
    bool result1, result2;
    result1 = result2 = false;
    
    printf("Enter a1: ");
    scanf("%f", &a1);
    printf("Enter b1: ");
    scanf("%f", &b1);
    printf("Enter a2: ");
    scanf("%f", &a2);
    printf("Enter b2: ");
    scanf("%f", &b2);
    
    if( (b1 - a1) < (b2 - a2) )
        result1 = true;
    
    if( a1 >= a2 && b1 <=b2 )
        result2 = true;
        
    printf("First < second = ");
    printf( result1 ? "true\n" : "false\n");
    printf("First in second = ");
    printf( result2 ? "true\n" : "false\n");
    
    printf("Overlap = ");
    if ( (a1 >= a2 && a1 <= b2) || ( a2 >= a1 && a2 <= b1) )
       printf("true %f %f", fmin(a1,a2) , fmax(b1,b2));
       else
           printf("false");
       
    getch();
    return 0;
}
