GREEN=\e[103m\033[1;34m
NC=\033[0m
CC=g++
CFLAGS=-g -Wall -Weffc++ -std=c++11 -c -Iinclude -o
LFLAGS=-L/usr/lib

all: First Hello
Hello: bin/FileSystem.o bin/Commands.o bin/main.o bin/Files.o bin/Environment.o 
	@echo -e '${GREEN}Invoking: C++ Linker${NC}'
	$(CC) -o bin/Hello bin/FileSystem.o bin/Commands.o bin/main.o bin/Files.o bin/Environment.o $(LFLAGS)
	@echo ''
	@echo -e '\e[105m\033[1;96mFinished building target: Hello\033[0m'

bin/Files.o: src/Files.cpp
	@echo -e '${GREEN}Compiling target: Files.cpp${NC}'
	$(CC) $(CFLAGS) bin/Files.o src/Files.cpp
	@echo ''

bin/main.o: src/main.cpp
	@echo -e '${GREEN}Compiling target: main.cpp${NC}'
	$(CC) $(CFLAGS) bin/main.o src/main.cpp
	@echo ''

bin/Environment.o: src/Environment.cpp
	@echo -e '${GREEN}Compiling target: Environment.cpp${NC}'
	$(CC) $(CFLAGS) bin/Environment.o src/Environment.cpp
	@echo ''

bin/FileSystem.o: src/FileSystem.cpp
	@echo -e '${GREEN}Compiling target: FileSystem.cpp${NC}'
	$(CC) $(CFLAGS) bin/FileSystem.o src/FileSystem.cpp
	@echo ''

bin/Commands.o: src/Commands.cpp
	@echo -e '${GREEN}Compiling target: Commands.cpp${NC}'
	$(CC) $(CFLAGS) bin/Commands.o src/Commands.cpp
	@echo ''

First:
	@echo -e '\e[105m\033[1;96mBuilding target: Hello\033[0m'

clean:
	rm -f bin/*