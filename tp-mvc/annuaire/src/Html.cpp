
#include "Html.hpp"

#include <format>

std::string renderHtml(const Annuaire & annuaire) {

  std::string page;

  // TODO
  page +=
R"(
<!DOCTYPE html>
<html lang="fr">

  <head>
    <meta charset="utf-8">
    <link href="/style.css" rel="stylesheet" />
    <title>Annuaire</title>
  </head>

  <body>
    <h1>Annuaire</h1>

    <h2>Liste (SSR)</h2>

    <p>TODO</p>

  </body>

</html>
)";

  return page;
}


