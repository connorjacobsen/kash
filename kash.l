%{
#include <stdio.h>
#include <stdlib.h>
#include "include/kash.h"
#include "kash.tab.h"

int linenum = 1;
int charnum = 1;

#define INCR_LINE() { linenum += 1; charnum = 1; }
#define INCR_CHAR() { charnum += strlen(yytext); }
%}

%option noyywrap
%option yylineno

%%

"<"  { printf("(meta %s %u)\n", yytext, yylineno); }
">"  { INCR_CHAR(); return FILEIN; }
"|"  { printf("(meta %s %u)\n", yytext, yylineno); }
"&"  { printf("(meta %s %u)\n", yytext, yylineno); }
"\\" { printf("(meta %s %u)\n", yytext, yylineno); }
\"   { printf("(meta %s %u)\n", yytext, yylineno); }

 /* reserved words */
"setenv" { INCR_CHAR(); return tSETENV; }
"printenv" { return tPRINTENV; }
"unsetenv" { printf("(unsetenv %u)\n", yylineno); }
"alias" { yylval.string = yytext; INCR_CHAR(); return tALIAS; }
"unalias" { yylval.string = yytext; INCR_CHAR(); return tUNALIAS; }
"bye" { INCR_CHAR(); return tBYE; }

\"([^\\\"]|\\.)*\" { 
    yylval.string = yytext;
    INCR_CHAR();
    return tWORD;
}
[^ \t\n<<EOF>>]*   {
    yylval.string = yytext;
    INCR_CHAR();
    return tWORD;
}

[ \t]   {
    INCR_CHAR();
}

\n {
    INCR_LINE();
    // printf("%s", kPROMPT);
    return tNEWLINE;
}

.       { printf("%s\n", yytext); INCR_CHAR(); }

<<EOF>>     {printf("(eof %u)\n", yylineno); exit(0); }

%%