/**
 * \file Main.c
 * \brief Fichier Main du programme.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#include "../include/Arbre.h"
#include "../include/draw.h"
#include "../include/Recap.h"
#include "../include/macro_profiler.h"
#include "../include/Menu.h"


/**
 * \fn void open_file(char* file_log, FILE** profiler, Zone* a, Zone* b, Zone* c,Zone* d)
 * \brief Ouvre le fichier entré par l'utilisateur.
 *
 *  
 */
void open_file(char* file_log, FILE** profiler, Zone* a, Zone* b, Zone* c,Zone* d){
	*profiler = fopen(file_log,"r");
	if (NULL == *profiler || file_log[strlen(file_log)-1] != 'g' || file_log[strlen(file_log)-2] != 'o' || file_log[strlen(file_log)-3] != 'l' || file_log[strlen(file_log)-4] != '.' ){
			printf("Erreur lors de l'ouverture du .log donné en argument\n");
			MLV_draw_text_box 	(a->x1,a->y1, a->x2-a->x1 ,50,  "Erreur lors de l'ouverture du .log",5,
			MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
			MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
			MLV_actualise_window();
			MLV_wait_milliseconds(1000);
			affiche_menu(a,b,c,d);

	}
}

/**
 * \fn void global(int argc, char* argv[])
 * \brief Le programme en entier.
 */
void global(int argc, char* argv[]){
	PROFILE
	ouverture_fenetre();
	FILE * file_log = NULL;
	char* log = "";
	Zone a,b,c,d;
	int z=-1 , k=0, page = 0;
	Arbre racine = NULL,test = NULL;
	RECAP rec ;
	affiche_menu(&a,&b,&c,&d);
	while((z=recup_clic_menu(&a,&b,&c,&d))!=0 ){
		if (z!=1 && file_log==NULL) {
			MLV_draw_text_box 	(a.x1,a.y1, a.x2-a.x1 ,50,  "YOU HAVE TO LOAD A FILE",5,
			MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
			MLV_TEXT_LEFT,MLV_HORIZONTAL_LEFT,MLV_VERTICAL_TOP );
			MLV_actualise_window();
			MLV_wait_milliseconds(1000);
			affiche_menu(&a,&b,&c,&d);
		}else{
			switch (z){
				case 1:log = file_to_load(&a); printf("%s\n",log );open_file(log,&file_log,&a,&b,&c,&d); if(file_log!=NULL){draw_load(&a);test=cre_arbre(file_log);racine=test;affiche_menu(&a,&b,&c,&d);}break;
				case 2:MLV_clear_window(MLV_COLOR_BLACK);draw_noeud(test,-MINI,-MINI_TEXT,LONGUEUR, HAUTEUR,test->temps, test->temps);MLV_actualise_window();
						button(test,racine);
						while((k=recup_click_tree(test,racine))!=5){
							action_tree(k, &rec, &test,racine);
							button(test,racine);
						}affiche_menu(&a,&b,&c,&d);break;
				case 3: draw_load_symbol(&c);
						rec = recap(test);
						draw_recap(rec, 0);
						while((k=recup_clic_recap(page, rec))!=5){
							action_recap(k,&rec,&page);
						}affiche_menu(&a,&b,&c,&d);break;
			}
		}
	}
	return;
}


int main(int argc, char* argv[]){
	PROFILE
	global(argc, argv);
	quitter();
	return 0;
}
