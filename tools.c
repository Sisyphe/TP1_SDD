/*
 * tools.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 19/02/13
 *
 */

#include "tools.h"
#include <stdlib.h>
#include <string.h>

/*
 * Retourne vrai si la chaine A contient la sous chaine B
 * Retourne faux sinon
 *
 * str: la chaine de caracteres ou cherche la sous chaine
 * pattern: la chaine de caracteres recherchee
 * return: un booleen valant vrai si str contient pattern
 *
 * i,j: iterateurs
 * size: la taille de la chaine recherchee
 * match: valeur de retour
 */
int matchPattern(char str[10],
                 char * pattern)
{
    unsigned int i = 0;
    unsigned int j = 0;
    size_t size = strnlen(pattern, 11);
    BOOL match = (size > 10);

    while(i<10 && !match)
    {
        j=0;
        match=TRUE;
        while(j < size && match)
        {
            match = (str[i+j] == pattern[j]);
            ++j;
        }
        ++i;
    }
    return (j == size);
}

/*
 * Permet d'extraire une sous chaine de src a partir
 * d'une valeur start et d'une valeur end
 *
 * src: la chaine de caracteres d'ou extraire la sous chaine
 * start: l'indice de la chaine str a partir duquel extraire la sous chaine
 * end: l'indice de la chaine str jusqu'ou extraire la sous chaine (dernier caractere compris)
 * retour: la chaine extraite
 *
 * chaine: valeur de retour
 * i: iterateur
 */
char * strsub (char * src,
               int start,
               int end)
{
    char *chaine = NULL;
    int i;

    if (src != NULL && start <= end)
    {
        chaine = (char *) malloc(sizeof(char) * (end - start + 2));

        i = start;

        while (i <= end && src[i] != '\0')
        {
            chaine[i - start] = src[i];
            i++;
        }
    }

    return chaine;
}
