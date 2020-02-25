#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgol.h"


/* 
 * Program Name: dyncgol.c
 * Author(s): Nathan Verghis
 * Date: November 20, 2019
 * Purpose: Reads in seeded input from user-decided file
 *          Computes Conway's Game of Life and displays
 *          to STDIN
 * Compilation: gcc -ansi -Wall -o dyncgol.c dyncgol
 * Execution: ./dyncgol (x) (y z) (x represents desired number of generations)
 * (y represents rows and z represents columns if user wishes to change dimensions)
 */ 


int main(int argc, char *argv[]){

   /*Variable Declarations*/
   FILE *f1;
   char input[500];
   int correct = 1;
   int maxTicks = 50;
   char fileName[30];
   int i = 0;
   int j = 0;
   int k = 0;
   int count = 0;
   int total = 0;
   int changed;
   int addition;
   int rows;
   int columns;
   int rowCount = 0;
   int colCount = 0;
   
   
   /*Check if there are enough command line parameters*/
   if (argc < 5) {
      printf("Insufficient command line parameters\n");
      exit(1);
   }else if (argc == 5){
      if (atoi(argv[2]) > 0){
         maxTicks = atoi(argv[2]);
      }else {
         printf("Inadmissable generation count\n");
         exit(1);
      }
      if(atoi(argv[3]) <= 0){
         printf("Inadmissable row number\n");
         exit(1);
      }else if(atoi(argv[4]) <= 0){
         printf("Inadmissable generation count\n");
         exit(1);
      }
      rows = atoi(argv[3]);
      columns = atoi(argv[4]);
   }else {
      printf("Inadmissable parameters\n");
      exit(1);
   }
   addition = maxTicks;  

   /*Declaring variable dependent on user input*/
   int currentGen [rows][columns];
   int nextGen [rows][columns];
   char string[columns * 3];

   /*Opening the file, checking if file matches command line specifications*/
   strcpy(fileName, argv[1]);
   chop(fileName);
   if ((f1 = fopen(fileName, "r")) != NULL ) {
      while ( fgets(string, 100, f1) != NULL ) {
         chop(string);
         for (k = 0; k < strlen(string); k++){
            if (string[k] == 48 || string[k] == 49){
               colCount++;
            }
         }
         if (colCount != columns){
            printf("Invalid column count\n");
            exit(1);
         }
         colCount = 0;
         rowCount++;
      }
      fclose(f1);
   }else {
      printf ("Cannot open %s\n", fileName);
      exit (1);
   }
   if (rowCount != rows){
      printf("Invalid row count\n");
      exit(1);
   }

   /*Opening the file, reading in the seed*/
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
   for(i = 0; i < columns; i++){
      printf("-");
   }
   printf("\n");
   for(i = 0; i < rows; i++){
      printf("|");
      for(j = 0; j < columns; j++){
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
   for(i = 0; i < columns; i++){
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
      for(i = 0; i < columns; i++){
         printf("-");
      }
      printf("\n");
      for(i = 0; i < rows; i++){
         printf("|");
         for(j = 0; j < columns; j++){
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
      for(i = 0; i < columns; i++){
         printf("-");
      }
      printf("%d\n", count);
      count++;
      i = 0;
      j = 0;

      /*Calculating next generation*/
      for(i = 0; i < rows; i++){
         for(j = 0; j < columns; j++){
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
            }else if (i == 0 && j == (columns - 1)){
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
            }else if (i == (rows - 1) && j == 0){
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
            }else if (i == (rows - 1) && j == (columns - 1)){
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
            }else if (i == (rows - 1)){
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
            }else if (j == (columns - 1)){
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
      for(i = 0; i < rows; i++){
         for(j = 0; j < columns; j++){
            if(nextGen[i][j] == currentGen[i][j]){
               changed++;
            }
         }
      }
      if(changed == (rows * columns)){
         exit(1);
      }
      changed = 0;
     
      /*Setting next generation as current generation*/
      for(i = 0; i < rows; i++){
         for(j = 0; j < columns; j++){
            currentGen[i][j] = nextGen[i][j];
         }
      }

      /*Asking if user wants to continue*/
      if (count == maxTicks + 1){
         while(correct){
           printf("Continue? (y or n): ");
           fgets(input, 500, stdin);
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
