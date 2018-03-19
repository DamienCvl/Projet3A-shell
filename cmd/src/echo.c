#include <stdio.h>
#include "../include/echo.h"

int echo(int argc, char *argv[]) {
  if (argc > 1) {
    printf("%s\n", argv[1]);
  }
  else {
    printf("\n");
  }
  return 0;
}
