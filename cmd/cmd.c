#ifdef INTEGRATED_FUNCTION

#include <string.h>
#include "cmd.h"

int NB_CMD = 2;
cmd_t CMD_FUNCTIONS[] = {echo, pwd, cd};
char *CMD_NAMES[] = {"echo", "pwd", "cd"};

cmd_t getCmd(char *name) {
  for (int i = 0; i < NB_CMD; i++) {
    if (strcmp(name, CMD_NAMES[i]) == 0) {
      return CMD_FUNCTIONS[i];
    }
  }
  return NULL;
}

#endif
