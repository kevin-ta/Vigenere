#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    Arguments args = getArguments(argc, argv);
    invalid(args.alphabet, args.cle);
    char *repeat = repeatkey(args.cle, strlen(args.message));
    decode(args.alphabet, args.message, repeat);
    printf("%s\n", args.message);
    return 0;
}