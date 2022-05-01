#include "page_rank.c"

int main ()
{

    LIST* array = NULL;
    array = lecture_matrix(array);
    printf("HEY");

    LIST ptr = array[5];

    while (ptr != NULL)
    {
        printf("%ld    %lf \n",ptr->origin,ptr->cout);
        ptr = ptr->suivant;
    }
    
    
return 0;

}