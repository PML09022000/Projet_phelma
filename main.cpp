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

#define debug 1

int main()
{
  std::cout << "\nmain.cpp, INFO : PROG RUNNNING" << '\n';
  //////////////////////  .DOT WORK //////////////////////

  std::vector<std::string> dot_line_vector = file_to_string_vector("full_adder.dot");
  // Affichage Vector de lignes//
  cout << "\nmain.cpp, INFO : FILE .DOT OK " << endl;
  if(debug){
    for(std::vector<string>::iterator it = dot_line_vector.begin(); it != dot_line_vector.end(); ++it) {
        cout << "main.cpp, DEBUG : " << *it << endl;
    }
    cout << endl;
  }



  std::vector<Symbole> symbole_vector = lexeme_dot(dot_line_vector);
  // Affichage Vector de Symboles//
  cout << "main.cpp, INFO : LEXER .DOT FINISHED WITH SUCCES" << endl;
  if(debug){
    for(vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end(); ++it) {
        Symbole symb = *it;
        cout << "main.cpp, DEBUG : Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
    }
    cout << endl;
  }


  map<string, Noeud> noeud_map = parser_dot(symbole_vector);
  // Affichage Map de Noeud//
  cout << "main.cpp, INFO : PARSER .DOT FINISHED WITH SUCCES " << endl;
  if(debug){
    for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it){
        Noeud noeud = it->second;
        cout << "main.cpp, DEBUG : Nom : " << noeud.get_nom() << "\t\t\tType : " << noeud.get_type() << "\t\t\tNb_input : " << noeud.get_nb_inout()<< "\t\t\tLink : "; noeud.print_link(); cout << endl;
    }
  }

  //////////////////////  .DOT WORK END //////////////////////
  //////////////////////  .JSON WORK BEGIN //////////////////////

  std::vector<std::string> json_line_vector = file_to_string_vector("full_adder.json");
  // Affichage Vector de lignes//
  cout << "\nmain.cpp, INFO : FILE .JSON OK" << endl;
  if(debug){
    for(std::vector<string>::iterator it = json_line_vector.begin(); it != json_line_vector.end(); ++it){
        cout << "main.cpp, DEBUG : " << *it << endl;
    }
    cout << endl;
  }

  std::vector<Symbole_json> symbole_vector_json = lexeme_json(json_line_vector);
  // Affichage Vector de Symboles//
  cout << "main.cpp, INFO : LEXER .JSON FINISHED WITH SUCCES" << endl;
  if(debug){
    for(vector<Symbole_json>::iterator it = symbole_vector_json.begin(); it != symbole_vector_json.end(); ++it) {
        Symbole_json symb = *it;
        cout << "main.cpp, DEBUG : Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
    }
    cout << endl;
  }


  std::vector<Stimulus> stimulus_vector= parser_json(symbole_vector_json);
  cout << "main.cpp, INFO : PARSER .JSON FINISHED WITH SUCCES " << endl;
  if(debug){
    for(vector<Stimulus>::iterator it = stimulus_vector.begin(); it != stimulus_vector.end(); ++it) {
        Stimulus stimu = *it;
        cout << "main.cpp, DEBUG : Nom : " << stimu.get_nom() << "\tValeur : ";
        for(int i = 0 ; i < stimu.get_stimulus_size() ; i++){
          cout << stimu.get_valeur_stimulus_at_index(i);
        }
        cout << endl;
    }
    cout << endl;
  }

  //////////////////////  .JSON WORK END /////////////////////

  /////////////// MATCH BETWEEN .DOT AND .JSON BEGIN /////////
  matching(noeud_map, stimulus_vector);
  std::cout << "\nmain.cpp, INFO : DOT & JSON MATCHING FINISHED WITH SUCCES" << '\n';
  /////////////// MATCH BETWEEN .DOT AND .JSON END /////////

  /////////////////// RUN SIMULATION BEGIN /////////////////
  std::cout << "\nmain.cpp, INFO : STARTING SIMULATION" << '\n';
  vector<Stimulus> output_result_vector = Simulateur(noeud_map, stimulus_vector);
  std::cout << "main.cpp, INFO : SIMULATION FINISHED WITH SUCCES" << '\n';
  if(debug){
    for(vector<Stimulus>::iterator it = output_result_vector.begin(); it != output_result_vector.end(); ++it) {
        Stimulus stimu = *it;
        cout << "main.cpp, DEBUG : Nom : " << stimu.get_nom() << "\tValeur : ";
        for(int i = 0 ; i < stimu.get_stimulus_size() ; i++){
          cout << stimu.get_valeur_stimulus_at_index(i);
        }
        cout << endl;
    }
    cout << endl;
  }
  /////////////////// RUN SIMULATION END /////////////////

  ////////////////// GENERATE OUTPUT JSON BEGIN ///////////////////////
  std::cout << "\nmain.cpp, INFO : GENERATING OUTPUT .JSON" << '\n';
  generate_output_json(output_result_vector);
  std::cout << "main.cpp, INFO : OUTPUT .JSON GENERATED" << '\n';
  ////////////////// GENERATE OUTPUT JSON END ///////////////////////

  std::cout << "\nmain.cpp, INFO : PROG TERMINATED WITH SUCCES\n" << '\n';

  return 0;
}
