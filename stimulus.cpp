#include <string.h>

#include "stimulus.h"

Stimulus::Stimulus(string nom) : m_nom(nom){}


Stimulus::~Stimulus(){}



string Stimulus::get_nom(){
  return m_nom;
}


vector<int> Stimulus::get_valeur_stimulus(){
  return m_valeur_stimulus;
}


void Stimulus::add_valeur_stimulus(int sti){
  m_valeur_stimulus.push_back(sti);
}
