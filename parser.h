#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include <string>
#include <map>

#include "symbole.h"
#include "stimulus.h"
#include "symbole_json.h"
#include "Noeud.h"
#include "stimulus.h"


map<string, Noeud> parser_dot(vector<Symbole> &symbole_vector);

//Fonction parser pour le fichier json
vector <Stimulus >parser_json(vector<Symbole_json> &symbole_vector_json);
//bool parser_decoupage_json(vector<Symbole_json> &symbole_vector_json);
//vector <Stimulus >parser_create_stimulus_vector(vector<Symbole_json> &symbole_vector_json);

#endif
