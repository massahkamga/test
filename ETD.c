#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
struct etudiant {
    char mat[10] ;
    char nom[30] ;
    int tab_note[4] ; /// quatre notes
};
typedef struct etudiant ETUDIANT;///Simplification de la manipulation de cette structure sans pour autant avoir à utiliser le mot-cle place devant etudiant
///Definition de la structure liste d'étudiants
struct cellule{
ETUDIANT e;
struct cellule *suivant;
};
typedef struct cellule *LISTE_E; /// une LISTE_P chainée est un pointeur sur la première cellule

ETUDIANT *lire_etudiant1(){
    ETUDIANT *ptr_e;
    int i;
    float n;
    ptr_e=(ETUDIANT*)malloc(sizeof(ETUDIANT));
    printf("Entre le matricule de l'etudiant:\n ");
    scanf("%s",(ptr_e->mat));
    printf("Entre le nom de l'etudiant:\n ");
    scanf("%s",(ptr_e->nom));
    for(i=0;i<4;i++){
         do{
        printf("Entre la note numero %d de l'etudiant %s\n:",i+1,ptr_e->nom);
        scanf("%f",&n);
        (ptr_e->tab_note)[i]=n;
        }
        while((ptr_e->tab_note)[i]>20);
    }
    return ptr_e;
}

ETUDIANT* lire_etudiant2(ETUDIANT *pe){
    int i;
    pe=(ETUDIANT*)malloc(sizeof(ETUDIANT)*1);
    printf("Entrer le matricule de l'etudiant.\n");
	scanf("%s",pe->mat);
    printf("Entrer le nom de l'etudiant \n");
    scanf("%s",pe->nom);
    for(i=0; i<4; i++){
        do{
        printf("Entrer la note %d de l'etudiant %s\n", i+1,(pe->nom));
        scanf("%d",&(pe->tab_note)[i]);
        }
        while(pe->tab_note[i]>20);
    }
    return pe;
}

///CALCULE DE LA MOYENNE DE L'ETUDIANT
float moyenne(ETUDIANT e){
    int i;
    float moy,soe=0;
    for(i=0; i<4; i++){
        soe=soe+e.tab_note[i]; //Boucle qui permet de stocker à chaque fois dans la variable soe, la somme de toutes les 4 tab_notes de l'etudiant
    }
    moy=soe/i; //Calcul de la moyenne des tab_notes sachant que le compteur i sort de la boucle avec le nombre de tab_notes
    return moy;
}
/// 3) afficharge dun etudiant *pe a lecran
 void affiche_etud1(ETUDIANT *pe){
    printf("\n%s\t\t %s\t\t %d\t %d\t %d\t %d\t %.2f \n",(pe->mat),(pe->nom),(pe->tab_note[0]),(pe->tab_note[1]),(pe->tab_note[2]),(pe->tab_note[3]),moyenne(*pe));
    return;
 }
///probleme affiche etudant)
void affiche_etud2(ETUDIANT e){
    printf("MATRICULE\t NOM(S)\t\t NOTE1\t NOTE2\t NOTE3\t NOTE4\t MOYENNE\n");
    printf("\n%s\t %s\t %d\t %d\t %d\t %d\n",e.mat,e.nom,e.tab_note[0],e.tab_note[1],e.tab_note[2],e.tab_note[3]);
    return;
}
///procedure verifiant si une liste est vide
int liste_vide(LISTE_E le){
	if(le==NULL) return TRUE;
	else return FALSE;
}

/// ajout_en_queue...
LISTE_E ajout_en_queue(LISTE_E l,ETUDIANT e){
    LISTE_E li;
    struct cellule *ptc;
    ptc=(struct cellule*)malloc(sizeof(struct cellule));
    ptc->e=e;
    ptc->suivant=NULL;
    if(liste_vide(l))
        return ptc;
    else{
        li=l;
        while(li->suivant!=NULL){
            li=li->suivant;
        }
        li->suivant=ptc;
    }
    return l;
}


///procedure qui affiche une liste d'etudiant.
void affiche_list(LISTE_E le){
	if(liste_vide(le)){
		printf("\nIl n'y a rien a afficher, car la liste est vide.\n");
		return ;
	}
    LISTE_E l1=le;
    printf("MATRICULE\t NOM(S)\t\t NOTE1\t NOTE2\t NOTE3\t NOTE4\t MOYENNE\n");
    while(l1!=NULL){
        printf("%s\t\t %s\t\t %d\t %d\t %d\t %d\t %.2f\n", l1->e.mat,l1->e.nom,l1->e.tab_note[0],l1->e.tab_note[1],l1->e.tab_note[2],l1->e.tab_note[3],moyenne(l1->e));
        l1=l1->suivant;
		}
		return ;
	}

	/*
int main(){
	ETUDIANT*e;
	e=(ETUDIANT*)malloc(sizeof(ETUDIANT));
	e=lire_etudiant1();
	affiche_etud2(*e);
	return 0;	
}  */

