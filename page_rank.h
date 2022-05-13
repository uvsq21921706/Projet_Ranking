#include "stdlib.h"

#include <stdio.h>
#include "math.h"
#include "string.h"

#define PATH "matrice_test.txt"
#define alpha 0.85
#define epsilon 1e-6


// VERSION SALAH 
struct list{

    int origin;
    float cout;
    struct list* suivant;

};
typedef struct list* LIST;


struct structure_creuse {   

    int nbr_lignes;
    int nbr_arcs; 
    LIST* les_listes;
    int* F; 
    //float* nabla; // le min d'une ligne 
    //float* delta;  // le max d'une ligne
    float* pi;

};
typedef struct structure_creuse DATA;

LIST ajouter_element(LIST l,int origin,float cout);

DATA lecture_matrix(DATA);

DATA init_DATA(DATA donnee);

void liberer_DATA(DATA les_donnees);

void afficher_Data(DATA les_donnees);

float* PG_google (DATA data);

