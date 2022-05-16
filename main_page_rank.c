#include "page_rank.c"
#include <time.h>


int main ()
{
    
    DATA les_donnees;

    les_donnees = init_DATA(les_donnees);
   
    les_donnees = lecture_matrix(les_donnees);
    clock_t t3, t4;
    t3 = clock();
    float* PageRank = PG_google(les_donnees);
    t4 = clock();
    printf("Le temps d'execution de PageRank : %f\n",(float)(t4-t3)/(float)CLOCKS_PER_SEC);
    printf("LE VECTEUR PAGE RANK \n");
    for (size_t i = 0; i < les_donnees.nbr_lignes; i++)
    {
        if(i<10)
            printf("    %lf    ",PageRank[i]);
        
    }
    free(PageRank);
    
    printf("\n\n");

    clock_t t1, t2;
    t1 = clock();
    page_rank_nabla(les_donnees);
    t2 = clock();
    printf("Le temps d'execution de NABLA : %f\n",(float)(t2-t1)/(float)CLOCKS_PER_SEC);
    

return 0;

}
