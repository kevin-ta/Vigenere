#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    Arguments args = getArguments(argc, argv);
    char *s, *repeat;
    invalid(args.alphabet, args.cle);
    if(args.skip == 1)
    {
        s = skip(args.message, args.alphabet);
        strcpy(args.message, s);
    }
    repeat = repeatkey(args.cle, strlen(args.message));
    code(args.alphabet, args.message, repeat);
    if(args.sortie != NULL)
    {
    	printf("Ecriture du resultat dans le fichier %s.\n", args.sortie);
    	setFileContent(args.sortie, args.message);
    }
    else printf("%s\n", args.message);
    return 0;
}