#include <stdio.h>
#include <conio.h>
int main (void){
    int n, num500, num100, num25, num5, num1;
    num500 = num100 = num25 = num5 = num1 = 0;
    
    printf("Enter n: ");
    scanf("%d", &n);
    
    if(n >= 1000){
       printf("\ninvalid input!!!\nn must be less than 1000");
       getch();
       return 0;
       }
       
    if (n >= 500){
       num500 = 1;
       n = n - 500;
       }
       
    while(n >= 100){
            num100++;
            n = n - 100;
            }
            
    while (n >= 25){
          num25++;
          n = n - 25;
          }
          
    while (n >=5){
          num5++;
          n = n -5;
          }
                
    while ( n>= 1){
          num1++;
          n--;
          }
          
    printf("#500 = %d\n", num500);
    printf("#100 = %d\n", num100);
    printf("#25 = %d\n", num25);
    printf("#5 = %d\n", num5);
    printf("#1 = %d\n", num1);
    
    getch();
    return 0;
}
