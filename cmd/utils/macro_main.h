#ifndef _MACRO_MAIN_H_
#define _MACRO_MAIN_H_

#ifdef CREATE_MAIN
// Création d'un main dans chaque exécutable :
// utile pour la génération des exécutables de chaque commande
#define MAIN(cmd) int main(int argc, char *argv[]) { cmd(argc - 1, argv + 1); return 0; }

#else
#define MAIN(cmd)
#endif

#endif
