#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9600
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Création de la socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Erreur lors de la création de la socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Liaison de la socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Erreur lors de la liaison" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Mise en écoute
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Erreur lors de l'écoute" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Serveur TCP en attente de connexions sur le port " << PORT << "..." << std::endl;

    // Acceptation des connexions entrantes
    while ((new_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len)) >= 0) {
        std::cout << "Nouvelle connexion acceptée." << std::endl;

        ssize_t len = read(new_socket, buffer, BUFFER_SIZE);
        if (len < 0) {
            std::cerr << "Erreur lors de la lecture du message" << std::endl;
            close(new_socket);
            continue;
        }
        buffer[len] = '\0';  // Null-terminate the buffer
        std::cout << "Message reçu : " << buffer << std::endl;

        // Envoi de réponse
        const char* response = "Message reçu";
        if (write(new_socket, response, std::strlen(response)) < 0) {
            std::cerr << "Erreur lors de l'envoi de la réponse" << std::endl;
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}