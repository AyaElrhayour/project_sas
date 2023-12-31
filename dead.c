#include <stdio.h>
#include <time.h>

void calculateDeadline(int day, int month, int year, int hour, int minute) {
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

int main() {
    int day, month, year, hour, minute;

    printf("Enter the deadline (DD/MM/YYYY HH:MM): ");
    scanf("%d/%d/%d %d:%d", &day, &month, &year, &hour, &minute);

    calculateDeadline(day, month, year, hour, minute);

    return 0;
}
