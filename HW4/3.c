#include <stdio.h>
#include <conio.h>

bool check_complete(int x);

main(){
       int n, i, res_num = 0;
       
       printf("Enter n: ");
       scanf("%d", &n);
       
       for ( i = 1 ; i <= n ; i++){
           if ( check_complete(i) )
              res_num++;
       }
       
       printf("# of complete numbers: %d\n", res_num);
       
       for ( i = 1 ; i <= n ; i++){
           if ( check_complete(i) )
              printf("%d\n", i);
       }
       getch();       
}

bool check_complete(int x){
     int j, sum = 0;
     bool result = false;
     for(j = 1 ; j < x ; j++){
           if ((x % j) == 0)
              sum += j;
     }
     
     if ( x == sum )
        result = true;
        
     return result;
}
