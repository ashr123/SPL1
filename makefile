GREEN=\e[103m\033[1;34m
NC=\033[0m
CC=g++
CFLAGS=-g -Wall -Weffc++ -std=c++11
LFLAGS= -L/usr/lib

all: Hello
Hello: bin/FileSystem.o bin/Commands.o bin/main.o bin/Files.o bin/Environment.o 
	@echo 'Building target: Hello'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/Hello bin/FileSystem.o bin/Commands.o bin/main.o bin/Files.o bin/Environment.o $(LFLAGS)
	@echo 'Finished building target: Hello'

bin/Files.o: src/Files.cpp
	@echo -e '${GREEN}Compiling target: Files.cpp${NC}'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Files.o src/Files.cpp
	@echo ''

bin/main.o: src/main.cpp
	@echo -e '${GREEN}Compiling target: main.cpp${NC}'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp
	@echo ''

bin/Environment.o: src/Environment.cpp
	@echo -e '${GREEN}Compiling target: Environment.cpp${NC}'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Environment.o src/Environment.cpp
	@echo ''

bin/FileSystem.o: src/FileSystem.cpp
	@echo -e '${GREEN}Compiling target: FileSystem.cpp${NC}'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp
	@echo ''

bin/Commands.o: src/Commands.cpp
	@echo -e '${GREEN}Compiling target: Commands.cpp${NC}'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Commands.o src/Commands.cpp
	@echo ''

clean:
	rm -f bin/*
