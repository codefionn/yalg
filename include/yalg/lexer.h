#ifndef YALG_LEXER_H
#define YALG_LEXER_H

#ifdef __cplusplus
extern "C" {
#endif

/*!\file yalg/lexer.h
 * \brief Lexical analysis/tokenizer
 */

#include "yalg/global.h"

typedef int32_t TokenType;

#define  TOK_EOF     EOF     //!< End-of-line
#define  TOK_ID      256     //!< identifier
#define  TOK_NEWLINE 259     //!< newline
#define  TOK_SECTION 260     //!< '%%'
#define  TOK_SPACE   261     //!< space(s)
#define  TOK_NUM     262     //!< Reserved in case ...

#define TOK_REGEXO   263     //!< '(' for beginning secondary regex expr
#define TOK_REGEXC   264     //!< ')' for closing secondary regex expr
#define TOK_RANGEO   265     //!< '[' for beginning range expr
#define TOK_RANGEC   266     //!< ']' for ending range expr
#define TOK_VARO     267     //!< '{' for beginning variable expr
#define TOK_VARC     268     //!< '}' for ending variable expr

#define TOK_MUL      269     //!< * for zero or multiple occurrences
#define TOK_ADD      270     //!< + for one or more occurences
#define TOK_OR       271     //!< | for LHS or RHS case.
 
#define  TOK_ERR     300     //!< Token value reserved for errors

typedef struct {
  TokenType type; //!< Type of the token
  union {
	  char * str;   //!< String value TOK_ID, TOK_NUM
  } value;
} Token;

/*!\brief Allocate token.
 * \param type Type of the Token to allocate
 * \return Returns NULL if failed to dynamically allocate storage, otherwise
 * not NULL (reference to memory segment).
 */
Token *Token_alloc(TokenType type, void *userdata);

/*!\brief Frees memory allocated by tok
 * \param tok Memory to free
 */
void Token_free(Token *tok);

/*!\param tok Token to copy
 * \return Returns copied token tok. If dynamic allocation failed NULL.
 */
Token *Token_copy(Token *tok);

typedef struct {
  FILE *input;    //!< Input stream

  int ch;         //!< Current character 0-255, EOF
  Token *tok;     //!< Current token

  size_t line;    //!< Current line number. Starting from 0.
} Lexer;

/*!\brief Initializes lexer. Read-operation on input.
 * \param lex
 * \return Returns true on success otherwise false.
 */
bool Lexer_init(Lexer *lex, FILE *input);

/*!\brief Read next token.
 */
Token *Lexer_next(Lexer *lex);

#ifdef __cplusplus
}
#endif

#endif /* YALG_LEXER_H */
