CC=gcc
OPTIONS=-Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`


main: socket.o main.o
	$(CC) $(OPTIONS) main.o socket.o  `pkg-config --libs-only-l MLV` -o main

main.o: main.c main.h
	$(CC) $(OPTIONS) -c main.c

socket.o: socket.c socket.h
	$(CC) $(OPTIONS) -c socket.c
 
clear: 
	rm *.o main 