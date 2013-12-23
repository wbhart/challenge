CXX=g++ -Wall -g -O2 -std=c++11
CC=gcc -Wall -g -O2
INC=
LIB=
OBJS=word.o nn_t.o zz_t.o ZZ.o Poly.o	
HEADERS=Poly.h ZZ.h zz_t.h nn_t.h word.h common.h
TESTS=t-ZZ t-Poly

all: $(OBJS)

ZZ.o: ZZ.cpp $(HEADERS)
	$(CXX) -c -o ZZ.o ZZ.cpp $(INC)

zz_t.o: zz_t.c $(HEADERS)
	$(CC) -c -o zz_t.o zz_t.c $(INC)

nn_t.o: nn_t.c $(HEADERS)
	$(CC) -c -o nn_t.o nn_t.c $(INC)

word.o: word.c $(HEADERS)
	$(CC) -c -o word.o word.c $(INC)

t-ZZ: t-ZZ.cpp $(OBJS) $(HEADERS)
	$(CXX) -o t-ZZ t-ZZ.cpp $(OBJS) $(INC) -lm

Poly.o: Poly.cpp $(HEADERS)
	$(CXX) -c -o Poly.o Poly.cpp $(INC)

t-Poly: t-Poly.cpp $(OBJS) $(HEADERS)
	$(CXX) -o t-Poly t-Poly.cpp $(OBJS) $(INC) -lm

check: $(TESTS)
	./t-ZZ
	./t-Poly

clean:
	rm -f *.o
	rm -f t-ZZ
	rm -f t-Poly

.PHONY: all clean
