#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define PATH_CMD "../cmd/bin/"
#define CMD_PATH_SIZE 512

 int my_pipe(char * nomCommandeEntree, char * nomCommandeSortie){
   int fd[2];

   char commandeEntree[CMD_PATH_SIZE];
   strcpy(commandeEntree, PATH_CMD);
   strcat(commandeEntree, nomCommandeEntree);

   char commandeSortie[CMD_PATH_SIZE];
   strcpy(commandeSortie, PATH_CMD);
   strcat(commandeSortie, nomCommandeSortie);

   pid_t pid_fils;

   pipe(fd);

   //on doit fork() pour copier l'entrée et la sortie
   //possibilité de fail alors on catch

   if((pid_fils = fork()) == -1) {
     perror("fork");
     exit(1);
   }

   //On veut que le pere recoive des donnes depuis le fils
   //Il faut close(fd[1]) du pere et close(fd[0]) du fils
   //Maintenant que le pipeline est créé fd doit être traiter comme d'habitude

   if (pid_fils == 0) {
     close(0);
     dup(fd[0]);
     execl(commandeSortie, commandeSortie, NULL);
     exit(0);
   } else {
     close(fd[1]);
     execl(commandeEntree, commandeEntree, NULL);
   }
   return 0;
}
