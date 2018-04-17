#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/cd.h"

#ifdef CREATE_MAIN
#include "../utils/macro_main.h"
MAIN(cd)
#endif

int cd(int argc, char *argv[]) {
  char *path;

  if (argc == 0 || argv[0][0] == '~') {
    path = getenv("HOME");
  }
  else {
    path = argv[0];
  }

  if (chdir(path) != 0) {
    printf("cd: %s:No such file or directory\n", path);
  }
  return 0;
}
