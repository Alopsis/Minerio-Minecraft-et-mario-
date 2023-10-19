#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "types.h"
#include "socket.h"

int acc = 0;
char *serialize_map(map act)
{
    char *buffer = malloc(11); // Pour 10 entiers et un caractère de terminaison nul
    for (int i = 0; i < 10; i++)
    {
        buffer[i] = '0' + act->tab[i]; // Convertir l'entier en caractère
    }
    buffer[10] = '\0'; // Caractère de terminaison
    return buffer;
}

void recup_friends_deplacement(char *deplacement_ext)
{
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[MAX_BUFFER] = {0};
    int addr_len = sizeof(address);


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    acc ++;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connection...\n");
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len)) < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    read(client_fd, buffer, MAX_BUFFER);
    printf("Received message: %s\n", buffer);

    // Traiter les données si nécessaire. Par exemple, stockez le message dans deplacement_ext:
    strncpy(deplacement_ext, buffer, MAX_BUFFER);

    // Envoyer une réponse au client
    char *response = "Message received!";
    send(client_fd, response, strlen(response), 0);

    // Fermer le socket client
    //close(client_fd);

    return 0;
}



int open_socket() {
    int server_fd;
    struct sockaddr_in address;
    
    // Créer le socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    // Configurer l'adresse et le port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Lier le socket à l'adresse
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Commencer à écouter
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    return server_fd;
}


char* wait_for_response(int server_fd) {
    struct sockaddr_in address;
    int client_fd;
    char buffer[MAX_BUFFER] = {0};
    int addr_len = sizeof(address);

    printf("Waiting for connection...\n");

    // Accepter la connexion client
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Lire le message du client
    read(client_fd, buffer, MAX_BUFFER);
    printf("Received message: %s\n", buffer);

    // Fermer la connexion client après avoir terminé
    close(client_fd);

    // Retourner le message reçu
    return strdup(buffer);  // Pensez à libérer la mémoire après utilisation
}
