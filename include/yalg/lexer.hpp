#ifndef YALG_LEXER_HPP
#define YALG_LEXER_HPP

/*!\file yalg/lexer.hpp
 * \brief Lexical analysis/tokenizer
 */

#include "yalg/global.hpp"

namespace yalg {
  enum TokenType : uint32_t {
    TOK_ID = 256,      //!< identifier
    TOK_STR,           //!< string (C++)
    TOK_CHAR,          //!< character (C++)
    TOK_NEWLINE,       //!< newline
TOK_ERR,           //!< Token value reserved for errors
  };

  class Token {
    TokenType m_type;
    
    char m_valChar;
    std::string m_valStr;
  public:
    Token() noexcept
      : m_type{TOK_ERR}, m_valChar{'\0'}, m_valStr() {}
    Token(char c) noexcept
      : m_type{TOK_CHAR}, m_valChar{m_char}, m_valStr() {}
    Token(const std::string &str) noexcept
      : m_type{TOK_STR}, m_valChar{'\0'}, m_valStr(str) {}
    //! (Deep-) copy-constructor
    Token(const Token &tok) noexcept
      : m_type{tok.type()}, m_valChar{'\0'}, m_valStr() {}
    virtual ~Token() {}

    /*!\return Returns token key/type.
     */
    TokenType type() const noexcept { return m_type; }

    /*!\return Returns character token value. Only valid if 
     *     type() == TOK_CHAR
     */
    char ch() const noexcept { return m_valChar; }

    /*!\return Returns string token value. Only valid if
     *     type() == TOK_STRING``
     */
    const std::string &str() const noexcept { return m_valStr; }
  };

  class Tokenizer {
    Token m_tok;

    //! Stores the current line
    std::string m_currentLine;
    //! Stores lines which are already fully read
    std::vector<std::string> m_lines;

    std::istream &m_input;
  public:
    Tokenizer(std::istream &input)
      : m_input{input}, m_tok(), m_lines() noexcept {}
    virtual ~Tokenizer() {}

    /*!\return Returns input stream of tokenizer.
     */
    std::istream &input() noexcept { return m_input; }

    /*!\return Returns current token.
     * eat must be called at least one time beforehand.
     */
    const Token &token() const noexcept { return m_tok; }

    /*!\return Returns next token following the current one.
     */
    const Token &eat() noexcept;
  };
}

#endif /* YALG_LEXER_HPP */
