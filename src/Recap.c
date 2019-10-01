/**
 * \file Recap.c
 * \brief Fichier regroupant les fonctions de récapitulation.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#include "../include/Recap.h"

/**
 * \fn FONCT new_fonct(char* nom, double cumul_time)
 * \brief Créer les données d'une fonction.
 *
 * \param nom Le nom de la fonction.
 * \param cumul_time Le temps d'execution de la fonction.
 * \return Retourne une fonction FONCT.  
 */
FONCT new_fonct(char* nom, double cumul_time){
	PROFILE
	FONCT nouveau;
	nouveau.name = strdup(nom);
	nouveau.nb_appels = 1;
	nouveau.avg_time = cumul_time;
	nouveau.cumul_time = cumul_time;
	return nouveau;
}	

/**
 * \fn void update_fonct(RECAP* rec, int index, double new_time)
 * \brief Met à jour une fonction.
 *
 * \param rec La structure RECAP contenant la fonction à mettre à jour.
 * \param index L'index du tableau de rec.
 * \param new_time Le nouveau temps de la fonction. 
 */
void update_fonct(RECAP* rec, int index, double new_time){
	PROFILE
	rec->tab[index].nb_appels++;
	rec->tab[index].cumul_time+=new_time;
	rec->tab[index].avg_time = rec->tab[index].cumul_time/ rec->tab[index].nb_appels;
	return ;
}

/**
 * \fn int is_fonct_in_recap(RECAP rec, char* nom)
 * \brief Cherche dans rec si une fonction est présente.
 * 
 * \param rec Le récapitulatif des fonctions.
 * \param nom Le nom de la fonction qu'on cherche.
 * \return Retourne l'indice du tableau correspondant à la fonction cherchée, -1 sinon. 
 */
int is_fonct_in_recap(RECAP rec, char* nom){
	PROFILE
	int i = 0 ;
	while(i<rec.taille){
		if (strcmp(rec.tab[i].name,nom) == 0){
			return i;
		}
		i++;
	}
	return -1;
}


/**
 * \fn void lecture_arbre_aux(Arbre a, RECAP* rec)
 * \brief Fonction auxiliaire qui permet de créer le tableau de récapitulatif des fonctions de l'arbre.
 * 
 * \param a L'arbre a parcourir.
 * \param rec La structure qu'il faut modifier en ajoutant les fonctions.
 */
void lecture_arbre_aux(Arbre a, RECAP* rec){
	PROFILE
	if (a == NULL){
		return ;
	}
	int i = is_fonct_in_recap(*rec, a->nom);
	if (i!=-1){
		update_fonct(rec, i, a->temps);
	}else{
		rec->tab[rec->taille] = new_fonct(a->nom, a->temps);
		rec->taille++;
	}
	lecture_arbre_aux(a->fils, rec);
	lecture_arbre_aux(a->frere, rec);
	return ;
}

/**
 * \fn void lecture_arbre(Arbre a, RECAP* rec)
 * \brief Fonction qui permet de créer un tableau de récapitulatif des fonctions de l'arbre.
 * 
 * \param a L'arbre a parcourir.
 * \param rec La structure qu'il faut modifier en ajoutant les fonctions.
 */
void lecture_arbre(Arbre a, RECAP* rec){
	PROFILE
	if (a == NULL){
		return ;
	}
	int i = is_fonct_in_recap(*rec, a->nom);
	if (i!=-1){
		update_fonct(rec, i, a->temps);
	}else{
		rec->tab[rec->taille] = new_fonct(a->nom, a->temps);
		rec->taille++;
	}
	lecture_arbre_aux(a->fils, rec);
	return ;
}

/**
 * \fn RECAP creation_recap(Arbre a)
 * \brief Création d'un RECAP.
 *
 * \param a L'arbre qu'il faut parcourir pour créer le RECAP.
 * \return Retourne le RECAP crée. 
 */
