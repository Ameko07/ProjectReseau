# ProjectReseau
TP de Reseau 
- Langage : C++
- Contributeur : RAMANANKIEFERANA Lafatra Julio et Denis Julien du groupe 1

# Communication Client-Serveur en TCP et UDP

Ce projet illustre deux approches de communication réseau entre un client et un serveur :
- **Communication orientée datagramme (UDP)** : sans connexion, utilisant un seul socket pour la communication.
- **Communication orientée flux (TCP)** : avec connexion, utilisant des sockets dédiés pour chaque client.

## 📜 Fonctionnalités

### Serveur UDP
- Utilise un seul socket pour écouter, recevoir et répondre aux messages des clients.
- Ne nécessite pas de connexion explicite entre le serveur et les clients.

### Client UDP
- Envoie des messages au serveur UDP sans établir de connexion.
- Affiche les réponses reçues du serveur.

### Serveur TCP
- Crée un socket principal pour écouter les connexions.
- Accepte les connexions entrantes et crée des sockets dédiés pour chaque client.
- Gère plusieurs clients en parallèle via des processus fils (`fork()`).

### Client TCP
- Se connecte explicitement au serveur TCP via un socket.
- Envoie des messages au serveur et lit les réponses.

---

## 📂 Structure du projet

- `serveur_udp.cpp` : Serveur pour la communication UDP.
- `client_udp.cpp` : Client pour la communication UDP.
- `serveur_tcp.cpp` : Serveur pour la communication TCP.
- `client_tcp.cpp` : Client pour la communication TCP.
- `README.md` : Documentation du projet.

---

## 🚀 Instructions pour l'utilisation

### 1. Compilation

Assurez-vous que vous avez un compilateur compatible avec C++ (par exemple, `g++`).

- **Compiler les fichiers UDP** :
  ```bash
  g++ -o serveur_udp serveur_udp.cpp
  g++ -o client_udp client_udp.cpp
