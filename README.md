# yalg

Yet another lexer generator parses a lexer specification to C++ code.

## Lexer specification language

*newline* is one or more line-feed or carriage-return characters. *cpp-code* is
C++-code. *newline* *newline* means at least two consecutive newline
characters.

> program := header newline matches EOF

> header := project newline tokenids newline definitions newline program\
> project := **!program** newline id\
> tokenids := **!tokenids** newline ids\
> ids := id | id newline ids\
> definitions := **!definitions** newline newline defs\
> defs := def | def newline defs\
> def := id regex\
> program := **!program** newline cpp-code

> matches := match | match newline newline matches\
> match := regex **{** cpp-code **}**\
> regex := base | base **+** | base **\*** | base **?**\
> base := literal | range | definition | **{**id**}**\
> literal := [a-zA-Z0-9] | **.** | escaped | str\
> escaped := **\\n** | **\\r**\
> str := **\"**([^"]|\\\")\***\"**\
> range := **[**rangechars**]** | **[^**rangechars**]**\
> rangechars := ANY | ANY**-**ANY

The *regex* and *cpp-code* block in *match* are seperated by spaces. So spaces
in the regex expression are not allowed, when they must be used, ``[  ]``
should be used.

The ``!.*`` must be right after the newline character(s).

All newlines are automatically converted to unix newlines (line-feed).
