#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure pour représenter une date
typedef struct {
   int j,m,a;
} deadline;

// Structure pour représenter un statut
typedef struct {
    int a_realiser;
    int en_cours;
    int finalisee;
} statut;

// Structure pour représenter une tache
typedef struct {
    int id;
    char title[100];
    char description[200];
    deadline d;
    statut s;
} Task;

// Fonction pour ajouter une nouvelle tache au tableau
void addTask(Task tasks[100], int *taskCount) {
    Task newTask;
    newTask.id = (*taskCount) + 1;
    time_t current_time;
    current_time = time(NULL);
    printf("Current date: %s", ctime(&current_time));


    printf("Titre de la tache : ");
    scanf("%99s", newTask.title);

    printf("Description de la tache : ");
    scanf("%199s", newTask.description);

    printf("Deadline (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &newTask.d.j, &newTask.d.m, &newTask.d.a);

    printf("Statut de la tache (a_realiser/en_cours/finalisee) : ");
    scanf("%d/%d/%d", &newTask.s.a_realiser, &newTask.s.en_cours, &newTask.s.finalisee);

    tasks[*taskCount] = newTask;
    (*taskCount)++;
 }

// Fonction pour afficher une tache
void displayTask(Task task) {
    printf("ID : %d\n", task.id);
    printf("Titre : %s\n", task.title);
    printf("Description : %s\n", task.description);
    printf("Deadline : %d/%d/%d\n", task.d.j, task.d.m, task.d.a);
    printf("Statut : a_realiser: %d, en_cours: %d, finalisee: %d\n", task.s.a_realiser, task.s.en_cours, task.s.finalisee);
    printf("----------------------------\n");
}

// Fonction pour afficher la liste de toutes les taches
void displayAllTasks(Task tasks[100], int *taskCount) {
    printf("\n Liste de toutes les taches :\n");
    for (int i = 0; i < taskCount; i++) {
    printf("ID : %d\n", tasks[*taskCount].id);
    printf("Titre : %s\n", tasks[*taskCount].title);
    printf("Description : %s\n", tasks[*taskCount].description);
    printf("Deadline : %d/%d/%d\n", tasks[*taskCount].d.j, tasks[*taskCount].d.m, tasks[*taskCount].d.a);
    printf("Statut : a_realiser: %d, en_cours: %d, finalisee: %d\n", tasks[*taskCount].s.a_realiser, tasks[*taskCount].s.en_cours, tasks[*taskCount].s.finalisee);
    printf("----------------------------\n");
    }
}

int main() {
    Task tasks[100];  // Tableau pour stocker les taches
    int taskCount = 0; // Compteur de taches

    while (1) {
        printf("\nMenu : \n");
        printf("1. Ajouter une nouvelle tache\n");
        printf("2. Afficher la liste de toutes les taches\n");
        printf("3. Quitter\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                displayAllTasks(tasks, taskCount);
                break;
            case 3:
                exit(0);
            default:
                printf("Choix invalide\n");
        }
    }

    return 0;
}
