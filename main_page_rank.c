#include "page_rank.c"
#define _POSIX_C_SOURCE 199309L
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

    les_donnees.pi = malloc(sizeof(float)*les_donnees.nbr_lignes);

    afficher_Data(les_donnees);

    init_vecteur(1.0/(les_donnees.nbr_lignes * 1.0),les_donnees.pi,les_donnees.nbr_lignes);
    
    float * tmp3 = PG_google(les_donnees);
    printf("LE VECTEUR PAGE RANK \n");
    for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        if(i<10)
            printf("    %lf    ",les_donnees.pi[i]);
        
    }
    
    printf("\n\n");

    // afficher le vecteur de pertinence
    /*printf("VECTEUR PAGERANK SIMPLE \n");
    for (size_t i = 0; i < sizeof(tmp3); i++)
    {
        printf("    %lf    ",tmp3[i]);
        
    }
        printf("\n");*/

    //struct timespec temps_debut = {0,0}, temps_fin = {0,0};

    clock_t t1, t2;
    float temps;

    //temps_reel(&temps_debut);
    t1 = clock();
    page_rank_nabla(les_donnees);
    t2 = clock();
    //temps_reel(&temps_fin);
    printf("");
    //printf("temps sec %ld \n", temps_fin.tv_sec - temps_debut.tv_sec);
    //printf("temps nanosec %f \n", temps_fin.tv_nsec - temps_debut.tv_nsec);
    

return 0;

}