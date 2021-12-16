#ifndef _PARSERDOT_H_
#define _PARSERDOT_H_

#include "symbole.h"
#include "stimulus.h"
#include "Noeud.h"
#include "stimulus.h"


#include <string>
#include <vector>
#include <map>


map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector);
void parser_decoupage(vector<Symbole> &symbole_vector);

#endif
