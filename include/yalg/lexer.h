#ifndef YALG_LEXER_H
#define YALG_LEXER_H

/*!\file yalg/lexer.h
 * \brief Lexical analysis/tokenizer
 */

#include "yalg/global.h"

typedef uint32_t TokenType;

#define  TOK_ID      256,     //!< identifier
#define  TOK_STR     257,     //!< string (C++)
#define  TOK_CHAR    258,     //!< character (C++)
#define  TOK_NEWLINE 259,     //!< newline
  
#define  TOK_ERR     300,     //!< Token value reserved for errors

typedef struct {
  TokenType type; //!< Type of the token
  union value {
	  char ch;      //!< Character value TOK_CHAR
	  char * str;   //!< String value TOK_ID, TOK_STR
  };
} Token;

/*!\brief Allocate token.
 * \param type Type of the Token to allocate
 * \return Returns NULL if failed to dynamically allocate storage, otherwise
 * not NULL (reference to memory segment).
 */
Token *Token_alloc(TokenType type);

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

  char ch;        //!< Current character
  Token *tok;     //!< Current token

  size_t line;    //!< Current line number
} Lexer;

/*!\brief Initializes lexer. Read-operation on input.
 * \param lex
 */
void Lexer_init(Lexer *lex);

/*!\brief Read next token.
 */
Token *Lexer_next(Lexer *lex);

#endif /* YALG_LEXER_H */
