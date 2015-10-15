#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct{
       int id;
       char name[22];
       char teacher[22];
       char days[8];
       char time[6];
       }course;

struct course_node{
       course data;
       struct course_node *previous;
       struct course_node *next;
       };
typedef struct course_node course_node;

typedef struct{
        int id;
        char firstname[25];
        char surname[25];
        }student;

struct student_node{
       student data;
       struct student_node *previous;
       struct student_node *next;
       };
typedef struct student_node student_node;

struct make_dell_file{ // beshe make khali
       int id;
       struct make_dell_file *next;
       };
typedef struct make_dell_file make_dell_file;

struct std_grade{
       int id;
       char firstname[25];
       char surname[25];
       float grade;
       };
       
struct std_grade_node{
       struct std_grade data;
       struct std_grade_node *previous;
       struct std_grade_node *next;
       };
typedef struct std_grade_node std_grade_node;
       
enum menu{main_menu_code, courses_code, students_code, registration_code, grades_code, add_new_course_code, register_course_code,
course_list_code, search_course_code, add_new_student_code, student_list_code, search_student_code, current_courses_code, update_grades_code,
current_courses_code, days_code, time_code, check_course_data_code, check_student_data_code, change_grades_code, students_table_code,
courses_table_code, quick_search_student_code, advanced_search_student_code, quick_search_course_code, advanced_search_course_code,
course_chart_code, remove_course_code, student_grade_code, register_new_course_code, change_grade_code};

char menu;
int flag_back, flag_change_data, flag_course_removed, flag_grade_updated, flag_some_grade_changed, writed, readed, input, i, j;
course_node *course_list;
student_node *student_list;
make_dell_file *course_file_to_make_list;
make_dell_file *student_file_to_make_list;
course_node *student_courses_list;
std_grade_node *course_students_list;

void main_menu(void);
void show_start_tips(void);
void courses(void);
void add_new_course(void);
void get_course_data(course * new_course);
int check_course_data(course new_course);
void add_course(course new_course);
void courses_list(void);
int show_courses_table(void);
void search_course(void);
void quick_search_course(void);
void advanced_search_course(void);
void students(void);
void add_new_student(void);
void get_student_data(student * new_student);
int check_student_data(student new_student);
void add_student(student new_student);
void students_list(void);
int show_students_table(void);
void search_student(void);
void quick_search_student(void);
void advanced_search_student(void);
void regestration(void);
void register_for_student(student std);
student* choose_student(void);
void register_new_course(student std);
int course_registered_before(course *crs);
int course_has_overlab(course *crs);
int course_has_overlab(course *crs);
course_node* choose_course(course_node *list);
void register_course(course *crs, student std);
void current_courses(student std);
void remove_course(student std);
void remove_student_from_course_file(int std_id, int crs_id);
void course_chart(student std);
void grades(void);
void show_grades(course crs);
void change_grades(course crs);
void update_all_grades(course crs);
void change_some_grades(course crs);
std_grade_node* choose_std_grade(void);
void show_place(int place);
void show_menu(int menu_code);
void print_table_head(int table);
void print_table_course(course x, int end_of_table);
void print_table_student(student x, int end_of_table);
void print_day_chart(char *day, int end_of_table);
void print_table_std_grade(struct std_grade x, int end_of_table);
void show_course_data(course crs);
void show_student_data(student std);
void get_input(char * massage, int min_valid, int max_valid, int other_valid);
void load_courses(void);
void load_students(void);
void load_course_file(int id);
void load_student_file(int id);
FILE* open_file_by_id(char *folder, int id, char *opening_type);
void save_courses_changes(void);
void save_students_changes(void);
void save_student_file_changes(int id);
void free_student_courses_list(void);
void save_course_file_changes(int id);
void free_course_students_list(void);
void choose_menu(char *massage , char min_valid, char max_valid, char other_valid);
void string_to_lower( char out_str[], char in_str[], int size );
void check_error();
void Exit(void);

main(){
       show_start_tips();
       load_courses();
       load_students();
       while(1)
       main_menu();
}

void main_menu(void){
     show_place(main_menu_code);
     show_menu(main_menu_code);
     choose_menu("Please choose a menu", '1', '4', '9');
     switch (menu){
            case '1':
                 while( !flag_back )
                        courses();
                 flag_back = 0;
                 break;
            case '2':
                 while( !flag_back )
                        students();
                 flag_back = 0;
                 break;
            case '3':
                 regestration();
                 flag_back = 0;
                 break;
            case '4':
                 grades();
                 break;
            case '9':
                 Exit();
                 break;
            }
}

void courses(void){
     show_place(courses_code);
     show_menu(courses_code);
     choose_menu("Please choose a menu", '0', '2', '9');
     switch (menu){
            case '1':
                 do{
                    flag_change_data = 0;
                    add_new_course();
                 }while(flag_change_data);                
                 break;
            case '2':
                 do{
                    flag_back = 0;
                    courses_list();
                    }while(flag_back);
                 flag_back = 0;
                 break;
            case '0':
                 save_courses_changes();
                 flag_back = 1;
                 break;
            case '9':
                 save_courses_changes();
                 Exit();
                 break;
               }
}

void add_new_course(void){
     show_place(add_new_course_code);
     course new_course;
     get_course_data(&new_course);
     if( check_course_data(new_course) == 1 )
         add_course(new_course);
     else
         flag_change_data = 1;
}

void get_course_data(course * new_course){
     int flag_added_before;
     course_node *current;
     do{
        flag_added_before = 0;
        get_input("Enter course ID (7 digits)", 1000000, 9999999, 1111111);
        for( current = course_list ; current != NULL ; current = current->next )
             if( input == current->data.id ){
                 flag_added_before = 1;
                 printf("\t\t\t\tThis ID has been added befor!!\n");
                 break;
                 }
        }while( flag_added_before );
     new_course->id = input;
     
     printf("\nEnter name of course: ");
     gets( new_course->name );
     new_course->name[21] = '\0';
     
     printf("\nEnter name of teacher: ");
     gets( new_course->teacher );
     new_course->teacher[21] = '\0';
     
     show_menu(days_code);
     choose_menu("choose present day", '1', '2', '2');
     char days1[8] = "Sat-Mon";
     char days2[8] = "Sun-Tue";
     switch (menu){
            case '1':
                 strcpy(new_course->days , days1);
                 break;
            case '2':
                 strcpy(new_course->days , days2);
            }
     show_menu(time_code);
     choose_menu("Choose present time", '1', '4' ,'2');
     char time1[6] = "08-10";
     char time2[6] = "10-12";
     char time3[6] = "12-14";
     char time4[6] = "14-16";
     switch (menu){
            case '1':
                 strcpy(new_course->time , time1);
                 break;
            case '2':
                 strcpy(new_course->time , time2);
                 break;
            case '3':
                 strcpy(new_course->time , time3);
                 break;
            case '4':
                 strcpy(new_course->time , time4);
            }
}

