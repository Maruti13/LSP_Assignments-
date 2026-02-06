CC = gcc
AR = ar
CFLAGS = -Wall -Wextra
LIB = libmath.a

lib: math.o
	$(AR) rcs $(LIB) math.o

math.o: math.c math.h
	$(CC) $(CFLAGS) -c math.c

app: lib main.o
	$(CC) main.o -L. -lmath -o app

main.o: main.c math.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o *.a app
