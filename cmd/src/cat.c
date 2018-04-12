#include <stdio.h>
#include "../include/echo.h"

#ifdef CREATE_MAIN
#include "../include/macro_main.h"
MAIN(cat)
#endif

char *cat(int argc, char *argv[]);
