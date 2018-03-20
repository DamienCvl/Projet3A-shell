CC = gcc
NAME_PROGRAMME = "Shell"
SOURCE_EXECUTABLE = cmd/src/echo.c cmd/src/pwd.c
NAME_EXECUTABLE = 'echo' 'pwd'
BIN = cmd/lib/
SOURCE_INTEGRATED_FUNCTION = "add source"
SOURCE_LIBRARY = "add source"

all: executable

#EXECUTABLE
executable:
	$(CC) cmd/src/echo.c -o echo.exe -D CREATE_MAIN
	$(CC) cmd/src/pwd.c -o pwd.exe -D CREATE_MAIN
	mv *.exe $(BIN)

#INTEGRATED_FUNCTION
executable_function:
	@$(CC) -DINTEGRATED_FUNCTION $(SOURCE_INTEGRATED_FUNCTION)

#LIBRARY
executable.so: main.c
	@$(CC) -DLIBRARY $(SOURCE_LIBRARY)

clean:
	@/bin/rm -f *.o

re: clean all
