/*
 * calendar.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 19/02/13
 *
 * Contient les structures et énumérations utilisés pour definir un calendar.
 */

#ifndef STRUCT_H
#define STRUCT_H

/*
 * Taille de chaque champs d'une structure weekCal
 */
enum sizeWeekCal {YEAR_SIZE=4, WEEK_SIZE=2};

/*
 * Decallage pour la lecture des elements d'une
 * structure weekCal
 */
enum offsetWeekCal {YEAR_OFFSET=0, WEEK_OFFSET=4};

/*
 * Taille de chaque champs d'une structure eventCal
 */
enum sizeEventCal {DAY_SIZE=1, HOUR_SIZE=2, EVENT_SIZE=10};

/*
 * Decallage pour la lecture des elements d'une
 * structure eventCal
 */
enum offsetEventCal {DAY_OFFSET=6, HOUR_OFFSET=7, EVENT_OFFSET=9};

/*
 * Element de liste chainee du type weekCal
 * Cette liste est a double niveau :
 * Contient un pointeur sur weekCal suivant et un pointeur
 * sur une sous liste chainee
 */
typedef struct weekCal
{
    char * year;
    char * week;
    struct eventCal * eventList;
    struct weekCal * prevWeek;
    struct weekCal * nextWeek;
} weekCal_t;

/*
 * Element de liste chainee du type eventCal
 */
typedef struct eventCal
{
    char * day;
    char * hour;
    char * event;
    struct eventCal * nextEvent;
} eventCal_t;

/*
 * Redefinition du type weekCal_t * en calendar_t qui represente un pointeur sur
 * la tete de la liste chainee
 */
typedef weekCal_t * calendar_t;


#endif
