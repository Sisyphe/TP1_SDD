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
 * Convertit un fichier texte trie ouvert en lecture
 * en liste chainee de type weekCal/eventCal
 *
 * calendar: pointeur sur le calendrier à remplir
 * file: pointeur sur un fichier ouvert d'ou importer
 */
void importSortedFileCalendar(calendar_t * calendar,
                       FILE * file);

/*
 * Convertit un fichier texte ouvert en lecture non trie
 * en liste chainee de type weekCal/eventCal
 *
 * calendar: pointeur sur le calendrier à remplir
 * file: pointeur sur un fichier ouvert d'ou importer
 */
void importUnsortedFileCalendar(calendar_t * calendar,
                              FILE * file);

/*
 * A partir de la chaine bufferReader la fonction cree les sous-chaines
 * contenant les informations stockees dans la chaine de bufferReader
 *
 * bufferReader: la chaine formatee d'ou extraire les donnees
 * year, week, day, hour, event: les chaines de caractere ou stocker
 *      les informations extraites
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
 *
 * calendar: le calendrier a enregistrer dans le fichier
 * file: le fichier ouvert en mode ecriture ou enregistrer
 *      le calendrier
 */
void exportFileCalendar(calendar_t calendar,
                        FILE * file);

/*
 * Cree une liste contigue des jours contenant un event
 *
 * calendrier: le calendrier ou rechercher les evenements
 * chaineRecherche: la chaine de caracteres permettant de filtrer
 *      les evenements à rechercher
 * return: la liste des jours ou l'evenement a ete trouve sous forme
 *      de liste contigue de caracteres
 */
char * listeContigueDesEvent(calendar_t calendar,
                             char * chaineRecherche);

/*
 * Supprime l'event correspondant aux parametres year, week, day, hour
 * de calendar et supprime la week si elle est vide.
 * Retourne FAUX si la suppression a reussi.
 *
 * calendar: un pointeur vers le calendrier ou supprimer l'evenement
 * year, week, day, hour, event: les informations sur l'evenement recherche
 * return: un booleen valant faux si la supression a reussi
 */
int deleteWeekEventCal(calendar_t * calendar,
                       char * year,
                       char * week,
                       char * day,
                       char * hour);

/*
 * Conversion d'une liste chainee en liste bilatere
 *
 * calendar: le calendrier a convertir en liste bilatere
 * return: la liste bilatere creee a partir du calendrier
 */
weekCalBil_t * convertWeekCalToWeekCalBil(calendar_t calendar);

/*
 * Libere une liste chainee à deux niveau
 * de type weekCal/eventCal
 * On utilise une supression en tete
 *
 * calendar: un pointeur vers le calendrier a supprimer
 */
void freeCalendar(calendar_t * calendar);

/*
 * Affiche sur la sortie standard le contenu de la liste chainee
 * pointe par calendar
 *
 * calendar: le calendrier a afficher
 */
void printCalendar(calendar_t calendar);

#endif
