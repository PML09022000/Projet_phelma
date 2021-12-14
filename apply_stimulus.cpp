#include "apply_stimulus.h"

enum CHECK_NOEUD_MAP_IN_STIMULUS_VECTOR_FSM_STATE{
  IS_NOEUD_IN_MAP_AN_INPUT,
  CHECK_NAME_INPUT_WITH_STIMULUS_VECTOR,
  ERROR_NO_STIMULUS,
  NEXT_NOEUD,
};

enum CHECK_STIMULUS_VECTOR_IN_NOEUD_MAP_FSM_STATE{
  IS_NOEUD_IN_MAP_AN_INPUT,
  CHECK_NAME_INPUT_WITH_STIMULUS_VECTOR,
  ERROR_NO_STIMULUS,
};

void apply_stimulus(map<string, Noeud> &noeud_map, vector<int> stimulus){
  CHECK_NOEUD_MAP_IN_STIMULUS_VECTOR_FSM_STATE state = IS_NOEUD_IN_MAP_AN_INPUT;
  for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end();){
    switch(state){
      case IS_NOEUD_IN_MAP_AN_INPUT:
      break;

      case IS_NOEUD_IN_MAP_AN_INPUT:
      break;

      case IS_NOEUD_IN_MAP_AN_INPUT:
      break;
    }
    if( (it->second).get_type() == INPUT){
      for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it)
    }
  }
}
