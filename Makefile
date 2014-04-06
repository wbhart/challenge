CXX=g++ -Wall -ansi -pedantic -g -O2
CC=gcc -Wall -ansi -pedantic -g -O2
INC=
LIB=
OBJS=word.o nn_t.o ZZ.o
HEADERS=ZZ.h nn_t.h word.h common.h
TESTS=t-ZZ

all: $(OBJS)

ZZ.o: ZZ.c $(HEADERS)
	$(CXX) -c -o ZZ.o ZZ.c $(INC)

nn_t.o: nn_t.c $(HEADERS)
	$(CC) -c -o nn_t.o nn_t.c $(INC)

word.o: word.c $(HEADERS)
	$(CC) -c -o word.o word.c $(INC)

t-ZZ: t-ZZ.c $(OBJS) $(HEADERS)
	$(CXX) -o t-ZZ t-ZZ.c $(OBJS) $(INC) -lm

check: $(TESTS)
	./t-ZZ

clean:
	rm -f *.o
	rm -f t-ZZ

.PHONY: all clean
