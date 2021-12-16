#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <stdbool.h>
#include <stdlib.h>

#include "symbole.h"
#include "symbole_json.h"
#include "Noeud.h"
#include "parser.h"
#include "parser_dot.h"
#include "parser_json.h"
#include "stimulus.h"

using namespace std;


//
// // Verification decoupage fichier .dot
// static bool parser_decoupage(vector<Symbole> &symbole_vector);
//
// // Verification decoupage fichier .json
// static bool parser_decoupage_json(vector<Symbole_json> &symbole_vector_json);
//
// // Parser de .dot
// static map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector);
//
// // Parser create stimulus  de json
//
// static vector <Stimulus >parser_create_stimulus_vector(vector<Symbole_json> &symbole_vector_json);


// Fonction parser json qui appelle les 2 fct decoupage et create stimulus
vector <Stimulus> parser_json(vector<Symbole_json> &symbole_vector_json)
{
  parser_decoupage_json(symbole_vector_json);
  vector <Stimulus> stimulus_vector= parser_create_stimulus_vector(symbole_vector_json);
  return stimulus_vector;

}


// static bool is_new(string current_identifiant, map<string, Noeud> noeud_map){
//   std::map<string,Noeud>::iterator it = noeud_map.find(current_identifiant);
//   if (it != noeud_map.end())
//     return false;
//   else
//     return true;
// }
//
// static bool is_it_key_word(Nature_grammaticale n){
//   return (n == mot_clef) ? true:false;
// }
//
// static bool is_it_a_declaration(Nature_grammaticale n){
//   return is_it_key_word(n);
// }
//
// static bool is_it_title(Nature_grammaticale n){
//   return is_it_key_word(n);
// }
//
// static bool is_link_to_input(Nature_grammaticale n_moins1, Nature_grammaticale n_plus1){
//   if(n_moins1 == ponctuation && n_plus1 == operateur){
//     return true;
//   }else{
//     return false;
//   }
// }
//
// static bool is_link_to_output(Nature_grammaticale n_moins1, Nature_grammaticale n_plus1){
//   if(n_moins1 == operateur && n_plus1 == ponctuation){
//     return true;
//   }else{
//     return false;
//   }
// }
//
// static bool is_there_a_link(Nature_grammaticale n_moins1,Nature_grammaticale n_plus1){
//   bool result = is_link_to_input(n_moins1, n_plus1);
//   result |= is_link_to_output(n_moins1, n_plus1);
//   if(n_moins1 == operateur && n_plus1 == operateur){
//     result = true;
//   }else{}
//   return result;
// }
//
//
// static Noeud create_a_noeud(string str_name, string str_type){
//   if(str_type == "INPUT"){
//     Noeud new_noeud(str_name, INPUT, 0);
//     return new_noeud;
//   }
//   if(str_type == "OUTPUT"){
//     Noeud new_noeud(str_name, OUTPUT, 1);
//     return new_noeud;
//   }
//   if(str_type == "NOT"){
//     Noeud new_noeud(str_name, NOT, 1);
//     return new_noeud;
//   }
//   if(str_type == "AND2"){
//     Noeud new_noeud(str_name, ANDX, 2);
//     return new_noeud;
//   }
//   if(str_type == "NAND2"){
//     Noeud new_noeud(str_name, NANDX, 2);
//     return new_noeud;
//   }
//   if(str_type == "XNOR2"){
//     Noeud new_noeud(str_name, XNORX, 2);
//     return new_noeud;
//   }
//   if(str_type == "OR2"){
//     Noeud new_noeud(str_name, ORX, 2);
//     return new_noeud;
//   }
//   if(str_type == "NOR2"){
//     Noeud new_noeud(str_name, NORX, 2);
//     return new_noeud;
//   }
//   if(str_type == "XOR2"){
//     Noeud new_noeud(str_name, XORX, 2);
//     return new_noeud;
//   }
//   if(str_type == "XOR3"){
//     Noeud new_noeud(str_name, XORX, 3);
//     return new_noeud;
//   }
//   if(str_type == "MUX2"){
//    Noeud new_noeud(str_name, MUXX, 2+1);
//    return new_noeud;
//  }
//   else{
//     Noeud default_n(str_name, OTHER, 0);
//     return default_n;
//   }
// }


