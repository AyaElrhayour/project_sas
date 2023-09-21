#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour representer une tache
typedef struct  {
    int id;
    char titre[100];
    char description[600];
    int completed;
}Task;

// Fonction pour ajouter une tache à la liste
void addTask( Task *tasks, int *taskCount, const char *description, const char *titre) {
    if (*taskCount < 100) {
        strcpy(tasks[*taskCount].description, description);
        strcpy(tasks[*taskCount].titre, titre);
        tasks[*taskCount].completed = 0; // La tache est initialisee comme non terminee
        (*taskCount)++;
        printf("Tache ajoutee avec succès.\n");
    } else {
        printf("La liste de taches est pleine. Impossible d'ajouter une nouvelle tache.\n");
    }
}

// Fonction pour afficher la liste des taches
void displayTasks(const  Task *tasks, int taskCount) {
    printf("Liste des taches :\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s [%s]\n", i + 1,tasks[i].titre , tasks[i].description, tasks[i].completed ? "Terminee" : "Non terminee");
    }
}

// Fonction pour marquer une tache comme terminee
void markTaskComplete( Task *tasks, int taskCount, int taskIndex) {
    if (taskIndex >= 1 && taskIndex <= taskCount) {
        tasks[taskIndex - 1].completed = 1;
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
            tasks[i].completed = tasks[i + 1].completed;
        }
        (*taskCount)--;
        printf("Tache supprimee avec succès.\n");
    } else {
        printf("Numero de tache invalide.\n");
    }
}

int main() {
    Task tasks[100]; // Tableau pour stocker les taches
    int taskCount = 0; // Nombre de taches actuelles

    int id;
    char titre[100];
    int choice;
    char description[100];
    int taskIndex;

    printf("Bienvenue dans votre liste de taches !\n");

    do {
        printf("Menu :\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher les taches\n");
        printf("3. Marquer une tache comme terminee\n");
        printf("4. Supprimer une tache\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Entrez le titre de la tache : ");
                getchar();
                gets(titre);
                printf("Entrez la description de la tache : ");
                getchar();
                gets(description);
                addTask(tasks, &taskCount, description, titre);
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
