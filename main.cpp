#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "symbole.h"
#include "Noeud.h"

#include "lexer.h"
#include "parser.h"
#include "Simulateur.h"


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

                // Affichage Vector de lignes//
                for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
                    cout << *it << endl;
                }

                std::vector<Symbole> symbole_vector = lexeme(txt_line_vector);

                // Affichage Vector de Symboles//
                for(vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end(); ++it) {
                  Symbole symb = *it;
                    cout << "Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
                }

                static_noeud_map = parser(symbole_vector);

                for(map<string, Noeud>::iterator it = static_noeud_map.begin(); it != static_noeud_map.end(); ++it) {
                  Noeud noeud = it->second;
                  cout << "Nom : " << noeud.get_nom() << "\t\t\tType : " << noeud.get_type() << "\t\t\tNb_input : " << noeud.get_nb_inout()<< "\t\t\tLink : ";
                  noeud.print_link();
                  cout << endl;
                }



          }else { // sinon
                cerr << "Impossible d'ouvrir le fichier !" << endl;
          }

          return 0;
}
