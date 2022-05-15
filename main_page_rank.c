#include "page_rank.c"

int main ()
{
    DATA les_donnees;

    les_donnees = init_DATA(les_donnees);
    
    les_donnees = lecture_matrix(les_donnees);

    les_donnees.pi = calloc(les_donnees.nbr_lignes,sizeof(double));

    afficher_Data(les_donnees);

    init_vecteur(1.0/(les_donnees.nbr_lignes * 1.0),les_donnees.pi,les_donnees.nbr_lignes);
    
    //afficher le vecteur Pi aprés initialisation  
    /*for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        printf("    %lf    ",les_donnees.pi[i]);
        
    }
    
    printf("\n\n");*/
    
    //float * tmp3 = PG_google(les_donnees);

    // afficher le vecteur de pertinence
   /* for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        printf("    %lf    ",les_donnees.delta[i]);
        
    }
        printf("\n");*/

    page_rank_nabla(les_donnees);
    

return 0;

}