#ifndef _VIGENERE_H
#define _VIGENERE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

typedef struct {
	char* cle;
	char* alphabet;
	int skip;
	char *message;
	char *sortie;
} Arguments;

/**
 * Calcule la valeur d'un caractère selon sa position dans une string
 * @param Char *, Char
 * @return Integer
 */
int getValue(char *, char);

/**
 * Supprime un caractère d'une string
 * @param Char *, Char
 * @return Char *
 */
char *removeChar(char *, char);

/**
 * Supprime les caractères d'une string non présentes dans l'autre
 * @param Char *, Char *
 * @return Char *
 */
char *skip(char *, char *);

/**
 * Répète le contenu d'une string selon une longueur
 * @param Char *, Integer
 * @return Char *
 */
char *repeatkey(char *, int);

/**
 * Code une string selon un alphabet et une clé
 * @param Char *, Char *, Char *
 * @return
 */
void code(char *, char *, char *);

/**
 * Décode une string selon un alphaet et une clé
 * @param Char *, Char *, Char *
 * @return
 */
void decode(char *, char *, char *);

/**
 * Vérifie que le clé est composée de caractère présents dans l'alphabet
 * @param Char *, Char *
 * @return
 */
void invalid(char *, char *);

/**
 * Copie le contenu d'un fichier dans une string
 * @param Char *, Char *
 * @return
 */
void getFileContent(char *, char *);

/**
 * Copie une string dans un fichier
 * @param Char *, Char *
 * @return
 */
void setFileContent(char *, char *);

/**
 * Initie notre programme en exécutant les fonctions principales de vérification
 * @param Arguments
 * @return
 */
void init(Arguments);

/**
 * Renvoie le résultat du programme
 * @param Arguments
 * @return
 */
void output(Arguments);

/**
 * Récupère les arguments du programme
 * @param Integer, char **
 * @return
 */
Arguments getArguments(int, char **);

#endif