
#include "page_rank.h"

// initialise la structure à des valeurs par défaut et retourne la structure
DATA init_DATA(DATA donnees)
{
    donnees.les_listes = NULL;
    donnees.nabla = NULL;
    donnees.delta = NULL;
    donnees.F = NULL;
    donnees.nbr_lignes = 0;
    donnees.nbr_arcs = 0;

    return donnees;
}

// insére un nouvelle élement de la matrice à la structure de cette derniere 
LIST ajouter_element(LIST l,int origin,float cout)
{
    LIST tmp = malloc(sizeof(struct list));
    if (tmp == NULL){
        exit(EXIT_FAILURE);
    }
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

// initialiser le nabla
DATA init_nabla(DATA data)
{
    data.nabla  = malloc(sizeof(float)* data.nbr_lignes);
    if (data.nabla == NULL){
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < data.nbr_lignes; i++)
    {
        data.nabla[i] =(1.0 - alpha)/(data.nbr_lignes*1.0);
    }

    return data;
    
}

// initialiser le delta
DATA init_delta(DATA data)
{
    data.delta  = malloc(sizeof(float)* data.nbr_lignes);
    if (data.delta == NULL){
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < data.nbr_lignes; i++)
    {
        data.delta[i] =0.0;
    }

    return data; 
}

// initialiser le vecteur F
DATA init_F(DATA data)
{
    data.F = malloc(sizeof(int)* data.nbr_lignes);
    if (data.F == NULL){
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < data.nbr_lignes; i++)
    {
        data.F[i] = 1;
    }

    return data;
    
}

// initialiser les listes
DATA init_les_listes(DATA data)
{
    data.les_listes = malloc(sizeof(LIST)* data.nbr_lignes);
    if (data.les_listes == NULL){
        exit(EXIT_FAILURE);
    }

        for(int i = 0; i < data.nbr_lignes; i++)
        {
            data.les_listes[i] = NULL;
        }

    return data;
    
}

// initialise la structure représentant la matrice en meme temps que la lecture 
DATA lecture_matrix(DATA data)
{

    int* f_delta = malloc(sizeof(int)*data.nbr_lignes);
    if (f_delta == NULL){
        exit(EXIT_FAILURE);
    }
    int origin;
    int degre;
    int destination;
    float cout;

    FILE* fichier = fopen(PATH, "r");
     

     if(fichier != NULL)
     {

        fscanf(fichier, "%d", &data.nbr_lignes); // récuperer le nombre de sommets
        fscanf(fichier, "%d", &data.nbr_arcs); // récupérer le nombre d'arcs

        data = init_F(data);
        data = init_les_listes(data);
        data = init_nabla(data);
        data = init_delta(data);

        for(int i = 0; i < data.nbr_lignes; i++){
            
             fscanf(fichier, "%d", &origin); // récuperer la ligne
             fscanf(fichier, "%d", &degre); // récupérer le degré de la ligne
                
                if (degre == 0)
                {
                    data.F[i] = 1; // degré sortant NULL
                }
                else 
                {
                    data.F[i] = 0; // degré sortant NON NULL
                }
                
            for(int j = 0; j < degre; j++)
            {
                fscanf(fichier, "%d", &destination);
                fscanf(fichier, "%f", &cout);
                
                if (data.delta[destination-1] < cout)
                {
                    data.delta[destination-1] = cout ; // stocker le max de chaque ligne de la matrice stochastique
                    f_delta[destination-1] = origin-1; // stocker la ligne où on a trouvé le max
                }

                data.les_listes[destination-1] = ajouter_element(data.les_listes[destination-1],origin-1,cout); 
            }
        }

        for(int i=0; i<data.nbr_lignes;i++)
        {
            // MAX(G) = MAX(αP) + MAX((α/N)(ft*e)) + MAX((1-α)(et*e))
            data.delta[i]= alpha *data.delta[i] + data.F[f_delta[i]]*(alpha/data.nbr_lignes) + ((1.0-alpha)/data.nbr_lignes);
       
            // Le cas où le degré est NULL 
            if(data.delta[i]<1.0/data.nbr_lignes)
            {
                data.delta[i]=1.0/data.nbr_lignes;  // On remplace par 1/N
            }
        }
        fclose(fichier);
    }
    free(f_delta);
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
        somme +=valeur_absolue(data.pi[i] - y[i]); // Calcul de la valeur absolue
    }
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
     
    // xG = αxP + [(1 − α)(1/N) + α(1/N)(x*ft)]e

    // #############   DETAIL DE CALCUL ############

    // vect_x = xP
    vect_x = produit_ligne_matrice(data.pi,data); 
    
    // val_1 = (1 − α)(1/N)
    float val_1 = (1.0 - alpha)/ (data.nbr_lignes * 1.0); 

    // val_2 = α(1/N)
    float val_2 = alpha / (data.nbr_lignes * 1.0); 

    // resutlat_mult_des_vect = (x*ft)
    float resutlat_mult_des_vect = produit_vect_ligne_par_vect_colonne(data.pi,data);

    // constante = [(1 − α)(1/N) + α(1/N)(x*ft)]e
    float constante = (val_1 + (val_2 * resutlat_mult_des_vect) );
    
    for(int i = 0; i < data.nbr_lignes; i++){
        vect_x[i] = (vect_x[i] * alpha) + constante; // xG = αxP + [(1 − α)(1/N) + α(1/N)(x*ft)]e (1 ére itération)
    }
    
    // La boucle tant que 
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
    if(les_donnees.delta) free(les_donnees.delta);
    if(les_donnees.nabla) free(les_donnees.nabla);
    if(les_donnees.F) free(les_donnees.F);
    if(les_donnees.pi) free(les_donnees.pi);
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


