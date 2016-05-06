#Makefile realtivo ao projeto de LabProg 1
# componentes	cinematica.c *
#				Cinematica.h *
#				Main.c *
#				resultante.c *
#				Resultante.h *
#				estruturas.h NEW
# * significa que o arquivo eu modifiquei o arquivo -- verificar
#pegando as variáveis <-- para referencia
# $@ --- alvo
# $< --- 1a dependência
# $^ --- lista de dependência s/ repetição
# $+ --- lista de dependência
# $? --- lista de dependência mais "recentes"

CFLAGS= -Wall -g  -g -O2 -lm

#gerando executável
game:	resultante.o cinematica.o  Main.o
	${CC} ${CFLAGS} -o $@ $?

resultante.o:	resultante.c

cinematica.o:	cinematica.c 

Main.o:	Main.c
	${CC} -c $<

#limpando a 'bagunça'
ifndef game
clean:	
	rm *.o
else
clean:	
	rm *.o
	rm game
endif

# sei que já tem o zip e tals, mas colocar um método pra
#	imprimir é uma prática que eu curto
empacotar:	
	@mkdir entrega
	cp  *.c ./entrega
	cp  *.h ./entrega
	cp  *.txt ./entrega
	cp  Makefile ./entrega
	tar -cvf entrega.tar entrega
	rm -rf ./entrega

