// Simulateur

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdbool.h>
#include <map>

#include "Simulateur.h"
#include "Noeud.h"

using namespace std;

#define debug 0

enum SUMULATOR_FSM_STATE{
  CHECK_INDEX_IN_STMULUS_VECTOR,
  REINITIALIZE_NOEUDS_VALUES,
  APPLY_INDEX_STIMULUS_VALUES_TO_INPUT,
  CALCULATE_OUTPUTS,
  NEXT_INDEX,

  SIMULATION_END,
};


static int andX_result(vector<int> tab_data_operation){
  int result = 1;
  for(std::vector<int>::iterator it = tab_data_operation.begin(); it != tab_data_operation.end(); ++it){
    result &= *it;
  }
  return result;
}

static int xorX_result(vector<int> tab_data_operation){
  int result;
  for(std::vector<int>::iterator it = (tab_data_operation.begin()+1); it != tab_data_operation.end(); ++it){
    *it = (*it) ^ (*(it-1));
    result = *it;
  }
  return result;
}

static int orX_result(vector<int> tab_data_operation){
  int result = 0;
  for(std::vector<int>::iterator it = tab_data_operation.begin(); it != tab_data_operation.end(); ++it){
    result |= *it;
  }
  return result;
}

static int not_result(int x){
  return (x == 0) ? 1:0;
}

static int nandX_result(vector<int> tab_data_operation){
  int result = andX_result(tab_data_operation);
  result = not_result(result);
  return result;
}

static int norX_result(vector<int> tab_data_operation){
  int result = orX_result(tab_data_operation);
  result = not_result(result);
  return result;
}

static int xnorX_result(vector<int> tab_data_operation){
  int result = xorX_result(tab_data_operation);
  result = not_result(result);
  return result;
}

static int mux2_result(vector<int> tab_data_operation){
  if(tab_data_operation[0] == 0){
    return tab_data_operation[1];
  }else{
    return tab_data_operation[2];
  }
}

static void fonction_recursive(Noeud &noeud, map<string, Noeud> &noeud_map){

  std::map<string,Noeud>::iterator it_map;
  vector<string> dependances = noeud.get_links();
  vector<int> tab_data_operation;
  tab_data_operation.clear();

  for(std::vector<string>::iterator it = dependances.begin(); it != dependances.end(); ++it){

    it_map = noeud_map.find(*it);
    if(( (it_map->second).get_valeur() ) > 1){
      fonction_recursive((it_map->second), noeud_map);
    }else{
    }
    tab_data_operation.push_back((it_map->second).get_valeur( ));
  }

  if(debug){
    for(std::vector<string>::iterator it = dependances.begin(); it != dependances.end(); ++it){
      it_map = noeud_map.find(*it);
      cout  << "simulateur.cpp, DEBUG : "<< (it_map->second).get_nom() << " (logic value : " <<(it_map->second).get_valeur() << ") apply to " << noeud.get_nom() << endl;
    }
  }

  switch ( noeud.get_type() ) {
      case ANDX:
        noeud.set_logic_state(andX_result(tab_data_operation));
        break;

      case NANDX:
        noeud.set_logic_state(nandX_result(tab_data_operation));
        break;

      case XORX:
        noeud.set_logic_state(xorX_result(tab_data_operation));
        break;

      case ORX:
        noeud.set_logic_state(orX_result(tab_data_operation));
        break;

      case XNORX:
        noeud.set_logic_state(xnorX_result(tab_data_operation));
        break;

      case NORX:
        noeud.set_logic_state(norX_result(tab_data_operation));
        break;

      case MUXX:
        noeud.set_logic_state(mux2_result(tab_data_operation));
        break;

      case NOT:
        noeud.set_logic_state(not_result(tab_data_operation[0]));
        break;

      case OUTPUT:
        noeud.set_logic_state((it_map->second).get_valeur());

      default:
        break;
  }
  if(debug){
    cout << "simulateur.cpp, DEBUG : " << noeud.get_nom( ) << " result : "<< noeud.get_valeur( ) << endl;
  }
}

