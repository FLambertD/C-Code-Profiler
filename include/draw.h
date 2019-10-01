/**
 * \file draw.h
 * \brief Fichier header de draw.c
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#ifndef __DRAW__
#define __DRAW__

#define LONGUEUR 1100
#define HAUTEUR 700
#define MINI 5 
#define MINI_TEXT 20


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLV/MLV_all.h"
#include "Arbre.h"
#include "Recap.h"
#include "macro_profiler.h"




void ouverture_fenetre();

void draw_noeud(Arbre a, int x, int y, int largeur, int hauteur,double time_racine, double time_pere);

void quitter();

void draw_recap(RECAP rec, int page);

int recup_clic_recap(int page, RECAP rec);

void button(Arbre a, Arbre racine);

int recup_click_tree(Arbre a, Arbre racine);

void action_recap(int act, RECAP* rec, int* page);

void action_tree(int act, RECAP* rec, Arbre* tmp, Arbre racine);

void quitter();
#endif
