#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

char *readInput();
void displayPromptAndDirectory();
int parseInput(char *parsed[], char *input);
int interpret(int argc, char *argv[]);
void sayHi();
void sayGoodBye();
void fork_interpret(int argc, char *argv[]);

#endif
