#include <stdio.h>
#include "../include/echo.h"
#include "../utils/macro_main.h"

MAIN(echo)

int echo(int argc, char *argv[]) {
  if (argc >= 1) {
	for (int i = 0; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");
  }
  else {
    printf("\n");
  }
  return 0;
}
