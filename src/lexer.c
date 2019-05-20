#include "yalg/lexer.h"

// Token

Token *Token_alloc(TokenType type) {
  Token *tok = (Token*) malloc(sizeof(Token));
  if (!tok) return NULL;

  tok->type = type;

  return tok;
}

void Token_free(Token *tok) {
	switch(tok->type) {
		case TOK_ID:
		case TOK_STR:
			free(tok->value.str);
			break;
		default:
	}

  free(tok);
}

Token *Token_copy(Token *tok) {
  Token *result = Token_alloc(tok->type);
  if (!result) return NULL;

  switch (tok->type) {
    case TOK_ID:
    case TOK_STR:
      result->value.str = strcpy(tok->value.str);
      if (!result->value.str) {
        free(result);
        return NULL;
      }

      break;
    case TOK_CH:
      result->value.ch = strcpy(tok->value.ch);
      break;
    default:
  }

  return result;
}

// Lexer

Token *Lexer_next(Lexer *lex) {
  switch (lex->value.ch) {
    case '[':
    case '"':
    case '\'':
    case '{':
    default:
  }

  if (isalpha(lex)) {

  }
}
