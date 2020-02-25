#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgol.h"


/* 
 * Program Name: cgol.c
 * Author(s): Nathan Verghis
 * Date: November 20, 2019
 * Purpose: Reads in seeded input from user-decided file
 *          Computes Conway's Game of Life and displays
 *          to STDIN
 * Compilation: gcc -ansi -Wall -o cgol.c cgol
 * Execution: ./cgol (x) (x represents desired number of generations)
 */ 


int main(int argc, char *argv[]){

   /*Variable Declarations*/
   FILE *f1;
   char input[500];
   int correct = 1;
   int maxTicks = 50;
   char string[100];
   char fileName[10];
   int currentGen [20][40];
   int nextGen [20][40];
   int i = 0;
   int j = 0;
   int k = 0;
   int count = 0;
   int total = 0;
   int changed;
   int addition;
   
   
   /*Check if there are enough command line parameters*/
   if (argc < 2) {
      printf("Insufficient command line parameters\n");
      exit(1);
   }else if (argc == 3){
      if (atoi(argv[2]) > 0){
         maxTicks = atoi(argv[2]);
      }
   }else {
      printf("Too many command line parameters\n");
      exit(1);
   }
   addition = maxTicks;   

   /*Opening the file, reading in the seed*/
   strcpy(fileName, argv[1]);
   chop(fileName);
   if ((f1 = fopen(fileName, "r")) != NULL ) {
      while ( fgets(string, 100, f1) != NULL ) {
         chop(string);
         for (k = 0; k < strlen(string); k++){
            if (string[k] == 48){
               currentGen[j][i] = 0;
               i++;
            }else if(string[k] == 49){
               currentGen[j][i] = 1;
               i++;
            }
         }
         i = 0;
         j++;
      }
      fclose(f1);
   }else {
      printf ("Cannot open %s\n", fileName);
      exit (1);
   }

   /*Displaying First Generation*/
   system("clear");
   printf(" ");
   for(i = 0; i < 40; i++){
      printf("-");
   }
   printf("\n");
   for(i = 0; i < ROWS; i++){
      printf("|");
      for(j = 0; j < COLUMNS; j++){
         if(currentGen[i][j] == 1){
            printf("x");
         }else {
            printf(" ");
         }
      }
      printf("|");
      printf("\n");
   }
   printf(" ");
   for(i = 0; i < 40; i++){
      printf("-");
   }
   printf("%d\n", count);

   /*Determining if user wishes to start program*/
   while(correct){
      printf("Start? (y or n): ");
      fgets(input, 500, stdin);
      chop(input);
      if (strcmp(input, "y") != 0 && strcmp(input, "n") != 0 && strcmp(input, "Y") != 0 && strcmp(input, "N") != 0){
         printf("Invalid input. Please answer 'y' or 'n'.\n");
      }else {
         correct = 0;
         if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0){
            exit(1);
         }
      }
   }
   correct = 1;

   /*calculating and displaying the generations*/
   while(count <= maxTicks){
      changed = 0;
      system("sleep 0.25");
      system("clear");
      printf(" ");
      for(i = 0; i < 40; i++){
         printf("-");
      }
      printf("\n");
      for(i = 0; i < ROWS; i++){
         printf("|");
         for(j = 0; j < COLUMNS; j++){
            if(currentGen[i][j] == 1){
               printf("x");
            }else {
               printf(" ");
            }
         }
         printf("|");
         printf("\n");
      }
      printf(" ");
      for(i = 0; i < 40; i++){
         printf("-");
      }
      printf("%d\n", count);
      count++;
      i = 0;
      j = 0;

      /*Calculating next generation*/
      for(i = 0; i < ROWS; i++){
         for(j = 0; j < COLUMNS; j++){
            if (i == 0 && j == 0){
               total = currentGen[i][j + 1] + currentGen[i + 1][j + 1] + currentGen[i + 1][j];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else if (i == 0 && j == 39){
               total = currentGen[i][j - 1] + currentGen[i + 1][j - 1] + currentGen[i + 1][j];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else if (i == 19 && j == 0){
               total = currentGen[i][j + 1] + currentGen[i - 1][j + 1] + currentGen[i - 1][j];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else if (i == 19 && j == 39){
               total = currentGen[i][j - 1] + currentGen[i - 1][j - 1] + currentGen[i - 1][j];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else if (i == 0){
               total = currentGen[i][j - 1] + currentGen[i + 1][j + 1] + currentGen[i + 1][j] + currentGen[i + 1][j - 1] + currentGen[i][j + 1];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else if (i == 19){
               total = currentGen[i][j + 1] + currentGen[i - 1][j - 1] + currentGen[i - 1][j] + currentGen[i - 1][j + 1] + currentGen[i][j - 1];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else if (j == 0){
               total = currentGen[i][j + 1] + currentGen[i + 1][j + 1] + currentGen[i + 1][j] + currentGen[i - 1][j] + currentGen[i - 1][j + 1];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else if (j == 39){
               total = currentGen[i][j - 1] + currentGen[i + 1][j - 1] + currentGen[i + 1][j] + currentGen[i - 1][j - 1] + currentGen[i - 1][j];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }else{
               total = currentGen[i][j + 1] + currentGen[i + 1][j + 1] + currentGen[i + 1][j] + currentGen[i + 1][j - 1] + currentGen[i][j - 1] + currentGen[i - 1][j - 1] + currentGen[i - 1][j] + currentGen[i - 1][j + 1];
               if(currentGen[i][j] == 1){
                  if(total < 2 || total > 3){
                     nextGen[i][j] = 0;
                  }else {
                     nextGen[i][j] = 1;
                  }
               }else{
                  if (total == 3){
                     nextGen[i][j] = 1;
                  }else {
                     nextGen[i][j] = 0;
                  }
               }
            }
         }
      }

      /*Checking if there were any changes between generations*/
      for(i = 0; i < ROWS; i++){
         for(j = 0; j < COLUMNS; j++){
            if(nextGen[i][j] == currentGen[i][j]){
               changed++;
            }
         }
      }
      if(changed == 800){
         exit(1);
      }
      changed = 0;
     
      /*Setting next generation as current generation*/
      for(i = 0; i < ROWS; i++){
         for(j = 0; j < COLUMNS; j++){
            currentGen[i][j] = nextGen[i][j];
         }
      }

      /*Asking if user wants to continue*/
      if (count == maxTicks + 1){
         while(correct){
           printf("Continue? (y or n): ");
           fgets(input, 5, stdin);
            chop(input);
            if (strcmp(input, "y") != 0 && strcmp(input, "n") != 0 && strcmp(input, "Y") != 0 && strcmp(input, "N") != 0){
               printf("Invalid input. Please answer 'y' or 'n'.\n");
            }else {
               if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0){
                  exit(1);
               }else {
                  maxTicks += addition;
                  correct = 0;
               }
            }
         }
         correct = 1;
      }
   }
   
   return(0);
}
