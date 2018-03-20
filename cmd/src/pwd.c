#include <stdio.h>
#include <unistd.h>
#include "../include/pwd.h"

#ifdef CREATE_MAIN
#include "../include/macro_main.h"
MAIN(pwd)
#endif

int pwd(int argc, char *argv[]) {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL)
       printf("%s\n", cwd);
  return 0;
}
