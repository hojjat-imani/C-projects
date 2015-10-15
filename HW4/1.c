#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>


float n, m;
bool result1 = false, result2 = false, result3 = false, result4 = false;
const float a = 0.000001;

int fact(int x);
bool fresult1(float m, float n);
bool fresult2(float m, float n);
bool fresult3(float m, float n);

main(){

    printf("Enter n, m: ");
    scanf("%f%f", &n, &m);
    
    printf("\n\nIn the series 1: ");
    printf(fresult1(m, n) ? "true" : "false");
    printf("\nIn the series 2: ");
    printf(fresult2(m, n) ? "true" : "false");
    printf("\nIn the series 3: ");
    printf(fresult3(m, n) ? "true" : "false");
    getch();
}



bool fresult1(float m, float n){
  int x = 2, flag = 0;
  float diff1, diff2;

 // we should check m = 1 seperatly not to have divide by zero
 if ( m == 1 ) {
      if ( n == 0.5 )
      result1 = true;
      }
  else{
    

     do{
        diff1 = fabs(m - 1/(float)x);
        diff2 = fabs(m - 1/(float)(x+1));
          
        if ( diff1 <= a ){
           if( ( fabs(n - (1/(float)(x+1))) <=a ) || (fabs(n - (1/(float)(x-1))) <= a ) )
               result1 = true;
          
        }
        x++;

        }while ( diff2 < diff1 );
}
    return result1;

}

bool fresult2(float m, float n){
     int x = 10, flag = 0;
     float diff1, diff2;
   

     do{
           
        diff1 = fabs( m - sqrt(x) );
        diff2 = fabs( m - sqrt(x + 10) );
        
        
        if ( diff1 <= a ){
           if(  ( fabs( n - sqrt(x + 10) ) <= a )  || ( fabs(n - sqrt(x - 10) ) <= a ) )
               result2 = true;
        }
        x = x + 10;
        
        }while ( diff2 < diff1 );
    return result2;
}

bool fresult3(float m, float n){
     int x = 1, flag = 0;
     float diff1, diff2;
   
     do{
           
        diff1 = fabs( m - pow(fact(x) , 1/(pow(2 , (x-1))) ));
        diff2 = fabs( m - pow(fact(x+1) , 1/(pow(2 , (x) ))));
        
                
        if ( diff1 <= a ){
           if(  ( fabs( n - pow(fact(x+1) , 1/(pow(2 , (x)))) <= a ))  || ( fabs(n - pow(fact(x-1) , 1/(pow(2 , (x-2)))) <= a ))) 
               result3 = true;
        }
        x = x + 1;
        
        }while ( diff2 < diff1 );
    return result3;
}


int fact(int x){
    int factorial = 1, i;
    
    for (i = 1; i <= x ; i++)
        factorial = i * factorial;
        
    return factorial;
}
