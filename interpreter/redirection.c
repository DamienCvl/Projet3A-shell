#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "call.h"
#include "interpreter.h"
#include "redirection.h"

#define BUFFER_SIZE 1024

int myPipe(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[], int (*fctEntree)(int, char *[]), int (*fctSortie)(int, char *[])){
   int fd[2];
   pid_t pid_fils;
   pipe(fd);

   if ((pid_fils = fork()) == -1) {
     perror("fork");
     return -1;
   }

   if (pid_fils == 0) {
     close(fd[0]);
     dup2(fd[1],STDOUT_FILENO);
     (*fctEntree)(argcEntree, argvEntree);
   } else {
     close(fd[1]);
     dup2(fd[0],STDIN_FILENO);
     (*fctSortie)(argcSortie, argvSortie);
   }
   return 0;
}

int redirigerVersInterpreteur(int argcSortie, char *argvSortie[]) {
  char currentChar;
  char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
  strcpy(buffer, "");
  while ((currentChar!='\n') && (currentChar!=EOF)) {
    currentChar = fgetc(stdin);
    strcat(buffer, &currentChar);
  }
  char **argv = malloc(argcSortie + 1);
  for (int i = 0; i < argcSortie; i++) {
    argv[i] = argvSortie[i];
  }
  argv[argcSortie] = buffer;
  interpret(argcSortie + 1, argv);
  free(buffer);
  free(argv);
  return 0;
}

int redirigerVersFichier(char *filename, char *mode) {
  FILE *fichier = NULL;
  fichier = fopen(filename, mode);
  int currentChar;
  while ((currentChar!='\n') && (currentChar!=EOF)) {
    currentChar = fgetc(stdin);
    fputc(currentChar, fichier);
  }
  fclose(fichier);
  return 0;
}

int redirigerVersFichierEnAjout(int argcSortie, char *argvSortie[]) {
  char *filename = argvSortie[0];
  redirigerVersFichier(filename, "a");
  return 0;
}

int redirigerVersFichierEnEcrasant(int argcSortie, char *argvSortie[]) {
  char *filename = argvSortie[0];
  remove(filename);
  redirigerVersFichier(filename, "w");
  return 0;
}

int lireDepuisFichier(int argcEntree, char *argvEntree[]) {
  FILE *fichier = NULL;
  char *filename = argvEntree[0];
  fichier = fopen(filename, "r");
  int currentChar;
  while (!feof(fichier)) {
    currentChar = fgetc(stdin);
    printf("%c", currentChar);
  }
  fclose(fichier);
  return 0;
}

int lireDepuisClavier(int argcEntree, char *argvEntree[]) {
  char *chaine = NULL;
  char *fin = argvEntree[0];
  do {
    if (chaine != NULL)
      printf("%s", chaine);
    scanf("%s", chaine);
  } while (strcmp(chaine, fin) != 0);
  return 0;
}

// Interfaces de redirection
int redirectionCommandeVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
  return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, interpret, redirigerVersInterpreteur);
}

int redirectionCommandeVersFichierEnAjout(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
  return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, interpret, redirigerVersFichierEnAjout);
}

int redirectionCommandeVersFichierEnEcrasant(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
  return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, interpret, redirigerVersFichierEnEcrasant);
}

int redirectionFichierVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
  return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, lireDepuisFichier, interpret);
}

int redirectionClavierVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
  return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, lireDepuisClavier, interpret);
}