static bool can_we_apply_stimu_at_index(vector<Stimulus> stimulus_vector, int index){
  for(vector<Stimulus>::iterator it = stimulus_vector.begin(); it != stimulus_vector.end(); ++it){
    if((*it).get_stimulus_size() < (index+1)){
      return false;
    }
  }
  return true;
}

static void apply_stimulus(map<string, Noeud> &noeud_map, vector<Stimulus> stimulus_vector, int index){
  std::map<string,Noeud>::iterator it_map;
  for(vector<Stimulus>::iterator it = stimulus_vector.begin(); it != stimulus_vector.end(); ++it){
    it_map = noeud_map.find((*it).get_nom());
    int stimu = (*it).get_valeur_stimulus_at_index(index);
    (it_map->second).set_logic_state(stimu);
  }
}

static void init_noeuds_values(map<string, Noeud> &noeud_map){
  for(map<string, Noeud>::iterator it_map = noeud_map.begin(); it_map != noeud_map.end(); ++it_map) {
    (it_map->second).set_logic_state(2);
  }
}

static void calculate_outputs(map<string, Noeud> &noeud_map, vector<Stimulus> &output_result_vector){
  for(map<string, Noeud>::iterator it_map = noeud_map.begin(); it_map != noeud_map.end(); ++it_map) {
    if((it_map->second).get_type() == OUTPUT){
      fonction_recursive((it_map->second), noeud_map);
      //cout << "OUTPUT " << (it_map->second).get_nom() << " = " << (it_map->second).get_valeur() << endl << endl;
      for(vector<Stimulus>::iterator it = output_result_vector.begin(); it != output_result_vector.end(); ++it){
        if((*it).get_nom() == (it_map->second).get_nom()){
          (*it).add_valeur_stimulus((it_map->second).get_valeur());
        }
      }
    }else{}
  }
}


vector<Stimulus> Simulateur(map<string, Noeud> noeud_map, vector<Stimulus> stimulus_vector)
{
  vector<Stimulus> output_result_vector;

  for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it) {
    if((it->second).get_type() == OUTPUT){
      Stimulus Sti((it->second).get_nom());
      output_result_vector.push_back(Sti);
    }else{

    }
  }

  int cpt_simulation_cycle = 0;
  int index = 0;
  SUMULATOR_FSM_STATE next_state = APPLY_INDEX_STIMULUS_VALUES_TO_INPUT;

  while(next_state != SIMULATION_END){
    switch(next_state){
      case CHECK_INDEX_IN_STMULUS_VECTOR :
        next_state = (can_we_apply_stimu_at_index(stimulus_vector, index) == true) ? REINITIALIZE_NOEUDS_VALUES : SIMULATION_END;
        break;

      case REINITIALIZE_NOEUDS_VALUES :
        init_noeuds_values(noeud_map);
        next_state = APPLY_INDEX_STIMULUS_VALUES_TO_INPUT;
        break;

      case APPLY_INDEX_STIMULUS_VALUES_TO_INPUT :
        apply_stimulus(noeud_map, stimulus_vector, index);
        next_state = CALCULATE_OUTPUTS;
        break;

      case CALCULATE_OUTPUTS :
        calculate_outputs(noeud_map, output_result_vector);
        if(debug){
          cout  << "simulateur.cpp, DEBUG : " << "Outputs calculation cycle "<< ++cpt_simulation_cycle << " is over\n" << endl;
        }
        next_state = NEXT_INDEX;
        break;

      case NEXT_INDEX:
        index ++;
        next_state = CHECK_INDEX_IN_STMULUS_VECTOR;
        break;

      case SIMULATION_END :
      break;

      default:
        next_state = SIMULATION_END;
        break;
      break;
    }
  }

  return output_result_vector;

}
