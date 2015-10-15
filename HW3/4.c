#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>
int main (void){
    float x1, y1, x2, y2, x3, y3, x4, y4;
    bool moraba, loozi, motavazi;
    moraba = loozi = motavazi = false;

    printf("Left-Up x: ");
    scanf("%f", &x1);
    printf("Left-Up y: ");
    scanf("%f", &y1);
    printf("Right-Up x: ");
    scanf("%f", &x2);
    printf("Right-Up y: ");
    scanf("%f", &y2);
    printf("Right-down x: ");
    scanf("%f", &x3);
    printf("Right-down y: ");
    scanf("%f", &y3);
    printf("Left-down x: ");
    scanf("%f", &x4);
    printf("Left-down y: ");
    scanf("%f", &y4);
    /*these are our points:
            A(x1,y1)
            B(x2,y2)
            C(x3,y3)
            D(x4,y4) */
    
    if ((y2-y1)/(x2-x1) == (y4-y3)/(x4-x3) && pow((x2-x1),2) + pow((y2-y1),2) == pow((x4-x3),2) + pow((y4-y3),2)){
       motavazi = true;
       if(pow((x2-x1),2) + pow((y2-y1),2) == pow((x3-x2),2) + pow((y3-y2),2)){
           loozi = true;
           if(pow((x3-x1),2) + pow((y3-y2),2) == pow((x2-x1),2) + pow((y2-y1),2) + pow((x3-x2),2) + pow((y3-y2),2))
               moraba = true;
                                          }
                        }
                        
    printf("motavazi = ");
    printf(motavazi ? "true\n" : "false\n");
    printf("loozi = ");
    printf(loozi ? "true\n" : "false\n");
    printf("moraba = ");
    printf(moraba ? "true\n" : "false\n");
    
    getch();
    getch();
    return 0;
}
