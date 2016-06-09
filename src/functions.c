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
    if(skipped == NULL)
    {
        fprintf(stderr,"Erreur : probleme allocation memoire\n");
        exit(0);
    }
    
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
    if(temp == NULL)
    {
        fprintf(stderr,"Erreur : probleme allocation memoire\n");
        exit(0);
    }
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
    if(repeat == NULL)
    {
        fprintf(stderr,"Erreur : probleme allocation memoire\n");
        exit(0);
    }

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
    int size = 0;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if(realloc(args, size * sizeof(char)) == NULL)
    {
        fprintf(stderr,"Erreur : probleme reallocation memoire\n");
        exit(0);
    }
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

void init(Arguments args)
{
    char *s;
    invalid(args.alphabet, args.cle);
    if(args.skip == 1)
    {
        s = skip(args.message, args.alphabet);
        strcpy(args.message, s);
    }
    args.cle = repeatkey(args.cle, strlen(args.message));
}

void output(Arguments args)
{
    if(args.sortie != NULL)
    {
        printf("Ecriture du resultat dans le fichier %s.\n", args.sortie);
        setFileContent(args.sortie, args.message);
    }
    else printf("%s\n", args.message);
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
    if(args.cle == NULL)
    {
        fprintf(stderr,"Erreur : probleme allocation memoire\n");
        exit(0);
    }
    args.alphabet = malloc(strlen("abcdefghijklmnopqrstuvwxyz") * sizeof(char));
    if(args.alphabet == NULL)
    {
        fprintf(stderr,"Erreur : probleme allocation memoire\n");
        exit(0);
    }
    args.message = malloc(strlen("dcode") * sizeof(char));
    if(args.message == NULL)
    {
        fprintf(stderr,"Erreur : probleme allocation memoire\n");
        exit(0);
    }
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
                printf("Options : [-sh] [--help] [--skip] [-a alphabet] [-k clé] [--alphabet=alphabet] [--key=clé]\n");
                printf("Le programme code encode un texte en utilisant le code Vigenère.\n");
                printf("Le programme decode decode un texte en utilisant le code Vigenère.\n");
                printf("Lorsqu'aucun fichier n'est fourni, l'encodage se fait depuis l'entrée standard vers la sortie standard, ligne par ligne.\n");
                printf("Lorsqu'un seul fichier est fourni, l'encodage se fait depuis le fichier vers la sortie standard.\n");
                printf("Lorsque deux fichiers sont fournis, l'encodage se fait depuis le premier vers le deuxième.\n");
                printf("L'option -s (--skip), lorsqu'elle est présente, indique que les lettres du texte à encoder non présentes dans l'alphabet sont supprimées. Lorsqu'elle est absente, ces lettres restent en clair dans le message codé.\n");
                printf("Les options -a (--alphabet) et -k (--key) permettent de spécifier les fichiers contenant respectivement l'alphabet et la clé. Si elles sont absentes, l'alphabet est l'alphabet latin non accentué composé uniquement de lettres minuscules (abcdefghijklmnopqrstuvwxyz) et la clé est notaverysmartkey.\n");                
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
        if(message == NULL)
        {
            fprintf(stderr,"Erreur : probleme allocation memoire\n");
            exit(0);
        }
        printf("Entrez votre message > ");
        fgets(message, 255, stdin);
        lettre = strchr(message, '\n');
        if (lettre != NULL) *lettre = 0;
        else while (i != EOF && (i = fgetc(stdin)) != '\n');
        args.message = message;
    }

    return args;
}