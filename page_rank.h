#include "stdlib.h"

#include <stdio.h>
#include "math.h"
#include "string.h"

#define PATH "/home/user/Téléchargements/Ranking-projet/wb-cs-stanford.txt"
#define alpha 0.85


// VERSION SALAH 
struct list{

    long origin;
    double cout;
    struct list* suivant;

};
typedef struct list* LIST;


struct structure_creuse {   

    int nbr_lignes;
    int nbr_arcs; 
    LIST* les_listes;
    int* F; 
    double* nabla; // le min d'une ligne 
    double* delta;  // le max d'une ligne

};
typedef struct structure_creuse DATA;

LIST ajouter_element(LIST l,long origin,double cout);

DATA lecture_matrix(DATA);

DATA init_DATA(DATA donnee);

