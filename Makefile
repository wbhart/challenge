CXX=g++ -g -std=c++11
CC=gcc -g
INC=
LIB=
OBJS=n.o nn.o zz.o ZZ.o
HEADERS=ZZ.h zz.h nn.h n.h common.h
TESTS=t-ZZ

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

check: $(TESTS)
	./t-ZZ

clean:
	rm -f *.o
	rm -f t-ZZ

.PHONY: all clean
