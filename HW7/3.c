#include <stdio.h>
#include <conio.h>


struct node{
       int value;
       struct node *next;
       };

struct node * create_list(int first_element);
int add_list(struct node * list , int new_element);
void delete(struct node **plist, int num);
int function(struct node **plist, int num); // This is the function asked in the question
void print_result(int res, struct node* list, int num);
void print_list(struct node * list);
void Error();


main(){
       struct node *list = create_list(10);
       add_list(list, 20);
       add_list(list, 30);
       add_list(list, 40);

       printf(">>Main List :\n");
       print_list(list);
       
       delete(&list, 20);
       delete(&list, 40);
       delete(&list, 10);
       
       getch();
       
       }
       
struct node * create_list(int first_element){
       struct node* first_node = (struct node *) malloc ( sizeof(struct node) );
              if( first_node == NULL)
                  Error();
       first_node->value = first_element;
       first_node->next = NULL;
       return first_node;
              }
              
int add_list(struct node * list , int new_element){
                struct node * last_node;
                for( last_node = list ; last_node->next != NULL ; last_node = last_node->next);
                last_node->next = (struct node *) malloc( sizeof(struct node) );
                                if (last_node->next == NULL)
                                   Error();
                last_node->next->value = new_element;
                last_node->next->next = NULL;
                }
void delete(struct node **plist, int num){
       int res;
       res = function(plist, num);
       print_result(res, *plist, num);
}


//The Function asked in the question
int function(struct node **plist, int num){
       struct node *current = *plist;
       if( current == NULL ) // means that the list is empty
           return -1;
                 
       if( current->value == num ){ // means that the first member matches the number
           *plist = current->next;
           free(current);
           return 1;
           }
           
       if( current->next == NULL ) // means that the list has just one member & it does not match the number
           return 0;
               
       for( current = *plist ; current->next != NULL ; current = current->next ) // list has more than 1 element & number is not the first element
            if( current->next->value == num ){
                struct node *temp = current->next;
                current->next = current->next->next;
                free(temp);
                return 1;
                }
                
       return 0;
}
       
void print_result(int res, struct node* list,int num){
               if( res == -1 )
                   printf("Empty List!\n\n");
               else if ( res == 0 )
                       printf("%d is not in the list\n\n", num);
               else{
                    printf("%d removed!\n>>New List :\n", num);
                    print_list(list);
                   }
}

void print_list(struct node * list){
                  struct node * current;
                  int i;
                  for ( current = list , i = 0 ; current != NULL ; current = current->next , i++)
                      printf("\tElement[%d] = %d\n", i , current->value);
                      printf("\n");
}

void Error(){
     printf("Error allocating memory!!");
     sleep(2000);
     exit(-1);
}
