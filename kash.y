%{
#include "stdio.h"
#include "include/kash.h"

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
    arg_t* argval;
    arglist_t* arglistval;
    command_t* cmdval;
}

%start start
%type <string> word
%type <string> arg;
%type <arglistval> arglist;
%type <arglistval> arglist_ety;
%type <cmdval> cmd;

%type <string> tALIAS
%token tALIAS "alias"
%type <string> tUNALIAS
%token tUNALIAS "unalias"
%type <string> tWORD
%token tWORD
%token tBYE
%token tNEWLINE
%token tPRINTENV
%token tPWD
%token tSETENV

%%

start: command_list

command_list: command
    | command_list tNEWLINE command
    ;

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
    | tPRINTENV {
        print_env();
      }
    | tSETENV word {
        set_env($2);
      }
    | cmd {
        print_command($1);
      }
    ;

cmd:
    word arglist_ety {
        $$ = make_command($1, arglist_to_strings($2), NULL, NULL);
      }

arglist_ety: /* empty */ { $$ = make_arglist(NULL, NULL); }
    | arglist {
        $$ = $1;
      }
    ;

arglist:
    arg {
        $$ = make_arglist($1, NULL);
      }
    | arglist arg {
        $$ = make_arglist($2, $1);
      }
    ;

arg:
    word {
      $$ = make_arg($1);
    }
    ;

word:
    tWORD {
      $$ = $1;
    }
    ;

%%
