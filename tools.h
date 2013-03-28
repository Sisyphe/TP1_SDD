/*
 * tools.h
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
 * Retourne vrai si la chaine A contient la sous chaine B
 * Retourne faux sinon
 *
 * str: la chaine de caracteres ou cherche la sous chaine
 * pattern: la chaine de caracteres recherchee
 * return: un booleen valant vrai si str contient pattern
 */
int matchPattern(char str[10],
                 char * pattern);

/*
 * Permet d'extraire une sous chaine de src a partir
 * d'une valeur start et d'une valeur end
 *
 * src: la chaine de caracteres d'ou extraire la sous chaine
 * start: l'indice de la chaine str a partir duquel extraire la sous chaine
 * end: l'indice de la chaine str jusqu'ou extraire la sous chaine (dernier caractere compris)
 * retour: la chaine extraite
 */
char * strsub (char * src,
               int start,
               int end);

#endif
