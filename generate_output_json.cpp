#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "generate_output_json.h"


void generate_output_json(vector<Stimulus> output_result_vector){
  ostringstream flux;

  flux << "{signal: [\n";

  for(vector<Stimulus>::iterator it = output_result_vector.begin(); it != output_result_vector.end(); ++it){
    flux << "{name: '";
    flux << (*it).get_nom();
    flux << "',  wave: '";
  }


  string const chaine = flux.str(); //On récupère la chaine

  cout << chaine << endl;  //Affiche 'Salut les zeros !'

  flux << "\n]}";
}
