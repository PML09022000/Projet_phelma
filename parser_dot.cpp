#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdbool.h>
#include <stdlib.h>

#include "parser_dot.h"

using namespace std;


enum CREATE_AND_COMPLETE_NOEUD_FSM_STATES{
  IS_NEW,
    IS_TITLE,
    NEW_IDENTIFIANT,
      NEW_NOEUD_TO_CREATE_AND_ADD_TO_VECTOR,
      NEED_TO_ADD_SPECIAL_LINK_OR_NOT,
      ERROR_VARIABLE_UNDECLARED,
    OLD_IDENTIFIANT,
      IS_IT_SPECIAL_LINK_OR_NOT,
      ADD_LINK,
      ERROR_VARIABLE_LINKS_G,
      ERROR_VARIABLE_LINKS_INPUT,
      ERROR_VARIABLE_LINKS_OUTPUT,

  FINISHED,
};


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
  if(str_type == "NOT"){
    Noeud new_noeud(str_name, NOT, 1);
    return new_noeud;
  }
  if(str_type == "MUX2"){
    Noeud new_noeud(str_name, MUXX, 2+1);
    return new_noeud;
  }

 string str_type_p1;
 string str_type_p2;
 for(unsigned int i = 0; i <= str_type.length(); i++)
 {
   while((str_type[i] >= 'A' && str_type[i] <= 'Z')){
     str_type_p1.push_back(str_type[i]);
     if (i < str_type.length()){
       i++;
     }
   }
   while((str_type[i] >= '2' && str_type[i] <= '9')){
     str_type_p2.push_back(str_type[i]);
     if (i < str_type.length()){
       i++;
     }
   }
 }
 const char * c = str_type_p2.c_str();
  int nb_input = atoi(c);
  if(str_type_p1 == "AND"){
    Noeud new_noeud(str_name, ANDX, nb_input);
    return new_noeud;
  }
  if(str_type_p1 == "NAND"){
    Noeud new_noeud(str_name, NANDX, nb_input);
    return new_noeud;
  }
  if(str_type_p1 == "XNOR"){
    Noeud new_noeud(str_name, XNORX, nb_input);
    return new_noeud;
  }
  if(str_type_p1 == "OR"){
    Noeud new_noeud(str_name, ORX, nb_input);
    return new_noeud;
  }
  if(str_type_p1 == "NOR"){
    Noeud new_noeud(str_name, NORX, nb_input);
    return new_noeud;
  }
  if(str_type_p1 == "XOR"){
    Noeud new_noeud(str_name, XORX, nb_input);
    return new_noeud;
  }
  else{
    Noeud default_n(str_name, OTHER, 0);
    return default_n;
  }
}


static void loop_recursive_function(Noeud noeud, map<string, Noeud> noeud_map, string noeud_name){
  std::map<string,Noeud>::iterator it_map;
  vector<string> dependances = noeud.get_links();

  for(std::vector<string>::iterator it = dependances.begin(); it != dependances.end(); ++it){
    if(noeud_name == (*it)){
      cout << "parser_dot.cpp, ERROR : loop detected for " << noeud_name << ", EXIT NOW" << endl;
      exit(-1);
    }else{
      it_map = noeud_map.find(*it);
      loop_recursive_function((it_map->second), noeud_map, noeud_name);
    }
  }
}


