CC = cc
CFLAGS = -g -Wall
CSOURCES = main.c alias.c job.c ksignal.c command.c variables.c wildcard.c
GENSOURCES = lex.yy.c kash.tab.c
ALLSOURCES = $(CSOURCES) $(GENSOURCES)
OUTPUTFILE = shell
LEX = flex
YACC = bison -dv -t

all: lex.yy.c kash.tab.c
	$(CC) $(CFLAGS) $(ALLSOURCES) -o $(OUTPUTFILE)

test:
	$(CC) test.c util.c -o kash_test
	./kash_test
	rm kash_test

lex.yy.c: kash.l
	$(LEX) $<

kash.tab.c: kash.y
	$(YACC) $<

clean:
	rm -f $(CSOURCES:.c=.o)
	rm -f $(GENSOURCES)
	rm $(OUTPUTFILE)
	rm kash.tab.h
	rm kash.output