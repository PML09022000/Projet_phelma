#include <string.h>

#include "stimulus.h"

Stimulus::Stimulus(string nom) : m_nom(nom){}


Stimulus::~Stimulus(){}



string Stimulus::get_nom(){
  return m_nom;
}

int Stimulus::get_stimulus_size(){
  return m_valeur_stimulus.size();
}

int Stimulus::get_valeur_stimulus_at_index(int const index){
  return m_valeur_stimulus[index];
}


void Stimulus::add_valeur_stimulus(int sti){
  m_valeur_stimulus.push_back(sti);
}
