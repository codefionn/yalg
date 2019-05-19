#include "yalg/lexer.h"

void Token_free(Token *tok) {
	switch(tok->type) {
		case TOK_ID:
		case TOK_STR:
			free(tok->value.str);
			break;
		default:
	};


}
