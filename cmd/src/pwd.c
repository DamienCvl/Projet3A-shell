#include <stdio.h>
#include <unistd.h>
#include "../include/pwd.h"
#include "../utils/macro_main.h"

MAIN(pwd)

int pwd(int argc, char *argv[]) {
  char cwd[1024];
  // Récupération du répertoire de travail courant grâce à l'appel system getcwd
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
      return -1;
  }
  printf("%s\n", cwd);
  return 0;
}
