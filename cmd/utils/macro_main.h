#ifndef _MACRO_MAIN_H_
#define _MACRO_MAIN_H_

#ifdef CREATE_MAIN
#define MAIN(cmd) int main(int argc, char *argv[]) { cmd(argc - 1, argv + 1); return 0; }

#else
#define MAIN(cmd)
#endif

#endif
