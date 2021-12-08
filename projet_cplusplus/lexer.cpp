#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "symbole.h"

using namespace std;

Nature_grammaticale Is_a_letter(string l);


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

                string str = *(txt_line_vector.begin()+2);
                cout<<str<<endl;
                for(int i = 0; i < str.length(); ++i)
                {
                  while((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9'))
                  {
                    i++;
                  }
                  char delimiteur = str[i];
                  cout << delimiteur << endl;
                  stringstream sstream(str);
                  string symbole;
                  getline(sstream, symbole, delimiteur);
                  cout << symbole << endl;
                }

                //Symbole Symb_test(mot_clef, "diagraph_test", 1);


        }
        else  // sinon
                cerr << "Impossible d'ouvrir le fichier !" << endl;

        return 0;
}

// Nature_grammaticale Is_a_letter(string l){
//         for(int i = 0; i < l.length(); ++i)
//         {
//             char c = l[i];
//             if ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
//             {
//               cout << "lettre" << endl;
//             }else{
//               cout << "stop" << endl;
//             }
//         }
// }
