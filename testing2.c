#include<stdio.h>
#include<string.h>

int i, j, n;
int size = 0;
char choice=' ';
char status[10];


typedef struct tache
{
    char titre[30];
    char description[600];
    int deadline;
    int status;
}tache;


void displaymenu()
{
    printf("--------- Menu ---------\n\n");
    printf("\n 1. Ajouter une tache");
    printf("\n 2. Afficher la liste de toutes les taches");
    printf("\n 3. Modifier une tache");
    printf("\n 4. Supprimer une tache");
    printf("\n 5. Rechercher une tache");
    printf("\n 6. Statistique");
    printf("\n#. Quitter\n");
    scanf(" %c", &choice);
}
void displaytask(tache t[100], int i)
{
    printf("%d Titre: %s, Description: %s, Deadline: %d \n", i+1, t[i].titre, t[i].description, t[i].deadline);

}
void addtask(tache t[100], int i)
{
    for (i = 0; i < n; i++)
    {
        printf("Entrer le titre de la tache: ");
        getchar();
        gets(t[i].titre);
        printf("Entrer la description de la tache: ");
        getchar();
        gets( t[i].description);
        printf("Entrer le deadline de la tache en jrs: ");
        scanf("%d", &t[i].deadline);
        printf("Entrer le status de tache\n1=> A realiser\t 2=> En cours de realiser\t 3=> Done  ");
        scanf("%d", &t[i].status);
        size++;
    }
}



int main()
{
    tache task[100];

    do
    {   displaymenu();

        switch (choice)
        {
            case '1':   //ajouter une tache

                printf("Entrer le nombre de tache que voulez ajoute: ");
                scanf("%d", &n);
                addtask(task, i);
                break;

            case '2': // Afficher les taches

                for ( i = 0; i < n; i++)
                {
                    displaytask(task, i);
                }
                break;
        }
    }while (choice != '#');
}