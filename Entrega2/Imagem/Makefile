CFLAGS=-Wall -g  -g -O2



all : teste4 animacao

teste4 : teste4.o xwc.o
	${CC} ${CFLAGS} -o teste4 teste4.o xwc.o  -lm -lXpm -lX11
animacao : animacao.o xwc.o
	${CC} ${CFLAGS} -o animacao animacao.o xwc.o -lm -lXpm -lX11

xwc.o : xwc.c


clean: 
	rm -f *.o teste4 *~ 

