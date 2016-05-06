CFLAGS=-Wall -g  -g -O2



all : teste4

teste4 : teste4.o xwc.o
	${CC} ${CFLAGS} -o teste4 teste4.o xwc.o  -lm -lXpm -lX11

xwc.o : xwc.c


clean: 
	rm -f *.o teste4 *~ 

