CC = g++
CFLAGS = -g -Wall -Weffc++ -std=c++11
LFLAGS = -L/usr/lib

all: Hello
Hello: bin/main.o bin/Files.o 
	@echo 'Building target: Hello'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/Hello bin/main.o bin/Files.o $(LFLAGS)
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

clean:
	rm -f bin/*