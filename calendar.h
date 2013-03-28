/*
 * calendar.h
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 05/01/13
 *
 * Contient les fonctions de manipulation de calendar de bas niveau.
 */

#include "struct.h"

#ifndef SDDTP1_calendar_h
#define SDDTP1_calendar_h

/*
 * Insere un element du type weekCal apres l'adresse adrPrev
 *
 * adrPrev: adresse de l'element du calendrier apres lequel inserer
 *      la nouvelle semaine
 * year: annee de la semaine a inserer
 * week: numero de la semaine a inserer
 * return: le nouvel element inserer dans le calendrier
 */
weekCal_t * insertWeek(weekCal_t ** adrPrev,
                       char * year,
                       char * week);

/*
 * Insere un element du type eventCal apres l'adresse adrPrev
 *
 * adrPrev: adresse de l'evenement apres lequel inserer le nouvel
 *      evenement
 * day: le jour de l'evenement a inserer
 * hour: l'heure de l'evenement a inserer
 * event: le nom de l'evenement a inserer
 * return: le nouvel evenement insere
 */
eventCal_t * insertEvent(eventCal_t ** adrPrev,
                         char * day,
                         char * hour,
                         char * event);

/*
 * Cree un nouvel element du type weekCal et retourne un
 * pointeur sur cet element
 *
 * year: annee de la semaine a creer
 * week: numero de la semaine a creer
 * return: adresse de la semaine creee
 */
weekCal_t * newWeekCal(char * year,
                       char * week);

/*
 * Cree un nouvel element du type weekCalBil et retourne un
 * pointeur sur cet element
 *
 * year: l'annee de la nouvelle semaine
 * week: le numero de la nouvelle semaine
 * eventList: la liste chainee d'evenements de la semaine a ajouter
 * return: un pointeur vers la nouvelle semaine creee
 */
weekCalBil_t * newWeekCalBil(char * year,
                             char * week,
                             eventCal_t * eventList);

/*
 * Cree un nouvel element du type eventCal et retourne un
 * pointeur sur cet element
 *
 * day: le jour de l'evenement a creer
 * hour: l'heure de l'evenement a creer
 * event: le nom de l'evenement a creer
 * return: le nouvel evenement cree
 */
eventCal_t * newEventCal(char * day,
                         char * hour,
                         char * event);

/*
 * Recherche la week correspondant aux parametres year et weekCal
 * et renvoie l'element precedent s'il existe, NUll sinon.
 *
 * headWeekCal: double pointeur sur la tete du calendrier
 *      ou rechercher la semaine
 * year: l'annee de la semaine recherchee
 * week: le numero de la semaine recherchee
 * return: double pointeur sur l'element precedent celui trouve
 *      ou NULL si non trouve
 */
weekCal_t ** searchWeek(weekCal_t ** headWeekCal,
                        char * year,
                        char * week);

/*
 * Compare si l'annee et la semaine des parametres et weekCal sont
 * egaux
 *
 * weekCal: l'adresse de la semaine a comparer
 * year: l'annee a comparer avec la semaine weekCal
 * week: le numero de la semaine a comparer avec weekCal
 * return: vrai si la semaine weekCal a pour annee year et pour
 *      numero week
 */
int isSameYearWeek(weekCal_t * weekCal,
                   char * year,
                   char * week);

/*
 * Retourne vrai si weekCal est inferieur à l'annee et la semaine des parametres
 *
 * weekCal: l'adresse de la semaine a comparer
 * year: l'annee a comparer avec la semaine weekCal
 * week: le numero de la semaine a comparer avec weekCal
 * return: vrai si weekCal est inferieur a year et week
 */
int isInferiorYearWeek(weekCal_t * weekCal,
                   char * year,
                   char * week);

/*
 * Recherche l'event correspondant aux parametres day et hour
 * et renvoie l'element precedent s'il existe, NUll sinon.
 *
 * headEventCal: double pointeur sur la tete de la liste des evenements ou rechercher
 * day: le jour de l'evenement recherche
 * hour: l'heure de l'evenement recherche
 * return: double pointeur sur l'evenement precedent celui recherche ou NULL
 *      si non trouve
 */
eventCal_t ** searchEvent(eventCal_t ** headEventCal,
                          char * day,
                          char * hour);

/*
 * Compare si le jour et l'heure des parametres et eventCal sont
 * egaux
 *
 * eventCal: l'adresse de l'evenement a comparer
 * day: le jour a comparer avec l'evenement eventCal
 * hour: l'heure a comparer avec eventCal
 * return: vrai si l'evenement eventCal a pour jour day et pour
 *      heure hour
 */
int isSameDayHour(eventCal_t * eventCal,
                   char * day,
                   char * hour);

/*
 * Retourne vrai si eventCal est inferieur au jour et a l'heure des parametres
 *
 * eventCal: l'adresse de l'evenement a comparer
 * day: le jour a comparer avec l'evenement eventCal
 * hour: l'heure de l'evenement a comparer avec eventCal
 * return: vrai si eventCal est inferieur a day et hour
 */
int isInferiorDayHour(eventCal_t * eventCal,
                  char * day,
                  char * hour);

/*
 * Supprime l'element pointe par adrPrev
 *
 * adrPrev: l'adresse de la semaine a supprimer
 * weekToDelete: stocke l'adresse de la semaine a supprimer
 */
void deleteWeek(weekCal_t ** adrPrev);

/*
 * Supprime l'element pointe par adrPrev
 *
 * adrPrev: l'adresse de l'evenement a supprimer
 * eventToDelete: stocke l'adresse de l'evenement a supprimer
 */
void deleteEvent(eventCal_t ** adrPrev);

/*
 * Libere un element weekCal
 *
 * weekCal: double pointeur sur la semaine a liberer
 */
void freeWeekCal(weekCal_t ** weekCal);

/*
 * Libere un element eventCal
 *
 * eventCal: double pointeur sur l'evenement a liberer
 */
void freeEventCal(eventCal_t ** eventCal);


#endif
