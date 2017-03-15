#Lucas Lopilato
#165A MP2
#

CXX=g++
LFLAGS=
CXXFLAGS=-std=c++11 -Wall -Werror -Wextra -lstdc++

OBJECTS = Gobang.o Player.o Board.o Move.o Direction.o

Gobang : $(OBJECTS)
	$(CXX) $(OBJECTS) -o Gobang

%.o : %.c
	$(CXX) -pg -std=c++11 $(CXXFLAGS) -c $< -o -pg $@

run: clean Gobang
	./Gobang -n 5
	rm -f Gobang *.o

leak: clean Gobang
	valgrind --leak-check=full ./Gobang

clean:
	rm -f Gobang *.o

