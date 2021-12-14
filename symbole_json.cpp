#include <string.h>

#include "symbole_json.h"

Symbole_json::Symbole_json(Nature_grammaticale_json nature, string valeur, int line_index) : m_nature_json(nature), m_valeur_json(valeur), m_line_index_json(line_index){};


Symbole_json::~Symbole_json(){}

int Symbole_json::get_line_index(){
  return m_line_index_json;
}

string Symbole_json::get_valeur(){
  return m_valeur_json;
}

Nature_grammaticale_json Symbole_json::get_nature(){
  return m_nature_json;
}
