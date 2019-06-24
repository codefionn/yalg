# yalg

Yet another lexer generator parses a lexer specification to C++ code.

## Lexer specification language

### BNF

*newline* is one or more line-feed or carriage-return characters. *newline*
*newline* means at least two consecutive newline characters. Text between two '
is literal. A single dot . represents all bytes possible except ' ', '*',
'+' and '\\'.

> space := spacechar | spacechar space\
> spacechar := ' ' | horizontaltab\
> id := letter | letter id\
> letter := 'A' | ... | 'Z' | 'a' | ... | 'z'\
> char := . | '\' escape-char\
> escape-char := 'n' | 'r' | 't' | '+' | '*' | ' ' | .

> program := defs '%%' toks\
> defs := def | def newline defs\
> def := id space regex\
> toks := defs
> regex := expr1 | regex '|' expr1 | '(' regex ')' \
> expr0 := expr1 '*' | expr1 '+'\
> expr1 := atom | atom expr1\
> atom := range | var | .\
> range := '[' range-chars ']'\
> range-chars := range-unit | range-unit range-chars\
> range-unit := escape-char '-' escape-char | ' -' escape-char | escape-char '- ' | escape-char\
> var := '{' id '}'

### Basic Interpretation

Let *Var* be a set consisting of all definitions and tokens, *Expr* an array
consisting of all tokens (the array start with index 0). I\[*x*\] is a function
for interpreting defined expression in *BNF*.

> I[program] = I[defs '%%' toks] = I[defs]; I[toks]

> I[defs] = I[def | def newline defs] = I[def] | I[def]; I[defs]

> I[def] = I[id space regex] =
> Var = Var AND x, where x has name *id* and match *regex*

> I[toks] = I1[def | def newline defs] = I1[def] | I1[def]; I1[defs]

> I1[def] = I[id space regex] =\
> { Var = Var AND x, \
> Expr[Expr.length] := x, where x has name *id* and match *regex* } \

## Constraints

Every identifier *id* must contain less than 256 characters.
