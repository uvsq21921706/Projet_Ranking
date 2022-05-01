#include "page_rank.c"

int main ()
{

    DATA les_donnees;

    les_donnees = init_DATA(les_donnees);
    
    les_donnees = lecture_matrix(les_donnees);

    les_donnees.pi = calloc(les_donnees.nbr_lignes,sizeof(double));

    //afficher_data(les_donnees);

    init_vecteur(1.0/(les_donnees.nbr_lignes * 1.0),les_donnees.pi,les_donnees.nbr_lignes);

    /*for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        printf("    %lf    ",les_donnees.pi[i]);
        if (i%2 == 0)
        {
            printf("\n");
        }
        
    }*/

    double* vecteur_tmp = produit_ligne_matrice(les_donnees.pi,les_donnees);
    
return 0;

}