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
#include "stimulus.h"

//Etats de la MAE pour la fonction parser_json qui verifie le decoupage
enum PARSER_JSON_FSM{
        START,
          MOT_CLEF,
          S1,
          S2,
          S3,
          S4,
          S5,
          S6,
          IDENTIFIANT,
          S7,
          S8,
          TAB_VALEUR,
          S9,
          S10,
          S11,
        FINISHED_JSON,
        ERROR,
};

enum FSM_STATES_CREATE_STIMULUS
 {
   IS_NEW_CS,
   FINISHED_CS,
   ERROR_CS,
 };


// Verification decoupage fichier .json
void parser_decoupage_json(vector<Symbole_json> &symbole_vector_json)
{
       int count= 0;
       // Compteur = 0 si pas d'erreurs
       // Compteur!= 0 si'il y a des erreurs
       int line_index_error=0;
       // Ligne ou on constate l'erreur

       std::vector<Symbole_json>::iterator it = symbole_vector_json.begin();
       // it est un iterateur qui pointe sur chaque symbole json

      PARSER_JSON_FSM next_state = START;

      while (next_state != FINISHED_JSON){

        switch (next_state){

            case START:
                 // On verifie que le premier mot du vecteur est bien {, sinon erreur
                   if((*it).get_valeur()!= "{"){
                          count++;
                          cout << "Error found on line:  " << symbole_vector_json[0].get_line_index()<<'\n';
                          next_state=ERROR;
                          }
                   else{
                          it++;
                          next_state= MOT_CLEF;
                    }
                   break;

            case MOT_CLEF:
                  // On verifie que ce qui suit est bien mot_clef, sinon erreur
                    if( (*it).get_nature()== mot_clef_json ){
                          next_state=S2;
                    }
                    else if( (*it).get_valeur()== "}" ){ //{}, cas de ligne vide à gerer
                          next_state=S10;
                    }
                    else{
                          count++;
                          line_index_error= (*it).get_line_index();
                          cout << "Error found on line:  " <<line_index_error<<'\n';
                          next_state=ERROR;
                          }
                      it++;
                      break;


              case S2 :
                   //ce qui suit  le mot_clef doit etre un :, sinon erreur
                      if( (*it).get_valeur()!= ":" ){
                          count++;
                          line_index_error= (*it).get_line_index();
                          cout << "Error found on line:  " <<line_index_error<<'\n';
                          next_state=ERROR;
                        }
                      else{
                          it++;
                          next_state=S3;
                        }
                      break;

              case S3:
                   // ce qui suit : doit etre un [ ou ' sinon erreur
                        if( (*it).get_valeur()=="[" ){
                           next_state=START;
                            }
                        else if((*it).get_valeur()=="'" ){
                           next_state=IDENTIFIANT;
                            }
                        else{
                            count++;
                            line_index_error= (*it).get_line_index();
                            cout << "Error found on line:  " <<line_index_error<<'\n';
                            next_state=ERROR;
                            }
                        it++;
                        break;

              case IDENTIFIANT:
                        if( (*it).get_nature()!=identifiant_json ){
                             next_state=ERROR;
                             count++;
                             line_index_error= (*it).get_line_index();
                             cout << "Error found on line:  " <<line_index_error<<'\n';
                             }
                        else{
                             next_state=S4;
                             }
                        it++;
                        break;

              case S4:
                     if( (*it).get_valeur()!="'" ){
                             count++;
                             line_index_error= (*it).get_line_index();
                             cout << "Error found on line:  " <<line_index_error<<'\n';
                             next_state=ERROR;
                             }
                      else{
                              next_state=S5;
                              }
                      it++;
                      break;

              case S5:
                     if( (*it).get_valeur()!="," ){
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                              next_state=ERROR;
                              }
                      else{
                              next_state=S6;
                              }
                      it++;
                      break;

              case S6:
                     if  ((*it).get_valeur()!= "wave" ){
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                              next_state=ERROR;
                              }

                    else{
                              next_state=S7;
                              }
                    it++;
                    break;

              case S7:
                     if(  (*it).get_valeur()!= ":" ){
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                              next_state=ERROR;
                              }
                     else{
                              next_state=S8;
                              }
                     it++;
                     break;

              case S8:
                    if  ((*it).get_valeur()!= "'" ){
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                              next_state=ERROR;
                              }
                    else{
                              next_state=TAB_VALEUR;
                              }

                    it++;
                    break;

              case TAB_VALEUR:
                     if(  (*it).get_valeur()== "0"|| (*it).get_valeur()=="1" || (*it).get_valeur()== "."){
                              next_state=TAB_VALEUR;
                              }
                     else if (  (*it).get_valeur()== "'"){
                              next_state=S9;
                              }
                    else {
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                              next_state=ERROR;
                              }
                    it++;
                    break;

              case S9:

                      if(  ((*it).get_valeur())== "}" ){
                              next_state=S10;
                              }


                      else{
                              next_state=ERROR;
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                            }
                      it++;
                      break;

              case S10:
                      if( (*it).get_valeur()=="," )
                              {next_state= START;}

                      else if( (*it).get_valeur()=="]" )
                              {next_state= S11;}
                      else{
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                              next_state=ERROR;
                              }

                      it++;
                      break;

              case S11:
                      if( (*it).get_valeur()!="}"){
                              count++;
                              line_index_error= (*it).get_line_index();
                              cout << "Error found on line:  " <<line_index_error<<'\n';
                              next_state=ERROR;
                              }

                      else{ next_state= FINISHED_JSON;}

                      it++;
                      break;

                case ERROR:
                              cout<< " The error is: " <<(*(it-1)).get_valeur()<< endl;
                              next_state=FINISHED_JSON;
                              it++;
                              break;


                case FINISHED_JSON:
                              //cout<< "Verification finished !! " <<'\n';
                              break;

                  default:    cout << "Unknown state" <<'\n';
                              next_state=FINISHED_JSON;
                              break;
                       }// fermeture du case
                 }// fermeture du while

                if(count==0){
                  cout<< "No errors found in parsing decoupage.json ! " <<endl;
                }
                else {
                  cout<< "Number of errors found in parsing decoupage.json : " <<count<<'\n';
                  exit(-1);
                }
}

