#ifndef _CMD_H_
#define _CMD_H_

typedef int (*cmd_t)(int,char**);

#ifdef INTEGRATED_FUNCTION
#include "include/echo.h"
#include "include/pwd.h"
#include "include/cd.h"

cmd_t getCmd(char *name);
#endif

#endif
