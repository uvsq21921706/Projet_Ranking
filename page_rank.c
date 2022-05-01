
#include "page_rank.h"


DATA init_DATA(DATA donnees)
{
    donnees.les_listes = NULL;
    donnees.F = NULL;
    donnees.nbr_lignes = 0;
    donnees.nbr_arcs = 0;

    return donnees;
}

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

DATA lecture_matrix(DATA data)
{

    long origin;
    long degre;
    long destination;
    double cout;

    FILE* fichier = fopen(PATH, "r");
     

     if(fichier != NULL)
     {

         fscanf(fichier, "%d", &data.nbr_lignes);
         fscanf(fichier, "%d", &data.nbr_arcs);

        data.F = malloc(sizeof(int)*data.nbr_lignes);     

        double val = (1.0 - alpha)/(data.nbr_lignes*1.0);
    
        data.les_listes = malloc(sizeof(LIST)* data.nbr_lignes);

        for(int i = 1; i <= data.nbr_lignes; i++){
            data.les_listes[i] = NULL;
        }

        for(int i = 1; i <= data.nbr_lignes; i++){
            
             fscanf(fichier, "%ld", &origin);
             fscanf(fichier, "%ld", &degre);
                if (degre == 0)
                {
                    data.F[i] = 1;
                }
                else 
                {
                    data.F[i] = 0;
                }
                
                
            for(int j = 0; j < degre; j++){
                fscanf(fichier, "%ld", &destination);
                fscanf(fichier, "%lf", &cout);
                data.les_listes[destination] = ajouter_element(data.les_listes[destination],origin,cout); 
            }

        }
        
        fclose(fichier);
    }
    return data;
} 

/*double* algo_puissance()
{

}*/

/*double* produit_ligne_matrice()
{

}*/

/*void page_rank_cote_alpha( )
{
    //calculer les constantes et la multiplication de vecteur ligne par 
    // vecteur colonne = valeur et faire la somme avec les constantes et 
    // le produit (alpha*P*x)
}*/

/*double produit_vecteur_ligne_par_vecteur_colonne()
{

}*/