void parser_decoupage_dot(vector<Symbole> &symbole_vector){

//Methode 2
  int count= 0;
  // Compteur qui va etre à 0 si pas d'erreurs
  // Valeur de compteur differente de 0 si'il y a des erreurs
  int line_index_error=0;
  // Ligne ou on constate l'erreur


  if(symbole_vector[3].get_valeur()== "}")
  {
    cout << "parser_dot.cpp, ERROR : Empty graph!" <<'\n';
    exit(-1);
  }



  for(std::vector<Symbole>::iterator it = (symbole_vector.begin()+3); it != (symbole_vector.end()-2); ++it)
  {
  //Je ne parcoure pas les 2 dernieres symboles parce que je vais verifier appart que c'est bien ; et }

  //       Chaque *it pointe sur un symbole
  //       //Identifiant doit etre suivie de ponctuation [, ou   ou operateur -


      if( (*it).get_nature()==identifiant ){
          if( (*(it+1)).get_valeur()!="["  && (*(it+1)).get_valeur()!=";" && (*(it+1)).get_valeur()[0]!='"' ){
          //Identifiant doit etre suivie par [ ou  ;

            if ( (*(it+1)).get_valeur()== "-"){
             // Identifiant suivie par -
             // on regarde par quoi il est precedé
              if ( ((*(it-1)).get_valeur()==">" || (*(it-1)).get_valeur()==";") && ((*(it+2)).get_valeur()== ">" )){
              //pas d'erreur
              }
              else{
                count++;
                line_index_error= (*it).get_line_index();
                cout << "parser_dot.cpp, ERROR : line:  " <<line_index_error<<'\n';
                }

            }

            else{
                count++;
                line_index_error= (*it).get_line_index();
                cout << "parser_dot.cpp, ERROR : line:  " <<line_index_error<<'\n';
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
             cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
           }
          }
  //
  // //      mot clef label  doit etre suivi de =
  //
        else if( (*it).get_valeur()== "label" )
          {
            if( (*(it+1)).get_valeur()!= "=" ){
              count++;
              line_index_error= (*it).get_line_index();
              cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
            }
           }
  //      =  est suivi de "

      else  if( (*it).get_valeur()== "=" )
          {
            if( ((*(it+1)).get_valeur()[0])!= '"' )
            {
              count++;
              line_index_error= (*it).get_line_index();
              cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
            }
           }
  //
  //
  // //      "  est suivi de mot_clef ] ou identifiant dans le cas du mux
  //
        else if( (*it).get_valeur()[0]=='"' )
             {
               // if( (*(it+1)).get_nature()!= mot_clef ){
               //   // Verification du couple ""
               //      // if( (*(it+2)).get_valeur()[0]!= '"'  )
               //      // {
               //        // count++;
               //        // line_index_error= (*it).get_line_index();
               //        // cout << "Error found on line:  " <<line_index_error<<'\n';
               //      //}
               //  }

             if ( (*(it+1)).get_nature()!= mot_clef && (*(it+1)).get_nature()!=identifiant && (*(it+1)).get_valeur()!= "]" )
                {
                  count++;
                  line_index_error= (*it).get_line_index();
                  cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
                }
              }

  //      ]  est suivi de ';'
          else if( (*it).get_valeur()=="]" )
              {
                if( (*(it+1)).get_valeur()!= ";" )
                  {
                      count++;
                      line_index_error= (*it).get_line_index();
                      cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
                    }
               }
  //      ; est suivi de identifiant
        else if( (*it).get_valeur()==";" )
           {
              if( (*(it+1)).get_nature()!=identifiant )
                  {
                    count++;
                    line_index_error= (*it).get_line_index();
                    cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
                  }
             }

  //      - est suivi de >

        else if( (*it).get_valeur()=="-" )
                {
                   if( (*(it+1)).get_valeur()!= ">" )
                       {
                         count++;
                         line_index_error= (*it).get_line_index();
                         cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
                       }
                  }

    //      > est suivi de identifiant
          else if( (*it).get_valeur()==">" )
                {
                    if( (*(it+1)).get_nature()!= identifiant )
                    {
                        count++;
                        line_index_error= (*it).get_line_index();
                        cout << "parser_dot.cpp, ERROR : line " <<line_index_error<<'\n';
                    }
                }
              }
  //  Verification des premieres et dernieres symboles
  //  premier symbole doit etre digraph
            if(symbole_vector[0].get_valeur()!= "digraph")
            {
              count++;

              cout << "parser_dot.cpp, ERROR : line " << symbole_vector[0].get_line_index()<<'\n';
            }
            // deuxieme symbole doit etre identifiant
            if(symbole_vector[1].get_nature()!= identifiant)
                  {
                    count++;
                    cout << "parser_dot.cpp, ERROR : line " << symbole_vector[1].get_line_index()<<'\n';
                  }

            //  troisieme symbole doit etre {
            if(symbole_vector[2].get_valeur()!= "{")
            {
              count++;
              cout << "parser_dot.cpp, ERROR : line " << symbole_vector[2].get_line_index()<<'\n';
            }

  //  Dernier symbole doit etre {
  // Recuperation du dernier symbole de notre symbole vecteur

  //cout<<(*((symbole_vector.end()-1))).get_valeur()<<endl;

              if((*((symbole_vector.end()-1))).get_valeur()!= "}")
              {
              count++;
              cout << "parser_dot.cpp, ERROR : line " << (*((symbole_vector.end()-1))).get_line_index()<<'\n';
              }

              //  Avant dernier symbole doit etre ;

              if((*((symbole_vector.end()-2))).get_valeur()!= ";")
              {
              count++;
              cout << "parser_dot.cpp, ERROR : line " << (*((symbole_vector.end()-2))).get_line_index()<<'\n';
              }

  // Affichage des erreurs et des numeros de lignes

        if(count==0) {
          //cout << "No errors found in parser_decoupage.dot!" << '\n';
        }
        else {
          cout << "parser_dot.cpp, TOTAL ERRORS BEFORE KILL : " << count<<'\n';
          exit(-1);
        }

}

map<string, Noeud>  parser_nodes_and_links(vector<Symbole> &symbole_vector){

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
                next_state = NEED_TO_ADD_SPECIAL_LINK_OR_NOT;
                break;

              case NEED_TO_ADD_SPECIAL_LINK_OR_NOT :
                if( (*(it1+7)).get_valeur() == "sel" && (*(it1+10)).get_nature() == mot_clef ){
                  it = noeud_map.find((*it1).get_valeur());
                  (it->second).add_link_to_previous_noeud((*(it1+10)).get_valeur());
                }else{

                }
                next_state = FINISHED;

                break;

              // case NEED_TO_ADD_SPECIAL_LINK_OR_NOT :
              //   it = noeud_map.find((*it1).get_valeur());
              //   if( (it->second).get_type( ) == MUXX ){
              //     next_state = GET_SELS_MOINS1;
              //   }else{
              //     next_state = FINISHED;
              //   }
              //
              //   break;
              //
              // case GET_SELS_MOINS1 :
              //   nb_sel_moins1 = round(log2((it->second).get_nb_inout( )) )-1;
              //   if( (*(it1+7)).get_valeur() == "sel" && (*(it1+10)).get_nature() == mot_clef ){
              //     (it->second).add_link_to_previous_noeud((*(it1+10)).get_valeur());
              //   }
              //   for(int i = 1 ; i <= nb_sel_moins1 ; i++){
              //     if((*(it1+7+(5*i))).get_valeur() == "sel" && (*(it1+10+(5*i))).get_nature() == mot_clef ){
              //         (it->second).add_link_to_previous_noeud((*(it1+10+(5*i))).get_valeur());
              //     }
              //     else{
              //       break;
              //     }
              //   }
              //   (it->second).set_nb_inout((nb_sel_moins1 + 1) + (it->second).get_nb_inout());
              //   next_state = FINISHED;
              //   break;


              case OLD_IDENTIFIANT :
                next_state = (is_there_a_link( (*(it1-1)).get_nature(), (*(it1+1)).get_nature() ) == true ) ? ADD_LINK : ERROR_VARIABLE_LINKS_G;
              break;

              // case IS_IT_SPECIAL_LINK_OR_NOT:
              //   if( (*(it1-1)).get_nature() == ponctuation && (*(it1+1)).get_nature() == ponctuation && (*(it1-3)).get_nature() == mot_clef ){
              //     next_state = FINISHED;
              //   }else{
              //     next_state = ERROR_VARIABLE_LINKS_G;
              //   }
              //   break;

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
                cout << "parser_dot.cpp, ERROR : " << (*it1).get_valeur() << " must be declared first" << endl;
                next_state = FINISHED;
              break;

              case ERROR_VARIABLE_LINKS_G :
                cpt_error ++;
                cout << "parser_dot.cpp, ERROR : no good links for " << (*it1).get_valeur() << " at line " << (*it1).get_line_index() << endl;
                next_state = FINISHED;
              break;

              case ERROR_VARIABLE_LINKS_INPUT :
                cpt_error ++;
                cout << "parser_dot.cpp, ERROR : missing '->' after INPUT " << (*it1).get_valeur() << " at line " << (*it1).get_line_index() << endl;
                next_state = FINISHED;
              break;

              case ERROR_VARIABLE_LINKS_OUTPUT :
                cpt_error ++;
                cout << "parser_dot.cpp, ERROR : missing '->' before OUTPUT " << (*it1).get_valeur() << " at line " << (*it1).get_line_index() << endl;
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

      for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it) {
        loop_recursive_function((it->second), noeud_map, (it->second).get_nom());
      }

      // Check Nb_link OK With nb get_nb_inout
      for(map<string, Noeud>::iterator it = noeud_map.begin(); it != noeud_map.end(); ++it) {
        if((it->second).get_nb_inout() != ( (it->second).get_links() ).size() ){
          cpt_error ++;
          cout << "parser_dot.cpp, ERROR : " << (it->second).get_nom() << " should have " << (it->second).get_nb_inout() << " links but have " << ( (it->second).get_links() ).size() << endl;
        }else{}
      }

      if(cpt_error == 0){
        return noeud_map;
      }else{
        cout << "parser_dot.cpp, TOTAL ERRORS BEFORE KILL : " << cpt_error << endl;
        cout << "parser_dot.cpp, PROG KILLED\n" << endl;
        exit(-1);
      }

}
