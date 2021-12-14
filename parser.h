#ifndef _PARSER_H_
#define _PARSER_H_

#include "symbole.h"
#include "symbole_json.h"
#include "Noeud.h"

#include <string>
#include <map>


map<string, Noeud> parser(vector<Symbole> &symbole_vector);

//Fonction parser pour le fichier json

map<string,vector<int> &symbole_valeur > parser_json(vector<Symbole_json> &symbole_vector_json);

#endif
