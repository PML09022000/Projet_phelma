#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdbool.h>
#include <stdlib.h>

#include "symbole.h"
#include "Noeud.h"
#include "parser.h"
using namespace std;

enum CREATE_AND_COMPLETE_NOEUD_FSM_STATES{
  IS_NEW,
    IS_TITLE,
    NEW_IDENTIFIANT,
      NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR,
      ERROR_VARIABLE_UNDECLARED,
    OLD_IDENTIFIANT,
      ADD_LINK,
      ERROR_VARIABLE_LINKS_G,
      ERROR_VARIABLE_LINKS_INPUT,
      ERROR_VARIABLE_LINKS_OUTPUT,

  FINISHED,
};

static bool parser_decoupage(vector<Symbole> &symbole_vector);
static map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector);

static bool is_new(string current_identifiant, map<string, Noeud> noeud_map){
  std::map<string,Noeud>::iterator it = noeud_map.find(current_identifiant);
  if (it != noeud_map.end())
    return false;
  else
    return true;
}

static bool is_it_key_word(Nature_grammaticale n){
  return (n == mot_clef) ? true:false;
}

static bool is_it_a_declaration(Nature_grammaticale n){
  return is_it_key_word(n);
}

static bool is_it_title(Nature_grammaticale n){
  return is_it_key_word(n);
}

static bool is_link_to_input(Nature_grammaticale n_moins1, Nature_grammaticale n_plus1){
  if(n_moins1 == ponctuation && n_plus1 == operateur){
    return true;
  }else{
    return false;
  }
}

static bool is_link_to_output(Nature_grammaticale n_moins1, Nature_grammaticale n_plus1){
  if(n_moins1 == operateur && n_plus1 == ponctuation){
    return true;
  }else{
    return false;
  }
}

static bool is_there_a_link(Nature_grammaticale n_moins1,Nature_grammaticale n_plus1){
  bool result = is_link_to_input(n_moins1, n_plus1);
  result |= is_link_to_output(n_moins1, n_plus1);
  if(n_moins1 == operateur && n_plus1 == operateur){
    result = true;
  }else{}
  return result;
}


