/**
 * \file Menu.h
 * \brief Fichier header de Menu.c et contient la structure Zone.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "macro_profiler.h"

/**
 * \struct Zone
 * \brief Structure pour définir la surface d'une zone rectangulaire. Utilisable surtout pour les boutons.
 */
typedef struct zone {
	int x1;
	int y1;
	int x2;
	int y2;
} Zone;

void affiche_menu(Zone *load, Zone *tree, Zone *symbol, Zone *quit);

int recup_clic_menu(Zone *load, Zone *tree, Zone *symbol, Zone *quit);

char* file_to_load(Zone *load);

void draw_load(Zone *load);

void draw_load_symbol(Zone *symbol);

#endif