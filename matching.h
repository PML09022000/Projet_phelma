#ifndef _MATCHING_H_
#define _MATCHING_H_

#include <vector>
#include <map>

#include "Noeud.h"
#include "stimulus.h"

void matching(map<string, Noeud> noeud_map, vector<Stimulus> stimulus_vector);
void check_is_there_an_output(map<string, Noeud> noeud_map);

#endif
