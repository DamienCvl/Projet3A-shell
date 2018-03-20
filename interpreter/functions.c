#include <string.h>
#include "functions.h"

int NB_CMD = 2;
function CMD_FUNCTIONS[] = {echo, pwd};
char *CMD_NAMES[] = {"echo", "pwd"};

function getFunction(char *name) {
  for (int i = 0; i < NB_CMD; i++) {
    if (strcmp(name, CMD_NAMES[i]) == 0) {
      return CMD_FUNCTIONS[i];
    }
  }
  return NULL;
}
