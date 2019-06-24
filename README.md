# yalg

Yet another lexer generator parses a lexer specification to C++ code.

## Lexer specification language

### BNF

*newline* is one or more line-feed or carriage-return characters. *cpp-code* is
C++-code. *newline* *newline* means at least two consecutive newline
characters. Text between two ' is literal. A single dot . represents all
bytes possible except byte representation of ' '.

> space := spacechar | spacechar space\
> spacechar := ' ' | horizontaltab\
> id := letter | letter id\
> letter := 'A' | ... | 'Z' | 'a' | ... | 'z'

> program := code '%%' defs '%%' toks\
> code := cpp-code\
> defs := def | def newline defs\
> def := id space regex\
> toks := tok | tok newline toks\
> tok := id space regex space '{' cpp-code-tok newline '}'\
> cpp-code-tok := cpp-code\
> regex := expr1 | regex '|' expr1 \
> expr0 := expr1 '*' | expr1 '+'\
> expr1 := atom | atom expr1\
> atom := range | var | .\
> range := '[' range-chars ']'\
> range-chars := range-unit | range-unit range-chars\
> range-unit := . '-' . | ' -' . | . '- ' | .\
> var := '{' id '}'

### Basic Interpretation

Let *Var* be a set consisting of all definitions and tokens, *Expr* an array
consisting of all tokens (the array start with index 0). I\[*x*\] is a function
for interpreting defined expression in *BNF*.

> I[program] = I[defs '%%' toks] = I[defs]; I[toks]

> I[defs] = I[def | def newline defs] = I[def] | I[def]; I[defs]

> I[def] = I[id space regex] = Var := Var AND x, where x has name *id* and match *regex*

> I[toks] = I[tok | tok newline toks] = I[tok] | I[tok]; I[toks]

> I[tok] = I[id space regex space '{' cpp-code newline '}'] =\
> Var := Var AND x, where x has name *id* and match *regex*;

> Expr[Expr.length] := y, where y has name *id*, match *regex* and attached
> code *cpp-code*

## Constraints

Every identifier *id* must contain less than 256 characters.
