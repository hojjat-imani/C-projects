#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int computer_guess_number_counter, user_guess_number_counter, finish_flag;

int computer_turn(void);
void user_turn(void);
int computer_play(void);
int random_number(void);
int computer_guess_number_random(int min, int max);


main(){
       printf("\t\t\t\t*****Let's Play!!!*****\n\n\n");
       
       while ( ! finish_flag ){
             computer_turn();
             if ( ! finish_flag )
                user_turn();
                }
                
       printf(".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.>>>FINISH<<<-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n\n\n");
       printf("Computer guessed   \" %d \"   times\n\n", computer_guess_number_counter);
       printf("You guessed   \" %d \"   times\n\n", user_guess_number_counter); 
           
       getch();
       
       }

int computer_turn(void){
     int number, user_guess_number, finish = 0, flag = 0;
 
     number = random_number();
     
     
     printf(">>>>>>>Computer's turn :\n\n");
     printf("You should guess!!\n\n\n");

     do{
                printf("guess a number (from 1 to 1000)\t");
                scanf("%d", &user_guess_number);
                user_guess_number_counter++;
                
                if ( user_guess_number < number )
                   printf("\nYour guessed number is \"SMALLER\" than the number\n\n\n");
                
                
                if ( user_guess_number > number )
                   printf("\nYour guessed number is \"LARGER\" than the number\n\n\n");

                
                
                if ( user_guess_number == 0 )
                   finish++;
                else
                    finish = 0;
                
                
                if ( finish == 3)
                   break;
                
       }while (user_guess_number != number);
       
       if ( finish == 3 ){
            finish_flag = true;
            user_guess_number_counter -= 3;
            return 0;
            }
        
       printf("\n\n\t\tbravo!!! Thats Right!!.\n\n\n\n\n");
}

void user_turn(void){
     printf(">>>>>>>Your turn:\n\nspot a number & Computer will guess!!!\n\n");
     printf("Ready????  Press any key to start\n\n\n");
     getch();
     computer_play();
     
}

int computer_play(void){
     int true_flag = 0, flag_invalid_input = 0, finish = 0, number, min = 0, max = 1000;
     char check;
     
     do{
        number = computer_guess_number_random(min , max);
        printf("\nComputer's guess :    >>%d<<\n\n", number);
        printf("if %d is                  the number\n");
        printf("           \"EQUAL to\"                   -----> press \"e\" & Enter\n");
        printf("          \"LARGER than\"                 -----> press \"l\" & then Enter\n", number);
        printf("          \"Smaller than\"                -----> press \"s\" & then Enter\n\n", number);
        
        do{
           flag_invalid_input = 0;
           scanf(" %c", &check);
        
           switch(check){
                     case 't':
                          printf("\t\tCompuer has done it!\n\n\n");
                          true_flag = 1;
                          break;
                     case 'l':
                          max = number;
                          break;
                     case 's':
                          min = number;
                          break;
                     default:
                             printf("\n\ninvalid input!\twrite a valid character again:\n\n");
                             flag_invalid_input = true;
                             }
            if (check == '0')
               finish++;
            else
                finish = 0;
                                    
            if (finish == 3){
            finish_flag = true;
            break;
            }
                  }while ( flag_invalid_input );
                 
            if (finish_flag || true_flag)
               break;
                    
                    }while( true );
                    }

int random_number(void){
    
    srand( time(NULL) );
    int x = ( (float)rand() / RAND_MAX ) * 1000;
     return x;
     
     }

int computer_guess_number_random(int min, int max){
    srand( time(NULL) );
    
    int n = min + ( 1.0 * rand() / RAND_MAX ) * (max - min);
    computer_guess_number_counter++;
    return n;
}
