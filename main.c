#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>


//golabal variable declaration
int day, month,year , size, s, flag, sort_type;
int i = 0, error = 0, print_error = 0;
char temp, temp1, str[99], new_str[100];
char holder[10], holder1[10], holder2[10];


//structur deadline
typedef struct{
    int d,m,y;
}deadline;

typedef struct {
    int day;
    int month;
    int year;
} Date;


typedef struct{
    int id;
    char title[100];
    char description[600];
    Date dl;
    Date  date;
    char status [50];
}Task;

bool is_time_valid ( int day ,int  month , int year){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    if(year < 1900 || year >2100)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day<1 || day > 31)
        return false;

    //feb check
    if ( month == 2){
        if ((year %4 == 0 && year %100 != 0) || (year %400 ==0)){
           if (day > 29)
               return false;
        } else {
            if (day > 28)
              return false;
        }
    }

    if (year > tm.tm_year +1900 || (year == tm.tm_year +1900 && month > tm.tm_mon +1)
       || (year == tm.tm_year +1900 && month == tm.tm_mon +1 && day >= tm.tm_mday))
       return true;

    return false;
}
int date_to_days(Date date) {
    struct tm timeinfo = {0};
    timeinfo.tm_year = date.year - 1900;
    timeinfo.tm_mon = date.month - 1;
    timeinfo.tm_mday = date.day;

    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;

    time_t epochTime = mktime(&timeinfo);
    int days = (epochTime / (60 * 60 * 24));
    return days;
}
int days_left(Date current_date, Date   given_date) {
    int current_days = date_to_days(current_date);
    int given_days = date_to_days(given_date);

    return  given_days - current_days;
}

int calc_remaining_time(int day, int month, int year, int hour, int minute) {
    struct tm deadline = {0};
    struct tm current_time;
    time_t t;

    time(&t);
    current_time = *localtime(&t);

    deadline.tm_year = year - 1900;
    deadline.tm_mon = month - 1;
    deadline.tm_mday = day;
    deadline.tm_hour = hour;
    deadline.tm_min = minute;

    mktime(&deadline);

    double seconds = difftime(mktime(&deadline), t);
    int days = seconds / (60 * 60 * 24);
    int hours = (seconds - (days * 60 * 60 * 24)) / (60 * 60);

    printf("Time remaining: %d days and %d hours\n", days, hours);
}
void add_task_s(Task *task, int size, int s, int flag) {
    int i = 0;
    int error = 0;
    int print_error = 0;
    char temp; // Used for clearing input buffer
    char temp1; // Used for reading a single character
    char str[100];
    char new_str[100];
    char holder[3], holder1[3], holder2[5];

    if (flag == 1)
        i = 0;
    else if (flag > 1)
        i = size;

    for (; i < s; i++) {
        task[i].id = i + 1;
        printf("title: ");
        scanf("%c", &temp);
        fgets(task[i].title, 50, stdin);
        task[i].title[strcspn(task[i].title, "\n")] = '\0';

        printf("description : ");
        scanf("%c", &temp1);
        fgets(str, 99, stdin);
        str[strlen(str) - 1] = '\0';

        new_str[0] = temp1;
        new_str[1] = '\0';

        strcat(new_str, str);
        strcpy(task[i].description, new_str);

        while (error == 0) {
            if (print_error == 1) {
                printf("ERROR!! The date you entered is invalid please try again\n");
            }
            printf("Deadline :\n");
            printf("Enter the deadline (DD/MM/YYYY HH:MM): ");
            scanf("%2s/%2s/%4s", holder, holder1, holder2);
            task[i].dl.day = atoi(holder);
            task[i].dl.month = atoi(holder1);
            task[i].dl.year = atoi(holder2);
            if (is_time_valid(task[i].dl.day, task[i].dl.month, task[i].dl.year)) {
                error = 1;
            } else
                print_error = 1;
        }
        error = 0;
        print_error = 0;

        while (error == 0) {
            if (print_error == 1) {
                printf("ERROR!! The status you entered is invalid please try again\n");
            }
            printf("status :");
            scanf("%s", task[i].status);
            if (strcmp(task[i].status, "to do") == 0 ||
                strcmp(task[i].status, "doing") == 0 ||
                strcmp(task[i].status, "done") == 0) {
                error = 1;
            } else
                print_error = 1;
        }
        error = 0;
        print_error = 0;
        printf("____________________________\n");
    }
}

