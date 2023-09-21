#include <stdio.h>
#include <string.h>

int n, i ;
int size = 0;
char choice = ' ';

typedef struct tache
{
    int id;
    char titre[30];
    char description[150];
    int deadline;
    int status;
} tache;

void displaymenu()
{
    printf("--------- Menu ---------\n\n");
    printf("\n 1. Ajouter une tache");
    printf("\n 2. Afficher la liste de toutes les taches");
    printf("\n 3. Modifier une tache");
    printf("\n 4. Supprimer une tache");
    printf("\n 5. Rechercher une tache");
    printf("\n 6. Statistique");
    printf("\n #. Quitter\n");
}

int main()
{
    tache task[100];

    do
    {
        displaymenu();
        printf("\nChoisissez une option : ");
        scanf(" %c", &choice); // Added space before %c to consume any whitespace

        switch (choice)
        {
        case '1': // Ajouter une tache
            printf("Entrer le nombre de taches que vous voulez ajouter : ");
            scanf("%d", &n);
            for (i = 0; i < n; i++)
            {
                printf("Entrer le titre de la tache : ");
                getchar(); // Consume newline from previous input
                fgets(task[size].titre, sizeof(task[size].titre), stdin);
                strtok(task[size].titre, "\n"); // Remove trailing newline

                printf("Entrer la description de la tache : ");
                fgets(task[size].description, sizeof(task[size].description), stdin);
                strtok(task[size].description, "\n"); // Remove trailing newline

                printf("Entrer le deadline de la tache en jours : ");
                scanf("%d", &task[size].deadline);

                size++;
            }
            break;

        case '2':
            printf("Liste de toutes les taches :\n");
            for (int i = 0; i < size; i++)
            {
                printf("Tache %d\n", i + 1);
                printf("Titre : %s\n", task[i].titre);
                printf("Description : %s\n", task[i].description);
                printf("Deadline : %d jours\n", task[i].deadline);
                printf("\n");
            }
            break;

        case '#':
            printf("Quitting...\n");
            break;

        default:
            printf("Option non valide. Veuillez choisir une option valide.\n");
        }
    } while (choice != '#');

    return 0;
}
