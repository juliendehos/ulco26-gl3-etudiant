#pragma once

#include <string>
#include <vector>

struct Personne {
  std::string prenom;
  std::string nom;
  int annee;
  std::string tel;
};

class Annuaire {
  private:
    std::vector<Personne> personnes;

  public:
    const std::vector<Personne> & getPersonnes() const;
    void ajouter(const Personne & p);
};

Annuaire mkAnnuaireTest();

