#include "functions.h"

int main(int argc, char *argv[])
{
    Arguments args = getArguments(argc, argv);
    init(args);
    code(args.alphabet, args.message, args.cle);
    output(args);
    return 0;
}