void display_task(Task t)
{
    printf("id : %d\n", t.id);
    printf("title : %s\n", t.title);
    printf("description : %s\n", t.description);
    printf("deadline : %d-%d-%d\n", t.dl.day, t.dl.month, t.dl.year);
    printf("status : %s\n", t.status);
    printf("---------------------->\n");
}

void display_tasks(Task tasks[], int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        display_task(tasks[i]);
        i++;
    }
}
void display_sorted_tasks (Task *task, int size , int sort_type){
   int i = 0 , j;
   Task tmp;
   Date current_date;
    if( sort_type ==1 || sort_type == 2){
       while( i < size - 1){
        j = i + 1;
        while (j < size){
            if (sort_type == 1){
                if(task[i].title[0] > task[j].title[0]){
                    tmp = task[i];
                    task[i] = task[j];
                    task[j] = tmp;
                }
            } else if (sort_type == 2){
                if(task[i].dl.year > task[j].dl.year){
                    tmp = task[i];
                    task[i] = task[j];
                    task[j] = tmp;
                }else if (task[i].dl.year == task[j].dl.year){
                    if (task[i].dl.month > task[j].dl.month){
                        tmp = task[i];
                        task[i] = task[j];
                        task[j] = tmp;
                    }else if (task[i].dl.month == task[j].dl.month){
                        if (task[i].dl.day > task[j].dl.day){
                            tmp = task[i];
                            task[i] = task[j];
                            task[j] = tmp;
                        }
                    }
                }
            }
        j++;
       }
    i++;
    }
    }else if( sort_type == 3){
         int i = 0;
        Date current_date;
        Date given_date;

        time_t t;
        t = time(NULL);
        struct tm tm = *localtime(&t);

        current_date.day = tm.tm_mday;
        current_date.month = tm.tm_mon+1;
        current_date.year = tm.tm_year+1900;
                
        while (i < size)
        {
            given_date = task[i].dl;
                
            if (days_left(current_date, given_date) <= 3)
            {
                printf("--------> %d days left\n", days_left(current_date, given_date));
                display_task(task[i]);
            }
            i++;
        }  
    }
}
void modify_task (Task *task, int size, int modify_option){
    int i;
    int task_index = -1;
    int id;
    char temp;
    int error = 0;
    int print_error = 0;
    char handler[10];

    char holder[10];
    char holder1[10];
    char holder2[10];

    printf("Enter the ID of the task you would like to update:");
    scanf("%s", handler);
    id = atoi(handler);

    i = 0;
    while (i < size && task_index == -1)
    {
        if(id == task[i].id)
            task_index = i;
        i++;
    }

    if(task_index == -1){
        printf("The task you are looking can't be found !\n");
    }else{
        printf("You are modifying the task withe the ID %d : %s\n", id, task[task_index].title);
        if (modify_option == 1){
            char str[99];
            char new_str[100];
            printf("new description :");
            scanf(" %c",&temp);
            fgets(str, 99, stdin);
            str[strcspn(str, "\n")] = '\0';

            new_str[0] = temp;
            new_str[1] = '\0';

            strcat(new_str, str);
            strcpy(task[task_index].description, new_str);
        }else if (modify_option == 2){
            while (error == 0){
                if( print_error == 1){
                    printf("ERROR!! The status you entered is invalid please try again the status can only be(to do , doing, done)\n");
                }
                printf("The new status :");
                scanf("%s", task[task_index].status);
                if (strcmp(task[task_index].status, "to do") == 0 ||
                    strcmp(task[task_index].status, "doing") == 0 ||
                    strcmp(task[task_index].status, "done") == 0){
                    error = 1;
                }
            }
            error = 0;
            print_error = 0;
        }else if(modify_option == 3){
            while (error == 0){
                if(print_error == 1){
                    printf("ERROR!! The date you entered is invalid please try again\n");
                }
                printf("The new deadline is:");
                printf("Enter the deadline (DD/MM/YYYY HH:MM): ");
            scanf("%2s/%2s/%4s", holder, holder1, holder2);
            task[i].dl.day = atoi(holder);
            task[i].dl.month = atoi(holder1);
            task[i].dl.year = atoi(holder2);
                if (is_time_valid(task[i].dl.day, task[i].dl.month, task[i].dl.year)){
                    error = 1;
                }else print_error = 1;
            }
            error = 0;
            print_error = 0;
        }
    }
}

