
#include "Annuaire.hpp"

const std::vector<Personne> & Annuaire::getPersonnes() const {
  return personnes;
}

void Annuaire::ajouter(const Personne & p) {
  personnes.push_back(p);
}

Annuaire mkAnnuaireTest() {
  Annuaire annuaire;
  annuaire.ajouter({"John", "Doe", 1942, "03 42 42 42 42"});
  annuaire.ajouter({"Foo", "Bar", 2009, "02 13 37 13 37"});
  return annuaire;
}

