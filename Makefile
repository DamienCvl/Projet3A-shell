CC=gcc
COMMANDS= echo pwd cd rm
PATH_BIN=cmd/bin/
PATH_LIB=cmd/lib/
PATH_COMMAND_SRC=cmd/src/
PATH_COMMAND=cmd/
PATH_INTERPRETER=interpreter/

all: as_executable as_integrated_function as_library

command_executables:
	@if [ ! -d "$(PATH_BIN)" ]; then\
  	mkdir "$(PATH_BIN)";\
	fi
	@for cmd in $(COMMANDS); do\
		$(CC) -o $(PATH_BIN)$$cmd $(PATH_COMMAND_SRC)$$cmd.c -D CREATE_MAIN;\
	done

command_libraries:
	@if [ ! -d "$(PATH_LIB)" ]; then\
  	mkdir "$(PATH_LIB)";\
	fi
	@for cmd in $(COMMANDS); do\
		$(CC) -shared -o $(PATH_LIB)lib$$cmd.so -fPIC $(PATH_COMMAND_SRC)$$cmd.c -D CREATE_MAIN;\
	done

as_executable: command_executables
	@$(CC) -o asExecutable $(PATH_INTERPRETER)*.c -D EXECUTABLE

as_integrated_function:
	@$(CC) -o asIntegratedFunction $(PATH_INTERPRETER)*.c $(PATH_COMMAND)*.c $(PATH_COMMAND_SRC)*.c -D INTEGRATED_FUNCTION

as_library: command_libraries
	@$(CC) -o asLibrary $(PATH_INTERPRETER)*.c -D LIBRARY -ldl

clean:
	@/bin/rm -f *.o

re: clean all
