#include<stdio.h>
#include<conio.h>

float a1, b1, c1, a2, b2, c2;

void get_input(void);
void check_answer();
void calculate_answer();


main(){       
       get_input();       
       check_answer(a1, b1, c1, a2, b2, c2);
       getch();
}


void get_input(){
            printf("Enter first equation parameters: ");
            scanf("%f%f%f", &a1, &b1, &c1);
       
            printf("Enter second equation parameters: ");
            scanf("%f%f%f", &a2, &b2, &c2);
}
            
            
void check_answer(){
                 if ( (a1 * b2 - a2 * b1) != 0 )
                    calculate_answer();
                 else
                     printf("No solution\n");
}


void calculate_answer(){
                   double x1, x2;
                     
                   x1 = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
                   x2 = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
                     
                   printf("x1 = %lf, x2 = %lf", x1, x2);
}
