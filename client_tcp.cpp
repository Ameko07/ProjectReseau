#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9600
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Création de la socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erreur lors de la création de la socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Adresse invalide ou non supportée" << std::endl;
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Connexion au serveur
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Erreur lors de la connexion" << std::endl;
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connecté au serveur TCP.\n" << std::endl;

    while (true) {
        std::cout << "Entrez un message : ";
        std::cin.getline(buffer, BUFFER_SIZE);  // Utilisation de std::cin pour la saisie

        // Envoi du message
        if (write(sockfd, buffer, std::strlen(buffer)) < 0) {
            std::cerr << "Erreur lors de l'envoi du message" << std::endl;
            break;
        }

        // Lecture de la réponse
        ssize_t len = read(sockfd, buffer, BUFFER_SIZE);
        if (len < 0) {
            std::cerr << "Erreur lors de la lecture de la réponse" << std::endl;
            break;
        }
        buffer[len] = '\0';  // Null-terminate the buffer
        std::cout << "Réponse du serveur : " << buffer << std::endl;
    }

    close(sockfd);
    return 0;
}