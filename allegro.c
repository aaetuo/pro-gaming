#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>

#define LARGEUR 1024
#define HAUTEUR 768
#define MAX_IMAGES_CAT 6
#define INITIAL_SPEED 7
#define NB_BACKGROUNDS 2

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} player;

typedef struct {
    int x;
    int y;
} background;


int main()
{
    BITMAP *page;   // BITMAP buffer d'affichage

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,LARGEUR,HAUTEUR,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Charger un sprite
    BITMAP *sprites[MAX_IMAGES_CAT];
    int compteur_animation = 0;
    char filename[100];

    /// TODO: Charger les images dans le tableau sprites

    char path[100] = "../images/cat/cat%d.bmp";
    for(int i = 0; i < 6; ++i){
        char imagepath[100];
        sprintf(imagepath, path, i);
        sprites[i] = load_bitmap(imagepath,NULL);
    }


    // Charger un fond
    BITMAP *fond = load_bitmap("../images/cat/decor.bmp", NULL);
    if (!fond) {
        allegro_message("prb chargement image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    /// TODO: Créer un joueur et un tableau de background
    player joueur;
    joueur.x = 0;
    joueur.y = SCREEN_H / 2 - sprites[0]->h;
    joueur.dx = 5;
    joueur.dy = 0;

    background bg[2];
    bg[0].x = 0;
    bg[0].y = 0;
    bg[1].x = SCREEN_W;
    bg[1].y = 0;


    // Boucle de jeu
    while (!key[KEY_ESC])
    {
        // EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        clear_bitmap(page);

        /// TODO: Afficher le background et le joueur
        for (int i=0; i<2;i++){
            stretch_blit(fond, page, 0, 0, fond->w, fond->h, bg[i].x, bg[i].y, SCREEN_W, SCREEN_H);
        }

        draw_sprite(page, sprites[compteur_animation], joueur.x, joueur.y);


/// TODO: Gérer les sauts avec la barre d'espace
        if(key[KEY_SPACE]){
            if (joueur.y >= SCREEN_H / 2 - sprites[0]->h){
                joueur.dy = -16;
            }
        }
        joueur.y += joueur.dy;
        if(joueur.y >= SCREEN_H / 2 -sprites[0]->h){
            joueur.dy = 0;
            /// TODO: Animation (passer à l'image suivante)
            compteur_animation++;
            if(compteur_animation >= MAX_IMAGES_CAT) {
                compteur_animation = 0;
            }
        }
        else {
            joueur.dy++;
        }
        // Print cat position on the screen
        //textprintf_ex(page, font, 10, 10, makecol(255, 255, 255), -1, "cat.y = %d", cat.y);


        /// TODO: Faire défiler les backgrounds
        for (int i =0; i<2; i++){
            if(bg[i].x < -1 * SCREEN_W) {
                int other_bg_x = 0;
                if (i==0){
                    other_bg_x = bg[1].x;
                } else {other_bg_x = bg[0].x;}
                bg[i].x = other_bg_x + SCREEN_W;
                bg[i].y = 0;

                bg[i].x= other_bg_x + SCREEN_W;
                bg[i].y = 0;

            }
            bg[i].x -= joueur.dx;
        }

        // Montrer la souris à l'écran
        show_mouse(page);

        // Afficher le buffer à l'écran
        blit(page,screen,0,0,0,0,LARGEUR,HAUTEUR);
        rest(40);
    }

    return 0;
} END_OF_MAIN();
