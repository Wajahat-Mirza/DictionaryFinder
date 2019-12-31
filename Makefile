CC=g++
CFLAGS=-I.
DEPS = binary_search.h
OBJ = mydictionary.o binary_search.o 

output: mydictionary.o binary_search.o 
	g++ binary_search.o mydictionary.o -o mydictionary.out
	$(info =====================================================================================================)
	$(info .WELCOME TO Dictionary FINDER APP!)
	$(info .NOTE! Call program using format: ./mydictionary -d <filename> -l < number of words output>)
	$(info .INSTRUCTIONS: There are three main commands (without angular brackets))
	$(info .1: find a word by typing it in)
	$(info .2: find words starting with a prefix by putting * at the end like "expl*")
	$(info .3: find words with prefix and suffix by putting ? in between like "exp?ore")
	$(info ===================================================
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mydictionary: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)