#include <stdio.h>
#include "../include/echo.h"

#ifdef CREATE_MAIN
#include "../include/macro_main.h"
MAIN(echo)
#endif

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