//Fonction parser pour le fichier json qui crée des objets stimulus
vector <Stimulus> parser_create_stimulus_vector(vector<Symbole_json> &symbole_vector_json){
  // Declaration de vecteur vide SIMULUS_VECTOR
  vector <Stimulus> stimulus_vector;

  FSM_STATES_CREATE_STIMULUS next_state;

  //Suppression des mot_clefs et ponctuations
  for(std::vector<Symbole_json>::iterator it = symbole_vector_json.begin(); it != symbole_vector_json.end();)
  {
    if((*it).get_nature() == ponctuation_json || (*it).get_nature() == mot_clef_json)
    {
      it = symbole_vector_json.erase(it); // Pas d'incrementation
    }
    else{ ++it; }
  }
  // Variable dans la quelle on sauvegarde la derniere valeur de l'input
  int sauvegarde=0;

  // Declaration de it sur symbole_json à utiliser dans la FSM
  std::vector<Symbole_json>::iterator it = symbole_vector_json.begin();

    if((*it).get_nature() == identifiant_json){
      FSM_STATES_CREATE_STIMULUS next_state = IS_NEW_CS;
    }

    while (next_state != FINISHED_CS ){

          switch (next_state){

            case IS_NEW_CS :

            // Variable sauvegarde initialisé à 0 pour chaque nouveau stimulus
            sauvegarde=0;

            // Si stimulus_vector est vide => Creation du stimulus
            if (stimulus_vector.empty()) {
                //Creation de stimulus avec un seul attribut: string m_nom;
                Stimulus new_stimulus((*it).get_valeur());
                cout<<"Creation d'objet stimulus: "<<(*it).get_valeur()<<endl;
                // Incrementation du it pour lire les valeurs numeriques
                // Identifiant est suivi que de valeurs numeriques
                it++;

                while ((*it).get_nature()==valeur_numerique_json){

                   if( (*it).get_valeur()=="1"){
                       new_stimulus.add_valeur_stimulus(1);
                       sauvegarde=1;
                     }

                   else if( (*it).get_valeur()=="0"){
                       new_stimulus.add_valeur_stimulus(0);
                       sauvegarde=0;
                     }
                   else{
                        new_stimulus.add_valeur_stimulus(sauvegarde);
                     }

                    if( it== symbole_vector_json.end()) {}
                    else { it++;}
                  } // closed while

               if( it== symbole_vector_json.end()){
                        next_state=FINISHED_CS; // fin du vecteur symbole_json
                        break;}

               else{
                    stimulus_vector.push_back( new_stimulus);
                    next_state=IS_NEW_CS;
                    break;}
              }

          else{ //stimulus_vector n'est pas vide

            // Verification que le stimulus n'a pas deja ete declare
              for(std::vector<Stimulus>::iterator it2 = stimulus_vector.begin(); it2 != stimulus_vector.end(); ++it2){
               // Si deja declaré
                if(((*it).get_valeur())==((*it2).get_nom())){
                    cout<<(*it).get_valeur()<< " a deja été declaré! "<<endl;
                    next_state = ERROR_CS;
                    break;
                  }
               }

              Stimulus new_stimulus((*it).get_valeur());
              cout<< "Creation d'objet stimulus: "<<(*it).get_valeur()<<endl;
              it++;
                 // On remplit  le vecteur de int
                  while ((*it).get_nature()==valeur_numerique_json )
                  {
                        if( (*it).get_valeur()=="1"){
                          new_stimulus.add_valeur_stimulus(1);
                          sauvegarde=1;
                        }
                        else if( (*it).get_valeur()=="0"){
                          new_stimulus.add_valeur_stimulus(0);
                          sauvegarde=0;
                        }
                        else{
                          new_stimulus.add_valeur_stimulus(sauvegarde);
                        }
                        if( it== symbole_vector_json.end()){}
                        else {  it++;}
                    }// while closed
                    // Dernier element du vecteur symbole_json
                    if( it== symbole_vector_json.end())
                          {
                            stimulus_vector.push_back( new_stimulus);
                            next_state=FINISHED_CS;
                            break;
                          }
                    else{
                        stimulus_vector.push_back( new_stimulus);
                        next_state=IS_NEW_CS;
                        break;
                      }
                  } // cas stimulus_vector pas vide OK


              case ERROR_CS:
                cout<<"ERREUR DE DECLARATION!"<<endl;
                next_state= FINISHED_CS;
                break;

              case FINISHED_CS:
                cout<<"DONE!"<<endl;
                break;

               default:
                 cout<<"ERREUR DE FSM!"<<endl;
                 next_state= FINISHED_CS;
                 break;
              }// case closed
            }
          return stimulus_vector;
} // Function closed
