#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct gooya{
       int sorat, makhraj;
       struct gooya * next;
       };
typedef struct gooya gooya;

float scale, sum;
gooya *list;

void make_linked_list(void);
void get_numbers(void);
void add_to_list(int sorat, int makhraj);
void get_scale(void);
void calculate_sum(void);
void print_result(void);
void error(void);

main(){
       make_linked_list();
       get_numbers();
       get_scale();
       calculate_sum();
       print_result();
       getch();
       }

void make_linked_list(){
     gooya *last_node = (gooya *) malloc( sizeof(gooya) );
     if( last_node == NULL )
         error();
     last_node->sorat = last_node->makhraj = 0;
     last_node->next = NULL;
     list = last_node;
}

void get_numbers(void){
     int sorat, makhraj;
     while(1){
              printf("Enter sorat makhraj: ");
              scanf("%d%d", &sorat, &makhraj);
              if( sorat == 0 & makhraj == 0 )
                  break;
              if( makhraj == 0)
                  printf("\t\t\tinvalid!\n");
              else
                  add_to_list(sorat, makhraj);
              }
}

void add_to_list(int sorat, int makhraj){
     gooya *new_gooya = (gooya *) malloc( sizeof(gooya) );
     if( new_gooya == NULL )
         error();
     new_gooya->next = list;
     list = new_gooya;
     new_gooya->sorat = sorat;
     new_gooya->makhraj = makhraj;
}

void get_scale(void){
     printf("\nEnter scale: ");
     scanf("%f", &scale);
}

void calculate_sum(void){
     gooya *current;
     for( current = list ; current->next != NULL ; current = current->next )
          sum += (float) current->sorat / current->makhraj;
}

void print_result(){
     gooya * current;
     for( current = list ; current->next != NULL ; current = current->next )
          if(  (float)current->sorat / current->makhraj < scale * sum )
              printf("%d / %d\n", current->sorat, current->makhraj);
}

void error(void){
     system("cls");
     printf("Error allocating memory!");
     sleep(2000);
     exit(-1);
}
