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

#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

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

        // Simulation d'une commande 'exit' pour quitter le programme
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
    // Vérification de la présence d'opérateurs de chaînage conditionnels de commandes
    for (int i = 0; i < argc; i++) {
        if (strcmp("||", argv[i]) == 0) {
            // Si la première commande échoue, la deuxième est exécutée
            return !interpret(i, argv) || interpret(argc - i - 1, argv + i + 1);
        }
        else if (strcmp("&&", argv[i]) == 0) {
            // Si la première commande réussie, la deuxième est exécutée
            return !interpret(i, argv) && interpret(argc - i - 1, argv + i + 1);
        }
    }

    int (*redirection)(int, char**, int, char **) = NULL;
    int position;
    // Vérification de la présence de redirections
    for (position = argc - 1; position > 0; position--) {
        if (strcmp("|", argv[position]) == 0) {
            redirection = redirectionCommandeVersCommande;
            break;
        }
        else if (strcmp(">", argv[position]) == 0) {
            redirection = redirectionCommandeVersFichierEnEcrasant;
            break;
        }
        else if (strcmp(">>", argv[position]) == 0) {
            redirection = redirectionCommandeVersFichierEnAjout;
            break;
        }
        else if (strcmp("<", argv[position]) == 0) {
            redirection = redirectionFichierVersCommande;
            break;
        }
        else if (strcmp("<<", argv[position]) == 0) {
            redirection = redirectionClavierVersCommande;
            break;
        }
    }
    if (redirection != NULL) {
        // Passage des arguments pour l'entrée et la sortie de la redirection
        return redirection(position, argv, argc - position - 1, argv + position + 1);
    }

    // Si il n'y a pas de caractères de redirection :
    // Appel de la fonction call, pour exécuter la commande correspondante
    return call(argc, argv);
}

char *readInput() {
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, stdin); // Lecture de la ligne depuis l'entrée standard
    return line;
}

// Analyse de la chaine entrée, pour en récupérer la liste d'arguments
int parseInput(char *parsed[], char *input) {
    int indexCurrentCharArgument = 0, nombreArgument = 0, indexInput = 0;
    char currentChar = input[indexInput];

    while (currentChar != '\n' || nombreArgument > MAX_ARGS) {
        if (indexCurrentCharArgument == 0) {
            // Nouvel argument : allocation d'un nouveau bloc
            parsed[nombreArgument] = malloc(sizeof(char) * MAX_SIZE_ARG);
            nombreArgument++;
        }

        if (currentChar == ' ') { // Séparateur d'arguments (espace)
            parsed[nombreArgument - 1][indexCurrentCharArgument] = '\0';
            indexCurrentCharArgument = 0;
        }
        else { // Ajout du caractère courant dans l'argument courant
            parsed[nombreArgument - 1][indexCurrentCharArgument] = currentChar;
            indexCurrentCharArgument++;
        }
        indexInput++;
        currentChar = input[indexInput];
    }
    return nombreArgument;
}

void displayPromptAndDirectory() {
    char currentDirectory[1024];
    getcwd(currentDirectory, sizeof(currentDirectory)); // Récupération du répertoire de travail courant
    printf(ANSI_COLOR_GREEN "%s$ " ANSI_COLOR_RESET, currentDirectory);
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
