#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "call.c"

char *readCmd();
char **concCmd(char *cmd);
void directory();

int main(int argc, char **argv)
{
    char *cmd;
    char **args;
    int isLooping ; //savoir quand quitter

    do {
        directory();
        printf("\n> ");
        cmd = readCmd();
        args = concCmd(cmd);
        isLooping = call(args);

        free(cmd); //à remplacer par une insertion dans une stack (flèche du haut)
        free(args);
    } while (isLooping);

    return EXIT_SUCCESS;
}

void directory()
{
    char dir[1024];
    getcwd(dir, sizeof(dir));
    printf("\n> %s", dir);
}

char *readCmd()
{
    char *line = NULL;
    unsigned long bufsize = 0; //faut-il plus grand ?
    getline(&line, &bufsize, stdin);
    return line;
}

#define BUFFERSIZE_TOKEN 64
#define STROK_DELIM " \n"
char **concCmd(char *cmd)
{
    int tokBuff = BUFFERSIZE_TOKEN;
    int  indice = 0;
    char *tokens = malloc(tokBuff * sizeof(char));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Cannot Allocate Memory\n"); //Pas sur du message d'erreur d'allocation
        exit(EXIT_FAILURE);
    }

    token = strtok(cmd, STROK_DELIM);
    while (token != NULL) {
        tokens[indice] = token;
        indice++;

        if (indice >= tokBuff) {
            tokBuff += tokBuff;
            tokens = realloc(tokens, tokBuff * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Cannot Allocate Memory\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, STROK_DELIM);
    }
    tokens[indice] = NULL;
    return tokens;
}

