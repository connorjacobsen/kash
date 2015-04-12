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

">>" { INCR_CHAR(); return STDOUTAPP; }
"2>" { INCR_CHAR(); return STDERRTOK; }
"<"  { INCR_CHAR(); return FILEIN; }
">"  { INCR_CHAR(); return FILEOUT; }
"|"  { INCR_CHAR(); return PIPE; }
"&"  { INCR_CHAR(); return AMPERSAND; }
"\\" { printf("(meta %s %u)\n", yytext, yylineno); }
\"   { printf("(meta %s %u)\n", yytext, yylineno); }

\"([^\\\"]|\\.)*\" {
    INCR_CHAR();
    yytext++;
    yytext[strlen(yytext)-1] = 0;
    printf("YYTEXT: '%s'\n", yytext);
    yylval.string = insert_env_variable(yytext);
    printf("YYLVAL: '%s'\n", yylval.string);
    return tWORD;
}
[^ \t\n]*   {
    INCR_CHAR();
    yylval.string = insert_env_variable(yytext);
    printf("YYTEXT: '%s'\n", yytext);
    printf("YYLVAL: '%s'\n", yylval.string);
    return tWORD;
}

[ \t]   {
    INCR_CHAR();
}

\n {
    INCR_LINE();
    return tNEWLINE;
}

.       { printf("%s\n", yytext); INCR_CHAR(); }

<<EOF>>     {printf("(eof %u)\n", yylineno); exit(0); }

%%