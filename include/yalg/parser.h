#ifndef YALG_PARSER_H
#define YALG_PARSER_H

#include "yalg/global.h"
#include "yalg/lexer.h"

#define EXPR_PROGRAM      0
#define EXPR_DEFS         1
#define EXPR_DEF          2
#define EXPR_TOKS         3
#define EXPR_ID           4
#define EXPR_REGEX        5
#define EXPR_EXPR0        6
#define EXPR_EXPR1        7
#define EXPR_ATOM         8
#define EXPR_RANGE        9
#define EXPR_VAR         10
#define EXPR_RANGE_CHARS 11
#define EXPR_RANGE_UNIT  12

typedef struct {
	uint32_t type;
} Expr;

#endif /* YALG_PARSER_H */

