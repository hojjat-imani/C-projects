#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int num, dir, i;
struct date{
       int year, month, day;
       };

void get_num(void);
void get_dates(struct date *dates);
int date_is_invalid(int year, int month, int day);
void get_dir(void);
void sort(struct date * arr);
int dates_sort_asc(void* d1 , void* d2);
int dates_sort_dsc(void * d1 , void * d2);
void print_result(struct date * dates);

main(){
       get_num();
       struct date dates[num];
       
       get_dates(dates);
       get_dir();
       sort(dates);
       print_result(dates);
       getch();
       }
       
       
void get_num(void){
     do{
        printf("Enter num: ");
        scanf("%d", &num);
        if( num < 1 )
            printf("\t\tinvalid!\n");
        }while( num < 1 );
}

void get_dates(struct date *dates){
     for( i = 0 ; i < num ; i++ ){
          printf("Enter dates %d: ", i + 1 );
          scanf("%d/%d/%d", &dates[i].year, &dates[i].month, &dates[i].day);
          if( date_is_invalid( dates[i].year, dates[i].month, dates[i].day ) == 1 ){
              printf("\t\t\tinvalid!\n");
              i--;
              }
          }
}

int date_is_invalid(int year, int month, int day){
    if( year < 1 || year > 99 )
        return 1;
    if( month < 1 || month > 12 )
        return 1;
    if( day < 1 || day > 31 )
        return 1;
    if( month > 6 && day == 31)
        return 1;
    return 0;
}

void get_dir(void){
     do{
        printf("Enter direction: ");
        scanf("%d", &dir);
        }while( !( dir == 1 || dir == -1) );
}

void sort(struct date * arr){
     if( dir == 1)
         qsort( arr, num, sizeof(struct date), dates_sort_asc);
     else
         qsort( arr, num, sizeof(struct date), dates_sort_dsc);
         }
         
int dates_sort_asc(void * d1 , void * d2){
    struct date dates1 = * ( (struct date *) d1 );
    struct date dates2 = * ( (struct date *) d2 );
    
    if( dates1.year > dates2.year )
        return 1;
    else if( dates2.year > dates1.year )
         return -1;
    else if( dates1.month > dates2.month )
         return 1;
    else if( dates1.month < dates2.month )
         return -1;
    else if( dates1.day > dates2.day )
         return 1;
    else if( dates1.day < dates2.day )
         return -1;
    else
        return 0;
}

int dates_sort_dsc(void * d1 , void * d2){
    struct date dates1 = * ( (struct date *) d1 );
    struct date dates2 = * ( (struct date *) d2 );
    
    if( dates1.year > dates2.year )
        return -1;
    else if( dates2.year > dates1.year )
         return 1;
    else if( dates1.month > dates2.month )
         return -1;
    else if( dates1.month < dates2.month )
         return 1;
    else if( dates1.day > dates2.day )
         return -1;
    else if( dates1.day < dates2.day )
         return 1;
    else
        return 0;
}


void print_result(struct date * dates){
     int i;
     printf("\n\n");
     for( i = 0 ; i < num ; i++)
          printf("%.2d/%.2d/%.2d\n", dates[i].year, dates[i].month, dates[i].day);
}
