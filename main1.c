#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TASKS 100

// Global variable declaration
int size = 0;
int flag = 0;

// Structure for deadline
typedef struct {
    int d, m, y;
} deadline;

// Structure for Task
typedef struct {
    int id;
    char title[100];
    char description[600];
    deadline dl;
    char status[50];
} Task;

// Function to check if a date is valid
bool is_time_valid(int day, int month, int year) {
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    if (year < 1900 || year > 2100)
        return false;

    if (month < 1 || month > 12)
        return false;

    if (day < 1 || day > 31)
        return false;
    
    //February conndition check
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29)
                return false;
        } else {
            if (day > 28)
                return false;
        }
    }

    if (year > tm.tm_year + 1900 || (year == tm.tm_year + 1900 && month > tm.tm_mon + 1) 
        || (year == tm.tm_year + 1900 && month == tm.tm_mon + 1 && day >= tm.tm_mday))
        return true;

    return true; 
}

// Function to convert a date to days
int date_to_days(deadline date) {
    struct tm timeinfo = {0};
    timeinfo.tm_year = date.y - 1900;
    timeinfo.tm_mon = date.m - 1;
    timeinfo.tm_mday = date.d;

    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;

    time_t epochTime = mktime(&timeinfo);
    int days = (epochTime / (60 * 60 * 24));
    return 0; 
}

// Function to calculate remaining time for a deadline
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

    return 0; /
}

// Function to add multiple tasks
void add_tasks(Task *task, int numTasks) {
    for (int i = 0; i < numTasks; i++) {
        if (size >= MAX_TASKS) {
            printf("Task list is full.\n");
            break;
        }

        task[size].id = size + 1;
        printf("Title: ");
        scanf("%s", task[size].title); // Use %s for string input
        printf("Description: ");
        scanf("%s", task[size].description); // Use %s for string input

        // Input and validate the deadline (DD/MM/YYYY HH:MM)
        printf("Deadline (DD/MM/YYYY HH:MM): ");
        scanf("%d/%d/%d", &task[size].dl.d, &task[size].dl.m, &task[size].dl.y);

        if (!is_time_valid(task[size].dl.d, task[size].dl.m, task[size].dl.y)) {
            printf("Invalid deadline. Please enter a valid date.\n");
            i--; // Decrement i to re-enter the task data
            continue;
        }

        printf("Status (to do, doing, done): ");
        scanf("%s", task[size].status);

        size++; // Increment the task count
    }
}

// Function to display a task
void display_task(Task t) {
    printf("ID: %d\n", t.id);
    printf("Title: %s\n", t.title);
    printf("Description: %s\n", t.description);
    printf("Deadline: %d/%d/%d\n", t.dl.d, t.dl.m, t.dl.y);
    printf("Status: %s\n", t.status);
    printf("----------------------\n");
}

// Function to display all tasks
void display_tasks(Task *tasks, int count) {
    for (int i = 0; i < count; i++) {
        display_task(tasks[i]);
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int option;

    while (1) {
        printf("Menu:\n");
        printf("1. Add tasks\n");
        printf("2. Display tasks\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                int numTasks;
                printf("Enter the number of tasks to add: ");
                scanf("%d", &numTasks);
                add_tasks(tasks, numTasks);
                break;

            case 2:
                printf("Tasks:\n");
                display_tasks(tasks, size);
                break;

            case 3:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    return 0;
}
