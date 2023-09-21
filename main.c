#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//structur deadline
typedef struct{
    int j,m,a;
}deadline;
 
//structur statut
typedef struct{
    int to_do;
    int doing;
    int done;
}statut;


typedef struct{
    int id;
    char titre[100];
    char description[600];
    deadline dl;
    statut stat;
}tache;

void main_menu(){
    printf("______main menu_____");
    printf("1/ add a task");
    printf("2/ display task :");
    printf("3/ search for task :");
    printf("# leave");
};
void dis_menu(){
    printf("______display task_____");
    printf("1/ alphabetically");
    printf("2/ by deadline");
    printf("* go back to main menu");
    printf("# leave");
};
void srch_menu(){
    printf("______search for task_____");
    printf("1/ by id");
    printf("2/ by title");
    printf("* go back to main menu");
    printf("# leave");
};
void ajouTache(tache *tab, tache x, int taille) {

    tab [(taille)++] = x;
    printf("Ajout de tâche réalisé avec succès.\n");
};