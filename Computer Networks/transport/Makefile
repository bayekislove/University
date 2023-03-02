CC=g++
OBJ=transport.o udp.o wrappers.o window.p
CFLAGS= -Wall -Wextra

transport:
	${CC} ${CFLAGS} -c transport.cpp
	${CC} -o transport transport.o

clean:
	rm -f *.o

distclean:
	rm -f *.o *.out transport