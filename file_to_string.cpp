#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdlib.h>

#include "symbole.h"

#define display 0

std::vector<std::string> file_to_string_vector(const char* file_name){

  ifstream fichier(file_name, ios::in);  // on ouvre le fichier en lecture

  if(fichier){  // si l'ouverture a réussi
          if(display){
            cout << "fichier ouvert !" << endl;
          }
          std::vector<std::string> txt_line_vector;
          string line;
          while(getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
          {
                  txt_line_vector.push_back(line);
          }

          fichier.close();  // on ferme le fichier
          if(display){
            cout << "fichier fermé !" << endl;
          }
          return txt_line_vector;

  }else { // sinon
          cerr << "file_to_string.cpp, impossible to open file '" << file_name << "'" << endl;
          exit(-1);
  }
}
