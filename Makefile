CC = gcc<
NAME_PROGRAMME = "Shell"
SOURCE_EXECUTABLE = cmd/src/echo.c cmd/src/pwd.c
BIN = cmd/lib/
SOURCE_INTEGRATED_FUNCTION = "add source"
SOURCE_LIBRARY = "add source"

all: executable

#EXECUTABLE
executable:
	#Pb ca créer un seul executable
	@$(CC) $(SOURCE_EXECUTABLE) -o $(NAME_PROGRAMME) -D CREATE_MAIN
	@mv $(NAME_PROGRAMME) cmd/bin/

#INTEGRATED_FUNCTION
executable_function:
	@$(CC) -DINTEGRATED_FUNCTION $(SOURCE_INTEGRATED_FUNCTION)

#LIBRARY
executable.so: main.c
	@$(CC) -DLIBRARY $(SOURCE_LIBRARY)

clean:
	@/bin/rm -f *.o

re: clean all
