
#include "Annuaire.hpp"
#include "Html.hpp"
#include "Json.hpp"

#include <hv/HttpServer.h>
#include <hv/hlog.h>

const int port = 3000;

int main(int argc, char ** argv) {

  Annuaire annuaire = mkAnnuaireTest();

  HttpService router;

  // route statique /
  router.Static("/", "./static");

  // TODO route get /api/annuaire

  // TODO route get /liste_ssr.html

  // TODO route post /add

  // lance le serveur
  std::cout << "listening, port " << port << "..." << std::endl;
  hv::HttpServer server(&router);
  server.setPort(port);
  server.run();

  return 0;
}

