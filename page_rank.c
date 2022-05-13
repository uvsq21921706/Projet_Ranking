
#include "page_rank.h"

// initialise la structure à des valeurs par défaut et retourne la structure
DATA init_DATA(DATA donnees)
{
    donnees.les_listes = NULL;
    donnees.F = NULL;
    donnees.nbr_lignes = 0;
    donnees.nbr_arcs = 0;

    return donnees;
}

// insére un nouvelle élement de la matrice à la structure de cette derniere 
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

// initialise la structure représentant la matrice en meme temps que la lecture 
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

        data.F = malloc(sizeof(int)* data.nbr_lignes);     

        double val = (1.0 - alpha)/(data.nbr_lignes*1.0);
    
        data.les_listes = malloc(sizeof(LIST)* data.nbr_lignes);

        for(int i = 1; i <= data.nbr_lignes; i++)
        {
            data.les_listes[i] = NULL;
        }

        for(int i = 1; i <= data.nbr_lignes; i++){
            
             fscanf(fichier, "%ld", &origin);
             fscanf(fichier, "%ld", &degre);

                if (degre == 0)
                {
                    data.F[(i-1)] = 1;
                }
                else 
                {
                    data.F[(i-1)] = 0;
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

// afficher la matrice en parcourant la structure mémoire
void afficher_data(DATA data)
{
    LIST ptr;
    for (size_t i = 0; i < data.nbr_lignes; i++)
    {
        
        ptr = data.les_listes[i];
        printf("HEY\n");

        if(ptr != NULL)
            printf("ligne numéro : %ld \n",ptr->origin);
        while (ptr != NULL)
        {
            printf(" %f ",ptr->cout);

            ptr = ptr->suivant;
        }

        printf("\n");
           
    }
    
}

// initialiser un vecteur plus (vecteur Opi par exemple)
void init_vecteur(double val,double *vecteur, int taille)
{
    for (int i=0; i<taille;i++){
        vecteur[i] = val;
    }
}

/*double* algo_puissance()
{

}*/

double* produit_ligne_matrice(double* vecteur,DATA data)
{
    double res_tmp = 0; // variable intermédiaire
    double* vecteur_res = calloc(data.nbr_lignes,sizeof(double)); // le vecteur resultat
    LIST ptr = NULL; // pointeur permet de parcourir les différenetes listes (colonnes) de la structure
    for (size_t i = 0; i < data.nbr_lignes; i++)
    {
        res_tmp = 0;
        ptr = data.les_listes[i];
        
        while (ptr != NULL)
        {
            res_tmp = res_tmp + ( ptr->cout * vecteur[ptr->origin-1]);
            ptr = ptr->suivant;
        }
        vecteur_res[i] = res_tmp;   
    }
    return vecteur_res;
}

/*void page_rank_cote_alpha( )
{
    //calculer les constantes et la multiplication de vecteur ligne par 
    // vecteur colonne = valeur et faire la somme avec les constantes et 
    // le produit (alpha*P*x)
}*/

/*double produit_vecteur_ligne_par_vecteur_colonne()
{

}*/


