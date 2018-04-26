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

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char **argv) {
    char **parsedInput;
    char *input;
    int loop = 1;

    sayHi();
    do {
        displayPromptAndDirectory();
        input = readInput();
        parsedInput = malloc(MAX_ARGS);
        int nombreArgument = parseInput(parsedInput, input);
        free(input);

        if (nombreArgument >= 1 && strcmp(parsedInput[0], "exit") == 0) {
          loop = 0;
        }
        else {
          fork_interpret(nombreArgument, parsedInput);
        }
    } while (loop);
    sayGoodBye();
    return 0;
}

void fork_interpret(int argc, char *argv[]) {
  pid_t cpid;
  int status;

  if ((cpid = fork()) == 0) {
    exit(interpret(argc, argv));
  }

  waitpid(cpid, &status, 0);
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

char *readInput() {
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, stdin);
    return line;
}

int parseInput(char *parsed[], char *input) {
  int indexCurrentCharArgument = 0, nombreArgument = 0, indexInput = 0;
  char currentChar = input[indexInput];

  while (currentChar != '\n' || nombreArgument > MAX_ARGS) {
    if (indexCurrentCharArgument == 0) {
      parsed[nombreArgument] = malloc(sizeof(char) * MAX_SIZE_ARG);
      nombreArgument++;
    }

    if (currentChar == ' ') {
      parsed[nombreArgument - 1][indexCurrentCharArgument] = '\0';
      indexCurrentCharArgument = 0;
    }
    else {
      parsed[nombreArgument - 1][indexCurrentCharArgument] = currentChar;
      indexCurrentCharArgument++;
    }
    indexInput++;
    currentChar = input[indexInput];
  }
  return nombreArgument;
}

void displayPromptAndDirectory() {
    char dir[1024];
    getcwd(dir, sizeof(dir));
    printf(ANSI_COLOR_GREEN "%s$ " ANSI_COLOR_RESET, dir);
}

void sayHi() {
  printf(ANSI_COLOR_CYAN
    "\n=============================================\n"
    "=   Bienvenue sur le Mini-Shell créé par    =\n"
    "=\t\tJohan Sorette               =\n"
    "=\t\tDamien Chevalerias          =\n"
    "=\t\tBastien Chupin              =\n"
    "=\t\tYves Le Palud               =\n="
    "============================================\n\n");
}

void sayGoodBye() {
  printf(ANSI_COLOR_CYAN "\nA bientôt !\n\n");
}
