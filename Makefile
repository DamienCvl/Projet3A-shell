CC = "gcc"
NAME_PROGRAMME = "Shell"
SOURCE_EXECUTABLE = "/cmd/src/echo.c /cmd/src/pwd.c"
SOURCE_INTEGRATED_FUNCTION = "add source"
SOURCE_LIBRARY = "add source"

#Si on fait un make sans argument on compile en mode EXECUTABLE
all: executable

#EXECUTABLE
executable: executable_c
\t$(CC) *.o -o $(NAME_PROGRAMME)
	#Il faut move les executable vers le bin Sinon ca doit marcher

executable_c:
\t$(CC) $(SOURCE_EXECUTABLE) -c

#INTEGRATED_FUNCTION
executable_function:
\t$(CC) -DINTEGRATED_FUNCTION $(SOURCE_INTEGRATED_FUNCTION)

#LIBRARY
executable.so: main.c
\t$(CC) -DLIBRARY $(SOURCE_LIBRARY)

clean:
\t/bin/rm -f *.o

re: clean all
