#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdbool.h>

#include "symbole.h"
#include "Noeud.h"
#include "parser.h"
using namespace std;

enum CREATE_AND_COMPLETE_NOEUD_FSM_STATES{
  IS_NEW,
    NEW_IDENTIFIANT,
      NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR,
    OLD_IDENTIFIANT,
      CHECK_NOEUD,
      ADD_LINK,
  FINISHED,
};

static bool parser_decoupage(vector<Symbole> &symbole_vector);
static map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector);

static bool is_new(string current_identifiant, map<string, Noeud> noeud_map);
static bool is_it_a_declaration(Nature_grammaticale n);
static Noeud create_a_noeud(string name, string type);


map<string,Noeud> parser(vector<Symbole> &symbole_vector){

    bool decoupage_ok = parser_decoupage(symbole_vector); // Le Parser_Decoupage recupere un vecteur de symboles
                                                          // On doit verifier l'ordre
                                                          // On parcoure ce vecteur pour verifier l'ordre des symboles

    // for(std::vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end();) // suppression des symboles de nature ponctuation
    // {
    //   if((*it).get_nature() == ponctuation){
    //     it = symbole_vector.erase(it);
    //   }
    //   else{
    //     ++it;
    //   }
    // }

    map<string, Noeud>  noeud_vector = parser_structure(symbole_vector);

    for(map<string, Noeud>::iterator it = noeud_vector.begin(); it != noeud_vector.end(); ++it) {
      Noeud noeud = it->second;
      cout << "Nom : " << noeud.get_nom() << "\t\t\tType : " << noeud.get_type() << "\t\t\tNb_input : " << noeud.get_nb_inout()<< "\t\t\tLink : ";
      noeud.print_link();
      cout << endl;
    }

    /* regarder l'identifiant a été répertorier
      si oui alors regarder son origine
      si non regarder si la structure de la ligne correspond à une déclaration de variable ==> appel de fonction
        si tout est OK création d'un noeud avec comme nom la valeur de l'identifiant, comme type la valeur du mot clef situé à 3 symboles, nb input dépend du mot clef
    */
    return noeud_vector;
  }

map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector){

    map<string, Noeud> noeud_map;
    std::map<string,Noeud>::iterator it;

    for(std::vector<Symbole>::iterator it1 = symbole_vector.begin(); it1 != symbole_vector.end(); ++it1){
      if((*it1).get_nature() == identifiant){
        CREATE_AND_COMPLETE_NOEUD_FSM_STATES next_state = IS_NEW;
        while (next_state != FINISHED){

            switch (next_state){
              case IS_NEW :
                next_state = (is_new((*it1).get_valeur(), noeud_map) == true) ? NEW_IDENTIFIANT : OLD_IDENTIFIANT;
                break;

              case NEW_IDENTIFIANT :
                next_state = (is_it_a_declaration((*(it1+5)).get_nature()) == true) ? NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR : FINISHED;
              break;

              case NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR :
                noeud_map.insert (std::pair<string, Noeud>((*it1).get_valeur(),create_a_noeud((*it1).get_valeur(),(*(it1+5)).get_valeur())) );
                next_state = FINISHED;
                break;

              case OLD_IDENTIFIANT :
                cout << (*it1).get_valeur() <<endl;
                next_state = (is_it_a_declaration((*(it1+5)).get_nature()) == true) ? FINISHED : ADD_LINK;
              break;
              case ADD_LINK :
                it = noeud_map.find((*it1).get_valeur());
                //cout << "TYPE : "<< (it->second).get_type()<< endl;
                switch( (it->second).get_type() ){

                  case INPUT :
                  //cout << "ici INPUT"<< (*(it1-3)).get_valeur() << endl;
                  next_state = ((*(it1-1)).get_valeur() == ";") ? FINISHED : FINISHED;
                  break;

                  case OUTPUT :
                  (it->second).add_link_to_previous_noeud((*(it1-3)).get_valeur());
                  //cout << "ici OUTPUT"<< (*(it1-3)).get_valeur() << endl;
                  next_state = FINISHED;
                  break;

                  default :
                  if((*(it1-1)).get_valeur() == ">" && (*(it1-2)).get_valeur() == "-"){
                    (it->second).add_link_to_previous_noeud((*(it1-3)).get_valeur());
                  }else{
                  }
                  next_state = FINISHED;

                  break;

                }
              break;


              case FINISHED :

              break;
              default :
              break;
            }

          }
        }else{
        }
      }
    return noeud_map;
}


bool is_new(string current_identifiant, map<string, Noeud> noeud_map){
  std::map<string,Noeud>::iterator it = noeud_map.find(current_identifiant);
  if (it != noeud_map.end())
    return false;
  else
    return true;
}

bool is_it_a_declaration(Nature_grammaticale n){
  return (n == mot_clef) ? true:false;
}


Noeud create_a_noeud(string str_name, string str_type){
  if(str_type == "INPUT"){
    Noeud new_noeud(str_name, INPUT, 1);
    return new_noeud;
  }
  if(str_type == "OUTPUT"){
    Noeud new_noeud(str_name, OUTPUT, 1);
    return new_noeud;
  }
  if(str_type == "AND2"){
    Noeud new_noeud(str_name, AND2, 2);
    return new_noeud;
  }
  if(str_type == "XOR2"){
    Noeud new_noeud(str_name, XOR2, 2);
    return new_noeud;
  }else{
    Noeud default_n(str_name, OTHER, 0);
    return default_n;
  }
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
  //       //Identifiant doit etre suivie de ponctuation [, ou   ou operateur -


       if( (*it).get_nature()==identifiant )
        {

          if( (*(it+1)).get_valeur()!="["  && (*(it+1)).get_valeur()!=";" )
          //Identifiant doit etre suivie par [ ou  ;
          {
            if ( (*(it+1)).get_valeur()== "-")
             // sinon suivie par -
            {
              // on regarde par quoi il est precedé
                if ( (*(it-1)).get_valeur()==">" && (*(it+2)).get_valeur()== ">" && (*(it+3)).get_nature()!= identifiant)
                {
                  count++;
                  line_index_error= (*it).get_line_index();
                  cout << "Error found on line:  " <<line_index_error<<'\n';

                  }
              }

              else
              {
                count++;
                line_index_error= (*it).get_line_index();
                cout << "Error found on line:  " <<line_index_error<<'\n';
              }

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

    //      > est suivi de identifiant
          else if( (*it).get_valeur()==">" )
                                {
                                   if( (*(it+1)).get_nature()!= identifiant )
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
