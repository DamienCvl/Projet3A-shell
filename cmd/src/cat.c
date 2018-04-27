#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/cat.h"
#include "../utils/macro_main.h"

MAIN(cat)

int cat(int argc, char *argv[]) {
    FILE *file;
    if (argc >= 1) {
        // Lecture à partir du fichier passé en paramètre
        char *filename = argv[0];

        file = fopen(filename,"r");

        if (!file) {
            printf("cat: %s: %s\n", filename, strerror(errno));
            return -1;
        }
    }
    else {
        // Si nom de fichier non renseigné : lecture depuis l'entrée standard
        file = stdin;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
    }
    if (line) {
        free(line);
    }

    fclose(file);
    return 0;
}
