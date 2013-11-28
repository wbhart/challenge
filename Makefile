CXX=g++ -g -O2 -std=c++11
CC=gcc -g -O2
INC=
LIB=
OBJS=n.o nn.o zz.o ZZ.o Poly.o	
HEADERS=Poly.h ZZ.h zz.h nn.h n.h common.h
TESTS=t-ZZ t-Poly

all: $(OBJS)

ZZ.o: ZZ.cpp $(HEADERS)
	$(CXX) -c -o ZZ.o ZZ.cpp $(INC)

zz.o: zz.c $(HEADERS)
	$(CC) -c -o zz.o zz.c $(INC)

nn.o: nn.c $(HEADERS)
	$(CC) -c -o nn.o nn.c $(INC)

n.o: n.c $(HEADERS)
	$(CC) -c -o n.o n.c $(INC)

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
