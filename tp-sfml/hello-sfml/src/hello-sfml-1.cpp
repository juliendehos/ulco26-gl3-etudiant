
#include <SFML/Graphics.hpp>

#include <filesystem>

int main(int, char ** argv) {

  // dossier data 
  const std::string dataDir = 
    (std::filesystem::path(argv[0]).parent_path() / "../data/").string();

  // titre de l'application
  const std::string myTitle = "hello-sfml-1";

  // couleur de fond
  const sf::Color myBgColor(80, 80, 80, 255);

  // texte à afficher
  const sf::Font myFont(dataDir + "arial.ttf");
  sf::Text myText(myFont, myTitle, 50);
  myText.setPosition({250, 120});

  // image à afficher
  const sf::Texture myTexture(dataDir + "bob.png");
  sf::Sprite mySprite(myTexture);
  mySprite.setPosition({50, 100});

  // fenêtre principale
  sf::RenderWindow window(sf::VideoMode({600, 300}), myTitle, sf::Style::Close);
  window.setVerticalSyncEnabled(true);
  window.setPosition({50, 50});

  // TODO boucle principale

    // TODO fermeture de la fenêtre

    // TODO événements clavier

    // TODO événements souris

    // TODO affichage

  return 0;
}

