# Auteurs
- Kévin Driencourt
- Florent Conderine

# Avant de commencer
Il est recommandé de lire ce `README.md` sur le [GitHub du projet](https://github.com/Triomphh/ProjetSDSE) (si ce n'est pas déjà le cas). </br >
<sub>https://github.com/Triomphh/ProjetSDSE/</sub>


# Quelques infos avant de lire
...


# Compilation
### Serveur
```
clear; gcc -o serveur main.c communication.c gestion_requete.c ../fonctions/creerSocketTCP.c; ./serveur 4006
```
### Client
```
clear; gcc -o afficheur_message afficheur_message.c; gcc -o client client_chat.c ../fonctions/creerSocketTCP.c; ./client localhost 4006
```
