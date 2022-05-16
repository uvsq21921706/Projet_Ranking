#include "page_rank.c"
#include <time.h>

void temps_reel(struct timespec* t)
{
    clock_gettime(CLOCK_MONOTONIC_RAW, t);
}

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

    struct timespec temps_debut = {0,0}, temps_fin = {0,0};
    temps_reel(&temps_debut);

    page_rank_nabla(les_donnees);

    temps_reel(&temps_fin);

    printf("temps sec %ld \n", temps_fin.tv_sec - temps_debut.tv_sec);
    printf("temps nanosec %f \n", temps_fin.tv_nsec - temps_debut.tv_nsec);
    

return 0;

}