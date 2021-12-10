// Simulateur

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "Simulateur.h"
#include "Noeud.h"

using namespace std;

int resultat Simulateur(vector<Noeud> &Noeud_vector)
{
  // Cette fonction recupere un vecteur de Noeuds par le parser et renvoie le resultat de la simulation

  // Un iterateur va recuperer l'info de chaque Noeud du vector_Noeud


  // On lit chaque noued
  // Si le type c'est input, on appelle set_logic set_logic_state
  // Si le type est un output, on stocke la valeur dans resultat
  // S'il s'agit d'un gate, on effectue l'operation entre les noeud dans les adresses qui le precedent et on stocke le resultat dans le logic state du Noeud qui le suit



  for(std::vector<Noeud>::iterator it = Noeud_vector.begin(); it != Noeud_vector.end(); ++it)

  {
