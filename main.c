
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>  /* Autorise l'utilisation de malloc
                        et de free. */



#define MaxC 10


#define STR(s) #s
#define XSTR(s) STR(s)
#define SIZE 30

//Cellule d'une liste simplement chaînée de noms de personnes
typedef struct  Cellule
{ char NomP[20];  // nom de personne (les noms de personnes sont suppos és distincts)
  struct Cellule * PP ;    // pointeur sur la personne suivante inscrite
} Cellule;

//Cahier des inscriptions
typedef struct Cahier
{
 char NomA[30];// nom d'activité (les activités sont supposées distinct es)
 struct Cellule * LP ; // donne accès à l’adresse de tête de la liste chaînée des personnes inscrites  à cette activité
} Cahier;

typedef struct Dossier
{ struct Cahier TC[MaxC] ; // MaxC: nombre maximum de cahiers (constante globale)
  int NbC  ; // nombre de cahiers des inscriptions courantes. Nbc est compris entre 0 et MaxC-1
} Dossier;


void RemplissageAutomatique(Dossier *D)
{
//Tableau des activités à insérer dans l e dossier
char tabAct[3][20]={"Lecture","Jeu d'echecs","Tennis"};

// Tableau des personnes inscrites à l’activité 1 "Lecture"
char PerA1[3][10]={"Wadii","Youssef","Asma"};

//Tableau des personnes inscrites à l’activité 2 "Jeu d'echecs"
char PerA2[3][10]={"Nour","Mohamed","Emir"};

// Tableau des personnes inscrites à l’activité 3 "Tennis"
char PerA3[3][10]={"Wadii","Aziz","Sarra"};

int i; Cellule * cel;
D->NbC=0;

//Ajout de l'activité 1
strcpy(D->TC[0].NomA,tabAct[0]);
D->NbC++;
D->TC[0].LP=NULL;

//Insertion des personnes à l'activité 1. La nouvelle personne est insérée au débu t de liste.
for(i=2;i>=0;i--)
{ cel = (Cellule*)malloc(sizeof(Cellule));
if (cel == NULL)
printf("Allocation impossible !");
else
{ strcpy(cel->NomP,PerA1[i]);
cel->PP = D->TC[0].LP;
D->TC[0].LP = cel;
}
}

//Ajout de l'activité 2
strcpy(D->TC[1].NomA,tabAct[1]);
D->NbC++;
D->TC[1].LP=NULL;
//Insertion des personnes à l'activité 2. La nouvelle personne est insérée au débu t de liste.
for(i=2;i>=0;i--)
{ cel = (Cellule*)malloc(sizeof(Cellule));
if (cel == NULL)
printf("Allocation impossible !");
else
{ strcpy(cel->NomP,PerA2[i]);
cel->PP = D->TC[1].LP;
D->TC[1].LP = cel;
}
}


//Ajout de l'activité 3
strcpy(D->TC[2].NomA,tabAct[2]);
D->NbC++;
D->TC[2].LP=NULL;

//Insertion des personnes à l'activité 3. La nouvelle personne est insérée au débu t de liste.
for(i=2;i>=0;i--)
{ cel = (Cellule*)malloc(sizeof(Cellule));
if (cel == NULL)
printf("Allocation impossible !");
else
{ strcpy(cel->NomP,PerA3[i]);
cel->PP = D->TC[2].LP;
D->TC[2].LP = cel;
}
}
}


//VERIFICATION DE L'INSCRIPTION D'UNE PERSONNE A UNE ACTIVITE
/* Renvoie l'adresse de la cellule qui contient le nom NP s'il appartient a
la liste des personnes de tete T. Sinon, elle renvoie NULL.    */
Cellule * Appartient (char NP[20], Cellule *T)
{
	bool existe=false;
	while(!existe)
	{
		if(T != NULL )
		{
			
		  if(strcmp(NP,T->NomP)==0)
		  	existe=true;
		  else{
		 
		    existe=false;
		    T = T->PP;
		     }
		}else{
			return NULL;
		}
	}
	return T;
}

