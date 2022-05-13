#include "page_rank.c"

int main ()
{

    DATA les_donnees;

    les_donnees = init_DATA(les_donnees);
    
    les_donnees = lecture_matrix(les_donnees);

    les_donnees.pi = calloc(les_donnees.nbr_lignes,sizeof(double));

    //afficher_data(les_donnees);

    init_vecteur(1.0/(les_donnees.nbr_lignes * 1.0),les_donnees.pi,les_donnees.nbr_lignes);
    
    //afficher le vecteur Pi aprés initialisation  
    for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        printf("    %lf    ",les_donnees.pi[i]);
        
    }
        printf("\n\n");
    /*
        teste dE LA MÉTHODE PRODUIT LIGNE MATRICE
    
    double* vecteur_tmp = produit_ligne_matrice(les_donnees.pi,les_donnees);

    //afficher le vecteur Pi aprés multiplication par la matrice   
    for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        printf("    %lf    ",vecteur_tmp2[i]);
       
    }
    printf("\n");*/

    //AFFICHER LE VECTEUR F
    for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        printf("    %d    ",les_donnees.F[i]);
       
    }
    printf("\n");
    
    double tmp2 = produit_vect_ligne_par_vect_colonne(les_donnees.pi,les_donnees);

    printf("LA VALEUR DU PRODUIT : %lf\n",tmp2);
return 0;

}