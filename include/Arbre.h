/**
 * \file Arbre.h
 * \brief Contient la structure de noeud.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#ifndef __ARBRE__
#define __ARBRE__



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * \struct Noeud
 * \brief Un noeud de l'arbre, correspondant à une fonction appelée.
 */
typedef struct noeud{
	char *nom; 				/*!< Nom de la fonction */
	double temps;			/*!< Temps lors de l'appel */
	struct noeud *fils; 	/*!< Adresse du noeud fils, NULL à l'initialisation */
	struct noeud *frere;	/*!< Adresse du noeud frere, NULL à l'initialisation */
	struct noeud *pere;		/*!< Adresse du noeud pere */
} Noeud, *Arbre;

Noeud* alloue_noeud(char* str, double t, Arbre pere);

void affiche_arbre(Arbre a);

Arbre lecture_fichier(FILE *fichier);

int lecture_ligne(FILE *fichier, char* name, double* time);

void lecture_aux(FILE *fichier, char* name, double* time, Arbre a);

int Ajouter_fils(Arbre a,char* str, double t);

int Ajouter_frere(Arbre a,char* str, double t);

Arbre cre_arbre(FILE *profiler);
#endif
