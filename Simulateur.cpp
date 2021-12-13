// Simulateur

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdbool.h>
#include <map>

#include "Simulateur.h"
#include "Noeud.h"

using namespace std;

int resultat Simulateur(map<string, Noeud>  noeud_vector)
{


//   // Cette fonction recupere un map de Noeuds par le parser et renvoie le resultat de la simulation

//   // On lit chaque noeud
//   // If get_type = input               val logique get.valeur()== 0  ou 1
//   // If get_type = output              val logique inconnue get.valeur()==2
//   // If get_type = other               val logique inconnue get.valeur()==2


std::map<string,Noeud>::iterator it; // it qui va parcourir la map

for(map<string, Noeud>::iterator it = noeud_vector.begin(); it != noeud_vector.end(); ++it) {

  Noeud noeud = it->second;  // Dans la map: first c'est l'identifiant du noeud, second c'est le noeud

  if ( noeud.get_type()==OUTPUT && noeud.get_valeur()==2) {
    // Si on ne connait pas la val logique de l'output, il faudrait la calculer
  // On parcoure le vecteur des noms des precedents et on cherche chacun dans la map

    for(std::vector<Noeud>::iterator it = (noeud.get_links()).begin(); it != (noeud.get_links()).end(); ++it)
    {
      //On recupere les dependances
      // chaque it pointe sur un string

      im = noeud_map.find((*it);
      //
      for(map<string, Noeud>::iterator im = noeud_vector.begin(); im != noeud_vector.end(); ++im) {
        // On reparcoure la map pour chercher

        Noeud noeud = it->second;  // Dans la map: first c'est l'identifiant du noeud, second c'est le noeud




    }



std::map<string,Noeud>::iterator it = noeud_map.find(current_identifiant);
if (it != noeud_map.end())
  return false;
else
  return true;
}

//   // Ensuite on recupere les identifiants des noeuds qui le precedent   get_link()
