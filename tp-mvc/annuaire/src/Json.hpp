#pragma once

#include "Annuaire.hpp"

#include <hv/HttpMessage.h>

void to_json(hv::Json & j, const Personne & p);

