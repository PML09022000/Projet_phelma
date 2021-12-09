#ifndef _NOEUD_H_
#define _NOEUD_H_

#include <iostream>


using namespace std;

class Noeud {

private:

string nom;
string type;
int nb_inout;
bool valeur;
const Noeud *tab; //vecteur de Noeuds avec les adresses sur les quelles il pointe

public:
// Constructeur
Noeud(string nom, string type,int nb_inout, bool valeur);
//Destructeur
~Noeud();

// Accesseur
string get_nom() const;
string get_type() const;
bool get_valeur() const;
int get_nb_inout() const;


//
void set_nom(string name);
void set_logic_state (bool valeur);



};
#endif
