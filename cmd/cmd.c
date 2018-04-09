#ifdef INTEGRATED_FUNCTION

#include <string.h>
#include "cmd.h"

#include "include/echo.h"
#include "include/pwd.h"
#include "include/cd.h"
#include "include/rm.h"

int NB_CMD = 2;
cmd_t CMD_FUNCTIONS[] = {echo, pwd, cd, rm};
char *CMD_NAMES[] = {"echo", "pwd", "cd", "rm"};

cmd_t getCmd(char *name) {
  for (int i = 0; i < NB_CMD; i++) {
    if (strcmp(name, CMD_NAMES[i]) == 0) {
      return CMD_FUNCTIONS[i];
    }
  }
  return NULL;
}

#endif
