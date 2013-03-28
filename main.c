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
    calendarBil_t calendarBil = NULL;
	FILE * file, * fileOut;

	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		fileOut = fopen("output.dat", "w");

		if (file && fileOut)
		{
			importSortedFileCalendar(&calendar, file);
			printCalendar(calendar);

			exportFileCalendar(calendar, fileOut);

			printf("%s", listeContigueDesEvent(calendar, "TP S"));

			calendarBil = convertWeekCalToWeekCalBil(calendar);

			freeCalendar(&calendar);

			fclose(file);
			fclose(fileOut);
		}
		else
		{
			printf("Erreur fichier");
		}
	}
	else
	{
		printf("Erreur argument\n");
	}

    return 0;
}

