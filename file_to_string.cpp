#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdlib.h>


#include "symbole.h"


std::vector<std::string> file_to_string_vector(const char* file_name){

  ifstream fichier(file_name, ios::in);  // on ouvre le fichier en lecture

  if(fichier){  // si l'ouverture a réussi
          cout << "fichier ouvert !" << endl;

          std::vector<std::string> txt_line_vector;
          string line;
          while(getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
          {
                  txt_line_vector.push_back(line);
          }

          fichier.close();  // on ferme le fichier
          cout << "fichier fermé !" << endl;

          return txt_line_vector;

  }else { // sinon
          cerr << "Impossible d'ouvrir le fichier !" << endl;
          exit(-1);
  }
}
