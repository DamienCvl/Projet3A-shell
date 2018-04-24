#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

  char *readInput();
  void directory();
  int parseInput(char *parsed[], char *input);
  int interpret(int argc, char *argv[]);

#endif