map<string,Noeud> parser_dot(vector<Symbole> &symbole_vector){

    parser_decoupage(symbole_vector); // Le Parser_Decoupage recupere un vecteur de symboles
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

    return noeud_vector;
  }

// map<string, Noeud>  parser_structure(vector<Symbole> &symbole_vector){
//
//     map<string, Noeud> noeud_map;
//     std::map<string,Noeud>::iterator it;
//     int cpt_error = 0;
//
//     for(std::vector<Symbole>::iterator it1 = symbole_vector.begin(); it1 != symbole_vector.end(); ++it1){
//       if((*it1).get_nature() == identifiant){
//         CREATE_AND_COMPLETE_NOEUD_FSM_STATES next_state = IS_NEW;
//         while (next_state != FINISHED){
//
//             switch (next_state){
//               case IS_NEW :
//                 next_state = (is_new((*it1).get_valeur(), noeud_map) == true) ? IS_TITLE : OLD_IDENTIFIANT;
//                 break;
//
//               case IS_TITLE :
//                 next_state = (is_it_title((*(it1-1)).get_nature()) == true) ? FINISHED : NEW_IDENTIFIANT;
//                 break;
//
//               case NEW_IDENTIFIANT :
//                 next_state = (is_it_a_declaration((*(it1+5)).get_nature()) == true) ? NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR : ERROR_VARIABLE_UNDECLARED;
//               break;
//
//               case NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR :
//                 noeud_map.insert (std::pair<string, Noeud>((*it1).get_valeur(),create_a_noeud((*it1).get_valeur(),(*(it1+5)).get_valeur())) );
//                 next_state = NEED_TO_ADD_SPECIAL_LINK_OR_NOT;
//                 break;
//
//               case NEED_TO_ADD_SPECIAL_LINK_OR_NOT :
//                 if( (*(it1+7)).get_valeur() == "sel" && (*(it1+10)).get_nature() == identifiant ){
//                   it = noeud_map.find((*it1).get_valeur());
//                   (it->second).add_link_to_previous_noeud((*(it1+10)).get_valeur());
//                 }else{
//
//                 }
//                 next_state = FINISHED;
//
//                 break;
//
//               case OLD_IDENTIFIANT :
//                 next_state = (is_there_a_link( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ) ? ADD_LINK : ERROR_VARIABLE_LINKS_G;
//                 next_state = (is_there_a_link( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ) ? ADD_LINK : IS_IT_BETWEEN_COTE;
//               break;
//
//               case IS_IT_BETWEEN_COTE:
//                 if( (*(it1-1)).get_nature() == ponctuation && (*(it1+1)).get_nature() == ponctuation){
//                   next_state = FINISHED;
//                 }else{
//                   next_state = ERROR_VARIABLE_LINKS_G;
//                 }
//                 break;
//
//               case ADD_LINK :
//                 it = noeud_map.find((*it1).get_valeur());
//                 switch( (it->second).get_type() ){
//
//                   case INPUT :
//                     next_state = (is_link_to_input( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ) ? FINISHED : ERROR_VARIABLE_LINKS_INPUT;
//                   break;
//
//                   case OUTPUT :
//                     if( is_link_to_output( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ){
//                       (it->second).add_link_to_previous_noeud((*(it1-3)).get_valeur());
//                       next_state = FINISHED;
//                     }else{
//                       next_state = ERROR_VARIABLE_LINKS_OUTPUT;
//                     }
//                     break;
//
//                   default :
//                   if((*(it1-1)).get_valeur() == ">" && (*(it1-2)).get_valeur() == "-"){
//                     (it->second).add_link_to_previous_noeud((*(it1-3)).get_valeur());
//                   }else{
//                   }
//                   next_state = FINISHED;
//
//                   break;
//
//                 }
//               break;
//
//               case ERROR_VARIABLE_UNDECLARED :
//                 cpt_error ++;
//                 cout << "Error parsing, " << (*it1).get_valeur() << " must be declared first" << endl;
//                 next_state = FINISHED;
//               break;
//
//               case ERROR_VARIABLE_LINKS_G :
//                 cpt_error ++;
//                 cout << "Error parsing, there si no good links for " << (*it1).get_valeur() << "at line " << (*it1).get_line_index() << endl;
//                 next_state = FINISHED;
//               break;
//
//               case ERROR_VARIABLE_LINKS_INPUT :
//                 cpt_error ++;
//                 cout << "Error parsing, Missing '->' after INPUT " << (*it1).get_valeur() << "at line " << (*it1).get_line_index() << endl;
//                 next_state = FINISHED;
//               break;
//
//               case ERROR_VARIABLE_LINKS_OUTPUT :
//                 cpt_error ++;
//                 cout << "Error parsing, Missing '->' after INPUT " << (*it1).get_valeur() << "at line " << (*it1).get_line_index() << endl;
//                 next_state = FINISHED;
//               break;
//
//               case FINISHED :
//
//               break;
//               default :
//               break;
//             }
//
//           }
//         }else{
//         }
//       }
//       // Check Nb_link OK With nb get_nb_inout
//       for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it) {
//         if((it->second).get_nb_inout() != ( (it->second).get_links() ).size() ){
//           cpt_error ++;
//           cout << "Error parsing, " << (it->second).get_nom() << " should have " << (it->second).get_nb_inout() << " links but have " << ( (it->second).get_links() ).size() << endl;
//         }else{}
//       }
//       if(cpt_error == 0){
//         return noeud_map;
//       }else{
//         cout << "Nombre total d'erreurs : " << cpt_error << endl;
//         cout << "Prog killed in parser.cpp"<< endl<< endl;
//         exit(-1);
//       }
//
// }


