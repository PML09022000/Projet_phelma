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
  int result = 1;
  for(std::vector<int>::iterator it = tab_data_operation.begin(); it != tab_data_operation.end(); ++it){
    result |= *it;
  }
  return result;
}

static int mux2_result(vector<int> tab_data_operation){
  cout << "sel = " << tab_data_operation[0] << endl;
  cout << tab_data_operation[1] << "  " <<tab_data_operation[2] << endl;
  if(tab_data_operation[0] == 0){
    return tab_data_operation[1];
  }else{
    return tab_data_operation[2];
  }
}

static void maj_tab_data(vector<int> &tab_data_operation, int maj_data){
  tab_data_operation.clear();
  tab_data_operation.push_back(maj_data);
}

static void fonction_recursive(Noeud &noeud, map<string, Noeud> &noeud_map){

  std::map<string,Noeud>::iterator it_map;
  vector<string> dependances = noeud.get_links();
  static vector<int> tab_data_operation;
  tab_data_operation.clear();

  for(std::vector<string>::iterator it = dependances.begin(); it != dependances.end(); ++it){

    it_map = noeud_map.find(*it);

    if(( (it_map->second).get_valeur() ) > 1){
      fonction_recursive((it_map->second), noeud_map);
    }else{
      tab_data_operation.push_back((it_map->second).get_valeur( ));
    }

    switch ( (it_map->second).get_type() ) {
      case ANDX:
        (it_map->second).set_logic_state(andX_result(tab_data_operation));
        maj_tab_data(tab_data_operation, (it_map->second).get_valeur());
        cout << "AND" << (it_map->second).get_nb_inout( ) << " result : " <<(it_map->second).get_valeur( ) << endl;
        break;

      case XORX:
        (it_map->second).set_logic_state(xorX_result(tab_data_operation));
        maj_tab_data(tab_data_operation, (it_map->second).get_valeur());
        cout << "XOR" << (it_map->second).get_nb_inout( ) << " result : "<<(it_map->second).get_valeur( ) << endl;
        break;

      default:
        break;
    }
  }
  noeud.set_logic_state(tab_data_operation[0]);
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
