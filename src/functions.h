#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

typedef struct {
	char* cle;
	char* alphabet;
	int skip;
	char *message;
	char *sortie;
} Arguments;

int getValue(char *, char);
char *removeChar(char *, char);
char *skip(char *, char *);
char *repeatkey(char *, int);
void code(char *, char *, char *);
void decode(char *, char *, char *);
void invalid(char *, char *);
Arguments getArguments(int, char **);