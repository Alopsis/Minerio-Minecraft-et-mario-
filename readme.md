# Jeu bac à sable en 2d

## Utilisation
Pour compiler le programme :
> make
Pour lancer le programme : 
> ./main
# Differentes touches 
> ESPACE Pour sauter
> d Pour aller a droite
> q Pour aller a gauche
> R Pour ouvrir l'inventaire
> i o p Pour choisir le bloc 
> w Pour détruire le bloc a sa gauche
> d Pour détruire le bloc a sa droite

## Pour mettre le jeu en réseau 

Decommenter ces deux lignes : 
> message = wait_for_response(server_socket);
> actualise_deplacement_friends(message);

Lancer le programme sur l'appareil manette
> make 
> ./main