// Copyright (c) 2018-2019 Roland Bernard

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "./number.h"
#include "./string.h"
#include "./operation.h"

typedef enum token_type_e {
        TOKEN_TYPE_START,
        TOKEN_TYPE_END,
        TOKEN_TYPE_NUM,
        TOKEN_TYPE_STR,
        TOKEN_TYPE_VAR,
        TOKEN_TYPE_NONE,
        TOKEN_TYPE_OPEN_BRAC,
        TOKEN_TYPE_CLOSE_BRAC,
        TOKEN_TYPE_OPEN_CUR,
        TOKEN_TYPE_CLOSE_CUR,
        TOKEN_TYPE_OPEN_REC,
        TOKEN_TYPE_CLOSE_REC,
        TOKEN_TYPE_ABS,
        TOKEN_TYPE_ASSIGN,
        TOKEN_TYPE_EQU,
        TOKEN_TYPE_GTR,
        TOKEN_TYPE_LES,
        TOKEN_TYPE_GEQ,
        TOKEN_TYPE_LEQ,
        TOKEN_TYPE_DO,
        TOKEN_TYPE_THEN,
        TOKEN_TYPE_ARROW,
        TOKEN_TYPE_WHILE,
        TOKEN_TYPE_IF,
        TOKEN_TYPE_ELSE,
        TOKEN_TYPE_SEMICOL,
        TOKEN_TYPE_COMMA,
        TOKEN_TYPE_DOT,
        TOKEN_TYPE_MINUS,
        TOKEN_TYPE_PLUS,
        TOKEN_TYPE_MUL,
        TOKEN_TYPE_DIV,
        TOKEN_TYPE_POW,
        TOKEN_TYPE_MOD,
        TOKEN_TYPE_BOOL,
        TOKEN_TYPE_PAIR,
        TOKEN_TYPE_DEF,
        TOKEN_TYPE_STRUCT,
        TOKEN_TYPE_TO_NUM,
        TOKEN_TYPE_TO_STR,
        TOKEN_TYPE_TO_BOOL,
        TOKEN_TYPE_TO_ASCII,
        TOKEN_TYPE_READ,
        TOKEN_TYPE_WRITE,
        TOKEN_TYPE_AND,
        TOKEN_TYPE_OR,
        TOKEN_TYPE_XOR,
        TOKEN_TYPE_NOT,
        TOKEN_TYPE_SQRT,
        TOKEN_TYPE_CBRT,
        TOKEN_TYPE_SIN,
        TOKEN_TYPE_COS,
        TOKEN_TYPE_TAN,
        TOKEN_TYPE_ASIN,
        TOKEN_TYPE_ACOS,
        TOKEN_TYPE_ATAN,
        TOKEN_TYPE_SINH,
        TOKEN_TYPE_COSH,
        TOKEN_TYPE_TANH,
        TOKEN_TYPE_ASINH,
        TOKEN_TYPE_ACOSH,
        TOKEN_TYPE_ATANH,
        TOKEN_TYPE_TRUNC,
        TOKEN_TYPE_FLOOR,
        TOKEN_TYPE_CEIL,
        TOKEN_TYPE_ROUND,
        TOKEN_TYPE_RAND,
        TOKEN_TYPE_LEN,
        TOKEN_TYPE_DIC,
        TOKEN_TYPE_FIND,
        TOKEN_TYPE_SPLIT,
        TOKEN_TYPE_EXP,
        TOKEN_TYPE_LOCAL,
        TOKEN_TYPE_GLOBAL,
        TOKEN_TYPE_COPY,
        TOKEN_TYPE_FOR,
        TOKEN_TYPE_BACKSLASH,
        TOKEN_TYPE_IN,
        TOKEN_TYPE_IMPORT,
        TOKEN_TYPE_FOPEN,
        TOKEN_TYPE_FCLOSE,
        TOKEN_TYPE_FWRITE,
        TOKEN_TYPE_FREAD,
} token_type_t;

typedef struct token_s {
    token_type_t type;
    union {
        string_t* str;
        number_t num;
        bool_t boolean;
        operation_t* op;
    } data;
    struct token_s* next;
} token_t;

token_t* token_create();

#endif
