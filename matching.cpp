#include <stdbool.h>
#include <stdlib.h>

#include "matching.h"


enum CHECK_NOEUD_MAP_IN_STIMULUS_VECTOR_FSM_STATE{
  IS_NOEUD_IN_MAP_AN_INPUT,
  CHECK_NAME_INPUT_WITH_STIMULUS_VECTOR,
  ERROR_NO_STIMULUS,
  NEXT_NOEUD,
};

enum CHECK_STIMULUS_VECTOR_IN_NOEUD_MAP_FSM_STATE{
  IS_STIMULUS_NAME_IN_MAP_AS_AN_INPUT,
  ERROR_STIMULUS_TO_UNDECLARED_INPUT,
  NEXT_STIMULUS,
};

static bool is_name_in_stimulus_vector(string name, vector<Stimulus> stimulus_vector, int* p_index){
  for(vector<Stimulus>::iterator it = stimulus_vector.begin(); it != stimulus_vector.end(); ++it){
    if(name == (*it).get_nom()){
      *p_index = it - stimulus_vector.begin();
      return true;
    }else{}
  }
  return false;
}

void matching(map<string, Noeud> noeud_map, vector<Stimulus> stimulus_vector){
  int cpt_error = 0;

  CHECK_NOEUD_MAP_IN_STIMULUS_VECTOR_FSM_STATE state_1 = IS_NOEUD_IN_MAP_AN_INPUT;
  int index = 0;
  for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end();){
    switch(state_1){
      case IS_NOEUD_IN_MAP_AN_INPUT:
        state_1 = ( (it->second).get_type() == INPUT ) ? CHECK_NAME_INPUT_WITH_STIMULUS_VECTOR : NEXT_NOEUD;
        break;

      case CHECK_NAME_INPUT_WITH_STIMULUS_VECTOR:
        state_1 = (is_name_in_stimulus_vector( (it->second).get_nom(), stimulus_vector, &index ) == true) ? NEXT_NOEUD : ERROR_NO_STIMULUS;
        break;

      case ERROR_NO_STIMULUS:
        cpt_error++;
        cout << "Error check stimulus, INPUT " << (it->second).get_nom() << " don't have her STIMULUS" << endl;
        state_1 = NEXT_NOEUD;
        break;

      case NEXT_NOEUD:
        ++it;
        state_1 = IS_NOEUD_IN_MAP_AN_INPUT;
        break;

      default:
        break;
    }
  }

  CHECK_STIMULUS_VECTOR_IN_NOEUD_MAP_FSM_STATE state_2 = IS_STIMULUS_NAME_IN_MAP_AS_AN_INPUT;
  std::map<string,Noeud>::iterator it_map;
  for(vector<Stimulus>::iterator it = stimulus_vector.begin(); it != stimulus_vector.end();){
    switch(state_2){
      case IS_STIMULUS_NAME_IN_MAP_AS_AN_INPUT:
        it_map = noeud_map.find((*it).get_nom());
        state_2 = (it_map != noeud_map.end() && (it_map->second).get_type() == INPUT) ? NEXT_STIMULUS : ERROR_STIMULUS_TO_UNDECLARED_INPUT;
        break;

      case ERROR_STIMULUS_TO_UNDECLARED_INPUT:
        cpt_error++;
        cout << "Error check stimulus, STIMULUS " << (*it).get_nom() << " don't have his INPUT" << endl;
        state_2 = NEXT_STIMULUS;
        break;

      case NEXT_STIMULUS:
        ++it;
        state_2 = IS_STIMULUS_NAME_IN_MAP_AS_AN_INPUT;
        break;

      default:
        break;
    }
  }

  if(cpt_error == 0){

  }else{
    cout << "Nombre total d'erreurs : " << cpt_error << endl;
    cout << "Prog killed in check_stimulus.cpp"<< endl<< endl;
    exit(-1);
  }
}
