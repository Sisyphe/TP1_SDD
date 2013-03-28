/*
 * calendar.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 05/01/13
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "calendar.h"
#include "tools.h"

/*
 * Insere un element du type weekCal apres l'adresse adrPrev
 *
 * adrPrev: adresse de l'element du calendrier apres lequel inserer
 *      la nouvelle semaine
 * year: annee de la semaine a inserer
 * week: numero de la semaine a inserer
 * return: le nouvel element inserer dans le calendrier
 *
 * newWeek: pointeur vers l'element representant la nouvelle semaine
 */
weekCal_t * insertWeek(weekCal_t ** adrPrev,
                       char * year,
                       char * week)
{
    weekCal_t * newWeek = newWeekCal(year, week);

    newWeek->nextWeek = *adrPrev;
    *adrPrev = newWeek;

    return newWeek;
}

/*
 * Insere un element du type eventCal apres l'adresse adrPrev
 *
 * adrPrev: adresse de l'evenement apres lequel inserer le nouvel
 *      evenement
 * day: le jour de l'evenement a inserer
 * hour: l'heure de l'evenement a inserer
 * event: le nom de l'evenement a inserer
 * return: le nouvel evenement insere
 *
 * newEvent: le nouvel evenement cree
 */
eventCal_t * insertEvent(eventCal_t ** adrPrev,
                         char * day,
                         char * hour,
                         char * event)
{
    eventCal_t * newEvent = newEventCal(day, hour, event);

    newEvent->nextEvent = *adrPrev;
    *adrPrev = newEvent;

    return newEvent;
}

/*
 * Cree un nouvel element du type weekCal et retourne un
 * pointeur sur cet element
 *
 * year: annee de la semaine a creer
 * week: numero de la semaine a creer
 * return: adresse de la semaine creee
 *
 * newWeek: la nouvelle semaine creee
 */
weekCal_t * newWeekCal(char * year,
                       char * week)
{
    weekCal_t * newWeek = (weekCal_t *) malloc(sizeof(weekCal_t));

    newWeek->year = (char *) malloc(sizeof(char)*YEAR_SIZE);
    newWeek->week = (char *) malloc(sizeof(char)*WEEK_SIZE);

    newWeek->year = year;
    newWeek->week = week;
    newWeek->eventList = NULL;
    newWeek->nextWeek = NULL;

    return newWeek;
}

/*
 * Cree un nouvel element du type weekCalBil et retourne un
 * pointeur sur cet element
 *
 * year: l'annee de la nouvelle semaine
 * week: le numero de la nouvelle semaine
 * eventList: la liste chainee d'evenements de la semaine a ajouter
 * return: un pointeur vers la nouvelle semaine creee
 *
 * newWeek: un pointeur vers la nouvelle semaine creee
 */
weekCalBil_t * newWeekCalBil(char * year,
                             char * week,
                             eventCal_t * eventList)
{
    weekCalBil_t * newWeek = (weekCalBil_t *) malloc(sizeof(weekCalBil_t));

    newWeek->year = (char *) malloc(sizeof(char)*YEAR_SIZE);
    newWeek->week = (char *) malloc(sizeof(char)*WEEK_SIZE);

    newWeek->year = year;
    newWeek->week = week;
    newWeek->eventList = eventList;
    newWeek->prevWeek = NULL;
    newWeek->nextWeek = NULL;

    return newWeek;
}

/*
 * Cree un nouvel element du type eventCal et retourne un
 * pointeur sur cet element
 *
 * day: le jour de l'evenement a creer
 * hour: l'heure de l'evenement a creer
 * event: le nom de l'evenement a creer
 * return: le nouvel evenement cree
 *
 * newEvent: le nouvel evenement cree
 */
eventCal_t * newEventCal(char * day,
                         char * hour,
                         char * event)
{
    eventCal_t * newEvent = (eventCal_t *) malloc(sizeof(eventCal_t));

    newEvent->day = (char *) malloc(sizeof(char)*DAY_SIZE);
    newEvent->hour = (char *) malloc(sizeof(char)*HOUR_SIZE);
    newEvent->event = (char *) malloc(sizeof(char)*EVENT_SIZE);

    newEvent->day = day;
    newEvent->hour = hour;
    newEvent->event = event;
    newEvent->nextEvent = NULL;

    return newEvent;
}

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
 *
 * prevWeek: pointeur precedent utilise pour le parcours des semaines
 * currentWeek: le pointeur courant utilise pour le parcours des semaines
 */
