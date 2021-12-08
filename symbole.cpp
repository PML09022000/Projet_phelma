#include <string.h>

#include "symbole.h"

Symbole::Symbole(Nature_grammaticale nom, string valeur, int line_index) : m_nom(nom), m_valeur(valeur), m_line_index(line_index){};


Symbole::~Symbole(){}

int Symbole::get_line_index(){
  return m_line_index;
}

void Symbole::set_valeur(string valeur){
  m_valeur = valeur;
}
