#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "../cmd/include/echo.h"
#include "../cmd/include/pwd.h"

typedef int (*function)(int,char**);

function getFunction(char *name);

#endif