weekCal_t ** searchWeek(weekCal_t ** headWeekCal,
                       char * year,
                       char * week)
{
    weekCal_t ** prevWeek = headWeekCal;
    weekCal_t * currentWeek = *headWeekCal;

    while (currentWeek != NULL && isInferiorYearWeek(currentWeek, year, week))
    {
        prevWeek = &(currentWeek->nextWeek);
        currentWeek = *prevWeek;
    }

    return prevWeek;
}

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
                   char * week)
{
    return strcmp(weekCal->year, year) == 0 && strcmp(weekCal->week, week) == 0;
}

/*
 * Retourne vrai si weekCal est inferieur à l'annee et la semaine des parametres
 *
 * weekCal: l'adresse de la semaine a comparer
 * year: l'annee a comparer avec la semaine weekCal
 * week: le numero de la semaine a comparer avec weekCal
 * return: vrai si weekCal est inferieur a year et week
 *
 * isInferior: la valeur de retour de la fonction
 * compYear: stocke le resultat de comparaison des annees
 */
int isInferiorYearWeek(weekCal_t * weekCal,
                   char * year,
                   char * week)
{
    int isInferior = 0;
    int compYear = strcmp(weekCal->year, year);
    if (compYear < 0) isInferior=1;
    else if(compYear == 0)
        isInferior = (strcmp(weekCal->week, week) < 0);
    return isInferior;
}

/*
 * Recherche l'event correspondant aux parametres day et hour
 * et renvoie l'element precedent s'il existe, NUll sinon.
 *
 * headEventCal: double pointeur sur la tete de la liste des evenements ou rechercher
 * day: le jour de l'evenement recherche
 * hour: l'heure de l'evenement recherche
 * return: double pointeur sur l'evenement precedent celui recherche ou NULL
 *      si non trouve
 *
 * prevEvent: pointeur precedent utilise pour parcourir la liste d'evenements
 * currentEvent: pointeur courrant utilise pour parcourir la liste d'evenements
 */
eventCal_t ** searchEvent(eventCal_t ** headEventCal,
                         char * day,
                         char * hour)
{
    eventCal_t ** prevEvent = headEventCal;
    eventCal_t * currentEvent = *headEventCal;

    while (currentEvent != NULL && isInferiorDayHour(currentEvent, day, hour))
    {
        prevEvent = &(currentEvent->nextEvent);
        currentEvent = *prevEvent;
    }

    return prevEvent;
}

/*
 * Retourne vrai si eventCal est inferieur au jour et a l'heure des parametres
 *
 * eventCal: l'adresse de l'evenement a comparer
 * day: le jour a comparer avec l'evenement eventCal
 * hour: l'heure de l'evenement a comparer avec eventCal
 * return: vrai si eventCal est inferieur a day et hour
 *
 * isInferior: la valeur de retour de la fonction
 * compDay: stocke le resultat de comparaison des jours
 */
int isInferiorDayHour(eventCal_t * eventCal,
                  char * day,
                  char * hour)
{
    int isInferior = 0;
    int compDay = strcmp(eventCal->day, day);
    if (compDay < 0) isInferior=1;
    else if(compDay == 0)
        isInferior = (strcmp(eventCal->hour, hour) < 0);
    return isInferior;
}

/*
 * Supprime l'element pointe par adrPrev
 *
 * adrPrev: l'adresse de la semaine a supprimer
 * weekToDelete: stocke l'adresse de la semaine a supprimer
 */
void deleteWeek(weekCal_t ** adrPrev)
{
    weekCal_t * weekToDelete = *adrPrev;

    *adrPrev = weekToDelete->nextWeek;

    freeWeekCal(&weekToDelete);
}

/*
 * Supprime l'element pointe par adrPrev
 *
 * adrPrev: l'adresse de l'evenement a supprimer
 * eventToDelete: stocke l'adresse de l'evenement a supprimer
 */
void deleteEvent(eventCal_t ** adrPrev)
{
    eventCal_t * eventToDelete = *adrPrev;

    *adrPrev = eventToDelete->nextEvent;

    freeEventCal(&eventToDelete);
}

/*
 * Libere un element weekCal
 *
 * weekCal: double pointeur sur la semaine a liberer
 */
void freeWeekCal(weekCal_t ** weekCal)
{
    free((*weekCal)->year);
    free((*weekCal)->week);
    free(*weekCal);
}

/*
 * Libere un element eventCal
 *
 * eventCal: double pointeur sur l'evenement a liberer
 */
void freeEventCal(eventCal_t ** eventCal)
{
    free((*eventCal)->day);
    free((*eventCal)->hour);
    free((*eventCal)->event);
    free(*eventCal);
}
