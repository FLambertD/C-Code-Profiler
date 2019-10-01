/**
 * \file Menu.c
 * \brief Fichier regroupant les fonctions du menu.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */

#include "../include/Menu.h"

/**
 * \fn void affiche_menu(Zone *load, Zone *tree, Zone *symbol, Zone *quit)
 * \brief Fonction qui affiche graphiquement le menu.
 *
 * \param load La zone du cadran "load".
 * \param tree La zone du cadran "tree".
 * \param symbol La zone du cadran "symbol".
 * \param quit La zone du cadran "quit".
 */
void affiche_menu(Zone *load, Zone *tree, Zone *symbol, Zone *quit) {
    // Affiche un menu avec 4 choix, renvois par adresse les zones de clic de ces 4 choix.
    PROFILE
    int hauteur = MLV_get_window_height();
    int largeur = MLV_get_window_width();

    int width, height;

    MLV_clear_window(MLV_COLOR_LIGHT_CYAN);

    MLV_get_size_of_text("PROFILER", &width, &height);
    MLV_draw_text(largeur*0.5 - width*0.5, hauteur*0.1 , "PROFILER", MLV_COLOR_ROYALBLUE1);

    (*load).x1 = largeur*0.15;
    (*load).y1 = hauteur*0.15;
    (*load).x2 = (*load).x1 + largeur*0.7;
    (*load).y2 = (*load).y1 + hauteur*0.2;

    MLV_draw_rectangle((*load).x1, (*load).y1, (*load).x2 - (*load).x1, (*load).y2 - (*load).y1, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle((*load).x1 + 1, (*load).y1 + 1, (*load).x2 - (*load).x1 - 2, (*load).y2 - (*load).y1 - 2, MLV_COLOR_PALETURQUOISE);
    MLV_get_size_of_text("LOAD FILE", &width, &height);
    MLV_draw_text((*load).x1 + ((*load).x2 - (*load).x1)*0.5 - width*0.5, (*load).y1 + ((*load).y2 - (*load).y1)*0.5 - height*0.55, "LOAD FILE", MLV_COLOR_ROYALBLUE3);

    (*tree).x1 = largeur*0.15;
    (*tree).y1 = hauteur*0.35;
    (*tree).x2 = (*tree).x1 + largeur*0.7;
    (*tree).y2 = (*tree).y1 + hauteur*0.2;

    MLV_draw_rectangle((*tree).x1, (*tree).y1, (*tree).x2 - (*tree).x1, (*tree).y2 - (*tree).y1, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle((*tree).x1 + 1, (*tree).y1 + 1, (*tree).x2 - (*tree).x1 - 2, (*tree).y2 - (*tree).y1 - 2, MLV_COLOR_PALETURQUOISE);
    MLV_get_size_of_text("GRAPHIC TREE", &width, &height);
    MLV_draw_text((*tree).x1 + ((*tree).x2 - (*tree).x1)*0.5 - width*0.5, (*tree).y1 + ((*tree).y2 - (*tree).y1)*0.5 - height*0.55, "GRAPHIC TREE", MLV_COLOR_ROYALBLUE3);

    (*symbol).x1 = largeur*0.15;
    (*symbol).y1 = hauteur*0.55;
    (*symbol).x2 = (*symbol).x1 + largeur*0.7;
    (*symbol).y2 = (*symbol).y1 + hauteur*0.2;

    MLV_draw_rectangle((*symbol).x1, (*symbol).y1, (*symbol).x2 - (*symbol).x1, (*symbol).y2 - (*symbol).y1, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle((*symbol).x1 + 1, (*symbol).y1 + 1, (*symbol).x2 - (*symbol).x1 - 2, (*symbol).y2 - (*symbol).y1 - 2, MLV_COLOR_PALETURQUOISE);
    MLV_get_size_of_text("TABLE OF SYMBOLS", &width, &height);
    MLV_draw_text((*symbol).x1 + ((*symbol).x2 - (*symbol).x1)*0.5 - width*0.5, (*symbol).y1 + ((*symbol).y2 - (*symbol).y1)*0.5 - height*0.55, "TABLE OF SYMBOLS", MLV_COLOR_ROYALBLUE3);

    (*quit).x1 = largeur*0.15;
    (*quit).y1 = hauteur*0.75;
    (*quit).x2 = (*quit).x1 + largeur*0.7;
    (*quit).y2 = (*quit).y1 + hauteur*0.2;

    MLV_draw_rectangle((*quit).x1, (*quit).y1, (*quit).x2 - (*quit).x1, (*quit).y2 - (*quit).y1, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle((*quit).x1 + 1, (*quit).y1 + 1, (*quit).x2 - (*quit).x1 - 2, (*quit).y2 - (*quit).y1 - 2, MLV_COLOR_PALETURQUOISE);
    MLV_get_size_of_text("QUIT", &width, &height);
    MLV_draw_text((*quit).x1 + ((*quit).x2 - (*quit).x1)*0.5 - width*0.5, (*quit).y1 + ((*quit).y2 - (*quit).y1)*0.5 - height*0.55, "QUIT", MLV_COLOR_ROYALBLUE3);
    MLV_actualise_window();
    return;
}


/**
 * \fn int recup_clic_menu(Zone *load, Zone *tree, Zone *symbol, Zone *quit)
 * \brief Recupère les coordonnées du clique dans le menu.
 * 
 * \param load La zone du cadran "load".
 * \param tree La zone du cadran "tree".
 * \param symbol La zone du cadran "symbol".
 * \param quit La zone du cadran "quit".
 * \return Retourne un entier selon les coordonnées du clique.
 */
int recup_clic_menu(Zone *load, Zone *tree, Zone *symbol, Zone *quit){
    PROFILE
    int x = 0, y=0;
    MLV_wait_mouse(&x,&y);
    while (x <(*load).x1 || x >(*load).x2 || y <(*load).y1 ||  y >(*quit).y2){
        MLV_wait_mouse(&x,&y);
    }
    if(y <(*load).y2){
        return 1;
    }
    if(y <(*tree).y2){
        return 2;
    }
    if(y <(*symbol).y2){
        return 3;
    }
    if(y <(*quit).y2){
        return 0;
    }
    return 0;

}

/**
 * \fn char* file_to_load(Zone *load)
 * \brief Affiche, recupère et renvoie le fichier à charger.
 *
 * \param load La zone du cadran "load".
 * \return Retourne le nom du fichier à charger.
 */
char* file_to_load(Zone *load){
    PROFILE
    char* file_log;
    MLV_wait_input_box(load->x1,load->y1,load->x2-load->x1,load->y2-load->y1,
                MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
                "Entrez le '.log': ",
                &file_log
        );
    
    return file_log;
}

/**
 * \fn void draw_load(Zone *load)
 * \brief Affiche graphiquement le cadran load.
 *
 * \param load La Zone de load. 
 */
void draw_load(Zone *load){
    PROFILE
    
    MLV_draw_text_box   (load->x1,load->y1,load->x2-load->x1,load->y2-load->y1, "LOADING TREE",5,
        MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
        MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER );
    MLV_actualise_window();
    return ;
}

/**
 * \fn void draw_load_symbol(Zone * symbol)
 * \brief Affiche graphiquement le symbol.
 *
 * \param symbol La Zone de symbol. 
 */
void draw_load_symbol(Zone * symbol){
    PROFILE
    
    MLV_draw_text_box   (symbol->x1,symbol->y1,symbol->x2-symbol->x1,symbol->y2-symbol->y1, "LOADING SYMBOL TABLE ",5,
        MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_ROYALBLUE3,
        MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER );
    MLV_actualise_window();
    return;
}

