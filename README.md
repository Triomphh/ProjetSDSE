# Auteurs
- Kévin Driencourt
- Florent Conderine

# Avant de commencer
Il est recommandé de lire ce `README.md` sur le [GitHub du projet](https://github.com/Triomphh/ProjetSDSE) (si ce n'est pas déjà le cas). </br >
<sub>https://github.com/Triomphh/ProjetSDSE/</sub>




# Architecture
## Partie client
<sup>(Même architecture que celle du sujet)</sup>  
### `client_chat.c`
- `client_chat.c` communique avec `communication.c` via un socket TCP
- `client_chat.c` communique avec `afficheur_message.c` via un pipe (nommé ou anonyme, voir [partie pipe](#pipe-client_chatc--afficheur_messagec))

### `afficheur_message.c`

### Pipe `client_chat.c` |> `afficheur_message.c`
Deux structures possibles : 
  - **Par défaut**: utilise un pipe nommé
  - **Alternative**: utilise un pipe anonyme, mais fonctionne uniquement avec xTerm
     - Utiliser le script `INSTALL.txt` : permet de compiler localement toutes les dépendances de xTerm <sub>(il a été conçu spécialement pour être lancé dans un environnement non super-utilisateur, comme à la fac...)</sub>  
     <sub>**ou**</sub>
     - Installer directement xTerm à l'aide de votre gestionnaire de packages


## Partie centralisée


## Partie Java



## Global
signal arret ............................................................




# Compilation
### Serveur
```
clear; gcc -o serveur main.c communication.c gestion_requete.c ../fonctions/creerSocketTCP.c; ./serveur 4009
```
### Client
```
clear; gcc -o afficheur_message afficheur_message.c; gcc -o client client_chat.c ../fonctions/creerSocketTCP.c -lpthread; ./client localhost 4009
```
