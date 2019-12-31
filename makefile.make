CC=g++
CFLAGS=-I.
DEPS = main_file.h
OBJ = functions.o main_file.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

functions: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)