#Lucas Lopilato
#165A MP2
#

CC	= clang++
LFLAGS = -pthread
CFLAGS = -g

OBJECTS = Gobang.o Player.o Board.o Move.o Direction.o

Gobang : $(OBJECTS)
	$(CC) $(OBJECTS) -o Gobang

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: clean Gobang
	./Gobang -n 5
	rm -f Gobang *.o

leak: clean Gobang
	valgrind --leak-check=yes ./Gobang

clean:
	rm -f Gobang *.o