static Noeud create_a_noeud(string str_name, string str_type){
  if(str_type == "INPUT"){
    Noeud new_noeud(str_name, INPUT, 0);
    return new_noeud;
  }
  if(str_type == "OUTPUT"){
    Noeud new_noeud(str_name, OUTPUT, 1);
    return new_noeud;
  }
  if(str_type == "AND2"){
    Noeud new_noeud(str_name, ANDX, 2);
    return new_noeud;
  }
  if(str_type == "XOR2"){
    Noeud new_noeud(str_name, XORX, 2);
    return new_noeud;
  }
  if(str_type == "XOR3"){
    Noeud new_noeud(str_name, XORX, 3);
    return new_noeud;
  }
  else{
    Noeud default_n(str_name, OTHER, 0);
    return default_n;
  }
}


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

    // for(map<string, Noeud>::iterator it = noeud_vector.begin(); it != noeud_vector.end(); ++it) {
    //   Noeud noeud = it->second;
    //   cout << "Nom : " << noeud.get_nom() << "\t\t\tType : " << noeud.get_type() << "\t\t\tNb_input : " << noeud.get_nb_inout()<< "\t\t\tLink : ";
    //   noeud.print_link();
    //   cout << endl;
    // }

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
    int cpt_error = 0;

    for(std::vector<Symbole>::iterator it1 = symbole_vector.begin(); it1 != symbole_vector.end(); ++it1){
      if((*it1).get_nature() == identifiant){
        CREATE_AND_COMPLETE_NOEUD_FSM_STATES next_state = IS_NEW;
        while (next_state != FINISHED){

            switch (next_state){
              case IS_NEW :
                next_state = (is_new((*it1).get_valeur(), noeud_map) == true) ? IS_TITLE : OLD_IDENTIFIANT;
                break;

              case IS_TITLE :
                next_state = (is_it_title((*(it1-1)).get_nature()) == true) ? FINISHED : NEW_IDENTIFIANT;
                break;

              case NEW_IDENTIFIANT :
                next_state = (is_it_a_declaration((*(it1+5)).get_nature()) == true) ? NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR : ERROR_VARIABLE_UNDECLARED;
              break;

              case NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR :
                noeud_map.insert (std::pair<string, Noeud>((*it1).get_valeur(),create_a_noeud((*it1).get_valeur(),(*(it1+5)).get_valeur())) );
                next_state = FINISHED;
                break;

              case OLD_IDENTIFIANT :
                next_state = (is_there_a_link( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ) ? ADD_LINK : ERROR_VARIABLE_LINKS_G;
              break;

              case ADD_LINK :
                it = noeud_map.find((*it1).get_valeur());
                switch( (it->second).get_type() ){

                  case INPUT :
                    next_state = (is_link_to_input( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ) ? FINISHED : ERROR_VARIABLE_LINKS_INPUT;
                  break;

                  case OUTPUT :
                    if( is_link_to_output( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ){
                      (it->second).add_link_to_previous_noeud((*(it1-3)).get_valeur());
                      next_state = FINISHED;
                    }else{
                      next_state = ERROR_VARIABLE_LINKS_OUTPUT;
                    }
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

              case ERROR_VARIABLE_UNDECLARED :
                cpt_error ++;
                cout << "Error parsing, " << (*it1).get_valeur() << " must be declared first" << endl;
                next_state = FINISHED;
              break;

              case ERROR_VARIABLE_LINKS_G :
                cpt_error ++;
                cout << "Error parsing, there si no good links for " << (*it1).get_valeur() << "at line " << (*it1).get_line_index() << endl;
                next_state = FINISHED;
              break;

              case ERROR_VARIABLE_LINKS_INPUT :
                cpt_error ++;
                cout << "Error parsing, Missing '->' after INPUT " << (*it1).get_valeur() << "at line " << (*it1).get_line_index() << endl;
                next_state = FINISHED;
              break;

              case ERROR_VARIABLE_LINKS_OUTPUT :
                cpt_error ++;
                cout << "Error parsing, Missing '->' after INPUT " << (*it1).get_valeur() << "at line " << (*it1).get_line_index() << endl;
                next_state = FINISHED;
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
      // Check Nb_link OK With nb get_nb_inout
      for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it) {
        if((it->second).get_nb_inout() != ( (it->second).get_links() ).size() ){
          cpt_error ++;
          cout << "Error parsing, " << (it->second).get_nom() << " should have " << (it->second).get_nb_inout() << " links but have " << ( (it->second).get_links() ).size() << endl;
        }else{}
      }
      if(cpt_error == 0){
        return noeud_map;
      }else{
        cout << "Nombre total d'erreurs : " << cpt_error << endl;
        cout << "Prog killed in parser.cpp"<< endl<< endl;
        exit(-1);
      }

}


bool parser_decoupage(vector<Symbole> &symbole_vector)
{

//Methode 1

//   int count=0;
//    int line_index_error=0;
//
// std::vector<Symbole>::iterator it = symbole_vector.begin();
// // it est un iterateur qui pointe sur chaque symbole du vecteur
//
// while(it!= symbole_vector.end()){
//
//      VERIFICATION_DECOUPAGE_FSM_STATES next_state = S1;
//
//
//
//
// while (next_state != NULL_STATE){
//
//       switch (next_state){
//         /////////////////////
//           case S1:
//           // On verifie que le premier mot du vecteur est bien digraph, sinon erreur
//             if((*it).get_valeur()!= "digraph")
//             {
//               count++;
//               cout << "Error found on line:  " << symbole_vector[0].get_line_index()<<'\n';}
//                it++;
//                next_state = S2;
//
//             case S2 :
//
//                 // On verifie que ce qui suit est bien identifiant, sinon erreur
//
//                  if( (*it).get_nature()!=identifiant )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                 next_state =S3;
//                 break;
//
//         /////////////////////
//             case S3 :
//             //ce qui suit l'identifiant doit etre un {, sinon erreur
//                    if( (*it).get_valeur()!= "{" )
//                    {
//                      count++;
//                          line_index_error= (*it).get_line_index();
//                                 cout << "Error found on line:  " <<line_index_error<<'\n';
//                    }
//                    next_state = ID_S4;
//                    it++;
//                     break;
//
//             case ID_S4:
//             // ce qui suit { doit etre un identifiant, sinon erreur
//              if( (*it).get_nature()!=identifiant )
//              {
//                count++;
//                    line_index_error= (*it).get_line_index();
//                           cout << "Error found on line:  " <<line_index_error<<'\n';
//              }
//              it++;
//              next_state = S5;
//             break;
//
//             case S5: // plusieurs possibilités à gerer
//               // Identifiant doit etre suivi de [ - ou ;, sinon erreur
//               if( (*it).get_valeur()=="["  || (*it).get_valeur()=="-" || (*it).get_valeur()!=";" )
//                    {
//                      if ( (*it).get_valeur()=="[" )
//                       {
//                         next_state=S6;
//                       }
//
//                       else if( (*it).get_valeur()=="-" )
//                       {
//                         next_state=S13;
//                       }
//                       else // if( (*it).get_valeur()==";" )
//                       {
//                         next_state=ID_S4;
//                       }
//                    }
//               else
//                {cout<<"Fin de verification "<< endl;
//
//                             break;
//                  count++;
//                      line_index_error= (*it).get_line_index();
//                             cout << "Error found on line:  " <<line_index_error<<'\n';
//                   next_state=WAIT;
//                }
//                     it++;
//                     break;
//
//             case S6:
//
//               if( (*it).get_valeur()!="label" )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                 next_state= S7;
//                   break;
//
//             case S7:
//               if( (*it).get_valeur()!="=" )
//                      {
//                        count++;
//                            line_index_error= (*it).get_line_index();
//                                   cout << "Error found on line:  " <<line_index_error<<'\n';
//                      }
//                       it++;
//                        next_state= S8;
//                       break;
//
//             case S8:
//
//               if(  ((*it).get_valeur()[0])!= '"' )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S9;
//                  break;
//
//             case S9:
//
//               if(  (*it).get_nature()!= mot_clef || (*it).get_valeur()== "label" || (*it).get_valeur()== "digraph")
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S10;
//                  break;
//
//             case S10: //
//
//               if(  ((*it).get_valeur()[0])!= '"' )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S11;
//                  break;
//
//             case S11: //
//
//               if(  (*it).get_valeur()!= "]"  )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S12;
//                  break;
//
//             case S12: // si pas de ; erreur
//
//                     if(  ((*it).get_valeur())!= ";" )
//                          {
//                            count++;
//                                line_index_error= (*it).get_line_index();
//                                       cout << "Error found on line:  " <<line_index_error<<'\n';
//                          }
//
//                       it++;
//                       next_state= S16;// ; suivie d'identifiant ou de }
//                       break;
//
//             case S13:
//                     if( (*it).get_valeur()!=">" )
//                    {
//                      count++;
//                          line_index_error= (*it).get_line_index();
//                                 cout << "Error found on line:  " <<line_index_error<<'\n';
//                    }
//
//                   it++;
//                   next_state=S14;
//                   break;
//
//             case S14:
//                       if( (*it).get_nature()!=identifiant )
//                      {
//                        count++;
//                            line_index_error= (*it).get_line_index();
//                                   cout << "Error found on line:  " <<line_index_error<<'\n';
//                      }
//
//                       it++;
//                       next_state=S15;
//                       break;
//
//               case S15:
//               // 2 possibilités à gerer
//                         if( (*it).get_valeur()=="-"  || (*it).get_valeur()==";" )
//                        {
//                          if( (*it).get_valeur()=="-" )
//                               {
//                                 next_state=S13;
//                               }
//
//                         else if( (*it).get_valeur()==";" )
//                              {
//                                next_state=S16;// identifiant ou }
//                              }
//                        }
//                        else
//                             {
//                               count++;
//                                   line_index_error= (*it).get_line_index();
//                                          cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=WAIT;
//                             }
//                       it++;
//                       break;
//
//               case S16:
//                         if( (*it).get_valeur()=="}"  || (*it).get_nature()==identifiant)
//                        {
//                              if( (*it).get_valeur()=="}")
//                                   {
//                                     next_state=NULL_STATE;
//                                   }
//
//                             else if( (*it).get_nature()==identifiant )
//                                  {
//                                    next_state=S5;// identifiant ou }
//                                  }
//                        }
//                        else
//                             {
//                               count++;
//                                   line_index_error= (*it).get_line_index();
//                                          cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=WAIT;
//                             }
//                       it++;
//                       break;
//
//           case WAIT:
//              if( (*it).get_valeur()=="label" )
//                  {
//                    next_state=S7;
//                  }
//              else if( (*it).get_nature()==identifiant )
//                  {
//                    next_state=S5;
//                  }
//              else if( (*it).get_valeur()==">" )
//                  {
//                    next_state=S14;
//                  }
//             else if( (*it).get_valeur()=="}" )
//                      {
//                        next_state=NULL_STATE;
//                      }
//             // else if( (*it).get_valeur()=="=" )
//             //         {
//             //         next_state=S8;
//             //         }
//             // else if( (*it).get_valeur()=="]" )
//             //     {
//             //     next_state=S12;
//             //     }
//             else {
//               next_state= WAIT;
//
//             }
//             it++;
//             break;
//
//             default:   cout << "erreur de FSM " <<'\n';
//               next_state=WAIT;
//               break;
//
//
//
//                 }// fermeture du case
//
//             }// fermeture du while
//           cout<<"Fin de verification "<< endl;
//
//
//           }// fermeture du while

//Methode 2
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
             // Identifiant suivie par -
            {
              // on regarde par quoi il est precedé
              if ( ((*(it-1)).get_valeur()==">" || (*(it-1)).get_valeur()==";") && ((*(it+2)).get_valeur()== ">" ))
                {
                  //pas d'erreur
                  }
              else {
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

  //  //      "[" doit etre suivi de identifiant
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
                    { if(symbole_vector[0].get_valeur()!= "digraph")
            {
              count++;

              cout << "Error found on line:  " << symbole_vector[0].get_line_index()<<'\n';
            }
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
