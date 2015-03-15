CC = cc
CFLAGS = -g -Wall
SOURCES = map.c element.c
OUTPUTFILE = kash
LEX = lex
YACC = yacc -y

all: lex.yy.c
	$(CC) $(CFLAGS) lex.yy.c main.c $(SOURCES) -o $(OUTPUTFILE)

test:
	$(CC) test.c $(SOURCES) -o kash_test
	./kash_test
	rm kash_test

lex.yy.c:
	$(LEX) kash.l

clean:
	rm lex.yy.c
	rm kash