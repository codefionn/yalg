#include "yalg/lexer.h"

// Token

Token *Token_alloc(TokenType type, void *userdata) {
  Token *tok = (Token*) malloc(sizeof(Token));
  if (!tok) return NULL;

  tok->type = type;

  if (type == TOK_ID || type == TOK_NUM)
    tok->value.str = (char*) userdata;

  return tok;
}

void Token_free(Token *tok) {
	switch(tok->type) {
		case TOK_ID:
    case TOK_NUM:
      if (tok->value.str) free(tok->value.str); // safe deletion
			break;
		default:
      break;
	}

  free(tok);
}

Token *Token_copy(Token *tok) {
  switch (tok->type) {
    case TOK_ID:
    case TOK_NUM: {
      const size_t len = strlen(tok->value.str) * sizeof(char);
      char *cpy = (char*) malloc(len);
      if (!cpy)
        return NULL;
      else {
        memcpy(cpy, tok->value.str, len);
        Token *result = Token_alloc(tok->type, cpy);
        if (!result) { // if alloc failed, cleanup
          free(cpy);
          return NULL;
        } else
          return result;
      }
    }
    default:
      return Token_alloc(tok->type, NULL);
  }
}

// Lexer

bool Lexer_init(Lexer *lex, FILE *input) {
  lex->input = input;

  // Improve sanity.
  lex->tok = Token_alloc(TOK_EOF, NULL);
  if (!(lex->tok))
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
    int (*validch)(int ch)) {
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
    return lex->tok = Token_alloc(TOK_ERR, NULL);

  // allocate cpy, because Token_alloc needs dynamically allocated C-string
  char * cpy = (char*) malloc(strlen(str) * sizeof(char));
  strcpy(cpy, str); // copy str to cpy
  // allocate result token
  Token *result = Token_alloc(toktype, cpy);
  if (!result) {
    free(cpy);
    return NULL;
  }

  return lex->tok = result;
}

static int _isspace(int ch) {
  switch(ch) {
  case ' ':
  case '\t':
    return true;
  default:
    return false;
  }
}

static Token *_Lexer_next_fn_null(Lexer *lex,
    TokenType toktype, int (*validch)(int ch)) {
  while (validch(lex->ch)) lex->ch = fgetc(lex->input);
  return Token_alloc(toktype, NULL);
}

#define TOK_CHARS_MAX 256

Token *Lexer_next(Lexer *lex) {
  // ignored characters
  switch(lex->ch) {
    case '\r':
      lex->ch = fgetc(lex->input); // eat
      return Lexer_next(lex);
  }
  // free lex->tok
  Token_free(lex->tok); lex->tok = NULL;
  // simple characters/escape sequence
  switch (lex->ch) {
    case '\\': {
      // Escaped character
      int tmp = fgetc(lex->input); // eat
      // catch EOF
      if (tmp == EOF)
        return lex->tok = Token_alloc(lex->ch = TOK_EOF, NULL);
      lex->ch = fgetc(lex->input); // eat
      switch (tmp) {
        case 'n':
          return Token_alloc('\n', NULL);
        case 't':
          return Token_alloc('\t', NULL);
        case 'r':
          return Token_alloc('\r', NULL);
        case '\n':
          ++(lex->line);
        default:
          return Token_alloc(tmp, NULL);
      }
    }
    case '\n':
      // newline
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_NEWLINE, NULL);
    case '%':
      // single % or TOK_SECTION
      lex->ch = fgetc(lex->input); // eat
      switch (lex->ch) {
        case '%':
          lex->ch = fgetc(lex->input); // eat
          return Token_alloc(TOK_SECTION, NULL);
        default:
          return Token_alloc('%', NULL);
      }
    case '(':
      // secondary regex expression
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_REGEXO, NULL);
    case ')':
      // secondary regex expression
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_REGEXC, NULL);
    case '[':
      // range expression
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_RANGEO, NULL);
    case ']':
      // range expression
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_RANGEC, NULL);
    case '{':
      // variable
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_VARO, NULL);
    case '}':
      // variable
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_VARC, NULL);
    case '+':
      // TOK_ADD
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_ADD, NULL);
    case '*':
      // TOK_MUL
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_MUL, NULL);
    case '|':
      // TOK_OR
      lex->ch = fgetc(lex->input); // eat
      return Token_alloc(TOK_OR, NULL); 
  }
  // TOK_ID
  if (isalpha(lex->ch))
    return _Lexer_next_fn(lex, TOK_ID, TOK_CHARS_MAX, isalpha);
  // TOK_SPACE
  if (_isspace(lex->ch))
    return _Lexer_next_fn_null(lex, TOK_SPACE, _isspace);
  // all other characters and EOF
  int tmp = lex->ch;
  lex->ch = fgetc(lex->input);
  return Token_alloc(tmp, NULL);
}

#undef TOK_CHARS_MAX
