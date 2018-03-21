# On vera plus tard pour faire un makefile propre

all: generate_command_executables generate_command_libraries generate_as_executable generate_as_integrated_function

generate_command_executables:
	gcc -o cmd/bin/echo cmd/src/echo.c -D CREATE_MAIN
	gcc -o cmd/bin/pwd cmd/src/pwd.c -D CREATE_MAIN

generate_command_libraries:
	gcc -shared -o cmd/lib/libecho.so -fPIC cmd/src/echo.c -D CREATE_MAIN
	gcc -shared -o cmd/lib/libpwd.so -fPIC cmd/src/pwd.c -D CREATE_MAIN

generate_as_executable:
	gcc -o asExecutable interpreter/test.c interpreter/call.c -D EXECUTABLE

generate_as_integrated_function:
	gcc -o asIntegratedFunction interpreter/test.c interpreter/call.c interpreter/functions.c cmd/src/echo.c  cmd/src/pwd.c -D INTEGRATED_FUNCTION

generate_as_library:
	gcc -o asLibrary interpreter/test.c interpreter/call.c -D LIBRARY -ldl

clean:
	@/bin/rm -f *.o

re: clean all
