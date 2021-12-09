#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "symbole.h"

using namespace std;

// enum Lexeme_fsm_state{
//   IS_NEXT_TOKEN_ALPHANUM,
//   GET_ALPHANUM_TOKEN_END,
// };


int main()
{
        ifstream fichier("and_xor.dot", ios::in);  // on ouvre le fichier en lecture

        if(fichier)  // si l'ouverture a réussi
        {
                cout << "fichier ouvert !" << endl;

                std::vector<std::string> txt_line_vector;
                string line;
                while(getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
                {
                        txt_line_vector.push_back(line);
                }

                fichier.close();  // on ferme le fichier
                cout << "fichier fermé !" << endl;


                // // Affichage //
                // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
                //     cout << *it << endl;
                // }

                // Sppression des espaces //
                for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
                  (*it).erase(std::remove((*it).begin(), (*it).end(), ' '), (*it).end());
                }

                // // Affichage //
                // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
                //     cout << *it << endl;
                // }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                std::vector<Symbole> symbole_vector;
                for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it)
                {
                  // cout << "<Ligne complete>" << *it<<endl;
                  string str=*it; //  ligne de notre tableau de lignes

                  string token;

                  for(int i = 0; i <= str.length(); i++)
                  {

                    token.clear();
                    token.push_back(str[i]);
                    //check si alphanum
                    if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_')
                    {
                      while((str[i+1] >= 'A' && str[i+1] <= 'Z') || (str[i+1] >= 'a' && str[i+1] <= 'z') || (str[i+1] >= '0' && str[i+1] <= '9') || str[i+1] == '_')
                      {
                        token.push_back(str[i+1]);
                        i++;
                      }
                      //check si keyword
                      if(token == "label" || token == "digraphtest" || token == "INPUT" || token == "OUTPUT" || token == "AND2" || token == "XOR2"){
                        Symbole S(mot_clef, token, it - txt_line_vector.begin() + 1);
                        symbole_vector.push_back(S);
                      }else{
                        Symbole S(identifiant, token, it - txt_line_vector.begin() + 1);
                        symbole_vector.push_back(S);
                      }
                    }
                    else
                    {//si pas alphanum
                       if(str[i]== '[' || str[i]== '{' || str[i] == ']' || str[i]== '}' || str[i]== '"' || str[i]== ';'){
                          Symbole S(ponctuation, token, it - txt_line_vector.begin() + 1);
                          symbole_vector.push_back(S);
                       }else{
                         if(str[i]== '=' || str[i]== '-' || str[i] == '>'){
                           Symbole S(operateur, token, it - txt_line_vector.begin() + 1);
                           symbole_vector.push_back(S);
                         }else{
                           if (str[i] != 0)
                             cout << "erreur ! " << str[i] << it - txt_line_vector.begin() + 1 << endl;
                         }
                       }
                     }
                   }
                 }

              // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it)
              //    {
              //      cout << *it<<endl;
              //      string ligne=*it;//  ligne de notre tableau de lignes
              //
              //      string mot; // Mot de notre ligne, tab de characteres on initialise à vide
              //
              //
              //      std::vector<std::string> tab_mots; // tab de mots
              //
              //      for(int i=0; i<ligne.length(); i++) // on lit chaque caractere de la ligne
              //      {
              //
              //        if(ligne[i]!= '[' && ligne[i]!= '{' && ligne[i]!= ']' && ligne[i]!= '=' && ligne[i]!= '"')
              //        {
              //          mot.push_back(ligne[i]); // je cree le mot apres la lecture de chaque caractere
              //        }
              //
              //
              //        else { // Il a fini de lire le premier mot, il a rencontré un delimitateur
              //        tab_mots.push_back(mot);
              //
              //        // On veut recuperer ce delimitateur dans une nouvelle mot
              //       // mot="";
              //       mot.clear(); // reinitialisation du mot à vide
              //
              //       mot.push_back(ligne[i]); // mot = delimitateur
              //       tab_mots.push_back(mot);
              //       mot.clear();
              //      }
              //
              //
              //      }
              //
              //      for(std::vector<string>::iterator it = tab_mots.begin(); it != tab_mots.end(); ++it)
              //      {
              //       cout << *it<<endl;// affichage de mots
              //      }
              //    }
              // Symbole Symb_test1(mot_clef, "diagraph_test", 1);
              // Symbole Symb_test2(identifiant, "I1", 1);
              // std::vector<Symbole> Symbole_vector;
              // Symbole_vector.push_back(Symb_test1);
              // Symbole_vector.push_back(Symb_test2);
              //
              for(vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end(); ++it) {
                Symbole symb = *it;
                  cout << "Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
              }

            }else { // sinon
                cerr << "Impossible d'ouvrir le fichier !" << endl;
            }
        return 0;
}
