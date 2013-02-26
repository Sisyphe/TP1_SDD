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
