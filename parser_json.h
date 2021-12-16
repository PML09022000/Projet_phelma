#ifndef _PARSERJSON_H_
#define _PARSERJSON_H_

#include <vector>

#include "symbole_json.h"
#include "stimulus.h"

void parser_decoupage_json(vector<Symbole_json> &symbole_vector_json);
vector <Stimulus> parser_create_stimulus_vector(vector<Symbole_json> &symbole_vector_json);

#endif