int check_course_data(course new_course){
    show_place(add_new_course_code);
    printf("You are going to add this course:\n\n");
    print_table_head(courses_table_code);
    print_table_course(new_course, 1);
    show_menu(check_course_data_code);
    choose_menu("Check course data and choose", '1', '2', '2');
       switch(menu){
                     case '1':
                          return 1;
                     case '2':
                          return 0;
                     }
}
    
void add_course(course new_course){
     course_node *current;
     course_node *new_node = (course_node *) malloc(sizeof(course_node));
     check_error( (int)new_node, "Allocating memory", NULL );
     new_node->data = new_course;
     new_node->next = NULL;
     if( course_list == NULL )
         course_list = new_node;                     
     else{
         for(current = course_list ; current->next != NULL ; current = current->next);
                     current->next = new_node;
         }
     make_dell_file *course_to_make = (make_dell_file *) malloc(sizeof(make_dell_file));
     check_error( (int)course_to_make, "allocating memory", NULL );
     course_to_make->id = new_course.id;
     course_to_make->next = course_file_to_make_list;
     course_file_to_make_list = course_to_make;
     printf("\n\n\n\t\t\t\"%s\" added successfully!!", new_course.name);
     sleep(1000);
}
  
void courses_list(void){
     int flag_no_course;
     show_place(course_list_code);
     flag_no_course = show_courses_table();
     if ( !flag_no_course)
        search_course();
}

int show_courses_table(void){
    course_node *current;
    if( course_list == NULL ){
        printf("\n\n\t\t\t   NO course is added!!!");
        printf("\n\nPress any key ...");
        getch();
        return 1;
        }
    else{
         print_table_head(courses_table_code);
         for( current = course_list; current != NULL ; current = current->next)
              if( current->next != NULL )
                  print_table_course(current->data, 0);
              else
                  print_table_course(current->data, 1);
              return 0;
              }
}

void search_course(void){
     show_menu(search_course_code);
     choose_menu("Please choose a menu", '0', '2', '1');
     switch(menu){
             case '1':
                  quick_search_course();
                  break;
             case '2':
                  advanced_search_course();
                  }                   
}

void quick_search_course(void){
     course_node *current;
     int num_match_found = 0;
     char search_str[25], str_id[8], search_str_lower[22], name[22], teacher[25], days[8], time[6];
     show_place(quick_search_course_code);
     show_courses_table();
     printf("\n\n\nIn order to search in courses:\n\n");
     printf("Enter course ID, name, teacher's name, day or time (even part): ");
     gets(search_str);
     search_str[21] = '\0';
     string_to_lower(search_str_lower, search_str, strlen(search_str));
     show_place(quick_search_course_code);
     printf("Search Result:\n\n");
     for( current = course_list; current != NULL ; current = current->next){
          sprintf(str_id , "%d", current->data.id);
          string_to_lower(name, current->data.name, strlen(current->data.name));
          string_to_lower(teacher, current->data.teacher, strlen(current->data.teacher));
          string_to_lower(days, current->data.days, strlen(current->data.days));
          string_to_lower(time, current->data.time, strlen(current->data.time));
          if( (strstr(str_id, search_str_lower) != NULL) || (strstr(name, search_str_lower) != NULL) || (strstr(teacher, search_str_lower) != NULL) || (strstr(days, search_str_lower) != NULL) || (strstr(time, search_str_lower) != NULL) ){
              num_match_found ++;
              if( num_match_found == 1)
                  print_table_head(courses_table_code);
              print_table_course(current->data, 0);
              }
              }
     if( num_match_found == 0 )
         printf("\t\t\tNo match found!!");
     else{
         for( printf(" %c", 192) , i = 0 ; i < 9 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 23 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 23 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 9 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 7 ; printf("%c", 196), i++);
         printf("%c\n", 217);
         }
     printf("\n\nPress any key ...");
     flag_back = 1;
     getch();
}

void advanced_search_course(void){
     course_node *current;
     int num_match_found = 0;
     char  id_part[8], name_part[22], teacher_part[22], days_part[8], time_part[6], str_id[8], name[22], teacher[25], days[8];
     show_place(advanced_search_course_code);
     show_courses_table();
     printf("\n\n\nFind results including:\n\n");
     printf("Enter ID part: ");
     gets(id_part);
     printf("\nEnter course name part: ");
     gets(name_part);
     printf("\nEnter teacher's name part: ");
     gets(teacher_part);
     printf("\nEnter days part: ");
     gets(days_part);
     printf("\nEnter time part: ");
     gets(time_part);
     id_part[7] = name_part[21] = teacher_part[21] = days_part[7] = time_part[5] = '\0';
     string_to_lower(name_part, name_part, strlen(name_part));
     string_to_lower(teacher_part, teacher_part, strlen(teacher_part));
     string_to_lower(days_part, days_part, strlen(days_part));
     show_place(advanced_search_course_code);
     printf("Search Result:\n\n");
     for( current = course_list; current != NULL ; current = current->next){
          sprintf(str_id , "%d", current->data.id);
          string_to_lower(name, current->data.name, strlen(current->data.name));
          string_to_lower(teacher, current->data.teacher, strlen(current->data.teacher));
          string_to_lower(days, current->data.days, strlen(current->data.days));
          if( (strstr(str_id, id_part) != NULL) && (strstr(name, name_part) != NULL) && (strstr(teacher, teacher_part) != NULL) && (strstr(days, days_part) != NULL) && (strstr(current->data.time, time_part) != NULL) ){
              num_match_found ++;
              if( num_match_found == 1)
                  print_table_head(courses_table_code);
              print_table_course(current->data, 0);
              }
              }
     if( num_match_found == 0 )
         printf("\t\t\tNo match found!!");
     else{
          for( printf(" %c", 192) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 23 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 23 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 7 ; printf("%c", 196), i++);
          printf("%c\n", 217);
         }
     printf("\n\nPress any key ...");
     flag_back = 1;
     getch();
     }    

