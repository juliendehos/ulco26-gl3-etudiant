#include <hv/HttpServer.h>

#include "Html.hpp"

const int port = 3000;

int main(int argc, char ** argv) {

  HttpService router;

  router.Static("/", "./static");

  router.GET("/", [](const HttpContextPtr& ctx) {
    return ctx->redirect("/index.html");
  });

  // TODO route /index.html

  // TODO route /human.html

  // TODO route /human.svg

  // TODO route /face.html

  // TODO route /face.svg

  std::cout << "listening, port " << port << "..." << std::endl;
  hv::HttpServer server(&router);
  server.setPort(port);
  server.run();

  return 0;
}

