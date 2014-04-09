CXX=g++ -Wall -ansi -pedantic -g -O2
CC=gcc -Wall -ansi -pedantic -g -O2
INC=
LIB=
OBJS=word.o nn_t.o ZZ.o numthy.o
HEADERS=numthy.h ZZ.h nn_t.h word.h common.h
TESTS=t-ZZ t-numthy

all: $(OBJS)

numthy.o: numthy.c $(HEADERS)
	$(CXX) -c -o numthy.o numthy.c $(INC)

ZZ.o: ZZ.c $(HEADERS)
	$(CXX) -c -o ZZ.o ZZ.c $(INC)

nn_t.o: nn_t.c $(HEADERS)
	$(CC) -c -o nn_t.o nn_t.c $(INC)

word.o: word.c $(HEADERS)
	$(CC) -c -o word.o word.c $(INC)

t-Poly: t-Poly.c $(OBJS) $(HEADERS)
	$(CXX) -o t-Poly t-Poly.c $(OBJS) $(INC) -lm

t-ZZ: t-ZZ.c $(OBJS) $(HEADERS)
	$(CXX) -o t-ZZ t-ZZ.c $(OBJS) $(INC) -lm

t-numthy: t-numthy.c $(OBJS) $(HEADERS)
	$(CXX) -o t-numthy t-numthy.c $(OBJS) $(INC) -lm

check: $(TESTS)
	./t-ZZ
	./t-numthy

clean:
	rm -f *.o
	rm -f t-ZZ

.PHONY: all clean