// bool parser_decoupage(vector<Symbole> &symbole_vector)
// {
// //Methode 2
//   int count= 0;
//   // Compteur qui va etre à 0 si pas d'erreurs
//   // Valeur de compteur differente de 0 si'il y a des erreurs
//   int line_index_error=0;
//   // Ligne ou on constate l'erreur
//
//
//   for(std::vector<Symbole>::iterator it = (symbole_vector.begin()+3); it != (symbole_vector.end()-2); ++it)
//   {
//   //Je ne parcoure pas les 2 dernieres symboles parce que je vais verifier appart que c'est bien ; et }
//
//   //       Chaque *it pointe sur un symbole
//   //       //Identifiant doit etre suivie de ponctuation [, ou   ou operateur -
//
//
//       if( (*it).get_nature()==identifiant ){
//           if( (*(it+1)).get_valeur()!="["  && (*(it+1)).get_valeur()!=";" && (*(it+1)).get_valeur()[0]!='"' ){
//           //Identifiant doit etre suivie par [ ou  ;
//
//             if ( (*(it+1)).get_valeur()== "-"){
//              // Identifiant suivie par -
//              // on regarde par quoi il est precedé
//               if ( ((*(it-1)).get_valeur()==">" || (*(it-1)).get_valeur()==";") && ((*(it+2)).get_valeur()== ">" )){
//               //pas d'erreur
//               }
//               else{
//                 count++;
//                 line_index_error= (*it).get_line_index();
//                 cout << "Error found on line:  " <<line_index_error<<'\n';
//                 }
//
//             }
//
//             else{
//                 count++;
//                 line_index_error= (*it).get_line_index();
//                 cout << "Error found on line:  " <<line_index_error<<'\n';
//                 }
//           }
//       }
//
//   //  //      "[" doit etre suivi de identifiant
//     else if( (*it).get_valeur()=="[" )
//          {
//            if( (*(it+1)).get_nature()!= mot_clef || (*(it-1)).get_nature()!= identifiant )
//            {
//              count++;
//              line_index_error= (*it).get_line_index();
//              cout << "Error found on line:  " <<line_index_error<<'\n';
//            }
//           }
//   //
//   // //      mot clef label  doit etre suivi de =
//   //
//         else if( (*it).get_valeur()== "label" )
//           {
//             if( (*(it+1)).get_valeur()!= "=" ){
//               count++;
//               line_index_error= (*it).get_line_index();
//               cout << "Error found on line:  " <<line_index_error<<'\n';
//             }
//            }
//   //      =  est suivi de "
//
//       else  if( (*it).get_valeur()== "=" )
//           {
//             if( ((*(it+1)).get_valeur()[0])!= '"' )
//             {
//               count++;
//               line_index_error= (*it).get_line_index();
//               cout << "Error found on line:  " <<line_index_error<<'\n';
//             }
//            }
//   //
//   //
//   // //      "  est suivi de mot_clef ] ou identifiant dans le cas du mux
//   //
//         else if( (*it).get_valeur()[0]=='"' )
//              {
//                // if( (*(it+1)).get_nature()!= mot_clef ){
//                //   // Verification du couple ""
//                //      // if( (*(it+2)).get_valeur()[0]!= '"'  )
//                //      // {
//                //        // count++;
//                //        // line_index_error= (*it).get_line_index();
//                //        // cout << "Error found on line:  " <<line_index_error<<'\n';
//                //      //}
//                //  }
//
//              if ( (*(it+1)).get_nature()!= mot_clef && (*(it+1)).get_nature()!=identifiant && (*(it+1)).get_valeur()!= "]" )
//                 {
//                   count++;
//                   line_index_error= (*it).get_line_index();
//                   cout << "Error found on line:  " <<line_index_error<<'\n';
//                 }
//               }
//
//   //      ]  est suivi de ';'
//           else if( (*it).get_valeur()=="]" )
//               {
//                 if( (*(it+1)).get_valeur()!= ";" )
//                   {
//                       count++;
//                       line_index_error= (*it).get_line_index();
//                       cout << "Error found on line:  " <<line_index_error<<'\n';
//                     }
//                }
//   //      ; est suivi de identifiant
//         else if( (*it).get_valeur()==";" )
//            {
//               if( (*(it+1)).get_nature()!=identifiant )
//                   {
//                     count++;
//                     line_index_error= (*it).get_line_index();
//                     cout << "Error found on line:  " <<line_index_error<<'\n';
//                   }
//              }
//
//   //      - est suivi de >
//
//         else if( (*it).get_valeur()=="-" )
//                 {
//                    if( (*(it+1)).get_valeur()!= ">" )
//                        {
//                          count++;
//                          line_index_error= (*it).get_line_index();
//                          cout << "Error found on line:  " <<line_index_error<<'\n';
//                        }
//                   }
//
//     //      > est suivi de identifiant
//           else if( (*it).get_valeur()==">" )
//                 {
//                     if( (*(it+1)).get_nature()!= identifiant )
//                     {
//                         count++;
//                         line_index_error= (*it).get_line_index();
//                         cout << "Error found on line:  " <<line_index_error<<'\n';
//                     }
//                 }
//               }
//   //  Verification des premieres et dernieres symboles
//   //  premier symbole doit etre digraph
//             if(symbole_vector[0].get_valeur()!= "digraph")
//             {
//               count++;
//
//               cout << "Error found on line:  " << symbole_vector[0].get_line_index()<<'\n';
//             }
//             // deuxieme symbole doit etre identifiant
//             if(symbole_vector[1].get_nature()!= identifiant)
//                   {
//                     count++;
//                     cout << "Error found on line:  " << symbole_vector[1].get_line_index()<<'\n';
//                   }
//
//             //  troisieme symbole doit etre {
//             if(symbole_vector[2].get_valeur()!= "{")
//             {
//             count++;
//             cout << "Error found on line:  " << symbole_vector[2].get_line_index()<<'\n';
//             }
//
//   //  Dernier symbole doit etre {
//   // Recuperation du dernier symbole de notre symbole vecteur
//
//   //cout<<(*((symbole_vector.end()-1))).get_valeur()<<endl;
//
//               if((*((symbole_vector.end()-1))).get_valeur()!= "}")
//               {
//               count++;
//               cout << "Error found on line:  " << (*((symbole_vector.end()-1))).get_line_index()<<'\n';
//               }
//
//               //  Avant dernier symbole doit etre ;
//
//               if((*((symbole_vector.end()-2))).get_valeur()!= ";")
//               {
//               count++;
//               cout << "Error found on line:  " << (*((symbole_vector.end()-2))).get_line_index()<<'\n';
//               }
//
//   // Affichage des erreurs et des numeros de lignes
//
//         if(count==0) {
//         cout << "No errors found" << '\n';
//
//         }
//         else {
//         cout << "Nb errors " << count<<'\n';
//         exit(-1);
//         }
//
//     }
//
// //Etats de la MAE pour la fonction parser_json qui verifie le decoupage
// enum PARSER_JSON_FSM{
//         START,
//           MOT_CLEF,
//           S1,
//           S2,
//           S3,
//           S4,
//           S5,
//           S6,
//           IDENTIFIANT,
//           S7,
//           S8,
//           TAB_VALEUR,
//           S9,
//           S10,
//           S11,
//         FINISHED_JSON,
//         ERROR,
//       };
//
//
// void parser_decoupage_json(vector<Symbole_json> &symbole_vector_json)
// {
//        int count= 0;
//        // Compteur = 0 si pas d'erreurs
//        // Compteur!= 0 si'il y a des erreurs
//        int line_index_error=0;
//        // Ligne ou on constate l'erreur
//
//        std::vector<Symbole_json>::iterator it = symbole_vector_json.begin();
//        // it est un iterateur qui pointe sur chaque symbole json
//
//       PARSER_JSON_FSM next_state = START;
//
//       while (next_state != FINISHED_JSON){
//
//         switch (next_state){
//
//             case START:
//                  // On verifie que le premier mot du vecteur est bien {, sinon erreur
//                    if((*it).get_valeur()!= "{"){
//                           count++;
//                           cout << "Error found on line:  " << symbole_vector_json[0].get_line_index()<<'\n';
//                           next_state=ERROR;
//                           }
//                    else{
//                           it++;
//                           next_state= MOT_CLEF;
//                     }
//                    break;
//
//             case MOT_CLEF:
//                   // On verifie que ce qui suit est bien mot_clef, sinon erreur
//                     if( (*it).get_nature()== mot_clef_json ){
//                           next_state=S2;
//                     }
//                     else if( (*it).get_valeur()== "}" ){ //{}, cas de ligne vide à gerer
//                           next_state=S10;
//                     }
//                     else{
//                           count++;
//                           line_index_error= (*it).get_line_index();
//                           cout << "Error found on line:  " <<line_index_error<<'\n';
//                           next_state=ERROR;
//                           }
//                       it++;
//                       break;
//
//
//               case S2 :
//                    //ce qui suit  le mot_clef doit etre un :, sinon erreur
//                       if( (*it).get_valeur()!= ":" ){
//                           count++;
//                           line_index_error= (*it).get_line_index();
//                           cout << "Error found on line:  " <<line_index_error<<'\n';
//                           next_state=ERROR;
//                         }
//                       else{
//                           it++;
//                           next_state=S3;
//                         }
//                       break;
//
//               case S3:
//                    // ce qui suit : doit etre un [ ou ' sinon erreur
//                         if( (*it).get_valeur()=="[" ){
//                            next_state=START;
//                             }
//                         else if((*it).get_valeur()=="'" ){
//                            next_state=IDENTIFIANT;
//                             }
//                         else{
//                             count++;
//                             line_index_error= (*it).get_line_index();
//                             cout << "Error found on line:  " <<line_index_error<<'\n';
//                             next_state=ERROR;
//                             }
//                         it++;
//                         break;
//
//               case IDENTIFIANT:
//                         if( (*it).get_nature()!=identifiant_json ){
//                              next_state=ERROR;
//                              count++;
//                              line_index_error= (*it).get_line_index();
//                              cout << "Error found on line:  " <<line_index_error<<'\n';
//                              }
//                         else{
//                              next_state=S4;
//                              }
//                         it++;
//                         break;
//
//               case S4:
//                      if( (*it).get_valeur()!="'" ){
//                              count++;
//                              line_index_error= (*it).get_line_index();
//                              cout << "Error found on line:  " <<line_index_error<<'\n';
//                              next_state=ERROR;
//                              }
//                       else{
//                               next_state=S5;
//                               }
//                       it++;
//                       break;
//
//               case S5:
//                      if( (*it).get_valeur()!="," ){
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=ERROR;
//                               }
//                       else{
//                               next_state=S6;
//                               }
//                       it++;
//                       break;
//
//               case S6:
//                      if  ((*it).get_valeur()!= "wave" ){
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=ERROR;
//                               }
//
//                     else{
//                               next_state=S7;
//                               }
//                     it++;
//                     break;
//
//               case S7:
//                      if(  (*it).get_valeur()!= ":" ){
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=ERROR;
//                               }
//                      else{
//                               next_state=S8;
//                               }
//                      it++;
//                      break;
//
//               case S8:
//                     if  ((*it).get_valeur()!= "'" ){
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=ERROR;
//                               }
//                     else{
//                               next_state=TAB_VALEUR;
//                               }
//
//                     it++;
//                     break;
//
//               case TAB_VALEUR:
//                      if(  (*it).get_valeur()== "0"|| (*it).get_valeur()=="1" || (*it).get_valeur()== "."){
//                               next_state=TAB_VALEUR;
//                               }
//                      else if (  (*it).get_valeur()== "'"){
//                               next_state=S9;
//                               }
//                     else {
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=ERROR;
//                               }
//                     it++;
//                     break;
//
//               case S9:
//
//                       if(  ((*it).get_valeur())== "}" ){
//                               next_state=S10;
//                               }
//
//
//                       else{
//                               next_state=ERROR;
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                             }
//                       it++;
//                       break;
//
//               case S10:
//                       if( (*it).get_valeur()=="," )
//                               {next_state= START;}
//
//                       else if( (*it).get_valeur()=="]" )
//                               {next_state= S11;}
//                       else{
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=ERROR;
//                               }
//
//                       it++;
//                       break;
//
//               case S11:
//                       if( (*it).get_valeur()!="}"){
//                               count++;
//                               line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=ERROR;
//                               }
//
//                       else{ next_state= FINISHED_JSON;}
//
//                       it++;
//                       break;
//
//                 case ERROR:
//                               cout<< " The error is: " <<(*(it-1)).get_valeur()<< endl;
//                               next_state=FINISHED_JSON;
//                               it++;
//                               break;
//
//
//                 case FINISHED_JSON:
//                               //cout<< "Verification finished !! " <<'\n';
//                               break;
//
//                   default:    cout << "Unknown state" <<'\n';
//                               next_state=FINISHED_JSON;
//                               break;
//                        }// fermeture du case
//                  }// fermeture du while
//
//                 if(count==0){
//                   cout<< "No errors found in parsing decoupage.json ! " <<endl;
//                 }
//                 else {
//                   cout<< "Number of errors found in parsing decoupage.json : " <<count<<'\n';
//                   exit(-1);
//                 }
// }
//
// // Etats de la MAE pour la fonction du parser_json qui cree les stimulus
// enum FSM_STATES_CREATE_STIMULUS
//  {
//    IS_NEW_CS,
//    FINISHED_CS,
//    ERROR_CS,
//  };
//
// //Fonction parser pour le fichier json qui crée des objets stimulus
// vector <Stimulus> parser_create_stimulus_vector(vector<Symbole_json> &symbole_vector_json)
// {
//   // Declaration de vecteur vide SIMULUS_VECTOR
//   vector <Stimulus> stimulus_vector;
//
//   FSM_STATES_CREATE_STIMULUS next_state;
//
//   //Suppression des mot_clefs et ponctuations
//   for(std::vector<Symbole_json>::iterator it = symbole_vector_json.begin(); it != symbole_vector_json.end();)
//   {
//     if((*it).get_nature() == ponctuation_json || (*it).get_nature() == mot_clef_json)
//     {
//       it = symbole_vector_json.erase(it); // Pas d'incrementation
//     }
//     else{ ++it; }
//   }
//   // Variable dans la quelle on sauvegarde la derniere valeur de l'input
//   int sauvegarde=0;
//
//   // Declaration de it sur symbole_json à utiliser dans la FSM
//   std::vector<Symbole_json>::iterator it = symbole_vector_json.begin();
//
//     if((*it).get_nature() == identifiant_json){
//       FSM_STATES_CREATE_STIMULUS next_state = IS_NEW_CS;
//     }
//
//     while (next_state != FINISHED_CS ){
//
//           switch (next_state){
//
//             case IS_NEW_CS :
//
//             // Variable sauvegarde initialisé à 0 pour chaque nouveau stimulus
//             sauvegarde=0;
//
//             // Si stimulus_vector est vide => Creation du stimulus
//             if (stimulus_vector.empty()) {
//                 //Creation de stimulus avec un seul attribut: string m_nom;
//                 Stimulus new_stimulus((*it).get_valeur());
//                 cout<<"Creation d'objet stimulus: "<<(*it).get_valeur()<<endl;
//                 // Incrementation du it pour lire les valeurs numeriques
//                 // Identifiant est suivi que de valeurs numeriques
//                 it++;
//
//                 while ((*it).get_nature()==valeur_numerique_json){
//
//                    if( (*it).get_valeur()=="1"){
//                        new_stimulus.add_valeur_stimulus(1);
//                        sauvegarde=1;
//                      }
//
//                    else if( (*it).get_valeur()=="0"){
//                        new_stimulus.add_valeur_stimulus(0);
//                        sauvegarde=0;
//                      }
//                    else{
//                         new_stimulus.add_valeur_stimulus(sauvegarde);
//                      }
//
//                     if( it== symbole_vector_json.end()) {}
//                     else { it++;}
//                   } // closed while
//
//                if( it== symbole_vector_json.end()){
//                         next_state=FINISHED_CS; // fin du vecteur symbole_json
//                         break;}
//
//                else{
//                     stimulus_vector.push_back( new_stimulus);
//                     next_state=IS_NEW_CS;
//                     break;}
//               }
//
//           else{ //stimulus_vector n'est pas vide
//
//             // Verification que le stimulus n'a pas deja ete declare
//               for(std::vector<Stimulus>::iterator it2 = stimulus_vector.begin(); it2 != stimulus_vector.end(); ++it2){
//                // Si deja declaré
//                 if(((*it).get_valeur())==((*it2).get_nom())){
//                     cout<<(*it).get_valeur()<< " a deja été declaré! "<<endl;
//                     next_state = ERROR_CS;
//                     break;
//                   }
//                }
//
//               Stimulus new_stimulus((*it).get_valeur());
//               cout<< "Creation d'objet stimulus: "<<(*it).get_valeur()<<endl;
//               it++;
//                  // On remplit  le vecteur de int
//                   while ((*it).get_nature()==valeur_numerique_json )
//                   {
//                         if( (*it).get_valeur()=="1"){
//                           new_stimulus.add_valeur_stimulus(1);
//                           sauvegarde=1;
//                         }
//                         else if( (*it).get_valeur()=="0"){
//                           new_stimulus.add_valeur_stimulus(0);
//                           sauvegarde=0;
//                         }
//                         else{
//                           new_stimulus.add_valeur_stimulus(sauvegarde);
//                         }
//                         if( it== symbole_vector_json.end()){}
//                         else {  it++;}
//                     }// while closed
//                     // Dernier element du vecteur symbole_json
//                     if( it== symbole_vector_json.end())
//                           {
//                             stimulus_vector.push_back( new_stimulus);
//                             next_state=FINISHED_CS;
//                             break;
//                           }
//                     else{
//                         stimulus_vector.push_back( new_stimulus);
//                         next_state=IS_NEW_CS;
//                         break;
//                       }
//                   } // cas stimulus_vector pas vide OK
//
//
//               case ERROR_CS:
//                 cout<<"ERREUR DE DECLARATION!"<<endl;
//                 next_state= FINISHED_CS;
//                 break;
//
//               case FINISHED_CS:
//                 cout<<"DONE!"<<endl;
//                 break;
//
//                default:
//                  cout<<"ERREUR DE FSM!"<<endl;
//                  next_state= FINISHED_CS;
//                  break;
//               }// case closed
//             }
//           return stimulus_vector;
//         } // Function closed
