//Methode 1

//   int count=0;
//    int line_index_error=0;
//
// std::vector<Symbole>::iterator it = symbole_vector.begin();
// // it est un iterateur qui pointe sur chaque symbole du vecteur
//
// while(it!= symbole_vector.end()){
//
//      VERIFICATION_DECOUPAGE_FSM_STATES next_state = S1;
//
//
//
//
// while (next_state != NULL_STATE){
//
//       switch (next_state){
//         /////////////////////
//           case S1:
//           // On verifie que le premier mot du vecteur est bien digraph, sinon erreur
//             if((*it).get_valeur()!= "digraph")
//             {
//               count++;
//               cout << "Error found on line:  " << symbole_vector[0].get_line_index()<<'\n';}
//                it++;
//                next_state = S2;
//
//             case S2 :
//
//                 // On verifie que ce qui suit est bien identifiant, sinon erreur
//
//                  if( (*it).get_nature()!=identifiant )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                 next_state =S3;
//                 break;
//
//         /////////////////////
//             case S3 :
//             //ce qui suit l'identifiant doit etre un {, sinon erreur
//                    if( (*it).get_valeur()!= "{" )
//                    {
//                      count++;
//                          line_index_error= (*it).get_line_index();
//                                 cout << "Error found on line:  " <<line_index_error<<'\n';
//                    }
//                    next_state = ID_S4;
//                    it++;
//                     break;
//
//             case ID_S4:
//             // ce qui suit { doit etre un identifiant, sinon erreur
//              if( (*it).get_nature()!=identifiant )
//              {
//                count++;
//                    line_index_error= (*it).get_line_index();
//                           cout << "Error found on line:  " <<line_index_error<<'\n';
//              }
//              it++;
//              next_state = S5;
//             break;
//
//             case S5: // plusieurs possibilités à gerer
//               // Identifiant doit etre suivi de [ - ou ;, sinon erreur
//               if( (*it).get_valeur()=="["  || (*it).get_valeur()=="-" || (*it).get_valeur()!=";" )
//                    {
//                      if ( (*it).get_valeur()=="[" )
//                       {
//                         next_state=S6;
//                       }
//
//                       else if( (*it).get_valeur()=="-" )
//                       {
//                         next_state=S13;
//                       }
//                       else // if( (*it).get_valeur()==";" )
//                       {
//                         next_state=ID_S4;
//                       }
//                    }
//               else
//                {cout<<"Fin de verification "<< endl;
//
//                             break;
//                  count++;
//                      line_index_error= (*it).get_line_index();
//                             cout << "Error found on line:  " <<line_index_error<<'\n';
//                   next_state=WAIT;
//                }
//                     it++;
//                     break;
//
//             case S6:
//
//               if( (*it).get_valeur()!="label" )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                 next_state= S7;
//                   break;
//
//             case S7:
//               if( (*it).get_valeur()!="=" )
//                      {
//                        count++;
//                            line_index_error= (*it).get_line_index();
//                                   cout << "Error found on line:  " <<line_index_error<<'\n';
//                      }
//                       it++;
//                        next_state= S8;
//                       break;
//
//             case S8:
//
//               if(  ((*it).get_valeur()[0])!= '"' )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S9;
//                  break;
//
//             case S9:
//
//               if(  (*it).get_nature()!= mot_clef || (*it).get_valeur()== "label" || (*it).get_valeur()== "digraph")
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S10;
//                  break;
//
//             case S10: //
//
//               if(  ((*it).get_valeur()[0])!= '"' )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S11;
//                  break;
//
//             case S11: //
//
//               if(  (*it).get_valeur()!= "]"  )
//                  {
//                    count++;
//                        line_index_error= (*it).get_line_index();
//                               cout << "Error found on line:  " <<line_index_error<<'\n';
//                  }
//                  it++;
//                  next_state= S12;
//                  break;
//
//             case S12: // si pas de ; erreur
//
//                     if(  ((*it).get_valeur())!= ";" )
//                          {
//                            count++;
//                                line_index_error= (*it).get_line_index();
//                                       cout << "Error found on line:  " <<line_index_error<<'\n';
//                          }
//
//                       it++;
//                       next_state= S16;// ; suivie d'identifiant ou de }
//                       break;
//
//             case S13:
//                     if( (*it).get_valeur()!=">" )
//                    {
//                      count++;
//                          line_index_error= (*it).get_line_index();
//                                 cout << "Error found on line:  " <<line_index_error<<'\n';
//                    }
//
//                   it++;
//                   next_state=S14;
//                   break;
//
//             case S14:
//                       if( (*it).get_nature()!=identifiant )
//                      {
//                        count++;
//                            line_index_error= (*it).get_line_index();
//                                   cout << "Error found on line:  " <<line_index_error<<'\n';
//                      }
//
//                       it++;
//                       next_state=S15;
//                       break;
//
//               case S15:
//               // 2 possibilités à gerer
//                         if( (*it).get_valeur()=="-"  || (*it).get_valeur()==";" )
//                        {
//                          if( (*it).get_valeur()=="-" )
//                               {
//                                 next_state=S13;
//                               }
//
//                         else if( (*it).get_valeur()==";" )
//                              {
//                                next_state=S16;// identifiant ou }
//                              }
//                        }
//                        else
//                             {
//                               count++;
//                                   line_index_error= (*it).get_line_index();
//                                          cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=WAIT;
//                             }
//                       it++;
//                       break;
//
//               case S16:
//                         if( (*it).get_valeur()=="}"  || (*it).get_nature()==identifiant)
//                        {
//                              if( (*it).get_valeur()=="}")
//                                   {
//                                     next_state=NULL_STATE;
//                                   }
//
//                             else if( (*it).get_nature()==identifiant )
//                                  {
//                                    next_state=S5;// identifiant ou }
//                                  }
//                        }
//                        else
//                             {
//                               count++;
//                                   line_index_error= (*it).get_line_index();
//                                          cout << "Error found on line:  " <<line_index_error<<'\n';
//                               next_state=WAIT;
//                             }
//                       it++;
//                       break;
//
//           case WAIT:
//              if( (*it).get_valeur()=="label" )
//                  {
//                    next_state=S7;
//                  }
//              else if( (*it).get_nature()==identifiant )
//                  {
//                    next_state=S5;
//                  }
//              else if( (*it).get_valeur()==">" )
//                  {
//                    next_state=S14;
//                  }
//             else if( (*it).get_valeur()=="}" )
//                      {
//                        next_state=NULL_STATE;
//                      }
//             // else if( (*it).get_valeur()=="=" )
//             //         {
//             //         next_state=S8;
//             //         }
//             // else if( (*it).get_valeur()=="]" )
//             //     {
//             //     next_state=S12;
//             //     }
//             else {
//               next_state= WAIT;
//             }
//             it++;
//             break;
//
//             default:   cout << "erreur de FSM " <<'\n';
//               next_state=WAIT;
//               break;
//
//
//
//                 }// fermeture du case
//
//             }// fermeture du while
//           cout<<"Fin de verification "<< endl;
//
//
//           }// fermeture du while
