/*
 * main.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 02/01/13
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "handler.h"

int main(int argc, const char * argv[])
{
    calendar_t calendar = NULL;
	FILE * file, * fileOut;

	if (argc == 2)
    {
        file = fopen(argv[1], "r");
        fileOut = fopen("output.dat", "w");
    }

    if (file && fileOut)
    {
        importFileCalendar(&calendar, file);
        printCalendar(calendar);
        exportFileCalendar(calendar, fileOut);



        weekCal_t ** test = searchWeek(&calendar, "2016", "12");

        insertWeek(test, "2014", "12");

        printCalendar(calendar);

        /*freeCalendar(&calendar);*/

        fclose(file);
        fclose(fileOut);
    }
    else
    {
        printf("Erreur fichier");
    }
	/*}
     else
     {
     printf("Erreur argument\n");
     }*/

    return 0;
}

