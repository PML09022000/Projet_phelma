#ifndef _NOEUD_H_
#define _NOEUD_H_

#include <iostream>
#include <vector>

using namespace std;

enum TYPE_enum{
  TITRE = 0,
  INPUT,
  OUTPUT,
  NOT,
  AND2,
  XOR2,
  OTHER,
};

class Noeud {

  private:
    string m_nom;
    TYPE_enum m_type;
    int m_nb_inout;
    bool m_valeur;
    vector<string> m_noeud_noms_pre; //vecteur de Noeuds avec les adresses sur les quelles il pointe

  public:
    // Constructeur
    Noeud(string nom, TYPE_enum type,int nb_inout);
    //Destructeur
    ~Noeud();

    // Accesseur
    string get_nom() const;
    TYPE_enum get_type() const;
    bool get_valeur() const;
    int get_nb_inout() const;
    void print_link() ;

    vector<string> get_links() const;


    //
    void set_nom(string name);
    void set_logic_state (bool valeur);
    void add_link_to_previous_noeud (string m_nom);



};
#endif
