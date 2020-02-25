#include <string.h>
#include <stdlib.h>

/* 
 * Program Name: chop.c
 * Author(s): Nathan Verghis
 * Date: November 3, 2019
 * Purpose: Reads in line of string.
 *          Removes \n and all string following
 *          Return count of removed \n.
 *          Cannot be run independent of main
 */ 

int chop ( char *line ) {
   int i = 0;
   int works = -1;
   for (i = 0; i < strlen(line); i++){
      if (strcmp(&line[i], "\n") == 0){
         line[i] = *"\0";
         works = 0;
      }
   }
   return(works);
}

