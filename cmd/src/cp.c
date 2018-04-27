#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/cp.h"
#include "../utils/macro_main.h"

MAIN(cp)

int cp(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Bad use");
        return -1;
    }

    FILE* fileSource = NULL;
    FILE* fileDestination = NULL;
    int currentChar;


    if ((fileSource = fopen(argv[0], "r")) == NULL) {
        printf("%s, %s\n", argv[0], strerror(errno));
        return -1;
    }

    if ((fileDestination = fopen(argv[1], "w+")) == NULL) {
        printf("%s, %s\n", argv[1], strerror(errno));
        return -1;
    }

    while ((currentChar = fgetc(fileSource)) != EOF) {
        fputc(currentChar, fileDestination);
    }

    fclose(fileSource);
    fclose(fileDestination);
    return 0;
}
