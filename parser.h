#ifndef _PARSER_H_
#define _PARSER_H_

#include "symbole.h"
#include "Noeud.h"

#include <string>
#include <map>


map<string, Noeud> parser(vector<Symbole> &symbole_vector);

#endif
