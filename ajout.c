#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//structur deadline
typedef struct{
    int j,m,a;
}deadline;
 
//structur statut
typedef struct{
    int a_realiser;
    int en_cours;
    int finalisee;
}statut;

//structur tache
typedef struct{
    int id;
    char titre[50];
    char description[200];
    deadline d;
    statut s;
}tache;

void ajouTache(tache *tab, tache x, int taille) {

    tab [(taille)++] = x;
    printf("Ajout de tâche réalisé avec succès.\n");
}

int main() {
    tache *tableauTaches,nouvelleTache;
    int taille = 0,i;

    printf("Combien de taches souhaitez-vous ajouter ");
    scanf("%d", &taille);

    // Allocation dynamique de mémoire pour le tableau de tâches
    tableauTaches = malloc(taille * sizeof(tache));

    for (int i = 0; i < taille; i++) {
        printf("Entrez le titre de la tache : ");
        scanf("%s", nouvelleTache.titre);

        printf("Entrez la description de la tache : ");
        scanf("%s", nouvelleTache.description);

        printf("Entrez la date de la tache (jj mm aaaa) : ");
        scanf("%d %d %d", &nouvelleTache.d.j, &nouvelleTache.d.m, &nouvelleTache.d.a);

        ajouTache(tableauTaches, nouvelleTache, &taille);
    }

    // Affichage des tâches ajoutées
    printf("Liste des tâches :\n");
    for (i = 0; i < taille; i++) {
        printf("Tâche %d : %s\n", i + 1, tableauTaches[i].titre);
    }

}