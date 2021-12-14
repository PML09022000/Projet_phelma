#ifndef _STIMULUS_H_
#define _STIMULUS_H_

#include <string>
#include <vector>

using namespace std;


class Stimulus{
  private:
    string m_nom;
    vector<int> m_valeur_stimulus;

  public:
    Stimulus(string nom);
    ~Stimulus();

    string get_nom();
    vector<int> get_valeur_stimulus();

    void add_valeur_stimulus(int sti);
};

#endif
