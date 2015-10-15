#include <stdio.h>
#include <conio.h>
#include <math.h>

       int digit_num(int x);

main(){
       int digit, i, a , b, diff, flag = 1;
         
       printf("Enter a,b: ");
       scanf("%d%d", &a, &b);
       
      diff = fmax(a , b) - fmin(a , b);
              
       for(i = 0 ; i < digit_num(fmin(a,b)) ; i++){
             digit = diff % 10;
             if (digit != 0){
                flag = 0;
                break;
                }
            diff /= 10;
             }
       
       printf("Check: ");
       printf(flag ? "true" : "false");
       
       getch();
}
       int digit_num(int x){
           int result = 1;
           while (x >= 10){
             result++;
             x /= 10;
             }
             return result;
       }
