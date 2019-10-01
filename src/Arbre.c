/**
 * \file Arbre.c
 * \brief Regroupe les fonctions utilisées à la création de l'arbre des appels.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#include "../include/Arbre.h"
#include "../include/macro_profiler.h"

/** 
 * \fn Noeud* alloue_noeud(char* str, double t, Arbre pere)
 * \brief Fonction d'allocation d'un noeud.
 *
 * \param str Une chaine de caractère soit le nom de la fonction du noeud.
 * \param t Un double correspondant au temps.
 * \param pere Le père du noeud.
 * \return Retourne un noeud, sinon retourne NULL. 
 */
Noeud* alloue_noeud(char* str, double t, Arbre pere){
	PROFILE
	Noeud* arb;
	arb = (Noeud*)malloc(sizeof(Noeud));
	if(NULL == arb){
		return NULL;
	}
	arb->nom = strdup(str);
	arb->temps = t;
	arb->fils = NULL;
	arb->frere = NULL;
	arb->pere = pere;
	return arb;
}

/**
 * \fn void affiche_arbre(Arbre a)
 * \brief Fonction d'affichage d'un arbre d'appel.
 *
 * \param a L'arbre à afficher.
 */
void affiche_arbre(Arbre a){
	PROFILE
	if(a != NULL){
		printf("%s %lf\n", (a)->nom, (a)->temps);
		affiche_arbre(((a)->fils));
		affiche_arbre(((a)->frere));
	}
	return ;
}
 
/**
 * \fn int Ajouter_fils(Arbre a,char* str, double t)
 * \brief Ajoute un noeud au fils de l'arbre passé en paramètre.
 *
 * \param a L'arbre auquel on ajoute le un noeud.
 * \param str Nom de la fonction du noeud.
 * \param t Temps de la fonction.
 * \return Retourne 1 allocation réussie, sinon retourne 0.
 */
int Ajouter_fils(Arbre a,char* str, double t){
	PROFILE
	Noeud* arb = alloue_noeud(str, t, a);
	if (arb == NULL){
		return 0;
	}
	a->fils = arb;
	return 1;
}

/**
 * \fn int Ajouter_frere(Arbre a,char* str, double t)
 * \brief Ajoute un noeud au frere de l'arbre passé en paramètre.
 *
 * \param a L'arbre auquel on ajoute le un noeud.
 * \param str Nom de la fonction du noeud.
 * \param t Temps de la fonction.
 * \return Retourne 1 allocation réussie, sinon retourne 0.
 */
int Ajouter_frere(Arbre a,char* str, double t){
	PROFILE
	Noeud* arb = alloue_noeud(str, t, a->pere);
	if (arb == NULL){
		return 0;
	}
	a->frere = arb;
	return 1;
}

/**
 * \fn int lecture_ligne(FILE *fichier, char* name, double* time_)
 * \brief Lit une ligne du fichier formaté .log
 *
 * \param fichier Le fichier à lire.
 * \param name Affectation par adresse d'une chaine de caractère lu dans le fichier.
 * \param time_ Affectation par adresse du temps lu dans le fichier.
 * \return Retourne 1 si la ligne bien lu, sinon retourne 0.  
 */
int lecture_ligne(FILE *fichier, char* name, double* time_){
	PROFILE
	char use [4][30];
	if (fscanf(fichier, "%s %s %s %s %lf%s", name, use[0], use[1], use[2], time_, use[3])!= EOF){
		return 1; 
	}
	return 0;
}

/**
 * \fn Arbre lecture_fichier(FILE * fichier)
 * \brief Lit le fichier .log en entier et créer un arbre d'appel des fonctions.
 *
 * \param fichier Le fichier à lire.
 * \return Retourne l'arbre créer lors de la lecture du fichier.
 */
Arbre lecture_fichier(FILE * fichier){
	PROFILE
	char name[30] = "";
	double time_;
	int test;
	int ouvert = 0;
	Arbre res = NULL;
	Arbre arb = NULL;
	if (fichier == NULL){
		return NULL;
	}
	test = lecture_ligne(fichier, name, &time_);
	while(test){
		if (strcmp(name,"END")!= 0){
			if(res == NULL){
				res = arb = alloue_noeud(name, time_, NULL);
				ouvert = 1;
			}else{
				if(ouvert){
					Ajouter_fils(arb, name, time_);
					arb = arb->fils;
				}else{

					arb= arb->fils;
					while (arb->frere != NULL)
						arb = arb->frere;
					Ajouter_frere(arb, name, time_);
					arb = arb->frere;
					ouvert = 1;
				}
			}
		}else{
			arb->temps = time_ - arb->temps;
			arb = arb->pere;
			ouvert = 0;
		}
		test = lecture_ligne(fichier, name, &time_);
	}
	return res;
}

/**
 * \fn Arbre cre_arbre(FILE *profiler)
 * \brief Fonction de création et d'affichage de l'arbre.
 *
 * \param profiler Le fichier à lire.
 * \return Retourne l'arbre. 
 */
Arbre cre_arbre(FILE *profiler){
	PROFILE

	Arbre test = lecture_fichier(profiler);

	affiche_arbre(test);

	fclose(profiler);

	return test;
}