///fonction qui recherche un etudiant dans un liste connaissant son matricul
ETUDIANT* search_etudiant(LISTE_E le,char *matr){
    int i;
	while(le!=NULL){
		if(strcmp(le->e.mat,matr)==0){
			ETUDIANT *pte;
			pte=(ETUDIANT*)malloc(sizeof(ETUDIANT)*1);
			strcpy(pte->mat,le->e.mat);
			strcpy(pte->nom,le->e.nom);
			for(i=0;i<4;i++)
			pte->tab_note[i]=le->e.tab_note[i];
			return pte;
		}
		le=le->suivant;
	}
	printf("L'ETUDIANT DE MATRICULE: %s n'est pas dans la liste\n", matr);
	return NULL;
}
///fonction qui suprime un etudiant dans une liste connaissant son matricule
LISTE_E delette(LISTE_E le, char* matr){
	struct cellule *pl1,*pl2;
	ETUDIANT *p;
	pl2=(struct cellule*)malloc(sizeof(struct cellule)*1);
	pl1=(struct cellule*)malloc(sizeof(struct cellule)*1);
	pl1=le;
	if(liste_vide(le)){
		//printf("Il n'y a rien a supprimer car cette liste est vide \n");
		return NULL;
	}
    if(strcmp(pl1->e.mat,matr)==0){
                le=pl1->suivant;
                //printf("supression avec succes!!!! \n");
                free(pl1);
        return le;
    }
    p=search_etudiant(le,matr);
    if(p!=NULL){
    while(pl1!=NULL){
        if(strcmp(((pl1->suivant)->e).mat,matr)==0){
        pl2=pl1->suivant;
        pl1->suivant=(pl1->suivant)->suivant;
        free(pl2);
        //printf("supression avec succes!!!! \n");
        return le;
    }
    pl1=pl1->suivant;
	}
    }
    printf("echec de la supression car l'etudiant de matricule: %s n'est pas dans la liste!!!! \n",matr);
    return le;
}

///fonction determinant le nombre d'etudiant dans une liste
int taille(LISTE_E le){
	int cpt=0;
    while(le!=NULL){
        le=le->suivant;
        cpt++;
    }
		return cpt;
	}


///8 fonction qui trie les etudiants par moyenne CROISSANTE
void trie_bulle(LISTE_E le){
    int i,j,n;
    ETUDIANT *pe;
    struct cellule *ple;
    pe=(ETUDIANT*)malloc(sizeof(ETUDIANT)*1);
    ple=(struct cellule*)malloc(sizeof(struct cellule));
    n=taille(le);
    for(i=0;i<n;i++){
        ple=le;///permet de revenir au debut de la liste.
        j=0;
        while(ple->suivant!=NULL){///nous permet de parcourrir la partie non trie de la liste
            if(j>n-1-i){
                break;///break  met fin a la boucle while.
            }
            else{
                if(moyenne(ple->e)>moyenne((ple->suivant)->e)){
               *pe=ple->e;
               ple->e=(ple->suivant)->e;
               (ple->suivant)->e=*pe;
            }
            }
            j++;
            ple=ple->suivant;
        }
    }
     printf("trie effectuer!!!\n");
     return;
}

///CLASSEMENT DES ETUDIANTS PAR ORDRE ALPHABETIQUE
void ORDRE_ALPHABETIQUE(LISTE_E le){
    int i,j,n;
    ETUDIANT *pe;
    struct cellule *ple;
    pe=(ETUDIANT*)malloc(sizeof(ETUDIANT)*1);
    ple=(struct cellule*)malloc(sizeof(struct cellule));
    n=taille(le);
    for(i=0;i<n;i++){
        ple=le;///permet de revenir au debut de la liste.
        j=0;
        while(ple->suivant!=NULL){//nous permet de parcourrir la partie non trie de la liste
            if(j>n-1-i){
                break;///break  met fin a la boucle while.
            }
            else{
                if(strcmp(ple->e.nom, (ple->suivant)->e.nom)>0){
               *pe=ple->e;
               ple->e=(ple->suivant)->e;
               (ple->suivant)->e=*pe;
            }
            }
            j++;
            ple=ple->suivant;
        }
    }
     printf("ordre alphabetique effectuer!!!\n");
     return;
}
///fonction qui copie le contenue d'une liste dans un fichier
int list_to_file(char *nom_f,LISTE_E le){
    FILE *in_file;
    printf("Entrer le nom du fichier \n");
    scanf("%s",nom_f);
    in_file=fopen(nom_f,"w");
    while(le!=NULL){
        fprintf(in_file,"%s\t %s\t %d\t %d\t %d\t %d\n",le->e.mat,le->e.nom,le->e.tab_note[0],le->e.tab_note[1],le->e.tab_note[2],le->e.tab_note[3]);
        le=le->suivant;
    }
    fclose(in_file);
    printf("\n La liste d'etudiants a ete enregistree avec succes dans le fichier %s!!\n",nom_f);
    return 0;
}



