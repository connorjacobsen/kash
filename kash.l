%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    yytext++;
    yytext[strlen(yytext)-1] = 0;
    if (contains_env_variable(yytext)) {
        char *str = insert_env_variable(yytext);
        int len = strlen(str);
        while (len > -1)
            unput(str[len--]);
    } else if (alias_exists(yytext)) {
        char *str = resolve_alias(yytext);
        int len = strlen(str);
        while (len > -1)
            unput(str[len--]);
    } else {
        INCR_CHAR();
        yylval.string = yytext;
        return tWORD;
    }
}
[^ \t\n]*   {
    INCR_CHAR();
    if (contains_env_variable(yytext)) {
        char *str = insert_env_variable(yytext);
        int len = strlen(str);
        while (len > -1) {
            unput(str[len--]);
        }
    } else if (alias_exists(yytext)) {
        char *str = resolve_alias(yytext);
        int len = strlen(str);
        while (len > -1)
            unput(str[len--]);
    } else {
        yylval.string = yytext;
        return tWORD;
    }
}

[ \t]   {
    INCR_CHAR();
}

\n {
    INCR_LINE();
    return tNEWLINE;
}

.       { printf("%s\n", yytext); INCR_CHAR(); }

<<EOF>>     {}

%%