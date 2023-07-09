CC = gcc
CFLAGS = -Wall -pthread

all: order fork-join rendezvous

order: order.c
	$(CC) $(CFLAGS) -o order order.c

fork-join: fork-join.c
	$(CC) $(CFLAGS) -o fork-join fork-join.c -lrt

rendezvous: rendezvous.c
	$(CC) $(CFLAGS) -o rendezvous rendezvous.c

clean:
	rm -f order fork-join rendezvous
