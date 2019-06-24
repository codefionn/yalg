#include "yalg/global.h"
#include "yalg/lexer.h"

int main(int argsc, char * argsv[]) {
  if (argsc != 1 + 2) {
    fprintf(stderr, "Expected: %s (file|text) str\n", argsv[0]);
    return EXIT_FAILURE;
  }

  const bool IsFile = !strcmp(argsv[1], "file");
  if (IsFile) {
    FILE *input = fopen(argsv[2], "r");
    if (!input) {
      fprintf(stderr, "Error: Cannot open file for reading.");
      return EXIT_FAILURE;
    }

    Lexer lex;
    Lexer_init(&lex, input); // initialize lexer

    Token *tok;
    while ((tok = Lexer_next(&lex)) && tok->type != TOK_EOF) {
      if (tok->type > 127)
        printf("%d\n", tok->type);
      else
        printf("%c\n", (char)tok->type);
    }

    Lexer_free(&lex);
    fclose(input); // close file stream

    if (!tok) {
      fprintf(stderr, "Error: Memory error occured during lexical analysis.");
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  FILE *stream = fopen("test.txt", "w");
  if (!stream) {
    fprintf(stderr, "Error: Cannot open tmp file for writing.");
    return EXIT_FAILURE;
  }
  // write to file
  fputs(argsv[2], stream);
  // fluse
  fflush(stream);
  // reopen as read-only
  stream = freopen("test.txt", "r", stream);
  if (!stream) {
    fprintf(stderr, "Error: Cannot reopen tmp file for reading.");
    return EXIT_FAILURE;
  }

  Lexer lex;
  Lexer_init(&lex, stream);

  Token *tok;
  while ((tok = Lexer_next(&lex)) && tok->type != TOK_EOF) {
    if (tok->type > 127)
      printf("%d\n", tok->type);
    else
      printf("%c\n", (char)tok->type);
  }

  Lexer_free(&lex);
  fclose(stream);

  if (!tok) {
    fprintf(stderr, "Error: Memory error occured during lexical analysis.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
