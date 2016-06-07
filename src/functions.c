#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "functions.h"

int getValue(char *alphabet, char lettre)
{
    char *value = strchr(alphabet, lettre);
    return value - alphabet;
}

char *removeChar(char *message, char lettre)
{
    int i, j = 0, length = strlen(message);
    char *skipped = malloc(length * sizeof(char));
    
    for(i = 0; i < length; i++)
    {
        if(message[i] != lettre)
        {
            *(skipped + j) = *(message + i);
            j++;
        }
    }

    return skipped;
}

char *skip(char *message, char *alphabet)
{
    int i, length = strlen(message);
    char *temp = malloc(length * sizeof(char));
    strcpy(temp, message);

    for(i = 0; i < strlen(temp); i++)
    {
        if(strchr(alphabet, *(temp + i)) == NULL)
        {
            strcpy(message, removeChar(message, *(temp + i)));
        }
    }

    return message;
}

char *repeatkey(char *cle, int size)
{
    int i, index = 0, length = strlen(cle);
    char *repeat = malloc(size * sizeof(char));

    if(length >= size) return cle;
    
    for(i = 0; i < size; i++)
    {
        *(repeat + i) = *(cle + index);
        index += 1;
        if(index == length) index = 0;
    }
    return repeat;
}

void code(char *alphabet, char *message, char *repeat)
{
    int i, value, length = strlen(message);
    for(i = 0; i < length; i++)
    {
        if(strchr(alphabet, *(message + i)) == NULL) continue;
        value = getValue(alphabet, *(message + i)) + getValue(alphabet, *(repeat + i));
        if(value >= strlen(alphabet)) value -= strlen(alphabet);
        *(message + i) = *(alphabet + value);
    }
}

void decode(char *alphabet, char *message, char *repeat)
{
    int i, value, length = strlen(message);
    for(i = 0; i < length; i++)
    {
        if(strchr(alphabet, *(message + i)) == NULL) continue;
        value = getValue(alphabet, *(message + i)) - getValue(alphabet, *(repeat + i));
        if(value < 0) value += strlen(alphabet);
        message[i] = alphabet[value];    
    }
}

void invalid(char *alphabet, char *cle)
{
    int i, length = strlen(cle);
    for(i = 0; i < length; i++)
    {
        if(strchr(alphabet, *(cle + i)) == NULL)
        {
            printf("La cle contient des lettres qui ne sont pas dans l'alphabet\n");
            exit(1);
        }
    }
}

void getFileContent(char *filename, char *args)
{
    FILE *file = NULL;
    char letter;
    int size = 0;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }
    letter = getc(file);
    while(letter != EOF) {
        size++;
        letter = getc(file);
    }
    realloc(args, size * sizeof(char));
    fgets(args, size, file);
    fclose(file);
}

void setFileContent(char *filename, char *args)
{
    FILE *file = NULL;
    file = fopen(filename, "w+");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }
    fputs(args, file);
    fclose(file);
}

Arguments getArguments(int argc, char *argv[])
{
    int opt = 0, index = 0, i;
    char *message, *lettre;
    Arguments args;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h' },
        {"skip", no_argument, 0, 's' },
        {"alphabet", required_argument, 0, 'a' },
        {"key", required_argument, 0, 'k' },
        {0,0,0,0}
    };
    args.cle = malloc(strlen("notaverysmartkey") * sizeof(char));
    args.alphabet = malloc(strlen("abcdefghijklmnopqrstuvwxyz") * sizeof(char));
    args.message = malloc(strlen("dcode") * sizeof(char));
    args.skip = 0;
    args.sortie = NULL;
    strcpy(args.cle, "notaverysmartkey");
    strcpy(args.alphabet, "abcdefghijklmnopqrstuvwxyz");
    strcpy(args.message, "dcode");

    while((opt = getopt_long(argc, argv,"k:a:sh", long_options, &index)) != -1)
    {
        switch(opt)
        {
            case 'k':
            {
                getFileContent(optarg, args.cle);
                break;
            }
            case 'a':
            {
                getFileContent(optarg, args.alphabet);
                break;
            }
            case 's':
            {
                args.skip = 1;
                break;
            }
            case 'h':
            {
                printf("Aide");
                break;
            }
            default:
                break;
        }
    }

    if(optind < argc)
    {
        switch(argc - optind)
        {
            case 1:
            {
                getFileContent(argv[optind], args.message);
                break;
            }
            case 2:
            {
                getFileContent(argv[optind], args.message);
                args.sortie = argv[optind+1];
                break;
            }
            default:
                break;
        }
    }
    else
    {
        free(args.message);
        message = malloc(255 * sizeof(char));
        printf("Entrez votre message > ");
        fgets(message, 255, stdin);
        printf("%s\n", message);
        lettre = strchr(message, '\n');
        if (lettre != NULL) *lettre = 0;
        else while (i != EOF && (i = fgetc(stdin)) != '\n');
        args.message = message;
    }

    return args;
}