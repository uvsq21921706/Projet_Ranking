
#include "page_rank.h"


LIST ajouter_element(LIST l,long origin,double cout)
{
    LIST tmp = malloc(sizeof(struct list));
    tmp->origin = origin;
    tmp->cout = cout;
    tmp->suivant = NULL;

    if(l==NULL){
        l = tmp;
    }else
    {
        tmp->suivant = l;
        l = tmp;

    }

    return l;
}

LIST* lecture_matrix(LIST* les_listes){


    long nbr_ligne;
    int nbr_arc;
    long origin;
    long degre;
    long destination;
    double cout;

    FILE* fichier = fopen(PATH, "r");
     

     if(fichier != NULL)
     {

         fscanf(fichier, "%ld", &nbr_ligne);
         fscanf(fichier, "%d", &nbr_arc);
        
    

        les_listes = malloc(sizeof(LIST)* nbr_ligne);

        for(int i = 1; i <= nbr_ligne; i++){
            les_listes[i] = NULL;
        }

        for(int i = 1; i <= nbr_ligne; i++){
            
             fscanf(fichier, "%ld", &origin);
             fscanf(fichier, "%ld", &degre);

            for(int j = 0; j < degre; j++){
                fscanf(fichier, "%ld", &destination);
                fscanf(fichier, "%lf", &cout);
                les_listes[destination] = ajouter_element(les_listes[destination],origin,cout); 
            }

        }
        
        fclose(fichier);
    }
    return les_listes;
} 
