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

\"([^\\\"]|\\.)*\" { printf("(word %s %u)\n", yytext, yylineno); }
[^ \t\n<<EOF>>]*   { printf("(word %s %u)\n", yytext, yylineno); }

[ \t]   {}
.       { printf("I got nothing.\n"); }

%%