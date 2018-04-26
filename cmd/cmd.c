#ifdef INTEGRATED_FUNCTION

#include <string.h>
#include "cmd.h"

#include "include/echo.h"
#include "include/pwd.h"
#include "include/cat.h"
#include "include/cd.h"
#include "include/rm.h"
#include "include/ls.h"
#include "include/chmod.h"
#include "include/cp.h"

int NB_CMD = 7;
cmd_t CMD_FUNCTIONS[] = {echo, pwd, cat, cd, rm, ls, chmod, cp};
char *CMD_NAMES[] = {"echo", "pwd", "cat", "cd", "rm", "ls", "chmod", "cp"};

cmd_t getCmd(char *name) {
  for (int i = 0; i < NB_CMD; i++) {
    if (strcmp(name, CMD_NAMES[i]) == 0) {
      return CMD_FUNCTIONS[i];
    }
  }
  return NULL;
}

#endif
