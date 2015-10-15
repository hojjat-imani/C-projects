#include <stdio.h>
#include <conio.h>
int main(void){
    int n;
    
    printf("Enter 5 digit number:");
    scanf("%d", &n);
    
    printf("\nReverse:");
    while (n > 0)
    {
          printf("%d", n % 10);
          n = n / 10;
    }
    
    getch();
    return 0;
}
