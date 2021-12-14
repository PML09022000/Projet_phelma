#ifndef _LEXER_H_
#define _LEXER_H_

#include "symbole.h"
#include "symbole_json.h"

vector<Symbole> lexeme(vector<string> &txt_line_vector);
vector<Symbole_json> lexeme_json(vector<string> &txt_line_vector);

#endif
