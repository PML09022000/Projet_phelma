#ifndef _PARSERDOT_H_
#define _PARSERDOT_H_

#include <string>
#include <vector>
#include <map>

#include "symbole.h"
#include "Noeud.h"

void parser_decoupage_dot(vector<Symbole> &symbole_vector);
map<string, Noeud>  parser_nodes_and_links(vector<Symbole> &symbole_vector);

#endif
