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
    int get_stimulus_size();
    int get_valeur_stimulus_at_index(int const index);

    void add_valeur_stimulus(int sti);
};

#endif
