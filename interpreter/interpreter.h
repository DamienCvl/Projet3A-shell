#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

  char *readInput();
  void displayPromptAndDirectory();
  int parseInput(char *parsed[], char *input);
  int interpret(int argc, char *argv[]);
  int onBording();
  int out();

#endif
