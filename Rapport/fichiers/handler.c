/*
 * calendar.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 19/02/13
 *
 * Contient les fonctions de manipulation de calendar de haut niveau.
 */

#include "handler.h"
#include <string.h>
#include <stdlib.h>
#include "tools.h"


/*
 * Initialise un nouveau calendrier et le retourne
 */
weekCal_t * newCalendar()
{
    return newWeekCal("\0","\0");
}


/*
 * Convertit un fichier texte en liste chainee
 * de type weekCal/eventCal
 */
void importFileCalendar(calendar_t calendar,
                       FILE * file)
{
    char bufferReader[BUFFER_READER_SIZE];
    char *year, *week, *day, *hour, *event;

    weekCal_t * currentWeek = calendar;

    eventCal_t ** prevEvent = NULL;
    eventCal_t * currentEvent = NULL;

    int fin1=FALSE, fin2=FALSE;

    if(fgets(bufferReader, sizeof(bufferReader), file))
    {
        extractSubString(bufferReader, &year, &week, &day, &hour, &event);

        while (!fin1)
        {
            currentWeek = insertWeek(currentWeek, year, week);
            prevEvent = &(currentWeek->eventList);

            fin2=0;
            while (!fin2)
            {
                currentEvent = insertEvent(prevEvent, day, hour, event);
                prevEvent = &(currentEvent->nextEvent);

                if(fgets(bufferReader, sizeof(bufferReader), file))
                {
                    extractSubString(bufferReader, &year, &week, &day, &hour, &event);
                    fin2 = !isSameYearWeek(currentWeek, year, week);
                }
                else
                {
                    fin2=TRUE;
                    fin1=TRUE;
                }
            }
        }
    }
}

/*
 * A partir de la chaine bufferReader la fonction cree les sous-chaines
 * contenant les informations stockees dans la chaine de bufferReader
 */
void extractSubString(char * bufferReader,
                      char ** year,
                      char ** week,
                      char ** day,
                      char ** hour,
                      char ** event)
{
    *year = strsub(bufferReader, YEAR_OFFSET, YEAR_OFFSET+YEAR_SIZE-1);
    *week = strsub(bufferReader, WEEK_OFFSET, WEEK_OFFSET+WEEK_SIZE-1);
    *day = strsub(bufferReader, DAY_OFFSET, DAY_OFFSET+DAY_SIZE-1);
    *hour = strsub(bufferReader, HOUR_OFFSET, HOUR_OFFSET+HOUR_SIZE-1);
    *event = strsub(bufferReader, EVENT_OFFSET, EVENT_OFFSET+EVENT_SIZE-1);
}

/*
 * Exporte une liste chainee de type weekCal/eventCal
 * en fichier en utilisant le meme format que la lecture
 * 4charYEar|2charWeek|1charDay|2charHour|10charEvent
 */
void exportFileCalendar(calendar_t calendar,
                        FILE * file)
{
    weekCal_t * currentWeek = calendar->nextWeek;
    eventCal_t * currentEvent = NULL;

    while (currentWeek != calendar)
    {
        currentEvent = currentWeek->eventList;
        while (currentEvent != NULL)
        {
            fprintf(file, "%s%s%s%s%s\n", currentWeek->year, currentWeek->week, currentEvent->day, currentEvent->hour, currentEvent->event);

            currentEvent = currentEvent->nextEvent;
        }
        currentWeek = currentWeek->nextWeek;
    }
}

/*
 * Cree une liste contigue des jours contenant un event
 */
char * listeContigueDesEvent(calendar_t calendar,
                             char * chaineRecherche)
{
    char * listeContigue;
    weekCal_t * currentWeek = calendar->nextWeek;
    eventCal_t * currentEvent = NULL;
    int i = 0; /* iterateur */

    listeContigue = (char *)malloc(sizeof(char)*LISTE_CONTIGUE_SIZE);

    while (currentWeek != calendar)
    {
        currentEvent = currentWeek->eventList;
        while (currentEvent != NULL)
        {
            while (currentEvent != NULL && !matchPattern(currentEvent->event, chaineRecherche))
            {
                currentEvent = currentEvent->nextEvent;
            }

            if (currentEvent != NULL)
            {
                strncpy(listeContigue+i,currentWeek->year, YEAR_SIZE);
                strncpy(listeContigue+i+WEEK_OFFSET,currentWeek->week, WEEK_SIZE);
                strncpy(listeContigue+i+DAY_OFFSET,currentEvent->day, DAY_SIZE);
                strncpy(listeContigue+i+HOUR_OFFSET,currentEvent->hour, HOUR_SIZE);
                
                i += YEAR_SIZE+WEEK_SIZE+DAY_SIZE+HOUR_SIZE;

                currentEvent = currentEvent->nextEvent;
            }
        }
        currentWeek = currentWeek->nextWeek;
    }

    return listeContigue;
}

/*
 * Affiche sur la sortie standard le contenu de la liste chainee
 * pointe par calendar
 */
void printCalendar(calendar_t calendar)
{
    weekCal_t * currentWeek;
    eventCal_t * currentEvent;

    currentWeek = calendar->nextWeek;

    printf("\n** Calendar **\n\n");

    if (currentWeek == calendar)
    {
        printf("Calendrier Vide");
    }

    while (currentWeek != calendar)
    {
        printf("%s - semaine %s\n", currentWeek->year, currentWeek->week);

        currentEvent = currentWeek->eventList;
        while (currentEvent != NULL)
        {
            printf("    Jour %s - Heure %s - %s\n", currentEvent->day, currentEvent->hour, currentEvent->event);

            currentEvent = currentEvent->nextEvent;
        }
        currentWeek = currentWeek->nextWeek;
    }
}

/*
 * Supprime l'event correspond aux paramètres year, week, day, hour
 * de calendar et supprime la week si elle est vide.
 * Retourne FAUX si la suppression a réussi.
 */
int deleteWeekEventCal(calendar_t calendar,
                       char * year,
                       char * week,
                       char * day,
                       char * hour)
{
    eventCal_t ** prevEvent = NULL;
    int error = TRUE;

    weekCal_t * currentWeek = searchWeek(calendar, year, week);

    if (currentWeek != calendar)
    {
        prevEvent = searchEvent(&currentWeek->eventList, day, hour);

        if (prevEvent != NULL)
        {
            deleteEvent(prevEvent);
            error = FALSE;

            if (currentWeek->eventList == NULL)
            {
                deleteWeek(currentWeek);
            }
        }
    }

    return error;
}

/*
 * Libere une liste chainee à deux niveaux
 * de type weekCal/eventCal
 */
void freeCalendar(calendar_t * calendar)
{
    weekCal_t * currentWeek=(*calendar)->nextWeek;
    weekCal_t * weekToDelete=NULL;

    while (currentWeek != *calendar)
    {
        while (currentWeek->eventList != NULL)
        {
            printCalendar(*calendar); printf("\n");
            deleteEvent(&currentWeek->eventList);
        }

        weekToDelete=currentWeek;
        currentWeek=currentWeek->nextWeek;
        deleteWeek(weekToDelete);
    }

    (*calendar)=NULL;
}
