#include<stdio.h>
#include<conio.h>
#include<math.h>

int n;

void get_input(void);
void check_num_validity(int x);
int check_in_fibo(int x);
int fibo(int i);
void print_result();

int main(){
    
    get_input();
    check_num_validity(n);
    print_result();
    
    getch();
    return 0;
    
}

void get_input(){
            printf("Enter n: ");
            scanf("%d", &n);
}

void check_num_validity(int x){
                       while (n < 3){
                          printf("\tinvalid input!!!\nn must be an integr larger than 2\n\n");
                          get_input();
                          }
                       }
                       
int check_in_fibo (int x){
    
    int i = 4;
    int diff1, diff2;
    do{
        diff1 = fabs( x - fibo(i));
        diff2 = fabs( x - fibo(i + 1) );
        
        if ( x == fibo(i) )
           return fibo(i + 1);
        i++;
           }while(diff2 < diff1);
    
    return -1;
}

int fibo(int i){
    if (i == 1)
       return 1;
    else if(i == 2)
         return 1;
    else return (fibo(i - 1) + fibo(i - 2));
}

void print_result(){
     int result = check_in_fibo(n);
     if ( result == -1 )
        printf("%d is not in Fibonacci", n);
     else
         printf("%d is in Fibonacci, the next is %d", n, result);
}
