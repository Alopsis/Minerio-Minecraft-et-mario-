#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

int position = 2;
int hauteur = 1;
int tab[][5] = {{0,0,0,0,1},
                {0,0,0,1,1},
                {0,0,1,1,1},
                {0,0,0,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,1,1},
                {0,0,1,1,1},
                {0,0,0,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,1,1},
                {0,0,1,1,1},
                {0,0,0,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,1,1},
                {0,0,1,1,1},
                {0,0,0,1,1},
                {0,0,0,0,1},
                {0,0,0,0,1},
                {0,0,0,1,1},
                {0,0,1,1,1},
                {0,0,0,1,1},
                {0,0,0,0,1}
                };

void init_carte(){
    MLV_create_window("Mario" , "Mario" , 500,500);
    MLV_clear_window(MLV_COLOR_WHITE);
}
void afficher_carte(){
    int i;
    int j;
    MLV_Image * terre_herbe;
    MLV_Image * terre;
    terre= MLV_load_image( "./images/minecraft_dirt_sans_herbe.png" );
    terre_herbe = MLV_load_image( "./images/minecraft_dirt.png" );
    MLV_resize_image_with_proportions( terre, 50, 50);
    MLV_resize_image_with_proportions( terre_herbe, 50, 50);
    for(i=0; i <5; i++){
        for(j=0;j<5;j++){
            if(tab[position-1+i][j] == 1){
                MLV_draw_filled_rectangle(i*50+150,j*50+50,50,50,MLV_COLOR_RED);
                if(tab[position-1+i][j-1] == 1){
                    MLV_draw_image( terre, i*50+150, j*50+50 );
                }else{
                    MLV_draw_image( terre_herbe, i*50+150, j*50+50 );

                }

            }else{
                MLV_draw_filled_rectangle(i*50+150,j*50+50,50,50,MLV_COLOR_BLUE);

            }
        }
    }
    MLV_draw_filled_rectangle(1*50+150,hauteur*50+50,50,50,MLV_COLOR_GREEN);
    
}
int main(){
    init_carte();
    MLV_actualise_window();
    position--;
    while(1){
        if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED){
            hauteur--;
        }
        if (MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED){
            if(tab[position-1][hauteur] == 0){
                position--;

            }
        }
        if(MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED){
            if(tab[position+1][hauteur] == 0){
                position++;

            }
        }


        afficher_carte();
        MLV_actualise_window();
        MLV_wait_milliseconds(150);

        while(tab[position][hauteur+1] == 0){
            hauteur++;
        }
        afficher_carte();
        MLV_actualise_window();
    }

}