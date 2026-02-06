CC = gcc
CFLAGS = -Wall -Wextra -fPIC
LIB = libmath.so

so: math.o
	$(CC) -shared -o $(LIB) math.o

math.o: math.c math.h
	$(CC) $(CFLAGS) -c math.c

app: so main.o
	$(CC) main.o -L. -lmath -o app

main.o: main.c math.h
	$(CC) -Wall -Wextra -c main.c

run:
	LD_LIBRARY_PATH=. ./app

clean:
	rm -f *.o *.so app
