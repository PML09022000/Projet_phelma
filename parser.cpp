#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdbool.h>
#include <stdlib.h>

#include "parser.h"
#include "parser_dot.h"
#include "parser_json.h"


using namespace std;


//
// // Verification decoupage fichier .dot
// static bool parser_decoupage(vector<Symbole> &symbole_vector);
//
// // Verification decoupage fichier .json
// static bool parser_decoupage_json(vector<Symbole_json> &symbole_vector_json);
//
// // Parser de .dot
// static map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector);
//
// // Parser create stimulus  de json
//
// static vector <Stimulus >parser_create_stimulus_vector(vector<Symbole_json> &symbole_vector_json);


// Fonction parser json qui appelle les 2 fct decoupage et create stimulus
vector <Stimulus> parser_json(vector<Symbole_json> &symbole_vector_json)
{
  parser_decoupage_json(symbole_vector_json);
  cout << "parser.cpp, INFO : PARSER DECOUPAGE .JSON FINISHED WITH SUCCES " << endl;
  vector <Stimulus> stimulus_vector= parser_create_stimulus_vector(symbole_vector_json);
  cout << "parser.cpp, INFO : PARSER CREATE STIMULUS VECTOR .JSON FINISHED WITH SUCCES " << endl;
  return stimulus_vector;

}


map<string,Noeud> parser_dot(vector<Symbole> &symbole_vector){
    parser_decoupage_dot(symbole_vector);
    cout << "parser.cpp, INFO : PARSER DECOUPAGE .DOT FINISHED WITH SUCCES " << endl;
    map<string, Noeud>  noeud_vector = parser_nodes_and_links(symbole_vector);
    cout << "parser.cpp, INFO : PARSER NODES AND LINKS (.DOT) FINISHED WITH SUCCES " << endl;
    return noeud_vector;
  }
