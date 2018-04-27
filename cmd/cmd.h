#ifndef _CMD_H_
#define _CMD_H_

typedef int (*cmd_t)(int,char**);

#ifdef INTEGRATED_FUNCTION
// Sorte d'interface permettant de récupérer les fonctions des commandes à partir de leur nom :
// utile pour l'exécutable avec les fonctions intégrées
cmd_t getCmd(char *name);
#endif

#endif
