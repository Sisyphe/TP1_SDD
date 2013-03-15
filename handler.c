/*
 * handler.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 19/02/13
 *
 */

#include "handler.h"
#include <string.h>
#include <stdlib.h>
#include "tools.h"

/*
 * Convertit un fichier texte en liste chainee
 * de type weekCal/eventCal
 */
void importSortedFileCalendar(calendar_t * calendar,
							  FILE * file)
{
    char bufferReader[BUFFER_READER_SIZE];
    char *year, *week, *day, *hour, *event;

    weekCal_t ** prevWeek = calendar;
    weekCal_t * currentWeek = *calendar;

    eventCal_t ** prevEvent = NULL;
    eventCal_t * currentEvent = NULL;

    int fin1=FALSE, fin2=FALSE;

    if(fgets(bufferReader, sizeof(bufferReader), file))
    {
        extractSubString(bufferReader, &year, &week, &day, &hour, &event);

        while (!fin1)
        {
            currentWeek = insertWeek(prevWeek, year, week);
            prevWeek = &(currentWeek->nextWeek);
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
 * Convertit un fichier texte non trie en liste chainee
 * de type weekCal/eventCal
 */
void importUnsortedFileCalendar(calendar_t * calendar,
                                FILE * file)
{
    char bufferReader[BUFFER_READER_SIZE];
    char *year, *week, *day, *hour, *event;

    weekCal_t ** prevWeek = NULL;
    eventCal_t ** prevEvent = NULL;

    while (fgets(bufferReader, sizeof(bufferReader), file))
    {
        extractSubString(bufferReader, &year, &week, &day, &hour, &event);

        prevWeek = searchWeek(calendar, year, week);

        if ((*prevWeek) == NULL || !isSameYearWeek((*prevWeek), year, week))
        {
            insertWeek(prevWeek, year, week);
        }

        prevEvent = searchEvent(&(*prevWeek)->eventList, day, hour);

        insertEvent(prevEvent, day, hour, event);
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
    weekCal_t * currentWeek = calendar;
    eventCal_t * currentEvent = NULL;

    while (currentWeek != NULL)
    {
        currentEvent = currentWeek->eventList;
        while (currentEvent != NULL)
        {
            fprintf(
                file,
                "%s%s%s%s%s\n",
                currentWeek->year,
                currentWeek->week,
                currentEvent->day,
                currentEvent->hour,
                currentEvent->event
            );

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
    weekCal_t * currentWeek = calendar;
    eventCal_t * currentEvent = NULL;
    int i = 0; /* iterateur */

    listeContigue = (char *)malloc(sizeof(char)*LISTE_CONTIGUE_SIZE);

    while (currentWeek != NULL)
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

                i += YEAR_SIZE+WEEK_SIZE+DAY_SIZE;

                currentEvent = currentEvent->nextEvent;
            }
        }
        currentWeek = currentWeek->nextWeek;
    }

    return listeContigue;
}

/*
 * Supprime l'event correspond aux parametres year, week, day, hour
 * de calendar et supprime la week si elle est vide.
 * Retourne FAUX si la suppression a reussi.
 */
int deleteWeekEventCal(calendar_t * calendar,
                       char * year,
                       char * week,
                       char * day,
                       char * hour)
{
    weekCal_t ** prevWeek = NULL;
    eventCal_t ** prevEvent = NULL;
    int error = TRUE;

    prevWeek = searchWeek(calendar, year, week);

    if (prevWeek != NULL)
    {
        prevEvent = searchEvent(&(*prevWeek)->eventList, day, hour);

        if (prevEvent != NULL)
        {
            deleteEvent(prevEvent);
            error = FALSE;

            if ((*prevWeek)->eventList == NULL)
            {
                deleteWeek(prevWeek);
            }
        }
    }

    return error;
}

/*
 * Conversion d'une liste chainee en liste bilatere
 */
weekCalBil_t * convertWeekCalToWeekCalBil(calendar_t calendar)
{
    weekCal_t * currentWeek = calendar;
	weekCalBil_t * prevWeekBil;

    weekCalBil_t * listeBilatere = newWeekCalBil("\0", "\0", NULL);
    listeBilatere->prevWeek = listeBilatere;
    listeBilatere->nextWeek = listeBilatere;

    prevWeekBil = listeBilatere;

    while (currentWeek != NULL)
    {
        /* creer nouvel element avec valeur de l'ancien */
        weekCalBil_t * newWeekCal = newWeekCalBil(
            currentWeek->year,
            currentWeek->week,
            currentWeek->eventList
        );

        /* lie newelem avec le prec */
        newWeekCal->prevWeek = prevWeekBil;
        /* lie newelem avec le suiv */
        newWeekCal->nextWeek = prevWeekBil->nextWeek;
        /* lie le prec avec newElem */
        prevWeekBil->nextWeek = newWeekCal;
        /* lie suiv avec newElem */
        newWeekCal->nextWeek->prevWeek = newWeekCal;

        /* avancer le prec */
        prevWeekBil = newWeekCal;

        currentWeek = currentWeek->nextWeek;
    }

    return listeBilatere;
}

/*
 * Libere une liste chainee à deux niveau
 * de type weekCal/eventCal
 * On utilise une supression en tete
 */
void freeCalendar(calendar_t * calendar)
{
    while (*calendar != NULL)
    {
        while ((*calendar)->eventList != NULL)
        {
            deleteEvent(&(*calendar)->eventList);
        }
        deleteWeek(calendar);
    }
}

/*
 * Affiche sur la sortie standard le contenu de la liste chainee
 * pointe par calendar
 */
void printCalendar(calendar_t calendar)
{
    weekCal_t * currentWeek;
    eventCal_t * currentEvent;

    currentWeek = calendar;

    printf("\n** Calendar **\n\n");

    if (currentWeek == NULL)
    {
        printf("Calendrier Vide =(\n");
    }

    while (currentWeek != NULL)
    {
        printf("%s - semaine %s\n", currentWeek->year, currentWeek->week);

        currentEvent = currentWeek->eventList;
        while (currentEvent != NULL)
        {
            printf(
                "    Jour %s - Heure %s - %s\n",
                currentEvent->day,
                currentEvent->hour,
                currentEvent->event
            );

            currentEvent = currentEvent->nextEvent;
        }
        currentWeek = currentWeek->nextWeek;
    }
}
