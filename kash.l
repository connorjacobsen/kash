%{
#include <stdio.h>
#include <stdlib.h>

#include "include/kash.h"
%}

%option noyywrap
%option yylineno

%%

"<"  { printf("(meta %s %u)\n", yytext, yylineno); }
">"  { printf("(meta %s %u)\n", yytext, yylineno); }
"|"  { printf("(meta %s %u)\n", yytext, yylineno); }
"&"  { printf("(meta %s %u)\n", yytext, yylineno); }
"\\" { printf("(meta %s %u)\n", yytext, yylineno); }
\"   { printf("(meta %s %u)\n", yytext, yylineno); }

 /* reserved words */
"setenv" { printf("(setenv %u)\n", yylineno); }
"printenv" { printf("(printenv %u)\n", yylineno); }
"unsetenv" { printf("(unsetenv %u)\n", yylineno); }
"cd" { printf("(cd %u)\n", yylineno); }
"alias" { printf("(alias %u)\n", yylineno); }
"unalias" { printf("(unalias %u)\n", yylineno); }
"bye" { printf("(bye %u)\n", yylineno); }

\"([^\\\"]|\\.)*\" { printf("(word %s %u)\n", yytext, yylineno); }
[^ \t\n<<EOF>>]*   { printf("(word %s %u)\n", yytext, yylineno); }

[ \t\n]   {}
.       { printf("I got nothing.\n"); }

<<EOF>>     {printf("(eof %u)\n", yylineno); return 0; }

%%