# yalg

Yet another lexer generator parses a lexer specification to C++ code.

## Lexer specification language

*newline* is one or more line-feed or carriage-return characters. *cpp-code* is
C++-code.

> program := header newline matches EOF

> header := project newline tokenids newline definitions newline program\
> project := **!program** newline id\
> tokenids := **!tokenids** newline ids\
> ids := id | id newline ids\
> definitions := **!definitions** newline defs\
> defs := def | def newline defs\
> def := id regex\
> program := **!program** newline cpp-code

> matches := match | match newline matches\
> match := regex **{** cpp-code **}**\
> regex := base | base **+** | base **\*** | base **?**\
> base := literal | range | definition\
> literal := [a-zA-Z0-9] | **.** | escaped | str\
> escaped := **\\n** | **\\r**\
> str := **\"**([^"]|\\\")\***\"**\
> range := **[**rangechars**]** | **[^**rangechars**]**\
> rangechars := ANY | ANY**-**ANY
