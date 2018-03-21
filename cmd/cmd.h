#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

typedef int (*cmd_t)(int,char**);

#ifdef INTEGRATED_FUNCTION
#include "include/echo.h"
#include "include/pwd.h"

cmd_t getCmd(char *name);
#endif

#endif
