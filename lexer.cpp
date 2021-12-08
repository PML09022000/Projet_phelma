#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "symbole.h"

using namespace std;


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


                // Affichage //
                for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
                    cout << *it << endl;
                }

                // Sppression des espaces //
                for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
                  (*it).erase(std::remove((*it).begin(), (*it).end(), ' '), (*it).end());
                }

                // Affichage //
                for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
                    cout << *it << endl;
                }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it)
                {
                  cout << "<Ligne complete>" << *it<<endl;
                  string str=*it; //  ligne de notre tableau de lignes
                  string alphanum;
                  int p = 0;

               //pour toute la ligne
                  for(int i = 0; i <= str.length(); i++)
                  {
                    alphanum.clear();
                    //str[i] ? alphanum?

                    if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'){
                     //si c'est un identifiant
                      while((str[i+1] >= 'A' && str[i+1] <= 'Z') || (str[i+1] >= 'a' && str[i+1] <= 'z') || (str[i+1] >= '0' && str[i+1] <= '9') || str[i+1] == '_')
                      {
                        i++;
                      }
                      for (int k=p ; k <= i; k++){
                        alphanum.push_back(str[k]);
                      }
                      cout << alphanum << endl;
                      //voir si keyword
                      if(alphanum == "label" || alphanum == "digraphtest"){
                        cout << "mot clef" << endl;
                      }else{
                        cout << "identifiant" << endl;
                      }

                    }else{//si pas alphanum
                       if((str[i]== '[' || str[i]== '{' || str[i] == ']' || str[i]== '}' || str[i]== '"' || str[i]== ';')){
                          cout << str[i] << endl; // ponctuation
                       }else{
                         switch(str[i])
                         {
                           case '=':// operateur =
                              cout << str[i] << endl;
                           break;

                           case '-':
                              if(str[i+1] == '>'){
                                cout << str[i] << str[i+1] << endl;
                                i++;
                              }else{
                                cout << "erreur !!!" << it - txt_line_vector.begin() + 1 << endl;
                              }
                           break;

                           case NULL :
                           break;

                           default:
                              cout << "erreur !!!" << str[i] << it - txt_line_vector.begin() + 1 << endl;
                            break;
                         }
                       }
                    }

                    p = i+1;
                    //sauvegarde lexemes/symbole
                    //continue la ligne
                }
                //getline(sstream, symbole, delimiteur);

                //Symbole Symb_test(mot_clef, "diagraph_test", 1);


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
            }else { // sinon
                cerr << "Impossible d'ouvrir le fichier !" << endl;
              }
        return 0;
}
