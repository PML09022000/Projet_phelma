#ifndef _PARSERJSON_H_
#define _PARSERJSON_H_

#include "symbole.h"
#include "stimulus.h"
#include "symbole_json.h"
#include "Noeud.h"
#include "stimulus.h"


#include <string>
#include <vector>


void parser_decoupage_json(vector<Symbole_json> &symbole_vector_json);
vector <Stimulus> parser_create_stimulus_vector(vector<Symbole_json> &symbole_vector_json);

#endif
