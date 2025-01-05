# ProjectReseau
TP de Reseau 
- Langage : C++
- Contributeur : RAMANANKIEFERANA Lafatra Julio et Denis Julien du groupe 1

# Communication Client-Serveur en TCP et UDP

Ce projet illustre deux approches de communication réseau entre un client et un serveur :
- **Communication orientée datagramme (UDP)** : sans connexion, utilisant un seul socket pour la communication.
- **Communication orientée flux (TCP)** : avec connexion, utilisant des sockets dédiés pour chaque client.

## 📜 Fonctionnalités

## 📜 Fonctionnalités

### UDP
- **Serveur UDP** :
  - Écoute sur un port prédéfini.
  - Reçoit des messages de n'importe quel client.
  - Répond directement au client ayant envoyé le message.

- **Client UDP** :
  - Envoie des messages au serveur sans établir de connexion.
  - Affiche les réponses reçues.

---
### TCP
- **Serveur TCP** :
  - Écoute sur un port prédéfini.
  - Accepte les connexions entrantes.
  - Lit les messages du client et y répond.
  - Traite chaque connexion indépendamment.

- **Client TCP** :
  - Se connecte au serveur via une adresse IP et un port.
  - Envoie des messages au serveur.
  - Lit les réponses du serveur.


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
