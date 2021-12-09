#ifndef  _SYMBOLE_H_
#define _SYMBOLE_H_

#include <string>
#include <iostream>

using namespace std;

enum Nature_grammaticale
{
    identifiant = 1,
    mot_clef,
    ponctuation,
    operateur,
};

class Symbole{
  private:
    Nature_grammaticale m_nature;
    string m_valeur;
    int m_line_index;

  public:
    Symbole(Nature_grammaticale nature, string valeur, int line_index);
    ~Symbole();

    int get_line_index();
    string get_valeur();
    Nature_grammaticale get_nature();
};

#endif