RECAP creation_recap(Arbre a){
	PROFILE
	RECAP rec;
	rec.taille=0;
	lecture_arbre(a, &rec);
	return rec;
}

/**
 * \fn void affiche_recap(RECAP rec)
 * \brief Affiche les données de récapitulation des fonctions dans la sortie standard.
 *
 * \param rec Le RECAP qu'il faut affichier. 
 */
void affiche_recap(RECAP rec){
	PROFILE
	printf("%30s | %8s | %17s | %15s|\n","FUNCTION NAME","NB_CALLS","AVG_TIME_PER_CALL","TOTAL_TIME");
	int i = 0;
	for(i = 0;i<rec.taille;i++){
		printf("%30s | %8d | %17lf | %15lf|\n", rec.tab[i].name, rec.tab[i].nb_appels, rec.tab[i].avg_time, rec.tab[i].cumul_time);
	}
	return ;
}

/**
 * \fn int compar(RECAP* rec, int mode, int index)
 * \brief Fonction de comparaison entre une fonction et la suivante.
 * 
 * \param rec Le RECAP qu'il faut analyser.
 * \param mode Entier représentant le mode de comparaison.
 * \param index L'indice du tableau de RECAP, soit la fonction qu'il faut comparer.
 * \return Retourne 1 s'il y a eu une comparaison, 0 s'il la comparaison a échoué, -1 si mode invalide.
 */ 
int compar(RECAP* rec, int mode, int index){
	PROFILE
	switch (mode){
		case 0: if (rec->tab[index].nb_appels<rec->tab[index+1].nb_appels){
					return 1;
				}else{
					return 0;
				}break;
		case 1: if (rec->tab[index].avg_time<rec->tab[index+1].avg_time){
					return 1;
				}else{
					return 0;
				}break;
		case 2: if (rec->tab[index].cumul_time<rec->tab[index+1].cumul_time){
					return 1;
				}
				else{
					return 0;
				}break;
	}
	return -1;
}

/**
 * \fn void echange(RECAP* rec, int index)
 * \brief Echange 2 elements du tableau du récapitulatif des fonctions.
 *
 * \param rec Le RECAP.
 * \param index L'indice et son suivant su tableau qu'il faut échanger. 
 */
void echange(RECAP* rec, int index){
	PROFILE
	FONCT tmp = rec->tab[index];
	rec->tab[index] = rec->tab[index+1];
	rec->tab[index+1] = tmp;
	return ;
}

/**
 * \fn void tri(RECAP* rec, int mode)
 * \brief Tri des fonctions de RECAP.
 *
 * \param rec Le RECAP a trier.
 * \param mode Le mode de tri.
 */
void tri(RECAP* rec, int mode){
	PROFILE
    int passage = 0;
    int permutation = 1;
    int en_cours;
    while ( permutation) {
        permutation = 0;
        passage ++;
        for (en_cours=0;en_cours<rec->taille-1;en_cours++) {
        	if(compar(rec, mode, en_cours)){
        		echange(rec,en_cours);
        		 permutation = 1;
        	}
        }
    }
    return ;
}

/**
 * \fn RECAP recap(Arbre test)
 * \brief Affiche dans la sortie standard le récapitulatif des fonctions appelées.
 *
 * \param test L'arbre dont on fait des tries.
 * \return Retourne un RECAP de l'arbre test.
 */
RECAP recap(Arbre test){
	PROFILE
	RECAP res = creation_recap(test);
	printf("\n-------------------------------TRI PAR NOMBRE D'APPELS------------------------\n");
	tri(&res,0);
	affiche_recap(res);
	printf("\n-------------------------------TRI PAR TEMPS MOYEN----------------------------\n");
	tri(&res,1);
	affiche_recap(res);
	printf("\n-------------------------------TRI PAR TEMPS CUMULE---------------------------\n");
	tri(&res,2);
	affiche_recap(res);
	return res;
}