void students(void){
     show_place(students_code);
     show_menu(students_code);
     choose_menu("Please select a menu", '0', '2', '9');
             switch (menu){
               case '1':
                    do{
                       flag_change_data = 0;
                       add_new_student();
                       }while(flag_change_data);
                       break;
               case '2':
                    do{
                       flag_back = 0;
                       students_list();
                       }while(flag_back);
                    flag_back = 0;
                    break;
               case '0':
                    save_students_changes();
                    flag_back = 1;
                    break;
               case '9':
                    save_students_changes();
                    Exit();
               }
}

void add_new_student(void){
     show_place(add_new_student_code);
     student new_student;
     get_student_data(&new_student);
     if( check_student_data(new_student) == 1)
         add_student(new_student);
     else
         flag_change_data = 1;
}

void get_student_data(student * new_student){
     get_input("Enter student ID (7 digits)", 1000000, 9999999, 1111111);
     new_student->id = input;
     
     printf("\nEnter student's firstname: "); 
     gets( new_student->firstname );
     new_student->firstname[24] = '\0';
     
     printf("\nEnter student's surname: ");
     gets( new_student->surname );
     new_student->surname[24] = '\0';
     }
     
int check_student_data(student new_student){
    show_place(add_new_student_code);
    printf("You are going to add this Student:\n\n");
    print_table_head(students_table_code);
    print_table_student(new_student, 1);
    show_menu(check_student_data_code);
    choose_menu("Check student data and choose", '1', '2', '2');
       switch(menu){
                     case '1':
                          return 1;
                     case '2':
                          return 0;
                     }
}

void add_student(student new_student){
     student_node *current;
     student_node *new_node = (student_node *) malloc(sizeof(student_node));
     check_error( (int)new_node, "allocating memory", NULL );
     new_node->data = new_student;
     new_node->next = NULL;
     if( student_list == NULL )
         student_list = new_node;                     
     else{
         for(current = student_list ; current->next != NULL ; current = current->next);
         current->next = new_node;
         }
     make_dell_file *student_to_make = (make_dell_file *) malloc(sizeof(make_dell_file));
     check_error( (int)student_to_make, "allocating memory", NULL );
     student_to_make->id = new_student.id;
     student_to_make->next = student_file_to_make_list;
     student_file_to_make_list = student_to_make;
     printf("\n\n\n\t\t\"%s %s\" added successfully!!", new_student.firstname, new_student.surname );
     sleep(1000);
}

void students_list(void){
     int flag_no_student;
     show_place(student_list_code);
     flag_no_student = show_students_table();
     if( !flag_no_student )
         search_student();
}

int show_students_table(void){
    student_node *current;
    if( student_list == NULL ){
         printf("\n\n\t\t\t   No student is added!!!");
         printf("\n\nPress any key ...");
         getch();
         return 1;
         }
     else{
          print_table_head(students_table_code);
          for( current = student_list; current != NULL ; current = current->next)
               if( current->next != NULL)
                   print_table_student(current->data, 0);
               else
                   print_table_student(current->data, 1);
          return 0;
              }
    }
    
void search_student(void){
     show_menu(search_student_code);
     choose_menu("Please choose a menu", '0', '2', '1');
     switch (menu){
             case '1':
                  quick_search_student();
                  break;
             case '2':
                  advanced_search_student();
                  }
                   
}
 
