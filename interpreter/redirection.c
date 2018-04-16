#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "call.h"

#define BUFFER_SIZE 1024

 int my_pipe(char *entree, char *sortie, int (*fct)(char *)){
   int fd[2];
   pid_t pid_fils;
   pipe(fd);

   if ((pid_fils = fork()) == -1) {
     perror("fork");
     exit(1);
   }

   if (pid_fils == 0) {
     close(fd[0]);
     interpreteur(entree);
   } else {
     close(fd[1]);
     redirectionNormal(sortie);
     exit(0);
   }
   wait(NULL);
   return 0;
}

int redirectionNormal(char *sortie){
  int currentChar ;
  char *buffer[BUFFER_SIZE];
  strcpy(buffer, sortie);
  strcpy(buffer, ' \"');
  while (!feof(stdin)) {
    currentChar = fgetc(stdin);
    strcpy(buffer, currentChar);
  }
  strcpy(buffer, '\"');
  interpreteur(buffer);
  return 0;
}

int redirectionFichierAjout(char *filename) {
  redirectionFichier(filename, "a");
}

int redirectionFichierEcraser(char *filename) {
  remove(filename);
  redirectionFichier(filename, "w");
}

int redirectionFichier(char *filename, char *mode) {
  FILE *fichier = NULL;
  fichier = fopen(filename, mode);
  int currentChar ;
  while (currentChar != '\n') {
    currentChar = fgetc(stdin);
    fputc(currentChar, fichier);
  }
}

  int redirectionEntre();
    /*  <  */
    //Prend le fichier dans l'entrée
    // cat < monFichier.txt

 int redirectionEntreClavier();
    /*  <<  */
    //Prend le entrée standard jusqu'a l'entrée donné
    // sort << FIN
