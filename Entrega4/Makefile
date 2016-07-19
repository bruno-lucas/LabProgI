#pegando as variáveis <-- para referencia
# $@ --- alvo
# $< --- 1a dependência
# $^ --- lista de dependência s/ repetição
# $+ --- lista de dependência
# $? --- lista de dependência mais "recentes"

CFLAGS= -Wall -g  -lm

#gerando executável
Main:	resultante.o cinematica.o xwc.o graph.o Main.o
	${CC} ${CFLAGS} -o $@ $^ -lm -lXpm -lX11

resultante.o:	resultante.c estruturas.h
	${CC} -c $^ ${CFLAGS} -lm

cinematica.o:	cinematica.c estruturas.h

#ignorar e deletar o teste
teste.o:	teste.c
	${CC} -c $^ -lXpm -lX11 ${CFLAGS}

teste:	teste.o xwc.o
	${CC} ${CFLAGS} -o $@ $^ -lm -lXpm -lX11

xwc.o:	xwc.c 
	${CC} -c $^ -lXpm -lX11 ${CFLAGS}

graph.o:	graph.c estruturas.h
	${CC} -c $^ -lXpm -lX11 ${CFLAGS} -lm

Main.o:	Main.c
	${CC} -c $^ -lXpm -lX11

clean:	
	rm *.o

# sei que já tem o zip e tals, mas colocar um método pra
#	imprimir é uma prática interessnate
empacotar:	
	@mkdir entrega
	cp  *.c ./entrega
	cp  *.h ./entrega
	cp  *.txt ./entrega
	cp *.docx ./entrega
	cp  Makefile ./entrega
	tar -cvf entrega.tar entrega
	rm -rf ./entrega
