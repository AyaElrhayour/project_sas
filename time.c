#include <stdio.h>
#include <time.h>


                    /*this part of code uses the time library and helps to
                 calculate the age of the student with updated time features*/




int calculateAge(int birth_day, int birth_month, int birth_year) {
    struct tm birthdate = {0};
    struct tm present_date;
    time_t t;

    time(&t);
    present_date = *localtime(&t);

    birthdate.tm_year = birth_year - 1900;
    birthdate.tm_mon = birth_month - 1;
    birthdate.tm_mday = birth_day;

    mktime(&birthdate);

    double seconds = difftime(t, mktime(&birthdate));
    int days = seconds / (60*60 * 24);
    int years = days / 365;

    return years;
}

int main() {

    int birth_day ;
    int birth_month ;
    int birth_year ;
    printf("veuillez saisir la date de naissance d'apprenant:");
    scanf("%d/%d/%d",&birth_day ,&birth_month ,&birth_year);

    int age = calculateAge(birth_day, birth_month, birth_year);
    printf("Age: %d years\n", age);

    return 0;
}