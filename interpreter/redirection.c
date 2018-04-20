#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "call.h"

#define BUFFER_SIZE 1024

int myPipe(char *entree, char *sortie, int (*fctEntree)(char *), int (*fctSortie)(char *)){
   int fd[2];
   pid_t pid_fils;
   pipe(fd);

   if ((pid_fils = fork()) == -1) {
     perror("fork");
     return -1;
   }

   if (pid_fils == 0) {
     close(fd[0]);
     (*fctEntree)(entree);
   } else {
     close(fd[1]);
     (*fctSortie)(sortie);
     wait(NULL);
   }
   return 0;
}

int redirigerVersInterpreteur(char *sortie) {
  int currentChar ;
  char *buffer[BUFFER_SIZE];
  strcpy(buffer, sortie);
  strcpy(buffer, " \"");
  while (!feof(stdin)) {
    currentChar = fgetc(stdin);
    strcpy(buffer, currentChar);
  }
  strcpy(buffer, "\"");
  interpreteur(buffer);
  return 0;
}

int redirigerVersFichier(char *filename, char *mode) {
  FILE *fichier = NULL;
  fichier = fopen(filename, mode);
  int currentChar ;
  while (currentChar != '\n') {
    currentChar = fgetc(stdin);
    fputc(currentChar, fichier);
  }
  return 0;
}

int redirigerVersFichierEnAjout(char *filename) {
  redirigerVersFichier(filename, "a");
  return 0;
}

int redirigerVersFichierEnEcrasant(char *filename) {
  remove(filename);
  redirigerVersFichier(filename, "w");
  return 0;
}

int lireDepuisFichier(char *filename) {
  return 0;
}

int lireDepuisClavier(char *inutile) {
  return 0;
}

// Interfaces de redirection
int redirectionCommandeVersCommande(char *entree, char *sortie) {
  return myPipe(entree, sortie, interpreteur, redirigerVersInterpreteur);
}

int redirectionCommandeVersFichierEnAjout(char *entree, char *sortie) {
  return myPipe(entree, sortie, interpreteur, redirigerVersFichierEnAjout);
}

int redirectionCommandeVersFichierEnEcrasant(char *entree, char *sortie) {
  return myPipe(entree, sortie, interpreteur, redirigerVersFichierEnEcrasant);
}

int redirectionFichierVersCommande(char *entree, char *sortie) {
  return myPipe(entree, sortie, lireDepuisFichier, interpreteur);
}

int redirectionClavierVersCommande(char *entree, char *sortie) {
  return myPipe(entree, sortie, lireDepuisClavier, interpreteur);
}
