#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

#include "generate_output_json.h"


void generate_output_json(vector<Stimulus> output_result_vector){
  ostringstream flux;

  flux << "{signal: [\n";

  for(vector<Stimulus>::iterator it = output_result_vector.begin(); it != output_result_vector.end(); ++it){
    int stimulus_size = (*it).get_stimulus_size();
    flux << "\t{name: '";
    flux << (*it).get_nom();
    flux << "',  wave: '";
    int i = 0;
    int valeur = 2; int pre_valeur = 2;
    while(i< (stimulus_size)){
      valeur = (*it).get_valeur_stimulus_at_index(i);
      if(pre_valeur == valeur){
        flux << '.';
      }else{
        flux << valeur;
      }
      pre_valeur = valeur;
      i++;
    }
    flux << "'}',\n";
  }
  flux << "]}";

  std::ofstream outfile ("Outputs.json");
  outfile << flux.str() << std::endl;
  outfile.close();

}
