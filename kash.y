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
    command_list_t* cmdlistval;
    outfile_t* outfileval;
}

%start start
%type <string> word
%type <string> arg
%type <arglistval> arglist
%type <arglistval> arglist_ety
%type <string> infile_ety
%type <outfileval> outfile_ety
%type <string> stderr_ety
%type <cmdval> cmd
%type <cmdlistval> cmd_list_ety
%type <cmdlistval> cmd_list

%type <string> tWORD
%token tWORD
%token FILEIN FILEOUT
%token PIPE 
%token tNEWLINE
%token AMPERSAND
%token STDERRTOK
%token STDOUTAPP

%%

start: command_list

command_list: command
    | command_list tNEWLINE command
    ;

command:
    cmd_list_ety infile_ety outfile_ety  stderr_ety {
        kash_exec($1, $2, $3, $4);
      }
    ;

cmd_list_ety: /* empty */ { $$ = NULL; }
    | cmd_list { $$ = $1; }
    ;

cmd_list:
    cmd { $$ = make_command_list($1, NULL); }
    | cmd_list PIPE cmd {
        $$ = make_command_list($3, $1);
      }
    ;

cmd:
    word arglist_ety {
        $$ = make_command($1, arglist_to_strings($2));
      }
    ;
    

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

infile_ety: /* empty */ { $$ = NULL; }
    | FILEIN word {
        $$ = $2;
      }

outfile_ety: /* empty */ { $$ = NULL; }
    | FILEOUT word {
        $$ = make_outfile($2, 0);
      }
    | STDOUTAPP word {
        $$ = make_outfile($2, 1);
      }
    ;

stderr_ety: /* empty */ { $$ = NULL; }
    | STDERRTOK word {
        $$ = $2;
      }
    | STDERRTOK AMPERSAND "1" {
        $$ = "&1";
      }

word:
    tWORD {
      int strsize = strlen($1) + 1;
      char *w = malloc(sizeof(char) * strlen($1) + 1);
      assert(w != NULL);
      strcpy(w, $1);
      w[strsize] = '\0';
      $$ = w;
    }
    ;

%%
