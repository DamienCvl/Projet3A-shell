#include <stdio.h>
#include <unistd.h>
#include "../include/pwd.h"
#include "../utils/macro_main.h"

MAIN(pwd)

int pwd(int argc, char *argv[]) {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
      return -1;
  }
  printf("%s\n", cwd);
  return 0;
}
