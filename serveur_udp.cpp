#include <iostream> 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


#include <string.h>
/*port local du serveur*/
#define PORT 9600

using  namespace std; 


int main (int argc , char *argv[]){
    /*déclaration de variable */

    
    int sockfd ;                    /* le descripteur de socket*/
    sockaddr_in serverAddr ;        /*struct d'addresse locale du serveur*/
    sockaddr_in clientAddr ;        /*struct d'addresse du client*/
    socklen_t clientAddrL;                /*taille de l'addresse du client */
    char buffer[20];    

    sockfd = socket(PF_INET, SOCK_DGRAM,0);

    if (sockfd < 0) {
        cout << "Erreur lors de la création de la socket" << endl;
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    

    int bindR = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bindR < 0) {
        cerr << "Erreur lors du bind de la socket" << endl;
        close(sockfd);
        return 1;
    }
    
    cout << "attente du serveur sur le port " << PORT << "..." << endl;
    while (1){
        memset(buffer, 0, sizeof(buffer));
        clientAddrL = sizeof(clientAddr);
        

        // Réception des données
        ssize_t recvLen = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                           (struct sockaddr*)&clientAddr, &clientAddrL);

        if (recvLen < 0) {
            cerr << "Erreur lors de la réception des données" << endl;
            continue;
        }

        cout << "Reçu de " << inet_ntoa(clientAddr.sin_addr)
             << ":" << ntohs(clientAddr.sin_port) << " -> " << buffer << endl;
        

        ssize_t dataSent = write(STDOUT_FILENO, buffer, recvLen); 
        if (dataSent<0){
             cerr << "Erreur : Impossible d'écrire les données" << endl;
        }

        


    }
    close(sockfd);
    return 0; 

}