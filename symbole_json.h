#ifndef  _SYMBOLEJSON_H_
#define  _SYMBOLEJSON_H_

#include <string>
#include <iostream>

using namespace std;

enum Nature_grammaticale_json
{
    identifiant_json = 1,
    mot_clef_json,
    ponctuation_json,
    valeur_numerique_json,
};

class Symbole_json{
  private:
    Nature_grammaticale_json m_nature_json;
    string m_valeur_json;
    int m_line_index_json;

  public:
    Symbole_json(Nature_grammaticale_json nature, string valeur, int line_index);
    ~Symbole_json();

    int get_line_index();
    string get_valeur();
    Nature_grammaticale_json get_nature();
};

#endif
