

typedef struct etage
{
    struct etage *gauche;
    int *tab;
    struct etage *droit;
} etage;

typedef etage *map;
#define PORT 8080
#define MAX_BUFFER 1024