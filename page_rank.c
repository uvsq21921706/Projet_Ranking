
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
LIST ajouter_element(LIST l,int origin,float cout)
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

    int origin;
    int degre;
    int destination;
    float cout;

    FILE* fichier = fopen(PATH, "r");
     

     if(fichier != NULL)
     {

         fscanf(fichier, "%d", &data.nbr_lignes);
         fscanf(fichier, "%d", &data.nbr_arcs);

        data.F = malloc(sizeof(int)* data.nbr_lignes);     

        float val = (1.0 - alpha)/(data.nbr_lignes*1.0);
    
        data.les_listes = malloc(sizeof(LIST)* data.nbr_lignes);

        for(int i = 0; i < data.nbr_lignes; i++)
        {
            data.les_listes[i] = NULL;
        }

        for(int i = 0; i < data.nbr_lignes; i++){
            
             fscanf(fichier, "%d", &origin);
             fscanf(fichier, "%d", &degre);

                if (degre == 0)
                {
                    data.F[i] = 1;
                }
                else 
                {
                    data.F[i] = 0;
                }
                
                
            for(int j = 0; j < degre; j++){
                fscanf(fichier, "%d", &destination);
                fscanf(fichier, "%f", &cout);
                data.les_listes[destination-1] = ajouter_element(data.les_listes[destination-1],origin,cout); 
            }

        }
        
        fclose(fichier);
    }
    return data;
} 

// Affichage de DATA
void afficher_Data(DATA les_donnees){

    printf("***********************************************************\n");
    printf("\n\n");
    printf("Le nombre de ligne : %d\n",les_donnees.nbr_lignes);
    printf("Le nombre d'arc : %d\n",les_donnees.nbr_arcs);
    printf("\n\n");
    printf("***********************LES ARCS****************************\n");
    printf("\n\n");
    LIST tmp;
        for(int i=1 ; i <= les_donnees.nbr_lignes; i++){
            tmp = les_donnees.les_listes[i];
            while(tmp != NULL){
                printf(" (%d , %d , %f) ",tmp->origin,i+1,tmp->cout);
                tmp = tmp->suivant;
            }
            printf("\n");
        }
}

// retourne la valeur absolue d'un float
float valeur_absolue(float x)
{
    return (x<0)?(-x):x;
}

// initialiser un vecteur plus (vecteur Opi par exemple)
void init_vecteur(float val,float *vecteur, int taille)
{
    for (int i=0; i<taille;i++){
        vecteur[i] = val;
    }
}
// produit vecteur ligne et vecteur colonne 
float produit_vect_ligne_par_vect_colonne (float *x,DATA data)
{
    float resultat=0; 
    
    for (int i=0;i<data.nbr_lignes;i++){
        resultat+= x[i] *  data.F[i]*1.0;
    }
    return resultat;
}

// produit ligne matrice retourne un vecteur ligne
float* produit_ligne_matrice(float* vecteur,DATA data)
{
    float res_tmp = 0; // variable intermédiaire
    float* vecteur_res = calloc(data.nbr_lignes,sizeof(float)); // le vecteur resultat
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

// test de convergence (condition d'arret de pageRank)
int Convergence(DATA data, float *y){
    float somme=0.0;
    for(int i=0; i<data.nbr_lignes; i++)
    {
        somme +=valeur_absolue(data.pi[i] - y[i]); 
    }

    //printf("%.9f", som);
    if (somme<epsilon)
        return 1;
    // Retourne 1 SI "som<epsilon" ET 0 SINON
  
    return 0;
    
}

// l'algo de pageRank version google 
float* PG_google (DATA data)
{
    float *vect_x; 
    int n=1;
    
    vect_x = produit_ligne_matrice(data.pi,data);
     
    // xG = αxP + [(1 − α)(1/N) + α(1/N)(x*ft)]e

    float val_1 = (1.0 - alpha)/ (data.nbr_lignes * 1.0);
    float val_2 = alpha / (data.nbr_lignes * 1.0);
    float resutlat_mult_des_vect= produit_vect_ligne_par_vect_colonne(data.pi,data);
    float constante = (val_1 + (val_2 * resutlat_mult_des_vect) );
    
    for(int i = 0; i < data.nbr_lignes; i++){
        vect_x[i] = (vect_x[i] * alpha) + constante;
    }
    
    while (!Convergence(data,vect_x))
    {   
        n++;
        free(data.pi);

        data.pi=vect_x; 
        vect_x = produit_ligne_matrice(data.pi,data);

        // xG = αxP + [(1 − α)(1/N) + α(1/N)(x*ft)]e

        resutlat_mult_des_vect= produit_vect_ligne_par_vect_colonne(data.pi,data);
        constante = (val_1 + (val_2 * resutlat_mult_des_vect));

        for(int i = 0; i < data.nbr_lignes; i++){
        vect_x[i] = (vect_x[i] * alpha) + constante;
    }
    }
    
    printf("\nNbre d'itérations: %d ", n);
    return vect_x;

}

//Liberer une liste
void liberer_liste(LIST l){
        LIST tmp;
        while(l){
            tmp = l;
            l = l->suivant;
            free(tmp);
        }
}

//liberer DATA
void liberer_DATA(DATA les_donnees){
    if(les_donnees.les_listes){
        for(int i ; i  <= les_donnees.nbr_lignes; i++){
            if(les_donnees.les_listes[i]){
                liberer_liste(les_donnees.les_listes[i]);
                free(les_donnees.les_listes[i]);
            }
        }
        free(les_donnees.les_listes);
    }
}

/*void page_rank_cote_alpha( )
{
    //calculer les constantes et la multiplication de vecteur ligne par 
    // vecteur colonne = valeur et faire la somme avec les constantes et 
    // le produit (alpha*P*x)
}*/


