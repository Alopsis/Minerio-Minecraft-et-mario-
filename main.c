#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "types.h"
#include "main.h"
#include "socket.h"

map map_vide()
{
    return NULL;
}
map nouvel_etage(map etage_gauche)
{
    map et = malloc(sizeof(etage));
    if (!et)
    {
        perror("Failed to allocate memory for etage");
        exit(EXIT_FAILURE);
    }
    et->tab = malloc(sizeof(int) * 10);
    if (!et->tab)
    {
        perror("Failed to allocate memory for et->tab");
        free(et);
        exit(EXIT_FAILURE);
    };
    et->droit = map_vide();
    elem++;
    et->gauche = etage_gauche;
    et->tab[0] = 0;
    et->tab[1] = 0;
    et->tab[2] = 0;
    if (elem % 2 == 1)
    {
        et->tab[3] = 0;
    }
    else
    {
        et->tab[3] = 1;
    }
    et->tab[4] = 1;
    et->tab[5] = 1;
    et->tab[6] = 2;
    et->tab[7] = 2;
    et->tab[8] = 2;
    et->tab[9] = 3;
    return et;
}

void init_tableau()
{
    int i;
    map premier = malloc(sizeof(etage)); // Allocate memory for premier

    if (!premier)
    {
        perror("Failed to allocate memory for premier");
        exit(EXIT_FAILURE);
    }

    premier->tab = malloc(sizeof(int) * 10); // Allocate memory for the tab inside premier

    if (!premier->tab)
    {
        perror("Failed to allocate memory for premier->tab");
        free(premier);
        exit(EXIT_FAILURE);
    }

    premier->droit = map_vide();
    premier->gauche = map_vide();
    premier->tab[0] = 0;
    premier->tab[1] = 0;
    premier->tab[2] = 0;
    if (elem % 2 == 1)
    {
        premier->tab[3] = 0;
    }
    else
    {
        premier->tab[3] = 1;
    }
    premier->tab[4] = 1;
    premier->tab[5] = 1;
    premier->tab[6] = 2;
    premier->tab[7] = 2;
    premier->tab[8] = 2;
    premier->tab[9] = 3;
    actuel = premier;

    for (i = 0; i < 50; i++)
    {
        premier->droit = nouvel_etage(premier);
        premier = premier->droit;
    }

    premier->droit = actuel;
    actuel->gauche = premier;
}

void init_carte()
{

    actuel = malloc(sizeof(etage));
    if (!actuel)
    {
        perror("Failed to allocate memory for premier");
        exit(EXIT_FAILURE);
    }
    actuel->tab = malloc(sizeof(int) * 10);
    if (!actuel->tab)
    {
        perror("Failed to allocate memory for premier->tab");
        free(actuel);
        exit(EXIT_FAILURE);
    }

    MLV_create_window("Mario", "Mario", 500, 500);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_change_frame_rate(14);
    terre = MLV_load_image("./images/minecraft_dirt_sans_herbe.png");
    terre_herbe = MLV_load_image("./images/minecraft_dirt.png");
    stone = MLV_load_image("./images/stone.png");
    mario = MLV_load_image("./images/mario.png");
    mario_jump = MLV_load_image("./images/mario_jump.png");
    bedrock = MLV_load_image("./images/bedrock.png");
    MLV_resize_image_with_proportions(terre, 50, 50);
    MLV_resize_image_with_proportions(bedrock, 50, 50);
    MLV_resize_image_with_proportions(terre_herbe, 50, 50);
    MLV_resize_image_with_proportions(stone, 50, 50);
    MLV_resize_image_with_proportions(mario, 50, 50);
    MLV_resize_image_with_proportions(mario_jump, 50, 50);
}
void afficher_carte()
{
    int i;
    int j;

    map current = malloc(sizeof(etage));
    if (!current)
    {
        perror("Failed to allocate memory for premier");
        exit(EXIT_FAILURE);
    }
    current->tab = malloc(sizeof(int) * 10);
    if (!current->tab)
    {
        perror("Failed to allocate memory for premier->tab");
        free(current);
        exit(EXIT_FAILURE);
    }

    if (menu == 1)
    {
        if (MLV_get_frame_rate() != 15)
        {
            MLV_change_window_size(500, 600);

            MLV_change_frame_rate(15);
        }
        MLV_draw_image(bedrock, 50, 500);
        MLV_draw_image(terre, 100, 500);
        MLV_draw_image(stone, 150, 500);
        MLV_draw_rectangle(200 - 50*selection,500,51,51,MLV_COLOR_GREEN);
    }
    else
    {
        if (MLV_get_frame_rate() != 14)
        {
            MLV_change_window_size(500, 500);
            MLV_change_frame_rate(14);
        }
    }

    current = actuel;

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (current->gauche->tab[j] == 1)
            {
                if (current->gauche->tab[j - 1] == 1)
                {
                    MLV_draw_image(terre, i * 50, j * 50);
                }
                else
                {
                    MLV_draw_image(terre_herbe, i * 50, j * 50);
                }
            }
            else if (current->gauche->tab[j] == 2)
            {
                MLV_draw_image(stone, i * 50, j * 50);
            }
            else if (current->gauche->tab[j] == 3)
            {

                MLV_draw_image(bedrock, i * 50, j * 50);
            }
            else
            {
                MLV_draw_filled_rectangle(i * 50, j * 50, 50, 50, MLV_COLOR_BLUE);
            }
        }
        current = current->droit;
    }

    MLV_draw_filled_rectangle(1 * 50, hauteur * 50, 50, 50, MLV_COLOR_GREEN);
    MLV_draw_image(mario, 1 * 50, hauteur * 50);
}
void afficher_actuel()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%d ", actuel->tab[i]);
    }
    printf("\n");
}

