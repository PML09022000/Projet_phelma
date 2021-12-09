#include <string.h>

#include "symbole.h"

Symbole::Symbole(Nature_grammaticale nature, string valeur, int line_index) : m_nature(nature), m_valeur(valeur), m_line_index(line_index){};


Symbole::~Symbole(){}

int Symbole::get_line_index(){
  return m_line_index;
}

string Symbole::get_valeur(){
  return m_valeur;
}

Nature_grammaticale Symbole::get_nature(){
  return m_nature;
}