int delete_task (Task *task, int *size){
    int i = 0, task_index = -1, id, to_continue = 0, passed = 0;
    char holder1[10], holder2[10];

    printf("Enter the ID of the task you would like to delete :");
    scanf("%s", holder1);
    id = atoi(holder1);

    while (i < (*size) && task_index == -1){
        if(id == task[i].id)
            task_index = i;
        i++;
    }
    if (task_index == -1){
        printf("The task you are looking can't be found !\n");
    } else{
        printf("Are you sure you want to delete ID : %d title : %s\n", id, task[task_index].title);
        printf("If yes, please enter 1 to proceed with the deleting process (other value) to quite :");
        scanf("%s", holder2);
        to_continue = atoi(holder2);
        if (to_continue == 1){
            i = task_index;
            while (i < (*size) - 1){
                task[i] = task[i + 1];
                i++;
            }
            (*size)--;
            passed++;
        }
    }
    if (id == 0) printf("invalid input !!!!!\n");
    return passed;
}
void search_task(Task *task, int size, int search_option){
    int i=0 , task_index = -1 ,id;
    char title[50], temp, holder[10];
    if (search_option == 1){
        printf("Enter the Id of task you would like to search for :");
        scanf("%s", holder);
        id = atoi(holder);

        while (i < size && task_index == -1){
            if(id == task[i].id)
                task_index = i;
            i++;
        }
        if (id == 0)
            printf("invalid input!!!!\n");
        else if (task_index == -1)
            printf("The task you are looking can't be found !\n");
        else display_task(task[task_index]);
    }else if (search_option == 2){
        printf("Enter the title of task you would like to search for :");
        scanf("%c",&temp);
	    fgets(title, 50, stdin);
        title[strcspn(title, "\n")] = '\0';

        while (i < size && task_index == -1){
            if(strcmp(title, task[i].title) == 0)
                task_index = i;
            i++;
        }
        if (task_index == -1)
            printf("The task you are looking can't be found !\n");
        else display_task(task[task_index]);
    }
}
int finished_tasks(Task *task, int size){
    int total = 0, i= 0;

    while (i < size){
        if (strcmp(task[i].status, "done") == 0)
            total++;
        i++;
    }
    return total;
}

int none_finished_tasks(Task *task, int size){
    int total = 0, i= 0;
    while (i < size){
        if (strcmp(task[i].status, "done") != 0)
            total++;
        i++;
    }
    return total;
}