void actualise_deplacement()
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
    {
        hauteur--;
    }
    afficher_carte();
    MLV_actualise_window();
    MLV_wait_milliseconds(50);
    if (MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED)
    {
        if (actuel->gauche->tab[hauteur] == 0)
        {
            actuel = actuel->gauche;
        }
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED)
    {
        actuel->droit->tab[hauteur] = selection;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED)
    {
        menu = 1;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_t) == MLV_PRESSED)
    {
        menu = 0;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_a) == MLV_PRESSED)
    {
        actuel->gauche->tab[hauteur] = selection;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_w) == MLV_PRESSED)
    {
        actuel->gauche->tab[hauteur] = 0;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_c) == MLV_PRESSED)
    {
        actuel->droit->tab[hauteur] = 0;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED)
    {
        if (actuel->droit->tab[hauteur] == 0)
        {
            actuel = actuel->droit;
        }
    }

        if (MLV_get_keyboard_state(MLV_KEYBOARD_i) == MLV_PRESSED)
        {
            selection = 1;
        }
        if (MLV_get_keyboard_state(MLV_KEYBOARD_o) == MLV_PRESSED)
        {
            selection = 2;
        }
        if (MLV_get_keyboard_state(MLV_KEYBOARD_p) == MLV_PRESSED)
        {
            selection = 3;
        }
    afficher_carte();
    MLV_actualise_window();
    MLV_wait_milliseconds(100);
}

void actualise_deplacement_friends(char message[500])
{
    printf("on traite");
    printf("\"%s\"", message);
    if (strstr(message, "z"))
    {
        hauteur--;
    }
    afficher_carte();
    MLV_actualise_window();
    MLV_wait_milliseconds(50);
    if (strstr(message, "q"))
    {
        if (actuel->gauche->tab[hauteur] == 0)
        {
            printf("On va a gauche\n");
            actuel = actuel->gauche;
        }
    }
    if (strstr(message, "d"))
    {
        if (actuel->droit->tab[hauteur] == 0)
        {
            printf("On va a droite\n");
            actuel = actuel->droit;
        }
    }
    afficher_carte();
    MLV_actualise_window();
    MLV_wait_milliseconds(100);
}
int main()
{
    char deplacement_ext[500];
    // int server_socket = open_socket();
    char *message;
    srand(time(NULL));
    init_carte();
    init_tableau();
    MLV_actualise_window();
    actuel = actuel->gauche;
    while (1)
    {
        printf("selection = %d\n",selection);
        actualise_deplacement();
        // message = wait_for_response(server_socket);
        // actualise_deplacement_friends(message);
        while (actuel->tab[hauteur + 1] == 0)
        {
            hauteur++;
        }
        afficher_carte();
        MLV_actualise_window();
        afficher_actuel();
        MLV_wait_milliseconds(50);
        MLV_clear_window(MLV_COLOR_BLACK);
        // free(message);
    }
}
