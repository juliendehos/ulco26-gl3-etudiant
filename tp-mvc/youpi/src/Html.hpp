#pragma once

#include "Scene.hpp"

#include <string>

// retourne le contenu HTML de la page principale
std::string mkPageIndex();

// retourne le contenu HTML d'une page d'image
std::string mkPageHtml(const std::string & imageTitle, const std::string & imageSrc);

// retourne le contenu d'une image SVG
std::string mkPageSvg(const Scene & scene);

