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
 */
weekCal_t * insertWeek(weekCal_t ** adrPrev,
                       char * year,
                       char * week);

/*
 * Insere un element du type eventCal apres l'adresse adrPrev
 */
eventCal_t * insertEvent(eventCal_t ** adrPrev,
                         char * day,
                         char * hour,
                         char * event);

/*
 * Cree un nouvel element du type weekCal et retourne un
 * pointeur sur cet element
 * L'element creee contient un element EventCal
 */
weekCal_t * newWeekCal(char * year,
                       char * week);

/*
 * Cree un nouvel element du type weekCalBil et retourne un
 * pointeur sur cet element
 */
weekCalBil_t * newWeekCalBil(char * year,
                             char * week,
                             eventCal_t * eventList);

/*
 * Cree un nouvel element du type eventCal et retourne un
 * pointeur sur cet element
 */
eventCal_t * newEventCal(char * day,
                         char * hour,
                         char * event);

/*
 * Recherche la week correspondant aux param�tres year et weekCal
 * et renvoie l'�lement pr�cedent s'il existe, NUll sinon.
 */
weekCal_t ** searchWeek(weekCal_t ** headWeekCal,
                        char * year,
                        char * week);

/*
 * Compare si l'annee et la semaine des parametres et weekCal sont
 * egaux
 */
int isSameYearWeek(weekCal_t * weekCal,
                   char * year,
                   char * week);

/*
 * Compare si l'annee et la semaine des parametres et weekCal sont
 * egaux
 */
int isInferiorYearWeek(weekCal_t * weekCal,
                   char * year,
                   char * week);

/*
 * Recherche l'event correspondant aux parametres day et hour
 * et renvoie l'element pr�cedent s'il existe, NUll sinon.
 */
eventCal_t ** searchEvent(eventCal_t ** headEventCal,
                          char * day,
                          char * hour);

/*
 * Compare si le jour et l'heure des parametres et eventCal sont
 * egaux
 */
int isInferiorDayHour(eventCal_t * eventCal,
                  char * day,
                  char * hour);

/*
 * Supprime l'�lement point� par adrPrev
 */
void deleteWeek(weekCal_t ** adrPrev);

/*
 * Supprime l'�lement point� par adrPrev
 */
void deleteEvent(eventCal_t ** adrPrev);

/*
 * Libere un element weekCal
 */
void freeWeekCal(weekCal_t ** weekCal);

/*
 * Libere un element eventCal
 */
void freeEventCal(eventCal_t ** eventCal);


#endif
