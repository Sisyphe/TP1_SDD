/*
 * handler.h
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 19/02/13
 *
 * Contient les fonctions de manipulation de calendar de haut niveau.
 */

#ifndef HANDLER_H
#define HANDLER_H

#include "calendar.h"
#include <stdio.h>

#define BUFFER_READER_SIZE 21
#define LISTE_CONTIGUE_SIZE 256

/*
 * Convertit un fichier texte trie en liste chainee
 * de type weekCal/eventCal
 */
void importSortedFileCalendar(calendar_t * calendar,
                       FILE * file);

/*
 * Convertit un fichier texte non trie en liste chainee
 * de type weekCal/eventCal
 */
void importUnsortedFileCalendar(calendar_t * calendar,
                              FILE * file);

/*
 * A partir de la chaine bufferReader la fonction cree les sous-chaines
 * contenant les informations stockees dans la chaine de bufferReader
 */
void extractSubString(char * bufferReader,
                      char ** year,
                      char ** week,
                      char ** day,
                      char ** hour,
                      char ** event);

/*
 * Exporte une liste chainee de type weekCal/eventCal
 * en fichier en utilisant le meme format que la lecture
 * 4charYEar|2charWeek|1charDay|2charHour|10charEvent
 */
void exportFileCalendar(calendar_t calendar,
                        FILE * file);

/*
 * Cree une liste contigue des jours contenant un event
 */
char * listeContigueDesEvent(calendar_t calendar,
                             char * chaineRecherche);

/*
 * Supprime l'event correspond aux paramètres year, week, day, hour
 * de calendar et supprime la week si elle est vide.
 * Retourne FAUX si la suppression a réussi.
 */
int deleteWeekEventCal(calendar_t * calendar,
                       char * year,
                       char * week,
                       char * day,
                       char * hour);

/*
 * Conversion d'une liste chainee en liste bilatere
 */
weekCalBil_t * convertWeekCalToWeekCalBil(calendar_t calendar);

/*
 * Libere une liste chainee Ã  deux niveau
 * de type weekCal/eventCal
 * On utilise une supression en tete
 */
void freeCalendar(calendar_t * calendar);

/*
 * Affiche sur la sortie standard le contenu de la liste chainee
 * pointe par calendar
 */
void printCalendar(calendar_t calendar);

#endif
