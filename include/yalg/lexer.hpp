#ifndef YALG_LEXER_HPP
#define YALG_LEXER_HPP

/*!\file yalg/lexer.hpp
 * \brief Lexical analysis/tokenizer
 */

#include "yalg/global.hpp"

namespace yalg {
  typedef uint32_t TokenType;

#define  TOK_ID      256,     //!< identifier
#define  TOK_STR     257,     //!< string (C++)
#define  TOK_CHAR    258,     //!< character (C++)
#define  TOK_NEWLINE 259,     //!< newline
  
#define  TOK_ERR     300,     //!< Token value reserved for errors

  struct Token {
	  TokenType type;
	  union value {
		  char ch;
		  char * str;
	  };
  };

  /*!\brief Frees memory allocated by tok
   */
  void Token_free(Token *tok);
}

#endif /* YALG_LEXER_HPP */
