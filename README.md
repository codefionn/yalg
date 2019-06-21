# yalg

Yet another lexer generator parses a lexer specification to C++ code.

## Lexer specification language

*newline* is one or more line-feed or carriage-return characters. *cpp-code* is
C++-code. *newline* *newline* means at least two consecutive newline
characters. Text between two ' is literal. A single dot . represents all
bytes possible except byte representation of ' '.

> space := spacechar | spacechar space\
> spacechar := ' ' | horizontaltab
> id := letter | letter id\
> letter := 'A' | ... | 'Z' | 'a' | ... | 'z'

> program := defs '%%' toks\
> defs := def | def newline defs\
> def := id space regex\
> toks := tok | tok newline toks\
> tok := id space regex '{' cpp-code '}'\
> | id space regex space '{' cpp-code '}'\
> regex := expr1 | regex '|' expr1 \
> expr0 := expr1 '*' | expr1 '+'\
> expr1 := atom | atom expr1\
> atom := range | var | .\
> range := '[' range-chars ']'\
> range-chars := range-unit | range-unit range-chars\
> range-unit := . '-' . | ' -' . | . '- ' | .\
> var := '{' id '}'\
