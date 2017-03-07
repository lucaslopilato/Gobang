#Lucas Lopilato
#165A MP2
#

CC	= g++ #clang++ 
LFLAGS = -pthread
CFLAGS = -g

OBJECTS = Gobang.o Player.o

Gobang : $(OBJECTS)
	$(CC) $(OBJECTS) -o Gobang

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f Gobang *.o

