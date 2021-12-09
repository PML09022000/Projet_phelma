#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include "Noeud.h"

using namespace std;



Noeud::Noeud(string nom1, string type1, int nb, bool val1): nom(nom1), type(type1), nb_inout(nb),valeur(val1)  // liste d'initialisation
{
  std::cout << "Construction of class Noeud"<< std::endl;
}

Noeud::~Noeud()
{

cout<< "Destruction of class Noeud"<< std::endl;
}

// Accesseurs

string Noeud::  get_nom() const {
  return this-> nom;
}
bool Noeud:: get_valeur()const{
   return this-> valeur;
}


int Noeud::get_nb_inout() const{
  return this-> nb_inout;
}


string Noeud::get_type() const{
  return this-> type;
}

////////////////////////////////////////:

void Noeud::set_nom(string name){
  this->nom=name;
}

void Noeud::set_logic_state (bool val){
   this-> valeur=val;
}
