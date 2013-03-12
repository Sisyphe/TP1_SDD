/*
 * calendar.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 05/01/13
 *
 * Contient les fonctions de manipulation de calendar de bas niveau.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "calendar.h"
#include "tools.h"

/*
 * Insere un element du type weekCal apres l'element d'adresse adr
 */
weekCal_t * insertWeek(weekCal_t * adr,
                       char * year,
                       char * week)
{
    weekCal_t * newWeek = newWeekCal(year, week);

    newWeek->prevWeek=adr;
    newWeek->nextWeek=adr->nextWeek;
    adr->nextWeek=newWeek;
    newWeek->nextWeek->prevWeek=newWeek;

    return newWeek;
}

/*
 * Insere un element du type eventCal apres l'adresse adrPrev
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
    newWeek->prevWeek = newWeek;
    newWeek->nextWeek = newWeek;

    return newWeek;
}

/*
 * Cree un nouvel element du type eventCal et retourne un
 * pointeur sur cet element
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
 * et la renvoie si elle existe, NULL sinon.
 */
weekCal_t * searchWeek(weekCal_t * headWeekCal,
                       char * year,
                       char * week)
{
    weekCal_t * currentWeek = headWeekCal->nextWeek;

    while (currentWeek != headWeekCal && !isSameYearWeek(currentWeek, year, week))
    {
        currentWeek = currentWeek->nextWeek;
    }

    return currentWeek;
}

/*
 * Compare si l'annee et la semaine des parametres et weekCal sont
 * egaux
 */
int isSameYearWeek(weekCal_t * weekCal,
                   char * year,
                   char * week)
{
    return strcmp(weekCal->year, year) == 0 && strcmp(weekCal->week, week) == 0;
}

/*
 * Recherche l'event correspondant aux parametres day et hour
 * et renvoie l'element precedent s'il existe, NULL sinon.
 */
eventCal_t ** searchEvent(eventCal_t ** headEventCal,
                         char * day,
                         char * hour)
{
    eventCal_t ** prevEvent = headEventCal;
    eventCal_t * currentEvent = *headEventCal;

    while (currentEvent != NULL && !isSameDayHour(currentEvent, day, hour))
    {
        prevEvent = &(currentEvent->nextEvent);
        currentEvent = *prevEvent;
    }

    if (currentEvent == NULL)
    {
        prevEvent = NULL;
    }

    return prevEvent;
}

/*
 * Compare si le jour et l'heure des parametres et eventCal sont
 * egaux
 */
int isSameDayHour(eventCal_t * eventCal,
                  char * day,
                  char * hour)
{
    return strcmp(eventCal->day, day) == 0 && strcmp(eventCal->hour, hour) == 0;
}

/*
 * Supprime l'element pointe par adr
 */
void deleteWeek(weekCal_t * adr)
{
    adr->prevWeek->nextWeek=adr->nextWeek;
    adr->nextWeek->prevWeek=adr->prevWeek;

    freeWeekCal(adr);
}

/*
 * Supprime l'element pointe par adrPrev
 */
void deleteEvent(eventCal_t ** adrPrev)
{
    eventCal_t * eventToDelete = *adrPrev;

    *adrPrev = eventToDelete->nextEvent;

    freeEventCal(&eventToDelete);
}

/*
 * Libere un element weekCal
 */
void freeWeekCal(weekCal_t * weekCal)
{
    free(weekCal->year);
    free(weekCal->week);
    free(weekCal);
}

/*
 * Libere un element eventCal
 */
void freeEventCal(eventCal_t ** eventCal)
{
    free((*eventCal)->day);
    free((*eventCal)->hour);
    free((*eventCal)->event);
    free(*eventCal);
}
