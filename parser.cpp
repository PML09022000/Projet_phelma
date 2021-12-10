#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdbool.h>

#include "symbole.h"
#include "Noeud.h"

using namespace std;

static bool parser_decoupage(vector<Symbole> &symbole_vector);
static vector<Noeud> parser_structure(vector<Symbole> &symbole_vector);

void parser(vector<Symbole> &symbole_vector){

    bool decoupage_ok = parser_decoupage(symbole_vector); // Le Parser_Decoupage recupere un vecteur de symboles
                                                          // On doit verifier l'ordre
                                                          // On parcoure ce vecteur pour verifier l'ordre des symboles

    for(std::vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end();) // suppression des symboles de nature ponctuation
    {
      if((*it).get_nature() == ponctuation){
        it = symbole_vector.erase(it);
      }
      else{
        ++it;
      }
    }

    vector<Noeud> noeud_vector = parser_structure(symbole_vector);

  }

vector<Noeud> parser_structure(vector<Symbole> &symbole_vector){
    vector<Noeud> noeud_vector;
    vector<string> nom_noeud_vector;
    for(std::vector<Symbole>::iterator it1 = symbole_vector.begin(); it1 != symbole_vector.end(); ++it1){
      if((*it1).get_nature() == identifiant){
        string current_identifiant = (*it1).get_valeur();
        bool existant = false;
        for(std::vector<string>::iterator it2 = nom_noeud_vector.begin(); it2 != nom_noeud_vector.end(); ++it2){
          if((*it2) == current_identifiant){
            existant = true;
          }else{

          }
        }
        if(existant == false){
          nom_noeud_vector.push_back(current_identifiant);
          Noeud new_noeud();
        }else{
          cout << "nom deja trouve : " << current_identifiant << endl;
          if((*(it1+3)).get_nature() != mot_clef){
            cout << "OK" << endl;
          }else{
            cout << "ERROR" << endl;
          }
        }
      }else{

      }
    }
    return noeud_vector;
}




bool parser_decoupage(vector<Symbole> &symbole_vector){
  int count= 0;
  // Compteur qui va etre à 0 si pas d'erreurs
  // Valeur de compteur differente de 0 si'il y a des erreurs
  int line_index_error=0;
  // Ligne ou on constate l'erreur


  for(std::vector<Symbole>::iterator it = (symbole_vector.begin()+3); it != (symbole_vector.end()-2); ++it)
  {
  //Je ne parcoure pas les 2 dernieres symboles parce que je vais verifier appart que c'est bien ; et }

  //       Chaque *it pointe sur un symbole
  //       //Identifiant doit etre suivie de ponctuation [, ou ;  ou operateur -

       if( (*it).get_nature()==identifiant )
        {
          if( (*(it+1)).get_valeur()!="[" && (*(it+1)).get_valeur()!=";" && (*(it+1)).get_valeur()!= "-")
          {
            count++;
            line_index_error= (*it).get_line_index();
            cout << "Error found on line:  " <<line_index_error<<'\n';
          }
        }

  //  //      "[" doit etre suivi de identifiant, probleme de ] à gerer
  else if( (*it).get_valeur()=="[" )
         {
           if( (*(it+1)).get_nature()!= mot_clef || (*(it-1)).get_nature()!= identifiant )
           {
             count++;
             line_index_error= (*it).get_line_index();
             cout << "Error found on line:  " <<line_index_error<<'\n';
           }
          }
  //
  // //      mot clef label  doit etre suivi de =
  //
        else if( (*it).get_valeur()== "label" )
          {
            if( (*(it+1)).get_valeur()!= "=" )
            {
              count++;
              line_index_error= (*it).get_line_index();
              cout << "Error found on line:  " <<line_index_error<<'\n';
            }
           }
  //      =  est suivi de "

      else  if( (*it).get_valeur()== "=" )
          {
            if( ((*(it+1)).get_valeur()[0])!= '"' )
            {
              count++;
              line_index_error= (*it).get_line_index();
              cout << "Error found on line:  " <<line_index_error<<'\n';
            }
           }
  //
  //
  // //      "  est suivi de mot_clef
  //
           else if( (*it).get_valeur()[0]=='"' )
             {
               if( (*(it+1)).get_nature()== mot_clef )
               { // Verification du couple ""
                    if( (*(it+2)).get_valeur()[0]!= '"'  )
                    {
                      count++;
                      line_index_error= (*it).get_line_index();
                      cout << "Error found on line:  " <<line_index_error<<'\n';
                    }
                }
              else if ( (*(it+1)).get_valeur()!= "]" )
                {
                  count++;
                  line_index_error= (*it).get_line_index();
                  cout << "Error found on line:  " <<line_index_error<<'\n';
                }
              }

  //      ]  est suivi de ';'
          else if( (*it).get_valeur()=="]" )
              {
                if( (*(it+1)).get_valeur()!= ";" )
                    {
                      count++;
                      line_index_error= (*it).get_line_index();
                      cout << "Error found on line:  " <<line_index_error<<'\n';
                    }
               }
  //      ; est suivi de identifiant
        else if( (*it).get_valeur()==";" )
           {
              if( (*(it+1)).get_nature()!=identifiant )
                  {
                    count++;
                    line_index_error= (*it).get_line_index();
                    cout << "Error found on line:  " <<line_index_error<<'\n';
                  }
             }

  //      - est suivi de >

        else if( (*it).get_valeur()=="-" )
                {
                   if( (*(it+1)).get_valeur()!= ">" )
                       {
                         count++;
                         line_index_error= (*it).get_line_index();
                         cout << "Error found on line:  " <<line_index_error<<'\n';
                       }
                  }


  }

  //  Verification des premieres et dernieres symboles
  //  premier symbole doit etre digraph
  if(symbole_vector[0].get_valeur()!= "digraph")
  {
    count++;

    cout << "Error found on line:  " << symbole_vector[0].get_line_index()<<'\n';
  }
  // deuxieme symbole doit etre identifiant
  if(symbole_vector[1].get_nature()!= identifiant)
        {
          count++;
          cout << "Error found on line:  " << symbole_vector[1].get_line_index()<<'\n';
        }

  //  troisieme symbole doit etre {
  if(symbole_vector[2].get_valeur()!= "{")
  {
  count++;
  cout << "Error found on line:  " << symbole_vector[2].get_line_index()<<'\n';
  }

  //  Dernier symbole doit etre {
  // Recuperation du dernier symbole de notre symbole vecteur

  //cout<<(*((symbole_vector.end()-1))).get_valeur()<<endl;

  if((*((symbole_vector.end()-1))).get_valeur()!= "}")
  {
  count++;
  cout << "Error found on line:  " << (*((symbole_vector.end()-1))).get_line_index()<<'\n';
  }

  //  Avant dernier symbole doit etre ;

  if((*((symbole_vector.end()-2))).get_valeur()!= ";")
  {
  count++;
  cout << "Error found on line:  " << (*((symbole_vector.end()-2))).get_line_index()<<'\n';
  }

  // Affichage des erreurs et des numeros de lignes

  if(count==0) {
  cout << "No errors found" << '\n';
  }
  else {
  cout << "Nb errors " << count<<'\n';
  }
}
