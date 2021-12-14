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


int main()
{
  //////////////////////  .DOT WORK //////////////////////

  std::vector<std::string> dot_line_vector = file_to_string_vector("and_xor.dot");
  // Affichage Vector de lignes//
  cout << "\nFILE .DOT : " << endl;
  for(std::vector<string>::iterator it = dot_line_vector.begin(); it != dot_line_vector.end(); ++it) {
      cout << *it << endl;
  }

  cout << endl;

  std::vector<Symbole> symbole_vector = lexeme_dot(dot_line_vector);
  // Affichage Vector de Symboles//
  cout << "\nLEXER .DOT FINISHED WITH SUCCES : " << endl;
  for(vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end(); ++it) {
      Symbole symb = *it;
      cout << "Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
  }

  cout << endl;

  map<string, Noeud> noeud_map = parser(symbole_vector);
  // Affichage Map de Noeud//
  cout << "\nPARSING FINISHED WITH SUCCES : " << endl;
  for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it){
      Noeud noeud = it->second;
      cout << "Nom : " << noeud.get_nom() << "\t\t\tType : " << noeud.get_type() << "\t\t\tNb_input : " << noeud.get_nb_inout()<< "\t\t\tLink : "; noeud.print_link(); cout << endl;
  }

  //////////////////////  .DOT WORK END //////////////////////
  //////////////////////  .JSON WORK BEGIN //////////////////////

  std::vector<std::string> json_line_vector = file_to_string_vector("Inputs.json");
  // Affichage Vector de lignes//
  cout << "\nFILE .JSON: " << endl;
  for(std::vector<string>::iterator it = json_line_vector.begin(); it != json_line_vector.end(); ++it){
      cout << *it << endl;
  }

  cout << endl;

  std::vector<Symbole_json> symbole_vector_json = lexeme_json(json_line_vector);
  // Affichage Vector de Symboles//
  cout << "\nLEXER .JSON FINISHED WITH SUCCES : " << endl;
  for(vector<Symbole_json>::iterator it = symbole_vector_json.begin(); it != symbole_vector_json.end(); ++it) {
      Symbole_json symb = *it;
      cout << "Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
  }

  cout << endl;

  //bool ret = parser_decoupage_json(symbole_vector_json);

  std::vector<Stimulus> stimulus_vector; // = la valeur de retour de la fonction parser_json... ...à compléter

  //////////////////////  .JSON WORK END /////////////////////
  /////////////// MATCH BETWEEN .DOT AND .JSON BEGIN /////////
  Stimulus Sti1("I1") ; Sti1.add_valeur_stimulus(1); Sti1.add_valeur_stimulus(0); stimulus_vector.push_back(Sti1);
  Stimulus Sti2("I2") ; Sti2.add_valeur_stimulus(1); Sti2.add_valeur_stimulus(1); stimulus_vector.push_back(Sti2);
  Stimulus Sti3("I3") ; Sti3.add_valeur_stimulus(0); Sti3.add_valeur_stimulus(1); stimulus_vector.push_back(Sti3);


  apply_stimulus(noeud_map, stimulus_vector);

  std::cout << "DOT & JSON MATCHING FINISHED WITH SUCCES" << '\n';
  /////////////// MATCH BETWEEN .DOT AND .JSON END /////////
  /////////////////// RUN SIMULATION BEGIN /////////////////

  /////////////////// RUN SIMULATION END /////////////////
  return 0;
}
