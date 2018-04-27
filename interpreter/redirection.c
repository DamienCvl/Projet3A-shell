#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "interpreter.h"
#include "redirection.h"

#define WAIT_CHILD 1
#define DO_NOT_WAIT_CHILD 0

int myPipe(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[], int (*fctEntree)(int, char *[]), int (*fctSortie)(int, char *[]), int waitChild){
    int fd[2];
    pid_t pid_fils;
    int status;
    pipe(fd);

    // Création du processus fils avec duplication du file descriptor sur les deux processus
    if ((pid_fils = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (pid_fils == 0) {
        close(fd[0]); // Fermeture de l'entrée standard du processus fils
        dup2(fd[1],STDOUT_FILENO);
        return (*fctEntree)(argcEntree, argvEntree);
    }

    close(fd[1]); // Fermeture de la sortie standard du processus parent
    dup2(fd[0],STDIN_FILENO);
    if (waitChild) { // Attente du processus enfant avant d'exécuter la commande
        waitpid(pid_fils, &status, 0);
    }
    return (*fctSortie)(argcSortie, argvSortie);
}

int redirigerVersFichier(char *filename, char *mode) {
    FILE *fichier = NULL;
    fichier = fopen(filename, mode);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    // Récupération ligne par ligne de l'entrée standard du processus
    while ((read = getline(&line, &len, stdin)) != -1) {
        fputs(line, fichier); // Ecrire dans le fichier
    }
    if (line) {
        free(line);
    }

    fclose(fichier);
    return 0;
}

int redirigerVersFichierEnAjout(int argcSortie, char *argvSortie[]) {
    char *filename = argvSortie[0];
    redirigerVersFichier(filename, "a"); // Mode ajout
    return 0;
}

int redirigerVersFichierEnEcrasant(int argcSortie, char *argvSortie[]) {
    char *filename = argvSortie[0];
    remove(filename); // Suppression de l'ancien fichier
    redirigerVersFichier(filename, "w"); // Mode ecriture
    return 0;
}

int lireDepuisFichier(int argcEntree, char *argvEntree[]) {
    FILE *fichier = NULL;
    char *filename = argvEntree[0];
    fichier = fopen(filename, "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    // Lecture du fichier ligne par ligne
    while ((read = getline(&line, &len, fichier)) != -1) {
        printf("%s", line); // Envoie du contenu au processus parent qui écoûte
    }
    if (line) {
        free(line);
    }

    fclose(fichier);
    return 0;
}

int lireDepuisClavier(int argcEntree, char *argvEntree[]) {
    char *fin = argvEntree[0];
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    strcat(fin, "\n");
    do {
        getline(&line, &len, stdin);
        if (strcmp(line, fin) != 0) { // Lecture du clavier jusqu'à retrouver la chaine de fin donnée
            printf("%s", line); // Envoie du contenu au processus parent qui écoûte
        }
    } while (strcmp(line, fin) != 0);
    return 0;
}

// Interfaces de redirection
int redirectionCommandeVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
    return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, interpret, interpret, DO_NOT_WAIT_CHILD);
}

int redirectionCommandeVersFichierEnAjout(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
    return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, interpret, redirigerVersFichierEnAjout, DO_NOT_WAIT_CHILD);
}

int redirectionCommandeVersFichierEnEcrasant(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
    return myPipe(argcEntree, argvEntree, argcSortie, argvSortie, interpret, redirigerVersFichierEnEcrasant, DO_NOT_WAIT_CHILD);
}

int redirectionFichierVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
    // Switch des entrées/sorties, pour que la commande soit le processus parent, afin qu'elle puisse traiter le contenu
    return myPipe(argcSortie, argvSortie, argcEntree, argvEntree, lireDepuisFichier, interpret, DO_NOT_WAIT_CHILD);
}

int redirectionClavierVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]) {
    // Switch des entrées/sorties, pour que la commande soit le processus parent, afin qu'elle puisse traiter le contenu
    return myPipe(argcSortie, argvSortie, argcEntree, argvEntree, lireDepuisClavier, interpret, WAIT_CHILD);
}
