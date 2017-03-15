#Lucas Lopilato
#165A MP2
#

CXX=g++
CXXFLAGS=-std=c++11 -lstdc++

OBJECTS = Gobang.o Player.o Board.o Move.o Direction.o

Gobang : $(OBJECTS)
	$(CXX) $(OBJECTS) -o Gobang

%.o : %.c
	$(CXX) -std=c++11 $(CXXFLAGS) -c $< -o $@

run: clean Gobang
	./Gobang -n 5
	rm -f Gobang *.o

clean:
	rm -f Gobang *.o

