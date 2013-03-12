/*
 * calendar.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 19/02/13
 *
 * Contient des fonctions de bas niveau sans lien direct avec les calendar.
 */

#ifndef TOOLS_H
#define TOOLS_H

enum BOOLEAN {TRUE=1, FALSE=0};

typedef unsigned int BOOL;

/*
 * Retourne vrai si la chaine str contient la sous chaine pattern
 * Retourne faux sinon
 */
int matchPattern(char str[10],
                 char * pattern);

/*
 * Permet d'extraire une sous chaine de src a partir
 * d'une valeur start et d'une valeur end
 */
char * strsub (char * src,
               int start,
               int end);

#endif
