CC=g++
OBJ=webserver.o HttpResponse.o
CFLAGS= -Wall -Wextra

webserver:
		${CC} ${CFLAGS} -c webserver.cpp
		${CC} -o webserver webserver.o

clean:
		rm -f *.o

distclean:
		rm -f *.o *.out webserver