CC=gcc
CFLAGS=-Wall -ansi -pedantic
LDFLAGS=
EXEC=bin/code bin/decode
CODE=src/code.c src/functions.c
DECODE=src/decode.c src/functions.c
HEAD=functions.h
USER=tak_mathisa

all: $(EXEC)

bin/code: $(CODE)
	$(CC) $(CFLAGS) -o bin/code $(CODE)

bin/decode: $(DECODE)
	$(CC) $(CFLAGS) -o bin/decode $(DECODE)

force:
	$(CC) $(CFLAGS) -o bin/code $(CODE)
	$(CC) $(CFLAGS) -o bin/decode $(DECODE)

clean:
	rm -rf bin/* *~ 2> /dev/null
 
zip: clean
	mkdir -p $(USER)
	cp -R Makefile bin/ doc/ src/ $(USER)
	rm -rf $(USER)/doc/.gitignore $(USER)/bin/.gitignore
	tar czf $(USER).tgz $(USER)
	rm -rf $(USER)