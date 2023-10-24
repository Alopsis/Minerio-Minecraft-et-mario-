


int elem = 0;
MLV_Image *terre_herbe;
MLV_Image *terre;
MLV_Image *stone;
MLV_Image *mario;
MLV_Image *mario_jump;
MLV_Image *bedrock;
int menu = 0;
int selection = 0;

map actuel;
int position = 1;
int hauteur = 1;
int tab[][10] = {{0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 1, 1, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 1, 1, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 1, 1, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 1, 1, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 1, 1, 1, 2, 2},
                 {0, 0, 0, 1, 1, 2, 2},
                 {0, 0, 0, 0, 1, 2, 2}};


map map_vide();
map nouvel_etage(map etage_gauche);
void init_tableau();
void init_carte();
void afficher_carte();
void afficher_actuel();
void actualise_deplacement();