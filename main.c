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
    weekCal_t * headWeekCal = NULL;
	FILE * file, * fileOut;

	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		fileOut = fopen("output.dat", "w");

		if (file && fileOut)
		{
			importSortedFileCalendar(&headWeekCal, file);
			printCalendar(headWeekCal);
			exportFileCalendar(headWeekCal, fileOut);

			printf("%s", listeContigueDesEvent(headWeekCal, "TP S"));

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

