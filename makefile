CC = g++
CFLAGS = -g -Wall -Weffc++ -std=c++11
LFLAGS = -L/usr/lib

all: Hello
Hello: bin/FileSystem.o bin/Commands.o bin/main.o bin/Files.o bin/Environment.o 
	@echo 'Building target: Hello'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/Hello bin/FileSystem.o bin/Commands.o bin/main.o bin/Files.o bin/Environment.o $(LFLAGS)
	@echo 'Finished building target: Hello'

bin/Files.o: src/Files.cpp
	@echo ''
	@echo ''
	@echo ''
	@echo 'Compiling target: Files.cpp'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Files.o src/Files.cpp

bin/main.o: src/main.cpp
	@echo ''
	@echo ''
	@echo ''
	@echo 'Compiling target: main.cpp'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

bin/Environment.o: src/Environment.cpp
	@echo ''
	@echo ''
	@echo ''
	@echo 'Compiling target: Environment.cpp'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Environment.o src/Environment.cpp

bin/FileSystem.o: src/FileSystem.cpp
	@echo ''
	@echo ''
	@echo ''
	@echo 'Compiling target: FileSystem.cpp'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp

bin/Commands.o: src/Commands.cpp
	@echo ''
	@echo ''
	@echo ''
	@echo 'Compiling target: Commands.cpp'
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Commands.o src/Commands.cpp

clean:
	rm -f bin/*