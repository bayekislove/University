CC=gcc
OBJ=traceroute.o icmp.o wrappers.o
CFLAGS= -Wall -Wextra

traceroute:
	${CC} ${CFLAGS} -c traceroute.c
	${CC} -o traceroute traceroute.o

clean:
	rm -f *.o

distclean:
	rm -f *.o *.out traceroute