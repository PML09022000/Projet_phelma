#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "symbole.h"
#include "Noeud.h"
#include "stimulus.h"

#include "file_to_string.h"
#include "lexer.h"
#include "parser.h"
#include "matching.h"
#include "Simulateur.h"
#include "generate_output_json.h"

#define display 0

int main()
{
  //////////////////////  .DOT WORK //////////////////////

  std::vector<std::string> dot_line_vector = file_to_string_vector("mux.dot");
  // Affichage Vector de lignes//
  cout << "\nFILE .DOT OK " << endl;
  if(display){
    for(std::vector<string>::iterator it = dot_line_vector.begin(); it != dot_line_vector.end(); ++it) {
        cout << *it << endl;
    }
  }

  cout << endl;

  std::vector<Symbole> symbole_vector = lexeme_dot(dot_line_vector);
  // Affichage Vector de Symboles//
  cout << "\nLEXER .DOT FINISHED WITH SUCCES" << endl;
  if(display){
    for(vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end(); ++it) {
        Symbole symb = *it;
        cout << "Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
    }
  }

  cout << endl;

  map<string, Noeud> noeud_map = parser(symbole_vector);
  // Affichage Map de Noeud//
  cout << "\nPARSER .DOT FINISHED WITH SUCCES " << endl;
  if(display){
    for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it){
        Noeud noeud = it->second;
        cout << "Nom : " << noeud.get_nom() << "\t\t\tType : " << noeud.get_type() << "\t\t\tNb_input : " << noeud.get_nb_inout()<< "\t\t\tLink : "; noeud.print_link(); cout << endl;
    }
  }

  //////////////////////  .DOT WORK END //////////////////////
  //////////////////////  .JSON WORK BEGIN //////////////////////

  std::vector<std::string> json_line_vector = file_to_string_vector("Inputs.json");
  // Affichage Vector de lignes//
  cout << "\nFILE .JSON OK" << endl;
  if(display){
    for(std::vector<string>::iterator it = json_line_vector.begin(); it != json_line_vector.end(); ++it){
        cout << *it << endl;
    }
  }

  cout << endl;

  std::vector<Symbole_json> symbole_vector_json = lexeme_json(json_line_vector);
  // Affichage Vector de Symboles//
  cout << "\nLEXER .JSON FINISHED WITH SUCCES" << endl;
  if(display){
    for(vector<Symbole_json>::iterator it = symbole_vector_json.begin(); it != symbole_vector_json.end(); ++it) {
        Symbole_json symb = *it;
        cout << "Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
    }
  }

  cout << endl;

  std::vector<Stimulus> stimulus_vector= parser_json(symbole_vector_json);
  cout << "\nPARSER .JSON FINISHED WITH SUCCES " << endl;

  //////////////////////  .JSON WORK END /////////////////////

  /////////////// MATCH BETWEEN .DOT AND .JSON BEGIN /////////
  matching(noeud_map, stimulus_vector);
  std::cout << "DOT & JSON MATCHING FINISHED WITH SUCCES" << '\n';
  cout << endl;
  /////////////// MATCH BETWEEN .DOT AND .JSON END /////////

  /////////////////// RUN SIMULATION BEGIN /////////////////
  std::cout << "\nSTARTING SIMULATION" << '\n';
  vector<Stimulus> output_result_vector = Simulateur(noeud_map, stimulus_vector);
  std::cout << "\nSIMULATION FINISHED" << '\n';
  cout << endl;
  /////////////////// RUN SIMULATION END /////////////////

  ////////////////// GENERATE OUTPUT JSON BEGIN ///////////////////////
  std::cout << "GENERATING OUTPUT .JSON" << '\n';
  generate_output_json(output_result_vector);
  std::cout << "OUTPUT .JSON GENERATED" << '\n';
  cout << endl;
  ////////////////// GENERATE OUTPUT JSON END ///////////////////////

  std::cout << "PROG TERMINATED WITH SUCCES" << '\n';

  return 0;
}