//RECHERCHE D'UNE ACTIVITE
/* Retourne l'indice de l'activite nommee NA dans le dossier D
si elle est y presente, sinon elle retourne -1.   */
int RechercheActivite (Dossier D, char NA[30])
{
    int i=0;
		for( i;i<D.NbC;i++){
			
			if(strcmp(NA,D.TC[i].NomA)==0){
				return i;
			}
		}
	
	    return -1;
}


// AJOUT D'UNE PERSONNE
/* Permet d'ajouter une personne de nom NP a la fin de la
   liste de tete T (la liste est supposee non vide).      */
void AjouterPersonne (char NP[20], Cellule *T)
{
	bool arriverALaFin = false;
	
	while(!arriverALaFin){
		if( T->PP == NULL)
		   arriverALaFin= true;
		else {
			 arriverALaFin= false;
			T= T->PP;
		}
		  	
	}
	
	Cellule *cel = (Cellule*)malloc(sizeof(Cellule));
    if (cel == NULL)
       printf("Allocation impossible !");
    else
    { strcpy(cel->NomP,NP);
       cel->PP = NULL;
      T->PP = cel;
    }   
    printf("inscription valider \n ");
	
}

// AJOUT D'UN NOUVEAU CAHIER D'INSCRIPTION
/*  Permet d'ajouter, dans le dossier D, un nouveau cahier d'inscriptions a l'activite
nommee NA
avec la personne de nom NP comme premier inscrit (c.a.d. l'activite NA est
ajoutee a la fin du :
tableau TC et la personne NP est ajoutee en tete de la liste des inscrits).
NB : NbC < MaxC (sinon, ajout impossible !)   */

void AjouterCahier (Dossier *D, char NP[20], char NA[30])
{
	if(D->NbC >= MaxC)
		printf("Dossier plain, ajout impossible !");
	else{
		strcpy(D->TC[D->NbC].NomA,NA);
		
		Cellule *cel = (Cellule*)malloc(sizeof(Cellule));
		
        if (cel == NULL)
       		printf("Allocation impossible !");
    	else
    	{ strcpy(cel->NomP,NP);
       	    cel->PP = NULL;
    	    D->TC[D->NbC].LP=cel;
    	}   
		D->NbC++;
	
	}
}

//  INSCRIPTION D’UNE PERSONNE A UNE ACTIVITE
void AjouterInscription (Dossier *D, char NP[20], char NA[30])
{
	int numActivite = RechercheActivite(*D,NA);
	
	if (numActivite >= 0)  // si l'activite existe dans le dossier
	{
		Cellule *personne = Appartient(NP,D->TC[numActivite].LP);
		
		if (personne == NULL) // la personne n'existe pas on vas l'ajouter a l'activite
		{
			AjouterPersonne(NP,D->TC[numActivite].LP);
		
		}
		else 
			printf("La personne est deja inscrit a cette activite \n");
			
	}else // si l'activite n'existe pas on vas l'ajouter au dossier
		AjouterCahier(D,NP,NA);
	
	
}

//   AFFICHAGE DES INSCRIPTIONS
void AfficherDossier (Dossier D, char NA[30])
{
	int numActivite = RechercheActivite(D,NA);
	Cellule *cel = D.TC[numActivite].LP;
	printf("%s : \n",D.TC[numActivite].NomA);
	
	while ( cel != NULL) {
		printf(" - %s  \n",cel->NomP);
		cel = cel->PP;
		
	}
	
	free(cel);
}


//  SUPPRESSION D’UNE PERSONNE
void SupprimerPersonne (Dossier *D, char NP[20], char NA[30])
{
	int numActivite = RechercheActivite(*D,NA);
	
	Cellule *cel = D->TC[numActivite].LP;
	
	if (Appartient ( NP, cel) != NULL )
	{
	
	if(strcmp(NP,cel->NomP)==0){
	 	free(D->TC[numActivite].LP);
	 	D->TC[numActivite].LP=cel->PP;
	 	
	}else{
			Cellule *cellulePrecedent=cel;
	 		cel =cel->PP;
	 	
	 		while(true)
			{   if(strcmp(NP,cel->NomP)==0)
				{
					if (cel->PP != NULL){
	 					cellulePrecedent->PP=cel->PP;
	 					free(cel);
	 					printf("supprimer avec succes \n");
	 					break;
	 					
				 	
					}else{
						free(cel);
						cellulePrecedent->PP=NULL;
						printf("supprimer avec succes \n");
						break;
					}	
				}else{
					cellulePrecedent=cel;
					cel =cel->PP;
				}
	 			 	
		 	}	
	 			
	 			
			
		 	
	   }
   } else {
   	printf("\n Impossible de supprimer,la personne n'existe pas dans l'activite \n");
   }
	
}


