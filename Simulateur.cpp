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


  // On lit chaque noeud
  // Si le type c'est input                val logique get.valeur== 0  ou 1
  // Si le type est un output              val logique inconnue get.valeur==2
  // S'il s'agit d'un gate                val logique inconnue get.valeur==2







  // for(std::vector<Noeud>::iterator it = Noeud_vector.end(); it != Noeud_vector.begin(); it--)
  // {
  //    if ((*it).get_type()=="OUTPUT")
  //    {
  //      Noeud* pointeur= *it;
  //      while ((*pointeur).get_valeur()==2)
  //         *pointeur= (*pointeur).get_adresse_pointeur();
  //
  //
  //    }
