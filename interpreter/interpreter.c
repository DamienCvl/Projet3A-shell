#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "call.h"

#define TAILLE_MAX_ARGUMENT 100
#define NBR_MAX_DE_COMMANDE 25
#define BUFFER_SIZE 1024

char *readInput();
void directory();
int parseInput(char *parsed[], char *input);
int interpret(int argc, char *argv[]);

int main(int argc, char **argv) {
    char *cmd;
    char **args;
    char parsedInput[NBR_MAX_DE_COMMANDE][TAILLE_MAX_ARGUMENT];
    do {
        directory();
        char *input = readInput();
        int nombreArgument = parseInput(parsedInput, input);
        interpret(nombreArgument, parsedInput);
    } while (1);
    return EXIT_SUCCESS;
}

int interpret(int argc, char *argv[]){
  for (int i = argc-1; i > 0; i--) {
    if (strcmp("|", argv[i]) == 0) {
      //redirectionCommandeVersCommande(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp(">", argv[i]) == 0) {
      //redirectionCommandeVersFichierEnEcrasant(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp(">>", argv[i]) == 0) {
      //redirectionCommandeVersFichierEnAjout(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp("<", argv[i]) == 0) {
      //redirectionFichierVersCommande(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp("<<", argv[i]) == 0) {
      //redirectionClavierVersCommande(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else {
      call(argc, argv);
    }
  }
}

void directory() {
    char dir[1024];
    getcwd(dir, sizeof(dir));
    printf("\n%s $", dir);
}

char *readInput() {
    char *line = NULL;
    unsigned int bufsize = BUFFER_SIZE;
    getline(&line, &bufsize, stdin);
    return line;
}

int parseInput(char *parsed[], char *input) {
  int currentIndex = 0, nombreArgument = 0;
  char currentChar = input[currentIndex];

  while (currentChar != '\n' || nombreArgument > NBR_MAX_DE_COMMANDE) {
    if (currentChar == ' ') {
      parsed[nombreArgument][currentIndex + 1] = '\0';
      nombreArgument++;
      currentIndex = 0;
    } else {
      parsed[nombreArgument][currentIndex] = currentChar;
    }
  }
  return nombreArgument;
}
