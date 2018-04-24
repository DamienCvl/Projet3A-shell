#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "interpreter.h"
#include "call.h"
#include "redirection.h"

#define MAX_SIZE_ARG 100
#define MAX_ARGS 25
#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    char *cmd;
    char **args;
    char **parsedInput;
    do {
        directory();
        char *input = readInput();
        int nombreArgument = parseInput(parsedInput, input);
        interpret(nombreArgument, parsedInput);
    } while (1);
    return 0;
}

int interpret(int argc, char *argv[]){
  for (int i = argc-1; i > 0; i--) {
    if (strcmp("|", argv[i]) == 0) {
      return redirectionCommandeVersCommande(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp(">", argv[i]) == 0) {
      return redirectionCommandeVersFichierEnEcrasant(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp(">>", argv[i]) == 0) {
      return redirectionCommandeVersFichierEnAjout(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp("<", argv[i]) == 0) {
      return redirectionFichierVersCommande(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else if (strcmp("<<", argv[i]) == 0) {
      return redirectionClavierVersCommande(i - 1, &argv[0], i + 1, &argv[i + 1]);
    }
    else {
      return call(argc, argv);
    }
  }
}

void directory() {
    char dir[1024];
    getcwd(dir, sizeof(dir));
    printf("%s$ ", dir);
}

char *readInput() {
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, stdin);
    return line;
}

int parseInput(char *parsed[], char *input) {
  int currentIndex = 0, nombreArgument = 0;
  char currentChar = input[currentIndex];

  parsed = malloc(MAX_ARGS);
  parsed[0] = malloc(sizeof(char) * MAX_SIZE_ARG);

  while (currentChar != '\n' || nombreArgument > MAX_ARGS) {
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
