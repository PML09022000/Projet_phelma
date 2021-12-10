#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "lexer.h"

using namespace std;

vector<Symbole> lexeme(vector<string> &txt_line_vector){
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
        if(token == "label" || token == "digraph" || token == "INPUT" || token == "OUTPUT" || token == "AND2" || token == "XOR2"){
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
             if (str[i] != 0 && str[i] != ' ')
               cout << "erreur ! " << str[i] << it - txt_line_vector.begin() + 1 << endl;
           }
         }
       }
     }
   }
   return symbole_vector;
}



























// int main()
// {
//         ifstream fichier("and_xor.dot", ios::in);  // on ouvre le fichier en lecture
//
//         if(fichier)  // si l'ouverture a réussi
//         {
//                 cout << "fichier ouvert !" << endl;
//
//                 std::vector<std::string> txt_line_vector;
//                 string line;
//                 while(getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
//                 {
//                         txt_line_vector.push_back(line);
//                 }
//
//                 fichier.close();  // on ferme le fichier
//                 cout << "fichier fermé !" << endl;
//
//
//                 // // Affichage //
//                 // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
//                 //     cout << *it << endl;
//                 // }
//
//                 // Sppression des espaces //
//                 // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
//                 //   (*it).erase(std::remove((*it).begin(), (*it).end(), ' '), (*it).end());
//                 // }
//
//                 // // Affichage //
//                 // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it) {
//                 //     cout << *it << endl;
//                 // }
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                 // std::vector<Symbole> symbole_vector;
//                 // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it)
//                 // {
//                 //   // cout << "<Ligne complete>" << *it<<endl;
//                 //   string str=*it; //  ligne de notre tableau de lignes
//                 //
//                 //   string token;
//                 //
//                 //   for(int i = 0; i <= str.length(); i++)
//                 //   {
//                 //
//                 //     token.clear();
//                 //     token.push_back(str[i]);
//                 //     //check si alphanum
//                 //     if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_')
//                 //     {
//                 //       while((str[i+1] >= 'A' && str[i+1] <= 'Z') || (str[i+1] >= 'a' && str[i+1] <= 'z') || (str[i+1] >= '0' && str[i+1] <= '9') || str[i+1] == '_')
//                 //       {
//                 //         token.push_back(str[i+1]);
//                 //         i++;
//                 //       }
//                 //       //check si keyword
//                 //       if(token == "label" || token == "digraph" || token == "INPUT" || token == "OUTPUT" || token == "AND2" || token == "XOR2"){
//                 //         Symbole S(mot_clef, token, it - txt_line_vector.begin() + 1);
//                 //         symbole_vector.push_back(S);
//                 //       }else{
//                 //         Symbole S(identifiant, token, it - txt_line_vector.begin() + 1);
//                 //         symbole_vector.push_back(S);
//                 //       }
//                 //     }
//                 //     else
//                 //     {//si pas alphanum
//                 //        if(str[i]== '[' || str[i]== '{' || str[i] == ']' || str[i]== '}' || str[i]== '"' || str[i]== ';'){
//                 //           Symbole S(ponctuation, token, it - txt_line_vector.begin() + 1);
//                 //           symbole_vector.push_back(S);
//                 //        }else{
//                 //          if(str[i]== '=' || str[i]== '-' || str[i] == '>'){
//                 //            Symbole S(operateur, token, it - txt_line_vector.begin() + 1);
//                 //            symbole_vector.push_back(S);
//                 //          }else{
//                 //            if (str[i] != 0 && str[i] != ' ')
//                 //              cout << "erreur ! " << str[i] << it - txt_line_vector.begin() + 1 << endl;
//                 //          }
//                 //        }
//                 //      }
//                 //    }
//                 //  }
//
//               // for(std::vector<string>::iterator it = txt_line_vector.begin(); it != txt_line_vector.end(); ++it)
//               //    {
//               //      cout << *it<<endl;
//               //      string ligne=*it;//  ligne de notre tableau de lignes
//               //
//               //      string mot; // Mot de notre ligne, tab de characteres on initialise à vide
//               //
//               //
//               //      std::vector<std::string> tab_mots; // tab de mots
//               //
//               //      for(int i=0; i<ligne.length(); i++) // on lit chaque caractere de la ligne
//               //      {
//               //
//               //        if(ligne[i]!= '[' && ligne[i]!= '{' && ligne[i]!= ']' && ligne[i]!= '=' && ligne[i]!= '"')
//               //        {
//               //          mot.push_back(ligne[i]); // je cree le mot apres la lecture de chaque caractere
//               //        }
//               //
//               //
//               //        else { // Il a fini de lire le premier mot, il a rencontré un delimitateur
//               //        tab_mots.push_back(mot);
//               //
//               //        // On veut recuperer ce delimitateur dans une nouvelle mot
//               //       // mot="";
//               //       mot.clear(); // reinitialisation du mot à vide
//               //
//               //       mot.push_back(ligne[i]); // mot = delimitateur
//               //       tab_mots.push_back(mot);
//               //       mot.clear();
//               //      }
//               //
//               //
//               //      }
//               //
//               //      for(std::vector<string>::iterator it = tab_mots.begin(); it != tab_mots.end(); ++it)
//               //      {
//               //       cout << *it<<endl;// affichage de mots
//               //      }
//               //    }
//
//
//
//
//
//
//                           //   // Le Parser_Decoupage recupere un vecteur de symboles
//                           //   // On doit verifier l'ordre
//                           //   //On parcoure ce vecteur pour verifier l'ordre des symboles
//                           //
//                           //     int count= 0;
//                           //     // Compteur qui va etre à 0 si pas d'erreurs
//                           //     // Valeur de compteur differente de 0 si'il y a des erreurs
//                           //     int line_index_error=0;
//                           //     // Ligne ou on constate l'erreur
//                           //
//                           //
//                           //   for(std::vector<Symbole>::iterator it = (symbole_vector.begin()+3); it != (symbole_vector.end()-2); ++it)
//                           //          {
//                           //         //Je ne parcoure pas les 2 dernieres symboles parce que je vais verifier appart que c'est bien ; et }
//                           //
//                           //
//                           //         //       Chaque *it pointe sur un symbole
//                           //         //       //Identifiant doit etre suivie de ponctuation [, ou ;  ou operateur -
//                           //
//                           //              if( (*it).get_nature()==identifiant )
//                           //               {
//                           //                 if( (*(it+1)).get_valeur()!="[" && (*(it+1)).get_valeur()!=";" && (*(it+1)).get_valeur()!= "-")
//                           //                 {
//                           //                   count++;
//                           //                   line_index_error= (*it).get_line_index();
//                           //                   cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                 }
//                           //               }
//                           //
//                           //        //  //      "[" doit etre suivi de identifiant, probleme de ] à gerer
//                           //         else if( (*it).get_valeur()=="[" )
//                           //                {
//                           //                  if( (*(it+1)).get_nature()!= mot_clef || (*(it-1)).get_nature()!= identifiant )
//                           //                  {
//                           //                    count++;
//                           //                    line_index_error= (*it).get_line_index();
//                           //                    cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                  }
//                           //                 }
//                           //        //
//                           //        // //      mot clef label  doit etre suivi de =
//                           //        //
//                           //               else if( (*it).get_valeur()== "label" )
//                           //                 {
//                           //                   if( (*(it+1)).get_valeur()!= "=" )
//                           //                   {
//                           //                     count++;
//                           //                     line_index_error= (*it).get_line_index();
//                           //                     cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                   }
//                           //                  }
//                           //         //      =  est suivi de "
//                           //
//                           //             else  if( (*it).get_valeur()== "=" )
//                           //                 {
//                           //                   if( ((*(it+1)).get_valeur()[0])!= '"' )
//                           //                   {
//                           //                     count++;
//                           //                     line_index_error= (*it).get_line_index();
//                           //                     cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                   }
//                           //                  }
//                           //       //
//                           //       //
//                           //       // //      "  est suivi de mot_clef
//                           //       //
//                           //                  else if( (*it).get_valeur()[0]=='"' )
//                           //                    {
//                           //                      if( (*(it+1)).get_nature()== mot_clef )
//                           //                      { // Verification du couple ""
//                           //                           if( (*(it+2)).get_valeur()[0]!= '"'  )
//                           //                           {
//                           //                             count++;
//                           //                             line_index_error= (*it).get_line_index();
//                           //                             cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                           }
//                           //                       }
//                           //                     else if ( (*(it+1)).get_valeur()!= "]" )
//                           //                       {
//                           //                         count++;
//                           //                         line_index_error= (*it).get_line_index();
//                           //                         cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                       }
//                           //                     }
//                           //
//                           //         //      ]  est suivi de ';'
//                           //                 else if( (*it).get_valeur()=="]" )
//                           //                     {
//                           //                       if( (*(it+1)).get_valeur()!= ";" )
//                           //                           {
//                           //                             count++;
//                           //                             line_index_error= (*it).get_line_index();
//                           //                             cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                           }
//                           //                      }
//                           //         //      ; est suivi de identifiant
//                           //               else if( (*it).get_valeur()==";" )
//                           //                  {
//                           //                     if( (*(it+1)).get_nature()!=identifiant )
//                           //                         {
//                           //                           count++;
//                           //                           line_index_error= (*it).get_line_index();
//                           //                           cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                         }
//                           //                    }
//                           //
//                           //         //      - est suivi de >
//                           //
//                           //               else if( (*it).get_valeur()=="-" )
//                           //                       {
//                           //                          if( (*(it+1)).get_valeur()!= ">" )
//                           //                              {
//                           //                                count++;
//                           //                                line_index_error= (*it).get_line_index();
//                           //                                cout << "Error found on line:  " <<line_index_error<<'\n';
//                           //                              }
//                           //                         }
//                           //
//                           //
//                           //   }
//                           //
//                           // //  Verification des premieres et dernieres symboles
//                           // //  premier symbole doit etre digraph
//                           //   if(symbole_vector[0].get_valeur()!= "digraph")
//                           //         {
//                           //           count++;
//                           //
//                           //           cout << "Error found on line:  " << symbole_vector[0].get_line_index()<<'\n';
//                           //         }
//                           //   // deuxieme symbole doit etre identifiant
//                           // if(symbole_vector[1].get_nature()!= identifiant)
//                           //               {
//                           //                 count++;
//                           //                 cout << "Error found on line:  " << symbole_vector[1].get_line_index()<<'\n';
//                           //               }
//                           //
//                           // //  troisieme symbole doit etre {
//                           // if(symbole_vector[2].get_valeur()!= "{")
//                           //     {
//                           //         count++;
//                           //         cout << "Error found on line:  " << symbole_vector[2].get_line_index()<<'\n';
//                           //       }
//                           //
//                           // //  Dernier symbole doit etre {
//                           // // Recuperation du dernier symbole de notre symbole vecteur
//                           //
//                           // //cout<<(*((symbole_vector.end()-1))).get_valeur()<<endl;
//                           //
//                           // if((*((symbole_vector.end()-1))).get_valeur()!= "}")
//                           // {
//                           //   count++;
//                           //   cout << "Error found on line:  " << (*((symbole_vector.end()-1))).get_line_index()<<'\n';
//                           //  }
//                           //
//                           //  //  Avant dernier symbole doit etre ;
//                           //
//                           //  if((*((symbole_vector.end()-2))).get_valeur()!= ";")
//                           //  {
//                           //    count++;
//                           //    cout << "Error found on line:  " << (*((symbole_vector.end()-2))).get_line_index()<<'\n';
//                           //   }
//                           //
//                           //   // Affichage des erreurs et des numeros de lignes
//                           //
//                           //   if(count==0) {
//                           //       cout << "No errors found" << '\n';
//                           //     }
//                           //   else {
//                           //     cout << "Nb errors " << count<<'\n';
//                           //      }
//
//
//               std::vector<Symbole> symbole_vector = lexeme(txt_line_vector);
//
//
//               for(vector<Symbole>::iterator it = symbole_vector.begin(); it != symbole_vector.end(); ++it) {
//                 Symbole symb = *it;
//                   cout << "Nature_grammaticale : " << symb.get_nature() << "\t\t\tValeur : " << symb.get_valeur() << "\t\t\tLigne : " << symb.get_line_index()<< endl;
//               }
//
//
//
//
//
//             }else { // sinon
//                 cerr << "Impossible d'ouvrir le fichier !" << endl;
//             }
//         return 0;
// }
//
//
