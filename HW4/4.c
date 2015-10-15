#include <stdio.h>
#include <conio.h>
#include <math.h>

int fact(int x);

main(){
       int i, n, j = 1;
       float x, result = 0;

       printf("Enter x: ");
       scanf("%f", &x);
       printf("Enter n: ");
       scanf("%d", &n);
       
       for(i = 0 ; i < n ; i++){

             result += pow(-1 , i) * ( pow(x , j) / fact(j) );
             j += 2;
             
            
       }
       printf("sim(x): %f", result);
       getch();
}

int fact(int x){
    int i, factorial = 1;
    for( i = 1 ; i <= x ; i++ )
         factorial *= i;
    return factorial;
}
