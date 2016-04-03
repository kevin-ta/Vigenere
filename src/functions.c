#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if(length >= size)
    {
        return cle;
    }
    
    char *repeat = malloc(size * sizeof(char));
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