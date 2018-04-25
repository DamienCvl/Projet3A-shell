#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/wait.h>
#include "call.h"
#include "../cmd/cmd.h"

int call(int argc, char *argv[]) {
  char *cmd_name = argv[0];
  int exit_value;
#ifdef EXECUTABLE
  char path[80];
  strcpy(path, "cmd/bin/");
  strcat(path, cmd_name);
  pid_t cpid;
  int status;

  cpid = fork();
  if (cpid == 0) {
    return execv(path, argv);
  }

  waitpid(cpid, &status, 0);
  return status;
#elif INTEGRATED_FUNCTION
  cmd_t cmd = getCmd(cmd_name);
  if (cmd)
    return cmd(argc - 1, argv + 1);
  return -1;
#elif LIBRARY
  char path[80];
  strcpy(path, "cmd/lib/lib");
  strcat(path, cmd_name);
  strcat(path, ".so");
  void *handle = dlopen(path, RTLD_NOW);

  if (handle) {
       cmd_t cmd = dlsym(handle, cmd_name);
       cmd(argc - 1, argv + 1);
  }
#endif
}
