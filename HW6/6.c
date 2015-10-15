#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


int map_x, map_y, theif_x_t1, theif_y_t1, theif_x_t2, theif_y_t2, number_of_polices, theif_moves, polices_moves, i, j;

void get_input();
void start(char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]);
void clean_map();
void move(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]);
void police_move_random(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]);
void police_follow_theif(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]);
void theif_move_random(char map_t2[map_x][map_y]);
void theif_flee(char map_t1[map_x][map_y], char map_t2[map_x][map_y]);
void time_pass(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]);
void print_map(char map[map_x][map_y]);
int theif_is_seen(int police_x_t1[], int police_y_t1[]);
int theif_is_arrested(char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]);
void moves_counter(int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]);
void finish(char map_t2[map_x][map_x]);


main(){
       get_input();
       
       char map_t1[map_x][map_y], map_t2[map_x][map_y];
       int police_x_t1[number_of_polices], police_y_t1[number_of_polices], police_x_t2[number_of_polices], police_y_t2[number_of_polices];
       srand( time(NULL));
       
       start(map_t2, police_x_t1, police_y_t1, police_x_t2, police_y_t2);
       while(!theif_is_arrested(map_t2, police_x_t1, police_y_t1, police_x_t2, police_y_t2)){
             time_pass(map_t1, map_t2, police_x_t1, police_y_t1, police_x_t2, police_y_t2);
             move(map_t1, map_t2, police_x_t1, police_y_t1, police_x_t2, police_y_t2);
             moves_counter(police_x_t1, police_y_t1, police_x_t2, police_y_t2);
             print_map(map_t2);
       }
       finish(map_t2);
       
       getch();
}


void get_input(){
     int flag_invalid_input = 0;
     do{
     if(flag_invalid_input)
          printf("\n\ninvalid input!!!\n\n");
     printf("Enter the size of map by 2 integers less than 80: ");
     scanf("%d%d", &map_x, &map_y);
     printf("Enter number of polices: ");
     scanf("%d", &number_of_polices);
     if( (map_x < 1) || (map_y < 1) || (map_x > 79) || (map_y > 79) || (number_of_polices < 1) || (number_of_polices >= map_x * map_y) )
         flag_invalid_input = 1;
     else
         flag_invalid_input = 0;
     }while( flag_invalid_input );
}


void clean_map(char map[map_x][map_y]){
       for(i = 0 ; i < map_x ; i++)
             for(j = 0 ; j < map_y ; j++)
                   map[i][j] = '.';
}


void start(char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]){
     clean_map(map_t2);
     
//allocating theif's first place:
     theif_x_t1 = theif_x_t2 = rand() % map_x;
     theif_y_t1 = theif_y_t2 = rand() % map_y;
     map_t2[theif_x_t2][theif_y_t2] = 'D';                   
     
//allocating polices's first place:                     
     for( i = 0 ; i < number_of_polices ; i++ ){
          do{
             police_x_t1[i] = police_x_t2[i] = rand() % map_x;
             police_y_t1[i] = police_y_t2[i] = rand() % map_y;
             }while(map_t2[police_x_t2[i]][police_y_t2[i]] != '.');
          map_t2[police_x_t2[i]][police_y_t2[i]] = 'P';
          }
          
     print_map(map_t2);
}


void print_map(char map[map_x][map_y]){
               sleep(500);
               system("cls");               
               for( i = 0 ; i < map_x ; i++ ){
                    for( j = 0 ; j < map_y ; j++ )
                         printf("%c", map[i][j]);
                    printf("\n");                     
                    }
            printf("\n\nTheive moves = %d\nPolices moves = %d", theif_moves, polices_moves);
}


void move(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]){
     clean_map(map_t2);
     if ( theif_is_seen(police_x_t1, police_y_t1) ){
          theif_flee(map_t1,map_t2);
          police_follow_theif(map_t1 ,map_t2, police_x_t1, police_y_t1, police_x_t2, police_y_t2);
           }
     else{
          theif_move_random(map_t2);
          police_move_random(map_t1, map_t2, police_x_t1, police_y_t1, police_x_t2, police_y_t2);
     }
}


int theif_is_arrested(char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]){
           for(i = 0 ; i < number_of_polices ; i++){
                 if( ((theif_x_t2 == police_x_t2[i]) && (theif_y_t2 == police_y_t2[i])) || ((theif_x_t2 == police_x_t1[i]) && (theif_y_t2 == police_y_t1[i])))
                     return 1;
                 }
           return 0;
}


void theif_move_random(char map_t2[map_x][map_y]){
             do{
                theif_x_t2 = theif_x_t1 + (rand() % 3) - 1;
                theif_y_t2 = theif_y_t1 + (rand() % 3) - 1;
                }while( (theif_x_t2 < 0) || (theif_x_t2 >= map_x) || (theif_y_t2 < 0) || (theif_y_t2 >= map_y) );
              map_t2[theif_x_t2][theif_y_t2] = 'D';
}


void police_move_random(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]){
     for(i = 0 ; i < number_of_polices ; i++){
           do{
              police_x_t2[i] = police_x_t1[i] + (rand() % 3) - 1;
              police_y_t2[i] = police_y_t1[i] + (rand() % 3) - 1;
              }while( (police_x_t2[i] < 0) || (police_x_t2[i] >= map_x) || (police_y_t2[i] < 0) || (police_y_t2[i] >= map_y) || (map_t2[police_x_t2[i]][police_y_t2[i]] == 'P') );
           map_t2[police_x_t2[i]][police_y_t2[i]] = 'P';
           }
}


