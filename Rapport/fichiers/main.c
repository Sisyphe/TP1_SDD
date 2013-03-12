/*
 * main.c
 *
 * Gerald Lelong / Noel Martignoni
 * ISIMA
 * SDD TP1
 * 02/01/13
 *
 * Programme principal
 */

#include <stdio.h>
#include <stdlib.h>

#include "handler.h"

int main(int argc, const char * argv[])
{
    calendar_t calendar = newCalendar();
    FILE * file, * fileOut;
    char * liste;
    
    /*if (argc == 2)
    {*/
        file = fopen("/Users/darkshadow/Developper/SDDTP1/SDDTP1/file", "r");
        fileOut = fopen("output.dat", "w");
        
        if (file && fileOut)
        {
            importFileCalendar(calendar, file);
            printCalendar(calendar);
            exportFileCalendar(calendar, fileOut);
            
            liste=listeContigueDesEvent(calendar, "TP S");
            printf("%s", liste);
            free(liste);
            
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
    
    freeCalendar(&calendar);
    
    return 0;
}

