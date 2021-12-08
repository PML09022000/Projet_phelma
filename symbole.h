#ifndef  _SYMBOLE_H_
#define _SYMBOLE_H_

#include <string>
#include <iostream>

using namespace std;

enum Nature_grammaticale
{
    identifiant,
    mot_clef,
    ponctuation,
    operateurs,
    valeur_numerique_logique
};

class Symbole{
  private:
    Nature_grammaticale m_nom;
    string m_valeur;
    int m_line_index;

  public:
    Symbole(Nature_grammaticale nom, string valeur, int line_index);
    ~Symbole();
    void set_valeur(string valeur);
    int get_line_index();
};

#endif