void police_follow_theif(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]){
     for( i = 0 ; i < number_of_polices ; i++ ){
                if( police_x_t1[i] < theif_x_t1 )
                               police_x_t2[i] = police_x_t1[i] + 1;
                else if( police_x_t1[i] > theif_x_t1 )
                                    police_x_t2[i] = police_x_t1[i] - 1;
                else
                    police_x_t2[i] = police_x_t1[i];
                    
                if( police_y_t1[i] < theif_y_t1 )
                               police_y_t2[i] = police_y_t1[i] + 1;
                else if( police_y_t1[i] > theif_y_t1 )
                                    police_y_t2[i] = police_y_t1[i] - 1;
                else
                    police_y_t2[i] = police_y_t1[i];
                
                if( map_t2[police_x_t2[i]][police_y_t2[i]] == 'P' ){
                    police_x_t2[i] = police_x_t1[i];
                    police_y_t2[i] = police_y_t1[i];
                    }    
                map_t2[police_x_t2[i]][police_y_t2[i]] = 'P';     
                }
}


void theif_flee(char map_t1[map_x][map_y], char map_t2[map_x][map_y]){
     int flag_right, flag_left, flag_up, flag_down;
     flag_right = flag_left = flag_up = flag_down = 0;
     
     for( i = theif_y_t1 - 2 ; i < theif_y_t1 && i < map_y ; i++){
          if( i < 0 )
              continue;
          for ( j = theif_x_t1 - 2 ; j < theif_x_t1 + 3 && j < map_x ; j++ ){
              if( j < 0 )
                  continue;
              if( map_t1[j][i] == 'P' ){
                  theif_y_t2++;
                  flag_left = 1;
                  break;
                  }
              }
              if( flag_left )
                  break;
          }
          
     for( i = theif_y_t1 + 1 ; i < theif_y_t1 + 3 && i < map_y; i++){
          if( i < 0 )
              continue;
          for ( j = theif_x_t1 -2 ; j < theif_x_t1 + 3 && j < map_x ; j++ ){
              if( j < 0 )
                  continue;
              if( map_t1[j][i] == 'P' ){
                  theif_y_t2--;
                  flag_right = 1;
                  break;
                  }
              }
              if( flag_right )
                  break;
          }
          
     if ( (!flag_left) && (!flag_right) )
        do{
           theif_y_t2 = theif_y_t1 + (int) pow(-1 , rand());
           }while( (theif_y_t2 < 0) || (theif_y_t2 >= map_y) );
          
     if( (theif_y_t2 < 0) || (theif_y_t2 >= map_y) )
         theif_y_t2 = theif_y_t1;
     
     for ( i = theif_y_t1 - 2 ; i < (theif_y_t1 + 3) && i < map_y ; i++ ){
         if( i < 0 )
              continue;
         for ( j = theif_x_t1 + 1 ; j < (theif_x_t1 + 3) && j < map_x ; j++ ){
             if( j < 0 )
                 continue;
             if( map_t1[j][i] == 'P' ){
                 theif_x_t2--;
                 flag_up = 1;
                 break;
                 }
             }
             if( flag_up )
                  break;
         }
         
     for ( i = theif_y_t1 - 2 ; i < (theif_y_t1 + 3) && i < map_y ; i++ ){
         if( i < 0 )
              continue;
         for ( j = theif_x_t1 - 2 ; j < theif_x_t1 && j < map_x ; j++ ){
             if( j < 0 )
                 continue;
             if( map_t1[j][i] == 'P' ){
                 theif_x_t2++;
                 flag_down = 1;
                 break;
                 }
             }
             if( flag_down )
                  break;
         }
     
     if ( (!flag_up) && (!flag_down) )
        do{
           theif_x_t2 = theif_x_t1 + (int) pow(-1 , rand());
           }while( (theif_x_t2 < 0) || (theif_x_t2 >= map_x) );
           
     if( (theif_x_t2 < 0) || (theif_x_t2 >= map_x) )
         theif_x_t2 = theif_x_t1;
         
     map_t2[theif_x_t2][theif_y_t2] = 'D';
}


void time_pass(char map_t1[map_x][map_y], char map_t2[map_x][map_y], int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]){
     theif_x_t1 = theif_x_t2;
     theif_y_t1 = theif_y_t2;
     for( i = 0 ; i < number_of_polices ; i++){
          police_x_t1[i] = police_x_t2[i];
          police_y_t1[i] = police_y_t2[i];
          }
     for( i= 0 ; i < map_x ; i++)
          for (j = 0 ; j < map_y ; j++)
              map_t1[i][j] = map_t2[i][j];
}


int theif_is_seen(int police_x_t1[], int police_y_t1[]){
    for( i = 0 ; i < number_of_polices ; i++)
         if( (fabs(police_x_t1[i] - theif_x_t1) < 3)  &&  (fabs(police_y_t1[i] - theif_y_t1) < 3) )
             return 1;
    return 0;
}


void moves_counter(int police_x_t1[], int police_y_t1[], int police_x_t2[], int police_y_t2[]){
     if( (theif_x_t1 !=theif_x_t2) || (theif_y_t1 !=theif_y_t2) )
         theif_moves++;
     for ( i = 0 ; i < number_of_polices ; i++)
         if( (police_x_t1[i] != police_x_t2[i]) || (police_y_t1[i] != police_y_t2[i]) )
             polices_moves++;
}


void finish(char map_t2[map_x][map_y]){
            printf("\n\nTheif is arrested!!\n\n");
}
