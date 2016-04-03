#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int main(int argc, char *argv[])
{
	int opt = 0;
    char *message = malloc(strlen("Comment y es-tu allé ?") * sizeof(char));
    strcpy(message, "Comment y es-tu allé ?");
    char *cle = malloc(16 * sizeof(char));
    strcpy(cle, "notaverysmartkey");
    char *alphabet = malloc(26 * sizeof(char));
    strcpy(alphabet, "abcdefghijklmnopqrstuvwxyz");

	while ((opt = getopt(argc, argv, "k:a:s")) != -1)
	{
        switch (opt) {
        case 'k':
        {
            int *res = realloc(cle, sizeof(optarg));
            if (res == NULL)
            {
                break;
            }
            strcpy(cle, optarg);
            break;
        }
        case 'a':
        {
            int *res = realloc(alphabet, sizeof(optarg));
            if (res == NULL)
            {
                break;
            }
            strcpy(alphabet, optarg);
            break;
        }
        case 's':
        {
            char *s = skip(message, alphabet);
            int *res = realloc(message, sizeof(s));
            if (res == NULL)
            {
                break;
            }
            strcpy(message, s);
            break;
        }
            
        default: /* '?' */
            break;
       }
    }

    char *repeat = repeatkey(cle, strlen(message));
    code(alphabet, message, repeat);
    printf("%s", message);
    return 0;
}