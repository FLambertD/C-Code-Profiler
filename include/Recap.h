/**
 * \file Recap.h
 * \brief Fichier header de Recap.c et contient les structures FONCT et RECAP.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#ifndef __RECAP__
#define __RECAP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arbre.h"
#include "macro_profiler.h"


#define TAILLE_MAX 100

/**
 * \struct FONCT
 * \brief Représente une fonction de l'appel.
 */
typedef struct fonct{
	char* name;				/*!< Nom de la fonction */
	int nb_appels;			/*!< Le nombre d'appel de cette fonction */
	double avg_time;		/*!< Le temps moyen d'execution de cette fonction */
	double cumul_time;		/*!< Le temps d'appel cumulé de la fonction  */
}FONCT;

/**
 * \struct RECAP
 * \brief Représente l'ensemble des fonctions.
 */
typedef struct recap{
	FONCT tab [TAILLE_MAX];		/*!< Tableau des fonctions */
	int taille;					/*!< Le nombre de fonction sans doublon */
}RECAP;



FONCT new_fonct(char* nom, double cumul_time);

RECAP creation_recap(Arbre a);

int is_fonct_in_recap(RECAP rec, char* nom);

void update_fonct(RECAP* rec, int index, double new_time);

void affiche_recap(RECAP rec);

void lecture_arbre(Arbre a, RECAP* rec);

int compar(RECAP* rec, int mode, int index);

void tri(RECAP* rec, int mode);

void echange(RECAP* rec, int index);

RECAP recap(Arbre test);




#endif