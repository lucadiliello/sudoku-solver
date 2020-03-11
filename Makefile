CC=g++

# CFLAGS will be the options passed to the compiler.
CFLAGS= -c -Wall

all:
	$(CC) main.o read_csv.o -o build/prog

main.o: main.cc
	$(CC) $(CFLAGS) main.cc

read_csv.o: read_csv.cc
	$(CC) $(CFLAGS) read_csv.cc

clean:
	rm -rf build/*