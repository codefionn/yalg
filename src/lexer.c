#include "yalg/lexer.h"

// Token

Token *Token_alloc(TokenType type, void *userdata) {
  Token *tok = (Token*) malloc(sizeof(Token));
  if (!tok) return NULL;

  tok->type = type;

  if (type == TOK_ID, TOK_VAR)
    tok->value.str = (char*) userdata;

  return tok;
}

void Token_free(Token *tok) {
	switch(tok->type) {
		case TOK_ID:
		case TOK_VAR:
      if (tok->value.str) free(tok->value.str); // safe deletion
			break;
		default:
	}

  free(tok);
}

Token *Token_copy(Token *tok) {
  switch (tok->type) {
    case TOK_ID:
    case TOK_STR:
    case TOK_NUM:
      return 
  }
}

// Lexer

bool Lexer_init(Lexer *lex, FILE *input) {
  lex->input = input;

  // Improve sanity.
  lex->tok = Token_alloc(TOK_EOF, NULL);
  if (!tok)
    return false;

  lex->ch = fgetc(input);
  lex->line = 0;

  return true;
}

/*!\return Returns NULL on failure, otherwise a valid token,
 * which is either toktype or TOKE_ERR (if at least *max* characters were read).
 * \param lex
 * \param toktype Which token type the function should have. Not TOK_ERR.
 * \param max Maximum valid characters. Minimum: 1.
 * \param validch As long as validch(lex->ch) returns true, the funciton
 * advances to the next character.
 */
static Token *_Lexer_next_fn(Lexer *lex,
    TokenType toktype, const size_t max,
    bool (*)(int ch) validch) {
  // free last stored token
  Token_free(lex->tok);
  // allocate string
  char str[max]; memset(str, 0, sizeof(char)); size_t pos = 0;
  // Read characters as long as validch returns true. 
  // Write them to str as long as toktype IS NOT TOK_ERR.
  // Switch toktype to TOK_ERR if pos >= max.
  while (validch(lex->ch)) {
    if (toktype != TOK_ERR) {
      str[pos++] = lex->ch; // write to result char. advance to next pos.

      if (pos == max)      // check error condition
        toktype = TOK_ERR; // too many characters
    }

    lex->ch = fgetc(lex->input); // advance to next characters
  }

  if (toktype == TOK_ERR)
    return Token_alloc(TOK_ERR, NULL);

  // allocate cpy, because Token_alloc needs dynamically allocated C-string
  char * cpy = (char*) malloc(strlen(str) * sizeof(char));
  strcpy(cpy, str); // copy str to cpy
  // allocate result token
  Token *result = Token_alloc(toktype, cpy);
  if (!result) {
    free(cpy);
    return NULL;
  }

  return result;
}

Token *Lexer_next(Lexer *lex) {
  switch (lex->value.ch) {
    case '"':
    case '\'':
    case '{':
      // either CPP-Code or VAR
      lex->ch = fgetc(lex->input);
      if (lex->ch == '\n') {
        // cpp-code
      } else {
        // variable
        Token *result = _Lexer_next_fn(lex, TOK_VAR, 256, isalpha);
        if (!result)
          return NULL;
        // check result->value.str.length > 0
        if (!result->value.str) {
          Token_free(result);
          fprintf(stderr, "error:%u: Empty variable!\n",
              (unsigned int) result->line + 1);
          return Token_alloc(TOK_ERR, NULL);
        }

        return result;
      }
    default:
  }
  // identifier
  if (isalpha(lex))
    return  _Lexer_next_fn(lex, TOK_ID, 256, isalpha);

  // Return character
  Token *result = Token_alloc(lex->ch);
  if (!result)
    return NULL;
  // eat current character
  lex->ch = fgetc(lex->input);
  // return result
  return result;
}