void days_left_in_deadline (Task *task, int size){
    int i;
    Date current_date;
    Date given_date;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    current_date.day = tm.tm_mday;
    current_date.month = tm.tm_mon+1;
    current_date.year = tm.tm_year+1900;
    i = 0;  

    while (i < size){
        given_date = task[i].dl;

        printf("task : ID  %d\n", task[i].id);
        printf(" %d day left\n", days_left(current_date, given_date));
        printf(">\n");

        i++;
    }
}
int main_menu (int error){
    int choice;
    char holder[20];

    if (error == -1)
        printf("invalid choice!!! try again :) .\n");
    printf("*----------------------------MENU-----------------------------*\n");
    printf("* Press 1 to add multible tasks.                              *\n");
    printf("* Press 2 to add one task.                                    *\n");
    printf("* Press 3 to disalay tasks.                                   *\n");
    printf("* Press 4 to modify a task.                                   *\n");
    printf("* Press 5 to delete a task.                                   *\n");
    printf("* Press 6 to search for a task.                               *\n");
    printf("* Press 7 to display statistics.                              *\n");
    printf("* Press -1 to quit.                                           *\n");
    printf("*-------------------------------------------------------------*\n");
    printf("* Enter your choice:                                           \n");
    scanf("%s", holder);

    choice = atoi(holder);
    if (choice == 0)
        choice = -2;
    return choice;
}
int main(){
    int size = 0;
    int s = 0;
    int option;
    Task* task = NULL;
    int stop = 0;
    int flag = 0;
    int error = 0;

while (stop != -1) {
    option = main_menu(0);

    switch (option) {
        case 1: {
            char holder[10];
            printf("enter size :");
            scanf("%s", holder);
            s = atoi(holder);
            if (s == 0)
                printf("invalid input !!!!!\n");
            else {
                int size1 = size;
                size = size + s;

                if (flag > 0) {
                    flag++;
                    task = (Task*)realloc(task, (size * sizeof(task)));
                    if (task == NULL) {
                        printf("Memory allocation failed!!");
                        return 1;
                    }
                }
                if (flag == 0) {
                    flag++;
                    task = (Task*)malloc(size * sizeof(task));
                    if (task == NULL) {
                        printf("Memory allocation failed");
                        return 1;
                    }
                }

                printf("<---------------------------add tasks------------------------->\n");
                add_task_s(task, size1, size, flag);
            }
            break;
        }

        case 2: {
            size++;
            if (flag > 0) {
                flag++;
                task = (Task*)realloc(task, (size * sizeof(task)));
                if (task == NULL) {
                    printf("Memory allocation failed!!");
                    return 1;
                }
            }
            if (flag == 0) {
                flag++;
                task = (Task*)malloc(size * sizeof(task));
                if (task == NULL) {
                    printf("Memory allocation failed");
                    return 1;
                }
            }

            break;
        }

        case 3: {
            int sort_option;
            char holder[10];
            printf("<------------------display all tasks--------------->\n");
            printf("< how you wanna display tasks :                    >\n");
            printf("< 1 sorted by alphabetical order :                 >\n");
            printf("< 2 sorted by deadline :                           >\n");
            printf("< 3 tasks that have 3 days or less for deadline.    >\n");
            printf("< 4 display :                                      >\n");
            printf("<-------------------------------------------------->\n");
            printf("enter your choice:");
            scanf("%s", holder);
            sort_option = atoi(holder);
            if (sort_option >= 1 && sort_option < 4) {
                printf("<---------------------------display--------------------------->\n");
                display_sorted_tasks(task, size, sort_option);
                if (sort_option != 3)
                    display_tasks(task, size);
            } else if (sort_option == 4) {
                printf("<---------------------------display--------------------------->\n");
                display_tasks(task, size);
            } else if (sort_option == 0) {
                printf("invalid input !!!!!\n");
            }
            break;
        }

        case 4:{
            int modify_option;
            char holder[10];
            printf("<-------------------modify all tasks--------------->\n");
            printf("< modification options :                           >\n");
            printf("< 1 to modify description.                         >\n");
            printf("< 2 to modify status.                              >\n");
            printf("< 3 to modify deadline.                            >\n");
            printf("< -1 quit.                                         >\n");
            printf("<-------------------------------------------------->\n");
            printf("enter your choice:");
            scanf("%s", holder);
            modify_option = atoi(holder);
            if (modify_option >= 1 && modify_option <= 3)
                modify_task(task, size, modify_option);
            else if (modify_option == 0)
                printf("invalid input !!!!!\n");
            break;
        }

        case 5: {
            printf("<---------------------------delete--------------------------->\n");
            int passed = delete_task(task, &size);
            if (passed == 1) {
                task = (Task*)realloc(task, (size * sizeof(task)));

                if (size == 0) {
                    free(task);
                    task = NULL;
                }
            }
            break;
        }

        case 6: {
            int search_option;
            char handler[10];
            printf("<-----------------search for tasks----------------->\n");
            printf("< search options :                                 >\n");
            printf("< 1 to search by ID.                               >\n");
            printf("< 2 to search by title.                            >\n");
            printf("< 3 other.                                         >\n");
            printf("< -1 quit.                                          >\n");
            printf("<-------------------------------------------------->\n");
            printf("enter your choice:");
            scanf("%s", handler);
            search_option = atoi(handler);
            if (search_option >= 1 && search_option <= 3)
                search_task(task, size, search_option);
            else if (search_option == 0)
                printf("invalid input !!!!!\n");
            break;
        }

        case 7: {
            int statistics_option;
            char handler[10];
            printf("<--------------------statistics-------------------->\n");
            printf("< statistics options :                             >\n");
            printf("< 1 for the total number of tasks.                     >\n");
            printf("< 2 for finished tasks and not.                    >\n");
            printf("< 3 for the number of days for the deadline.               >\n");
            printf("< -1 quit.                                          >\n");
            printf("<-------------------------------------------------->\n");
            printf("enter your choice:");
            scanf("%s", handler);
            statistics_option = atoi(handler);
            if (statistics_option == 1) {
                printf("<------------------------total tasks------------------------->\n");
                printf("total number of tasks : %d\n", size);
            } else if (statistics_option == 2) {
                printf("<----------------------finished tasks------------------------>\n");
                printf("The number of finished tasks : %d\n", finished_tasks(task, size));
                printf("The number of none finished tasks : %d\n", none_finished_tasks(task, size));
            } else if (statistics_option == 3) {
                printf("<-------------------days left in deadline-------------------->\n");
                days_left_in_deadline(task, size);
            } else if (statistics_option == 0) {
                printf("invalid input !!!!!\n");
            }
            break;
        }

        case -2: {
            printf("error!!!! you entered a string instead of an integer\n");
            break;
        }

        case -1: {
            stop = -1;
            break;
        }

        default: {
            printf("Invalid option!\n");
            break;
        }
    }
}
}
