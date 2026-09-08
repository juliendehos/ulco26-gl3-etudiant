
# connect4

## Description

Une implémentation du jeu [Puissance 4](https://fr.wikipedia.org/wiki/Puissance_4).

Interface console + interface graphique.

Joueurs humains ou IA (random, Monte Carlo).


## Fonctionnalités

- jeu de Puissance 4 :
  - [x] représenter le plateau et l'état du jeu courant
  - [x] pouvoir lire le plateau et l'état du jeu (pour les UI)
  - [x] jouer un coup, en respectant les règles
  - [x] récupérer les coups possibles (pour les IA)

- player :
  - [ ] humain (le prochain coup à jouer est donné par un utilisateur)
  - [ ] random (choisit un coup aléatoirement)
  - [ ] monte carlo avec 10 simulations par coup possible
  - [ ] monte carlo avec 100 simulations par coup possible

- UI console :
  - [ ] afficher le jeu et saisir les coups, au format texte
  - [ ] gérer différents types de player (humain, random, mc10, mc100)
  - [ ] dérouler une partie de jeu complète
  - [ ] arguments de la ligne de commande

- UI gtkmm :
  - [x] bouton quitter
  - [ ] afficher le jeu
  - [x] saisir les coups
  - [ ] dérouler la partie de jeu
  - [ ] bouton nouveau jeu
  - [ ] listes pour choisir les players 1 et 2


## Planning

- [x] implémenter le jeu + tests unitaires

- [x] implémenter une UI gtkmm basique avec zone de dessin, bouton quitter,
  état du jeu...

- [ ] TODO


## Conception

### Modèle

Game =
  - _status
  - _firstStatus    // pour alterner le joueur qui commence
  - _board
  - _heights
  - _nMoves

  + newGame()
  + status()
  + isRunning()
  + cell(i, j)
  + playMove(j)
  + computeValidMoves()

TODO

### Vue/Contrôleur UiGtkmm

MyDrawingArea =
  - _window

MyWindow =
  - _game
  - _drawingArea
  - TODO

  + updateMove(move)    // maj les actions de jeu
  + updateGame()        // maj le dessin du jeu
  + gameIsRunning()     // accesseur pour MyDrawingArea
  + gameCell(i, j)      // accesseur pour MyDrawingArea

### Vue UiConsole

TODO


## Références

- [Programming with gtkmm 4](https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/index.html)
- [Gtk Namespace Reference](https://gnome.pages.gitlab.gnome.org/gtkmm/namespaceGtk.html)


