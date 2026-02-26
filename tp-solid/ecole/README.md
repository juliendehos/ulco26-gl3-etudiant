
# ecole

## Description

Gère les personnes d'une école, via les classes et un annuaire général.

## Planning

- [ ] single responsibility: séparer Classes en Classes + Annuaire, ajouter un attribut `Ecole::_annuaire`
- [ ] dependency inversion: IGestion* -> IGestion, Annuaire, Classes
- [ ] interface segregation: IGestion -> Affichable + Recherchable
- [ ] open/close: Personne + Etudiant
- [ ] Liskov substitution: Annuaire

