#include "stdlib.h"

#include <stdio.h>
#include "math.h"
#include "string.h"

#define PATH "/home/user/Téléchargements/Ranking-projet/wb-cs-stanford.txt"
// VERSION SALAH 
struct list{

    long origin;
    double cout;
    struct list* suivant;

};
typedef struct list* LIST;

LIST ajouter_element(LIST l,long origin,double cout);

LIST* lecture_matrix(LIST* les_listes);

