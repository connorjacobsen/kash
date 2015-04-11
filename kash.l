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

"2>" { INCR_CHAR(); return STDERRTOK; }
"<"  { INCR_CHAR(); return FILEIN; }
">"  { INCR_CHAR(); return FILEOUT; }
"|"  { INCR_CHAR(); return PIPE; }
"&"  { INCR_CHAR(); return AMPERSAND; }
"\\" { printf("(meta %s %u)\n", yytext, yylineno); }
\"   { printf("(meta %s %u)\n", yytext, yylineno); }

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
    return tNEWLINE;
}

.       { printf("%s\n", yytext); INCR_CHAR(); }

<<EOF>>     {printf("(eof %u)\n", yylineno); exit(0); }

%%