#include<stdio.h>
#include<conio.h>

int n, m;

void get_input(void);
void check_input_validity();
int LCM(int x, int y);
int GCD(int x , int y);


main(){
    get_input();
    check_input_validity();
    printf("LCM = %d", LCM(n, m));
    getch();
}


void get_input(){
     printf("Enter n, m: ");
     scanf("%d%d", &n, &m);
}


void check_input_validity(){
     while ( (n < 1) || (m < 1) ){
           printf("invalid input!!! - numbers should be positive\n\n");
           get_input();
           }
}


int LCM(int x, int y){    
    return x * y / GCD(x, y);
}


int GCD(int x, int y){
    int temp;
    
    while ( y != 0 ){
          temp = x % y;
          x = y;
          y = temp;
          }      
    return x;
}
