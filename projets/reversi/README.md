
# Reversi

## Description

Une implémentation du jeu [Reversi](https://fr.wikipedia.org/wiki/Othello_(jeu)).

Interface graphique.

Joueurs humains.


## Fonctionnalités

- représenter et dérouler un jeu de reversi :

    - [ ] représenter le plateau de jeu et y accéder
    - [ ] représenter l'état du jeu
    - [ ] calculer les coups valides
    - [ ] jouer un coup valide
    - [ ] détecter la fin de partie et le résultat

- interface graphique : 

    - [ ] bouton quitter
    - [ ] bouton nouvelle partie
    - [ ] afficher le jeu (board + status)
    - [ ] jouer (click de souris)


## Planning

- [ ] TODO


## Conception

### Modèle

Status = Play1 | Play2 | Win1 | Win2 | Tie 

Cell = Player1 | Player2 | Empty

Pos = pair<int, int>

Moves = map<Pos, set<Pos>>

Board =
    - cells
    + cell(i, j)
    + cell_(i, j)
    + newBoard()

Game =
    TODO

### Vue/Contrôleur

DrawingArea =
    TODO

MyWindow =
    TODO


## Références

- [Programming with gtkmm 4](https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/index.html)
- [Gtk Namespace Reference](https://gnome.pages.gitlab.gnome.org/gtkmm/namespaceGtk.html)

