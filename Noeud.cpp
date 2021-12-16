#include <iostream>
#include <iterator>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include "Noeud.h"

using namespace std;



Noeud::Noeud(string nom1, TYPE_enum type1, unsigned int nb): m_nom(nom1), m_type(type1), m_nb_inout(nb), m_valeur(2) // liste d'initialisation
{
  //std::cout << "Construction of class Noeud"<< std::endl;
}

Noeud::~Noeud()
{

//cout<< "Destruction of class Noeud"<< std::endl;
}

// Accesseurs

string Noeud::  get_nom() const {
  return this-> m_nom;
}
int Noeud:: get_valeur()const{
   return this-> m_valeur;
}


unsigned int Noeud::get_nb_inout() const{
  return this-> m_nb_inout;
}


TYPE_enum Noeud::get_type() const{
  return this-> m_type;
}

void Noeud:: print_link() {
  ostream_iterator<string> it(cout, ", ");
  for(std::vector<string>::iterator it_noeud = m_noeud_noms_pre.begin(); it_noeud != m_noeud_noms_pre.end(); ++it_noeud){
    *it = *it_noeud;
  }
}


vector<string> Noeud:: get_links() const
{
  return this-> m_noeud_noms_pre;

}




////////////////////////////////////////:

void Noeud::set_nom(string name){
  this->m_nom=name;
}

void Noeud::set_logic_state (int val){
   this-> m_valeur=val;
}

void Noeud::add_link_to_previous_noeud (string m_nom){
   m_noeud_noms_pre.push_back(m_nom);
}
