
#include "GuiGtkmm.hpp"
#include "GuiSfml.hpp"
#include "Params.hpp"

#include <iostream>
#include <filesystem>

void usage() {
  std::cerr << "usage: <sfml|gtkmm>" << std::endl;
  exit(-1);
}

int main(int argc, char ** argv) {

  if (argc != 2)
    usage();
  const std::string guiName = argv[1];

  // assets
  const std::string dataDir = 
    (std::filesystem::path(argv[0]).parent_path() / "../data/").string();

  // game
  Game game(gNbWidth, gNbHeight, gTimeStep);

  // view
  if (guiName == "sfml") {
    GuiSfml gui(game, dataDir);
    gui.run();
  }
  else if (guiName == "gtkmm") {
    GuiGtkmm gui(game, dataDir);
    gui.run();
  }
  else
    usage();

  return 0;
}

