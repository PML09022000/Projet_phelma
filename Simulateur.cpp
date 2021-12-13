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


void fonction_recursive(Noeud &noeud, map<string, Noeud> &noeud_map){

  std::map<string,Noeud>::iterator it_map;
  vector<string> dependances = noeud.get_links();
  static vector<int> tab_data_operation;
  tab_data_operation.clear();

  for(std::vector<string>::iterator it = dependances.begin(); it != dependances.end(); ++it){

    it_map = noeud_map.find(*it);

    if(( (it_map->second).get_valeur() ) > 1){
      fonction_recursive((it_map->second), noeud_map);
    }else{
      tab_data_operation.push_back((it_map->second).get_valeur( ));
    }

    switch ( (it_map->second).get_type() ) {
      case AND2:
        (it_map->second).set_logic_state(tab_data_operation[0] & tab_data_operation[1]);
        tab_data_operation.clear();
        tab_data_operation.push_back((it_map->second).get_valeur( ));
        cout << "AND2 result : " <<(it_map->second).get_valeur( ) << endl;
        break;

      case XOR2:
        (it_map->second).set_logic_state(tab_data_operation[0] ^ tab_data_operation[1]);
        tab_data_operation.clear();
        tab_data_operation.push_back((it_map->second).get_valeur( ));
        cout << "XOR2 result : " <<(it_map->second).get_valeur( ) << endl;
        break;

      default:
        break;
    }
  }
  noeud.set_logic_state(tab_data_operation[0]);
}

int Simulateur(map<string, Noeud> noeud_map)
{
  for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it) {
    if((it->second).get_type() == INPUT){
      int boool = 0;
      cout << "Valeur Input" << endl;
      cin >> boool;
      (it->second).set_logic_state(boool);
    }else{}
  }

  for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it) {
    if((it->second).get_type() == OUTPUT){
      fonction_recursive((it->second), noeud_map);
      cout << "OUTPUT = " << (it->second).get_valeur() << endl;
    }else{}
  }
  return 0;

//  it = static_noeud_map.find();
//
//
// //   // Cette fonction recupere un map de Noeuds par le parser et renvoie le resultat de la simulation
//
// //   // On lit chaque noeud
// //   // If get_type = input               val logique get.valeur()== 0  ou 1
// //   // If get_type = output              val logique inconnue get.valeur()==2
// //   // If get_type = other               val logique inconnue get.valeur()==2
//
//
// std::map<string,Noeud>::iterator it; // it qui va parcourir la map
//
// for(map<string, Noeud>::iterator it = noeud_vector.begin(); it != noeud_vector.end(); ++it) {
//
//   Noeud noeud = it->second;  // Dans la map: first c'est l'identifiant du noeud, second c'est le noeud
//
//   if ( noeud.get_type()==OUTPUT && noeud.get_valeur()==2) {
//     // Si on ne connait pas la val logique de l'output, il faudrait la calculer
//   // On parcoure le vecteur des noms des precedents et on cherche chacun dans la map
//
//     for(std::vector<Noeud>::iterator it = (noeud.get_links()).begin(); it != (noeud.get_links()).end(); ++it)
//     {
//       //On recupere les dependances
//       // chaque it pointe sur un string
//
//       im = noeud_map.find((*it);
//       //
//       for(map<string, Noeud>::iterator im = noeud_vector.begin(); im != noeud_vector.end(); ++im) {
//         // On reparcoure la map pour chercher
//
//         Noeud noeud = it->second;  // Dans la map: first c'est l'identifiant du noeud, second c'est le noeud
//
//
//

    }



// std::map<string,Noeud>::iterator it = noeud_map.find(current_identifiant);
// if (it != noeud_map.end())
//   return false;
// else
//   return true;
// }

//   // Ensuite on recupere les identifiants des noeuds qui le precedent   get_link()
