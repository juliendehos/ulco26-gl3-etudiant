
#include "MonForum.hpp"
#include "View.hpp"

#include <hv/HttpServer.h>
#include <hv/hlog.h>

#include <format>

const int port = 3000;

int main(int argc, char ** argv) {

  HttpService router;

  // route statique /
  router.Static("/", "./static");

  // route get /
  router.GET("/", [](HttpRequest *, HttpResponse * resp) {
    resp->content_type = TEXT_HTML;
    resp->body = "<h1>MonForum</h1>";
    return 200;
  });

  // lance le serveur
  std::cout << "listening, port " << port << "..." << std::endl;
  hv::HttpServer server(&router);
  server.setPort(port);
  server.run();

  return 0;
}