void clean_stdin(void)
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}
  
char*  lireLaLigne()
{
	// cette fonction permet de lire la ligne avec les espaces
	char chaine[SIZE]=" " ;
	int rtn = 0;
 
    			do
   				 {
        			rtn = scanf("%"XSTR(SIZE)"[^\n]",chaine );
        			clean_stdin();
    				}
   				 while (rtn != 1);
   				 
   return strdup(chaine);
}

int main()
{
    
    //Dossier des inscriptions du club
    Dossier DossierDuClub;
    DossierDuClub.NbC=-1; // dossier vide
    
    // la variable option est utiliser pour selection les choix.
    unsigned int Option = 0; 
    
    // declaration de variable pour recuprer le nom et l'activité.
    char *nom;
    char *activite;
    
    // Boucle ce répete tantque on a pas choisi l'option 6(Quitter).
    while( Option != 6 ){
    	
    	printf("\n\n       --- MENU ---    \n");
    	printf("1. Remplissage automatique \n");
    	printf("2. Ajouter une inscription \n");
    	printf("3. Afficher toutes les activites du club \n");
		printf("4. Afficher les personnes inscrites a une activite \n");
		printf("5. Supprimer une personne d une activite \n");
    	printf("6. Quitter \n");
    	
    	printf("\n\n Entrez votre choix : \n");
    	rewind(stdin) ; /* vide le tampon clavier */
    	scanf ("%d",&Option);
		
		switch (Option)
    	{
    	case 1:
        	
        	RemplissageAutomatique( &DossierDuClub);
        	printf(" Remplissage automatique terminer \n ") ;
        break ;
        
   		 case 2:
        	printf(" Ajouter une inscription : \n") ;
        	printf(" Entrez le nom: ") ;
        	nom=lireLaLigne();
            printf("\n") ;
        	printf(" Entrez  l'activite: ") ;
        	activite = lireLaLigne();
            printf("\n") ;
            AjouterInscription (&DossierDuClub,nom, activite);
            
        break ;
        
    	case 3:
        	printf(" Afficher toutes les activites du club \n") ;
        	
        	if(DossierDuClub.NbC< 0){
        		printf(" \n Le Club n'a pas d'inscrit \n") ;
			}else{
		
        		int i=0;
        		for( i=0;i<DossierDuClub.NbC;i++)
        		{
        		AfficherDossier (DossierDuClub, DossierDuClub.TC[i].NomA);
				}
				printf(" \n Affichage termier \n") ;
        	}
        break ;
        
        case 4:
        	printf(" Afficher les personnes inscrites a une activite \n") ;
        	if(DossierDuClub.NbC< 0){
        		printf(" \n Le Club n'a pas d'inscrit \n") ;
			}else{
				printf(" Entrez votre activite: ") ;
        		activite = lireLaLigne();
        		printf("\n") ;
        		AfficherDossier (DossierDuClub, activite);
        		printf(" \n Affichage termier \n") ;
        	}
        break ;
        
        case 5:
        	printf(" Supprimer une personne d une activite \n") ;
        	if(DossierDuClub.NbC< 0){
        		printf(" \n Le Club n'a pas d'inscrit \n") ;
			}else{
				printf(" Entrez le nom: ") ;
				
				nom=lireLaLigne();
            	printf("\n") ;
        		printf(" Entrez  l'activite: ") ;
                activite = lireLaLigne();
				SupprimerPersonne ( &DossierDuClub,nom, activite);
			}
        break ;
        
        case 6:
        	printf("Quitter") ;
        break ;
        
    	default :
        	printf("\n Quitter !") ;
        	Option=6;
        }
	}
    
    return 0;
}

