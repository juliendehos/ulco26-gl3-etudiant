
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Personne, Etudiant
///////////////////////////////////////////////////////////////////////////////

struct Personne {
  std::string _nom;
  std::string _prenom;

  Personne(const std::string & nom, const std::string & prenom):
    _nom(nom), _prenom(prenom)
  {}
};

struct Etudiant {
  std::string _nom;
  std::string _prenom;
  std::string _id;

  Etudiant(const std::string & nom, const std::string & prenom, const std::string & id):
    _nom(nom), _prenom(prenom), _id(id)
  {}

};

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class Classes {
  private:
    std::map<std::string, std::vector<Etudiant>> _groupes;
    std::vector<Personne> _personnes;

  public:

    const std::map<std::string, std::vector<Etudiant>> & getGroupes() const {
      return _groupes;
    }

    const std::vector<Personne> & getPersonnes() const {
      return _personnes;
    }

    void ajouterEtudiant(const std::string & groupe, const Etudiant & e) {
      _groupes[groupe].push_back(e);
    }

    void ajouterPersonne(const Personne & p) {
      _personnes.push_back(p);
    }

};

///////////////////////////////////////////////////////////////////////////////
// Ecole
///////////////////////////////////////////////////////////////////////////////

class Ecole {
  private:
    Classes _classes;

  public:

    const Classes & getClasses() const {
      return _classes;
    }

    void importer(std::istream & is) {
      std::string line;
      while (is) {
        std::getline(is, line);
        std::istringstream iss(line);
        std::string nom, prenom, id, classe;
        std::getline(iss, nom, ';');
        std::getline(iss, prenom, ';');
        std::getline(iss, id, ';');
        std::getline(iss, classe, ';');
        if (nom.empty() or prenom.empty())
          continue;

        if (id.empty()) {
          auto p = Personne(nom, prenom);
          _classes.ajouterPersonne(p);
        }
        else {
          auto p = Personne(nom, prenom);
          auto e = Etudiant(nom, prenom, id);
          _classes.ajouterEtudiant(classe, e);
          _classes.ajouterPersonne(p);
        }
      }
    }

};

///////////////////////////////////////////////////////////////////////////////
// Interfaces
///////////////////////////////////////////////////////////////////////////////

struct IGestion {
  virtual void afficher(std::ostream & os, const Ecole & ecole) const = 0;
  virtual std::vector<Personne> rechercher(const std::string & nom, const Ecole & ecole) const = 0;
};

struct GestionGroupes : public IGestion {
    void afficher(std::ostream & os, const Ecole & ecole) const override {
      for (const auto & [groupe, etudiants] : ecole.getClasses().getGroupes()) {
        os << groupe << ": " << std::endl;
        for (const auto & e : etudiants) {
          os << "- " << e._nom << ", " << e._prenom << ", " << e._id << std::endl;
        }
      }
    }

    std::vector<Personne> rechercher(const std::string & nom, const Ecole & ecole) const override {
      return {};
    }
};


struct GestionAnnuaire : public IGestion {
    void afficher(std::ostream & os, const Ecole & ecole) const override {
      for (const auto & p : ecole.getClasses().getPersonnes())
        os << "- " << p._nom << ", " << p._prenom << std::endl;
    }

    std::vector<Personne> rechercher(const std::string & nom, const Ecole & ecole) const override {
      std::vector<Personne> res;
      for (const auto & p : ecole.getClasses().getPersonnes()) {
        if (p._nom == nom)
          res.push_back(p);
      }
      return res;
    }
};

///////////////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////////////

void afficherRapport(std::ostream & os, const std::string & titre, const IGestion & gestion, const Ecole & ecole) {
  os << "*** " << titre << " ***" << std::endl;
  gestion.afficher(os, ecole);
  os << std::endl;
}

int main(int argc, char ** argv) {

  if (argc != 2) {
    std::cout << "usage: <filename>" << std::endl;
    exit(-1);
  }

  std::ifstream ifs(argv[1]);
  if (not ifs.is_open()) {
    std::cout << "cannot open: " << argv[1] << std::endl;
    exit(-1);
  }

  Ecole ecole;
  ecole.importer(ifs);

  GestionGroupes gestionGroupes;
  afficherRapport(std::cout, "classes", gestionGroupes, ecole);

  GestionAnnuaire gestionAnnuaire;
  afficherRapport(std::cout, "annuaire", gestionAnnuaire, ecole);

  std::cout << "recherche 'einstein':" << std::endl;
  auto res = gestionAnnuaire.rechercher("einstein", ecole);
  for (const auto & [nom, prenom] : res)
    std::cout << "- " << nom << ", " << prenom << std::endl;

  return 0;
}

