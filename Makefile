all: src/code.c src/decode.c src/functions.c
	gcc -Wall src/code.c src/functions.c -o bin/code
	gcc -Wall src/decode.c src/functions.c -o bin/decode

code: src/code.c src/decode.c src/functions.c
	gcc -Wall src/code.c src/functions.c -o bin/code

decode: src/decode.c src/decode.c src/functions.c
	gcc -Wall src/decode.c src/functions.c -o bin/decode

clean:
	rm -rf bin/*
