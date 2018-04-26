#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "interpreter.h"
#include "call.h"
#include "redirection.h"

#define MAX_SIZE_ARG 100
#define MAX_ARGS 25
#define BUFFER_SIZE 1024

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char **argv) {
    char **parsedInput;
    pid_t cpid;
    int status;
    do {
        displayPromptAndDirectory();
        char *input = readInput();
        parsedInput = malloc(MAX_ARGS);
        int nombreArgument = parseInput(parsedInput, input);

        cpid = fork();
        if (cpid == 0) {
          interpret(nombreArgument, parsedInput);
          return 0;
        }

        waitpid(cpid, &status, 0);
    } while (1);
    return 0;
}

int interpret(int argc, char *argv[]){
  for (int i = 0; i < argc; i++) {
    if (strcmp("||", argv[i]) == 0) {
      return !interpret(i, argv) || interpret(argc - i - 1, argv + i + 1);
    }
    else if (strcmp("&&", argv[i]) == 0) {
      return !interpret(i, argv) && interpret(argc - i - 1, argv + i + 1);
    }
  }
  for (int i = argc-1; i > 0; i--) {
    if (strcmp("|", argv[i]) == 0) {
      return redirectionCommandeVersCommande(i, argv, argc - i - 1, argv + i + 1);
    }
    else if (strcmp(">", argv[i]) == 0) {
      return redirectionCommandeVersFichierEnEcrasant(i, argv, argc - i - 1, argv + i + 1);
    }
    else if (strcmp(">>", argv[i]) == 0) {
      return redirectionCommandeVersFichierEnAjout(i, argv, argc - i - 1, argv + i + 1);
    }
    else if (strcmp("<", argv[i]) == 0) {
      return redirectionFichierVersCommande(i, argv, argc - i - 1, argv + i + 1);
    }
    else if (strcmp("<<", argv[i]) == 0) {
      return redirectionClavierVersCommande(i, argv, argc - i - 1, argv + i + 1);
    }
  }
  return call(argc, argv);
}

void displayPromptAndDirectory() {
    char dir[1024];
    getcwd(dir, sizeof(dir));
    printf(ANSI_COLOR_GREEN "%s$ " ANSI_COLOR_RESET, dir);
}

char *readInput() {
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, stdin);
    return line;
}

int parseInput(char *parsed[], char *input) {
  int indexCurrentCommande = 0, nombreArgument = 0, indexDansInput = 0;
  char currentChar = input[indexDansInput];

  while (currentChar != '\n' || nombreArgument > MAX_ARGS) {
    if (indexCurrentCommande == 0) {
      parsed[nombreArgument] = malloc(sizeof(char) * MAX_SIZE_ARG);
    }

    if (currentChar == ' ') {
      parsed[nombreArgument][indexCurrentCommande] = '\0';
      nombreArgument++;
      indexCurrentCommande = 0;
    } else {
      parsed[nombreArgument][indexCurrentCommande] = currentChar;
      indexCurrentCommande++;
    }
    indexDansInput++;
    currentChar = input[indexDansInput];
  }
  return nombreArgument + 1;
}
