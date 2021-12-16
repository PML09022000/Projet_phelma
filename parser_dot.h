#ifndef _PARSERDOT_H_
#define _PARSERDOT_H_

#include <string>
#include <vector>
#include <map>

#include "symbole.h"
#include "Noeud.h"

map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector);
void parser_decoupage(vector<Symbole> &symbole_vector);

#endif
