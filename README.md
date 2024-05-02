# Auteurs
- Kévin Driencourt
- Florent Conderine

# Avant de commencer
Il est recommandé de lire ce `README.md` sur le [GitHub du projet](https://github.com/Triomphh/ProjetSDSE) (si ce n'est pas déjà le cas). </br >
<sub>https://github.com/Triomphh/ProjetSDSE/</sub>
<br >
<br >
La majeure partie du code est commentée de façon très explicite pour faciliter la compréhension.
<br >
<br >



# Compilation
### Serveur
```
clear; gcc -o serveur main.c communication.c gestion_requete.c ../fonctions/creerSocketTCP.c; ./serveur 4009
```
### Client
```
clear; gcc -o afficheur_message afficheur_message.c; gcc -o client client_chat.c ../fonctions/creerSocketTCP.c -lpthread; ./client localhost 4009
```
<br >
<br >


# Architecture
## Partie client
<sup>(Même architecture que celle du sujet)</sup>  
### `client_chat.c`
- `client_chat.c` communique avec `communication.c` via un socket TCP
- `client_chat.c` communique avec `afficheur_message.c` via un pipe (nommé ou anonyme, voir la [section sur les pipes](#pipe-client_chatc--afficheur_messagec))
<br >

`client_chat.c` lance d'abord un **thread** qui s'occupe de reçevoir les messages du serveur <sub>(`communication.c`)</sub>  
puis dans le processus principal il s'occupe d'envoyer chaque chaîne de caractères qu'il reçoit dans son **_stdin_** <sub>(après avoir appuyé sur **[ENTRÉE]**)</sub> au serveur <sub>(`communication.c`)</sub>
<br >
<br >


### `afficheur_message.c`
Simple boucle qui lit le côté lecture de son pipe (nommé ou anonyme, voir la [section sur les pipes](#pipe-client_chatc--afficheur_messagec)) et affiche le contenu.
<br >
<br >


### Pipe `client_chat.c` |> `afficheur_message.c`
Deux structures possibles : 
  - **Par défaut**: utilise un pipe nommé
  - **Alternative**: utilise un pipe anonyme, mais fonctionne uniquement avec xTerm
     - Utiliser le script `INSTALL.txt` : permet de compiler localement toutes les dépendances de xTerm <sub>(il a été conçu spécialement pour être lancé dans un environnement non super-utilisateur, comme à la fac...)</sub>  
     <sub>**ou**</sub>
     - Installer directement xTerm à l'aide de votre gestionnaire de packages
<br >
<br >





## Partie centralisée
<sup>(Même architecture que celle du sujet)</sup>  

### `main.c`
S'occupe de lancer les différents processus (**Communication** et **Gestion Requête**) et de les fermer correctement via un gestionnaire de signal (voir [partie Gestionnaire de signaux](#gestionnaire-de-signaux))
<br >
<br >



### `communication.c`
- `communication.c` communique avec `client_chat.c` via un socket TCP
- `communication.c` communique avec `gestion_requete.c` via un pipe nommé <sub>(`request_pipe`)</sub>  
<br >

`communication.c` créé un esocket TCP d'écoute et attends la connexion de clients sur celle-ci.  
Si un client se connecte sur cette socket, on ouvre une socket de service pour le client et on lui créé un processus propre à lui qui va _`traiter()`_ la communication avec lui.  
<br >  

_`traiter()`_ permet de lire les chaînes de caractères envoyées par le client et de les différencier selon leur contenu : 
- si elle commence par un '**/**', c'est une commande qui sera envoyé à `gestion_requete.c` via le pipe,
- sinon, c'est un message qui est destiné à être envoyé aux autres utilisateurs
 
_`traiter()`_ permet aussi de faire la différence entre un utilisateur connecté ou non, si celui-ci n'est pas connecté, il ne peut pas envoyer de message mais uniquement des commandes <sub>_(pour se connecter, créer un compte, etc...)_</sub>
<br >
<br >



### `communication.c`
- `gestion_requete.c` communique avec `communication.c` via un pipe nommé <sub>(`response_pipe`)</sub>
<br >

`gestion_requete.c` permet d'effectuer diverses actions en fonction de la commande reçue
```c
// === Gestion des commandes "/..." ===
//      Connexion                           : /c  ,       , /connect   { nom, mdp }
//      Déconnexion                         : /e  ,       , /exit 
//      Afficher la liste des utilisateurs  : /l  , /list , /liste
//      Créer un compte                     : /cr ,       , /create     { nom, mdp }
//      Supprimer un compte                 : /d  , /del  , /delete     { nom, mdp }
// ====================================
```
<br >
<br >





## Partie Java

<br >
<br >



## Global
### Gestionnaire de signaux
Un gestionnaire de signal (SIGINT) a été créé pour arrêter proprement les différents processus, en sortant des boucles _"infinies"_ (ce qui permet déjà de fermer proprement les pipes et les sockets) mais aussi de supprimer les fichiers créés par les pipes nommés.  
<br >
<br >



## Optionnel
### `INSTALL.txt` (non conseillé)
Ce script a été conçu spécialement pour utiliser un pipe anonyme entre `client_chat.c` et `afficheur_message.c` grâce à xTerm, car pour des raisons de magie noire, gnome-terminal ne marche pas avec un pipe anonyme.  
Il permet de compiler localement toutes les dépendances de xTerm sans utiliser de gestionnaire de packages. Ce qui est nécessaire si l'utilisateur n'a pas accès au gestionnaire de packages ou aux droits super-utilisateur (comme à l'unniversité)
<br >
<br >
Si vous souhaitez utiliser le script il suffit de se placer dans `ProjetSDSE/` et copier le script dans le terminal **(`ProjetSDSE/` doit absolument se trouver dans `$HOME/Documents/`)**  
Nécessite uniquement **gcc** d'installé.
<br >
<br >
L'installation dure **~15 minutes**  
Toutes les dépendances seront installées dans le dossier `ProjetSDSE/dependencies/` et peuvent être retirées en supprimant ce dossier.
<br >
<br >
Aucun dossier/fichier externe à `ProjetSDSE/` n'est modifié.




