#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure deadline
typedef struct {
    int j, m, a;
} deadline;

// Structure statut
typedef struct {
    int a_realiser;
    int en_cours;
    int finalisee;
} statut;

// Structure tache
typedef struct {
    int id;
    char titre[50];
    char description[200];
    deadline d;
    statut s;
} tache;

// Fonction qui ajoute une tâche au tableau de tâches
void ajoutTache(tache x, tache *tabTache, int *tailleTabTache) {
    tabTache[(*tailleTabTache)++] = x;
    printf("Tache ajoutee\n\n");
}

// Affiche
void afficherTaches(tache *tab, int *taille) {
    int i;
    printf("Liste des taches\n");
    for (i = 0; i < *taille; i++) {
        printf("Tache %d :\n", i + 1);
        printf("Id: %d\n", tab[i].id);
        printf("Description: ");
        puts(tab[i].description);
        printf("Deadline: %d/%d/%d\n", tab[i].d.j, tab[i].d.m, tab[i].d.a);
        if (tab[i].s.a_realiser == 1)
            printf("Statut : a realiser\n");
        if (tab[i].s.en_cours == 1)
            printf("Statut : en cours\n");
        if (tab[i].s.finalisee == 1)
            printf("Statut : finalisee\n");
        printf("----------------------------------------\n");
    }
}

int main() {
    tache *tableauTaches, nouvelleTache;
    int taille = 0, i, choix, choix2;

    printf("Combien de taches souhaitez-vous ajouter ? ");
    scanf("%d", &taille);

    // Allocation dynamique de mémoire pour le tableau de tâches
    tableauTaches = malloc(taille * sizeof(tache));

    while (1) {
        printf("Choisir une option: \n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher les taches\n");
        printf("3. Quitter\n");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le titre de la tache : ");
                scanf("%s", nouvelleTache.titre);
                printf("Entrez la description de la tache : ");
                getchar(); // Capture la touche "Enter" laissée par le scanf précédent
                fgets(nouvelleTache.description, sizeof(nouvelleTache.description), stdin);

                printf("Entrez la date de la tache (jj mm aaaa) : ");
                scanf("%d %d %d", &nouvelleTache.d.j, &nouvelleTache.d.m, &nouvelleTache.d.a);

                while (1) {
                    printf("1. A realiser\n");
                    printf("2. En cours\n");
                    printf("3. Finalisee\n");
                    printf("4. Quitter\n");
                    scanf("%d", &choix2);

                    switch (choix2) {
                        case 1:
                            nouvelleTache.s.a_realiser = 1;
                            break;
                        case 2:
                            nouvelleTache.s.en_cours = 1;
                            break;
                        case 3:
                            nouvelleTache.s.finalisee = 1;
                            break;
                        case 4:
                            ajoutTache(nouvelleTache, tableauTaches, &taille);
                            break;
                    }
                    if (choix2 == 4) {
                        break; 
                    }
                }
                break;
            case 2:
                afficherTaches(tableauTaches, &taille);
                break;
            case 3:
                exit(0);

        }
    }
}