CC = cc
SOURCES = map.c element.c
OUTPUTFILE = main

all:
	$(CC) main.c $(SOURCES) -o $(OUTPUTFILE)

test:
	$(CC) test.c $(SOURCES) -o kash_test
	./kash_test
	rm kash_test

clean:
	rm main
