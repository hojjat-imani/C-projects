#include<conio.h>
#include<stdio.h>
#include<math.h>

int n;

void get_input();
void check_validity();
int least_factor(int x);
void all_factors(int x);


main(){
       get_input();
       check_validity();   
       printf("Factors: ");
       all_factors( fabs(n) );
       getch();
}


void get_input(){
     printf("Enter n: ");
     scanf("%d", &n);
}


void check_validity(){
     while ( (n == 1) || (n == 0) || (n == -1) ){
        printf("No prime factor - Try another number\n\n");
        get_input();
        }
        }
int least_factor(int x){
    int i;
    for (i = 2 ; i <= x ; i++)
        if ( x % i == 0 )
           return i;
}


void all_factors(int x){
    if ( x == least_factor(x) )
      printf("%d", x);
    else{
         printf("%d ", least_factor(x));
         while ( least_factor(x) == least_factor( x / least_factor(x) ) )
                               x = x / least_factor(x);
         
         all_factors( x / least_factor(x) );
         }
}
