/**
 * \file draw.c
 * \brief Regroupe les fonctions d'affichage graphique.
 * \auhtor KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */
#include "../include/draw.h"



/**
 * \fn void ouverture_fenetre()
 * \brief Ouvre une fenetre graphique. 
 */
void ouverture_fenetre(){
	PROFILE
	MLV_create_window("Projet", "projet",LONGUEUR+100, HAUTEUR+40); 
	return ;
}

/**
 * \fn void draw_noeud(Arbre a, int x, int y, int largeur, int hauteur,double time_racine, double time_pere)
 * \brief Cette fonction affiche graphiquement un noeud de l'arbre.
 *
 * \param a L'arbre à lire pour l'affichage.
 * \param x Position x de départ du premier noeud à afficher.
 * \param y Position y de départ du premier noeud à afficher.
 * \param largeur La largeur du carré représentant le premier noeud.
 * \param hauteur La hauteur du carré représentatn le premier noeud.
 * \param time_racine Le temps de la racine.
 * \param time_pere Le temps du pere.
 */
void draw_noeud(Arbre a, int x, int y, int largeur, int hauteur,double time_racine, double time_pere){
	PROFILE
	if (a==NULL){
		return ;
	}
	if (largeur < 2*MINI+2*MINI_TEXT || hauteur< 2*MINI+2*MINI_TEXT){
		if (a->frere == NULL)
		MLV_draw_text(x+largeur/2, y+hauteur/2,"...",MLV_COLOR_BLACK);
		return ;
	}
	int taille;
	double color = (a->temps/time_racine)*255;
	if (largeur < hauteur){
		taille  = (a->temps / time_pere)*hauteur; 
		if (taille< 2*MINI_TEXT){
			if (a->frere != NULL){
				MLV_draw_text_box(x+MINI, y+MINI_TEXT,2*MINI_TEXT, 2*MINI_TEXT,"...",5,MLV_COLOR_BLACK,MLV_COLOR_BLACK, MLV_convert_rgba_to_color 	(color,255-color,0,255),
				MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
				draw_noeud(a->frere, x+MINI+2*MINI_TEXT,y+MINI+2*MINI_TEXT, largeur-2*MINI_TEXT-MINI, hauteur-2*MINI_TEXT-MINI,time_racine, time_pere);
			}else{
				MLV_draw_text(x+largeur/2, y+hauteur/2,"...",MLV_COLOR_BLACK);
			}
			return ;
		} 

		MLV_draw_text_box 	(x+MINI, y+MINI_TEXT, largeur-2*MINI, 
		taille	- 2* MINI, a->nom, 5, 
		MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_convert_rgba_to_color 	(color,255-color,0,255),
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );

		draw_noeud(a->fils, x+MINI, y+MINI_TEXT, largeur-2*MINI, taille-MINI_TEXT-2*MINI,time_racine, a->temps);
		hauteur-=taille;
		y += taille;
			
	}else{
		taille  = (a->temps / time_pere)*largeur;
		if (taille< 2*MINI_TEXT){
			if (a->frere != NULL){
				MLV_draw_text_box(x+MINI, y+MINI_TEXT,2*MINI_TEXT, 2*MINI_TEXT,"...",5,MLV_COLOR_BLACK,MLV_COLOR_BLACK, MLV_convert_rgba_to_color 	(color,255-color,0,255),
				MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
				draw_noeud(a->frere, x+MINI+2*MINI_TEXT,y+MINI+2*MINI_TEXT, largeur-2*MINI_TEXT-MINI, hauteur-2*MINI_TEXT-MINI,time_racine, time_pere);
			}else{
				MLV_draw_text(x+largeur/2, y+hauteur/2,"...",MLV_COLOR_BLACK);
			}
			return ;
		} 
		
		MLV_draw_text_box 	(x+MINI, y+MINI_TEXT, taille-2*MINI, 
		hauteur- 2* MINI, a->nom, 5, 
		MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_convert_rgba_to_color 	(color,255-color,0,255),
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );

		draw_noeud(a->fils, x+MINI, y+MINI_TEXT+MINI, taille-2*MINI, hauteur-MINI_TEXT-2*MINI, time_racine, a->temps);
		x += taille;  
		largeur-=taille+MINI;
	}
	draw_noeud(a->frere, x,y, largeur, hauteur,time_racine, time_pere);
	return ;
}

/**
 * \fn void draw_line_recap(RECAP rec, int index ,int nb_ligne)
 * \brief Affiche une ligne du tableau de récapitulation des appels.
 * 
 * \param rec Les appels de fonction à afficher.
 * \param index Détermine la ligne à afficher.
 * \param nb_ligne Le nombre de ligne à dessiner.  
 */
void draw_line_recap(RECAP rec, int index ,int nb_ligne){
	PROFILE

	int hauteur = MLV_get_window_height();
    int largeur = MLV_get_window_width();
    char tab[4][30];
	if (index == -1){
		strcpy(tab[0] ,"FUNCTION NAME");
		strcpy(tab[1] ,"NUMBER OF CALLS");
		strcpy(tab[2] ,"AVERAGE TIME PER CALL");
		strcpy(tab[3] ,"CUMULATED TIME");
	}else{
		strcpy(tab[0] ,rec.tab[index].name);
		sprintf(tab[1], "%d", rec.tab[index].nb_appels);
		sprintf(tab[2], "%lf", rec.tab[index].avg_time);
		sprintf(tab[3], "%lf", rec.tab[index].cumul_time);
	}
	int j;
	for (j=0;j<4;j++){
		MLV_draw_text_box 	(largeur*0.15+200*j, hauteur*0.15+30* nb_ligne,200 ,30, tab[j],5, 
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}
	return;
}

/**
 * \fn void draw_recap(RECAP rec, int page)
 * \brief Affiche le tableau de récapitulation en entier.
 *
 * \param rec La structure contenant les fonctions.
 * \param page La page.  
 */
void draw_recap(RECAP rec, int page){
	PROFILE
	MLV_clear_window(MLV_COLOR_LIGHT_CYAN);
	int hauteur = MLV_get_window_height();
    int largeur = MLV_get_window_width();
    int width, height;
	int i= page*15, k = i+15;
	MLV_get_size_of_text("TABLE OF SYMBOLS ", &width, &height);
    MLV_draw_text(largeur*0.5 - width*0.5, hauteur*0.1 , "TABLE OF SYMBOLS", MLV_COLOR_ROYALBLUE1);
    draw_line_recap(rec, -1 ,1);
	for(i=page*15;(i<k && i<rec.taille); i++){
		draw_line_recap(rec, i,2+i%15);
	}
	MLV_draw_text_box 	(0,hauteur-50,200,50, "TRI_PAR_NB_APPELS",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	MLV_draw_text_box 	(200,hauteur-50,200,50, "TRI_PAR_TEMPS_MOYEN",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	MLV_draw_text_box 	(400,hauteur-50,200,50, "TRI_PAR_TEMPS_CUMULE",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	if (page!=0){
		MLV_draw_text_box 	(600,hauteur-50,200,50, "PAGE PRECEDENTE",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}
	if(i!=rec.taille){
		MLV_draw_text_box 	(800,hauteur-50,200,50, "PAGE SUIVANTE",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}
	MLV_draw_text_box 	(1000,hauteur-50,200,largeur-1000, "MENU",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_FOREST_GREEN,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	MLV_actualise_window();
	return;
}

/**
 * \fn int recup_clic_recap(int page, RECAP rec)
 * \brief Fonction récuperant le clique des options du tableau de récupération.
 * 
 * \param page La page.
 * \param rec La structure contenant les fonctions.
 * \return Retourne la position x du clique.
 */
int recup_clic_recap(int page, RECAP rec){
	PROFILE
	int hauteur = MLV_get_window_height();
	int x = 0,y=0;
	MLV_wait_mouse(&x,&y);
	while(y<hauteur-50 || (page*15+15>rec.taille && (x>800 && x<1000)) || (page == 0 && (x>600 && x<=800) ) ){
		MLV_wait_mouse(&x,&y);
	}
	return x/200;
}

/**
 * \fn void button(Arbre a, Arbre racine)
 * \brief Affiche les options graphique du "graphic tree".
 * 
 * \param a L'arbre dont on affiche les options.
 * \param racine La racine du noeud.
 */
void button(Arbre a, Arbre racine){
	PROFILE
	int hauteur = MLV_get_window_height();
    int largeur = MLV_get_window_width();
    if(a->pere != NULL){
    MLV_draw_text_box 	(0,hauteur-50,200,50, "-> PERE",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}
	if (a->fils != NULL){
    MLV_draw_text_box 	(200,hauteur-50,200,50, "-> FILS",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}


	if ((a->pere!=NULL )&& (a->pere->fils) != a){
    	MLV_draw_text_box 	(400,hauteur-50,200,50, "-> FRERE GAUCHE",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}


	if (a->frere != NULL){
    MLV_draw_text_box 	(600,hauteur-50,200,50, "-> FRERE DROIT",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}
	if(a!= racine){
    MLV_draw_text_box 	(800,hauteur-50,200,50, "RETOUR RACINE MAIN",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	}


	MLV_draw_text_box 	(1000,hauteur-50,200,largeur-1000, "MENU",5,
		MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_FOREST_GREEN,
		MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
	MLV_actualise_window();
	return;
}

/**
 * \fn int recup_click_tree(Arbre a, Arbre racine)
 * \brief Recupère l'option selectionné par l'utilisateur dans le "Graphis Tree".
 * 
 * \param a L'arbre affiché sur le graphique. 
 * \param racine La racine du noeud de l'arbre affiché.
 * \return Retourne un entier selon l'option.
 */
int recup_click_tree(Arbre a, Arbre racine){
	PROFILE
	int x=0,y=0;
	int hauteur = MLV_get_window_height();
	while(1){
		while (y<hauteur-50){
			MLV_wait_mouse(&x,&y);
		}
		if (a->pere != NULL && x<200){
    		return 0;
		}
		if (a->fils != NULL && x<400 && x>200){
    		return 1;
		}
		if ((a->pere!=NULL )&& (a->pere->fils) != a && x<600 && x>400){
			return 2;
		}
		if (a->frere != NULL  && x<800 && x>600){
			return 3;
		}
		if(a!= racine && x>800 && x<1000){
			return 4;
		}
		if(x>1000){
			return 5;
		}
		MLV_wait_mouse(&x,&y);
	}
	
}

/**
 * \fn void quitter()
 * \brief Ferme la fenetre graphique. 
 */
void quitter(){
	PROFILE
    MLV_free_window();
    return;
}

/**
 * \fn void action_recap(int act, RECAP* rec, int* page)
 * \brief Affiche le tableau de recapitulation selon les options.
 * 
 * \param act Entier représentant l'option de navigation choisi.
 * \param rec L'ensemble des fonctions.
 * \param page La page. 
 */
void action_recap(int act, RECAP* rec, int* page){
	PROFILE
	switch (act){
		case 0:tri(rec,0);draw_recap(*rec, *page=0);break;
		case 1:tri(rec,1);draw_recap(*rec, *page=0);break;
		case 2:tri(rec,2);draw_recap(*rec, *page=0);break;
		case 3: (*page)--;draw_recap(*rec, *page);break;
		case 4: (*page)++;draw_recap(*rec, *page);break;
	}
	return;
}

/**
 * \fn void action_tree(int act, RECAP* rec, Arbre* tmp, Arbre racine)
 * \brief Affiche graphiquement l'arbre selon les options.
 * 
 * \param act Entier représentant l'option de navigation choisi.
 * \param rec L'ensemble des fonctions.
 * \param tmp L'arbre qu'il faut afficher.
 * \param racine Racine de l'arbre.
 */
void action_tree(int act, RECAP* rec, Arbre* tmp, Arbre racine){
	PROFILE
	Arbre temp = *tmp;
	switch (act){
		case 0:*tmp=(*tmp)->pere;break;
		case 1:*tmp=(*tmp)->fils;break;
		case 2:*tmp = (*tmp)->pere->fils;while((*tmp)->frere!= temp){*tmp=(*tmp)->frere;}break;
		case 3:*tmp=(*tmp)->frere;break;
		case 4: *tmp=racine;break;
	}
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_noeud(*tmp,-MINI,-MINI_TEXT,LONGUEUR, HAUTEUR,(*tmp)->temps, (*tmp)->temps);
	MLV_actualise_window();
	return;
}
