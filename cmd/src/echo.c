#include <stdio.h>
#include "../include/macro_main.h"
#include "../include/echo.h"

int echo(int argc, char *argv[]) {
  if (argc >= 1) {
    printf("%s\n", argv[0]);
  }
  else {
    printf("\n");
  }
  return 0;
}

#ifdef CREATE_MAIN
MAIN(echo)
#endif