///Définition de la fonction qui prend le contenu d'un fichier et le charge dans une liste d'etudiants, qui retourne un pointeur sur une liste d'etudiants, et prend en parametre le nom du fichier
LISTE_E file_to_list(LISTE_E le){
    FILE *in_file=NULL;
    struct cellule *ple;
    ETUDIANT e;
    char nf[15];
    ple=(struct cellule*)malloc(sizeof(struct cellule) );
    ple=le;
    printf("entrer le nom du fichier a ouvrir\n");
    scanf("%s",nf);
    in_file=fopen(nf,"r");///Ouverture du fichier en mode lecture
    if(in_file == NULL){
            printf("\n Le fichier %s n'existe pas \n", nf);  //Dans le cas ou le fichier n'existe pas il affiche le message
           return NULL;
    }
        while(!feof(in_file)){
            fscanf(in_file,"%s %s %d %d %d %d",e.mat,e.nom,&e.tab_note[0],&e.tab_note[1],&e.tab_note[2],&e.tab_note[3]);  //On lit dans le fichier deux caracteres qui representent le matricule et le nom de l'etudiant
            ple=ajout_en_queue(ple,e);
        }
        fclose(in_file);  ///Fermeture du fichier
        printf("fichier enregistrer dans la liste\n");
        return ple;  ///On retourne le pointeur sur la liste d'etudian
}


int MENU(){
      int n;
      printf(" ********************************************** \n");
      
      printf(" ****************** MENU ********************** \n");
      printf(" 1...AJOUTER UN ETUDIANT ********************** \n");
      printf(" 2...SUPRIMER UN ETUDIANT ********************* \n");
      printf(" 3...TRIER LES ETUDIANTS PAR MOYENNE CROISSANTE \n");
      printf(" 4...AFICHER LES ETUDIANTS********************* \n");
      printf(" 5...RECHERCHER UN ETUDIANT******************** \n");
      printf(" 6...OUVRIR LE FICHIER DES ETUDIANTS*********** \n");
      printf(" 7...ENREGISTRER DANS UN FICHIER ************** \n");
      printf(" 9...QUITTER ********************************** \n");
      
      printf(" ********************************************** \n");
     do{
      printf(" choisez le numero de votre MENU \n");
      scanf("%d",&n);
     }while(n<1 || n>8);
     return n;
 }


int main(){
    ETUDIANT *pe=NULL;
    LISTE_E le=NULL;
    int n;
    char m[2],nf[25],matr[10];
    printf(" *** GESTION DES ETUDIANTS*********************\n");
   do{
    n=MENU();

    switch(n){
        case 1:
            pe=lire_etudiant1();
            le=ajout_en_queue(le,*pe);
            break;
        case 2:
            printf("entrer le matricule de l'etudiant a suprimer\n");
            scanf("%s",matr);
            le=delette(le,matr);
            break;
        case 3:
            n=taille(le);
            trie_bulle(le);
            affiche_list(le);
            break;
        case 4:
            affiche_list(le);
            break;
        case 5:
            printf("entrer le matricule de l'etudiant que vous rechercher\n");
            scanf("%s",matr);
            pe=search_etudiant(le,matr);
            if(pe!=NULL){
                printf("L'employe de mtricule %s est effectivement dans la liste\n", matr);
                affiche_etud1(pe);
            }
            break;
        case 6:
            le=file_to_list(le);
            break;
        case 7:
            list_to_file(nf,le);
            break;
        /*case 8:
            ORDRE_ALPHABETIQUE(le);
            affiche_list(le);
            break;*/
        case 8:
            printf("*****MERCI DE REVENIR TRES PROCHAINNEMENT!*****\n");
            return 0;
    }
    do{
        printf("pour revenir au menu cliquez sur 0  OU sur 8 pour sortir du programme...\n");
        scanf("%s",m);
        system("cls");
      }while(strcmp(m,"0")!=0 && strcmp(m,"8")!=0);
    }
    while(strcmp(m,"8")!=0);
    printf("*****MERCI DE REVENIR TRES PROCHAINNEMENT!*****\n");
    return 0;
    return 0;
}
