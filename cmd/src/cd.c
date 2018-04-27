#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "../include/cd.h"
#include "../utils/macro_main.h"

MAIN(cd)

int cd(int argc, char *argv[]) {
    char *path;

    if (argc == 0 || argv[0][0] == '~') {
        path = getenv("HOME");
    }
    else {
        path = argv[0];
    }

    if (chdir(path) != 0) {
        printf("cd: %s: %s\n", path, strerror(errno));
        return -1;
    }
    return 0;
}
