#include <iostream> 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


#include <string.h>
#define SIZE 100
#define PORT 9600

using namespace std;

int main (int argc , char *argv[]){
    

    int sockfd ;                    /* le descripteur de socket*/
    sockaddr_in serverAddr ;        /*struct d'addresse locale du serveur*/
    struct hostent *host;           /*pointer vers la structure descriptive de machine*/
    char buffer[SIZE];       /*zone de mémoire*/
    ssize_t messageLenght ;             /*taille du message */
        
    sockfd = socket(AF_INET, SOCK_DGRAM,0);

    if (sockfd < 0) {
        cout << "Erreur lors de la création de la socket" << endl;
        return 1;
    }

    memset(&serverAddr, 0 , sizeof(serverAddr)); 

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT); 

    const char *nomServeur =  "127.0.0.1"; // test de l'adresse 

    host = gethostbyname(nomServeur); 

    if (host == NULL) {
        cerr << "Erreur : Machine Hôte introuvable" << endl;
        close(sockfd);
        return 1;
    } 

    memcpy(&serverAddr.sin_addr.s_addr, host->h_addr, host->h_length);

    cout << "Entrez votre message: ";
    memset(buffer, 0, SIZE);
    messageLenght = read(STDIN_FILENO, buffer, SIZE-1);

    if (messageLenght < 0){
        cerr << "Erreur : impossible de lire l'entrée utilisateur " << endl; 
        close(sockfd); 
        return 1; 

    }

    buffer [messageLenght] = '\0';

    
    

    

    socklen_t serverAddrLen = sizeof(serverAddr); 
    if (sendto(sockfd, buffer, messageLenght, 0, (struct sockaddr *)&serverAddr, serverAddrLen) < 0) {
        
        cerr << "Erreur lors de l'envoi du message" << endl;
        close(sockfd);
        return 1;
    }

    cout << "Message envoyé au serveur : " << buffer << endl;

    memset(buffer, 0, SIZE);
    if (recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr *)&serverAddr, &serverAddrLen) < 0) {

        cerr << "Erreur lors de la réception de la réponse" << endl;

    } else {
        cout << "Réponse du serveur : " << buffer << endl;
    }



    close(sockfd);
    return 0;

}