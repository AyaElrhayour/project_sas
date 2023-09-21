#include<stdio.h>
#include<string.h>

int i, j, n;
char choice=' ';


typedef struct tache
{
    int id;
    char titre[30];
    char description[150];
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
    scanf("4%c", &choice);
}



int main()
{
    tache task[100];

    do
    {
        displaymenu();

        switch (choice)
        {
            case '1':   //ajouter une tache

                printf("Entrer le nombre de tache que voulez ajoute: ");
                scanf("%d", &n);
                for (i = 0; i < n; i++)
                {
                    printf("Entrer le titre de la tache: ");
                    getchar();
                    gets(task[i].titre);
                    printf("Entrer la description de la tache: ");
                    getchar();
                    gets(task[i].description);
                    printf("Entrer le deadline de la tache en jrs: ");
                    scanf("%d", &task[i].deadline);
                    

                }

            case '2':
                printf("iijs");
                break;
        }

    }while (choice != 0);



}
