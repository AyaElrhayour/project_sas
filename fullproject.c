#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int taskCount = 0;
int i, n, id, taskIndex, choice, remainingTime;
char titre[100] ,description[600];
// Structure pour representer une tache
typedef struct {
    int id;
    char titre[100];
    char description[600];
    struct tm deadline;
} Task;

// ... (rest of your code remains the same)

// Fonction pour ajouter une tache à la liste avec une deadline
void addTask(Task *tasks, int *taskCount, const char *description, const char *titre, struct tm deadline) {
    if (*taskCount < 100) {
        strcpy(tasks[*taskCount].description, description);
        strcpy(tasks[*taskCount].titre, titre);
        tasks[*taskCount].deadline = deadline; // Assign the provided deadline
        (*taskCount)++;
        printf("Tache ajoutee avec succes.\n");
    } else {
        printf("La liste de taches est pleine. Impossible d'ajouter une nouvelle tache.\n");
    }
}

// Fonction pour afficher la liste des taches
// Fonction pour afficher la liste des taches avec le temps restant
void displayTasks(const Task *tasks, int taskCount) {
    printf("Liste des taches :\n");
     for (i = 0; i < taskCount; i++) {
        int remainingTime = calculateDeadline(
            tasks[i].deadline.tm_mday,
            tasks[i].deadline.tm_mon + 1, // Months are 0-based in struct tm
            tasks[i].deadline.tm_year + 1900, // Years are 1900-based in struct tm
            tasks[i].deadline.tm_hour,
            tasks[i].deadline.tm_min
        );

        // Check if the deadline has passed
        if (remainingTime < 0) {
            printf("%d. %s %s \n Deadline has passed.\n", i + 1, tasks[i].titre, tasks[i].description);
        } else {
            printf("%d. %s %s \n Remaining time: %d hours\n", i + 1, tasks[i].titre, tasks[i].description, remainingTime);
        }
    }
}


// Fonction pour marquer une tache comme terminee
void markTaskComplete( Task *tasks, int taskCount, int taskIndex) {
    if (taskIndex >= 1 && taskIndex <= taskCount) {
        printf("Tache marquee comme terminee.\n");
    } else {
        printf("Numero de tache invalide.\n");
    }
}

// Fonction pour supprimer une tache de la liste
void deleteTask( Task *tasks, int *taskCount, int taskIndex) {
    if (taskIndex >= 1 && taskIndex <= *taskCount) {
        for (int i = taskIndex - 1; i < *taskCount - 1; i++) {
            strcpy(tasks[i].description, tasks[i + 1].description);
        }
        (*taskCount)--;
        printf("Tache supprimee avec succès.\n");
    } else {
        printf("Numero de tache invalide.\n");
    }
}
int calculateDeadline(int day, int month, int year, int hour, int minute) {
    struct tm deadline = {0};
    struct tm current_time;
    time_t t;

    time(&t);
    current_time = *localtime(&t);

    deadline.tm_year = year - 1900;
    deadline.tm_mon = month - 2;
    deadline.tm_mday = day;
    deadline.tm_hour = hour;
    deadline.tm_min = minute;

    mktime(&deadline);

    double seconds = difftime(mktime(&deadline), t);
    int days = seconds / (60 * 60 * 24);
    int hours = (seconds - (days * 60 * 60 * 24)) / (60 * 60);

    return days * 24 + hours;
}

int main() {
    Task tasks[100];



    printf("Bienvenue dans votre liste de taches !\n");

    do {
        printf("Menu :\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher les taches\n");
        printf("3. Modifier une tache\n");
        printf("4. Supprimer une tache\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Entrer le nombre de taches que vous voulez ajouter : ");
            scanf("%d", &n);
            for (i = 0; i < n; i++)
            {
                printf("Entrez le titre de la tache : ");
                getchar();
                gets(titre);
                printf("Entrez la description de la tache : ");
                getchar();
                gets(description);
                struct tm deadline;
                printf("Entrez le deadline (DD/MM/YYYY HH:MM) : ");
                scanf("%d/%d/%d %d:%d", &deadline.tm_mday, &deadline.tm_mon, &deadline.tm_year, &deadline.tm_hour, &deadline.tm_min);
                deadline.tm_year -= 1900;
                addTask(tasks, &taskCount, description, titre, deadline);
            }
                break;
            case 2:
                displayTasks(tasks, taskCount);
                break;
            case 3:
                printf("Entrez le numero de la tache à marquer comme terminee : ");
                scanf("%d", &taskIndex);
                markTaskComplete(tasks, taskCount, taskIndex);
                break;
            case 4:
                printf("Entrez le numero de la tache à supprimer : ");
                scanf("%d", &taskIndex);
                deleteTask(tasks, &taskCount, taskIndex);
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez reessayer.\n");
        }
    } while (choice != 5);

    return 0;
}
