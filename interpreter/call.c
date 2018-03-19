#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include "call.h"

int call(int argc, char *argv[]) {
  char *cmd = argv[0];
#ifdef EXECUTABLE
  char path[80];
  strcpy(path, "../cmd/bin/");
  strcat(path, cmd);
  execv(path, argv + 1);
#elif INTEGRATED_FUNCTION

#elif LIBRARY
  char path[80];
  strcpy(path, "../cmd/lib/");
  strcat(path, cmd);
  strcat(path, ".so");
  void *handle = dlopen(path, RTLD_NOW);

  if (handle) {
       int (*fct)(int,char**);
       fct = dlsym(handle, cmd);
       fct(argc - 1, argv + 1);
  }
#endif
}
