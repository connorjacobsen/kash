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

void
handle_wildcards(char *line);

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
    } else if(contains_wildcard(yytext)) {
        handle_wildcards(yytext);
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

void
handle_wildcards(char *line)
{
    char *str = strdup(line);
    int i = 0; 
    int index = -1;
    while(str[i] && str[i] != '*') {
        if(str[i] == '/')
            index = i;
        i++;
    }

    char *directory;
    char *pattern; 

    if(index == -1) {
        directory = (char *) malloc(2 * sizeof(char));
        directory[0] = '.';
        directory[1] = 0;

        pattern = (char *) malloc((strlen(str) + 1) * sizeof(char));
        strcpy(pattern, line);
    }
    else {
        directory = (char *) malloc((index + 2) * sizeof(char));
        strncpy(directory, str, index + 1);
        directory[index+1] = 0;

        pattern = (char *) malloc(strlen(&str[index]) * sizeof(char));
        strcpy(pattern, &str[index + 1]);
    }

    DIR *dir;
    if((dir = opendir(directory)) == NULL)
        printf("Directory could not be opened.\n");

    struct dirent *file;
    while((file = readdir(dir)) != NULL)
        if(fnmatch(pattern, file->d_name, FNM_PATHNAME | FNM_PERIOD) == 0)
            wildcard_add(make_wildcard(file->d_name));

    /* free wildcard list */
    wildcard_t *wc = wchead;
    if (wchead == NULL) return;
    while(wc != NULL) {
        /* push input back */
        int len = strlen(wc->filename);
        unput(' ');
        while(len > -1) {
            unput(wc->filename[len--]);
        }
        if (wc->next != NULL)
            wc = wc->next;
        else
            break;
    }
    wchead = NULL;

    free(directory);
    free(pattern);
    closedir(dir);
}