void quick_search_student(void){
     student_node *current;
     int num_match_found = 0;
     char search_str[25], str_id[8], search_str_lower[25], firstname[25], surname[25];
     show_place(quick_search_student_code);
     show_students_table();
     printf("\n\n\nIn order to search in students:\n\n");
     printf("Enter student ID, Firstname or Lastname(even a part name): ");
     gets(search_str);
     search_str[24] = '\0';
     string_to_lower(search_str_lower, search_str, strlen(search_str));
     show_place(quick_search_student_code);
     printf("Search Result:\n\n");
     for( current = student_list; current != NULL ; current = current->next){
          sprintf(str_id , "%d", current->data.id);
          string_to_lower(firstname, current->data.firstname, strlen(current->data.firstname));
          string_to_lower(surname, current->data.surname, strlen(current->data.surname));
          if( (strstr(str_id, search_str_lower) != NULL) || (strstr(firstname, search_str_lower) != NULL) || (strstr(surname, search_str_lower) != NULL) ){
              num_match_found ++;
              if( num_match_found == 1)
                  print_table_head(students_table_code);
              print_table_student(current->data, 0);
              }
              }
     if( num_match_found == 0 )
         printf("\t\t\tNo match found!!");
     else{
          for( printf("       %c", 192) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          printf("%c\n", 217);
         }
     printf("\n\nPress any key ...");
     flag_back = 1;
     getch();
}

void advanced_search_student(void){
     student_node *current;
     int num_match_found = 0;
     char  id_part[8], firstname_part[25], surname_part[25], str_id[8], firstname[25], surname[25];
     show_place(advanced_search_student_code);
     show_students_table();
     printf("\n\n\nFind results including:\n\n");
     printf("Enter ID part: ");
     gets(id_part);
     printf("\nEnter Firstname part: ");
     gets(firstname_part);
     printf("\nEnter Surname part: ");
     gets(surname_part);
     id_part[7] = firstname_part[24] = surname_part[24] = '\0';
     string_to_lower(firstname_part, firstname_part, strlen(firstname_part));
     string_to_lower(surname_part, surname_part, strlen(surname_part));
     show_place(advanced_search_student_code);
     printf("Search Result:\n\n");
     for( current = student_list; current != NULL ; current = current->next){
          sprintf(str_id , "%d", current->data.id);
          string_to_lower(firstname, current->data.firstname, strlen(current->data.firstname));
          string_to_lower(surname, current->data.surname, strlen(current->data.surname));
          if( (strstr(str_id, id_part) != NULL) && (strstr(firstname, firstname_part) != NULL) && (strstr(surname, surname_part) != NULL) ){
              num_match_found ++;
              if( num_match_found == 1)
                  print_table_head(students_table_code);
              print_table_student(current->data, 0);
              }
              }
     if( num_match_found == 0 )
         printf("\t\t\tNo match found!!");
     else{
          for( printf("       %c", 192) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          printf("%c\n", 217);
         }
     printf("\n\nPress any key ...");
     flag_back = 1;
     getch();
}
              
void regestration(void){
     student *std;
     show_place(registration_code);
     std = choose_student();
     if( std != NULL ){
         load_student_file(std->id);
         while( !flag_back )
                register_for_student(*std);
                 }
}
     
void register_for_student(student std){
         show_place(registration_code);
         show_student_data(std);
         show_menu(registration_code);
         choose_menu("please select a menu", '0', '3', '9');
         switch (menu){
               case '1':
                    register_new_course(std);
                    break;
               case '2':
                    do{
                       flag_course_removed = 0;
                       current_courses(std);
                       }while(flag_course_removed);
                    break;
               case '3':
                    course_chart(std);
                    break;
               case '0':
                    save_student_file_changes(std.id);
                    free_student_courses_list();
                    flag_back = 1;
                    break;
               case '9':
                    save_student_file_changes(std.id);
                    Exit();
               }
     }
     
student* choose_student(void){
              student_node *current;
              printf("[0] Back\n\n");
              while(1){
                       get_input("Enter student ID (7digits)", 1000000, 9999999, 0);
                       if( input == 0 )
                           return NULL;
                       for( current = student_list ; current != NULL ; current = current->next )
                            if( input == current->data.id )
                                return &current->data;
                       printf("\t\t\t\t\tinvalid ID!\n");
                       }
}

void register_new_course(student std){
     course_node *crs;
     int overlab_id;
     show_place(register_new_course_code);
     show_student_data(std);
     crs = choose_course(course_list);
     if( crs != NULL ){
         if( course_registered_before(&crs->data) )
             printf("\nThis course has been registered before!\n");
         else if( ( overlab_id = course_has_overlab(&crs->data) ) != 0 )
              printf("\nThis course has overlab with course by ID %d", overlab_id);
         else{
             register_course(&crs->data, std);
             save_student_file_changes(std.id);
             show_place(registration_code);
             show_student_data(std);
             printf("\nThe following course registered successfully!!\n\n");
             print_table_head(courses_table_code);
             print_table_course(crs->data, 1);
             }
     printf("\n\nPress any key ...");
     getch();
     }
}

     
int course_registered_before(course *crs){
    course_node *current;
    for( current = student_courses_list ; current != NULL ; current = current->next )
         if( crs->id == current->data.id )
             return 1;
    return 0;
}

int course_has_overlab(course *crs){
    course_node *current;
    for( current = student_courses_list ; current != NULL ; current = current->next )
         if( (strcmp(current->data.time , crs->time) == 0) && (strcmp(current->data.days , crs->days) == 0) )
             return current->data.id;
    return 0;    
}

course_node* choose_course(course_node *list){
             course_node *current;
             printf("[0] Back\n\n");
             while(1){
                     get_input("Enter course ID (7digits)", 1000000, 9999999, 0);
                     if( input == 0)
                         return NULL;
                     for( current = list ; current != NULL ; current = current->next )
                          if( input == current->data.id )
                              return current;
                     printf("\t\t\t\t\tinvalid ID!\n");
                     }
}


void register_course(course *crs, student std){
     float mark = 0;
     course_node *current;
     
     FILE *pcourse = open_file_by_id("courses", crs->id, "ab");
     writed = fwrite(&std, sizeof(student), 1, pcourse);
     check_error( writed, "write to", "courses", crs->id);
     writed = fwrite(&mark, sizeof(float), 1, pcourse);
     check_error( writed, "write to", "courses", crs->id);
     fclose(pcourse);
     
     course_node *new_node = (course_node *)malloc(sizeof(course_node));
     check_error((int)new_node, "Allocating memory", NULL);
     new_node->data = *crs;
     new_node->next = NULL;
     if( student_courses_list == NULL){
         student_courses_list = new_node;
         new_node->previous = NULL;
         }
     else{
          for(current = student_courses_list ; current->next != NULL ; current = current->next);
          current->next = new_node;
          new_node->previous = current;
          }
}

void current_courses(student std){
     course_node *current;
     show_place(current_courses_code);
     show_student_data(std);
     if( student_courses_list == NULL ){
         printf("\n\n\t\t\tNO course is registered yet!!");
         printf("\n\n\nPress any key ...");
         getch();
         }
     else{
          print_table_head(courses_table_code);
          for( current = student_courses_list ; current != NULL ; current = current->next)
               if( current->next != NULL )
                   print_table_course(current->data, 0);
               else
                   print_table_course(current->data, 1);
          show_menu(remove_course_code);
          choose_menu("Please choose a menu", '0', '1', '1');
          switch(menu){
                       case '1':
                            remove_course(std);
                            flag_course_removed = 1;
                       }
          }
}

void remove_course(student std){
     course_node *crs;
     course_node *current;
     show_place(remove_course_code);
     show_student_data(std);
     print_table_head(courses_table_code);
     for( current = student_courses_list ; current != NULL ; current = current->next)
          if( current->next != NULL )
              print_table_course(current->data, 0);
          else
              print_table_course(current->data, 1);
     printf("\n\n\nIn order to remove a course:\n\n");
     crs = choose_course(student_courses_list);
     if( crs != NULL){
         if( crs->previous == NULL )
             student_courses_list = crs->next;
         else
             crs->previous->next = crs->next;
         if( crs->next != NULL )
             crs->next->previous = crs->previous;
         remove_student_from_course_file(std.id, crs->data.id);
         printf("\n\n\t\t\tCourse %s removed successfully!!!", crs->data.name);
         free(crs);
         sleep(1000);
         }
}
     
void remove_student_from_course_file(int std_id, int crs_id){
     std_grade_node *current;
     load_course_file(crs_id);
     for( current = course_students_list ; current != NULL ; current = current->next )
          if( current->data.id == std_id ){
              if( current->previous == NULL)
                  course_students_list = current->next;
              else
                  current->previous->next = current->next;
              if( current->next != NULL)
                  current->next->previous = current->previous;
              free(current);
              break;
              }
     save_course_file_changes(crs_id);
     free_course_students_list();
}

void course_chart(student std){
     show_place(course_chart_code);
     show_student_data(std);
     print_table_head(course_chart_code);
     printf(" %c  SAT  %c", 179, 179);
     print_day_chart("Sat-Mon", 0);
     printf(" %c  SUN  %c", 179, 179);
     print_day_chart("Sun-Tue", 0);
     printf(" %c  MON  %c", 179, 179);
     print_day_chart("Sat-Mon", 0);
     printf(" %c  TUE  %c", 179, 179);
     print_day_chart("Sun-Tue", 1);
     printf("\n\n\nPerss any key...");
     getch();
}
               
void grades(void){
     course_node *crs;
     show_place(grades_code);
     crs = choose_course(course_list);
     if( crs != NULL ){
         load_course_file(crs->data.id);
         do{
            flag_grade_updated = 0;
            show_grades(crs->data);
            }while(flag_grade_updated);
         save_course_file_changes(crs->data.id);
         free_course_students_list();
         }
}

void show_grades(course crs){
     std_grade_node *current;
     show_place(grades_code);
     show_course_data(crs);
     if( course_students_list == NULL ){
         printf("\n\n\t\t\tNo student has registered this course!\n");
         printf("\n\nPress any key ...");
         getch();
         }
     else{
     print_table_head(student_grade_code);
     for( current = course_students_list ; current != NULL ; current = current->next )
          if( current->next != NULL )
              print_table_std_grade(current->data, 0);
          else
              print_table_std_grade(current->data, 1);
     change_grades(crs);
     }
}

void change_grades(course crs){
     show_menu(change_grades_code);
     if( flag_some_grade_changed ){
         flag_some_grade_changed = 0;
         change_some_grades(crs);
         }
     else{
     choose_menu("Please selece a menu", '0', '2', '1');
     switch( menu ){
             case '1':
                  update_all_grades(crs);
                  break;
             case '2':
                  change_some_grades(crs);
                  }
     }
}

void update_all_grades(course crs){
     show_place(update_grades_code);
     std_grade_node *current;
     float grade;
     int printed_chars;
     show_course_data(crs);
     printf("Enter every students grade:\n\n");
     printf("Student                                                    Grade\n");
     for(i = 0 ; i <65 ; i++, printf("%c", 196) );
     printf("\n");
     for( current = course_students_list ; current != NULL ; current = current->next ){
          grade = -1;          
          do{
             printed_chars = printf("%d  %s %s", current->data.id, current->data.firstname, current->data.surname );
               for( i = 0 ; i < 60 - printed_chars ; i++)
                    printf(" ");
             scanf("%f", &grade);
             if( grade < 0 || grade > 20)
                 printf("\t\t\t\t\t\t\t\t    invalid!\n");
             fflush(stdin);
               }while( grade < 0 || grade > 20 );
          current->data.grade = grade;
          }
     flag_grade_updated = 1;
     printf("\n\n\t\t\t No more student!");
     sleep(1500);
}

void change_some_grades(course crs){
     std_grade_node *current;
     std_grade_node *std;
     show_place(change_grade_code);
     show_course_data(crs);
     print_table_head(student_grade_code);
     for( current = course_students_list ; current != NULL ; current = current->next )
          if( current->next != NULL )
              print_table_std_grade(current->data, 0);
          else
              print_table_std_grade(current->data, 1);
     printf("\n\nIn order to change a grade:\n\n");
     std = choose_std_grade();
     if( std != NULL ){
         printf("\nEnter new grade: ");
         scanf("%f", &std->data.grade);
         flag_some_grade_changed = 1;
         }     
     flag_grade_updated = 1;
}

std_grade_node* choose_std_grade(void){
                std_grade_node *current;
              printf("[0] Back\n\n");
              while(1){
                       get_input("Enter student ID (7digits)", 1000000, 9999999, 0);
                       if( input == 0 )
                           return NULL;
                       for( current = course_students_list ; current != NULL ; current = current->next )
                            if( input == current->data.id )
                                return current;
                       printf("\t\t\t\t\tinvalid ID!\n");
                       }
}

void show_place(int place){
     system("cls");
     printf("-You are here: ");
     switch (place){
            case main_menu_code:
                 printf("Main Menu");
                 break;
            case courses_code:
                 printf("Main Menu > Courses");
                 break;
            case students_code:
                 printf("Main Menu > Students");
                 break;
            case registration_code:
                 printf("Main Menu > Registration");
                 break;
            case grades_code:
                 printf("Main Menu > Grades");
                 break;
            case add_new_course_code:
                 printf("Main Menu > Courses > Add New Course");
                 break;
            case course_list_code:
                 printf("Main Menu > Courses > Course List");
                 break;
            case add_new_student_code:
                 printf("Main Menu > Students > Add New Student");
                 break;
            case student_list_code:
                 printf("Main Menu > Students > Student List");
                 break;
            case quick_search_student_code:
                 printf("Main Menu > Students > Student List > Quick search");
                 break;
            case quick_search_course_code:
                 printf("Main Menu > Courses > Course List > Quick search");
                 break;
            case advanced_search_student_code:
                 printf("Main Menu > Students > Student List > Advanced Search");
                 break;
            case advanced_search_course_code:
                 printf("Main Menu > Courses > Course List > Advanced Search");
                 break;
            case register_new_course_code:
                 printf("Main Menu > Registration > Register New Course");
                 break;
            case current_courses_code:
                 printf("Main Menu > Registration > Current Courses");
                 break;
            case remove_course_code:
                 printf("Main Menu > Registration > Current Courses > Remove Course");
                 break;
            case course_chart_code:
                 printf("Main Menu > Registration > Course Chart");
                 break;
            case change_grade_code:
                 printf("Main Menu > Grades > Change Some Grades");
                 break;
            case update_grades_code:
                 printf("Main Menu > Grades > Update All Grades");
                 break;
                 }
     for( printf("\n"), i = 0 ; i < 80 ; i++ , printf("%c", 196) );
          printf("\n");
}

void show_menu(int menu_code){
     switch (menu_code){
            case main_menu_code:
                 printf("[1] Courses\n");
                 printf("[2] Students\n");
                 printf("[3] Regestration\n");
                 printf("[4] Grades\n");
                 printf("[9] Exit\n");
                 break;
            case courses_code:
                 printf("[1] Add New Course\n");
                 printf("[2] Course List\n");
                 printf("[0] Back\n");
                 printf("[9] Exit\n");
                 break;
            case search_course_code:
                 printf("\n\n[1] Quick Search\n");
                 printf("[2] Advanced Search\n");
                 printf("[0] Back\n");
                 break;
            case students_code:
                 printf("[1] Add New Student\n");
                 printf("[2] Student List\n");
                 printf("[0] Back\n");
                 printf("[9] Exit\n");
                 break;
            case search_student_code:
                 printf("\n\n[1] Quick Search\n");
                 printf("[2] Advanced Search\n");
                 printf("[0] Back\n");
                 break;
            case registration_code:
                 printf("[1] Register New Course\n");
                 printf("[2] Current Courses\n");
                 printf("[3] Course Chart\n");
                 printf("[0] Back\n");
                 printf("[9] Exit\n");
                 break;
            case days_code:
                 printf("\n[1] Sat-Mon\n");
                 printf("[2] Sun-Tue\n");
                 break;
            case time_code:
                 printf("\n\n[1] 08-10\n");
                 printf("[2] 10-12\n");
                 printf("[3] 12-14\n");
                 printf("[4] 14-16\n");
                 break;
            case check_course_data_code:
                 printf("\n\n[1] Right (Add Course)\n");
                 printf("[2] False (Reset Data)\n");
                 break;
            case check_student_data_code:
                 printf("\n\n[1] Right (Add Student)\n");
                 printf("[2] False (Reset Data)\n");
                 break;
            case change_grades_code:
                 printf("\n\n[1] Update All Grades (auto)\n");
                 printf("[2] Change Some Grades (manually)\n");
                 printf("[0] Back\n");
                 break;
            case remove_course_code:
                 printf("\n\n[1] Remove Course\n");
                 printf("[0] Back\n");
                 break;
            }        
}

void print_table_head(int table){
     switch (table){
            case students_table_code:
                 for( printf("       %c", 213), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 printf("%c\n       %c ID      %c Firstname                %c Surname                  %c", 184, 179, 179, 179, 179);
                 for( printf("\n       %c", 198), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 break;
            case courses_table_code:
                 for( printf(" %c", 213), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <23 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <23 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <7 ; printf("%c", 205), i++ );
                 printf("%c\n %c ID      %c Name                  %c Teacher               %c Days    %c Time  %c", 184, 179, 179, 179, 179, 179, 179);
                 for( printf("\n %c", 198), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <23 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <23 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <7 ; printf("%c", 205), i++ );
                 break;
            case course_chart_code:
                 for( printf(" %c", 213), i = 0 ; i <7 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 printf("%c\n %c  ...  %c     08-10      %c     10-12      %c     12-14      %c     14-16      %c", 184, 179, 179, 179, 179, 179, 179);
                 for( printf("\n %c", 198), i = 0 ; i <7 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <16 ; printf("%c", 205), i++ );
                 break;
            case student_grade_code:
                 for( printf("   %c", 213), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 for( printf("%c", 209), i = 0 ; i <7 ; printf("%c", 205), i++ );
                 printf("%c\n   %c ID      %c Firstname                %c Surname                  %c Grade %c", 184, 179, 179, 179, 179, 179);
                 for( printf("\n   %c", 198), i = 0 ; i <9 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <26 ; printf("%c", 205), i++ );
                 for( printf("%c", 216), i = 0 ; i <7 ; printf("%c", 205), i++ );
                 break;
            }
     printf("%c\n", 181);
}

void print_table_course(course x, int end_of_table){
     int printed_chars;
     printf(" %c %d %c ", 179, x.id, 179);
     printed_chars = printf("%s", x.name);
     for( i = 0 ; i < 22 - printed_chars ; i++ )
          printf(" ");
     printed_chars = printf("%c %s ", 179, x.teacher);
     for( i = 0 ; i < 24 - printed_chars ; i++)
          printf(" ");
     printf("%c %s %c", 179, x.days, 179);
     printf(" %s ", x.time);
     
     if( end_of_table){
         for( printf("%c\n %c", 179, 192) , i = 0 ; i < 9 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 23 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 23 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 9 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 7 ; printf("%c", 196), i++);
         printf("%c\n", 217);
         }
     else{
          for( printf("%c\n %c", 179, 195) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 23 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 23 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 7 ; printf("%c", 196), i++);
          printf("%c\n", 180);
          }
}

void print_table_student(student x, int end_of_table){
     int printed_chars;
     printf("       %c %d %c ",179, x.id, 179);
     printed_chars = printf("%s", x.firstname);
     for( i = 0 ; i < 25 - printed_chars ; i++ )
          printf(" ");
     printed_chars = printf("%c %s", 179, x.surname);
     for( i = 0 ; i < 27 - printed_chars ; i++)
          printf(" ");
     if( end_of_table){
         for( printf("%c\n       %c", 179, 192) , i = 0 ; i < 9 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
         printf("%c\n", 217);
         }
     else{
          for( printf("%c\n       %c", 179, 195) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          printf("%c\n", 180);
          }
}

void print_day_chart(char *day, int end_of_table){
     char *arr[4] = {"08-10", "10-12", "12-14", "14-16"};
     int flag[4] = {0};
     course_node *current;
     for( i = 0 ; i < 4 ; i++){
          for( current = student_courses_list ; current != NULL ; current = current->next ){
               if( strcmp(current->data.days , day) == 0 && strcmp(current->data.time , arr[i]) == 0){
                   flag[i] = 1;
                   if( strlen(current->data.name) > 13)
                       printf(" %.14s %c", current->data.name, 179);
                   else{
                        for( j = 0 ; j < (14 - strlen(current->data.name))/2 + 1 ; j++ )
                             printf(" ");
                        printf("%s", current->data.name);
                        for( j = 0 ; j < (14 - strlen(current->data.name))/2 + (strlen(current->data.name)%2) + 1  ; j++ )
                             printf(" ");
                        printf("%c", 179);
                        }
                   break;
                   }
               }
     if( ! flag[i] )
         printf("                %c", 179);
     }
     if( !end_of_table ){
         for( printf("\n %c", 195), i = 0 ; i <7 ; printf("%c", 196), i++ );
         for( printf("%c", 197), i = 0 ; i <16 ; printf("%c", 196), i++ );
         for( printf("%c", 197), i = 0 ; i <16 ; printf("%c", 196), i++ );
         for( printf("%c", 197), i = 0 ; i <16 ; printf("%c", 196), i++ );
         for( printf("%c", 197), i = 0 ; i <16 ; printf("%c", 196), i++ );
         printf("%c\n", 180);
         }
     else{
         for( printf("\n %c", 192), i = 0 ; i <7 ; printf("%c", 196), i++ );
         for( printf("%c", 193), i = 0 ; i <16 ; printf("%c", 196), i++ );
         for( printf("%c", 193), i = 0 ; i <16 ; printf("%c", 196), i++ );
         for( printf("%c", 193), i = 0 ; i <16 ; printf("%c", 196), i++ );
         for( printf("%c", 193), i = 0 ; i <16 ; printf("%c", 196), i++ );
         printf("%c\n", 217);
         }
}

void print_table_std_grade(struct std_grade x, int end_of_table){
     int printed_chars;
     printf("   %c %d %c ", 179, x.id, 179);
     printed_chars = printf("%s", x.firstname, 179);
     for( i = 0 ; i < 25 - printed_chars ; i++ )
          printf(" ");
     printed_chars = printf("%c %s", 179, x.surname);
     for( i = 0 ; i < 27 - printed_chars ; i++)
          printf(" ");
     if( x.grade < 10 )
         printf("%c %.2f  ", 179, x.grade);
     else
         printf("%c %.2f ", 179, x.grade);
     if( end_of_table){
         for( printf("%c\n   %c", 179, 192) , i = 0 ; i < 9 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 26 ; printf("%c", 196), i++);
         for( printf("%c", 193) , i = 0 ; i < 7 ; printf("%c", 196), i++);
         printf("%c\n", 217);
         }
     else{
          for( printf("%c\n   %c", 179, 195) , i = 0 ; i < 9 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 26 ; printf("%c", 196), i++);
          for( printf("%c", 197) , i = 0 ; i < 7 ; printf("%c", 196), i++);
          printf("%c\n", 180);
          }
}

void show_course_data(course crs){
     int printed_chars;
     printed_chars = printf("Course: %d  %s      Teacher: %s\n", crs.id , crs.name, crs.teacher);
     for( i = 0 ; i < printed_chars - 1 ; printf("%c", 220), i++ );
     printf("\n\n\n");
     }

void show_student_data(student std){
     int printed_chars;
     printed_chars = printf("Student: %d  %s %s\n", std.id, std.firstname, std.surname);
     for( i = 0 ; i < printed_chars -1 ; printf("%c", 220), i++);
     printf("\n\n\n");
     }

void get_input(char * massage, int min_valid, int max_valid, int other_valid){
     float temp;
     do{
        printf("%s: ", massage);
        scanf("%f", &temp);
        if( (floor(temp) != temp) || ( (temp > max_valid || temp < min_valid) && temp != other_valid ) )
            printf("\t\t\t\t\tinvalid!\n");
            fflush(stdin);
        }while( (floor(temp) != temp) || ( (temp > max_valid || temp < min_valid) && temp != other_valid ) );
     input = (int) temp;
}

void load_courses(void){
     course_node *current;
     course_node *new_node;
     FILE *pfcourses = fopen("files/courses.bin", "a+b");
     check_error( (int)pfcourses, "open", "courses", 0);
     rewind(pfcourses);
     new_node = (course_node *) malloc(sizeof(course_node));
     check_error( (int)new_node, "allocating memory", NULL );
     readed = fread(&new_node->data, sizeof(course), 1, pfcourses);
     if( ! feof(pfcourses) ){
         check_error( readed , "read from", "courses", 0);
         new_node->next = NULL;
         course_list = new_node;
         for( current = course_list ; ; current = current->next ){
              new_node = (course_node *) malloc(sizeof(course_node));
              check_error( (int)new_node, "allocating memory", NULL );
              readed = fread(&new_node->data, sizeof(course), 1, pfcourses);
              if( feof(pfcourses) )
                  break; 
              check_error( readed , "read from", "courses", 0);
              new_node->next = NULL;
              current->next = new_node;
              }
         }
     free(new_node);
     fclose(pfcourses);
}

void load_students(void){
     student_node *current;
     student_node *new_node;
     FILE *pfstudents = fopen("files/students.bin", "a+b");
     check_error( (int)pfstudents, "open", "students", 0);
     rewind(pfstudents);
     new_node = (student_node *) malloc(sizeof(student_node));
     check_error( (int)new_node, "allocating memory", NULL );
     readed = fread(&new_node->data, sizeof(student), 1, pfstudents);
     if( ! feof(pfstudents) ){
         check_error( readed , "read from", "students", 0);
         new_node->next = NULL;
         student_list = new_node;
         for( current = student_list ; ; current = current->next ){
              new_node = (student_node *) malloc(sizeof(student_node));
              check_error( (int)new_node, "allocating memory", NULL );
              readed = fread(&new_node->data, sizeof(student), 1, pfstudents);
              if( feof(pfstudents) )
                  break; 
              check_error( readed , "read from", "students", 0);
              new_node->next = NULL;
              current->next = new_node;
              }
         }
     free(new_node);
     fclose(pfstudents);
}

void load_course_file(int id){
     std_grade_node *current;
     std_grade_node *new_node;
     FILE *pf = open_file_by_id("courses", id, "rb");
     new_node = (std_grade_node *) malloc(sizeof(std_grade_node));
     check_error( (int)new_node, "Allocating memory", NULL );
     readed = fread(&new_node->data, sizeof(struct std_grade), 1, pf);
     if( ! feof(pf) ){
         check_error( readed , "read from", "courses", id);
         new_node->next = NULL;
         new_node->previous = NULL;
         course_students_list = new_node;
         for( current = course_students_list ; ; current = current->next ){
              new_node = (std_grade_node *) malloc(sizeof(std_grade_node));
              check_error( (int)new_node, "Allocating memory", NULL );
              readed = fread(&new_node->data, sizeof(struct std_grade), 1, pf);
              if( feof(pf) )
                  break; 
              check_error( readed , "read from", "courses", id);
              new_node->next = NULL;
              new_node->previous = current;
              current->next = new_node;
              }
         }
     free(new_node);
     fclose(pf);
}

void load_student_file(int id){
     course_node *current;
     course_node *new_node;
     FILE *pf = open_file_by_id("students", id, "rb");
     new_node = (course_node *) malloc(sizeof(course_node));
     check_error( (int)new_node, "allocating memory", NULL );
     readed = fread(&new_node->data, sizeof(course), 1, pf);
     if( ! feof(pf) ){
         check_error( readed , "read from", "courses", id);
         new_node->next = NULL;
         new_node->previous = NULL;
         student_courses_list = new_node;
         for( current = student_courses_list ; ; current = current->next ){
              new_node = (course_node *) malloc(sizeof(course_node));
              check_error( (int)new_node, "allocating memory", NULL );
              readed = fread(&new_node->data, sizeof(course), 1, pf);
              if( feof(pf) )
                  break; 
              check_error( readed , "read from", "courses", id);
              new_node->next = NULL;
              new_node->previous = current;
              current->next = new_node;
              }
         }
     free(new_node);
     fclose(pf);
}

FILE* open_file_by_id(char *folder, int id, char *opening_type){
     char address[21] = "files/";
     char id_str[8];
     sprintf(id_str, "%d", id);
     strcat(address, folder);
     strcat(address, "/");
     strcat(address, id_str);
     strcat(address, ".bin");
     FILE *pf = fopen(address, opening_type);
     check_error( (int)pf, "open", folder, id );
     return pf;
}

void save_courses_changes(void){
     course_node *current;
     make_dell_file *current1;
     FILE *pfcourses = fopen("files/courses.bin", "wb");
     check_error( (int)pfcourses, "open", "courses", 0);
     for( current = course_list ; current != NULL ; current = current->next ){
          writed = fwrite(&current->data , sizeof(course), 1, pfcourses);
          check_error( writed , "write to", "courses", 0);
             }
     fclose(pfcourses);
     
     for( current1 = course_file_to_make_list ; current1 != NULL ; current1 = current1->next )
          fclose( open_file_by_id("courses", current1->id, "ab") );
}

void save_students_changes(void){
     student_node *current;
     make_dell_file *current1;
     FILE *pfstudents = fopen("files/students.bin", "wb");
     check_error( (int)pfstudents, "open", "students", 0);
     for( current = student_list ; current != NULL ; current = current->next ){
          writed = fwrite(&current->data , sizeof(student), 1, pfstudents);
          check_error( writed , "write to", "students", 0);
             }
     fclose(pfstudents);
     
     for( current1 = student_file_to_make_list ; current1 != NULL ; current1 = current1->next )
          fclose( open_file_by_id("students", current1->id, "ab") );
}

void save_student_file_changes(int id){
     course_node *current;
     FILE *pf = open_file_by_id("students", id, "wb");
     for( current = student_courses_list ; current != NULL ; current = current->next ){
          writed = fwrite(&current->data, sizeof(course), 1, pf);
          check_error(writed, "write to", "students", id);
          }
     fclose(pf);
     }

void free_student_courses_list(void){
     course_node *current;
     if( student_courses_list != NULL){
         if( student_courses_list->next == NULL)
             free(student_courses_list);
         else{
              for(current = student_courses_list->next ; current->next != NULL ; current = current->next )
                   free(current->previous);
              free(current->previous);
              free(current);
              }
         student_courses_list = NULL;
         }
}

void save_course_file_changes(int id){
     std_grade_node *current;
     FILE *pf = open_file_by_id("courses", id, "wb");
     for( current = course_students_list ; current != NULL ; current = current->next ){
          writed = fwrite(&current->data, sizeof(struct std_grade), 1, pf);
          check_error(writed, "write to", "courses", id);
          } 
     fclose(pf);
     }

void free_course_students_list(void){
     std_grade_node *current;
     if( course_students_list != NULL){
         if( course_students_list->next == NULL)
             free(course_students_list);
         else{
              for(current = course_students_list->next ; current->next != NULL ; current = current->next )
                   free(current->previous);
              free(current->previous);
              free(current);
              }
         course_students_list = NULL;
         }
}

void choose_menu(char *massage , char min_valid, char max_valid, char other_valid){
     do{
        printf("%s: ", massage);
        menu = getche();
        if( (menu > max_valid || menu < min_valid) && menu != other_valid )
            printf("\n\t\t\t\tinvalid!\n");
        }while( (menu > max_valid || menu < min_valid) && menu != other_valid );
}

void string_to_lower( char out_str[], char in_str[], int size ){
      for( i = 0 ; i < size ; i++ )
           out_str[i] = tolower(in_str[i]);
      out_str[size] = '\0';
}

void check_error(int check_case, char *problem, char *folder_file, int id){
     if( check_case == 0){
         system("cls");
         printf("Unfortunately an error occured\n");
         printf("\n\n\n\nError:\n\n");
         if( folder_file == NULL)
             printf("Problem in %s", problem);
         else if( id == 0)
             printf("\t\tCan not %s file: files/%s.bin", problem, folder_file);
         else
             printf("\t\tCan not %s file: files/%s/%d.bin", problem, folder_file, id);
         printf("\n\n\n\n\nYour changes will not be saved \nExiting...9");
         for( i = 8 ; i >= 0 ; i--){
              sleep(1000);
              printf("\b%d", i);
              }
         exit(-1);
         }
}

void show_start_tips(void){
     printf("\n\n         %c", 213);
     for(i = 0 ; i < 60 ; printf("%c", 205), i++);
     printf("%c\n         %c  Tips !                                                    %c\n", 184, 179, 179);
     printf("         %c", 195);
     for(i = 0 ; i < 60 ; printf("%c", 196), i++);
     printf("%c\n         %c", 180, 179);
     for( i = 0 ; i < 60 ; printf(" "), i++);
     for( i = 0 , printf("%c\n         %c", 179, 179) ; i < 60 ; printf(" "), i++);
     printf("%c\n         %c  %c This application needs a folder named \"files\" including %c\n", 179, 179, 248, 179);
     printf("         %c    tow other folders nemed \"students\" and \"courses\" inside %c\n", 179, 179);
     printf("         %c    to run. provide this folders to avoid getting error!    %c", 179, 179);
     for(j = 0 ; j < 4 ; printf("%c", 179), j++)
           for( i = 0 , printf("\n         %c", 179) ; i < 60 ; printf(" "), i++);
     printf("\n         %c  %c For exiting the program just use the \"Exit\" menu item   %c\n", 179, 248, 179);
     printf("         %c    otherwise your changes might be lost!                   %c", 179, 179);
     for( i = 0 , printf("\n         %c", 179) ; i < 60 ; printf(" "), i++);
     for( i = 0 , printf("%c\n         %c", 179, 179) ; i < 60 ; printf(" "), i++);
     printf("%c\n         %c", 179, 195);
     for( i = 0 ; i < 60 ; printf("%c", 196), i++);
     printf("%c\n         %c                               Press any key to continue!>> %c\n",180 , 179, 179);
     for( i = 0 , printf("         %c", 212) ; i < 60 ; printf("%c", 205), i++);
     printf("%c\n\n\t\t", 190);
     getch();
     fflush(stdin);
}

void Exit(void){
     system("cls");
     printf("Disigned by : Hojjat imani\n\n\n");
     printf("Final Project of \"Introduction to programming\"\n");
     printf("\nspring 1392 - Amir Kabir University of Technology(AUT)\n");
     printf("\n\n\n\nExiting...");
     for(i = 8 ; i >0 ; i--){
           printf("\b%d", i);
           sleep(1000);
           }
     exit(0);
     }
