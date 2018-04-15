#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "call.h"

#define PATH_CMD "../cmd/bin/"
#define CMD_PATH_SIZE 512

 int my_pipe(int argcEntree, char *nomCommandeEntree[], int argcSortie, char *nomCommandeSortie[]){
   /*  |  */
   int fd[2];
   pid_t pid_fils;
   pipe(fd);

   //on doit fork() pour copier l'entrée et la sortie
   //possibilité de fail alors on catch

   if ((pid_fils = fork()) == -1) {
     perror("fork");
     exit(1);
   }

   //On veut que le pere recoive des donnes depuis le fils
   //Il faut close(fd[1]) du pere et close(fd[0]) du fils
   //La sortie de fd[1] devient l'entré de fd[0]
   //Maintenant que le pipeline est créé fd doit être traiter comme d'habitude

   //Envoie de donnes depuis l'enfant vers le parent
   if (pid_fils == 0) {
     close(0);
     dup(fd[0]);
     call(argcEntree, nomCommandeSortie);
     exit(0);
   } else {
     close(fd[1]);
     call(argcSortie, nomCommandeEntree);
   }
   wait(NULL);
   return 0;
}

int redirectionAvecAjout(int argc, char *commande[], char *file){
    /*  >>  */
    FILE *fichier = NULL;
    fichier = fopen(file, "a");
    int fd[2];
    pid_t pid_fils;

    if (fichier != NULL) {
      pipe(fd);

      if ((pid_fils = fork()) == -1) {
        perror("fork");
        exit(1);
      }

      //On veut que l'enfant récupère les données du parents
      //Le parent execute la commande le fils écrit
      if (pid_fils == 0) {
        close(fd[1]);

        int currentChar ;
        while (currentChar != '\n') {
          currentChar = fgetc(stdin);
          fputc(currentChar, fichier);
        }

        exit(0);
      } else {
        close(fd[0]);
        call(argc, commande);
      }
    } else {
      perror("ouverture");
      exit(1);
    }
    wait(NULL);
    fclose(fichier);
    return 0;
}

int redirection(int argc, char *commande[], char *file) {
  /*  >  */
  remove(file);
  FILE *fichier = NULL;
  fichier = fopen(file, "w");
  int fd[2];
  pid_t pid_fils;

  if (fichier != NULL) {
      pipe(fd);

      if ((pid_fils = fork()) == -1) {
        perror("fork");
        exit(1);
      }

      //On veut que l'enfant récupère les données du parents
      //Le parent execute la commande le fils écrit
      if (pid_fils == 0) {
        close(fd[1]);

        int currentChar ;
        while (currentChar != '\n') {
          currentChar = fgetc(stdin);
          fputc(currentChar, fichier);
        }

        exit(0);
      } else {
        close(fd[0]);
        call(argc, commande);
      }
    } else {
      perror("ouverture");
      exit(1);
    }
    wait(NULL);
    fclose(fichier);
    return 0;
  }
