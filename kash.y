%{
#include "stdio.h"
#include "include/alias.h"

#define YYDEBUG 1

extern int linenum;
extern int charnum;

int yylex(void);
void yyerror(const char *str)
{
    fprintf(stderr, "Error: %s, at line %d, char %d\n", str, linenum, charnum);
}

extern FILE *yyin;
%}

%union {
    int ival;
    char* string;
}

%start start
%type <string> word

%type <string> tALIAS
%token tALIAS "alias"
%type <string> tUNALIAS
%token tUNALIAS "unalias"
%type <string> tWORD
%token tWORD
%token tBYE
%token tNEWLINE

%%

start: command_list

command_list: command
    | command_list tNEWLINE command

command:
    tBYE { exit(0); }
    | tALIAS { print_aliases(); }
    | tALIAS word word {
        char* args = $2; char* arg2 = $3;
        int diff = arg2-args; char arg1[diff];
        strncpy(arg1, args, diff);
        arg1[diff-1] = '\0';
        alias(arg1, arg2);
      }
    | tUNALIAS word {
        unalias($2);
      }

word:
    tWORD

%%
