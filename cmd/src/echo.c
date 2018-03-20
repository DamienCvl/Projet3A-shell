#include <stdio.h>
#include "../include/echo.h"

#ifdef CREATE_MAIN
#include "../include/macro_main.h"
MAIN(echo)
#endif

int echo(int argc, char *argv[]) {
  if (argc >= 1) {
    printf("%s\n", argv[0]);
  }
  else {
    printf("\n");
  }
  return 0;
}
